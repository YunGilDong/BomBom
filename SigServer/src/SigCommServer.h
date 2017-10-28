//---------------------------------------------------------------------------

#ifndef SigCommServerH
#define SigCommServerH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include "szSock.h"
#include "wzMQueue.h"
#include "SigCommWorker.h"
//---------------------------------------------------------------------------
// SIG 통신 로그
//---------------------------------------------------------------------------
typedef struct {
	unsigned int devID;
	String strLog;
} SIG_COMMLOG, *LP_SIG_COMMLOG;

//---------------------------------------------------------------------------
class SigCommServer : public TThread
{
private:
	char localAddress[32];
	int  localPort;

	TcpServerSocket *sSocket;
    HANDLE     hDumpFile;
	String logDate;
	SgPacket   packet;
	SgPacket   weatherPacket;

	void __fastcall Finalize();
protected:
	void __fastcall Execute();
public:
	bool connectWaiting;
	wzMQueue<int, SigCommWorker*> activeWorkers;  // MDT_ID, MdtCommWorker
	wzMQueue<int, SigCommWorker*> pendingWorkers; // MDT_ID, MdtCommWorker

	//-------------------------------------------------------
	__fastcall SigCommServer(int port);

	void __fastcall StartProcess();
	void __fastcall StopProcess();
	bool __fastcall Init();
	void __fastcall SetStop( bool waiting );

	SigCommWorker* SetActiveWorker(int pendingID, int runningID);
	SigCommWorker* GetWorker(int bitID);

	bool __fastcall AddSendToMdt( int mdtID, const SgPacket *p );
	void __fastcall EndJob(SigCommWorker *pWorker);
};
//---------------------------------------------------------------------------
extern SigCommServer *sigCommSvr;
//---------------------------------------------------------------------------
#endif
