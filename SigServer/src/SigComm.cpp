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
{   "�˼�����",                 // 0
		// MDT => CENTER
		"������������",				// 1
		"�����������",             // 2
		"������ġ����",             // 3
		"�����ҵ�������",           // 4
		"�������������",           // 5
		"�����������",             // 6
		"������������",             // 7
		"������������",             // 8
		"������������",             // 9
		// CENTER => MDT
		"������������",           	// 10
		"�յ�����������",           // 11
		"�����ڸ޽�������",        	// 12
		"����������"
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
	             