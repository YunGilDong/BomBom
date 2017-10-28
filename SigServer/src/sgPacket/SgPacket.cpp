//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "MainFrm.h"
#include "SgPacket.h"
//---------------------------------------------------------------------
SgPacket::SgPacket()
{
	waitingAck  = false;
	retry       = 0;
	waitedTime  = 0;
	rstCode		= 0;
}

//---------------------------------------------------------------------
SgPacket::~SgPacket()
{

}

//---------------------------------------------------------------------
void SgPacket::getHeader(LP_IOPACKET_HEADER h)
{
	h->stx1	= buf[0];
	h->stx2	= buf[1];
	h->length	= getUInt2( buf, 2 );
	h->status	= buf[4]; //buf[0];
	h->opCode	= buf[5]; //buf[0];
	h->seqNo	= buf[6]; // getUInt2( buf, 1 );
//	h->deviceID = getUInt4( buf, 3 );
}

//---------------------------------------------------------------------
void SgPacket::getHeader(const char* b, LP_IOPACKET_HEADER h)
{
	h->stx1	= b[0];
	h->stx2	= b[1];
	h->length	= getUInt2( b, 2 );
	h->status	= b[4]; //buf[0];
	h->opCode	= b[5]; //buf[0];
	h->seqNo	= b[6]; // getUInt2( buf, 1 );
//	h->deviceID = getUInt4( b, 3 );
	/*
	h->opCode	= b[0];
	h->seqNo	= getUInt2( b, 1 );
	h->deviceID = getUInt4( b, 3 );
	h->length	= getUInt2( b, 7 );         */
}

//---------------------------------------------------------------------
unsigned char* SgPacket::getBody()
{
	return &buf[IOP_HEADER_SIZE];
}

//---------------------------------------------------------------------
unsigned char SgPacket::getOpCode()
{
	return buf[1];
}

//---------------------------------------------------------------------
void SgPacket::setOpCode(unsigned char opcode)
{
	buf[1] = opcode;
}

//---------------------------------------------------------------------
unsigned short int SgPacket::getSeqNo()
{
	return getUInt2( buf, 2 );
}

//---------------------------------------------------------------------
void SgPacket::setSeqNo( unsigned short seqNo )
{
	setUInt2( buf, 2, seqNo );
}


//---------------------------------------------------------------------
unsigned int SgPacket::getDeviceID()
{
	return getUInt4( buf, 3 );
}

//---------------------------------------------------------------------
void SgPacket::setDeviceID( unsigned int deviceID )
{
	setUInt4( buf, 3, deviceID );
}

//---------------------------------------------------------------------
unsigned short SgPacket::getLength()
{
	return IOP_HEADER_SIZE + getUInt2( buf, 7 );
}

//---------------------------------------------------------------------
unsigned short SgPacket::getDataLength()
{
	return getUInt2( buf, 7 );
}

//---------------------------------------------------------------------
void SgPacket::setDataLength( unsigned short len )
{
	setUInt2( buf, 7, len );
}

//---------------------------------------------------------------------
unsigned char* SgPacket::getBytes()
{
	return buf;
}
	
//---------------------------------------------------------------------
void SgPacket::setBytes(const unsigned char *b, int off, int len)
{
	memcpy( buf, &b[off], len );
}

//---------------------------------------------------------------------
void SgPacket::setBytes(int dstOff, const unsigned char *src, int srcOff, int len)
{
	memcpy( &buf[dstOff], &src[srcOff], len );
}

//---------------------------------------------------------------------
unsigned char SgPacket::getByte(int idx)
{
    return buf[idx];
}


//---------------------------------------------------------------------
//#ifdef __WIN32__
#if 1
void SgPacket::setPackSendTime( TDateTime t, int ackWaitTime )
{
	packSendTime  = t;
    waitLimitTime = t+ ackWaitTime/86400.0;
}

bool SgPacket::isTimeOut(TDateTime t)
{
    if( t > waitLimitTime ) return true;
    return false;
}

bool SgPacket::isWaitTimeOut()
{
    TDateTime currentTime = Now();
    if( currentTime > waitLimitTime ) return true;
    return false;
}
#else
void SgPacket::setPackSendTime( const LP_DATETIME t)
{
    memcpy( &sendTime, t, sizeof(DATETIME) );
}
#endif


//---------------------------------------------------------------------
void SgPacket::getIDevStat( const unsigned char *pData, LP_IDEV_STATUS pIDevStat )
{
	pIDevStat->commStatus = 1;

}


//---------------------------------------------------------------------
void SgPacket::headerToString(unsigned char *b, char *line)
{
	sprintf( line, "RES:%d OPCODE:0x%02X SEQNO:%d CL:%d LEN:%d\n",
			 b[0], b[1], getUInt2(b, 2), b[4], getUInt2(b, 5) );
}
//---------------------------------------------------------------------
