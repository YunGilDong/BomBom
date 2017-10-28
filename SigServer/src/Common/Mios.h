//---------------------------------------------------------------------------
// Mios.h
// Author       :
// LastModify   : 2016-05
// Comment      : MIOS APP Data Structure
//
//---------------------------------------------------------------------------
#ifndef _MIOS_H_
#define _MIOS_H_
//---------------------------------------------------------------------------

#define USE_COORD_DDMM			0

#define MAX_IDEV                128

#define ORAERR_NOT_LOGGED_ON   	-2       // 1012
#define ORAERR_NOT_CONNECTED   	-3       // 3114

//---------------------------------------------------------------------------

#define ISPT_CRTR_FILE			"ISPT_CRTR.CSV"  // 검사기준정보파일
#define VH_SPEC_FILE			"VH_SPEC.CSV"    // 제원정보파일

//--------------------------------------------------
#define FTPDOWN_ALL             0
#define FTPDOWN_ISPT_CRTR       1       // 검사기준정보
#define FTPDOWN_VH_SPEC		    2       // 제원정보

//---------------------------------------------------------------------------
typedef struct
{
	unsigned int 	vhVer;
	unsigned int 	specVer;
	unsigned int 	isptCrtrVer;
	unsigned int 	isptDevVer;
	char isptCrtrFileName[32];
	char specFileName[32];
} DATA_VERSION, *LP_DATA_VERSION;

//---------------------------------------------------------------------------
typedef struct
{
	char            strIpAddr[16];
	unsigned char   ipAddr[4];
	unsigned short  port;
	char            strUserID[16];
	char            strPasswd[16];
	char            isptDataPath[32];
	char            isptImgPath[32];
	char            specImgPath[32];

	char            isptDataDir[32];
	char            isptImgDir[32];
	char            specImgDir[32];

} IDEV_FTPSVRINFO, *LP_IDEV_FTPSVRINFO;


//---------------------------------------------------------------------------
//  검사장비 구조체 정의
//---------------------------------------------------------------------------
typedef struct
{
	char            updateTime[16];			// 수집시간
	char        	commStatus;      		//
} IDEV_STATUS, *LP_IDEV_STATUS;


typedef struct
{
	unsigned int    devID;              	// 검사장비 ID
	unsigned int    devType;              	// 검사장비 타입
	char            devName[16];          	// 검사장비 명
	char            ipAddress[16];  		// 접속IP주소
	char            isptOfficeID[5];       	// 검사소ID
	unsigned int    isptLane;			  	// 검사로

	IDEV_STATUS     stat;               	// 검사장비 상태정보
} IDEVINFO, *LP_IDEVINFO;

//---------------------------------------------------------------------------
//  차량정보 구조체 정의
//---------------------------------------------------------------------------
typedef struct
{
	char VIN[18];
	char VH_REG_NO[20];
	char SPEC_NO[18];
	char PRPS_SE_CD;
	char ABL_REG_SE_CD;
	char PLATE_RET_YN;
	int  runDistance;
	int  firstRegYear;
	int  firstRegMon;
	int  firstRegDay;

	char OWNER_SE_CD;
	char OWNER_NM[20];
	char OWNER_MEMBER_NO[20];
	char OWNER_TELNO[20];
	char OWNER_ADDR[64];
} VH, *LP_VH;

//---------------------------------------------------------------------------
//  제원정보 구조체 정의
//---------------------------------------------------------------------------
typedef struct
{
	char SPEC_NO[18];
	char MNFT_NM[32];
	char FIRST_MNFT_NM[32];
	char VH_NM[31];
	char FORM_NM[16];
	int  SEAT_CAPA;
	char VH_TY_CD[16];
	char VH_SE_CD[16];
	int  VH_WT;
	int  MAX_CARRY_WT;
	int  VH_TOT_WT;
	int  LOAD_FA_WT;
	int  LOAD_RA_WT;
	char ENG_FORM_NM[16];
	int  ENG_MAX_OUTPUT;    // x10
	int  ENG_RPM;
	int  ENG_SLNDCNT;
	int  ENG_DSPL;      	// x10
	char USE_FUEL_CD[8];
	int  WHEELBASE;
	char TIRE_FRONT_FORM[32];
	char TIRE_REAR_FORM[32];
	char MODEL_YEAR_SYM_CD[3];

	char SPEC_IMG_NM_0[32];
	char SPEC_IMG_NM_1[32];
	char SPEC_IMG_NM_2[32];
	char SPEC_IMG_NM_3[32];
} VH_SPEC, *LP_VH_SPEC;


//---------------------------------------------------------------------------
//  접수정보 구조체 정의
//---------------------------------------------------------------------------
typedef struct
{
	char RCPT_NO[18];
	int  ISPT_DIV_CD;		// 검사 구분 코드 1:정기검사 2:임시검사 3:튜닝검사
	int  ISPT_TP;			// 검사 유형 1:신규 2:재검사
	char VIN[18];
	char VH_REG_NO[20];
	char VH_NM[31];
	int  RCPT_YEAR;
	int  RCPT_MON;
	int  RCPT_DAY;
} RECEIPT, *LP_RECEIPT;


typedef struct
{
	char RCPT_NO[18];
} ISPT_STAT, *LP_ISPT_STAT;


//---------------------------------------------------------------------------
//  관능검사결과 구조체 정의
//---------------------------------------------------------------------------
typedef struct
{
	char ISPT_CODE[5];
	int  ISPT_RESULT;
	int  ISPT_ETC_LEN;
	char ISPT_ETC[256];
} SSR_ISPT_ITEM, *LP_SSR_ISPT_ITEM;

//---------------------------------------------------------------------------
typedef struct
{
	char RCPT_NO[18];
	char OPRT_ID[16];
	char ISPT_DATE[6];
	int  RUN_DISTANCE;
	char CAP_MODE;
	char FRONT_IMG[24];
	char SIDE_IMG[24];
	char REAR_IMG[24];
	int  ITEM_CNT;
	SSR_ISPT_ITEM ITEM[128];
} SSR_ISPT_RES, *LP_SSR_ISPT_RES;

//---------------------------------------------------------------------------
typedef struct
{
	char RCPT_NO[18];
	char OPRT_ID[16];
	char ISPT_DATE[6];
	int  HL_LMNN_RFV_UPLM;
	int  HL_LMNN_RFV_LOWLM;
	int  HL_LMNN_MSV;
	int  HL_LMNN_RST_CD;
	char HL_LMNN_ISPT_CODE[5];


	int  HL_RNG_RFV_UP;
	int  HL_RNG_RFV_DN;
	int  HL_RNG_RFV_LT;
	int  HL_RNG_RFV_RT;

	int  HL_RNG_MSV_UP;
	int  HL_RNG_MSV_DN;
	int  HL_RNG_MSV_LT;
	int  HL_RNG_MSV_RT;

	int  HL_RNG_RST_CD;

	char HL_RNG_UP_ISPT_CODE[5];
	char HL_RNG_DN_ISPT_CODE[5];
	char HL_RNG_LT_ISPT_CODE[5];
	char HL_RNG_RT_ISPT_CODE[5];

} HL_ISPT_RES, *LP_HL_ISPT_RES;

//---------------------------------------------------------------------------
typedef struct
{
	char RCPT_NO[18];
	char OPRT_ID[16];
	char ISPT_DATE[6];

	int  BP_FA_WT;
	int  BP_FA_RFV;
	int  BP_FA_MSV;
	int  BP_FA_RST_CD;
	char BP_FA_ISPT_CODE[5];

	int  BP_RA_WT;
	int  BP_RA_RFV;
	int  BP_RA_MSV;
	int  BP_RA_RST_CD;
	char BP_RA_ISPT_CODE[5];

	int  BP_ALL_WT;
	int  BP_ALL_RFV;
	int  BP_ALL_MSV;
	int  BP_ALL_RST_CD;
	char BP_ALL_ISPT_CODE[5];

	int  SPDMT_RFV;
	int  SPDMT_MSV;
	int  SPDMT_RST_CD;
	char SPDMT_ISPT_CODE[5];
} BS_ISPT_RES, *LP_BS_ISPT_RES;


#endif
//---------------------------------------------------------------------------
