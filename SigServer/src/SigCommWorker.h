//---------------------------------------------------------------------------
// IDevCommWorker.h
// Author       : Park Dong Ro
// LastModify   : 2016.8
// Comment      :
//---------------------------------------------------------------------------
#ifndef SigCommWorkerH
#define SigCommWorkerH
//---------------------------------------------------------------------------

#include <Data.DB.hpp>
#include <Data.DBXOracle.hpp>
#include <Data.FMTBcd.hpp>
#include <Data.SqlExpr.hpp>
#include <System.Classes.hpp>

#include "szSock.h"
#include "SgPacketInc.h"
#include "wzQueue.h"
#include "Mios.h"

//---------------------------------------------------------------------------
class SigCommWorker : public TThread
{
private:
	TcpSocket *cSock;
    WSANETWORKEVENTS netEvent;
    WSAEVENT hEvent; // #define WSAEVENT                HANDLE

	AnsiString logDate;

	wzQueue<SgPacket>       qSendPacket;
	wzMQueue<int, SgPacket> qWaitPacket;
	char strIpAddr[32];
	char serverAddr[32];
	char strRealIp[16];
	bool isHold;
	double lastCommTime;
	bool isEndConnectionCheck;
	bool isSendHeatHeat;
	PACK_INFO packInfo;
	/*
	MtPacket23 		mtPacket23;
	MtPacket24		mtPacket24;
	MtPacket41		mtPacket41;
	MtPacket42		mtPacket42;
	MtPacket43		mtPacket43;
	*/
	char rcvUserID[16];
	char rcvUserPW[16];
	char rcvVIN[18];
	char rcvSpecNo[18];

	VH 				dVH;
	VH_SPEC     	dVH_SPEC;
	RECEIPT     	dRECEIPT;

	ISPT_STAT		dISPT_STAT;

	SSR_ISPT_RES	dSSR_ISPT;
	HL_ISPT_RES     dHL_ISPT;
	BS_ISPT_RES     dBS_ISPT;

	TSQLQuery    	*qrySel;

	char dumpBuf[8192*4];

protected:
	virtual void __fastcall Execute(void);

public:
    int runningID;      // ´Ü¸»±â ID
    int pendingID;
	unsigned int   connDevID;
	unsigned int   busID;
    unsigned short seqNo;
	unsigned short qKey;
    bool running;
    bool processEndJob;

	__fastcall SigCommWorker( TcpSocket *csock );

    const char* __fastcall GetAddress();
    bool __fastcall IsHolding();

    void __fastcall SetPendingID(int pid );
    void __fastcall SetRunningID(int rid );
    unsigned short __fastcall GetSeqNo();
	unsigned short __fastcall GetNewQKey();
	unsigned char  __fastcall makeCheckSum(unsigned char* buf, int len);
	void __fastcall SetServerEventTime(LP_PACKINFO pPackInfo);

    void __fastcall StartProcess();
    void __fastcall StopProcess();

	void __fastcall AddPacketToMdt(const SgPacket *p);
	int  __fastcall RecvPacket(LP_IOPACKET_HEADER h, SgPacket* p, int timeout);

	int  __fastcall ProcessAuth(LP_IOPACKET_HEADER h, SgPacket* p);
	void __fastcall ProcessPacket(LP_IOPACKET_HEADER h, SgPacket* p);
	bool __fastcall ProcessLogIn(char* strUserID, char* strPasswd);
	int  __fastcall ProcessReqReceiptInfo();
	bool __fastcall GetVehicleInfo(char* strVin);
	bool __fastcall GetVehicleSpecInfo(char* specNo);

	void __fastcall SendPacket0x23();
	void __fastcall SendPacket0x24();
	void __fastcall SendAck(unsigned char recvOpCode, unsigned short recvSeq);
	void __fastcall SendNAck(unsigned char recvOpCode, unsigned short recvSeq, unsigned char nackCode);

	void __fastcall SendHeartBeat();
	void __fastcall SendHeartBeatRes(const LP_IOPACKET_HEADER h);
	void __fastcall SendMeasuSig(const LP_IOPACKET_HEADER h, char sigType, int eventTime, AnsiString code, AnsiString jName, int price);
	void __fastcall SendPacketToIDev(const SgPacket* p);

    void __fastcall Finalize();
    void __fastcall Send(char* buf);
	void __fastcall CommDump( int devID, const char* pBuf, int iLen, const char* tag );
};
//---------------------------------------------------------------------------
#endif
