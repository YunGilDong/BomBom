//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//#include <stdio.h>
#include <vcl.h>
#pragma hdrstop

#include "Mios.h"
#include "SigComm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

const char *strBitOpCode[] =
{   "알수없음",                 // 0
		// MDT => CENTER
		"버스부팅정보",				// 1
		"운행시작정보",             // 2
		"버스위치정보",             // 3
		"정류소도착정보",           // 4
		"정류소출발정보",           // 5
		"지점통과정보",             // 6
		"운행종료정보",             // 7
		"버스돌발정보",             // 8
		"버스위반정보",             // 9
		// CENTER => MDT
		"버스설정정보",           	// 10
		"앞뒤차정보제공",           // 11
		"운전자메시지전송",        	// 12
		"제어명령전송"
};


//---------------------------------------------------------------------------
const char* GetStrOpCode(int opCode)
{
    const char* str;
    switch( opCode )
	{
		case 0x40: str = strBitOpCode[ 1];  break;
		case 0x21: str = strBitOpCode[ 2];  break;
		case 0x10: str = strBitOpCode[ 3];  break;
		case 0x12: str = strBitOpCode[ 4];  break;
		case 0x13: str = strBitOpCode[ 4];  break;
		case 0x14: str = strBitOpCode[ 5];  break;
		case 0x25: str = strBitOpCode[ 7];  break;

		case 0x51: str = strBitOpCode[ 8];  break;
		case 0x52: str = strBitOpCode[ 9];  break;

		case 0x80: str = strBitOpCode[10];  break;
		case 0x22: str = strBitOpCode[11];  break;
		case 0x60: str = strBitOpCode[12];  break;
		case 0x62: str = strBitOpCode[13];  break;
		default:
			str = strBitOpCode[0];
        	break;
	}
    return str;
}

//---------------------------------------------------------------------------
	             