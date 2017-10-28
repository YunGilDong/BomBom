//--------------------------------------------------------------------------
// SB_Com_Packet.pas : SBComponents �� Anchor2.0 server �� ���ͳ� ��� protocol
// Script            : Anchor2.0 (Address : 181) server �� TSBCom ���� ��� protocol
//--------------------------------------------------------------------------
#ifndef _SB_PACKET_H
#define _SB_PACKET_H

//-----------------------------------------------------------------------------
// �ü��� ȣ�� ����
//-----------------------------------------------------------------------------
#define STOCK_HOGA_NUM          10
#define FUTURE_HOGA_NUM            5
#define OPTION_HOGA_NUM             5
#define INVEST_HOGA_NUM         12
//-----------------------------------------------------------------------------
#define MAX_TODAY_COMMENT_NUM   1024
//-----------------------------------------------------------------------------
// TR Number
//-----------------------------------------------------------------------------
// 1. Patch TR
const int ID_PATCH_REQ            = 131;    // ��ġ ���� ��û ��Ŷ
const int ID_PATCH_RES            = 132;    // ��ġ ���� ���� ��Ŷ

const int ID_PATCH_CMD          = 8001;
const int ID_PATCH_LIST_HEADER  = 8002;
const int ID_PATCH_LIST_FOOTER  = 8003;
const int ID_PATCH_TRANSFER_HEADER = 8004;
const int ID_PATCH_TRANSFER_FOOTER = 8005;
const int ID_PATCH_ERROR        = 8006;
const int ID_PATCH_OK           = 8007;

const int PC_LIST                = 0;      // ���丮/���� ����Ʈ ��û
const int PC_MKDIR                = 1;      // ���丮 ����
const int PC_RMDIR                = 2;      // ���丮 ����
const int PC_RMFILE                = 3;      // ���� ����
const int PC_READ                = 4;      // �����б��û

// 2. Login TR
const int ID_L1_PACKET_REQ          = 10001;  // �α��� ��û ��Ŷ
const int ID_L1_PACKET_REP          = 10002;  // �α��� ���� ��Ŷ
const int ID_L3_PACKET              = 10003;  // �α��� �������� �� ����

// 3. ���� TR
const int ID_D1_PACKET            = 10010;  // Hello ��Ŷ
const int ID_D2_PACKET            = 10011;  // HeartBeat ��Ŷ

const int ID_C1_PACKET           = 10020;  // ��Ʈ�� ��Ŷ
const int ID_C2_PACKET            = 10021;  // �屸�� ��Ŷ

// 4. ���� �ٽ���
const int ID_HT_C1_PACKET                      = 10030;  // ���� �ٽ��� ����Ʈ
                                                        // ����߰� ��û ��Ŷ
const int ID_HT_C1_PACKET_REP                  = 10031;  // ���� �ٽ��� ����Ʈ
                                                        // ����߰� ���� ��Ŷ
const int ID_HT_C2_PACKET                      = 10032;  // ���� �ٽ��� Ư������
                                                        // ����Ʈ ��û ��Ŷ
const int ID_HT_C2_PACKET_REP                 = 10033;  // ���� �ٽ��� Ư������
                                                        // ����Ʈ ���� ��Ŷ
// 5. Real TR
const int ID_A1_PACKET            = 11000;  // �ü����/���� ��Ŷ

const int ID_A2_PACKET          = 11010;  // �ǽð� ����� �α���Ŷ
const int ID_A3_PACKET          = 11020;  // �ǽð� ���ǽ� ���� ��û��Ŷ

const int ID_S1_PACKET            = 11100;  // �ֽ� �ü� ��Ŷ
const int ID_S3_PACKET          = 11101;  // �ֽ� �ü� minor
const int ID_J1_PACKET            = 11110;  // ���� �ü� ��Ŷ
const int ID_F1_PACKET            = 11120;  // ���� �ü� ��Ŷ
const int ID_F3_PACKET          = 11121;  // ���� �ü� minor
const int ID_O1_PACKET            = 11130;  // �ɼ� �ü� ��Ŷ
const int ID_O3_PACKET          = 11131;  // �ɼ� �ü� minor
const int ID_T1_PACKET            = 11140;  // ������ �ü� ��Ŷ
const int ID_U1_PACKET            = 11150;  // �ؿ� �ü� ��Ŷ
const int ID_PC1_PACKET            = 11160;  // ǲ�ݷ��̼�
const int ID_P1_PACKET            = 11170;  // ������  �ü� ��Ŷ
const int ID_N1_PACKET            = 11180;  // �ǽð� ���� ��Ŷ
const int ID_ST1_PACKET            = 11190;  // Unknown
const int ID_ST2_PACKET            = 11191;  // �ǽð� �׸� ��Ŷ
const int ID_R1_PACKET          = 11200;  // �ǽð� �ŷ��� ��Ŷ
const int ID_UP1_PACKET         = 11210;  // �ǽð� ���� ��Ŷ
const int ID_SM_PACKET          = 11220;  // �ǽð� ������ ��Ŷ
const int ID_CD1_PACKET         = 11230;  // �ǽð� ���ǽ� ���� ��Ŷ
/*/    TODO: MINI
const int ID_MF1_PACKET            = 11240;  // �̴� ���� �ü� ��Ŷ
const int ID_MF3_PACKET         = 11241;  // �̴� ���� �ü� minor
const int ID_MO1_PACKET            = 11250;  // �̴� �ɼ� �ü� ��Ŷ
const int ID_MO3_PACKET         = 11251;  // �̴� �ɼ� �ü� minor
//*/

// 6. ��ȸ TR
const int ID_B1_PACKET_REQ      = 12000;  // ��, �Ϻ� ��û ��Ŷ
const int ID_B1_PACKET_REP      = 12001;  // ��, �Ϻ� ���� ��Ŷ

const int ID_B2_PACKET_REQ      = 12010;  // ü�� ������ ��û ��Ŷ
const int ID_B2_PACKET_REP      = 12011;  // ü�� ������ ���� ��Ŷ

const int ID_B3_PACKET_REQ        = 12020;  // ������ ��,�Ϻ� ��û ��Ŷ
const int ID_B3_PACKET_REP        = 12021;  // ������ ��,�Ϻ� ���� ��Ŷ

const int ID_B4_PACKET_REQ        = 12030;  // PCR ��,�Ϻ� ��û ��Ŷ
const int ID_B4_PACKET_REP        = 12031;  // PCR ��,�Ϻ� ���� ��Ŷ

const int ID_B5_PACKET_REQ        = 12040;  // ������ ��,�Ϻ� ��û ��Ŷ
const int ID_B5_PACKET_REP        = 12041;  // ������ ��,�Ϻ� ���� ��Ŷ

/* �ֽ�, ����, ����, �ɼ�, �ؿ�    */
const int ID_B6_PACKET_REQ        = 12050;  // �ü� ��û ��Ŷ
const int ID_B6_PACKET_REP        = 12051;  // �ü� ���� ��Ŷ

const int ID_B7_PACKET_REQ        = 12060;  // �����̷а� ��û ��Ŷ
const int ID_B7_PACKET_REP        = 12061;  // �����̷а� ���� ��Ŷ

const int ID_B8_PACKET_REQ        = 12070;  // ���� �̰������� ��û ��Ŷ
const int ID_B8_PACKET_REP        = 12071;  // ���� �̰������� ���� ��Ŷ

const int ID_B9_PACKET_REQ        = 12080;  // ���� ���̽ý� ��û ��Ŷ
const int ID_B9_PACKET_REP        = 12081;  // ���� ���̽ý� ���� ��Ŷ

const int ID_B10_PACKET_REQ        = 12090;  // �ɼ� �̷а� ��û ��Ŷ
const int ID_B10_PACKET_REP        = 12091;  // �ɼ� �̷а� ���� ��Ŷ
                                          // �ɼ� ������ ������ ��Ʈ
                                          // �ɼ� ���� ������ ��Ʈ
                                          // �ɼ� ��Ÿ ��Ʈ
                                          // �ɼ� ���� ��Ʈ
                                          // �ɼ� ���� ��Ʈ
                                          // �ɼ� ��Ÿ ��Ʈ
                                          // �ɼ� �ΰ���
                                          // �ɼ� ������

const int ID_B11_PACKET_REQ        = 12100;  // �ɼ� ���������� ��û ��Ŷ
const int ID_B11_PACKET_REP        = 12101;  // �ɼ� ���������� ���� ��Ŷ

const int ID_B12_PACKET_REQ        = 12110;  // ��������Ʈ ��û ��Ŷ
const int ID_B12_PACKET_REP        = 12111;  // ��������Ʈ ���� ��Ŷ

const int ID_B13_PACKET_REQ        = 12120;  // �������� ��û ��Ŷ
const int ID_B13_PACKET_REP        = 12121;  // �������� ���� ��Ŷ

const int ID_B14_PACKET_REQ        = 12130;  // ���� sort ��û ��Ŷ
const int ID_B14_PACKET_REP        = 12131;  // ���� sort ���� ��Ŷ

const int ID_B15_PACKET_REQ        = 12140;  // �׸� ��ȸ ��û ��Ŷ
const int ID_B15_PACKET_REP        = 12141;  // �׸� ��ȸ ���� ��Ŷ

const int ID_B16_PACKET_REQ        = 12150;  // �ܱ��� ��ȸ ��û ��Ŷ
const int ID_B16_PACKET_REP        = 12151;  // �ܱ��� ��ȸ ���� ��Ŷ

const int ID_B17_PACKET_REQ        = 12160;  // ����������ȸ
const int ID_B17_PACKET_REP        = 12161;  // ����������ȸ

const int ID_B18_PACKET_REQ        = 12170;  // ���������丮 ��ȸ ��û ��Ŷ
const int ID_B18_PACKET_REP        = 12171;  // ���������丮 ��ȸ ���� ��Ŷ

const int ID_B19_PACKET_REQ        = 12180;  // ���� �ٽ�����ȸ ��û ��Ŷ
const int ID_B19_PACKET_REP        = 12181;  // ���� �ٽ�����ȸ ���� ��Ŷ

//-----------------------------------------------------------------------------
// B6 Market Type
//-----------------------------------------------------------------------------

const int MARKET_KOSPI   = 0x0001; // 0
const int MARKET_KOSDAQ  = 0x0002; // 1
const int MARKET_JISU    = 0x0004; // 2
const int MARKET_FUTURE  = 0x0008; // 3
const int MARKET_OPTION  = 0x0010; // 4
/*/    TODO: MINI
const int MARKET_MFUTURE = 0x0020; // 5
const int MARKET_MOPTION = 0x0040; // 6
//*/

const int MARKETS_STOCK  = (MARKET_KOSPI | MARKET_KOSDAQ);

//-----------------------------------------------------------------------------
// Data type
//-----------------------------------------------------------------------------
// B1_PACKET_REQ  body�� term
/*
const short DAY_DATA_TYPE    = 0;  // ��
const short WEEK_DATA_TYPE    = 1;  // ��
const short MONTH_DATA_TYPE    = 2;  // ��
const short MIN_DATA_TYPE    = 3;  // ��
const short SEC_DATA_TYPE    = 4;  // ��
const short TICK_DATA_TYPE    = 5;  // ƽ
const short INTRA_DATA_TYPE    = 6;  // ����
*/

//--------------------------------------------------------------------------
// ���� ��ġ
//--------------------------------------------------------------------------
// ���� ��û ��Ŷ

struct PATCH_CMD
{
    short packet_type;     // ID_PATCH_CMD
    short detail_type;

    int cmd;               // PC_LIST:���丮/���� ����Ʈ ��û
                           // PC_MKDIR: ���丮 ����, PC_RMDIR: ���丮 ����
                           // PC_RMFILE: ���� ����, PC_READ: ���� ��û
    char filename[504];
    int site;
    int work_type; // 1 - ��ġ, 2 - �����, 3 - �α�
    int broadcast;

    unsigned char filler;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

// ���� ���� ��Ŷ
struct PATCH_ERROR
{
    short packet_type;     // ID_PATCH_ERROR
    short detail_type;

    char msg[512];         // ���� �޽���

    unsigned char filler;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

// ���� ���� ��Ŷ
struct PATCH_OK
{
    short packet_type;      // ID_PATCH_OK
    short detail_type;

    unsigned char filler;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

// ���ϸ�� ���� ��� ��Ŷ
struct PATCH_LIST_HEADER
{
    short packet_type;      // ID_PATCH_LIST_HEADER
    short detail_type;

    int list_count;

    unsigned char filler;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

// ���ϸ�� ���� ������ ��Ŷ
struct PATCH_LIST_DATA
{
    int type;              // [���� Ÿ��] FT_FILE: ����, FT_DIR: ���͸�

    char filename[512];
    int filedate;
    int filetime;
    int filesize;
};

// ���ϸ�� ���� Footer ��Ŷ
struct PATCH_LIST_FOOTER
{
    short packet_type;    // ID_PATCH_LIST_FOOTER
    short detail_type;

    unsigned char filler;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

// ���� ���� ��� ��Ŷ
struct PATCH_TRANSFER_HEADER
{
    short packet_type;    // ID_PATCH_TRANSFER_HEADER
    short detail_type;

    char filename[504];
    int site;
    int work_type; // 1- ��ġ, 2 - �����, 3 - �α�
    int filedate;
    int filetime;
    int filesize;
    int broadcast;

    unsigned char filler;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

// ���� ���� ������ ��Ŷ
struct PATCH_TRANSFER_FOOTER
{
    short packet_type;     // ID_PATCH_TRANSFER_FOOTER
    short detail_type;

	unsigned char filler;
    unsigned char ff;
	unsigned char cr;
    unsigned char lf;
};

// ���� üũ ��Ŷ
struct CONNECTION_CHECK
{
    char process_name[64];
    int IsConnected;
};

// ���α׷� üũ ��Ŷ
struct ALIVE_CHECK
{
    char process_name[64];
    int IsAlive;
};
//--------------------------------------------------------------------------
// patch �� ���� Ÿ�� ����
const int FT_FILE                        = 0;                    // ����
const int FT_DIR                        = 1;                    // ���͸�

/// �ش� packet�� ��� ���·� ���������� Ȯ���ϱ� ���� data
struct GUBUN_DATA
{
    short packet_type;         // ��Ŷ Ÿ��
    short detail_type;         // ��Ŷ �ΰ� ����
};
//--------------------------------------------------------------------------
// Master file
//--------------------------------------------------------------------------
struct INVEST_HOGA
{
    int sell_price;                        // �ŵ�ȣ��
    int sell_vol;                          // �ŵ�ȣ�� �ܷ�
    int buy_price;                         // �ż�ȣ��
    int buy_vol;                           // �ż�ȣ�� �ܷ�
    int net_buy_price;                     // �� �ż�
    int net_buy_vol;                       // �� �ż�  �ܷ�
};

// �ֽ� ������
struct MASTER_STOCK_PACKET
{
    /* �ŷ���/�ڽ��� ���� �κ�      */
    short packet_type;                  /* ��Ŷ Ÿ�� (ID_MASTER_JONGMOK)         */
    short code_no;                      /* �ڵ��Ϸù�ȣ                          */
    int acode;                          /* ��Ŀ���� �ڵ�                         */
    int date;                           /* ��¥ YYYYMMDD                         */
    char code[9];                       /* �ڵ�                                  */
    char market_tag;                    /* ���� ���� '1': �ŷ���, '2': �ڽ���        */
    char capital_tag;                   /* �ں���                                */
                                        /* �ŷ��� 2:����, 3:����, 4:����         */
                                        /* �ڽ��� 6:(100��~), 7:(50��~100��),    */
                                        /*        8:(30��~50��), 9:(30��̸�)    */
    char ctrl_tag;                      /* �ŷ���������                          */
                                        /* 0: ����, 1: �ŷ��ߴ�, 2: �ŷ�����     */
    char kwanli_tag[1];                 /* �������� 0:����, 1:����               */
    char tuja_warn[1];                  /* ���ڰ�� 0:�Ϲ�, 1:���ڰ��           */
    char prv_gise_flag[1];              /* �⼼ 1:���ϱ⼼�߻�                   */
    char prv_daebi[1];                  /* ��� 1:����, 2:���, 3:����, 4:����,  */
                                        /*      5:�϶�              */
    char ex_tag[1];                     /* 1: �Ǹ���, 2: ����,3: �ǹ��,       */
                                        /* 4: �׸���� 5: �׸麴��, 6:�߰����� */
                                        /* 7:�Ǹ��߰�����              */
    char fake_gongsi[1];                /* �Ҽ��� ���� ����                      */
    short settle_mon;                   /* ���� ��                             */
    char intl_code[12];                 /* ���� �ڵ�                             */
    char name[44];                      /* �����                                */
    char eng_name[40];                  /* ������                                */
    int basic_price;                    /* ���ذ�                                */
    int prv_open_price;                 /* ���� �ð�                             */
    int prv_high_price;                 /* ���� ��                             */
    int prv_low_price;                  /* ���� ����                             */
    int prv_close_price;                /* ���� ����                             */
    int prv_volume;                     /* ���� �ŷ���                           */
    int prv_cash;                       /* ���� �ŷ���� ����: 10000��           */
    int max_price;                      /* ���Ѱ�                                */
    int min_price;                      /* ���Ѱ�                                */
    int reg_volume;                     /* �����ֽļ� ���� : õ��                */
    int face_value;                     /* �׸鰡                                */
    int reg_date;                       /* ������                                */
    int capital;                        /* �ں���   ����:�鸸��                  */
    int sub_value;                      /* ��밡                                */
    int open_value;                     /* �ð��Ѿ� ����:���                    */
    short year_max_date;                /* ���� �ְ� ���� ����                 */
    short year_min_date;                /* ���� ������ ���� ����                 */

    int year_max_price;                 /* ���� �ְ�                           */
    int year_min_price;                 /* ���� ������                           */
    short top_price_day;                /* ���ӻ��Ѱ��ϼ�                        */
    short down_price_day;               /* �������Ѱ��ϼ�                        */
    short year_max_day;                 /* ���� �������Ѱ� �ϼ�                  */
    short year_min_day;                 /* ���� �������Ѱ� �ϼ�                  */
    int max52w_price;                   /* 52�� �ְ�                           */
    int min52w_price;                   /* 52�� ������                           */
    int max52w_date;                    /* 52�� �ְ���                           */
    int min52w_date;                    /* 52�� ������                           */
    int sellbuy_open;                   /* �����Ÿ� ������                       */
    int sellbuy_close;                  /* �����Ÿ� ������                       */
    int buy_max_volume;                 /* �ܱ��� �ֹ����� ����  ����:����       */
    int buy_min_volume;                 /* �ܱ��� �ֹ����� ����  ����:��         */
    int limit_max_volume;               /* �ܱ��� �ѵ�����  ����:����            */
    int limit_min_volume;               /* �ܱ��� �ѵ�����  ����:��              */
    int limit_ratio;                    /* �ܱ��� �ѵ�����  �Ҽ������� 2�ڸ�     */
    int capital_upday;                  /* �׸� ��������                         */
    int ex_price;                       /* ����                                */
    short capital_chrul;                /* �׸� �������    ���� �׸麯����� SET*/

                                        /* ���� ����    */
    short upjong_large;                 /* �ŷ���:kospi200 ����, �ڽ���:���� ���*/
    short upjong_middle;                /* �ŷ���:����, �ڽ���:������            */
    short upjong_small;                 /* �ŷ���:������ �ڵ�, �ڽ���:������     */

    char tonghan_jisu_tag[1];           /* �������� ����        0:�Ϲ�, 1:���   */
    char filler1[1];

    char pos_tag[2];                    /* ���Ǳ׷� ID                                                      */
                                        /*      ST:�ֱ� MF:��������ȸ�� RT:�ε�������ȸ�� SC:��������ȸ��   */
                                        /*      IF:��ȸ�����ں�������ȸ�� DR:�ֽĿ�Ź���� EW:ELW EF:ETF     */
                                        /*      SW:�����μ������� SR:�����μ������� BC:�������� FE:�ؿ�ETF  */
                                        /*      FS:�ܱ��ֱ�                                                 */
    /* �ŷ��� ����  */
    char kospi_gubun[1];                /* [�ŷ���] '0':�Ϲ� '1':kospi100,       */
                                        /*          '2':kosp50, '3':kospi200     */
    char devide_tag[1];                 /* [�ŷ���] �׺� ���� 1:����, 2: ����    */
    char filler2[2];
    int max50_price;                    /* [�ŷ���] 50�� �ְ�                 */
    int min50_price;                    /* [�ŷ���] 50�� ������                 */
    int max50_date;                     /* [�ŷ���] 50�� �ְ�����             */
    int min50_date;                     /* [�ŷ���] 50�� ����������             */
    int sellbuy_unit;                   /* [�ŷ���] �ŸŴ���                    */

    /* �ڽ��� ����  */
    int start_date;                     /* [�ڽ���] �Ÿ� ������                        */
    short nation_code;                  /* [�ڽ���] �����ڵ�                           */
    short money_unit;                   /* [�ڽ���] ȭ�����                           */
    char venture_tag[1];                /* [�ڽ���] ��ó����.      0:�Ϲ�, 1:��ó      */
    char star_jisu_tag[1];              /* [�ڽ���] STAR���� ����  0:�Ϲ�, 1:���      */
    char exchange_rate[14];             /* [�ڽ���] ����ȯ��                           */

    char context[160];                  /* ��ũǮ�κ��� �޴� ���� ���� �ʵ�            */

    char krx_field[20];                 /* KRX ������ ���� ����                        */
                                        /* [0] : KRX���� �ڵ�������     0:�Ϲ�, 1:��� */
                                        /* [1] : KRX���� �ݵ�ü����     0:�Ϲ�, 1:��� */
                                        /* [2] : KRX���� ���̿�����     0:�Ϲ�, 1:��� */
                                        /* [3] : KRX���� ��������       0:�Ϲ�, 1:��� */
                                        /* [4] : KRX���� ������ű���   0:�Ϲ�, 1:��� */
                                        /* [5] : KRX���� ������ȭ�б��� 0:�Ϲ�, 1:��� */
                                        /* [6] : KRX���� ö������       0:�Ϲ�, 1:��� */
                                        /* [7] : KRX���� �ʼ��Һ��籸�� 0:�Ϲ�, 1:��� */
                                        /* [8] : KRX���� �̵����ű��� 0:�Ϲ�, 1:��� */
                                        /* [9] : KRX���� �Ǽ�����       0:�Ϲ�, 1:��� */
                                        /* [10]: KRX���� �������񽺱��� 0:�Ϲ�, 1:��� */
    int reserved[5];                    /* �����ʵ�                                    */

    char filler[1];
    unsigned char ff;                           /* FF '0xff'                                   */
    unsigned char cr;                           /* CR '0x0d'                                   */
    unsigned char lf;                           /* LF '0x0a'                                   */
};

// ���� ������
struct MASTER_JISU_PACKET
{
    short packet_type;                  // ��Ŷ Ÿ�� (ID_MASTER_JISU)
    short code_no;                      // �ڵ��Ϸù�ȣ

    int acode;

    int date;                           // ��¥ YYYYMMDD

    char code[10];                      // ����� �Է� �ڵ�
    char name[50];                      // ������

    int prv_open_jisu;                  // ���� �ð� �Ҽ��� �Ʒ� 2�ڸ�
    int prv_high_jisu;                  // ���� �� �Ҽ��� �Ʒ� 2�ڸ�
    int prv_low_jisu;                   // ���� ���� �Ҽ��� �Ʒ� 2�ڸ�
    int prv_close_jisu;                 // ���� ���� �Ҽ��� �Ʒ� 2�ڸ�
    int prv_volume;                     // ���ϰŷ��� ����:õ��

    char market_gb;                     // �屸��, ������
    unsigned char ff;                           // FF     '0xff'
    unsigned char cr;                           // CR     '0x0d'
    unsigned char lf;                           // LF     '0x0a'
};

// ���� ������
struct MASTER_FUTURE_PACKET
{
    short packet_type;                  // ��Ŷ Ÿ�� (ID_FUTURE_MASTER)
    short code_no;                         // �ڵ��Ϸù�ȣ
    int acode;
    int date;                           // ��¥ YYYYMMDD
    char intl_code[16];                 // ���� �ڵ�
    char code[8];                       // ������Է� �ڵ�
    char name[32];                      // �ѱ� ���� ��
    int reg_date;                       // ������     ������
    int last_deal_date;                 // ���� �ŷ���        ������
    int basic_price;                    // ���ذ� ������������: 0
    int max_price;                      // ���Ѱ�     SIGN��ȣ
    int min_price;                      // ���Ѱ�     SIGN��ȣ
    int prv_close_price;                // ���� ����      SIGN��ȣ
    int prv_volume;                     // ���� �ŷ���        ����: ���
    int prv_volume_near;                // ���� �ٿ��� �ŷ��� ����: ���
    int prv_volume_far;                 // ���� ������ �ŷ��� ����: ���
    int prv_cash1;                      // ���� �ŷ����1 ����: �鸸��
    int prv_cash2;                      // ���� �ŷ����2 ����: ��
    int interval_max_price;                                ///< �ǽð� ���Ѱ� ����             GSH 2014-09-01
    int interval_min_price;                                ///< �ǽð� ���Ѱ� ����             GSH 2014-09-01
    char filler1[8];
    int prv_no_vol;                     // ���� �̰������� ����    ����:���-Ȯ��ġ
                                        // ��������:0

    int prv_close_price_spread_near;    //���� �������� �ٿ��� ����
    int prv_close_price_spread_far;     //���� �������� ������ ����

    char code_near[20];                 // �ٿ��� �����ڵ�    �⺻: ' '
    char code_far[20];                  // ������ �����ڵ�    �⺻: ' '


    short listing_term;                 // ���� �ϼ�
    short remaning_term;                // ���� �ϼ�

    int dividend_fature;                // ���� ���� �̷���ġ
    int fair_settle_price;              // �̷а���(���갡)
    int fair_base_price;                // �̷а���(���ذ�)
    int cd_rate;                        // CD �ݸ� (X 1000)

    char prv_settle_gb[1];              // �������갡�� ����
    char prv_close_price_gb[1];         // ���� ���� ���� 1:�Ǽ�, 2:�⼼, 3,���ŷ�
    char real_limit_gb[1];                                  ///< �ǽð� ���Ѱ� �ݿ� ����(Y/N)   GSH 2014-09-01
    char filler2[1];

    int prv_settle_price;               // ���� ���갡��
    int list_high_price_day;            // ������ �ְ� ����
    int list_high_price;                // ������ �ְ�
    int list_low_price_day;             // ������ ����������
    int list_low_price;                 // ������ ������
    int entrance_day;                   // ��ȸ����

    char market_order_tag[1];           // ���尡��뱸��  Y:��� N:����
    char jokun_tag[1];                  // ���Ǻ���������� ���� Y:��� N:����
    char choi_tag[1];                   // ������������ ��뱸�� Y:��� N:����
    char last_clear_price_tag[1];       // ���������� ����

    int last_clear_price;               // ����������
    int cb_limit_high_price;            // C.B. ���Ѱ�
    int cb_limit_low_price;             // C.B. ���Ѱ�
    int prv_time;                       // ���� �����ŸŽ���

    short real_remaining_term;          // �������ϼ�

    int prv_open_price;                 // ���� �ð�
    int prv_high_price;                 // ���� ��
    int prv_low_price;                  // ���� ����

    unsigned char filler3[1];
    unsigned char ff;                           // FF     '0xff'
    unsigned char cr;                           // CR     '0x0d'
    unsigned char lf;                           // LF     '0x0a'
};

// �ɼ� ������
struct MASTER_OPTION_PACKET
{
    short packet_type;                  // ��Ŷ Ÿ�� (ID_MASTER_OPTION)
    short code_no;                      // �ڵ��Ϸù�ȣ
    int acode;
    int date;                           // ��¥ YYYYMMDD
    char intl_code[20];                 // ���� �ڵ�
    char code[8];                       // ������Է� �ڵ�
    char name[32];                      // �ѱ� ���� ��
    char short_name[20];                // ����
    char call_tag[1];                   // �ɼ� ����(ASCII) '2':call, '3': Put
    char last_trade_day_tag[1];         // �����ŷ��� ���� 1:����, 2:�ŷ�������
    char filler1[2];
    int reg_date;                       // ������  �����
    int first_deal_date;                // ���ʰŷ���  �����
    int last_deal_date;                 // ���� �ŷ��� �����
    int entrance_date;                  // ��ȸ��
    int close_date;                     // ���� �����
    short listing_term;                 // �����ϼ�
    short remaning_term;                // �����ϼ�
    int run_price;                      // ��簡��
    int basic_price;                    // ���ذ�
    int max_price;                      // ���Ѱ�
    int min_price;                      // ���Ѱ�
    int prv_close_price;                // ���� ����
    int prv_no_vol;                     // ���� �̰�����������
    int prv_volume;                     // ���� �ŷ���
    int prv_cash1;                      // ���� �ŷ����1 ����: �鸸��
    int prv_cash2;                      // ���� �ŷ����2 ����: ��
    char trans_jgcode[4];               // �ŷ�������� "01":kospi200
    char first_month_tag[1];            // �ٿ��� ���� 1:�ֱٿ���, 2:���ش�, 3:�ֿ�����
    char atm_tag[1];                    // ATM ���� : 1:ATM, 2:ITM, 3:OTM
    char newer_tag[1];                  // �ű�,�߰�,�������� 1:�ű�, 2:�߰�, 3:����
    char prv_close_tag[1];              // �������� ����
    char margin_tag[1];                 // �Ÿ����ű� ���ذ� ����
                                        // 1:��������(�ü�)
                                        // 2:���ϱ⼼(���ʰŷ������ı⼼
                                        // 3:�������űݱ��ذ�( ���ʰŷ������� ����������
                                        // 4:�������ű��̷а�( ���ʰŷ������� ���� ������
    char real_limit_gb[1];                                  ///< �ǽð��������ѿ���     �ǽð� �����Ѱ� �ݿ� ���� (Y/N)     GSH 2014-09-01
    char filler4[2];

    int newer_day;                      // �ű�/�߰�/������
    int dividend_current;               // �������� ���� ��ġ

    int fair_value;               // �̷а� �Ҽ���6�ڸ�
    int margin_price;             // �Ÿ����ű� ���ذ� : �Ҽ��� 2�ڸ�
    int interval_max_price;                                 ///< �ǽð� ���Ѱ� ���� GSH 2014-09-01
    int interval_min_price;                                 ///< �ǽð� ���Ѱ� ���� GSH 2014-09-01

    int cd_rate;                  // CD �ݸ�: ����:%
    int year_high_price_day;      // �����ְ����� YYYYMMDD
    int year_high_price;          // �����ְ�: �Ҽ��� 2�ڸ�
    int year_low_price_day;       // �������������� YYYYMMDD
    int year_low_price;           // ����������: �Ҽ��� 2�ڸ�
    int list_high_price_day;      // ������ �ְ� ����
    int list_high_price;          // ������ �ְ�
    int list_low_price_day;       // ������ ������ ����
    int list_low_price;           // ������ ������

    char market_order_tag[1];     // ���尡��� ���� Y:��� N:����
    char jokun_order_tag[1];      // ���Ǻ������� ��뱸�� Y: ���, N:����
    char cwoori_order_tag[1];     // �ֿ츮��������뱸�� Y:���, N:����
    char base_price_tag[1];       // ���ذ� ����
                                  // 1:�������ű� ���ذ�
                                  // 2:���� ���ذ� (���ʰŷ������� ���� ������)
                                  // 3:���ϱ��ذ��� �̷а� (���ʰŷ������� ���� ������
                                  // 4:���� �⼼(���ʰŷ������� �⼼����)

    int inter_volatility;         // ���纯���� : �Ҽ��� 3�ڸ�
    int historic_volatility[3];   // ������ ������ 3������ (�Ҽ��� 3�ڸ�)
    short real_remaining_term;    // �������ϼ�
    short filler6;

    int prv_open_price;           // ���� �ð�
    int prv_high_price;           // ���� ��
    int prv_low_price;            // ���� ����

    unsigned char filler5[1];             // filler
    unsigned char ff;                     // FF     '0xff'
    unsigned char cr;                     // CR     '0x0d'
    unsigned char lf;                     // LF     '0x0a'
};

// ������ ������
struct MASTER_INVEST_PACKET
{
    short packet_type;            // ��Ŷ Ÿ�� (ID_MASTER_INVEST)
    short code_no;                // �ڵ��Ϸù�ȣ

    int acode;

    char tuja_gubun[8];           // ���� ����
    char eng_name[48];            // ���� ������
    INVEST_HOGA hoga[INVEST_HOGA_NUM]; // ������ ���п� �ٸ� 100 ~ 10000 ���� 12��
                                  // 0 ����
                                  // 1 �ܱ���
                                  // 2 �����
                                  // 3 ����ȸ��
                                  // 4 ����ȸ��
                                  // 5 ���ڽ�Źȸ��
                                  // 6 ����
                                  // 7 ����
                                  // 8 ���
                                  // 9 ��Ÿ
    unsigned char filler1;
    unsigned char ff;                     // FF     '0xff'
    unsigned char cr;                     // CR     '0x0d'
    unsigned char lf;                     // LF     '0x0a��
};

// P/C Ratio ������
struct MASTER_PC_PACKET
{
    short packet_type;            // ID_MASTER_PCR_IV
    char filler[2];

    int acode;                    // ��Ŀ�ڵ�
    int date;                     // ��¥

    char name[80];                // �����

    int reserved[5];

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

// ������ ������
struct MASTER_POSITION_PACKET
{
    short packet_type;            // ID_MASTER_POSITION
    char filler[2];

    int acode;                    // ��Ŀ�ڵ�
    int date;                     // ��¥

    char name[80];                // �����
    int info_acode;

    int reserved[5];

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

// �ؿ� ������
struct MASTER_US_PACKET
{
    short packet_type;                                      // ��Ŷ Ÿ�� (ID_MASTER_US)
    short code_no;                                          // �ڵ��Ϸù�ȣ

    int acode;

    char code[12];                                          // ����� �Է� �ڵ�
    char eng_name[48];                                      // ���� ������

    char han_name[48];                                      // �ѱ� ������
    char place[28];                                         // usinfo �Ҽ�

    char symbol[12];                                        // Symbol

    int prv_open_price;                                     // ���� �ð�
    int prv_high_price;                                     // ���� ��
    int prv_low_price;                                      // ���� ����
    int prv_cur_price;                                      // ���� ��

    int div;                  // divide
    int open_date;              // ������
    
    unsigned char filler2[1];                                       // �е���Ʈ
    unsigned char ff;                                               // FF     '0xff'
    unsigned char cr;                                               // CR     '0x0d'
    unsigned char lf;                                               // LF     '0x0a��
};

//--------------------------------------------------------------------------
// TR ����
//--------------------------------------------------------------------------
// Real Packet PreHeader  // ������ó�� �������� ����ϴ� �κ�
struct REAL_HEADER
{
    unsigned short packet_type;      // TR Number
    unsigned short header_size;      // ��Ŷ ��� ũ��(byte)
    int total_size;          // ��Ŷ õü ũ��(byte)

    int acode;               // Anchor code
    int detail_type;         // 0: ȣ�� + ü��, 1: ü��
};

// Query Packet PreHeader  // ������ó�� �������� ����ϴ� �κ�
struct QUERY_HEADER
{
    unsigned short packet_type;      // TR Number
    unsigned short header_size;      // ��Ŷ ��� ũ��(byte)
    int total_size;          // ��Ŷ õü ũ��(byte)

    unsigned int handle;             // TSBQuery Handle

    unsigned char zip_flag;          // [���� �÷���] 0: uncompress, 1: compress

    char filler1[3];
};
// Query Footer           // Chart ���� ��� 
struct QUERY_FOOTER
{
    QUERY_HEADER hdr;

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

//--------------------------------------------------------------------------
// �α��� TR
//--------------------------------------------------------------------------
// �α��� ��û ��Ŷ
struct L1_BODY_REQ
{
    char id[32];              //  User ID
    char pw[32];              //  User Password

    unsigned short site;              // 0:��Ŀ2.0, 1:WOW, 2:SK HTS ��etc ����
    char filler1[2];          // �ʷ�

    unsigned char set_ip;             // IP ���� '1', ������ �ڵ�
    unsigned char ff;                 // 0xFF
    unsigned char cr;                 // 0x0D
    unsigned char lf;                 // 0x0A
};

struct L1_PACKET_REQ
{
    REAL_HEADER hdr;          // packet_type: ID_ L1_PACKET_REQ
    // acode ��� ����.
    L1_BODY_REQ body;
};

// �α��� ���� ��Ŷ
struct L1_BODY_REP
{
    int err_no;                // [���� �ڵ�]
                               // 0: ����, 1: ���� ����, 2: �α��� ����
    char err_msg[1024];        // [���� �޽���]

    char id[32];               // ����� ID
    char nick[32];             // ����� �ʸ�
    char name[32];             // ����� �̸�

    int today;                 // ���� ��¥ YYYYMMDD

    int jongmok_start_time;    // ���� �� ���� �ð� HHMMSS
    int jongmok_end_time;      // ���� �� �� �ð� HHMMSS

    int future_start_time;     // ���� �� ���� �ð� HHMMSS
    int future_end_time;       // ���� �� �� �ð� HHMMSS

    int chart_begin_date;      // ��Ʈ ��� ���� ��¥ YYYYMMDD
    int chart_end_date;        // ��Ʈ ��� ���� ��¥ YYYYMMDD

    int first_flag;            // [��Ʈ ó�� ����� ����]
                               // 0:ó�����ƴ� 1:ó�����
    int chart_type;            // [��Ʈ ����]
                               // ����Ʈ(CHART_LIGHT) �����̾�(CHART_PREMIUM)
    int reserved[5];

    char anchor_d_ip[2][16];   // anchor_d ip
    int anchor_d_port;         // anchor_d ��Ʈ

    char chart_d_ip[2][16];    // chart_d ip
    int chart_d_port;          // chart_d ��Ʈ

    char file_d_ip[2][16];     // ���� ���� ip
    int file_d_port;           // ���� ���� ��Ʈ

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

struct L1_PACKET_REP
{
    REAL_HEADER hdr;           // packet_type: ID_ L1_PACKET_REP

    L1_BODY_REP body;
};

// ��Ƽ���� �� �������� �� ��������
struct L3_PACKET
{
    REAL_HEADER hdr;           // packet_type 10003
                               // detail_type 1:��������(��), 2:����(�ƴϿ�)

    char id[32];               // ȸ�� ���̵�
    char anchor_d_ip[16];      // anchor_d IP
    int anchor_d_port;         // user�� ������ anchor_d ��Ʈ

    char filler;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};
//--------------------------------------------------------------------------
// ���� ���� ���� TR, ���� ���� TR
//--------------------------------------------------------------------------
// AnchorD UserD ���� ���� ��Ŷ
struct D1_BODY
{
    char id[32];            // ȸ�� ���̵�
    int user_type;          // [��Ŀ ����� Ÿ��] �����̾�, ����Ʈ, �Ϲ�...
    char anchor_d_ip[16];   // anchor_d IP
    short anchor_d_num;     // user�� ������ anchor_d ��ȣ
    short anchor_d_fd;      // user�� ������ anchor_d ���� user ��� id
    char user_d_ip[16];     // user_d ���� IP
    int user_d_port;        // user_d ���� ��Ʈ

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

struct D1_PACKET
{
    REAL_HEADER hdr;        // packet_type: ID_D1_PACKET
    // acode ��� ����.
    D1_BODY body;
};

// AnchorD �� UserD ���� ���� ���� ��Ŷ
struct D2_BODY
{
    char id[32];            // ȸ�� ���̵�

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

struct D2_PACKET
{
    REAL_HEADER hdr;        // packet_type: ID_D2_BODY
    // acode ��� ����.

    D2_BODY body;
};

// AnchorD Control ��Ŷ

struct C1_BODY
{
    short spot_type;                     // ���� Ÿ��
    short anchor_num;          // ��Ŀ ���� �ѹ�
    int date;              // ��¥
    int time;              // �ð�
    short how_ctrl_num;          // 0  �ǽð� ����    ( ID_CTRL_NOTICE    )
                 // 1  ������ �����  ( ID_CTRL_MASTER    )
                 // 2  ���� �޼���    ( ID_CTRL_ETC_MSG   )
                 // 3  ���� IP�缳��( ID_CTRL_IP_RESET  )
                 // 4  �����ǽð�����( ID_CTRL_NOTE  )
                 //    �IP:ac203.softbridge.co.kr(P:14052)
                 //    ����IP:ac20T.softbridge.co.kr(P:14052)
                 // 9  ���� ���� ����( ID_CTRL_FQUIT     )
                 // 10 ���� ���� ���� ( ID_CTRL_ETC_FQUIT )
    short site;
    char message[1024];

    unsigned char filler2;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;};

struct C1_PACKET
{
    REAL_HEADER hdr;        // packet_type: ID_C1_PACKET
    // acode ��� ����.
    C1_BODY body;
};

// AnchorD �屸�� ��Ŷ

struct C2_BODY
{
    short spot_type;                     // ���� Ÿ��
    short anchor_num;          // ��Ŀ ���� �ѹ�
    int date;              // ��¥
    int time;              // �ð�

    char message[32];                    // ����
                                         // ���� ����ȣ��
                                         // ������ ����
                                         // ���� �帶�� ����
                                         // ���� �� ����
                                         // ���� �ð��� ����
                                         // ���� �帶�� ����
                                         // ���� �� ����
                                         // ���� �ð��� ����
                                         // ���� �ð��� ����

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;};

struct C2_PACKET
{
    REAL_HEADER hdr;        // packet_type: ID_C2_PACKET
    // acode ��� ����.
    C2_BODY body;
};


//--------------------------------------------------------------------------
// ���� �ٽ��� ����Ʈ ��� �߰��ϱ�
//--------------------------------------------------------------------------
struct HT_C1_DATA
{
    int acode;              // anchor code
    char comment[MAX_TODAY_COMMENT_NUM];     // ���񼳸�
};
struct HT_C1_BODY
{
    int date;               // ����
    int count;              // ��ϰ���

    HT_C1_DATA* data;       // count ����

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};
struct HT_C1_PACKET
{
    REAL_HEADER hdr;        // packet_type: ID_HT_C1_PACKET

    HT_C1_BODY body;
};

struct HT_C1_DATA_REP
{
    char server[16];       // ��񼭹� IP
    int err_no;             // �۾���� �����ڵ�(0:����, -1:����)
};
struct HT_C1_BODY_REP
{
    int count;              // ��� �߰��۾��� ���� ����

    HT_C1_DATA_REP* data;   // count ����

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};
struct HT_C1_PACKET_REP
{
    REAL_HEADER hdr;        // packet_type: ID_HT_C1_PACKET_REP

    HT_C1_BODY_REP body;
};

//--------------------------------------------------------------------------
// ���� �ٽ��� Ư������ ����Ʈ ������ ��û
//--------------------------------------------------------------------------
struct HT_C2_BODY
{
    int date;               // ����

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};
struct HT_C2_PACKET
{
    REAL_HEADER hdr;        // packet_type: ID_HT_C2_PACKET

    HT_C2_BODY body;
};

struct HT_C2_DATA_REP
{
    int acode;              // anchor code
    char comment[MAX_TODAY_COMMENT_NUM];     // ���񼳸�
};
struct HT_C2_BODY_REP
{
    int date;               // ����
    int count;              // �ٽ��� ���� ����

    HT_C2_DATA_REP* data;   // count ����

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};
struct HT_C2_PACKET_REP
{
    REAL_HEADER hdr;        // packet_type: ID_HT_C2_PACKET_REP

    HT_C2_BODY_REP body;
};

//--------------------------------------------------------------------------
// ���� ���/���� TR
//--------------------------------------------------------------------------
// �ü� ���/���� ��Ŷ
struct A1_DATA
{
    int acode;           // anchor code
    int detail_type;     // 0: ȣ�� + ü��, 1: ü��
};

struct A1_BODY
{
    int count;           // ��ϰ���

    A1_DATA* data;       // count ����

    unsigned char rq_tag;        // [��û ����] 1: ���, 2: ����

    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

struct A1_PACKET
{
    REAL_HEADER hdr;     // packet_type: ID_A1_PACKET
    // acode ��� ����.
    A1_BODY body;
};

//--------------------------------------------------------------------------
// ���� �α� TR
//--------------------------------------------------------------------------
struct A2_BODY
{
    char log_id[16];       // �α�ID(Ŭ���̾�Ʈ���� �ø��� ���ϸ�)
    char id[32];          // ����� ID
    char message[256];       // ����

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

struct A2_PACKET
{
    REAL_HEADER hdr;     // packet_type: ID_A2_PACKET

    A2_BODY body;
};

//--------------------------------------------------------------------------
// ���� ���� TR
//--------------------------------------------------------------------------
// ���� �ü� ��Ŷ
struct J1_BODY
{
    int date;               // ��¥  YYYYMMDD
    int time;               // �ð�  HHMMSS

    short jang;             // [�屸��] 0: �� �� ����ȣ��, 3: ����,
    // 5: �ð��� ����(KOSPI200 ������:1100000�� ���� 9: ������
    // KOSDAQ50 ������:1100000�� ����, 9: ������)

    char daebi_tag;         // [��� ����] '0':�ŷ���, '1':����, '2':���,
                            // '3':����, '4':����, '5':�϶�
    unsigned char filler1;

    int cur_price;          // ���簡
    int open_price;         // �ð�
    int high_price;         // ��
    int low_price;          // ����
    int volume;             // �ŷ���. ����: õ��
    int cash;               // �ŷ� ��� (����:�鸸��)
    int daebi;              // ����� ������. ������ ? master(��������)
    int daebi_rate;         // �����
    int time_vol;           // ���� ü�ᷮ
    int seq_no;             // ƽ��ȣ

    unsigned char filler2;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

struct J1_PACKET
{
    REAL_HEADER hdr;        // packet_type: ID_J1_PACKET

    J1_BODY body;
};

//--------------------------------------------------------------------------
// ���� �ֽ� TR
//--------------------------------------------------------------------------
// �ֽ� �ü� ��Ŷ
struct STOCK_HOGA
{
    int sell_price;         // �ŵ�ȣ��
    int buy_price;          // �ż�ȣ��
    int sell_vol;           // �ŵ�ȣ�� �ܷ�
    int buy_vol;            // �ż�ȣ�� �ܷ�
};

struct S1_BODY
{
    STOCK_HOGA hoga[STOCK_HOGA_NUM];    // 10�ܰ� ȣ��

    int date;               // ��¥ YYYYMMDD
    int time;               // �ð�  :HHMMSS

    short jang;             // [�屸��] 0: �� ���� ��, 10: ���� �ð���,
                            // 20: ���� ����ȣ��, 30: ����, 40: ���� ����ȣ��,
                            // 50: ���� �ð���, 99: ������
    char vi_apply_code;     // VI���뱸���ڵ�    1:VI�ߵ�, 2:VI����
    char vi_code;           // VI�����ڵ�        1:����VI, 2:����VI, 3:����&����VI

    char daebi_tag;         // [��� ����] '0':�ŷ���, '1':����, '2':���,
                            // '3':����, '4':����, '5':�϶�
    char gise_tag;          // [�⼼ ����] '1':�⼼����
    // '2':�⼼���, '3':�⼼����, '4':�⼼�϶�
    unsigned char ctrl_tag;         // [�ŷ� ����] 0:����, 1:����, 2:�ߴ�
    char vol_tag;           // �ܷ� ����

    int cur_price;          // ���簡
    int open_price;         // �ð�
    int high_price;         // ��
    int low_price;          // ����
    int volume;             // ���� �ŷ���
    int cash;               // ���� �ŷ� ��� (����:õ��)
    int daebi;              // �����:���簡 - master(��������)
    int daebi_rate;         // �����

    int exp_buy_price;      // ����ü�ᰡ     ����:��
    int exp_buy_vol;        // ����ü�����   ����:��
    int timeout_sell_vol;   // �ð����Ѹŵ��ܷ�   ����:��
    int timeout_buy_vol;    // �ð����Ѹż��ܷ�   ����:��
    int tot10_sell_vol;     // 10�ܰ� �Ѹŵ�ȣ���ܷ�
    int tot10_buy_vol;      // 10�ܰ� �Ѹż�ȣ���ܷ�

    int jangprv_tot_buy_vol; // �尳���� �ð��� �� �ŵ� �ܷ�
    int jangprv_tot_sell_vol;// �尳���� �ð��� �� �ż� �ܷ�

    int weight_avg_price;   // ������հ�, �ð��� �뷮�ŸŽ�:�帶���� ����
    int buy_price;          // ü�ᰡ

    char max_price_tag;     // ���Ѱ� ���� ����
    char min_price_tag;     // ���Ѱ� ���� ����
    char vol_gubun;         // �ܷ� ����. filler �� ��ü
    char chegyul_gubun;     // �ż�ü��: 1, �ŵ�ü��: 2
    int seq_no;             // ȣ�� ������ �ѹ�
    int time_vol;           // ���� ü�ᷮ

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

struct S1_PACKET
{
    REAL_HEADER hdr; // packet_type: ID_S1_PACKET

    S1_BODY body;
};

///////////////////////////////////////////////////////////////////////////
//                       S3 ȣ�� ��Ŷ                                    //
///////////////////////////////////////////////////////////////////////////

struct S3_BODY
{
    STOCK_HOGA hoga[10];    // 10�ܰ� ȣ��

    int time;               // �ð�  :HHMMSS

    short jang;             // [�屸��] 0: �� ���� ��, 10: ���� �ð���,
                            // 20: ���� ����ȣ��, 30: ����, 40: ���� ����ȣ��,
                            // 50: ���� �ð���, 99: ������
    char daebi_tag;         // [��� ����] '0':�ŷ���, '1':����, '2':���,
                            // '3':����, '4':����, '5':�϶�
    char filler1;           // �����ʵ�
    int daebi;
    int daebi_rate;         // �����

    int exp_buy_price;      // ����ü�ᰡ     ����:��
    int exp_buy_vol;        // ����ü�����   ����:��
    int timeout_sell_vol;   // �ð����Ѹŵ��ܷ�   ����:��
    int timeout_buy_vol;    // �ð����Ѹż��ܷ�   ����:��
    int tot10_sell_vol;     // 10�ܰ� �Ѹŵ�ȣ���ܷ�
    int tot10_buy_vol;      // 10�ܰ� �Ѹż�ȣ���ܷ�

    int jangprv_tot_buy_vol; // �尳���� �ð��� �� �ŵ� �ܷ�
    int jangprv_tot_sell_vol;// �尳���� �ð��� �� �ż� �ܷ�

    int volume;
    int filler2;

    unsigned char filler;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

struct S3_PACKET
{
    REAL_HEADER hdr; // packet_type: ID_S3_PACKET(11101)

    S3_BODY body;
};


//--------------------------------------------------------------------------
// ���� ���� TR
//--------------------------------------------------------------------------
// ���� �ü� Small ��Ŷ    -- �������� �޴� ��Ŷ
struct FO_HOGA
{
    int sell_price;        // �ŵ�ȣ��
    int buy_price;         // �ż�ȣ��
    int sell_vol;          // �ŵ�ȣ�� �ܷ�
    int buy_vol;           // �ż�ȣ�� �ܷ�
    int sell_quantity;     // �ŵ�ȣ�� �ܷ�
    int buy_quantity;      // �ż�ȣ�� �ܷ�
};

struct F2_BODY
{
    FO_HOGA hoga[FUTURE_HOGA_NUM]; // FUTURE_HOGA_NUM = 5

    int date;                // ��¥
    int time;                // �ð�   ����:HHMMSS

    short jang;              // [�屸��]
                             // 1: ���� ����ȣ�� 3: ���� 5:�ð��� ����
                             // KOSPI200 ������:1100000�� ���� 9: ������
                             // KOSDAQ50 ������:1100000�� ���� 9: ������

    char daebi_tag;          // ��� ����
                             // '0':�ŷ���, '1':����, '2':���
                             // '3':����, '4':����, '5':�϶�

    char gise_tag;           // [�⼼ ����] 0:����, 1:�⼼
    unsigned char ctrl_tag;          // [�ŷ� ����] 0:����, 1:�������ߴ�
                             // 11:�������ߴ�,  ������ �ֽ�C,b�ߴ�,
                             // 3:�������� �ߴ�, 5:�������� C,B �ߴ�
    unsigned char filler1[3];

    int cb_time;             // �ð�, C,B �ߴܽ� ��ȿ
    int cur_price;           // ���簡
    int open_price;          // �ð�
    int high_price;          // ��
    int low_price;           // ����
    int volume;              // ���� �ŷ���
    int cash1;               // ���� �ŷ����1 ����: �鸸��
    int cash2;               // ���� �ŷ����2 ����: õ��
    int daebi;               // �����:���簡 - master(��������)
    int daebi_rate;          // �����

    int tot_sell_vol;        // �ŵ�ȣ�� �� ����
    int tot_buy_vol;         // �ż�ȣ�� �� ����
    int tot_sell_quantity;   // �ŵ�ȣ�� �� �Ǽ�
    int tot_buy_quantity;    // �ż�ȣ�� �� ����
    int not_deal_vol;        // �̰��� ���� ���� 1 ���� Ȯ��
    int tick_no;               // ƽ��ȣ

    int kospi200;            // kospi200 value
    int cd_rate;             // cd�ݸ�

    int remain_sec;          // Ķ����������
    int real_remain_sec;     // �������� : �������� �������� �����·� ��ȯ. �ű�

    int seq_no;              // ȣ�� ������ �ѹ�

    char chegyul_gubun;      // �ż�ü��: 1, �ŵ�ü��: 2
    unsigned char filler2[3];
    int time_vol;           // ���� ü�ᷮ

    int large_volume;       // ���Ǵ뷮ü�����                           2014-09-01
    int real_max_price;     // �ǽð����Ѱ�           SIGN ��ȣ           2014-09-01
    int real_min_price;     // �ǽð����Ѱ�           SIGN ��ȣ           2014-09-01
    char real_limit_gb[1];  // �ǽð��������ѿ���     �ǽð� �����Ѱ� �ݿ� ���� (Y/N)     2014-09-01
    char filler4[3];        // ��Ŷ ������ ������

    int max_step;           // ���Ѱ��ܰ�                                   2015-06-15
    int min_step;           // ���Ѱ��ܰ�                                   2015-06-15
    int max_price;          // ���Ѱ�                                       2015-06-15
    int min_price;          // ���Ѱ�                                       2015-06-15

    unsigned char filler3;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

struct F2_PACKET
{
    REAL_HEADER hdr; // packet_type: ID_F1_PACKET

    F2_BODY body;
};

// ���� �ü� ��Ŷ     -- ���α׷����� ����ϴ� ��Ŷ ����
struct F1_BODY
{
    FO_HOGA hoga[FUTURE_HOGA_NUM]; // FUTURE_HOGA_NUM = 5

    int date;                // ��¥
    int time;                // �ð�   ����:HHMMSS

    short jang;              // [�屸��]
                             // 1: ���� ����ȣ�� 3: ���� 5:�ð��� ����
                             // KOSPI200 ������:1100000�� ���� 9: ������
                             // KOSDAQ50 ������:1100000�� ���� 9: ������

    char daebi_tag;          // ��� ����
                             // '0':�ŷ���, '1':����, '2':���
                             // '3':����, '4':����, '5':�϶�

    char gise_tag;           // [�⼼ ����] 0:����, 1:�⼼
    unsigned char ctrl_tag;          // [�ŷ� ����] 0:����, 1:�������ߴ�
                             // 11:�������ߴ�,  ������ �ֽ�C,b�ߴ�,
                             // 3:�������� �ߴ�, 5:�������� C,B �ߴ�
    unsigned char filler1[3];

    int cb_time;             // �ð�, C,B �ߴܽ� ��ȿ
    int cur_price;           // ���簡
    int open_price;          // �ð�
    int high_price;          // ��
    int low_price;           // ����
    int volume;              // ���� �ŷ���
    int cash1;               // ���� �ŷ����1 ����: �鸸��
    int cash2;               // ���� �ŷ����2 ����: õ��
    int daebi;               // �����:���簡 - master(��������)
    int daebi_rate;          // �����

    int tot_sell_vol;        // �ŵ�ȣ�� �� ����
    int tot_buy_vol;         // �ż�ȣ�� �� ����
    int tot_sell_quantity;   // �ŵ�ȣ�� �� �Ǽ�
    int tot_buy_quantity;    // �ż�ȣ�� �� ����

    int not_deal_vol;        // �̰��� ���� ���� 1 ���� Ȯ��
    int tick_no;             // ƽ��ȣ

    int kospi200;            // kospi200 value
    int cd_rate;             // cd�ݸ�

    int remain_sec;          // Ķ����������
    int real_remain_sec;     // �������� : �������� �������� �����·� ��ȯ. �ű�

    int seq_no;              // ȣ�� ������ �ѹ�

    // ���ϴ� ����ؼ� ���� ����
    int cur_price_near;    // �ٿ��� ���� ���� ����
    int cur_price_far;     // ������ ���� ���� ����
    int volume_near;       // �ٿ��� ���� �ŷ���
    int volume_far;        // ������ ���� �ŷ���
    int cash1_near;        // �ٿ��� ���� �ŷ����1 ����: �鸸��
    int cash2_near;        // �ٿ��� ���� �ŷ����2 ����: õ��
    int cash1_far;         // ������ ���� �ŷ����1 ����: �鸸��
    int cash2_far;         // ������ ���� �ŷ����2 ����: õ��

    int fair_price;        // �̷а�
    int disparate_ratio;   // ������
    int fair_basis;        // �̷� ���̽ý�
    int market_basis;      // ���� ���̽ý�
    int fair_spread;       // �̷� ��������
    int market_spread;     // ���� ��������

    // �������� ���� ��
    char chegyul_gubun;    // �ż�ü��: 1, �ŵ�ü��: 2
    unsigned char filler2[3];
    int time_vol;           // ���� ü�ᷮ

    unsigned char filler3;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

struct F1_PACKET
{
    REAL_HEADER hdr; // packet_type: ID_F1_PACKET

    F1_BODY body;
};

///////////////////////////////////////////////////////////////////////////
//                       F3 ȣ�� ��Ŷ                                    //
///////////////////////////////////////////////////////////////////////////

struct SMALL_F_HOGA
{
    unsigned short sell_price;        // �ŵ�ȣ��
    unsigned short buy_price;         // �ż�ȣ��
    unsigned short sell_vol;          // �ŵ�ȣ�� �ܷ�
    unsigned short buy_vol;           // �ż�ȣ�� �ܷ�
    unsigned short sell_quantity;     // �ŵ�ȣ�� �ܷ�
    unsigned short buy_quantity;      // �ż�ȣ�� �ܷ�
};

struct F3_BODY
{
    SMALL_F_HOGA hoga[FUTURE_HOGA_NUM]; // FUTURE_HOGA_NUM = 5

    int time;                // �ð�   ����:HHMMSS

    short jang;              // [�屸��]
                             // 1: ���� ����ȣ�� 3: ���� 5:�ð��� ����
                             // KOSPI200 ������:1100000�� ���� 9: ������
                             // KOSDAQ50 ������:1100000�� ���� 9: ������
    short filler1;

    int tot_sell_vol;        // �ŵ�ȣ�� �� ����
    int tot_buy_vol;         // �ż�ȣ�� �� ����
    int tot_sell_quantity;   // �ŵ�ȣ�� �� �Ǽ�
    int tot_buy_quantity;    // �ż�ȣ�� �� ����

    int volume;
    int filler3;

    unsigned char filler2;

    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

struct F3_PACKET
{
    REAL_HEADER hdr; // packet_type: ID_F3_PACKET(11121)

    F3_BODY body;
};


//--------------------------------------------------------------------------
// �ɼ� ���� TR
//--------------------------------------------------------------------------
// �ɼ� �ü� SMALL ��Ŷ  -- �������� �޴� ��Ŷ
struct O2_BODY
{
    FO_HOGA hoga[OPTION_HOGA_NUM];  // OPTION_HOGA_NUM = 5

    int date;                // ��¥     ���� : YYYYMMDD
    int time;                // �ð�     ���� : HHMMSS

    short jang;              // �屸��,
                             // 1: ���� ����ȣ�� 3: ���� 5:�ð��� ����
                             // KOSPI200 ������:1100000�� ���� 9: ������
                             // KOSDAQ50 ������:1100000�� ���� 9: ������

    char daebi_tag;          // ��� ����
                             // '0':�ŷ���, '1':����, '2':���
                             // '3':����, '4':����, '5':�϶�

    char gise_tag;           // �⼼ ����      0:����, 1:�⼼
    unsigned char ctrl_tag;          // �ŷ� ����   0:����, 1:�������ߴ�
                             // 11:�������ߴ�,  ������ �ֽ�C,b�ߴ�,
                             // 3:�������� �ߴ�, 5:�������� C,B �ߴ�
    unsigned char filler1[3];

    int cb_time;             // �ð�           C,B �ߴܽ� ��ȿ
    int cur_price;           // ���簡
    int open_price;          // �ð�
    int high_price;          // ��
    int low_price;           // ����
    int volume;              // ���� �ŷ���
    int cash1;               // ���� �ŷ����1 ����: �鸸��
    int cash2;               // ���� �ŷ����2 ����: õ��
    int daebi;               // ����� : ���簡 - master(��������)
    int daebi_rate;          // �����

    int tot_sell_vol;        // �ŵ�ȣ�� �� ����
    int tot_buy_vol;         // �ż�ȣ�� �� ����
    int tot_sell_quantity;   // �ŵ�ȣ�� �� �Ǽ�
    int tot_buy_quantity;    // �ż�ȣ�� �� ����
    int not_deal_vol1;       // �̰��� ���� ���� 1 ���� Ȯ��
    int not_deal_vol2;       // �̰��� ���� ���� 2 ���� Ȯ��
    int tick_no;             // ƽ��ȣ

    int kospi200;            // kospi200

    int real_remain_sec;     // ��������
    int remain_sec;          // Ķ����������

    int future_cur_price;    // ���� ���簡
    int seq_no;              // ȣ�� ������ �ѹ�

    char chegyul_gubun;      // �ż�ü��: 1, �ŵ�ü��: 2
    unsigned char filler2[3];
    int time_vol;           // ���� ü�ᷮ

    int large_volume;       // ���Ǵ뷮ü�����                           2014-09-01
    int real_max_price;     // �ǽð����Ѱ�           SIGN ��ȣ           2014-09-01
    int real_min_price;     // �ǽð����Ѱ�           SIGN ��ȣ           2014-09-01
    char real_limit_gb[1];  // �ǽð��������ѿ���     �ǽð� �����Ѱ� �ݿ� ���� (Y/N)     2014-09-01
    char filler4[3];        // ��Ŷ ������ ������

    int max_step;           // ���Ѱ��ܰ�                                   2015-06-15
    int min_step;           // ���Ѱ��ܰ�                                   2015-06-15
    int max_price;          // ���Ѱ�                                       2015-06-15
    int min_price;          // ���Ѱ�                                       2015-06-15

    unsigned char filler3;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

struct O2_PACKET
{
    REAL_HEADER hdr; // packet_type: ID_O1_PACKET

    O2_BODY body;
};

// �ɼ� �ü� ��Ŷ        -- ���α׷����� ����ϴ� ��Ŷ ����
struct O1_BODY
{
    FO_HOGA hoga[OPTION_HOGA_NUM];  // OPTION_HOGA_NUM = 5

    int date;                // ��¥     ���� : YYYYMMDD
    int time;                // �ð�     ���� : HHMMSS

    short jang;              // �屸��,
                             // 1: ���� ����ȣ�� 3: ���� 5:�ð��� ����
                             // KOSPI200 ������:1100000�� ���� 9: ������
                             // KOSDAQ50 ������:1100000�� ���� 9: ������

    char daebi_tag;          // ��� ����
                             // '0':�ŷ���, '1':����, '2':���
                             // '3':����, '4':����, '5':�϶�

    char gise_tag;           // �⼼ ����      0:����, 1:�⼼
    unsigned char ctrl_tag;          // �ŷ� ����   0:����, 1:�������ߴ�
                             // 11:�������ߴ�,  ������ �ֽ�C,b�ߴ�,
                             // 3:�������� �ߴ�, 5:�������� C,B �ߴ�
    unsigned char filler1[3];

    int cb_time;             // �ð�           C,B �ߴܽ� ��ȿ
    int cur_price;           // ���簡
    int open_price;          // �ð�
    int high_price;          // ��
    int low_price;           // ����
    int volume;              // ���� �ŷ���
    int cash1;               // ���� �ŷ����1 ����: �鸸��
    int cash2;               // ���� �ŷ����2 ����: õ��
    int daebi;               // ����� : ���簡 - master(��������)
    int daebi_rate;          // �����

    int tot_sell_vol;        // �ŵ�ȣ�� �� ����
    int tot_buy_vol;         // �ż�ȣ�� �� ����
    int tot_sell_quantity;   // �ŵ�ȣ�� �� �Ǽ�
    int tot_buy_quantity;    // �ż�ȣ�� �� ����
    int not_deal_vol1;       // �̰��� ���� ���� 1 ���� Ȯ��
    int not_deal_vol2;       // �̰��� ���� ���� 2 ���� Ȯ��
    int tick_no;             // ƽ��ȣ

    int kospi200;            // kospi200

    int real_remain_sec;     // ��������
    int remain_sec;          // Ķ����������

    int future_cur_price;    // ���� ���簡
    int seq_no;              // ȣ�� ������ �ѹ�

    // ���ϴ� ����ؼ� ���� ����
    int fair_price;         // �̷а�
    int disparate_ratio;    // ������
    int hist_volatility;    // ������ ������ (Historical Volatility)
    int impl_volatility;    // ���� ������ (Implied Volatility)

    int delta;              // ��Ÿ
    int gamma;              // ����
    int theta;              // ��Ÿ
    int vega;               // ����
    int rho;                // ��

    // �������� ���� ��
    char chegyul_gubun;     // �ŵ�ü��: 1, �ż�ü��: 2
    unsigned char filler2[3];
    int time_vol;           // ���� ü�ᷮ

    unsigned char filler3;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

struct O1_PACKET
{
    REAL_HEADER hdr; // packet_type: ID_O1_PACKET

    O1_BODY body;
};

///////////////////////////////////////////////////////////////////////////
//                       O3 ȣ�� ��Ŷ                                    //
///////////////////////////////////////////////////////////////////////////

struct SMALL_O_HOGA
{
    unsigned short sell_price;        // �ŵ�ȣ��
    unsigned short buy_price;         // �ż�ȣ��
    int sell_vol;          // �ŵ�ȣ�� �ܷ�
    int buy_vol;           // �ż�ȣ�� �ܷ�
    unsigned short sell_quantity;     // �ŵ�ȣ�� �ܷ�
    unsigned short buy_quantity;      // �ż�ȣ�� �ܷ�
};

struct O3_BODY
{
    SMALL_O_HOGA hoga[OPTION_HOGA_NUM];  // OPTION_HOGA_NUM = 5

    int time;                // �ð�     ���� : HHMMSS

    short jang;              // �屸��,
                             // 1: ���� ����ȣ�� 3: ���� 5:�ð��� ����
                             // KOSPI200 ������:1100000�� ���� 9: ������
                             // KOSDAQ50 ������:1100000�� ���� 9: ������
    short filler1;

    int tot_sell_vol;        // �ŵ�ȣ�� �� ����
    int tot_buy_vol;         // �ż�ȣ�� �� ����
    int tot_sell_quantity;   // �ŵ�ȣ�� �� �Ǽ�
    int tot_buy_quantity;    // �ż�ȣ�� �� �Ǽ�

    int volume;              
    int filler2;             

    unsigned char filler3;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};


struct O3_PACKET
{
    REAL_HEADER hdr; // packet_type: ID_O3_PACKET(11131)

    O3_BODY body;
};

// ������ �ü� ��Ŷ
struct T1_BODY
{
    INVEST_HOGA hoga[INVEST_HOGA_NUM];         // ������ ���п� �ٸ� 100 ~ 10000 ���� 12��
                                               // 0 ����
                                               // 1 �ܱ���
                                               // 2 �����
                                               // 3 ����ȸ��
                                               // 4 ����ȸ��
                                               // 5 ���ڽ�Źȸ��
                                               // 6 ����
                                               // 7 ����
                                               // 8 ���
                                               // 9 ��Ÿ
    int date;                                  // ��������
    int time;                                  // ������ �ð�

    int code;                                  // �ɼ� ������ �ڵ�
    int code_no;                               // 000001 ����
    char data_gb[4];                           // ����Ÿ ���� : ��01��:����Ȯ��ġ
                                               //    ��02��:����Ȯ��ġ->��03��:����Ȯ��ġ

    int crt_time;                              // ���� ����
    short trade_gb;                            // ���� ����
    unsigned char filler1[2];

    int future_jisu_price;                     // �ֱ� ���� ���� ���� ����
    int daebi_price;                           // �ֱ� ���� ���� ���Ϻ�

    unsigned char filler2;
    unsigned char ff;                                  // FF     '0xff'
    unsigned char cr;                                  // CR     '0x0d'
    unsigned char lf;                                  // LF     '0x0a��
};

struct T1_PACKET
{
    REAL_HEADER hdr; // packet_type: ID_T1_PACKET

    T1_BODY body;
};

// P/C Ratio �ü� ��Ŷ

struct PC1_BODY
{
    int date;                     // ��¥
    int time;                      // �ð�

    int put_vol;                  // PUT ��ü �ŷ���
    int put_cash;                 // PUT ��ü �ŷ����
    int put_notdeal;              // PUT ��ü �̰�������
    int call_vol;                 // CALL ��ü �ŷ���
    int call_cash;                // CALL ��ü �ŷ����
    int call_notdeal;             // CALL ��ü �̰�������

    int option_put_rep_iv;        // PUT �ɼ� ��ǥ ���� ������
    int option_call_rep_iv;       // CALL �ɼ� ��ǥ ���� ������
    int option_put_atm_iv;        // PUT �ɼ� ��� ���� ������
    int option_call_atm_iv;       // CALL �ɼ� ��� ���� ������

    int tick_no;                  // ƽ��ȣ

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

struct PC1_PACKET
{
    REAL_HEADER hdr; // packet_type: ID_PC1_PACKET

    PC1_BODY body;
};

// �����Ǻм� �ü� ��Ŷ                // ���α׷����� ����ϴ� ��Ŷ
struct P1_HOGA
{
    int buy_avg_price;                // �ż���հ�
    int buy_vol;                   // �ż� ����
    int sell_avg_price;               // �ŵ� ��հ�
    int sell_vol;                  // �ŵ� ����
};

struct P1_BODY
{
    P1_HOGA hoga[INVEST_HOGA_NUM];    // INVEST_HOGA_NUM = 12

    int date;                         // ��¥
    int time;                         // �ð�

    int info_acode;                   // ������ �ڵ�

    int tick_no;                      // ƽ��ȣ

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

struct P1_PACKET
{
    REAL_HEADER hdr; // packet_type: ID_P1_PACKET

    P1_BODY body;
};

// �ؿ� �ü� ��Ŷ
struct U1_BODY
{
    int date;                // ��¥     ���� : YYYYMMDD
    int time;                // �ð�     ���� : HHMMSS

    char daebi_tag;          // ��� ����
                             // '0':�ŷ���, '1':����, '2':���
                             // '3':����, '4':����, '5':�϶�
    unsigned char filler1[3];

    int cur_price;           // ���簡
    int open_price;          // �ð�
    int high_price;          // ��
    int low_price;           // ����
    int volume;              // �ŷ���. ����: õ��
    int daebi;               // ����� ������. ���簡 - master(��������)
    int daebi_rate;          // �����
    int seq_no;
    int time_vol;             // �����ŷ��� ���

    unsigned char filler2;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

struct U1_PACKET
{
    REAL_HEADER hdr; // packet_type: ID_U1_PACKET

    U1_BODY body;
};

// ���� �ǽð� ��Ŷ
struct N1_BODY
{
    int date;                // ��¥     ���� : YYYYMMDD
    int time;                // �ð�     ���� : HHMMSS

    char db_num[20];

    short info_code;         //  �۽Ż� ����
                             // 00:����, 01:edaily, 02:joins, 03:�����Ӱ���,
                             // 04:���̳��ȴ���, 05:etoday,
                             // 06:�ѱ�����,  07:Financial Point
                             // 08:�Ӵ�������,  09:���մ���, 10:������

    short class_code;        // ���� ����
                             // 1:����, 2:����, 4:�������,
                             // 8:���, 16:�ؿܰ���, 128:��Ÿ

    char title[136];         // ���� ����
    int reserved;
    char market_tag;         // ���屸�� '1':�ŷ���, '2':�ڽ���, '3':����, '4':ä��

    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

struct N1_PACKET
{
    REAL_HEADER hdr; // packet_type: ID_N1_PACKET

    N1_BODY body;
};

// �׸� �ǽð� ��Ŷ              // ���α׷����� ����ϴ� ��Ŷ
struct ST2_BODY
{
    char theme_code[4];                 // �׸��ڵ�
    char theme_name[64];                // �׸���
    int date;                           // ��¥
    int time;                           // �ð�
    int tot_count;        // �׸� ���� �����
    int upcount;                        // ��� �����
    int highcount;        // ���� �����
    int downcount;                      // �϶� �����
    int lowcount;            // ���� �����
    int avg_rate;                       // ��� �����

};

struct ST2_PACKET
{
    REAL_HEADER hdr;     // packet_type: ID_ST2_PACKET
    ST2_BODY body[10];
};

// �ŷ��� �ǽð� ��Ŷ              // ���α׷����� ����ϴ� ��Ŷ
struct R1_HOGA
{
    short sell_no;                    // �ŵ� �ŷ�����ȣ
    short buy_no;                     // �ż� �ŷ�����ȣ
    int tot_sell_vol;                 // �ŵ� ����
    int tot_buy_vol;                  // �ż� ����
};

struct R1_BODY
{
    R1_HOGA hoga[5];                  //

    int date;                         // ��¥
    int time;                         // �ð�

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

struct R1_PACKET
{
    REAL_HEADER hdr;     // packet_type: ID_R1_PACKET
    R1_BODY body;
};

// ��ü���� �ǽð� ��Ŷ              // ���α׷����� ����ϴ� ��Ŷ
struct UP1_BODY
{
    int acode;                  // anchor code
    int date;                   // ��¥
    int time;                   // �ð�
    int cur_price;              // ������
    int open_price;             // �ð�
    int high_price;             // ��
    int low_price;              // ����
    int volume;                 // ���� �ŷ���
    int daebi;                  // ���ϴ��
    int daebi_rate;             // �����
    char daebi_tag;             // ��� ����
    char filler[3];
};

struct UP1_PACKET
{
    REAL_HEADER hdr;     // packet_type: ID_UP1_PACKET
    UP1_BODY  body[10];
};

// �ֽ� �ǽð� ������
struct SM_PACKET
{
    REAL_HEADER hdr;     // packet_type: ID_SM_PACKET

    MASTER_STOCK_PACKET body;
};

//--------------------------------------------------------------------------
// Query �к�, �Ϻ� TR
//--------------------------------------------------------------------------
// �к�, �Ϻ� ��û ��Ŷ
struct B1_BODY_REQ
{
    int acode;              // anchor code
    int count;              // ������ ��û ����. �켱��
    int s_date;             // ������     YYYYMMDD
    int e_date;             // ������     YYYYMMDD

    short time_unit;        // 1, 5, 10, 20, 40, 60 ���
    short term;             // 0: ��, 1: ��, 2: ��, 3: ��,
                            // 4: ��, 5: ƽ, 6: ����

    char sujung;            // ��0��: �����ְ���ó��
                            // ��1��: �����ְ�ó��
    char filler1[3];

    unsigned char filler2;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

struct B1_PACKET_REQ
{
    QUERY_HEADER hdr;       // packet_type: ID_B1_PACKET_REQ

    B1_BODY_REQ body;
};

// �к�, �Ϻ� ���� ���
struct B1_HEADER_REP
{
    QUERY_HEADER hdr;

    int acode;               // anchor code

    short time_unit;         // 1, 5, 10, 20, 40, 60 ���
    short term;              // 0: ��, 1: ��, 2: ��, 3: ��,
                             // 4: ��, 5: ƽ, 6: ����

    int cur_price;           // ���簡
    int daebi;               // ���
    int daebi_rate;          // �����
    int count;               // ������ ����

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

// �к�, �Ϻ� ���� ��Ŷ
struct B1_DATA_REP
{
    int acode;               // Anchor code
    int date;                // ��¥
    int time;                // �ð�   ����:HHMM00

    int cur_price;           // ���簡
    int open_price;          // �ð�
    int high_price;          // ��
    int low_price;           // ����
    int volume;              // �ŷ���
    int seq_no;              // nƽ�� ������ �ѹ�
    int time_vol;               // ���� ü�ᷮ
};

struct B1_PACKET_REP
{
    B1_HEADER_REP hdr;          // packet_type: ID_B1_PACKET_REP

    B1_DATA_REP* body;          // Header �� count ����

    QUERY_FOOTER footer;        // packet_type: ID_B1_PACKET_REP
};
//--------------------------------------------------------------------------
// Query ü�ᵥ���� TR
//--------------------------------------------------------------------------
// ü�ᵥ���� ��û ��Ŷ
struct B2_BODY_REQ
{
    int acode;              // Anchor code
    int count;              // ������ ��û ����. �켱��

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

struct B2_PACKET_REQ
{
    QUERY_HEADER hdr;       // packet_type: ID_B2_PACKET_REQ

    B2_BODY_REQ body;
};

// ü�ᵥ���� ���� ���
struct B2_HEADER_REP
{
    QUERY_HEADER hdr;

    int acode;               // anchor code
    int cur_price;           // ���簡
    int daebi;               // ���
    int daebi_rate;          // �����

    int count;               // �����Ͱ���

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

// ü�ᵥ���� ���� ��Ŷ
struct B2_DATA_REP
{
    int date;                // ��¥
    int time;                // �ð�   ����:HHMM00
    int cur_price;           // ���簡
    int volume;              // ���� �ŷ���
    int value;               // ��/���� ���� �̰�������, �ֽ� 0
    int tick_no;             // ƽ ī��Ʈ
    char buy_flag;           // ��0��: ����, ��1��: �ż�ü��
    unsigned char filler[3];
    int time_vol;
};

struct B2_PACKET_REP
{
    B2_HEADER_REP hdr;       // packet_type: ID_B2_PACKET_REP

    B2_DATA_REP* body;       // Header �� count ����

    QUERY_FOOTER footer;    // packet_type: ID_B2_PACKET_REP
};

// ������ �к�, �Ϻ� ��û ��Ŷ
struct B3_BODY_REQ
{
    int acode;               // anchor code
    int count;               // ������ ��û ����. �켱��
    int s_date;              // ������   YYYYMMDD
    int e_date;              // ������   YYYYMMDD

    short time_unit;         // 1, 5, 10, 20, 40, 60 ���
    short term;              // 0: ��, 1: ��, 2: ��, 3: ��,
                             // 4: ��, 5: ƽ, 6: ����

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

struct B3_PACKET_REQ
{
    QUERY_HEADER hdr;       // packet_type: ID_B3_PACKET_REQ

    B3_BODY_REQ body;
};

// ������ �к�, �Ϻ� ���� ���
struct B3_HEADER_REP
{
    QUERY_HEADER hdr;

    int acode;               // anchor code

    short time_unit;         // 1, 5, 10, 20, 40, 60 ���
    short term;              // 0: ��, 1: ��, 2: ��, 3: ��,
                             // 4: ��, 5: ƽ, 6: ����

    int count;               // ������ ����

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

// ������ �к�, �Ϻ� ���� ��Ŷ
struct B3_DATA_REP
{
    int acode;                  // Anchor code
    int date;                   // ��¥
    int time;                   // �ð�   ����:HHMM00

    int future_jisu_price;      // �ֱ� ���� ���� ���� ����
    int daebi_price;            // ���Ϻ�

    INVEST_HOGA hoga[INVEST_HOGA_NUM]; // INVEST_HOGA_NUM = 12
};

struct B3_PACKET_REP
{
    B3_HEADER_REP hdr;          // packet_type: ID_B3_PACKET_REP

    B3_DATA_REP* body;          // Header �� count ����

    QUERY_FOOTER footer;       // packet_type: ID_B3_PACKET_REP
};

// PC ratio �к�, �Ϻ� ��û ��Ŷ
struct B4_BODY_REQ
{
    int acode;               // anchor code
    int count;               // ������ ��û ����. �켱��
    int s_date;              // ������   YYYYMMDD
    int e_date;              // ������   YYYYMMDD
     
    short time_unit;         // 1, 5, 10, 20, 40, 60 ���
    short term;              // 0: ��, 1: ��, 2: ��, 3: ��,
                             // 4: ��, 5: ƽ, 6: ����

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

struct B4_PACKET_REQ
{
    QUERY_HEADER hdr;       // packet_type: ID_B4_PACKET_REQ

    B4_BODY_REQ body;
};

// PC ratio�к�, �Ϻ� ���� ���
struct B4_HEADER_REP
{
    QUERY_HEADER hdr;

    int acode;               // anchor code

    short time_unit;         // 1, 5, 10, 20, 40, 60 ���
    short term;              // 0: ��, 1: ��, 2: ��, 3: ��,
                             // 4: ��, 5: ƽ, 6: ����

    int count;               // ������ ����

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

// PC ratio �к�, �Ϻ� ���� ��Ŷ
struct B4_DATA_REP
{
    int acode;                          // anchor code
    int date;                           // ��¥
    int time;                           // �ð�

    int put_vol;                        // PUT ��ü �ŷ��� (���� 1��)
    int put_cash;                       // PUT ��ü �ŷ���� (���� �鸸��)
    int put_notdeal;                    // PUT ��ü �̰������ (���� 1��)
    int call_vol;                       // CALL ��ü �ŷ��� (���� 1��)
    int call_cash;                      // CALL ��ü �ŷ����  (���� �鸸��)
    int call_notdeal;                   // CALL ��ü �̰������ (���� 1��)

    int option_put_rep_iv;              // PUT �ɼ� ��ǥ ���� ������ (���� 0.0001)
    int option_call_rep_iv;             // CALL �ɼ� ��ǥ ���� ������ (���� 0.0001)
    int option_put_atm_iv;              // PUT �ɼ� ��� ���� ������ (���� 0.0001)
    int option_call_atm_iv;             // CALL �ɼ� ��� ���� ������ (���� 0.0001)

    int tick_no;                        // ƽ��ȣ

    int reserved[7];                    // reserved1 ~ reserved7
};

struct B4_PACKET_REP
{
    B4_HEADER_REP hdr;          // packet_type: ID_B4_PACKET_REP

    B4_DATA_REP* body;          // Header �� count ����

    QUERY_FOOTER footer;       // packet_type: ID_B4_PACKET_REP
};

// Position �к�, �Ϻ� ��û ��Ŷ
struct B5_BODY_REQ
{
    int acode;               // anchor code
    int count;               // ������ ��û ����. �켱��
    int s_date;              // ������   YYYYMMDD
    int e_date;              // ������   YYYYMMDD

    short time_unit;         // 1, 5, 10, 20, 40, 60 ���
    short term;              // 0: ��, 1: ��, 2: ��, 3: ��,
                             // 4: ��, 5: ƽ, 6: ����

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

struct B5_PACKET_REQ
{
    QUERY_HEADER hdr;       // packet_type: ID_B5_PACKET_REQ

    B5_BODY_REQ body;
};    

// Position �к�, �Ϻ� ���� ���
struct B5_HEADER_REP
{
    QUERY_HEADER hdr;

    int acode;               // anchor code

    short time_unit;         // 1, 5, 10, 20, 40, 60 ���
    short term;              // 0: ��, 1: ��, 2: ��, 3: ��,
                             // 4: ��, 5: ƽ, 6: ����

    int count;               // ������ ����

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

// Position �к�, �Ϻ� ���� ��Ŷ
struct B5_DATA_REP
{
    int acode;                   // anchor code
    int date;                    // ��¥
    int time;                    // �ð�

    int info_acode;              // �������ڵ�

    P1_HOGA hoga[INVEST_HOGA_NUM];  // INVEST_HOGA_NUM = 12

    int tick_no;                 // ƽ��ȣ
};

struct B5_PACKET_REP
{
    B5_HEADER_REP hdr;          // packet_type: ID_B5_PACKET_REP

    B5_DATA_REP* body;          // Header �� count ����

    QUERY_FOOTER footer;        // packet_type: ID_B5_PACKET_REP
};

// �ü� �к�, �Ϻ� ��û ��Ŷ
struct B6_BODY_REQ
{
    int acode;                  // anchor code(���� ���� ��û��)
    int date;                   // ��û��¥
    short market;               // �ŷ���=0x0001, �ڽ���=0x0002, ����=0x0004,
                                // ����=0x0008, �ɼ�=0x0010, ELW = 0x0020,
                                // �ؿ�=0x0040
    short rq_type;              // 0:������,
                                 // 1. ���Ѱ� 2. ���Ѱ� 3. ���Ѱ� �ӹ� 4. ���Ѱ� �ӹ�
                                // 5. ���Ѱ� ��Ż 6. ���Ѱ� ��Ż 7. (�ŵ�)�ܷ� ���� ���Ѱ�
                                // 8. (�ż�)�ܷ� ���� ���Ѱ� 9. ���� ���Ѱ� 10. ���� ���Ѱ�
                                // 11. ������ ���Ѱ� 12. ������ ���Ѱ� 13. ����� ����
                                // 14. �϶��� ���� 15. ���� 16. ��°� ���� 17. �϶��� ����
                                // 18. �ŷ��� ���� 19. ȸ�������� 20. �ŷ���� ����
                                // 21. �ð��Ѿ� ���� 22. ���ϴ�� �ŷ������� 23. ���ϰŷ��� ����
                                // 24. ���ϰŷ��� ���� �ӹ� 25. ���� �� ���� �ӹ�
                                // 26. ���� �ð� ���� �ӹ� 27. ���� �� ���� �ӹ�
                                // 28. ���� ���� ���� �ӹ� 29. ���Ϻ��������� 30. �׸鰡�̴�
                                // 31. 52�� �ְ� 32. 52�� ������ 33. 52�� �ְ� ���� �ӹ�
                                // 34. 52�� ������ ���� �ӹ� 35. �����ְ� 36. ���� ������
                                // 37. �����ְ� ���� �ӹ� 38. ���������� ���� �ӹ�
                                // 39. �����ֽļ� ���� 40. �űԻ��� ���� (���� 3���� �̳�)
                                // 41. �������� 42. ��������/���/���� 43. �ŷ�����
    int con_value;              // ������

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

struct B6_PACKET_REQ
{
    QUERY_HEADER hdr;       // packet_type: ID_B6_PACKET_REQ

    B6_BODY_REQ body;
};

// �ü� �к�, �Ϻ� ���� ���
struct B6_HEADER_REP
{
    QUERY_HEADER hdr;

    int count;              // ������ ����

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

// �ü� �к�, �Ϻ� ���� ��Ŷ
struct B6_DATA_REP
{
    int acode;                  // anchor code
    int date;                   // ��¥
    int time;                   // �ð�

    int cur_price;              // ������
    int open_price;             // �ð�
    int high_price;             // ��
    int low_price;              // ����
    int volume;                 // ���� �ŷ���
    int daebi;                  // ���ϴ��
    int daebi_rate;             // �����
    char daebi_tag;             // ��� ����
    unsigned char filler1[3];
    int ch_rate;                // ������
    int ch_value;               // ������
    int prv_volume;             // ���ϰŷ���
    int buy_price;              // �ż�ȣ��
    int sell_price;             // �ŵ�ȣ��
    int buy_vol;                // �ż��ܷ�
    int sell_vol;               // �ŵ��ܷ�
    int buy_vol_rate;           // 1ȣ���ż��ܷ�/�Ѹż��ܷ�
    int sell_vol_rate;          // 1ȣ���ŵ��ܷ�/�Ѹŵ��ܷ�
    int tot_buy_vol;            // �Ѹż��ܷ�
    int tot_sell_vol;           // �Ѹŵ��ܷ�
    int tot_rate;               // �Ѹż�/�Ѹŵ�
    int tot_buy_rate;           // �Ѹż�/�ŷ���
    int tot_trade_rate;         // ȸ����
    int cash;                   // �ŷ����
    int exp_vol;                // ����ü�ᷮ
    int volume_rate;            // �ŷ������
    int year_high_price;        // �����ְ�
    int year_low_price;         // ����������
    int week_high_price_52;     // 52���ְ�
    int week_low_price_52;      // 52��������
    int list_value;             // �ð��Ѿ�
    int face_price;             // �׸鰡
};

struct B6_PACKET_REP
{
    B6_HEADER_REP hdr;          // packet_type: ID_B6_PACKET_REP

    B6_DATA_REP* body;          // Header �� count ����

    QUERY_FOOTER footer;       // packet_type: ID_B6_PACKET_REP
};

// �����̷а� �к�, �Ϻ� ��û ��Ŷ
struct B7_BODY_REQ
{
    int acode;               // anchor code
    int count;               // ������ ��û ����. �켱��
    int s_date;              // ������   YYYYMMDD
    int e_date;              // ������   YYYYMMDD
     
    short time_unit;         // 1, 5, 10, 20, 40, 60 ���
    short term;              // 0: ��, 1: ��, 2: ��, 3: ��,
                             // 4: ��, 5: ƽ, 6: ����

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

struct B7_PACKET_REQ
{
    QUERY_HEADER hdr;       // packet_type: ID_B7_PACKET_REQ

    B7_BODY_REQ body;
};

// �����̷а� �к�, �Ϻ� ���� ���
struct B7_HEADER_REP
{
    QUERY_HEADER hdr;

    int acode;               // anchor code

    short time_unit;         // 1, 5, 10, 20, 40, 60 ���
    short term;              // 0: ��, 1: ��, 2: ��, 3: ��,
                             // 4: ��, 5: ƽ, 6: ����

    int count;               // ������ ����

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

// �����̷а� �к�, �Ϻ� ���� ��Ŷ
struct B7_DATA_REP
{
    int acode;                  // anchor code
    int date;                   // ��¥
    int time;                   // �ð�
    int cur_price;              // ������
    int volume;                 // �����ŷ���
    int kospi200;               // Kospi200
    int remain_sec;             // Ķ����������
    int real_remain_sec;        // ��������
    int cd_rate;                // cd�ݸ�
};

struct B7_PACKET_REP
{
    B7_HEADER_REP hdr;          // packet_type: ID_B7_PACKET_REP

    B7_DATA_REP* body;          // Header �� count ����

    QUERY_FOOTER footer;       // packet_type: ID_B7_PACKET_REP
};

// ���� �̰������� �к�, �Ϻ� ��û ��Ŷ
struct B8_BODY_REQ
{
    int acode;               // anchor code
    int count;               // ������ ��û ����. �켱��
    int s_date;              // ������   YYYYMMDD
    int e_date;              // ������   YYYYMMDD

    short time_unit;         // 1, 5, 10, 20, 40, 60 ���
    short term;              // 0: ��, 1: ��, 2: ��, 3: ��,
                             // 4: ��, 5: ƽ, 6: ����

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

struct B8_PACKET_REQ
{
    QUERY_HEADER hdr;       // packet_type: ID_B8_PACKET_REQ

    B8_BODY_REQ body;
};

// ���� �̰������� �к�, �Ϻ� ���� ���
struct B8_HEADER_REP
{
    QUERY_HEADER hdr;

    int acode;               // anchor code

    short time_unit;         // 1, 5, 10, 20, 40, 60 ���
    short term;              // 0: ��, 1: ��, 2: ��, 3: ��,
                             // 4: ��, 5: ƽ, 6: ����

    int count;               // ������ ����

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

// ���� �̰������� �к�, �Ϻ� ���� ��Ŷ
struct B8_DATA_REP
{
    int acode;                  // anchor code
    int date;                   // ��¥
    int time;                   // �ð�

    int cur_price;              // ������
    int volume;                 // �����ŷ���
    int not_deal_vol;           // �̰��� ��������
    int value;                  // �̰��� �񱳰���(��.�� ���� �ٸ�)
};

struct B8_PACKET_REP
{
    B8_HEADER_REP hdr;          // packet_type: ID_B8_PACKET_REP

    B8_DATA_REP* body;          // Header �� count ����

    QUERY_FOOTER footer;       // packet_type: ID_B8_PACKET_REP
};

// ���̽ý� �к�, �Ϻ� ��û ��Ŷ
struct B9_BODY_REQ
{
    int acode;               // anchor code
    int count;               // ������ ��û ����. �켱��
    int s_date;              // ������   YYYYMMDD
    int e_date;              // ������   YYYYMMDD

    short time_unit;         // 1, 5, 10, 20, 40, 60 ���
    short term;              // 0: ��, 1: ��, 2: ��, 3: ��,
                             // 4: ��, 5: ƽ, 6: ����

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

struct B9_PACKET_REQ
{
    QUERY_HEADER hdr;       // packet_type: ID_B9_PACKET_REQ

    B9_BODY_REQ body;
};

// ���̽ý� �к�, �Ϻ� ���� ���
struct B9_HEADER_REP
{
    QUERY_HEADER hdr;

    int acode;               // anchor code

    short time_unit;         // 1, 5, 10, 20, 40, 60 ���
    short term;              // 0: ��, 1: ��, 2: ��, 3: ��,
                             // 4: ��, 5: ƽ, 6: ����

    int count;               // ������ ����

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

// ���̽ý� �к�, �Ϻ� ���� ��Ŷ
struct B9_DATA_REP
{
    int acode;                  // anchor code
    int date;                   // ��¥
    int time;                   // �ð�
    int cur_price;              // ������
    int volume;                 // �����ŷ���
    int kospi200;               // Kospi200
    int fair_value;             // �̷а�
};

struct B9_PACKET_REP
{
    B9_HEADER_REP hdr;          // packet_type: ID_B9_PACKET_REP

    B9_DATA_REP* body;          // Header �� count ����

    QUERY_FOOTER footer;       // packet_type: ID_B9_PACKET_REP
};

// �ɼ��̷а� �к�, �Ϻ� ��û ��Ŷ
struct B10_BODY_REQ
{
    int acode;               // anchor code
    int count;               // ������ ��û ����. �켱��
    int s_date;              // ������   YYYYMMDD
    int e_date;              // ������   YYYYMMDD

    short time_unit;         // 1, 5, 10, 20, 40, 60 ���
    short term;              // 0: ��, 1: ��, 2: ��, 3: ��,
                             // 4: ��, 5: ƽ, 6: ����

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

struct B10_PACKET_REQ
{
    QUERY_HEADER hdr;       // packet_type: ID_B10_PACKET_REQ

    B10_BODY_REQ body;
};

// �ɼ��̷а� �к�, �Ϻ� ���� ���
struct B10_HEADER_REP
{
    QUERY_HEADER hdr;

    int acode;               // anchor code

    short time_unit;         // 1, 5, 10, 20, 40, 60 ���
    short term;              // 0: ��, 1: ��, 2: ��, 3: ��,
                             // 4: ��, 5: ƽ, 6: ����

    int count;               // ������ ����

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

// �ɼ��̷а� �к�, �Ϻ� ���� ��Ŷ
struct B10_DATA_REP
{
    int acode;                  // anchor code
    int date;                   // ��¥
    int time;                   // �ð�
    int cur_price;              // ������
    int kospi200;               // kospi200
    int future_cur_price;       // ���� ������
    int remain_sec;             // Ķ����������
    int real_remain_sec;        // ��������
    int cd_rate;                // cd�ݸ�
};

struct B10_PACKET_REP
{
    B10_HEADER_REP hdr;          // packet_type: ID_B10_PACKET_REP

    B10_DATA_REP* body;          // Header �� count ����

    QUERY_FOOTER footer;       // packet_type: ID_B10_PACKET_REP
};

// �ɼ� ���������� �к�, �Ϻ� ��û ��Ŷ
struct B11_BODY_REQ
{
    int acode;               // anchor code
    int count;               // ������ ��û ����. �켱��
    int s_date;              // ������   YYYYMMDD
    int e_date;              // ������   YYYYMMDD

    short time_unit;         // 1, 5, 10, 20, 40, 60 ���
    short term;              // 0: ��, 1: ��, 2: ��, 3: ��,
                             // 4: ��, 5: ƽ, 6: ����

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

struct B11_PACKET_REQ
{
    QUERY_HEADER hdr;       // packet_type: ID_B11_PACKET_REQ

    B11_BODY_REQ body;
};

// �ɼ� ���������� �к�, �Ϻ� ���� ���
struct B11_HEADER_REP
{
    QUERY_HEADER hdr;

    int acode;               // anchor code

    short time_unit;         // 1, 5, 10, 20, 40, 60 ���
    short term;              // 0: ��, 1: ��, 2: ��, 3: ��,
                             // 4: ��, 5: ƽ, 6: ����

    int count;               // ������ ����

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

// �ɼ� ���������� �к�, �Ϻ� ���� ��Ŷ
struct B11_DATA_REP
{
    int acode;                   // anchor code
    int date;                    // ��¥
    int time;                    // �ð�
    int kospi200;                // kospi200
    int future_cur_price;        // ���� ������
};

struct B11_PACKET_REP
{
    B11_HEADER_REP hdr;          // packet_type: ID_B11_PACKET_REP

    B11_DATA_REP* body;          // Header �� count ����

    QUERY_FOOTER footer;       // packet_type: ID_B11_PACKET_REP
};

// ��������Ʈ ��û ��Ŷ
struct B12_BODY_REQ
{
    int acode;                   // anchor code
    char db_num[20];             // db_num
                                 // �����: ó�� ��ȸ�ÿ��� db_num�� �𸣹Ƿ� 
                                 // 0�� �ѱ��
                                 // ���� ��ư Ŭ���� db_num�� �ָ� �� ��������
    int date;                    // �˻���   YYYYMMDD
    int info_code;               // �۽Ż� ����
                                 // 00:��ü(����/����)
                                 // 01:edaily, 02:joins, 03:�����Ӱ���, 04:���̳��ȴ���,
                                 // 05:etoday,  06:�ѱ�����,  07:Financial Point
                                 // 08:�Ӵ�������,  09:���մ���, 10:������ 99:����
    int class_code;              // ���� ����
    char sword[20];              // �˻���

    int count;                   // ������ ��û ����

    unsigned char by_chart;              // 'D' : �Ϻ���Ʈ���� ���������Ͱ� �Ϸ翡 �ϳ���
                                 // '\0'  : �⺻��
    unsigned char filler1;
    short site;                  // 0: ��ũ, 1: �Ϳ�, 2: SK

    unsigned char filler2;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

struct B12_PACKET_REQ
{
    QUERY_HEADER hdr;           // packet_type: ID_B12_PACKET_REQ

    B12_BODY_REQ body;
};

// ��������Ʈ ���� ���
struct B12_HEADER_REP
{
    QUERY_HEADER hdr;

    int count;               // ������ ����

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

// ��������Ʈ ���� ��Ŷ
struct B12_DATA_REP
{
    char db_num[20];            // db_num Primary_KEY
    int date;                   // ��¥
    int time;                   // �ð�
    int info_code;              // �۽Ż� ����
    int class_code;             // ���� ����
    int acode;                  // anchor code
    char title[136];            // ���� ����
};

struct B12_PACKET_REP
{
    B12_HEADER_REP hdr;          // packet_type: ID_B12_PACKET_REP

    B12_DATA_REP* body;          // Header �� count ����

    QUERY_FOOTER footer;         // packet_type: ID_B12_PACKET_REP
};

// �������� ��û ��Ŷ
struct B13_BODY_REQ
{
    char db_num[20];             // db_num

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

struct B13_PACKET_REQ
{
    QUERY_HEADER hdr;       // packet_type: ID_B13_PACKET_REQ

    B13_BODY_REQ body;
};

// �������� ���� ���
struct B13_HEADER_REP
{
    QUERY_HEADER hdr;

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

// �������� ���� ��Ŷ
// Component �ȿ����� �޸� ������ �Ѵ�.
// ���� Strcutor pointer �� �Ľ��ϸ� �ٸ� ������ ħ���� ������ �����Ͽ� ��������.
struct B13_DATA_REP
{
    char db_num[20];       // db_num Primary_KEY
    int length;           // ���� ����
    char* content;  // ����
};

struct B13_PACKET_REP
{
    B13_HEADER_REP hdr;          // packet_type: ID_B13_PACKET_REP

    B13_DATA_REP body;

    QUERY_FOOTER footer;       // packet_type: ID_B13_PACKET_REP
};

// ���� sort ��û ��Ŷ
struct B14_BODY_REQ
{
    int sort_type;    // sort Ÿ��
        // 1 : ���簡                 cur_price
        // 2 : �ð�                   open_price
        // 3 : ��                   high_price
        // 4 : ����                   low_price
        // 5 : ���� �ŷ���            volume
        // 6 : ���� �ŷ����          cash
        // 7 : �ŵ�ȣ��                 hoga[0].sel_price
        // 8 : �ż�ȣ��               hoga[0].buy_price
        // 9 : �ŵ�ȣ�� �ܷ�          hoga[0].sell_vol
        // 10: �ż�ȣ�� �ܷ�          hoga[0].buy_vol
        // 11: �ð��� �Ѹŵ� �ܷ�     timeout_sell_vol
        // 12: �ð��� �Ѹż� �ܷ�     timeout_buy_vol
        // 13: 10�ܰ� �Ѹŵ�ȣ�� �ܷ� tot10_sell_vol
        // 14: 10�ܰ� �Ѹż�ȣ�� �ܷ� tot0_buy_vol
        // 15: ������                 (��-����)*100/(����)
        // 16: ������                 �� - ����
        // 17: �ż�ȣ���ܷ�/�ŷ���    hoga[0].buy_vol/volume
        // 18: 1��ȣ��/�Ѹż�(%)      hoga[0].buy_price/tot10_buy_vol
        // 19: �ŵ�ȣ���ܷ�/�ŷ���    hoga[0].sell_vol/volume
        // 20: 1��ȣ��/�Ѹŵ�(%)      hoga[0].sell_price/tot10_sell_vol
        // 21: �Ѹż�/�Ѹŵ�(%)       tot10_buy_vol*100/tot10_sell_vol
        // 22: �Ѹż�/�Ѱŷ���(%)     tot10_sell_vol*100/volume
        // 31:���                    ���簡 - ��������
        // 32:���
         // 33:ȸ����

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

struct B14_PACKET_REQ
{
    QUERY_HEADER hdr;       // packet_type: ID_B14_PACKET_REQ

    B14_BODY_REQ body;
};

// ���� sort ���� ���
struct B14_HEADER_REP
{
    QUERY_HEADER hdr;
    int sort_type;
    int count;

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

// ���� sort ���� ��Ŷ
struct B14_DATA_REP
{
    int acode;            // ��Ŀ�ڵ�
    int value;                      // �ش� sort ��
};

struct B14_PACKET_REP
{
    B14_HEADER_REP hdr;          // packet_type: ID_B14_PACKET_REP

    B14_DATA_REP* body;

    QUERY_FOOTER footer;       // packet_type: ID_B14_PACKET_REP
};

// �׸� ��ȸ ��û ��Ŷ
struct B15_BODY_REQ
{
    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

struct B15_PACKET_REQ
{
    QUERY_HEADER hdr;       // packet_type: ID_B15_PACKET_REQ

    B15_BODY_REQ body;
};

// �׸� ��ȸ ���� ���
struct B15_HEADER_REP
{
    QUERY_HEADER hdr;
    int count;

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

// �׸� ��ȸ ���� ��Ŷ
struct B15_DATA_REP
{
    char theme_code[4];                 // �׸��ڵ�
    char theme_name[64];                // �׸���
    int date;                           // ��¥
    int time;                           // �ð�
    int tot_count;        // �׸� ���� �����
    int upcount;                        // ��� �����
    int high_count;                     // ���� �����
    int downcount;                      // �϶� �����
    int low_count;                      // �϶� �����
    int avg_rate;                       // ��� �����
};

struct B15_PACKET_REP
{
    B15_HEADER_REP hdr;          // packet_type: ID_B15_PACKET_REP

    B15_DATA_REP* body;

    QUERY_FOOTER footer;       // packet_type: ID_B15_PACKET_REP
};

// �Ϻ� �ܱ��� ��ȸ ��û ��Ŷ
struct B16_BODY_REQ
{
    int acode;               // anchor code
    int count;               // ������ ��û ����. �켱��
    int s_date;              // ������   YYYYMMDD
    int e_date;              // ������   YYYYMMDD

    short time_unit;         // 1, 5, 10, 20, 40, 60 ���
    short term;              // 0: ��, 1: ��, 2: ��, 3: ��,
                             // 4: ��, 5: ƽ, 6: ����
    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

struct B16_PACKET_REQ
{
    QUERY_HEADER hdr;       // packet_type: ID_B16_PACKET_REQ

    B16_BODY_REQ body;
};

// �Ϻ� �ܱ��� ��ȸ ���� ���
struct B16_HEADER_REP
{
    QUERY_HEADER hdr;
    int acode;
    int count;

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

// �Ϻ� �ܱ��� ��ȸ ���� ��Ŷ
struct B16_DATA_REP
{
    int acode;                        // ��Ŀ�ڵ�
    int date;                         // ��¥
    int reg_volume;                   // �����ֽļ�
    int prv_close_price;              // ��������
    int prv_volume;                   // ���ϰŷ���
    int buy_max_vol;                  // �ֹ����ɼ���
    int buy_min_vol;                  // �ֹ����ɼ���
    int limit_max_vol;                // �ѵ�����
    int limit_min_vol;                // �ѵ�����
    int limit_ratio;                  // �ѵ�����
    int chg_max_vol;                  // ��������
    int chg_min_vol;                  // ��������        ����:��
    int reserved_max_vol;             // �����ֽļ�        ����:����
    int reserved_min_vol;             // �����ֽļ�        ����:��
    int reserved_ratio;               // ��������
    int vanish_ratio;                 // �ѵ�������
};

struct B16_PACKET_REP
{
    B16_HEADER_REP hdr;          // packet_type: ID_B16_PACKET_REP

    B16_DATA_REP* body;

    QUERY_FOOTER footer;       // packet_type: ID_B16_PACKET_REP
};
//--------------------------------------------------------------------------
//���� ��ȸ ��û ��Ŷ
struct B17_BODY_REQ
{
    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

struct B17_PACKET_REQ
{
    QUERY_HEADER hdr;       // packet_type: ID_B17_PACKET_REQ

    B17_BODY_REQ body;
};

//���� ��ȸ ���� ���
struct B17_HEADER_REP
{
    QUERY_HEADER hdr;
    int count;

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

// ���� ��ȸ ���� ��Ŷ
struct B17_DATA_REP
{
    char sector_code[4];                // ���� �ڵ�
    char sector_name[64];               // ���� ��
    int date;                           // ��¥
    int time;                           // �ð�
    int tot_count;                        // ���� ���� �����
    int avg_rate;                       // ��� �����
};

struct B17_PACKET_REP
{
    B17_HEADER_REP hdr;          // packet_type: ID_B17_PACKET_REP

    B17_DATA_REP* body;

    QUERY_FOOTER footer;       // packet_type: ID_B17_PACKET_REP
};

//--------------------------------------------------------------------------
// �������� �����丮 ��ȸ ��û ��Ŷ
struct B18_BODY_REQ
{
    int req_count;           // �����丮 ��û ����
    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

struct B18_PACKET_REQ
{
    QUERY_HEADER hdr;       // packet_type: ID_B18_PACKET_REQ

    B18_BODY_REQ body;
};

// �������� �����丮 ��ȸ ���� ���
struct B18_HEADER_REP
{
    QUERY_HEADER hdr;

    int count;
};

// �������� �����丮 ��ȸ ���� ��Ŷ
struct B18_DATA_REP
{
    int date;
    int time;
    int site;
    char msg[1024];
};

struct B18_PACKET_REP
{
    B18_HEADER_REP hdr;          // packet_type: ID_B18_PACKET_REP

    B18_DATA_REP* body;

    QUERY_FOOTER footer;       // packet_type: ID_B18_PACKET_REP
};

//--------------------------------------------------------------------------
// ���� �ٽ��� ����Ʈ ��ȸ ��û
struct B19_BODY_REQ
{
    int bdate;              // ������

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

struct B19_PACKET_REQ
{
    QUERY_HEADER hdr;       // packet_type: ID_B19_PACKET_REQ

    B19_BODY_REQ body;
};

// ���� �ٽ��� ����Ʈ ��ȸ ����
struct B19_HEADER_REP
{
    QUERY_HEADER hdr;

    int count;
};

// �������� �����丮 ��ȸ ���� ��Ŷ
struct B19_DATA_REP
{
    int date;
    int acode;
    int time;                   // �ð�
    int cur_price;              // ���簡
    int open_price;             // �ð�
    int high_price;             // ��
    int low_price;              // ����
    int volume;                 // ���� �ŷ���
    int prv_close_price;        // ��������
    int daebi;                  // ���ϴ��
    int daebi_rate;             // �����
    int volume_rate;            // �ŷ������
    char comment[MAX_TODAY_COMMENT_NUM];         // �ٽ��� �ڸ�Ʈ
};

struct B19_PACKET_REP
{
    B19_HEADER_REP hdr;          // packet_type: ID_B19_PACKET_REP

    B19_DATA_REP* body;

    QUERY_FOOTER footer;
};
#endif
