//---------------------------------------------------------------------------
// IDevCommWorker.cpp
// Author       :
// LastModify   : 2016.05
// Comment      :
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "SigComm.h"
#include "wzFile.h"
#include "SgPacketInc.h"

#include "MainFrm.h"
//#include "CommonFrm.h"

#include "SigCommServer.h"
#include "SigCommWorker.h"
//#include "IDevCommDbProc.h"
//#include "IDevFileGenProc.h"

#define MODULE_NAME     "[Client_SOCK]"
//---------------------------------------------------------------------------
__fastcall SigCommWorker::SigCommWorker(TcpSocket *csock) : TThread(True)
{
    FreeOnTerminate=true;
	running   = true;
    //aa
	cSock     = csock; 	// 생성시에 cSock 연결
	connDevID= 0;
    runningID = 0;
    pendingID = 0;
    logDate   = "";
    seqNo     = 0;
    isHold    = false;
	processEndJob = true;
	int ret;
	isSendHeatHeat = false;

	AnsiString strLog;

	if( csock != NULL )                 // NULL이 아니면 소켓셋팅
	{
		cSock->getAddress(strIpAddr); 	// IP 정보 불러오기

		/*
		on : 지연 시간을 유효하게 할지 어떻지를 지정
		└> true이면, 아직 전송되지 않은 데이터가 있을 경우
		지연시간(linger/단위:milliseconds) 만큼 데이터를 전송한 후
		시간이 지나면 강제 종료됨!

		*/
		if( !cSock->setSoLinger(1) ){
			strLog.printf( "%s Set Option Failed : SO_LINGER", MODULE_NAME);
			MainF->SysLog( strLog.c_str(), 1, true);
		}

		if( !cSock->setNonBlocking(1) ){
			strLog.printf( "%s Set NonBlocking Failed", MODULE_NAME);
			MainF->SysLog( strLog.c_str(), 1, true);
		}

		/*
		WSAEventSelect란 ?
		이벤트 객체를 통해 네트워크 이벤트를 감지해서 처리하는 것.
		동작원리
		1. 소켓을 생성할때 마다 WSACreateEvent() 함수를 이용하여 이벤트 객체를 생성한다.
		2. WSAEventSelect() 함수를 이용하여 소켓과 이벤트를 연결하고 동시에, 처리할 네트워크 이벤트를 등록한다.
		3. WSAWaitForMultipleEvents() 함수를 호출하여 이벤트를 받기위한 대기상태가 된다.
		4. 3번과정이 풀리면, WSAEnumNetworkEvents() 함수를 호출하여 발생한 네트워크 이벤트를 알아내고 적절한 소켓 함수를 찾아 처리하면 된다.
		함수구조
		WSAEVENT WSACreateEvent(); // 이벤트를 만드는 함수
		BOOL WSACloseEvent(WSAEVENT hEvent); // 이벤트를 해제하는 함수
		*/
		//====================================================
		// NETEVENT SET
		if( (hEvent=WSACreateEvent()) == WSA_INVALID_EVENT)
		{
			strLog.printf( "WSACreateEvent failed  (%d)", WSAGetLastError());
			MainF->SysLog( strLog.c_str(), 1, true);
		}
		if( (ret=WSAEventSelect(cSock->handle, hEvent, FD_CLOSE)) == SOCKET_ERROR)
		{
			strLog.printf( "WSAEventSelect error (%d)", WSAGetLastError());
			MainF->SysLog( strLog.c_str(), 1, true);
		}
		//====================================================
	}

//	qrySel = new TSQLQuery(MainF);
//	qrySel->SQLConnection = MainF->DB;
}

//---------------------------------------------------------------------------
const char* __fastcall SigCommWorker::GetAddress()
{
    return strIpAddr;
}

//---------------------------------------------------------------------------
bool __fastcall SigCommWorker::IsHolding()
{
    isHold = true;
    for( int i=0; i<30; i++ )
    {
        if( !isHold ) break;
        Sleep(100);
    }
    return isHold;
}

//---------------------------------------------------------------------------
unsigned short __fastcall SigCommWorker::GetSeqNo()
{
	seqNo = ( seqNo < 65535 ) ? seqNo+1: 1;
	return seqNo;
}

//---------------------------------------------------------------------------
unsigned short __fastcall SigCommWorker::GetNewQKey()
{
    qKey = ( qKey < 65535 ) ? qKey+1: 1;
    return qKey;
}

//---------------------------------------------------------------------
unsigned char __fastcall SigCommWorker::makeCheckSum(unsigned char* buf, int len)
{
	unsigned char chkSum = 0;
	for( int i=0; i<len; i++) chkSum^=buf[i];
	return chkSum;
}


//---------------------------------------------------------------------------
void __fastcall SigCommWorker::SetPendingID(int pid )
{
    pendingID = pid;
    /*
    AnsiString strLog;
    strLog.sprintf( "%s %d Pending", MODULE_NAME, pendingID );
    MainF->fnBtCommLog(strLog.c_str(), 1, true);
    */
}

//---------------------------------------------------------------------------
void __fastcall SigCommWorker::SetRunningID(int rid )
{
	runningID = rid;
    pendingID = 0;
    /*
    AnsiString strLog;
    strLog.printf( "%s %d Running", MODULE_NAME, runningID );
	MainF->fnBtCommLog(strLog.c_str(), 1, true);
    */
}

//---------------------------------------------------------------------------
void __fastcall SigCommWorker::SetServerEventTime(LP_PACKINFO pPackInfo)
{
	packInfo.eventTime[0] = MainF->sysYear - 2000;
	packInfo.eventTime[1] = MainF->sysMon;
	packInfo.eventTime[2] = MainF->sysDay;
	packInfo.eventTime[3] = MainF->sysHour;
	packInfo.eventTime[4] = MainF->sysMin;
	packInfo.eventTime[5] = MainF->sysSec;
}

//---------------------------------------------------------------------------
void __fastcall SigCommWorker::AddPacketToMdt(const SgPacket *p)
{
	qSendPacket.push( *p );
}


//---------------------------------------------------------------------------
void __fastcall SigCommWorker::StartProcess()
{
	Start();
}

//---------------------------------------------------------------------------
void __fastcall SigCommWorker::StopProcess()
{
	running = false;
}

//---------------------------------------------------------------------------
// Execute
//---------------------------------------------------------------------------
void __fastcall SigCommWorker::Execute()
{
	SgPacket   toMdtPacket;
	AnsiString strLog;

	int recvBytes;
	SgPacket    p;
	IOPACKET_HEADER h;
	char* rxBuf;
	int qSize;

	bool isSockError= false;
	bool authorized = false;
	int  i;
	int  loopCnt = 0;
	int  packetTimeOutCnt=0;
	SgPacket* wPacket;
	int ret;
	TDateTime curTime;
	double lastStatReqTime;
	double curTimeSec;
	int opCode;
	int retCode;

	//================================================
	/*
	GetVehicleSpecInfo("08-KCE-00016");
	SgPacket43.clear();
	SgPacket43.setDeviceID(connDevID);
	//SgPacket43.setVhSpecInfo( &dVH_SPEC );
	int len =  SgPacket43.getLength();
	*/

	//==================================================
//	if( (ret = RecvPacket(&h, &p, 5000)) > 0  )
//	{
//		retCode = ProcessAuth(&h, &p);
//	}
//
//	if( retCode != MC_ERR_NONE )
//	{
//		if( retCode > 0 )
//		{
//			SendNAck( h.opCode, h.seqNo, retCode );
//        }
//		Sleep(3000);
//		Finalize();
//		return;
//	}
//	else {
//		strLog.sprintf( "[DEV_%05d] RECV [%02X:%4d] Connection Auth", connDevID, h.opCode, h.length );
//		MainF->SigCommLog(connDevID, strLog.c_str(), 1, true);
//		SendAck(h.opCode, h.seqNo);
//	}
	//==================================================

	curTime = Now();
	curTimeSec = curTime.Val*86400.0;
	lastCommTime = curTimeSec;
	isEndConnectionCheck = false;

	//==================================================
	rxBuf = (char*)p.getBytes();

	while( running && !Terminated )
	{
		isHold = false;

		try{
			if( (recvBytes = cSock->available()) > 0 )
			{
				recvBytes = cSock->recv((char*)rxBuf, IOP_HEADER_SIZE );
//				recvBytes = cSock->recv((char*)rxBuf, 256 );
				AnsiString s ="";
				s.printf("%s [%d]", rxBuf,recvBytes);
//				MainF->SysLog(rxBuf, 1, true);
				MainF->SysLog(s.c_str(), 1, true);

//                SendHeartBeatRes();
//				cSock->send( rxBuf, recvBytes );

//				if( MainF->ckSigCommLog->Checked && recvBytes > 0 )CommDump( connDevID, rxBuf, recvBytes, "RECV");
				if( true && recvBytes > 0 )CommDump( connDevID, rxBuf, recvBytes, "RECV");

				if( recvBytes == IOP_HEADER_SIZE )
				{
					p.getHeader(rxBuf, &h);

					if( h.length > 0 && h.length < IOP_DATA_SIZE )
					{
						recvBytes = cSock->recv( (char*)&rxBuf[IOP_HEADER_SIZE], h.length );
						if( /*MainF->ckSigCommLog->Checked*/true && recvBytes > 0 ) {
							CommDump( connDevID, (char*)&rxBuf[IOP_HEADER_SIZE], recvBytes, "RECV");
						}
					}
					else if( h.length > IOP_DATA_SIZE ) {
						strLog.printf( "[DEV_%05d] RECV [%02X:%4d] 패킷수신오류 LEN: %d",
									connDevID, h.opCode, recvBytes, h.length );
						MainF->SigCommLog( connDevID, strLog, 1, true );
//						running = false;
						continue;
					}

					if( h.length ==0 || recvBytes == (h.length ) )
					{
//						if( MainF->DB_READY ) {
							ProcessPacket(&h, &p);
//						}
					}
					else {
						strLog.printf( "[DEV_%05d] RECV [%02X:%4d] 패킷수신오류 LEN: %d",
									connDevID, h.opCode, recvBytes, h.length );
						MainF->SigCommLog( connDevID, strLog, 1, true );
//						running = false;
						continue;
					}

					lastCommTime = curTimeSec;
					isEndConnectionCheck = false;
				}
				else {
					strLog.printf( "[DEV_%05d] RECV [%02X:%4d] 헤더수신오류 SIZE", connDevID, h.opCode, recvBytes );
					MainF->SysLog(strLog.c_str(), 1, true);
//					MainF->SigCommLog( connDevID, strLog, 1, true );
				}
			}

			//========================================================
			qSize = qSendPacket.size();
			for( i=0; i<qSize; i++)
			{
				qSendPacket.pop( &toMdtPacket );
				SendPacketToIDev( &toMdtPacket );
			}
		}
		catch( NetException *e)
		{
			switch( e->getCode() )
			{
				//수신된 데이타가 없는 경우.
				case WSAEWOULDBLOCK:
					break;
				case WSAECONNRESET :
					isSockError =true;
					//strLog.printf("[DEV_%05d] WSAECONNRESET: %d Remote Host Disconnected.", connDevID, e->getCode() );
					break;
				case WSAENETDOWN :
					isSockError =true;
					//strLog.printf("[DEV_%05d] WSAENETDOWN  : %d Remote Host Disconnected.", connDevID, e->getCode() );
					break;
				default:
					isSockError =true;
					//strLog.printf("[DEV_%05d] Exception : %d", connDevID, e->getCode() );
					break;
			}

			delete e;
			if( isSockError ){
				//MainF->SigCommLog(connDevID, strLog, 1, true);
				//this->Terminate();
//				running = false;
				isSockError = false;
				continue;
			}
		}

		ret = WSAEnumNetworkEvents(cSock->handle, hEvent, &netEvent);
		if( (netEvent.lNetworkEvents & FD_CLOSE) == FD_CLOSE )
		{
			//strLog.printf("[DEV_%05d] NetworkEvent :연결 끊김", connDevID );
			//MainF->SigCommLog(connDevID, strLog.c_str(), 1, true);
			//this->Terminate();
//			running = false;
			continue;
		}
		else  {
			Sleep(100);
		}

		//========================================================
		// Thread Alive MessagePrint
		//========================================================
		/*
		loopCnt++;
		if( connDevID == BitInfos[MainF->cbBit->ItemIndex].bitID &&
			loopCnt >= 50 && MainF->ckSigCommWorker->Checked )
		{
			strLog.sprintf( "DEV_%05d Alive", connDevID );
			MainF->SigCommLog(connDevID, strLog.c_str(), 1, true);
			loopCnt = 0;
		}
		*/

		// 데이터 리로딩 중
//        if( !MainF->DB_READY ) {
//            Sleep(10000);
//            continue;
//        }

		//========================================================
		// Check Packet TimeOut 1초 단위
		//========================================================
		packetTimeOutCnt++;
		if( packetTimeOutCnt >= 10 )
		{
			curTime = Now();
			curTimeSec = curTime.Val*86400.0;

			qWaitPacket.Lock();
			wPacket = qWaitPacket.navFirst();
			while( wPacket != NULL )
			{
				if( wPacket->isTimeOut( curTime ) )
				{
					/*
					switch( wPacket->getOpCode() )
					{
						case 0x60 :
						case 0x62 :
							wPacket->rstCode = 0;
							dbProc->AddAckPacket( wPacket );
							break;
						default :
							break;
					}

					strLog.sprintf( "[DEV_%05d] TimeOut Remove Pakcet : %02X %d", connDevID, wPacket->reqOpcode, wPacket->reqSeqNo );
					MainF->SigCommLog(connDevID, strLog.c_str(), 1, true);
					qWaitPacket.navRemove();
					*/
				}

				wPacket = qWaitPacket.navNext();
			}
			qWaitPacket.UnLock();
			packetTimeOutCnt = 0;


			//============================================================
			// 통신이 없는경우
			//============================================================
			if( (curTimeSec - lastCommTime) >= MainF->cfg.connectionTimeout )
			{
				if( isEndConnectionCheck )
				{
//					running = false;
					strLog.printf( "[DEV_%05d] Connection TimeOut", connDevID );
					MainF->SigCommLog( connDevID, strLog, 1, true );
				}
				else {
					try{
//						SendHeartBeat();
						isSendHeatHeat = true;
						isEndConnectionCheck = true;
						Sleep(3000);

					}
					catch( NetException *e){
						strLog.sprintf( "[DEV_%05d] Connection TimeOut : SendHeartBeat Failed", connDevID );
						delete e;
//						running = false;
						continue;
					}
				}
			}
		 }
	}

	Finalize();
}


//----------------------------------------------------------------------
int __fastcall SigCommWorker::RecvPacket(LP_IOPACKET_HEADER h, SgPacket *p, int timeout)
{
	AnsiString strLog;
	int recvBytes = 0;
	int waitTime  = 0;

	char *rxBuf = p->getBytes();
	while( waitTime < timeout )
	{
		while ( (recvBytes = cSock->available()) > 0 )
		{
			try{
				recvBytes = cSock->recv(rxBuf, IOP_HEADER_SIZE );
				if( /*MainF->ckSigCommLog->Checked*/true && recvBytes > 0 ) CommDump( connDevID, rxBuf, recvBytes, "RECV");

				if( recvBytes == IOP_HEADER_SIZE )
				{
					p->getHeader(rxBuf, h);
					if( h->length > 0 && h->length < IOP_DATA_SIZE ) {
						recvBytes = cSock->recv( (char*)&rxBuf[IOP_HEADER_SIZE], h->length );
						if( /*MainF->ckSigCommLog->Checked*/true && recvBytes > 0 ) CommDump( connDevID, (char*)&rxBuf[IOP_HEADER_SIZE], recvBytes, "RECV");
                    }
                    else if( h->length > IOP_DATA_SIZE ) {
                        strLog.printf( "[DEV_%05d] RECV [%02X:%4d] 패킷수신오류 Length: %d", connDevID, h->opCode, recvBytes, h->length );
                        MainF->SigCommLog( connDevID, strLog, 1, true );
                        return -1;
                    }

					if( h->length==0 || recvBytes == h->length )
                    {
                        return 1;
                    }
                    else {
                        strLog.printf( "[DEV_%05d] RECV [%02X:%4d] 패킷수신오류 Length: %d", connDevID, h->opCode, recvBytes, h->length );
                        MainF->SigCommLog( connDevID, strLog, 1, true );
                        return -1;
                    }
                }
                else {
					strLog.printf( "[DEV_%05d] RECV [%02X:%4d] 헤더수신오류 SIZE", connDevID, h->opCode, recvBytes );
                    MainF->SigCommLog( connDevID, strLog, 1, true );
                    return -1;
                }
            }
            catch(NetException *exp)
            {
                switch( exp->getCode() )
                {
                    case WSAEWOULDBLOCK :
                        delete exp;
                        break;
                    default :
                        //strLog.sprintf( "%s RECV (Exception: %d)", MODULE_NAME, exp->getCode() );
                        //MainF->ProxyLog(strLog, 1, true);
                        cSock->close();
                        delete exp;
                        return -1;
                }
            }
        }
        Sleep(50);
        waitTime+=50;
    }
    return 0;
}


//----------------------------------------------------------------------
// ProcessAuth
//----------------------------------------------------------------------
int __fastcall SigCommWorker::ProcessAuth(LP_IOPACKET_HEADER h, SgPacket* p)
{
    AnsiString strLog;
	char* pData;
	AnsiString strTime;
	int ret;

	pData = p->getBody();
	connDevID = 0;//h->deviceID;

	if( h->opCode != 0x10 ) {
		strLog.printf("%s 접속인증 오류 => OP_CODE: %02X", MODULE_NAME, h->opCode );
		MainF->SysLog( strLog, 1, true);
		return DC_ERR_UNKNOWN_OPCODE;
	}

	if( connDevID == 0 ) {
		strLog.printf("%s 접속인증 오류 => DEV_ID: 0", MODULE_NAME );
		MainF->SysLog( strLog, 1, true);
		return DC_ERR_UNREGIST_DEVID;
	}

//    if( !MainF->DB_READY ) return MC_ERR_DB_DISCONNECTED;

	LP_IDEVINFO pIDevInfo = MainF->GetIDevInfo(connDevID);  // ProcessAuth
	if( pIDevInfo == NULL )
	{
		strLog.printf("%s 접속인증 오류 => 미등록장비 DEV_ID: %u %s", MODULE_NAME, connDevID, GetAddress() );
		MainF->SysLog( strLog, 1, true);
		return DC_ERR_UNREGIST_DEVID;
    }
    else
	{
		SigCommWorker* worker;
		worker = sigCommSvr->GetWorker( connDevID );
        if( worker == NULL )
        {
			sigCommSvr->SetActiveWorker( pendingID, connDevID );
			strLog.printf("[DEV_%05d] Connected", connDevID );
            MainF->SigCommLog(connDevID, strLog, 1, true);

            // 접속서버 IP
            struct sockaddr_in sin;
            int len = sizeof(sin);

            if( getsockname(cSock->handle, (struct sockaddr *)&sin, &len) == -1 )
            {
				strLog.printf("[DEV_%05d] Connected - ", connDevID );
                MainF->SysLog( strLog, 1, true);
            }
            else {
                snprintf( serverAddr, 31, inet_ntoa(sin.sin_addr) );
				strLog.printf("[DEV_%05d] Connected SERVER:%s", connDevID, serverAddr );
                MainF->SysLog( strLog, 1, true);
            }

            strTime = FormatDateTime("YYYYMMDDHHNNSS", Now());
			snprintf( pIDevInfo->stat.updateTime, 15, "%s", strTime.c_str() );
			snprintf( pIDevInfo->ipAddress, 16, "%s", strIpAddr );

			len = p->getDataLength();
			pIDevInfo->stat.commStatus = 1;
        }
        else {
			strLog.printf("[DEV_%05d] duplicate connection : NEW=%s OLD=%s",
				connDevID, strIpAddr, pIDevInfo->ipAddress );
			MainF->SysLog( strLog, 1, true);

			if( (ret=strcmp( strIpAddr, pIDevInfo->ipAddress )) == 0 )
            {
                //if( worker->IsHolding() ){
					strLog.printf("[DEV_%05d] remove duplicate connection", connDevID );
					MainF->SysLog( strLog, 1, true);
					sigCommSvr->EndJob( worker );
                    worker->processEndJob = false;
                    worker->StopProcess();
					Sleep(2000);
                //}
            }
            connDevID = 0;
			return DC_ERR_DUPLICATE_DEVID;
        }
    }
	return MC_ERR_NONE;
}


//----------------------------------------------------------------------
// ProcessPacket
//----------------------------------------------------------------------
void __fastcall SigCommWorker::ProcessPacket(LP_IOPACKET_HEADER h, SgPacket* p)
{
    AnsiString strLog;
    SgPacket reqPacket;
    unsigned short resOpCode;
    unsigned short resSeqNo;
	LP_IDEVINFO pIDevInfo;
	TDateTime curTime;
	AnsiString strTime;
	int cnt;
	bool result;
    unsigned char* pData = p->getBody();

	switch( h->opCode )
	{
		// HeartBeat
		case 0x01 :
			strLog.sprintf( "[DEV_%05d] RECV [%02X:%4d] HeartBeat수신", connDevID, h->opCode, h->length );
			MainF->SigCommLog(connDevID, strLog.c_str(), 1, true);

//			SendHeartBeatRes(h);
			SendMeasuSig(h,'b',10271805,"005930","삼성전자",2645000);
			break;

		// 로그아웃
		case 0x12 :
			strLog.sprintf( "[DEV_%05d] RECV [%02X:%4d] 로그아웃", connDevID, h->opCode, h->length );
			MainF->SigCommLog(connDevID, strLog.c_str(), 1, true);

			SendAck(h->opCode, h->seqNo);
			break;

		// 매수신호
		case 0x20 :

			SendAck(h->opCode, h->seqNo);
			break;


		// 설정정보요청
		case 0x13 :
			strLog.sprintf( "[DEV_%05d] RECV [%02X:%4d] 설정정보요청",
				connDevID, h->opCode, h->length );
			MainF->SigCommLog(connDevID, strLog.c_str(), 1, true);

			SendPacket0x23();
			break;

		// 버전정보요청
		case 0x14 :
			strLog.sprintf( "[DEV_%05d] RECV [%02X:%4d] 버전정보요청",
				connDevID, h->opCode, h->length );
			MainF->SigCommLog(connDevID, strLog.c_str(), 1, true);

			SendPacket0x24();
			break;

		// 접수정보요청
		case 0x31 :
			strLog.sprintf( "[DEV_%05d] RECV [%02X:%4d] 접수정보요청",
				connDevID, h->opCode, h->length );
			MainF->SigCommLog(connDevID, strLog.c_str(), 1, true);

			cnt = ProcessReqReceiptInfo();
			//strLog.sprintf( "[DEV_%05d] PROC 접수정보처리 %d", connDevID, cnt);
			//MainF->SigCommLog(connDevID, strLog.c_str(), 1, true);

//			SendPacketToIDev( &SgPacket41 );

			strLog.sprintf( "[DEV_%05d] RECV [%02X:%4d] 접수정보전송 CNT:%d",
				connDevID, h->opCode, h->length, cnt );
			MainF->SigCommLog(connDevID, strLog.c_str(), 1, true);

			//strLog = SgPacket41::toString( SgPacket41.getBody() );
			//MainF->SigCommLog(connDevID, strLog.c_str(), 0, false);
			break;

		// 차량정보요청
		case 0x32 :
			memcpy( rcvVIN, &pData[18], 18 );

			strLog.sprintf( "[DEV_%05d] RECV [%02X:%4d] 차량정보요청 %s",
				connDevID, h->opCode, h->length, rcvVIN );
			MainF->SigCommLog(connDevID, strLog.c_str(), 1, true);

			if( GetVehicleInfo( rcvVIN ) )
			{
//				SgPacket42.clear();
//				SgPacket42.setDeviceID(connDevID);
				//SgPacket42.setSeqNo( GetSeqNo() );
//				SgPacket42.setVhInfo( &dVH );
//				SendPacketToIDev( &SgPacket42 );

				strLog.sprintf( "[DEV_%05d] SEND [%02X:%4d] 차량정보전송",
					connDevID, h->opCode, h->length );
				MainF->SigCommLog(connDevID, strLog.c_str(), 1, true);

//				strLog = SgPacket42::toString( &dVH );
				MainF->SigCommLog(connDevID, strLog.c_str(), 0, false);
			}
			break;

		// 제원정보요청
		case 0x33 :
			memcpy( rcvSpecNo, &pData[ 0], 18 );

			strLog.sprintf( "[DEV_%05d] RECV [%02X:%4d] 제원정보요청 %s",
				connDevID, h->opCode, h->length, rcvSpecNo );
			MainF->SigCommLog(connDevID, strLog.c_str(), 1, true);

			if( GetVehicleSpecInfo( rcvSpecNo ) )
			{
//				SgPacket43.clear();
//				SgPacket43.setDeviceID(connDevID);
//				SgPacket43.setVhSpecInfo( &dVH_SPEC );
//				SendPacketToIDev( &SgPacket43 );

//				strLog.sprintf( "[DEV_%05d] SEND [%02X:%4d] 제원정보전송",
//					connDevID, 0x43, SgPacket43.getLength() );
//				MainF->SigCommLog(connDevID, strLog.c_str(), 1, true);
			}
			break;

		// 검사시작 수신
		case 0x50 :
			strLog.sprintf( "[DEV_%05d] RECV [%02X:%4d] 검사시작수신",
				connDevID, h->opCode, h->length );
			MainF->SigCommLog(connDevID, strLog.c_str(), 1, true);

			SendAck(h->opCode, h->seqNo);

			memcpy( dISPT_STAT.RCPT_NO, &pData[ 0], 18 );
//			dbProc->AddIsptStat( &dISPT_STAT );
			break;

		// 관능검사결과 수신
		case 0x51 :
			ZeroMemory( &dSSR_ISPT, sizeof(SSR_ISPT_RES));
			memcpy( dSSR_ISPT.OPRT_ID, rcvUserID, 16 );
//			result = SgPacket51::getInspectionResult(pData, &dSSR_ISPT );

			if( result )
			{
				strLog.sprintf( "[DEV_%05d] RECV [%02X:%4d] 관능검사결과수신 %s CNT:%d",
					connDevID, h->opCode, h->length, dSSR_ISPT.RCPT_NO, dSSR_ISPT.ITEM_CNT );
				MainF->SigCommLog(connDevID, strLog.c_str(), 1, true);

				SendAck(h->opCode, h->seqNo);
//				dbProc->AddSsrIsptLog( &dSSR_ISPT );
			}
			else {
				strLog.sprintf( "[DEV_%05d] RECV [%02X:%4d] 관능검사결과수신오류 %s CNT:%d",
					connDevID, h->opCode, h->length, dSSR_ISPT.RCPT_NO, dSSR_ISPT.ITEM_CNT );
				MainF->SigCommLog(connDevID, strLog.c_str(), 1, true);
                SendAck(h->opCode, h->seqNo);
            }
			break;

		// 전조등검사결과 수신
		case 0x52 :
			ZeroMemory( &dHL_ISPT, sizeof(HL_ISPT_RES) );
			memcpy( dHL_ISPT.OPRT_ID, rcvUserID, 16 );

			strLog.sprintf( "[DEV_%05d] RECV [%02X:%4d] 전조등검사결과수신 %s",
				connDevID, h->opCode, h->length, dHL_ISPT.RCPT_NO );
			MainF->SigCommLog(connDevID, strLog.c_str(), 1, true);

//			SgPacket52::getInspectionResult(pData, &dHL_ISPT);
//			dbProc->AddHlIsptLog( &dHL_ISPT );

			SendAck(h->opCode, h->seqNo);
			break;

		// BS검사결과 수신
		case 0x53 :
			ZeroMemory( &dBS_ISPT, sizeof(BS_ISPT_RES) );
			memcpy( dBS_ISPT.OPRT_ID, rcvUserID, 16 );

			strLog.sprintf( "[DEV_%05d] RECV [%02X:%4d] BS검사결과수신 %s",
				connDevID, h->opCode, h->length,  dBS_ISPT.RCPT_NO );
			MainF->SigCommLog(connDevID, strLog.c_str(), 1, true);

//			SgPacket53::getInspectionResult(pData, &dBS_ISPT);
//			dbProc->AddBsIsptLog( &dBS_ISPT );

			SendAck(h->opCode, h->seqNo);
			break;

		// HeartBeat수신
		case 0x70 :
			strLog.sprintf( "[DEV_%05d] RECV [%02X:%4d] HeartBeat수신",
				connDevID, h->opCode, h->length );
			MainF->SigCommLog(connDevID, strLog.c_str(), 1, true);

			SendHeartBeatRes(h);
			break;

		// HeartBeat응답 수신
		case 0x80 :
			strLog.sprintf( "[DEV_%05d] RECV [%02X:%4d] HeartBeat응답수신",
				connDevID, h->opCode, h->length );
			MainF->SigCommLog(connDevID, strLog.c_str(), 1, true);
			break;

		//=============================================================
        // 응답
        //=============================================================
		// 수신패킷에 대한 ACK
        case 0xA0 :
			resOpCode= pData[0];
			resSeqNo = getUInt2( pData, 1);

            strLog.printf( "[DEV_%05d] RECV [%02X:%4d] ACK", connDevID,  h->opCode, h->length );
            MainF->SigCommLog( connDevID, strLog, 1, true );

			/*
            // 응답대기 패킷이 존재 하는경우.
			if( qWaitPacket.pop( resSeqNo, &reqPacket ) )
			{
				// MDT => MMI 응답패킷
				if( reqPacket.reqPID != MDTCOMMSVR_PID ) {
					mmiProxy->AddResPacketToMmi(h, p, &reqPacket );
				}

				switch( resOpCode )
				{
					case 0x60 :  // 메시지 전송
					case 0x62 :  // 제어명령 전송
						reqPacket.rstCode = 1;
						dbProc->AddAckPacket( &reqPacket );
						break;
					default :
						break;
				}
			}
			*/
            break;

        default :
            strLog.printf( "[DEV_%05d] RECV [%02X:%4d] Unknown OpCode", connDevID,  h->opCode, h->length );
            MainF->SigCommLog( connDevID, strLog, 1, true );
            break;
    }
}

//----------------------------------------------------------------------
// ProcessLogIN
//----------------------------------------------------------------------
bool __fastcall SigCommWorker::ProcessLogIn(char* strUserID, char* strPasswd)
{
/*	int ret;
	bool res = false;
	qrySel->SQL->Text =
	"SELECT OPRT_ID, OPRT_PWD 	\
		FROM OPRT             	\
	WHERE OPRT_ID=:pUserID    	\
		AND OPRT_PWD = USER_PASS_CRYPT(:pPasswd, 1)";

	qrySel->ParamByName("pUserID")->AsAnsiString = strUserID;
	qrySel->ParamByName("pPasswd")->AsAnsiString = strPasswd;

	if((ret = CommonF->OpenSQL(qrySel)) > 0)
	{
		try {
			if( !qrySel->IsEmpty() )
			{
				res = true;
			}
		}catch(...){
		}
	}
	qrySel->Close();

	return res;     */
}


//----------------------------------------------------------------------
// SendPacket0x23
//
// - 설정정보 전송
//----------------------------------------------------------------------
void __fastcall SigCommWorker::SendPacket0x23()
{
/*
	AnsiString strLog;
	int len;
	char *buf;

	SgPacket23.setDeviceID( connDevID );

	SgPacket23.setConfig(&IDevFtpSvrInfo);
	SgPacket23.setSeqNo( GetSeqNo() );
	SgPacket23.setDataLength( SgPacket23::PACKET_DATA_SIZE );

	len = SgPacket23.getLength();
	buf = SgPacket23.getBytes();
	cSock->send( buf, len );

	if( MainF->ckSigCommLog->Checked )CommDump( connDevID, buf, len, "SEND");

	strLog.sprintf( "[DEV_%05d] SEND [%02X:%4d] 설정정보전송", connDevID, 0x23, len );
	MainF->SigCommLog(connDevID, strLog.c_str(), 1, true); */
}


//----------------------------------------------------------------------
// SendPacket0x24
//
// - 버전정보 전송
//----------------------------------------------------------------------
void __fastcall SigCommWorker::SendPacket0x24()
{
 /*	AnsiString strLog;
	int len;
	char *buf;

	SgPacket24.setDeviceID( connDevID );
	SgPacket24.setSeqNo( GetSeqNo() );
	SgPacket24.setDataLength( SgPacket24::PACKET_DATA_SIZE );

	SgPacket24.setVersionInfo( DataVersion.isptCrtrVer, DataVersion.isptCrtrFileName,
							   DataVersion.specVer, DataVersion.specFileName );

	len = SgPacket24.getLength();
	buf = SgPacket24.getBytes();
	cSock->send( buf, len );

	if( MainF->ckSigCommLog->Checked )CommDump( connDevID, buf, len, "SEND");

	strLog.sprintf( "[DEV_%05d] SEND [%02X:%4d] 버전정보전송", connDevID, 0x24, len );
	MainF->SigCommLog(connDevID, strLog.c_str(), 1, true);    */
}


//----------------------------------------------------------------------
// ProcessReqReceipt
// - 접수정보 전송
//----------------------------------------------------------------------
int __fastcall SigCommWorker::ProcessReqReceiptInfo()
{
/*	int ret;
	int cnt;

	SgPacket41.clear();

	SgPacket41.setDeviceID(connDevID);

	// 검사일자가 오늘인 접수정보 전송
	if( MainF->cfg.UseIsptDate )
	{
		qrySel->SQL->Text =
		"SELECT A.RCPT_NO, A.VIN, A.VH_REG_NO                   \
			,NVL(A.ISPT_DIV_CD, 0) ISPT_DIV_CD                  \
			,NVL(A.ISPT_TP, 1) ISPT_TP                          \
			,A.ISPT_OFFICE_ID                                   \
			,A.RCPT_STAT                                        \
			,A.RCPT_DT                                          \
			,A.ISPT_DT                                          \
			,TO_NUMBER( TO_CHAR(A.ISPT_DT,'YYYY') ) ISPT_YEAR   \
			,TO_NUMBER( TO_CHAR(A.ISPT_DT,'MM') )  ISPT_MON     \
			,TO_NUMBER( TO_CHAR(A.ISPT_DT,'DD') )  ISPT_DAY     \
			,NVL( C.VH_NM, '-') VH_NM                           \
		FROM                                                    \
			ISPT_RCPT A, VH B, SPEC C                           \
		WHERE A.RCPT_STAT = 1                                   \
			AND ISPT_DT = TO_CHAR( SYSDATE, 'YYYY-MM-DD')       \
			AND A.VIN = B.VIN                                   \
			AND B.SPEC_NO = C.SPEC_NO(+)                        \
		ORDER BY A.RCPT_NO";
	}
	else
	{
		// TEST시  모든 접수정보 전송
		qrySel->SQL->Text =
		"SELECT A.RCPT_NO, A.VIN, A.VH_REG_NO 		\
			,NVL(A.ISPT_DIV_CD, 0) ISPT_DIV_CD      \
			,NVL(A.ISPT_TP, 1) ISPT_TP              \
			,A.ISPT_OFFICE_ID                       \
			,A.RCPT_STAT                            \
			,A.RCPT_DT                              \
			,TO_NUMBER( TO_CHAR(A.RCPT_DT,'YYYY') ) ISPT_YEAR   \
			,TO_NUMBER( TO_CHAR(A.RCPT_DT,'MM') )  ISPT_MON     \
			,TO_NUMBER( TO_CHAR(A.RCPT_DT,'DD') )  ISPT_DAY     \
			,NVL( C.VH_NM, '-') VH_NM               \
		FROM                                        \
			ISPT_RCPT A, VH B, SPEC C               \
		WHERE A.RCPT_STAT = 1                       \
			AND A.VIN = B.VIN                       \
			AND B.SPEC_NO = C.SPEC_NO(+)            \
		ORDER BY A.RCPT_NO";
	}

	cnt = 0;
	if((ret = CommonF->OpenSQL(qrySel)) > 0)
	{
		try {
			while( !qrySel->Eof)
			{
				ZeroMemory( &dRECEIPT, sizeof( RECEIPT ) );
				snprintf( dRECEIPT.RCPT_NO,   18, "%s", qrySel->FieldByName("RCPT_NO"   )->AsAnsiString.c_str() );
				snprintf( dRECEIPT.VIN,       18, "%s", qrySel->FieldByName("VIN"       )->AsAnsiString.c_str() );
				snprintf( dRECEIPT.VH_REG_NO, 20, "%s", qrySel->FieldByName("VH_REG_NO" )->AsAnsiString.c_str() );
				snprintf( dRECEIPT.VH_NM,     31, "%s", qrySel->FieldByName("VH_NM"     )->AsAnsiString.c_str() );

				dRECEIPT.ISPT_DIV_CD = qrySel->FieldByName("ISPT_DIV_CD" )->AsInteger;
				dRECEIPT.ISPT_TP     = qrySel->FieldByName("ISPT_TP"     )->AsInteger;
				dRECEIPT.RCPT_YEAR   = qrySel->FieldByName("ISPT_YEAR"   )->AsInteger;
				dRECEIPT.RCPT_MON    = qrySel->FieldByName("ISPT_MON"    )->AsInteger;
				dRECEIPT.RCPT_DAY    = qrySel->FieldByName("ISPT_DAY"    )->AsInteger;

				SgPacket41.addReceiptInfo( &dRECEIPT );

				cnt++;
				if( cnt >= MAX_RCPT_INFO_CNT ) break;
				qrySel->Next();
			}
		}catch(...){
		}
	}
	qrySel->Close();

	return cnt;                   */
}

//----------------------------------------------------------------------
// GetVehicleInfo
// - 차량정보 전송
//----------------------------------------------------------------------
bool __fastcall SigCommWorker::GetVehicleInfo(char* strVin)
{
 /*	bool rst = false;
	int ret;
	qrySel->SQL->Text =
	"SELECT VIN, VH_REG_NO, SPEC_NO, 				\
		NVL(RUN_DIST,0) RUN_DIST, FIRST_REG_YMD, 	\
		SUBSTR( FIRST_REG_YMD, 1, 4) FREG_YEAR, 	\
		SUBSTR( FIRST_REG_YMD, 5, 2) FREG_MON, 		\
		SUBSTR( FIRST_REG_YMD, 7, 2) FREG_DAY 		\
		FROM VH 									\
	WHERE VIN=:pVIN";

	qrySel->ParamByName("pVIN")->AsAnsiString = strVin;

	ZeroMemory( &dVH, sizeof( VH ) );

	if((ret = CommonF->OpenSQL(qrySel)) > 0)
	{
		try {
			if( !qrySel->IsEmpty() )
			{
				snprintf( dVH.VIN,       18, "%s", qrySel->FieldByName("VIN"      )->AsAnsiString.c_str() );
				snprintf( dVH.VH_REG_NO, 20, "%s", qrySel->FieldByName("VH_REG_NO")->AsAnsiString.c_str() );
				snprintf( dVH.SPEC_NO,   18, "%s", qrySel->FieldByName("SPEC_NO"  )->AsAnsiString.c_str() );

				dVH.runDistance = qrySel->FieldByName("RUN_DIST"  )->AsInteger;
				dVH.firstRegYear= qrySel->FieldByName("FREG_YEAR" )->AsInteger;
				dVH.firstRegMon = qrySel->FieldByName("FREG_MON"  )->AsInteger;
				dVH.firstRegDay = qrySel->FieldByName("FREG_DAY"  )->AsInteger;
				rst = true;
			}
		}catch(...){
		}
	}
	qrySel->Close();
	return rst;          */
}


//----------------------------------------------------------------------
// GetVehicleSpecInfo
// -
//----------------------------------------------------------------------
bool __fastcall SigCommWorker::GetVehicleSpecInfo(char* specNo)
{
 /*	bool rst = false;
	int ret;

	qrySel->SQL->Text =
	"SELECT A.SPEC_NO                           \
		,A.MNFT_NM                              \
		,A.FIRST_MNFT_NM                        \
		,A.VH_NM                                \
		,A.FORM_NM                              \
		,A.SEAT_CAPA                            \
		,A.VH_TY_CD                             \
		,A.VH_SE_CD                             \
		,NVL(A.VH_WT, 0)        VH_WT           \
		,NVL(A.MAX_CARRY_WT, 0) MAX_CARRY_WT    \
		,NVL(A.VH_TOT_WT, 0)    VH_TOT_WT       \
		,NVL(A.LOAD_FA_WT, 0)   LOAD_FA_WT      \
		,NVL(A.LOAD_RA_WT, 0)   LOAD_RA_WT      \
		,A.ENG_FORM_NM                          \
		,A.ENG_MAX_OUTPUT                       \
		,A.ENG_RPM                              \
		,A.ENG_SLNDCNT                          \
		,A.ENG_DSPL                             \
		,A.USE_FUEL_CD                          \
		,A.WHEELBASE                            \
		,A.TIRE_FRONT_FORM                      \
		,A.TIRE_REAR_FORM                       \
		,A.MODEL_YEAR_SYM_CD                    \
		,SI_0.SPEC_IMG_NM SPEC_IMG_NM_0         \
		,SI_1.SPEC_IMG_NM SPEC_IMG_NM_1         \
		,SI_2.SPEC_IMG_NM SPEC_IMG_NM_2         \
		,SI_3.SPEC_IMG_NM SPEC_IMG_NM_3         \
	FROM SPEC A                                 \
		, SPEC_IMG SI_0                         \
		, SPEC_IMG SI_1                         \
		, SPEC_IMG SI_2                         \
		, SPEC_IMG SI_3                         \
	WHERE  A.SPEC_NO = :pSpecNo                 \
		AND A.SPEC_NO = SI_0.SPEC_NO(+)         \
		AND A.SPEC_NO = SI_1.SPEC_NO(+)         \
		AND A.SPEC_NO = SI_2.SPEC_NO(+)         \
		AND A.SPEC_NO = SI_3.SPEC_NO(+)";

	qrySel->ParamByName("pSpecNo")->AsAnsiString = specNo;

	ZeroMemory( &dVH_SPEC, sizeof( VH_SPEC ) );

	if( (ret = CommonF->OpenSQL(qrySel)) > 0 )
	{
		try
		{
			if( !qrySel->IsEmpty() )
			{
				snprintf( dVH_SPEC.SPEC_NO,       18, "%s", qrySel->FieldByName("SPEC_NO"      	)->AsAnsiString.c_str() );
				snprintf( dVH_SPEC.MNFT_NM, 	  32, "%s", qrySel->FieldByName("MNFT_NM"	   	)->AsAnsiString.c_str() );
				snprintf( dVH_SPEC.FIRST_MNFT_NM, 32, "%s", qrySel->FieldByName("FIRST_MNFT_NM"	)->AsAnsiString.c_str() );
				snprintf( dVH_SPEC.VH_NM,   	  31, "%s", qrySel->FieldByName("VH_NM"  		)->AsAnsiString.c_str() );
				snprintf( dVH_SPEC.FORM_NM,   	  16, "%s", qrySel->FieldByName("FORM_NM"  		)->AsAnsiString.c_str() );

				dVH_SPEC.SEAT_CAPA =  qrySel->FieldByName("SEAT_CAPA"  		)->AsInteger;
				snprintf( dVH_SPEC.VH_TY_CD,   	  16, "%s", qrySel->FieldByName("VH_TY_CD"      )->AsAnsiString.c_str() );
				snprintf( dVH_SPEC.VH_SE_CD,   	  16, "%s", qrySel->FieldByName("VH_SE_CD"  	)->AsAnsiString.c_str() );

				dVH_SPEC.VH_WT 		    = qrySel->FieldByName("VH_WT"  		  )->AsInteger;
				dVH_SPEC.MAX_CARRY_WT   = qrySel->FieldByName("MAX_CARRY_WT"  )->AsInteger;
				dVH_SPEC.VH_TOT_WT      = qrySel->FieldByName("VH_TOT_WT"  	  )->AsInteger;
				dVH_SPEC.LOAD_FA_WT     = qrySel->FieldByName("LOAD_FA_WT"    )->AsInteger;
				dVH_SPEC.LOAD_RA_WT     = qrySel->FieldByName("LOAD_RA_WT"    )->AsInteger;

				snprintf( dVH_SPEC.ENG_FORM_NM,   16, "%s", qrySel->FieldByName("ENG_FORM_NM"  	)->AsAnsiString.c_str() );
				dVH_SPEC.ENG_MAX_OUTPUT = qrySel->FieldByName("ENG_MAX_OUTPUT")->AsFloat*10;
				dVH_SPEC.ENG_RPM        = qrySel->FieldByName("ENG_RPM"       )->AsInteger;
				dVH_SPEC.ENG_SLNDCNT    = qrySel->FieldByName("ENG_SLNDCNT"   )->AsInteger;
				dVH_SPEC.ENG_DSPL       = qrySel->FieldByName("ENG_DSPL"      )->AsFloat*10;

				snprintf( dVH_SPEC.USE_FUEL_CD,    8, "%s", qrySel->FieldByName("USE_FUEL_CD"  	)->AsAnsiString.c_str() );
				dVH_SPEC.WHEELBASE      = qrySel->FieldByName("WHEELBASE"     )->AsInteger;

				snprintf( dVH_SPEC.TIRE_FRONT_FORM,  32, "%s", qrySel->FieldByName("TIRE_FRONT_FORM"  )->AsAnsiString.c_str() );
				snprintf( dVH_SPEC.TIRE_REAR_FORM,   32, "%s", qrySel->FieldByName("TIRE_REAR_FORM"   )->AsAnsiString.c_str() );
				snprintf( dVH_SPEC.MODEL_YEAR_SYM_CD, 3, "%s", qrySel->FieldByName("MODEL_YEAR_SYM_CD")->AsAnsiString.c_str() );

				snprintf( dVH_SPEC.SPEC_IMG_NM_0,  32, "%s", qrySel->FieldByName("SPEC_IMG_NM_0"  )->AsAnsiString.c_str() );
				snprintf( dVH_SPEC.SPEC_IMG_NM_1,  32, "%s", qrySel->FieldByName("SPEC_IMG_NM_1"  )->AsAnsiString.c_str() );
				snprintf( dVH_SPEC.SPEC_IMG_NM_2,  32, "%s", qrySel->FieldByName("SPEC_IMG_NM_2"  )->AsAnsiString.c_str() );
				snprintf( dVH_SPEC.SPEC_IMG_NM_3,  32, "%s", qrySel->FieldByName("SPEC_IMG_NM_3"  )->AsAnsiString.c_str() );
				rst = true;
			}
		}
		catch(...)
		{
		}
	}
	qrySel->Close();
	return rst;         */
}

//----------------------------------------------------------------------
// SendAck
//
// OPCODE : 0xA0
//----------------------------------------------------------------------
void __fastcall SigCommWorker::SendAck(unsigned char recvOpCode, unsigned short recvSeq)
{
	AnsiString strLog;
	int off;
	unsigned char txBuf[IOP_HEADER_SIZE+14];

	ZeroMemory(txBuf, IOP_HEADER_SIZE+12);
	txBuf[ 0] = 0xA0;
	setUInt2(txBuf, 1, GetSeqNo() );
	setUInt4(txBuf, 3, connDevID );    // MDT ID
	setUInt2(txBuf, 7, 3 );            // DataLength

	off = IOP_HEADER_SIZE;
	txBuf[off++] = recvOpCode;
	setUInt2(txBuf, 7, recvSeq );

	cSock->send( (char *)txBuf, IOP_HEADER_SIZE+3 );

	strLog.sprintf( "[DEV_%05d] SEND [%02X:%4d] SendAck", connDevID, 0xA0, 3 );
	MainF->SigCommLog(connDevID, strLog.c_str(), 1, true);
}


//----------------------------------------------------------------------
// SendNAck
//
// OPCODE : 0xA1
//----------------------------------------------------------------------
void __fastcall SigCommWorker::SendNAck(unsigned char recvOpCode, unsigned short recvSeq, unsigned char nackCode)
{
	AnsiString strLog;
	int off;
	unsigned char txBuf[IOP_HEADER_SIZE+14];

	ZeroMemory(txBuf, IOP_HEADER_SIZE+12);
	txBuf[ 0] = 0xA1;
	setUInt2(txBuf, 1, GetSeqNo() );
	setUInt4(txBuf, 3, connDevID );    // MDT ID
	setUInt2(txBuf, 7, 4 );            // DataLength

	off = IOP_HEADER_SIZE;
	txBuf[off++] = recvOpCode;
	setUInt2(txBuf, off, recvSeq ); off+=2;
	txBuf[off++] = nackCode;

	cSock->send( (char *)txBuf, IOP_HEADER_SIZE+4 );

	strLog.sprintf( "[DEV_%05d] SEND [%02X:%4d] SendNAck", connDevID, 0xA1, 4 );
	MainF->SigCommLog(connDevID, strLog.c_str(), 1, true);
}

//----------------------------------------------------------------------
// SendHeartBeat
//
// OPCODE : 0x70
//----------------------------------------------------------------------
void __fastcall SigCommWorker::SendHeartBeat()
{
	AnsiString strLog;
	unsigned char txBuf[IOP_HEADER_SIZE+2];

	ZeroMemory(txBuf, IOP_HEADER_SIZE+2);
	txBuf[ 0] = 0x70;
	setUInt2(txBuf, 1, GetSeqNo() );
	setUInt4(txBuf, 3, connDevID );    // DEV ID
	setUInt2(txBuf, 7, 2 );            // DataLength

	cSock->send( (char *)txBuf, IOP_HEADER_SIZE+2 );

	strLog.sprintf( "[DEV_%05d] SEND [%02X:%4d] HeartBeat", connDevID, 0x70, 2 );
	MainF->SigCommLog(connDevID, strLog.c_str(), 1, true);
}

//----------------------------------------------------------------------
// SendHeartBeatRes
//
// OPCODE : 0x01
//----------------------------------------------------------------------
void __fastcall SigCommWorker::SendHeartBeatRes(const LP_IOPACKET_HEADER h)
{
	AnsiString strLog;
	unsigned char txBuf[IOP_HEADER_SIZE+1];

	ZeroMemory(txBuf, IOP_HEADER_SIZE+1);

	txBuf[0] = 0x7E;
	txBuf[1] = 0x7E;
	setUInt2(txBuf, 2, 1);            // DataLength
	txBuf[4] = 0;
	txBuf[5] = 0x01;
	txBuf[6] = h->seqNo;
	txBuf[7] = 0;

	cSock->send( (char *)txBuf, IOP_HEADER_SIZE+1 );

	strLog.sprintf( "[DEV_%05d] SEND [%02X:%4d] HeartBeat응답", connDevID, 0x80, 2 );
	MainF->SigCommLog(connDevID, strLog.c_str(), 1, true);


}


//----------------------------------------------------------------------
// SendMeasuSig
//
// OPCODE : 0x01
//----------------------------------------------------------------------
void __fastcall SigCommWorker::SendMeasuSig(const LP_IOPACKET_HEADER h, char sigType, int eventTime, AnsiString code, AnsiString jName, int price)
{
	AnsiString strLog;
	unsigned char txBuf[IOP_HEADER_SIZE+49];
	unsigned char sigBuf[48];

	ZeroMemory(txBuf, IOP_HEADER_SIZE+1);

	txBuf[0] = 0x7E;
	txBuf[1] = 0x7E;
	setUInt2(txBuf, 2, 49);            // DataLength
	txBuf[4] = 0;
	txBuf[5] = 0x20;
	txBuf[6] = h->seqNo;

	// 매수 Data 버퍼
	sigBuf[0] = sigType;  // 구분
	setInt4(sigBuf,1,eventTime);  // 시간
	snprintf(&sigBuf[5],7,"%s",code);  // 코드
	snprintf(&sigBuf[12],32,"%s",jName);  // 종목명
	setInt4(sigBuf,44,price);                   // 가격

	memcpy(&txBuf[7], sigBuf, 48);
	txBuf[55] = 0;



	cSock->send( (char *)txBuf, IOP_HEADER_SIZE + 49);

	strLog.sprintf( "[DEV_%05d] SEND [%02X:%4d] SendMeasuSig", connDevID, 0x80, 2 );
	MainF->SigCommLog(connDevID, strLog.c_str(), 1, true);
}


//----------------------------------------------------------------------
// sendPacket
//----------------------------------------------------------------------
void __fastcall SigCommWorker::SendPacketToIDev(const SgPacket* p)
{
/*
    AnsiString strLog;
	unsigned short seqNo;

	char* buf = (char *)( p->getBytes() );
	unsigned short len = p->getLength();

	if( !p->staticSeq ) {
		seqNo = GetSeqNo();
		p->setSeqNo( seqNo );
	}

	try {
		cSock->send( buf, len );
	}
	catch (...) {
		strLog.sprintf( "[DEV_%05d] SEND [%02X:%4d] Failed", connDevID, p->getOpCode(), len );
		MainF->SigCommLog(connDevID, strLog.c_str(), 1, true);
	}


	if( MainF->ckSigCommLog->Checked ) {
		CommDump( connDevID, (char *)p->getBytes(), len, "SEND");
	}         */
}

//---------------------------------------------------------------------------
void __fastcall SigCommWorker::Finalize()
{
    AnsiString strLog;
    AnsiString strTime;
	if(cSock!=NULL )
    {
		try{
            try{
                cSock->close();
                //strLog.printf("[DEV_%05d] Socket Closed", connDevID );
                //MainF->SigCommLog(bitLoclaID, strLog, 1, true);
            }catch( NetException *e){
			}
		}__finally{
            delete cSock;
        }
	}

	strLog.printf("[SIG_Client] Disconnected", connDevID );
//	MainF->SigCommLog(connDevID, strLog, 1, true);
	MainF->SysLog(strLog.c_str(),1, true);
    strTime = FormatDateTime("YYYYMMDDHHNNSS", Now());

    //==============================================
//	IDevInfoLock->rdLock();      // rdLock
	IDEVINFO *idevInfo;
	if( (idevInfo =  MainF->GetIDevInfo( connDevID )) != NULL )  // locked
	{
		idevInfo->stat.commStatus = 0;
		snprintf( idevInfo->stat.updateTime, 15, "%s", strTime.c_str() );
    }
//	IDevInfoLock->rdUnlock();    // rdUnlock
	//==============================================

    qSendPacket.clear();
	qWaitPacket.clear();

    delete qrySel;
	if( processEndJob ) sigCommSvr->EndJob( this );
}

//---------------------------------------------------------------------------
// CommDump
//---------------------------------------------------------------------------
void __fastcall SigCommWorker::CommDump( int devID, const char* pBuf, int iLen, const char* tag )
{
    DWORD      dwWriteSize;
	String strFile;

    int sLen = 0;
    AnsiString sTag;
    HANDLE     hDumpFile;

    TDateTime curTime = Now();
    AnsiString strDate = curTime.FormatString("yyyy-mm-dd");
    AnsiString strTime = curTime.FormatString("[hh:nn:ss]");


    AnsiString logDir = MainF->LOG_ROOT + "\\"+strDate;
    MkDir( logDir );
	strFile.printf(L"%s\\DUMP_DEV_%05d.log", logDir, devID);
	if((hDumpFile = CreateFile(strFile.c_str(),
                           GENERIC_READ|GENERIC_WRITE,
                           FILE_SHARE_READ,
                           NULL,
						   OPEN_ALWAYS,
                           FILE_ATTRIBUTE_NORMAL,
						   NULL)) == INVALID_HANDLE_VALUE) return;

    SetFilePointer(hDumpFile, 0, NULL, FILE_END);
    int i=0;
    int wLen;

	sLen = strToHexStr( pBuf, iLen, dumpBuf );
    sTag.printf( "%s %s\r\n", strTime.c_str(), tag );
    WriteFile( hDumpFile, sTag.c_str(), sTag.Length(), &dwWriteSize, NULL);
    while( sLen > 0 )
    {
        wLen = min( 60, sLen );
		WriteFile( hDumpFile, &dumpBuf[i], wLen, &dwWriteSize, NULL);
        WriteFile( hDumpFile, "\r\n", 2, &dwWriteSize, NULL);
        sLen -= wLen;
        i+=wLen;
    }
    if( hDumpFile != NULL ) {
        CloseHandle(hDumpFile);
    }
}

//---------------------------------------------------------------------------






