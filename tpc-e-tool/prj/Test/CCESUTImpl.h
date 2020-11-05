
#ifndef CE_CCESUTImpl_H_
#define CE_CCESUTImpl_H_

#include "CESUTInterface.h"
#include <fstream>

using namespace std;
using namespace TPCE;

namespace TPCE {

class CCESUTImpl : public CCESUTInterface 
{
private:
	// CEGenLogger log;
	fstream& fout;
	// fstream out;
	int bvCnt, cpCnt, mwCnt, sdCnt, tlCnt, toCnt, tsCnt, tuCnt;
public:
	CCESUTImpl(fstream& out) : bvCnt(0), cpCnt(0), mwCnt(0), sdCnt(0), 
		tlCnt(0), toCnt(0), tsCnt(0), tuCnt(0), fout(out)
	{
	}

	virtual bool BrokerVolume( PBrokerVolumeTxnInput pTxnInput );
	
    virtual bool CustomerPosition( PCustomerPositionTxnInput pTxnInput );
	
    virtual bool MarketWatch( PMarketWatchTxnInput pTxnInput );
	
    virtual bool SecurityDetail( PSecurityDetailTxnInput pTxnInput ) ;

    virtual bool TradeLookup( PTradeLookupTxnInput pTxnInput ) ;
	
    virtual bool TradeOrder( PTradeOrderTxnInput pTxnInput, INT32 iTradeType, bool bExecutorIsAccountOwner );
	
    virtual bool TradeStatus( PTradeStatusTxnInput pTxnInput );

    virtual bool TradeUpdate( PTradeUpdateTxnInput pTxnInput );

	virtual bool TradeResult( PTradeResultTxnInput pTxnInput );     

	void PrintStatistics();

	~CCESUTImpl() { }  

	string ToIdList(TTrade *arr, int count);

	string ToDateString(TIMESTAMP_STRUCT& time);
};

}

#endif