//---------------------------------------------------------------------------
#ifndef _MT_PACKET_H_
#define _MT_PACKET_H_
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include "wzByte.h"
#include "szSock.h"
#include "Mios.h"
#include "SigComm.h"

//----------------------------------------------------------------------------
class SgPacket
{

private:

protected:
	unsigned char buf[IOP_BUF_SIZE];
	void headerToString(unsigned char *buf, char *line);

public:
	int  PACKET_SIZE;
	bool waitingAck;
	int  retry;
	int  waitedTime;
	int  length;
	unsigned char  rstCode;
	bool staticSeq;

	//==============================================================
	// 패킷 중계용
	//==============================================================
	unsigned reqPID;
	sockaddr_in    reqAddress;
	unsigned char  reqOpcode;
	unsigned short reqSeqNo;

	unsigned int busID;

	TDateTime packSendTime;
	TDateTime waitLimitTime;

	//==============================================================
	SgPacket();
	~SgPacket();

	void getHeader(LP_IOPACKET_HEADER h);
	static void getHeader(const char* b, LP_IOPACKET_HEADER h);
	unsigned char* getBody();

	unsigned char *getBytes();
	void setBytes(const unsigned char *b, int off, int len);
	void setBytes(int dstOff, const unsigned char *src, int srcOff, int len);

	unsigned int getDeviceID();
	void setDeviceID( unsigned int deviceID );

	unsigned char getOpCode();
	void setOpCode(unsigned char v);
	unsigned short getSeqNo();

	void setSeqNo( unsigned short seqNo );

	unsigned char getByte(int idx);

	unsigned short getLength();
	unsigned short getDataLength();
	void setDataLength( unsigned short len );


	void setPackSendTime( TDateTime t, int sec);
	bool isTimeOut(TDateTime t);
	bool isWaitTimeOut();

	static void getIDevStat(const unsigned char *pData, LP_IDEV_STATUS pIDevStat );
};

#endif
//---------------------------------------------------------------------------
