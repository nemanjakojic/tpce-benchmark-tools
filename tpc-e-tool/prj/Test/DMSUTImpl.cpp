
#include "DMSUTImpl.h"
using namespace std;
using namespace TPCE;

bool DMSUTImpl::DataMaintenance(PDataMaintenanceTxnInput pTxnInput) {
	fout << "EXEC " << "DataMaintenanceFrame1 "
		<< pTxnInput->acct_id << ", "
		<< pTxnInput->c_id << ", "
		<< pTxnInput->co_id << ", '"
		<< pTxnInput->day_of_month << "', '"
		<< pTxnInput->symbol << "', '"
		<< pTxnInput->table_name << "', '"
		<< pTxnInput->tx_id << "', '"
		<< "1010'," 
		<< pTxnInput->vol_incr << endl;
	return true;
}

bool DMSUTImpl::TradeCleanup(PTradeCleanupTxnInput pTxnInput) {
	fout << "EXEC " << "TradeCleanup " 
		<< pTxnInput->start_trade_id << ", '"
		<< pTxnInput->st_canceled_id << "', '"
		<< pTxnInput->st_pending_id << "', '"
		<< pTxnInput->st_submitted_id << "'" << endl;
	return true;
}
