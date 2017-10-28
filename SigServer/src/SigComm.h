//---------------------------------------------------------------------------
// SigComm.h
//---------------------------------------------------------------------------
#ifndef _SIG_COMM_H_
#define _SIG_COMM_H_

//---------------------------------------------------------------------------
#define WM_FM_TEST              (WM_USER + 0x00)

#define WM_SYS_LOG              (WM_USER + 0x01)    // �ý��� �α�
#define WM_PROXY_LOG            (WM_USER + 0x02)    // ���ͳ��ΰ� ��� �α�
#define WM_SIGCOMM_LOG         (WM_USER + 0x04)    // IDEV ��� �α�
#define WM_DB_CONNECTED         (WM_USER + 0x05)

#define WM_UPDATE_ARRIVALINFO   (WM_USER + 0x10)    //

#define WM_DB_CONNECT           (WM_USER + 0xA0)    // �����ͺ��̽� ����
#define WM_DB_DISCONNECT        (WM_USER + 0xA1)    // �����ͺ��̽� ����
//---------------------------------------------------------------------------

#define SITE_AUTH_KEY           "S@N#"

#define RUN_MODE_NORMAL				0
#define RUN_MODE_TEST				1

//---------------------------------------------------------------------------
#define MAX_RCPT_INFO_CNT 			30

#define MC_ERR_NONE					0
#define MC_ERR_DB_DISCONNECTED		-1

#define DC_ERR_UNKNOWN_OPCODE		1
#define DC_ERR_UNREGIST_DEVID		2
#define DC_ERR_DUPLICATE_DEVID		3
#define DC_ERR_UNREGIST_USERID		4
#define DC_ERR_PASSWD				5


//---------------------------------------------------------------------------
#define IOP_BUF_SIZE 			4096
#define IOP_HEADER_SIZE    		7
#define IOP_DATA_SIZE 			IOP_BUF_SIZE - IOP_HEADER_SIZE

typedef struct {
	unsigned char	stx1;
	unsigned char	stx2;
	unsigned short	length;
	unsigned char	status;
	unsigned char	opCode;
	unsigned short	seqNo;
} IOPACKET_HEADER, *LP_IOPACKET_HEADER;

//---------------------------------------------------------------------------
typedef struct
{
	IOPACKET_HEADER header;
	unsigned char   eventTime[6];
	unsigned int    busID;              	// ����ID
	unsigned int    routeID;              	// �뼱ID
	unsigned int    waypointID;             // �������ID
	unsigned short  waypointSeq;            // �����������

	unsigned char   runType;              	// ���౸�� 0:���� 1:ù�� 2:���� 3:����
	unsigned char   routeDeviate;           // �뼱��Ż 0:���� 1:�뼱��Ż
	unsigned char   speed;           		// �ӵ�
	unsigned short  direction;           	// ����
	unsigned short  serviceTime;           	// �����ð�

	unsigned int    lon;           			// �浵 X
	unsigned int    lat;           			// ���� Y

	unsigned char   satlCnt;				// ������
	unsigned char   rssi;					// �𵩼��Ű���
	unsigned char   gpsStat;				// GPS ����
	unsigned char   modemStat;				// �� ����

	unsigned char   posInfoType;           	// ���ֱ� ���� ����
	unsigned short  incCode;
	unsigned short  vioCode;
	unsigned int    vioVal;

}PACK_INFO, *LP_PACKINFO;

//---------------------------------------------------------------------------
/*
typedef struct
{
	unsigned char   sendTime[6];
	unsigned int    nSendDate;
	unsigned int    nSendTime;	
	unsigned int    busID;              	// ����ID
	unsigned int    routeID;              	// �뼱ID
	unsigned char   fBusPos;
	unsigned char   fBusTime;
	unsigned short  fBusPlateNum;
	unsigned char   rBusPos;
	unsigned char   rBusTime;
	unsigned short  rBusPlateNum;
}BUS_GAP_INFO, *LP_BUS_GAP_INFO;

//---------------------------------------------------------------------------
typedef struct
{
	unsigned int    mdtID;
	unsigned char   sendTime[6];
	unsigned int    nSendDate;
	unsigned int    nSendTime;
	unsigned int    busID;              	// ����ID
	unsigned int    routeID;              	// �뼱ID
	unsigned char   ctlCode;
}MDT_CONTROL_INFO, *LP_MDT_CONTROL_INFO;


//---------------------------------------------------------------------------
typedef struct
{
	//unsigned char   sendTime[6];
	unsigned int    nSendDate;
	unsigned int    nSendTime;
	unsigned int    busID;
	unsigned char   msgType;
	char			msg[132];
}MDT_MSG_INFO, *LP_MDT_MSG_INFO;
*/


const char* GetStrOpCode(int opCode);

//---------------------------------------------------------------------------
#endif

