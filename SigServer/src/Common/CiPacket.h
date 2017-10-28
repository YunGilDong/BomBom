//---------------------------------------------------------------------------
// CiPacket.h
// Author       :
// LastModify   : 
// Comment      : 
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#ifndef _CI_PACKET_H_
#define _CI_PACKET_H_
//---------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>
#include "wzByte.h"
#include "szSock.h"

#ifdef __WIN32__
#include <vcl.h>
#endif
//---------------------------------------------------------------------------
#define     MAINSVR_PID             100     // BIS ȣ��Ʈ
#define     BITCOMMSVR_PID          200     // BIT ��ż���
#define     MDTCOMMSVR_PID          300     // BUS ��ż���
#define     BMSCOMMSVR_PID          400     // BMS ��ż���
#define     MMI_PID                 500     // ��ܸ�
#define     CENTER_PID              600     // BIT ��ż���
#define     BRSSVR_PID          	800     // BRS ����
#define     SYSMON_PID              900     // �ý��׸���͸���

#define CIPACKET_BUF_SIZE 		    512
#define CIPACKET_HEADER_SIZE 	    12

//----------------------------------------------------------------------------
typedef struct {
	unsigned short srcPID;
	unsigned short dstPID;
	unsigned char  ctl;
	unsigned char  opCode;
    unsigned short seqNo;
	unsigned char  sfn;
	unsigned char  tfn;
	unsigned short length;
} CIPACKET_HEADER, *LP_CIPACKET_HEADER;

//----------------------------------------------------------------------------
class CiPacket
{

private:
    bool attached;
protected:
	void headerToString(unsigned char *buf, char *line);

public:
	unsigned char buf[CIPACKET_BUF_SIZE];
	int PACKET_SIZE;
	bool waitingAck;
    int  retry;
    int  waitedTime;

    //==============================================================
    // ��Ŷ �߰��
    //==============================================================
    sockaddr_in    reqAddress;
    unsigned char  reqOpcode;
    unsigned short reqSeqNo;

    //---------------------------------------------------------------
	CiPacket();
    ~CiPacket();
    
	//void attach(unsigned char *b);
	void getHeader(LP_CIPACKET_HEADER h);
    static void getHeader(const char* b, LP_CIPACKET_HEADER h);
    unsigned char* getBody();

	unsigned char *getBytes();
	void setBytes(const unsigned char *b, int off, int len);
    void setBytes(int dstOff, const unsigned char *src, int srcOff, int len);

    unsigned short getSrcPID();
    void setSrcPID( unsigned short pid);
    unsigned short getDstPID();
    void setDstPID( unsigned short pid);
	unsigned char getOpCode();
    void setOpCode(unsigned char v);
    unsigned short getSeqNo();
    void setSeqNo(unsigned short seqNo);
	char getCTL();
    void setCTL(char ctl);
    char getSFN();
    void setSFN(char sfn);
    char getTFN();
    void setTFN(char tfn);

    unsigned short getLength();
	unsigned short getDataLength();
	void setDataLength( unsigned short len );

    // #ifdef __WIN32__
    #if 1
    TDateTime sendTime;
    TDateTime waitLimitTime;

    void setSendTime( TDateTime t, int sec);
    void getSendTimeStr(char* strSendTime);
    bool isTimeOut(TDateTime t);
    bool isWaitTimeOut();
    #else
    DATETIME sendTime;
    void setSendTime( const LP_DATETIME t);
    #endif
};

#endif
//---------------------------------------------------------------------------
