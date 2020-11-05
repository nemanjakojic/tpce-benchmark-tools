#include "CCESUTImpl.h"
#include <iomanip>

using namespace std;

void CCESUTImpl::PrintStatistics() 
{
	double total = bvCnt + sdCnt + tlCnt + toCnt + tsCnt + tuCnt + cpCnt + mwCnt;
	cout << 
		"BV: " << bvCnt << " (" << bvCnt / total * 100 << "%)" << endl <<
		"SD: " << sdCnt << " (" << sdCnt / total * 100 << "%)" << endl << 
		"TL: " << tlCnt << " (" << tlCnt / total * 100 << "%)" << endl << 
		"TO: " << toCnt << " (" << toCnt / total * 100 << "%)" << endl <<
		"TS: " << tsCnt << " (" << tsCnt / total * 100 << "%)" << endl <<
		"TU: " << tuCnt << " (" << tuCnt / total * 100 << "%)" << endl <<
		"CP: " << cpCnt << " (" << cpCnt / total * 100 << "%)" << endl <<
		"MW: " << mwCnt << " (" << mwCnt / total * 100 << "%)" << endl;
}

string CCESUTImpl::ToDateString(TIMESTAMP_STRUCT& time) 
{
	stringstream ss;
	ss	<< "'" << time.year << "-" 
		<< setw(2) << setfill('0') << time.month	<< "-" 
		<< setw(2) << setfill('0') << time.day		<< " " 
		<< setw(2) << setfill('0') << time.hour		<< ":" 
		<< setw(2) << setfill('0') << time.minute	<< ":"
		<< setw(2) << setfill('0') << time.second	<< "'" ;
	string result(ss.str());
	return result;
}

string CCESUTImpl::ToIdList(TTrade *arr, int count) {
	stringstream ss;
	ss << "'" << arr[0];
	for (int i=0; i<count; i++)
	{
		ss << "," << arr[i];
	}
	ss << "'";

	string result(ss.str());
	return result;
}

// 5%, Broker init., Mid to Heavy, Read-Only
bool CCESUTImpl::BrokerVolume( PBrokerVolumeTxnInput pTxnInput ) {
	char (*blist)[50] = pTxnInput->broker_list;
	fout << "EXEC " << "BrokerVolumeFrame1 '" << pTxnInput->sector_name << "', '";
	fout << blist[0]; 
	for (int i=0; i<40 && strlen(blist[i]) > 0; i++) {
		fout << "," << blist[i];
	}
	fout << "'" << endl;
	bvCnt++;
	return true; 
}

// 10%, 
bool CCESUTImpl::TradeResult( PTradeResultTxnInput pTxnInput ) 
{
	fout << "EXEC "<< "TradeResultFrame1 " 
		<< pTxnInput->trade_id << ","
		<< pTxnInput->trade_price << endl;
	return true;
}

// 13%, Customer init., Mid to Heavy, Read-Only
bool CCESUTImpl::CustomerPosition( PCustomerPositionTxnInput pTxnInput ) { 
	fout << "EXEC "<< "CustomerPositionFrame1 " 
		<< pTxnInput->cust_id << ","
		<< "'" <<  pTxnInput->tax_id << "'" << ","
		<< pTxnInput->get_history << "," << pTxnInput->acct_id_idx << endl;
	/*
	if (pTxnInput->get_history) 
	{
	fout << "EXEC " << "CustomerPositionFrame2 " 
	<< pTxnInput->acct_id_idx << endl;
	}
	*/
	cpCnt++;
	return true; 
}

// 18%, Customer init., Medium, Read-Only
bool CCESUTImpl::MarketWatch( PMarketWatchTxnInput pTxnInput ) { 
	if (pTxnInput->acct_id != 0 || pTxnInput->c_id  != 0 || *pTxnInput->industry_name != 0) 
	{
		fout << "EXEC " << "MarketWatchFrame1 "
			<< pTxnInput->c_id << ","
			<< "'" << pTxnInput->industry_name << "'," 
			<< pTxnInput->starting_co_id << ","
			<< pTxnInput->ending_co_id << ","
			<< pTxnInput->acct_id << ","
			<< ToDateString(pTxnInput->start_day) << endl;
	}
	mwCnt++;
	return true; 
}

// 19%, Customer init., Light, Read-Only
bool CCESUTImpl::TradeStatus( PTradeStatusTxnInput pTxnInput ) {
	fout << "EXEC " << "TradeStatusFrame1 "
		<< pTxnInput->acct_id << endl;
	tsCnt++;
	return true; 
}

// 14%, Customer init., Medium, Read-Only
bool CCESUTImpl::SecurityDetail( PSecurityDetailTxnInput pTxnInput ) { 
	fout << "EXEC " << "SecurityDetailFrame1 "
		<< pTxnInput->access_lob_flag << ","
		<< pTxnInput->max_rows_to_return << ","
		<< ToDateString(pTxnInput->start_day) << ","
		<< "'" << pTxnInput->symbol << "'" << endl;

	sdCnt++;
	return true; 
}

// 8%, Customer/Broker init., Medium, Read-Only
bool CCESUTImpl::TradeLookup( PTradeLookupTxnInput pTxnInput ) { 
	if (pTxnInput->frame_to_execute == 1) {
		fout << "EXEC " << "TradeLookupFrame1 " 
			<< pTxnInput->max_trades << ","
			<< ToIdList(pTxnInput->trade_id, pTxnInput->max_trades) << endl;
	}
	else if (pTxnInput->frame_to_execute == 2) {
		fout << "EXEC " << "TradeLookupFrame2 "
			<< pTxnInput->acct_id << ","
			<< ToDateString(pTxnInput->start_trade_dts) << ","
			<< ToDateString(pTxnInput->end_trade_dts) << ","
			<< pTxnInput->max_trades << endl;
	}
	else if (pTxnInput->frame_to_execute == 3) {
		fout << "EXEC " << "TradeLookupFrame3 " 
			<< ToDateString(pTxnInput->start_trade_dts) << ","
			<< ToDateString(pTxnInput->end_trade_dts) << ","
			<< pTxnInput->max_acct_id << ","
			<< pTxnInput->max_trades << ","
			<< "'" << pTxnInput->symbol << "'" << endl;	
	}
	else if (pTxnInput->frame_to_execute == 4) {
		fout << "EXEC " << "TradeLookupFrame4 " 
			<< pTxnInput->acct_id << ","
			<< ToDateString(pTxnInput->start_trade_dts) << endl;
	}
	tlCnt++;
	return true; 
}

// 2%, Read-Write
bool CCESUTImpl::TradeUpdate( PTradeUpdateTxnInput pTxnInput ) 
{ 
	if (pTxnInput->frame_to_execute == 1)
	{
		fout << "EXEC " << "TradeUpdateFrame1 " 
			<< pTxnInput->max_trades << "," 
			<< pTxnInput->max_updates << "," 
			<< ToIdList(pTxnInput->trade_id, pTxnInput->max_trades) << endl;
	}
	else if (pTxnInput->frame_to_execute == 2) 
	{
		fout << "EXEC " << "TradeUpdateFrame2 " 
			<< pTxnInput->max_trades << "," 
			<< pTxnInput->max_updates << ","
			<< pTxnInput->acct_id << ","
			<< ToDateString(pTxnInput->start_trade_dts) << ","
			<< ToDateString(pTxnInput->end_trade_dts) << endl;
	}
	else if (pTxnInput->frame_to_execute == 3)
	{
		fout << "EXEC " << "TradeUpdateFrame3 " 
			<< pTxnInput->max_trades << "," 
			<< pTxnInput->max_updates << "," 
			<< pTxnInput->max_acct_id << ","
			<< pTxnInput->symbol << ","
			<< ToDateString(pTxnInput->start_trade_dts) << ","
			<< ToDateString(pTxnInput->end_trade_dts) << endl;
	}

	tuCnt++;
	return true; 
}

string ReplaceAll(string text, string oldval, string newval) {
	bool done = false;
	size_t pos = text.find(oldval);
	while (pos != string::npos) {
		text = text.replace(pos, oldval.length(), newval);
		pos = text.find(oldval, pos + newval.length());
	}
	return text;
}

string EscapeQuote(string str) {
	return ReplaceAll(str, "'", "''");
}

// 10, ReadWrite,
bool CCESUTImpl::TradeOrder( PTradeOrderTxnInput pTxnInput, INT32 iTradeType, bool bExecutorIsAccountOwner ) {
	fout << "EXEC " << "TradeOrderFrame1 " 
		<< pTxnInput->acct_id << ",'"
		<< pTxnInput->exec_f_name << "','"
		<< pTxnInput->exec_l_name << "','"
		<< pTxnInput->exec_tax_id << "','"
		<< pTxnInput->issue << "'," 
		<< pTxnInput->is_lifo << ",'" 
		<< pTxnInput->st_pending_id << "','" 
		<< pTxnInput->st_submitted_id << "'," 
		<< pTxnInput->trade_qty << "," 
		<< pTxnInput->type_is_margin << ",'" 
		<< pTxnInput->trade_type_id << "','"
		<< EscapeQuote(pTxnInput->co_name) << "','"
		<< pTxnInput->symbol << "',"
		<< pTxnInput->requested_price << endl;
	toCnt++;
	return true; 
}