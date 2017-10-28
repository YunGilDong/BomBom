//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "MainFrm.h"
#include "SigCommServer.h"

#define MODULE_NAME     "[SIG_COMM]"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall SigCommServer::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------
SigCommServer *sigCommSvr;
__fastcall SigCommServer::SigCommServer( int port ) : TThread(true)
{
    FreeOnTerminate = true;
	localPort   = port;
    hDumpFile   = NULL;
    connectWaiting  = false;
}

//---------------------------------------------------------------------------
void __fastcall SigCommServer::SetStop( bool waiting )
{
	SigCommWorker **pWorker;
    connectWaiting = waiting;
	if( connectWaiting )
    {
        pWorker = activeWorkers.navFirst();
        while( pWorker!=NULL )
        {
            (*pWorker)->running = false;
            pWorker = activeWorkers.navNext();
        }
    }
}


//---------------------------------------------------------------------------
// Execute
//---------------------------------------------------------------------------
bool __fastcall SigCommServer::Init()
{
	sSocket = new TcpServerSocket();    // szSock - TcpServerSocket (�������ϻ���)
    //sSocket->bind( ipaddress( 127,0,0,1), localPort );
	sSocket->bindall(localPort);    	// bind()
	try{
		sSocket->open();                // open()
	}
	catch(NetException *exp)
	{
		delete exp;
		return false;
	}
	return true;
}

//---------------------------------------------------------------------------
void __fastcall SigCommServer::StartProcess()
{
	Start();    // StartProcess
}

//---------------------------------------------------------------------------
void __fastcall SigCommServer::StopProcess()
{
	Terminate();
	if( sSocket!=NULL ) sSocket->clear();
}


//---------------------------------------------------------------------------
// Execute
//---------------------------------------------------------------------------
void __fastcall SigCommServer::Execute()
{
	String strLog;
	strLog.sprintf(L"SigCommServer���� Port: %d", localPort );
	MainF->SysLog(strLog.c_str(), 1, true);

	TcpSocket *cSock;           		//  Connect�� Sockets ������
	SigCommWorker *worker;              //
	int i;
	String strTime;
	bool socketReset = false;

	//--------------------------------------------------------
	while(!Terminated)
	{
		try{
			while( connectWaiting )     	// setSTOP ��û�� Sleep ���� ���
			{
				strLog.sprintf(L"connectWaiting");
				MainF->SysLog(strLog.c_str(), 1, true);
				Sleep(1);
			}

			if( socketReset )   			// Socket �����߻��� �ٽ� Reset ( Init )
			{
				Init();
				socketReset = false;
			}

			if( !connectWaiting )      		// setSTOP�� �ֱ������� true
			{
				cSock = new TcpSocket();    // TCP ���� ����
				sSocket->accept(cSock);     // sSocket(��������)���� accept ������[���]

				if( connectWaiting )        // setSTOP ��û�� Ŭ���̾�Ʈ ���� �ݱ�
				{
					cSock->close();
					delete cSock;
					continue;
				}
				worker = new SigCommWorker(cSock); 	// ����� cSock, worker������� ����
				pendingWorkers.push( worker->ThreadID, worker);
				worker->SetPendingID( worker->ThreadID );
				worker->StartProcess();

				String convChartoStr = worker->GetAddress();
				strLog.sprintf( L"[SIG_Client] �������PND[%d] %s : %d", worker->ThreadID,convChartoStr, cSock->getPort());
				if( MainF != NULL ) MainF->SysLog(strLog.c_str(), 1, true);
			}
		}
		catch(NetException *exp)
		{
			strLog.sprintf( L"%s Accept : Exception %d", MODULE_NAME, exp->getCode() );
			if( MainF != NULL ) MainF->SysLog(strLog.c_str(), 1, true);
			delete cSock;
			delete exp;
			socketReset = true;
			continue;
		}
	}

	Finalize();
}

//---------------------------------------------------------------------------
bool __fastcall SigCommServer::AddSendToMdt(int mdtID, const SgPacket *p)
{
	String strLog;

	SigCommWorker *pWorker = GetWorker(mdtID);
	if( pWorker != NULL )
	{
		pWorker->AddPacketToMdt( p );

		//==============================================================
		// �������� �α�
		//==============================================================
		/*
		switch( p->getOpCode() )
		{
			case 0x71 : // ������������ ����
				dbProc->AddPacket(p);
				break;
			default :
				break;
		}
		*/
	}

    return true;
}

//---------------------------------------------------------------------------
SigCommWorker* SigCommServer::GetWorker(int bitID)
{
	SigCommWorker *pWorker;
    if( activeWorkers.get( bitID, &pWorker ) ) {
        return pWorker;
    }

    return NULL;
}

//---------------------------------------------------------------------------
SigCommWorker* SigCommServer::SetActiveWorker(int pendingID, int runningID)
{
	SigCommWorker* pWorker = NULL;

    if( pendingWorkers.pop( pendingID, &pWorker ) )
    {
		sigCommSvr->activeWorkers.push( runningID, pWorker );
        pWorker->SetRunningID( runningID );
    }
    return pWorker;
}

//---------------------------------------------------------------------------
void __fastcall SigCommServer::EndJob(SigCommWorker *pWorker)
{
	AnsiString strLog;

    if( pWorker->runningID != 0 )
	{
		strLog.sprintf( "[SIG_Client]  �������� ACT[%d] %s",
			/*pWorker->runningID,*/ pWorker->ThreadID, pWorker->GetAddress() );
		MainF->SysLog(strLog.c_str(), 1, true);
		activeWorkers.remove ( pWorker->runningID );
	}
	else if( pWorker->pendingID != 0 ) {
		strLog.sprintf( "[SIG_Client] �������� PND[%d] %s",
			/*pWorker->connDevID,*/ pWorker->ThreadID, pWorker->GetAddress());
		MainF->SysLog(strLog.c_str(), 1, true);
        pendingWorkers.remove( pWorker->pendingID );
    }
}

//---------------------------------------------------------------------------
void __fastcall SigCommServer::Finalize()
{
	String strLog;
	SigCommWorker *worker;

    while( activeWorkers.popFirst(&worker) )
    {
        worker->Terminate();
    }
	strLog.sprintf( L"%s ActiveWorkers finalize", MODULE_NAME);
    MainF->SysLog(strLog.c_str(), 1, true);

    while( pendingWorkers.popFirst(&worker) )
    {
        worker->Terminate();
    }
	strLog.sprintf( L"%s PendingWorkers finalize", MODULE_NAME);
    MainF->SysLog(strLog.c_str(), 1, true);

    strLog.sprintf( L"%s �����", MODULE_NAME);
    MainF->SysLog(strLog.c_str(), 1, true);
}

//---------------------------------------------------------------------------




