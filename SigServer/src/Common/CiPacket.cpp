//---------------------------------------------------------------------------
// CiPacket.cpp
// Author       :
// LastModify   : 2007.8
// Comment      : 
//---------------------------------------------------------------------------
#pragma hdrstop

#include "CiPacket.h"
//---------------------------------------------------------------------
CiPacket::CiPacket()
{
	waitingAck  = false;
	retry       = 0;
	waitedTime  = 0;
    ZeroMemory( buf, CIPACKET_BUF_SIZE );
}

//---------------------------------------------------------------------
CiPacket::~CiPacket()
{
}

//---------------------------------------------------------------------
void CiPacket::getHeader(LP_CIPACKET_HEADER h)
{
	h->srcPID = getUInt2( buf, 0 );
	h->dstPID = getUInt2( buf, 2 );
	h->ctl	  = buf[4];
	h->opCode = buf[5];
    h->seqNo  = getUInt2( buf, 6 );
	h->sfn	  = buf[8];
	h->tfn    = buf[9];
	h->length = getUInt2( buf, 10 );
}

//---------------------------------------------------------------------
void CiPacket::getHeader(const char* b, LP_CIPACKET_HEADER h)
{
	h->srcPID = getUInt2( b, 0 );
	h->dstPID = getUInt2( b, 2 );
	h->ctl	  = b[4];
	h->opCode = b[5];
    h->seqNo  = getUInt2( b, 6 );
	h->sfn	  = b[8];
	h->tfn    = b[9];
	h->length = getUInt2( b, 10 );
}

//---------------------------------------------------------------------
unsigned char* CiPacket::getBody()
{
	return &buf[CIPACKET_HEADER_SIZE];
}

//---------------------------------------------------------------------
unsigned short CiPacket::getSrcPID()
{
	return getUInt2( buf, 0 );
}

//---------------------------------------------------------------------
void CiPacket::setSrcPID( unsigned short pid)
{
	setUInt2( buf, 0, pid );
}

//---------------------------------------------------------------------
unsigned short CiPacket::getDstPID()
{
	return getUInt2( buf, 2 );
}

//---------------------------------------------------------------------
void CiPacket::setDstPID( unsigned short pid)
{
	setUInt2( buf, 2, pid );
}

//---------------------------------------------------------------------
char CiPacket::getCTL()
{
	return buf[4];
}

//---------------------------------------------------------------------
void CiPacket::setCTL(char ctl)
{
	buf[4]=ctl;
}

//---------------------------------------------------------------------
unsigned char CiPacket::getOpCode()
{
	return buf[5];
}

//---------------------------------------------------------------------
void CiPacket::setOpCode(unsigned char opcode)
{
	buf[5] = opcode;
}

//---------------------------------------------------------------------
unsigned short CiPacket::getSeqNo()
{
	return getUInt2( buf, 6 );
}

//---------------------------------------------------------------------
void CiPacket::setSeqNo(unsigned short seqNo)
{
	setUInt2( buf, 6, seqNo );
}

//---------------------------------------------------------------------
char CiPacket::getSFN()
{
	return buf[8];
}

//---------------------------------------------------------------------
void CiPacket::setSFN(char sfn)
{
	buf[8]=sfn;
}

//---------------------------------------------------------------------
char CiPacket::getTFN()
{
	return buf[9];
}

//---------------------------------------------------------------------
void CiPacket::setTFN(char tfn)
{
	buf[9]=tfn;
}

//---------------------------------------------------------------------
unsigned short CiPacket::getLength()
{
	return CIPACKET_HEADER_SIZE+getUInt2( buf, 10 );
}

//---------------------------------------------------------------------
unsigned short CiPacket::getDataLength()
{
	return getUInt2( buf, 10 );
}

//---------------------------------------------------------------------
void CiPacket::setDataLength( unsigned short len)
{
	setUInt2( buf, 10, len );
}

//---------------------------------------------------------------------
unsigned char* CiPacket::getBytes()
{
	return buf;
}
	
//---------------------------------------------------------------------
void CiPacket::setBytes(const unsigned char *b, int off, int len)
{
	memcpy( buf, &b[off], len );
}

//---------------------------------------------------------------------
void CiPacket::setBytes(int dstOff, const unsigned char *src, int srcOff, int len)
{
	memcpy( &buf[dstOff], &src[srcOff], len );
}

//---------------------------------------------------------------------
//#ifdef __WIN32__
#if 1
void CiPacket::setSendTime( TDateTime t, int ackWaitTime )
{
    sendTime = t;
    waitLimitTime = t+ ackWaitTime/86400.0;
}

void CiPacket::getSendTimeStr(char* strSendTime)
{
    unsigned short year, mon, day, hour, min, sec, msec;
    sendTime.DecodeDate( &year, &mon, &day );
    sendTime.DecodeTime( &hour, &min, &sec, &msec );
    sprintf(strSendTime, "%hu%02hu%02hu%02hu%02hu%02hu", year, mon, day, hour, min, sec);
}

bool CiPacket::isTimeOut(TDateTime t)
{
    if( t > waitLimitTime ) return true;
    return false;
}


bool CiPacket::isWaitTimeOut()
{
    TDateTime currentTime = Now();
    if( currentTime > waitLimitTime ) return true;
    return false;
}
#else
void CiPacket::setSendTime( const LP_DATETIME t)
{
    memcpy( &sendTime, t, sizeof(DATETIME) );
}
#endif

//---------------------------------------------------------------------
void CiPacket::headerToString(unsigned char *b, char *line)
{
	sprintf( line, "SrcPID:%d DstPID:%d CTL:0x%02X OPCODE:0x%02X SEQ:%d SFN:0x%02X TFN:0x%02X LEN:%d\n",
			 getUInt2( b, 0 ), getUInt2( b, 2 ), 
			 b[4], buf[5], getUInt2(b,6), buf[8], b[9], getUInt2(b,10) );
}
//---------------------------------------------------------------------


