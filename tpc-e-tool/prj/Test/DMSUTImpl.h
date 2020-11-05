
#include "DMSUTInterface.h"
#include <fstream>

using namespace TPCE;

namespace TPCE {

	class DMSUTImpl : public CDMSUTInterface {
		fstream& fout;
	public:
		DMSUTImpl(fstream& out) : fout(out)
		{
			// fout.open("./transactions.plan", ios::out | ios::app);
		}

		~DMSUTImpl() { }
		
		bool DataMaintenance( PDataMaintenanceTxnInput pTxnInput ); // return whether it was successful

		bool TradeCleanup( PTradeCleanupTxnInput pTxnInput );   // return whether it was successful
	};
}