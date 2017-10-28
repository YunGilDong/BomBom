//--------------------------------------------------------------------------
// SB_Com_Packet.pas : SBComponents 와 Anchor2.0 server 와 인터넷 통신 protocol
// Script            : Anchor2.0 (Address : 181) server 와 TSBCom 과의 통신 protocol
//--------------------------------------------------------------------------
#ifndef _SB_PACKET_H
#define _SB_PACKET_H

//-----------------------------------------------------------------------------
// 시세의 호가 개수
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
const int ID_PATCH_REQ            = 131;    // 패치 정보 요청 패킷
const int ID_PATCH_RES            = 132;    // 패치 정보 응답 패킷

const int ID_PATCH_CMD          = 8001;
const int ID_PATCH_LIST_HEADER  = 8002;
const int ID_PATCH_LIST_FOOTER  = 8003;
const int ID_PATCH_TRANSFER_HEADER = 8004;
const int ID_PATCH_TRANSFER_FOOTER = 8005;
const int ID_PATCH_ERROR        = 8006;
const int ID_PATCH_OK           = 8007;

const int PC_LIST                = 0;      // 디렉토리/파일 리스트 요청
const int PC_MKDIR                = 1;      // 디렉토리 생성
const int PC_RMDIR                = 2;      // 디렉토리 삭제
const int PC_RMFILE                = 3;      // 파일 삭제
const int PC_READ                = 4;      // 파일읽기요청

// 2. Login TR
const int ID_L1_PACKET_REQ          = 10001;  // 로그인 요청 패킷
const int ID_L1_PACKET_REP          = 10002;  // 로그인 응답 패킷
const int ID_L3_PACKET              = 10003;  // 로그인 강제접속 및 해지

// 3. 연결 TR
const int ID_D1_PACKET            = 10010;  // Hello 패킷
const int ID_D2_PACKET            = 10011;  // HeartBeat 패킷

const int ID_C1_PACKET           = 10020;  // 컨트롤 패킷
const int ID_C2_PACKET            = 10021;  // 장구분 패킷

// 4. 핵투 핵심주
const int ID_HT_C1_PACKET                      = 10030;  // 핵투 핵심주 리스트
                                                        // 디비추가 요청 패킷
const int ID_HT_C1_PACKET_REP                  = 10031;  // 핵투 핵심주 리스트
                                                        // 디비추가 응답 패킷
const int ID_HT_C2_PACKET                      = 10032;  // 핵투 핵심주 특정일자
                                                        // 리스트 요청 패킷
const int ID_HT_C2_PACKET_REP                 = 10033;  // 핵투 핵심주 특정일자
                                                        // 리스트 응답 패킷
// 5. Real TR
const int ID_A1_PACKET            = 11000;  // 시세등록/삭제 패킷

const int ID_A2_PACKET          = 11010;  // 실시간 사용자 로그패킷
const int ID_A3_PACKET          = 11020;  // 실시간 조건식 종목 요청패킷

const int ID_S1_PACKET            = 11100;  // 주식 시세 패킷
const int ID_S3_PACKET          = 11101;  // 주식 시세 minor
const int ID_J1_PACKET            = 11110;  // 지수 시세 패킷
const int ID_F1_PACKET            = 11120;  // 선물 시세 패킷
const int ID_F3_PACKET          = 11121;  // 선물 시세 minor
const int ID_O1_PACKET            = 11130;  // 옵션 시세 패킷
const int ID_O3_PACKET          = 11131;  // 옵션 시세 minor
const int ID_T1_PACKET            = 11140;  // 투자자 시세 패킷
const int ID_U1_PACKET            = 11150;  // 해외 시세 패킷
const int ID_PC1_PACKET            = 11160;  // 풋콜레이쇼
const int ID_P1_PACKET            = 11170;  // 포지션  시세 패킷
const int ID_N1_PACKET            = 11180;  // 실시간 뉴스 패킷
const int ID_ST1_PACKET            = 11190;  // Unknown
const int ID_ST2_PACKET            = 11191;  // 실시간 테마 패킷
const int ID_R1_PACKET          = 11200;  // 실시간 거래원 패킷
const int ID_UP1_PACKET         = 11210;  // 실시간 업종 패킷
const int ID_SM_PACKET          = 11220;  // 실시간 마스터 패킷
const int ID_CD1_PACKET         = 11230;  // 실시간 조건식 종목 패킷
/*/    TODO: MINI
const int ID_MF1_PACKET            = 11240;  // 미니 선물 시세 패킷
const int ID_MF3_PACKET         = 11241;  // 미니 선물 시세 minor
const int ID_MO1_PACKET            = 11250;  // 미니 옵션 시세 패킷
const int ID_MO3_PACKET         = 11251;  // 미니 옵션 시세 minor
//*/

// 6. 조회 TR
const int ID_B1_PACKET_REQ      = 12000;  // 분, 일봉 요청 패킷
const int ID_B1_PACKET_REP      = 12001;  // 분, 일봉 응답 패킷

const int ID_B2_PACKET_REQ      = 12010;  // 체결 데이터 요청 패킷
const int ID_B2_PACKET_REP      = 12011;  // 체결 데이터 응답 패킷

const int ID_B3_PACKET_REQ        = 12020;  // 투자자 분,일봉 요청 패킷
const int ID_B3_PACKET_REP        = 12021;  // 투자자 분,일봉 응답 패킷

const int ID_B4_PACKET_REQ        = 12030;  // PCR 분,일봉 요청 패킷
const int ID_B4_PACKET_REP        = 12031;  // PCR 분,일봉 응답 패킷

const int ID_B5_PACKET_REQ        = 12040;  // 포지션 분,일봉 요청 패킷
const int ID_B5_PACKET_REP        = 12041;  // 포지션 분,일봉 응답 패킷

/* 주식, 지수, 선물, 옵션, 해외    */
const int ID_B6_PACKET_REQ        = 12050;  // 시세 요청 패킷
const int ID_B6_PACKET_REP        = 12051;  // 시세 응답 패킷

const int ID_B7_PACKET_REQ        = 12060;  // 선물이론가 요청 패킷
const int ID_B7_PACKET_REP        = 12061;  // 선물이론가 응답 패킷

const int ID_B8_PACKET_REQ        = 12070;  // 선물 미결제약정 요청 패킷
const int ID_B8_PACKET_REP        = 12071;  // 선물 미결제약정 응답 패킷

const int ID_B9_PACKET_REQ        = 12080;  // 선물 베이시스 요청 패킷
const int ID_B9_PACKET_REP        = 12081;  // 선물 베이시스 응답 패킷

const int ID_B10_PACKET_REQ        = 12090;  // 옵션 이론가 요청 패킷
const int ID_B10_PACKET_REP        = 12091;  // 옵션 이론가 응답 패킷
                                          // 옵션 역사적 변동성 차트
                                          // 옵션 내재 변동성 차트
                                          // 옵션 델타 차트
                                          // 옵션 감마 차트
                                          // 옵션 베가 차트
                                          // 옵션 세타 차트
                                          // 옵션 민감도
                                          // 옵션 변동성

const int ID_B11_PACKET_REQ        = 12100;  // 옵션 역사적변동 요청 패킷
const int ID_B11_PACKET_REP        = 12101;  // 옵션 역사적변동 응답 패킷

const int ID_B12_PACKET_REQ        = 12110;  // 뉴스리스트 요청 패킷
const int ID_B12_PACKET_REP        = 12111;  // 뉴스리스트 응답 패킷

const int ID_B13_PACKET_REQ        = 12120;  // 뉴스본문 요청 패킷
const int ID_B13_PACKET_REP        = 12121;  // 뉴스본문 응답 패킷

const int ID_B14_PACKET_REQ        = 12130;  // 종목 sort 요청 패킷
const int ID_B14_PACKET_REP        = 12131;  // 종목 sort 응답 패킷

const int ID_B15_PACKET_REQ        = 12140;  // 테마 조회 요청 패킷
const int ID_B15_PACKET_REP        = 12141;  // 테마 조회 응답 패킷

const int ID_B16_PACKET_REQ        = 12150;  // 외국인 조회 요청 패킷
const int ID_B16_PACKET_REP        = 12151;  // 외국인 조회 응답 패킷

const int ID_B17_PACKET_REQ        = 12160;  // 섹터종목조회
const int ID_B17_PACKET_REP        = 12161;  // 섹터종목조회

const int ID_B18_PACKET_REQ        = 12170;  // 쪽지히스토리 조회 요청 패킷
const int ID_B18_PACKET_REP        = 12171;  // 쪽지히스토리 조회 응답 패킷

const int ID_B19_PACKET_REQ        = 12180;  // 핵투 핵심주조회 요청 패킷
const int ID_B19_PACKET_REP        = 12181;  // 핵투 핵심주조회 응답 패킷

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
// B1_PACKET_REQ  body의 term
/*
const short DAY_DATA_TYPE    = 0;  // 일
const short WEEK_DATA_TYPE    = 1;  // 주
const short MONTH_DATA_TYPE    = 2;  // 월
const short MIN_DATA_TYPE    = 3;  // 분
const short SEC_DATA_TYPE    = 4;  // 초
const short TICK_DATA_TYPE    = 5;  // 틱
const short INTRA_DATA_TYPE    = 6;  // 일중
*/

//--------------------------------------------------------------------------
// 파일 패치
//--------------------------------------------------------------------------
// 파일 요청 패킷

struct PATCH_CMD
{
    short packet_type;     // ID_PATCH_CMD
    short detail_type;

    int cmd;               // PC_LIST:디렉토리/파일 리스트 요청
                           // PC_MKDIR: 디렉토리 생성, PC_RMDIR: 디렉토리 삭제
                           // PC_RMFILE: 파일 삭제, PC_READ: 파일 요청
    char filename[504];
    int site;
    int work_type; // 1 - 패치, 2 - 사용자, 3 - 로그
    int broadcast;

    unsigned char filler;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

// 전송 에러 패킷
struct PATCH_ERROR
{
    short packet_type;     // ID_PATCH_ERROR
    short detail_type;

    char msg[512];         // 에러 메시지

    unsigned char filler;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

// 전송 성공 패킷
struct PATCH_OK
{
    short packet_type;      // ID_PATCH_OK
    short detail_type;

    unsigned char filler;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

// 파일목록 파일 헤더 패킷
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

// 파일목록 파일 데이터 패킷
struct PATCH_LIST_DATA
{
    int type;              // [파일 타입] FT_FILE: 파일, FT_DIR: 디렉터리

    char filename[512];
    int filedate;
    int filetime;
    int filesize;
};

// 파일목록 파일 Footer 패킷
struct PATCH_LIST_FOOTER
{
    short packet_type;    // ID_PATCH_LIST_FOOTER
    short detail_type;

    unsigned char filler;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

// 파일 전송 헤더 패킷
struct PATCH_TRANSFER_HEADER
{
    short packet_type;    // ID_PATCH_TRANSFER_HEADER
    short detail_type;

    char filename[504];
    int site;
    int work_type; // 1- 패치, 2 - 사용자, 3 - 로그
    int filedate;
    int filetime;
    int filesize;
    int broadcast;

    unsigned char filler;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

// 파일 전송 데이터 패킷
struct PATCH_TRANSFER_FOOTER
{
    short packet_type;     // ID_PATCH_TRANSFER_FOOTER
    short detail_type;

	unsigned char filler;
    unsigned char ff;
	unsigned char cr;
    unsigned char lf;
};

// 연결 체크 패킷
struct CONNECTION_CHECK
{
    char process_name[64];
    int IsConnected;
};

// 프로그램 체크 패킷
struct ALIVE_CHECK
{
    char process_name[64];
    int IsAlive;
};
//--------------------------------------------------------------------------
// patch 용 파일 타입 정보
const int FT_FILE                        = 0;                    // 파일
const int FT_DIR                        = 1;                    // 디렉터리

/// 해당 packet이 어떠한 형태로 들어오는지를 확인하기 위한 data
struct GUBUN_DATA
{
    short packet_type;         // 패킷 타입
    short detail_type;         // 패킷 부가 정보
};
//--------------------------------------------------------------------------
// Master file
//--------------------------------------------------------------------------
struct INVEST_HOGA
{
    int sell_price;                        // 매도호가
    int sell_vol;                          // 매도호가 잔량
    int buy_price;                         // 매수호가
    int buy_vol;                           // 매수호가 잔량
    int net_buy_price;                     // 순 매수
    int net_buy_vol;                       // 순 매수  잔량
};

// 주식 마스터
struct MASTER_STOCK_PACKET
{
    /* 거래소/코스닥 공통 부분      */
    short packet_type;                  /* 패킷 타입 (ID_MASTER_JONGMOK)         */
    short code_no;                      /* 코드일련번호                          */
    int acode;                          /* 앵커내부 코드                         */
    int date;                           /* 날짜 YYYYMMDD                         */
    char code[9];                       /* 코드                                  */
    char market_tag;                    /* 시장 구분 '1': 거래소, '2': 코스닥        */
    char capital_tag;                   /* 자본금                                */
                                        /* 거래소 2:대형, 3:중형, 4:소형         */
                                        /* 코스닥 6:(100억~), 7:(50억~100억),    */
                                        /*        8:(30억~50억), 9:(30억미만)    */
    char ctrl_tag;                      /* 거래정지구분                          */
                                        /* 0: 정상, 1: 거래중단, 2: 거래정지     */
    char kwanli_tag[1];                 /* 관리구분 0:정상, 1:관리               */
    char tuja_warn[1];                  /* 투자경고 0:일반, 1:투자경고           */
    char prv_gise_flag[1];              /* 기세 1:전일기세발생                   */
    char prv_daebi[1];                  /* 등락 1:상한, 2:상승, 3:보합, 4:하한,  */
                                        /*      5:하락              */
    char ex_tag[1];                     /* 1: 권리락, 2: 배당락,3: 권배락,       */
                                        /* 4: 액면분할 5: 액면병합, 6:중간배당락 */
                                        /* 7:권리중간배당락              */
    char fake_gongsi[1];                /* 불성실 공시 여부                      */
    short settle_mon;                   /* 결산기 월                             */
    char intl_code[12];                 /* 국제 코드                             */
    char name[44];                      /* 종목명                                */
    char eng_name[40];                  /* 영문명                                */
    int basic_price;                    /* 기준가                                */
    int prv_open_price;                 /* 전일 시가                             */
    int prv_high_price;                 /* 전일 고가                             */
    int prv_low_price;                  /* 전일 저가                             */
    int prv_close_price;                /* 전일 종가                             */
    int prv_volume;                     /* 전일 거래량                           */
    int prv_cash;                       /* 전일 거래대금 단위: 10000원           */
    int max_price;                      /* 상한가                                */
    int min_price;                      /* 하한가                                */
    int reg_volume;                     /* 상장주식수 단위 : 천주                */
    int face_value;                     /* 액면가                                */
    int reg_date;                       /* 상장일                                */
    int capital;                        /* 자본금   단위:백만원                  */
    int sub_value;                      /* 대용가                                */
    int open_value;                     /* 시가총액 단위:억원                    */
    short year_max_date;                /* 연중 최고가 일자 월일                 */
    short year_min_date;                /* 연중 최저가 일자 월일                 */

    int year_max_price;                 /* 연중 최고가                           */
    int year_min_price;                 /* 연중 최저가                           */
    short top_price_day;                /* 연속상한가일수                        */
    short down_price_day;               /* 연속하한가일수                        */
    short year_max_day;                 /* 연간 누적상한가 일수                  */
    short year_min_day;                 /* 연간 누적하한가 일수                  */
    int max52w_price;                   /* 52주 최고가                           */
    int min52w_price;                   /* 52주 최저가                           */
    int max52w_date;                    /* 52주 최고일                           */
    int min52w_date;                    /* 52주 최저일                           */
    int sellbuy_open;                   /* 정리매매 개시일                       */
    int sellbuy_close;                  /* 정리매매 종료일                       */
    int buy_max_volume;                 /* 외국인 주문가능 수량  단위:억주       */
    int buy_min_volume;                 /* 외국인 주문가능 수량  단위:주         */
    int limit_max_volume;               /* 외국인 한도수량  단위:억주            */
    int limit_min_volume;               /* 외국인 한도수량  단위:주              */
    int limit_ratio;                    /* 외국인 한도비율  소숫점이하 2자리     */
    int capital_upday;                  /* 액면 변경일자                         */
    int ex_price;                       /* 배당금                                */
    short capital_chrul;                /* 액면 변경비율    최종 액면변경비율 SET*/

                                        /* 업종 관련    */
    short upjong_large;                 /* 거래소:kospi200 업종, 코스닥:업종 대대*/
    short upjong_middle;                /* 거래소:업종, 코스닥:업종대            */
    short upjong_small;                 /* 거래소:제조업 코드, 코스닥:업종중     */

    char tonghan_jisu_tag[1];           /* 통합지수 구분        0:일반, 1:대상   */
    char filler1[1];

    char pos_tag[2];                    /* 증권그룹 ID                                                      */
                                        /*      ST:주권 MF:증권투자회사 RT:부동산투자회사 SC:선박투자회사   */
                                        /*      IF:사회간접자본투융자회사 DR:주식예탁증서 EW:ELW EF:ETF     */
                                        /*      SW:신주인수권증권 SR:신주인수권증서 BC:수익증권 FE:해외ETF  */
                                        /*      FS:외국주권                                                 */
    /* 거래소 전용  */
    char kospi_gubun[1];                /* [거래소] '0':일반 '1':kospi100,       */
                                        /*          '2':kosp50, '3':kospi200     */
    char devide_tag[1];                 /* [거래소] 액분 구분 1:분할, 2: 병합    */
    char filler2[2];
    int max50_price;                    /* [거래소] 50일 최고가                 */
    int min50_price;                    /* [거래소] 50일 최저가                 */
    int max50_date;                     /* [거래소] 50일 최고가일자             */
    int min50_date;                     /* [거래소] 50일 최저가일자             */
    int sellbuy_unit;                   /* [거래소] 매매단위                    */

    /* 코스닥 전용  */
    int start_date;                     /* [코스닥] 매매 시작일                        */
    short nation_code;                  /* [코스닥] 국가코드                           */
    short money_unit;                   /* [코스닥] 화폐단위                           */
    char venture_tag[1];                /* [코스닥] 벤처구분.      0:일반, 1:벤처      */
    char star_jisu_tag[1];              /* [코스닥] STAR지수 구분  0:일반, 1:대상      */
    char exchange_rate[14];             /* [코스닥] 적용환율                           */

    char context[160];                  /* 씽크풀로부터 받는 종목 설명 필드            */

    char krx_field[20];                 /* KRX 지수에 대한 셋팅                        */
                                        /* [0] : KRX섹터 자동차구분     0:일반, 1:대상 */
                                        /* [1] : KRX섹터 반도체구분     0:일반, 1:대상 */
                                        /* [2] : KRX섹터 바이오구분     0:일반, 1:대상 */
                                        /* [3] : KRX섹터 금융구분       0:일반, 1:대상 */
                                        /* [4] : KRX섹터 정보통신구분   0:일반, 1:대상 */
                                        /* [5] : KRX섹터 에너지화학구분 0:일반, 1:대상 */
                                        /* [6] : KRX섹터 철강구분       0:일반, 1:대상 */
                                        /* [7] : KRX섹터 필수소비재구분 0:일반, 1:대상 */
                                        /* [8] : KRX섹터 미디어통신구분 0:일반, 1:대상 */
                                        /* [9] : KRX섹터 건설구분       0:일반, 1:대상 */
                                        /* [10]: KRX섹터 금융서비스구분 0:일반, 1:대상 */
    int reserved[5];                    /* 예약필드                                    */

    char filler[1];
    unsigned char ff;                           /* FF '0xff'                                   */
    unsigned char cr;                           /* CR '0x0d'                                   */
    unsigned char lf;                           /* LF '0x0a'                                   */
};

// 지수 마스터
struct MASTER_JISU_PACKET
{
    short packet_type;                  // 패킷 타입 (ID_MASTER_JISU)
    short code_no;                      // 코드일련번호

    int acode;

    int date;                           // 날짜 YYYYMMDD

    char code[10];                      // 사용자 입력 코드
    char name[50];                      // 업종명

    int prv_open_jisu;                  // 전일 시가 소수점 아래 2자리
    int prv_high_jisu;                  // 전일 고가 소수점 아래 2자리
    int prv_low_jisu;                   // 전일 저가 소수점 아래 2자리
    int prv_close_jisu;                 // 전일 종가 소수점 아래 2자리
    int prv_volume;                     // 전일거래량 단위:천주

    char market_gb;                     // 장구분, 숫자형
    unsigned char ff;                           // FF     '0xff'
    unsigned char cr;                           // CR     '0x0d'
    unsigned char lf;                           // LF     '0x0a'
};

// 선물 마스터
struct MASTER_FUTURE_PACKET
{
    short packet_type;                  // 패킷 타입 (ID_FUTURE_MASTER)
    short code_no;                         // 코드일련번호
    int acode;
    int date;                           // 날짜 YYYYMMDD
    char intl_code[16];                 // 국제 코드
    char code[8];                       // 사용자입력 코드
    char name[32];                      // 한글 종목 명
    int reg_date;                       // 상장일     연월일
    int last_deal_date;                 // 최종 거래일        연월일
    int basic_price;                    // 기준가 스프레드종목: 0
    int max_price;                      // 상한가     SIGN부호
    int min_price;                      // 하한가     SIGN부호
    int prv_close_price;                // 전일 종가      SIGN부호
    int prv_volume;                     // 전일 거래량        단위: 계약
    int prv_volume_near;                // 전일 근원물 거래량 단위: 계약
    int prv_volume_far;                 // 전일 원월물 거래량 단위: 계약
    int prv_cash1;                      // 전일 거래대금1 단위: 백만원
    int prv_cash2;                      // 전일 거래대금2 단위: 원
    int interval_max_price;                                ///< 실시간 상한가 간격             GSH 2014-09-01
    int interval_min_price;                                ///< 실시간 하한가 간격             GSH 2014-09-01
    char filler1[8];
    int prv_no_vol;                     // 전일 미결제약정 수량    단위:계약-확정치
                                        // 스프레드:0

    int prv_close_price_spread_near;    //전일 스프레드 근월물 종가
    int prv_close_price_spread_far;     //전일 스프레드 원월물 종가

    char code_near[20];                 // 근월물 종목코드    기본: ' '
    char code_far[20];                  // 원월물 종목코드    기본: ' '


    short listing_term;                 // 상장 일수
    short remaning_term;                // 잔존 일수

    int dividend_fature;                // 배당액 지수 미래가치
    int fair_settle_price;              // 이론가격(정산가)
    int fair_base_price;                // 이론가격(기준가)
    int cd_rate;                        // CD 금리 (X 1000)

    char prv_settle_gb[1];              // 전일정산가격 구분
    char prv_close_price_gb[1];         // 전일 종가 구분 1:실세, 2:기세, 3,무거래
    char real_limit_gb[1];                                  ///< 실시간 상한가 반영 여부(Y/N)   GSH 2014-09-01
    char filler2[1];

    int prv_settle_price;               // 전일 정산가격
    int list_high_price_day;            // 상장중 최고가 일자
    int list_high_price;                // 상장중 최고가
    int list_low_price_day;             // 상장중 최저가일자
    int list_low_price;                 // 상장중 최저가
    int entrance_day;                   // 입회일자

    char market_order_tag[1];           // 시장가허용구분  Y:허용 N:불허
    char jokun_tag[1];                  // 조건부지정가허용 구분 Y:허용 N:불허
    char choi_tag[1];                   // 최유리지정가 허용구분 Y:허용 N:불허
    char last_clear_price_tag[1];       // 최종결제가 구분

    int last_clear_price;               // 최종결제가
    int cb_limit_high_price;            // C.B. 상한가
    int cb_limit_low_price;             // C.B. 하한가
    int prv_time;                       // 전일 최종매매시작

    short real_remaining_term;          // 실잔존일수

    int prv_open_price;                 // 전일 시가
    int prv_high_price;                 // 전일 고가
    int prv_low_price;                  // 전일 저가

    unsigned char filler3[1];
    unsigned char ff;                           // FF     '0xff'
    unsigned char cr;                           // CR     '0x0d'
    unsigned char lf;                           // LF     '0x0a'
};

// 옵션 마스터
struct MASTER_OPTION_PACKET
{
    short packet_type;                  // 패킷 타입 (ID_MASTER_OPTION)
    short code_no;                      // 코드일련번호
    int acode;
    int date;                           // 날짜 YYYYMMDD
    char intl_code[20];                 // 국제 코드
    char code[8];                       // 사용자입력 코드
    char name[32];                      // 한글 종목 명
    char short_name[20];                // 축약명
    char call_tag[1];                   // 옵션 종류(ASCII) '2':call, '3': Put
    char last_trade_day_tag[1];         // 최종거래일 구분 1:평일, 2:거래최종일
    char filler1[2];
    int reg_date;                       // 상장일  년월일
    int first_deal_date;                // 최초거래일  년월일
    int last_deal_date;                 // 최종 거래일 년월일
    int entrance_date;                  // 입회일
    int close_date;                     // 만기 년월일
    short listing_term;                 // 기준일수
    short remaning_term;                // 잔존일수
    int run_price;                      // 행사가격
    int basic_price;                    // 기준가
    int max_price;                      // 상한가
    int min_price;                      // 하한가
    int prv_close_price;                // 전일 종가
    int prv_no_vol;                     // 전일 미결제약정수량
    int prv_volume;                     // 전일 거래량
    int prv_cash1;                      // 전일 거래대금1 단위: 백만원
    int prv_cash2;                      // 전일 거래대금2 단위: 원
    char trans_jgcode[4];               // 거래대상종목 "01":kospi200
    char first_month_tag[1];            // 근월물 구분 1:최근월물, 2:비해당, 3:최원월물
    char atm_tag[1];                    // ATM 구분 : 1:ATM, 2:ITM, 3:OTM
    char newer_tag[1];                  // 신규,추가,기존구분 1:신규, 2:추가, 3:기존
    char prv_close_tag[1];              // 전일종가 구분
    char margin_tag[1];                 // 매매증거금 기준가 구분
                                        // 1:당일종가(시세)
                                        // 2:당일기세(최초거래성립후기세
                                        // 3:전일증거금기준가( 최초거래성립후 종가미형성
                                        // 4:당일증거금이론가( 최초거래성립후 종가 미형성
    char real_limit_gb[1];                                  ///< 실시간가격제한여부     실시간 상하한가 반영 여부 (Y/N)     GSH 2014-09-01
    char filler4[2];

    int newer_day;                      // 신규/추가/기존일
    int dividend_current;               // 배당액지수 현재 가치

    int fair_value;               // 이론가 소숫점6자리
    int margin_price;             // 매매증거금 기준가 : 소숫점 2자리
    int interval_max_price;                                 ///< 실시간 상한가 간격 GSH 2014-09-01
    int interval_min_price;                                 ///< 실시간 하한가 간격 GSH 2014-09-01

    int cd_rate;                  // CD 금리: 단위:%
    int year_high_price_day;      // 연중최고가일자 YYYYMMDD
    int year_high_price;          // 연중최고가: 소숫점 2자리
    int year_low_price_day;       // 연중최저가일자 YYYYMMDD
    int year_low_price;           // 연중최저가: 소숫점 2자리
    int list_high_price_day;      // 상장중 최고가 일자
    int list_high_price;          // 상장중 최고가
    int list_low_price_day;       // 상장중 최저가 일자
    int list_low_price;           // 상장중 최저가

    char market_order_tag[1];     // 시장가허용 구분 Y:허용 N:불허
    char jokun_order_tag[1];      // 조건부지정가 허용구분 Y: 허용, N:불허
    char cwoori_order_tag[1];     // 최우리지정가허용구분 Y:허용, N:불허
    char base_price_tag[1];       // 기준가 구분
                                  // 1:전일증거금 기준가
                                  // 2:전일 기준가 (최초거래성립전 종가 미형성)
                                  // 3:당일기준가용 이론가 (최초거래성립전 종가 미형성
                                  // 4:전일 기세(최초거래성립후 기세형성)

    int inter_volatility;         // 내재변동성 : 소숫점 3자리
    int historic_volatility[3];   // 역사적 변동성 3개정도 (소수점 3자리)
    short real_remaining_term;    // 실잔존일수
    short filler6;

    int prv_open_price;           // 전일 시가
    int prv_high_price;           // 전일 고가
    int prv_low_price;            // 전일 저가

    unsigned char filler5[1];             // filler
    unsigned char ff;                     // FF     '0xff'
    unsigned char cr;                     // CR     '0x0d'
    unsigned char lf;                     // LF     '0x0a'
};

// 투자자 마스터
struct MASTER_INVEST_PACKET
{
    short packet_type;            // 패킷 타입 (ID_MASTER_INVEST)
    short code_no;                // 코드일련번호

    int acode;

    char tuja_gubun[8];           // 투자 구분
    char eng_name[48];            // 영문 업종명
    INVEST_HOGA hoga[INVEST_HOGA_NUM]; // 투자자 구분에 다른 100 ~ 10000 까지 12개
                                  // 0 개인
                                  // 1 외국인
                                  // 2 기관계
                                  // 3 증권회사
                                  // 4 보험회사
                                  // 5 투자신탁회사
                                  // 6 은행
                                  // 7 종금
                                  // 8 기금
                                  // 9 기타
    unsigned char filler1;
    unsigned char ff;                     // FF     '0xff'
    unsigned char cr;                     // CR     '0x0d'
    unsigned char lf;                     // LF     '0x0a‘
};

// P/C Ratio 마스터
struct MASTER_PC_PACKET
{
    short packet_type;            // ID_MASTER_PCR_IV
    char filler[2];

    int acode;                    // 앵커코드
    int date;                     // 날짜

    char name[80];                // 종목명

    int reserved[5];

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

// 포지션 마스터
struct MASTER_POSITION_PACKET
{
    short packet_type;            // ID_MASTER_POSITION
    char filler[2];

    int acode;                    // 앵커코드
    int date;                     // 날짜

    char name[80];                // 종목명
    int info_acode;

    int reserved[5];

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

// 해외 마스터
struct MASTER_US_PACKET
{
    short packet_type;                                      // 패킷 타입 (ID_MASTER_US)
    short code_no;                                          // 코드일련번호

    int acode;

    char code[12];                                          // 사용자 입력 코드
    char eng_name[48];                                      // 영문 업종명

    char han_name[48];                                      // 한글 업종명
    char place[28];                                         // usinfo 소속

    char symbol[12];                                        // Symbol

    int prv_open_price;                                     // 전일 시가
    int prv_high_price;                                     // 전일 고가
    int prv_low_price;                                      // 전일 저가
    int prv_cur_price;                                      // 전일 종

    int div;                  // divide
    int open_date;              // 개장일
    
    unsigned char filler2[1];                                       // 패딩비트
    unsigned char ff;                                               // FF     '0xff'
    unsigned char cr;                                               // CR     '0x0d'
    unsigned char lf;                                               // LF     '0x0a‘
};

//--------------------------------------------------------------------------
// TR 공통
//--------------------------------------------------------------------------
// Real Packet PreHeader  // 데이터처리 엔진에서 사용하는 부분
struct REAL_HEADER
{
    unsigned short packet_type;      // TR Number
    unsigned short header_size;      // 패킷 헤더 크기(byte)
    int total_size;          // 패킷 천체 크기(byte)

    int acode;               // Anchor code
    int detail_type;         // 0: 호가 + 체결, 1: 체결
};

// Query Packet PreHeader  // 데이터처리 엔진에서 사용하는 부분
struct QUERY_HEADER
{
    unsigned short packet_type;      // TR Number
    unsigned short header_size;      // 패킷 헤더 크기(byte)
    int total_size;          // 패킷 천체 크기(byte)

    unsigned int handle;             // TSBQuery Handle

    unsigned char zip_flag;          // [압축 플래그] 0: uncompress, 1: compress

    char filler1[3];
};
// Query Footer           // Chart 에서 사용 
struct QUERY_FOOTER
{
    QUERY_HEADER hdr;

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

//--------------------------------------------------------------------------
// 로그인 TR
//--------------------------------------------------------------------------
// 로그인 요청 패킷
struct L1_BODY_REQ
{
    char id[32];              //  User ID
    char pw[32];              //  User Password

    unsigned short site;              // 0:앵커2.0, 1:WOW, 2:SK HTS …etc 에러
    char filler1[2];          // 필러

    unsigned char set_ip;             // IP 고정 '1', 나머지 자동
    unsigned char ff;                 // 0xFF
    unsigned char cr;                 // 0x0D
    unsigned char lf;                 // 0x0A
};

struct L1_PACKET_REQ
{
    REAL_HEADER hdr;          // packet_type: ID_ L1_PACKET_REQ
    // acode 사용 안함.
    L1_BODY_REQ body;
};

// 로그인 응답 패킷
struct L1_BODY_REP
{
    int err_no;                // [에러 코드]
                               // 0: 정상, 1: 다중 접속, 2: 로그인 실패
    char err_msg[1024];        // [에러 메시지]

    char id[32];               // 사용자 ID
    char nick[32];             // 사용자 필명
    char name[32];             // 사용자 이름

    int today;                 // 오늘 날짜 YYYYMMDD

    int jongmok_start_time;    // 종목 장 시작 시간 HHMMSS
    int jongmok_end_time;      // 종목 장 끝 시간 HHMMSS

    int future_start_time;     // 선물 장 시작 시간 HHMMSS
    int future_end_time;       // 선물 장 끝 시간 HHMMSS

    int chart_begin_date;      // 차트 사용 시작 날짜 YYYYMMDD
    int chart_end_date;        // 차트 사용 만료 날짜 YYYYMMDD

    int first_flag;            // [차트 처음 사용자 여부]
                               // 0:처음사용아님 1:처음사용
    int chart_type;            // [차트 버전]
                               // 라이트(CHART_LIGHT) 프리미엄(CHART_PREMIUM)
    int reserved[5];

    char anchor_d_ip[2][16];   // anchor_d ip
    int anchor_d_port;         // anchor_d 포트

    char chart_d_ip[2][16];    // chart_d ip
    int chart_d_port;          // chart_d 포트

    char file_d_ip[2][16];     // 파일 서버 ip
    int file_d_port;           // 파일 서버 포트

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

// 멀티접속 중 강제접속 및 접속해지
struct L3_PACKET
{
    REAL_HEADER hdr;           // packet_type 10003
                               // detail_type 1:강제접속(예), 2:해지(아니오)

    char id[32];               // 회원 아이디
    char anchor_d_ip[16];      // anchor_d IP
    int anchor_d_port;         // user가 접속한 anchor_d 포트

    char filler;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};
//--------------------------------------------------------------------------
// 리얼 서버 연결 TR, 연결 유지 TR
//--------------------------------------------------------------------------
// AnchorD UserD 최초 접속 패킷
struct D1_BODY
{
    char id[32];            // 회원 아이디
    int user_type;          // [앵커 사용자 타입] 프리미엄, 라이트, 일반...
    char anchor_d_ip[16];   // anchor_d IP
    short anchor_d_num;     // user가 접속한 anchor_d 번호
    short anchor_d_fd;      // user가 접속한 anchor_d 에서 user 등록 id
    char user_d_ip[16];     // user_d 서버 IP
    int user_d_port;        // user_d 접속 포트

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

struct D1_PACKET
{
    REAL_HEADER hdr;        // packet_type: ID_D1_PACKET
    // acode 사용 안함.
    D1_BODY body;
};

// AnchorD 와 UserD 와의 연결 유지 패킷
struct D2_BODY
{
    char id[32];            // 회원 아이디

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

struct D2_PACKET
{
    REAL_HEADER hdr;        // packet_type: ID_D2_BODY
    // acode 사용 안함.

    D2_BODY body;
};

// AnchorD Control 패킷

struct C1_BODY
{
    short spot_type;                     // 버젼 타입
    short anchor_num;          // 앵커 데몬 넘버
    int date;              // 날짜
    int time;              // 시간
    short how_ctrl_num;          // 0  실시간 공지    ( ID_CTRL_NOTICE    )
                 // 1  마스터 재수신  ( ID_CTRL_MASTER    )
                 // 2  개별 메세지    ( ID_CTRL_ETC_MSG   )
                 // 3  개별 IP재설정( ID_CTRL_IP_RESET  )
                 // 4  핵투실시간쪽지( ID_CTRL_NOTE  )
                 //    운영IP:ac203.softbridge.co.kr(P:14052)
                 //    개발IP:ac20T.softbridge.co.kr(P:14052)
                 // 9  강제 접속 종료( ID_CTRL_FQUIT     )
                 // 10 개별 강제 종료 ( ID_CTRL_ETC_FQUIT )
    short site;
    char message[1024];

    unsigned char filler2;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;};

struct C1_PACKET
{
    REAL_HEADER hdr;        // packet_type: ID_C1_PACKET
    // acode 사용 안함.
    C1_BODY body;
};

// AnchorD 장구분 패킷

struct C2_BODY
{
    short spot_type;                     // 버젼 타입
    short anchor_num;          // 앵커 데몬 넘버
    int date;              // 날짜
    int time;              // 시간

    char message[32];                    // 장전
                                         // 장전 동시호가
                                         // 정규장 시작
                                         // 현물 장마감 동시
                                         // 현물 장 종료
                                         // 현물 시간외 종료
                                         // 선옵 장마감 동시
                                         // 선옵 장 종료
                                         // 현물 시간외 시작
                                         // 현물 시간외 종료

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;};

struct C2_PACKET
{
    REAL_HEADER hdr;        // packet_type: ID_C2_PACKET
    // acode 사용 안함.
    C2_BODY body;
};


//--------------------------------------------------------------------------
// 핵투 핵심주 리스트 디비 추가하기
//--------------------------------------------------------------------------
struct HT_C1_DATA
{
    int acode;              // anchor code
    char comment[MAX_TODAY_COMMENT_NUM];     // 종목설명
};
struct HT_C1_BODY
{
    int date;               // 일자
    int count;              // 등록갯수

    HT_C1_DATA* data;       // count 갯수

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
    char server[16];       // 디비서버 IP
    int err_no;             // 작업결과 에러코드(0:성공, -1:실패)
};
struct HT_C1_BODY_REP
{
    int count;              // 디비 추가작업한 서버 갯수

    HT_C1_DATA_REP* data;   // count 갯수

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
// 핵투 핵심주 특정일자 리스트 데이터 요청
//--------------------------------------------------------------------------
struct HT_C2_BODY
{
    int date;               // 일자

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
    char comment[MAX_TODAY_COMMENT_NUM];     // 종목설명
};
struct HT_C2_BODY_REP
{
    int date;               // 일자
    int count;              // 핵심주 종목 갯수

    HT_C2_DATA_REP* data;   // count 갯수

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
// 리얼 등록/삭제 TR
//--------------------------------------------------------------------------
// 시세 등록/삭제 패킷
struct A1_DATA
{
    int acode;           // anchor code
    int detail_type;     // 0: 호가 + 체결, 1: 체결
};

struct A1_BODY
{
    int count;           // 등록갯수

    A1_DATA* data;       // count 갯수

    unsigned char rq_tag;        // [요청 구분] 1: 등록, 2: 삭제

    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

struct A1_PACKET
{
    REAL_HEADER hdr;     // packet_type: ID_A1_PACKET
    // acode 사용 안함.
    A1_BODY body;
};

//--------------------------------------------------------------------------
// 리얼 로그 TR
//--------------------------------------------------------------------------
struct A2_BODY
{
    char log_id[16];       // 로그ID(클라이언트에서 올리는 파일명)
    char id[32];          // 사용자 ID
    char message[256];       // 내용

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
// 리얼 지수 TR
//--------------------------------------------------------------------------
// 지수 시세 패킷
struct J1_BODY
{
    int date;               // 날짜  YYYYMMDD
    int time;               // 시간  HHMMSS

    short jang;             // [장구분] 0: 장 전 동시호가, 3: 장중,
    // 5: 시간외 종가(KOSPI200 장종료:1100000만 존재 9: 장종료
    // KOSDAQ50 장종료:1100000만 존재, 9: 장종료)

    char daebi_tag;         // [등락 구분] '0':거래무, '1':상한, '2':상승,
                            // '3':보합, '4':하한, '5':하락
    unsigned char filler1;

    int cur_price;          // 현재가
    int open_price;         // 시가
    int high_price;         // 고가
    int low_price;          // 저가
    int volume;             // 거래량. 단위: 천주
    int cash;               // 거래 대금 (단위:백만원)
    int daebi;              // 대비값을 보낸다. 현제가 ? master(전일종가)
    int daebi_rate;         // 등락율
    int time_vol;           // 순간 체결량
    int seq_no;             // 틱번호

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
// 리얼 주식 TR
//--------------------------------------------------------------------------
// 주식 시세 패킷
struct STOCK_HOGA
{
    int sell_price;         // 매도호가
    int buy_price;          // 매수호가
    int sell_vol;           // 매도호가 잔량
    int buy_vol;            // 매수호가 잔량
};

struct S1_BODY
{
    STOCK_HOGA hoga[STOCK_HOGA_NUM];    // 10단계 호가

    int date;               // 날짜 YYYYMMDD
    int time;               // 시간  :HHMMSS

    short jang;             // [장구분] 0: 장 시작 전, 10: 장전 시간외,
                            // 20: 장전 동시호가, 30: 장중, 40: 장후 동시호가,
                            // 50: 장후 시간외, 99: 장종료
    char vi_apply_code;     // VI적용구분코드    1:VI발동, 2:VI해제
    char vi_code;           // VI종류코드        1:정적VI, 2:동적VI, 3:정적&동적VI

    char daebi_tag;         // [등락 구분] '0':거래무, '1':상한, '2':상승,
                            // '3':보합, '4':하한, '5':하락
    char gise_tag;          // [기세 구분] '1':기세상한
    // '2':기세상승, '3':기세하한, '4':기세하락
    unsigned char ctrl_tag;         // [거래 구분] 0:정상, 1:정지, 2:중단
    char vol_tag;           // 잔량 구분

    int cur_price;          // 현재가
    int open_price;         // 시가
    int high_price;         // 고가
    int low_price;          // 저가
    int volume;             // 누적 거래량
    int cash;               // 누적 거래 대금 (단위:천원)
    int daebi;              // 전대비:현재가 - master(전일종가)
    int daebi_rate;         // 등락율

    int exp_buy_price;      // 예상체결가     단위:원
    int exp_buy_vol;        // 예상체결수량   단위:주
    int timeout_sell_vol;   // 시간외총매도잔량   단위:주
    int timeout_buy_vol;    // 시간외총매수잔량   단위:주
    int tot10_sell_vol;     // 10단계 총매도호가잔량
    int tot10_buy_vol;      // 10단계 총매수호가잔량

    int jangprv_tot_buy_vol; // 장개시전 시간외 총 매도 잔량
    int jangprv_tot_sell_vol;// 장개시전 시간외 총 매수 잔량

    int weight_avg_price;   // 가중평균가, 시간외 대량매매시:장마감시 수신
    int buy_price;          // 체결가

    char max_price_tag;     // 상한가 변경 여부
    char min_price_tag;     // 상한가 변경 여부
    char vol_gubun;         // 잔량 구분. filler 가 대체
    char chegyul_gubun;     // 매수체결: 1, 매도체결: 2
    int seq_no;             // 호가 시퀀스 넘버
    int time_vol;           // 순간 체결량

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
//                       S3 호가 패킷                                    //
///////////////////////////////////////////////////////////////////////////

struct S3_BODY
{
    STOCK_HOGA hoga[10];    // 10단계 호가

    int time;               // 시간  :HHMMSS

    short jang;             // [장구분] 0: 장 시작 전, 10: 장전 시간외,
                            // 20: 장전 동시호가, 30: 장중, 40: 장후 동시호가,
                            // 50: 장후 시간외, 99: 장종료
    char daebi_tag;         // [등락 구분] '0':거래무, '1':상한, '2':상승,
                            // '3':보합, '4':하한, '5':하락
    char filler1;           // 보정필드
    int daebi;
    int daebi_rate;         // 등락율

    int exp_buy_price;      // 예상체결가     단위:원
    int exp_buy_vol;        // 예상체결수량   단위:주
    int timeout_sell_vol;   // 시간외총매도잔량   단위:주
    int timeout_buy_vol;    // 시간외총매수잔량   단위:주
    int tot10_sell_vol;     // 10단계 총매도호가잔량
    int tot10_buy_vol;      // 10단계 총매수호가잔량

    int jangprv_tot_buy_vol; // 장개시전 시간외 총 매도 잔량
    int jangprv_tot_sell_vol;// 장개시전 시간외 총 매수 잔량

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
// 리얼 선물 TR
//--------------------------------------------------------------------------
// 선물 시세 Small 패킷    -- 서버에서 받는 패킷
struct FO_HOGA
{
    int sell_price;        // 매도호가
    int buy_price;         // 매수호가
    int sell_vol;          // 매도호가 잔량
    int buy_vol;           // 매수호가 잔량
    int sell_quantity;     // 매도호가 잔량
    int buy_quantity;      // 매수호가 잔량
};

struct F2_BODY
{
    FO_HOGA hoga[FUTURE_HOGA_NUM]; // FUTURE_HOGA_NUM = 5

    int date;                // 날짜
    int time;                // 시간   형식:HHMMSS

    short jang;              // [장구분]
                             // 1: 장전 동시호가 3: 장중 5:시간외 종가
                             // KOSPI200 장종료:1100000만 존재 9: 장종료
                             // KOSDAQ50 장종료:1100000만 존재 9: 장종료

    char daebi_tag;          // 등락 구분
                             // '0':거래무, '1':상한, '2':상승
                             // '3':보합, '4':하한, '5':하락

    char gise_tag;           // [기세 구분] 0:정상, 1:기세
    unsigned char ctrl_tag;          // [거래 구분] 0:정상, 1:전종목중단
                             // 11:전종목중단,  전종목 주식C,b중단,
                             // 3:개별종목 중단, 5:개별종목 C,B 중단
    unsigned char filler1[3];

    int cb_time;             // 시간, C,B 중단시 유효
    int cur_price;           // 현재가
    int open_price;          // 시가
    int high_price;          // 고가
    int low_price;           // 저가
    int volume;              // 누적 거래량
    int cash1;               // 누적 거래대금1 단위: 백만원
    int cash2;               // 누적 거래대금2 단위: 천원
    int daebi;               // 전대비:현재가 - master(전일종가)
    int daebi_rate;          // 등락률

    int tot_sell_vol;        // 매도호가 총 수량
    int tot_buy_vol;         // 매수호가 총 수량
    int tot_sell_quantity;   // 매도호가 총 건수
    int tot_buy_quantity;    // 매수호가 총 수량
    int not_deal_vol;        // 미결재 약정 수량 1 당일 확정
    int tick_no;               // 틱번호

    int kospi200;            // kospi200 value
    int cd_rate;             // cd금리

    int remain_sec;          // 캘린더잔존초
    int real_remain_sec;     // 실잔존초 : 마스터의 결재일을 초형태로 변환. 신규

    int seq_no;              // 호가 시퀀스 넘버

    char chegyul_gubun;      // 매수체결: 1, 매도체결: 2
    unsigned char filler2[3];
    int time_vol;           // 순간 체결량

    int large_volume;       // 협의대량체결수량                           2014-09-01
    int real_max_price;     // 실시간상한가           SIGN 부호           2014-09-01
    int real_min_price;     // 실시간하한가           SIGN 부호           2014-09-01
    char real_limit_gb[1];  // 실시간가격제한여부     실시간 상하한가 반영 여부 (Y/N)     2014-09-01
    char filler4[3];        // 패킷 사이즈 보정용

    int max_step;           // 상한가단계                                   2015-06-15
    int min_step;           // 하한가단계                                   2015-06-15
    int max_price;          // 상한가                                       2015-06-15
    int min_price;          // 하한가                                       2015-06-15

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

// 선물 시세 패킷     -- 프로그램에서 사용하는 패킷 구조
struct F1_BODY
{
    FO_HOGA hoga[FUTURE_HOGA_NUM]; // FUTURE_HOGA_NUM = 5

    int date;                // 날짜
    int time;                // 시간   형식:HHMMSS

    short jang;              // [장구분]
                             // 1: 장전 동시호가 3: 장중 5:시간외 종가
                             // KOSPI200 장종료:1100000만 존재 9: 장종료
                             // KOSDAQ50 장종료:1100000만 존재 9: 장종료

    char daebi_tag;          // 등락 구분
                             // '0':거래무, '1':상한, '2':상승
                             // '3':보합, '4':하한, '5':하락

    char gise_tag;           // [기세 구분] 0:정상, 1:기세
    unsigned char ctrl_tag;          // [거래 구분] 0:정상, 1:전종목중단
                             // 11:전종목중단,  전종목 주식C,b중단,
                             // 3:개별종목 중단, 5:개별종목 C,B 중단
    unsigned char filler1[3];

    int cb_time;             // 시간, C,B 중단시 유효
    int cur_price;           // 현재가
    int open_price;          // 시가
    int high_price;          // 고가
    int low_price;           // 저가
    int volume;              // 누적 거래량
    int cash1;               // 누적 거래대금1 단위: 백만원
    int cash2;               // 누적 거래대금2 단위: 천원
    int daebi;               // 전대비:현재가 - master(전일종가)
    int daebi_rate;          // 등락률

    int tot_sell_vol;        // 매도호가 총 수량
    int tot_buy_vol;         // 매수호가 총 수량
    int tot_sell_quantity;   // 매도호가 총 건수
    int tot_buy_quantity;    // 매수호가 총 수량

    int not_deal_vol;        // 미결재 약정 수량 1 당일 확정
    int tick_no;             // 틱번호

    int kospi200;            // kospi200 value
    int cd_rate;             // cd금리

    int remain_sec;          // 캘린더잔존초
    int real_remain_sec;     // 실잔존초 : 마스터의 결재일을 초형태로 변환. 신규

    int seq_no;              // 호가 시퀀스 넘버

    // 이하는 계산해서 값을 구함
    int cur_price_near;    // 근월물 의제 약정 가격
    int cur_price_far;     // 원월물 의제 약정 가격
    int volume_near;       // 근월물 누적 거래량
    int volume_far;        // 원월물 누적 거래량
    int cash1_near;        // 근월물 누적 거래대금1 단위: 백만원
    int cash2_near;        // 근월물 누적 거래대금2 단위: 천원
    int cash1_far;         // 원월물 누적 거래대금1 단위: 백만원
    int cash2_far;         // 원월물 누적 거래대금2 단위: 천원

    int fair_price;        // 이론가
    int disparate_ratio;   // 괴리율
    int fair_basis;        // 이론 베이시스
    int market_basis;      // 시장 베이시스
    int fair_spread;       // 이론 스프레드
    int market_spread;     // 시장 스프레드

    // 서버에서 받은 값
    char chegyul_gubun;    // 매수체결: 1, 매도체결: 2
    unsigned char filler2[3];
    int time_vol;           // 순간 체결량

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
//                       F3 호가 패킷                                    //
///////////////////////////////////////////////////////////////////////////

struct SMALL_F_HOGA
{
    unsigned short sell_price;        // 매도호가
    unsigned short buy_price;         // 매수호가
    unsigned short sell_vol;          // 매도호가 잔량
    unsigned short buy_vol;           // 매수호가 잔량
    unsigned short sell_quantity;     // 매도호가 잔량
    unsigned short buy_quantity;      // 매수호가 잔량
};

struct F3_BODY
{
    SMALL_F_HOGA hoga[FUTURE_HOGA_NUM]; // FUTURE_HOGA_NUM = 5

    int time;                // 시간   형식:HHMMSS

    short jang;              // [장구분]
                             // 1: 장전 동시호가 3: 장중 5:시간외 종가
                             // KOSPI200 장종료:1100000만 존재 9: 장종료
                             // KOSDAQ50 장종료:1100000만 존재 9: 장종료
    short filler1;

    int tot_sell_vol;        // 매도호가 총 수량
    int tot_buy_vol;         // 매수호가 총 수량
    int tot_sell_quantity;   // 매도호가 총 건수
    int tot_buy_quantity;    // 매수호가 총 수량

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
// 옵션 선물 TR
//--------------------------------------------------------------------------
// 옵션 시세 SMALL 패킷  -- 서버에서 받는 패킷
struct O2_BODY
{
    FO_HOGA hoga[OPTION_HOGA_NUM];  // OPTION_HOGA_NUM = 5

    int date;                // 날짜     형식 : YYYYMMDD
    int time;                // 시간     형식 : HHMMSS

    short jang;              // 장구분,
                             // 1: 장전 동시호가 3: 장중 5:시간외 종가
                             // KOSPI200 장종료:1100000만 존재 9: 장종료
                             // KOSDAQ50 장종료:1100000만 존재 9: 장종료

    char daebi_tag;          // 등락 구분
                             // '0':거래무, '1':상한, '2':상승
                             // '3':보합, '4':하한, '5':하락

    char gise_tag;           // 기세 구분      0:정상, 1:기세
    unsigned char ctrl_tag;          // 거래 구분   0:정상, 1:전종목중단
                             // 11:전종목중단,  전종목 주식C,b중단,
                             // 3:개별종목 중단, 5:개별종목 C,B 중단
    unsigned char filler1[3];

    int cb_time;             // 시간           C,B 중단시 유효
    int cur_price;           // 현재가
    int open_price;          // 시가
    int high_price;          // 고가
    int low_price;           // 저가
    int volume;              // 누적 거래량
    int cash1;               // 누적 거래대금1 단위: 백만원
    int cash2;               // 누적 거래대금2 단위: 천원
    int daebi;               // 전대비 : 현재가 - master(전일종가)
    int daebi_rate;          // 등락률

    int tot_sell_vol;        // 매도호가 총 수량
    int tot_buy_vol;         // 매수호가 총 수량
    int tot_sell_quantity;   // 매도호가 총 건수
    int tot_buy_quantity;    // 매수호가 총 수량
    int not_deal_vol1;       // 미결재 약정 수량 1 당일 확정
    int not_deal_vol2;       // 미결재 약정 수량 2 당일 확정
    int tick_no;             // 틱번호

    int kospi200;            // kospi200

    int real_remain_sec;     // 실잔존초
    int remain_sec;          // 캘린더잔존초

    int future_cur_price;    // 선물 현재가
    int seq_no;              // 호가 시퀀스 넘버

    char chegyul_gubun;      // 매수체결: 1, 매도체결: 2
    unsigned char filler2[3];
    int time_vol;           // 순간 체결량

    int large_volume;       // 협의대량체결수량                           2014-09-01
    int real_max_price;     // 실시간상한가           SIGN 부호           2014-09-01
    int real_min_price;     // 실시간하한가           SIGN 부호           2014-09-01
    char real_limit_gb[1];  // 실시간가격제한여부     실시간 상하한가 반영 여부 (Y/N)     2014-09-01
    char filler4[3];        // 패킷 사이즈 보정용

    int max_step;           // 상한가단계                                   2015-06-15
    int min_step;           // 하한가단계                                   2015-06-15
    int max_price;          // 상한가                                       2015-06-15
    int min_price;          // 하한가                                       2015-06-15

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

// 옵션 시세 패킷        -- 프로그램에서 사용하는 패킷 구조
struct O1_BODY
{
    FO_HOGA hoga[OPTION_HOGA_NUM];  // OPTION_HOGA_NUM = 5

    int date;                // 날짜     형식 : YYYYMMDD
    int time;                // 시간     형식 : HHMMSS

    short jang;              // 장구분,
                             // 1: 장전 동시호가 3: 장중 5:시간외 종가
                             // KOSPI200 장종료:1100000만 존재 9: 장종료
                             // KOSDAQ50 장종료:1100000만 존재 9: 장종료

    char daebi_tag;          // 등락 구분
                             // '0':거래무, '1':상한, '2':상승
                             // '3':보합, '4':하한, '5':하락

    char gise_tag;           // 기세 구분      0:정상, 1:기세
    unsigned char ctrl_tag;          // 거래 구분   0:정상, 1:전종목중단
                             // 11:전종목중단,  전종목 주식C,b중단,
                             // 3:개별종목 중단, 5:개별종목 C,B 중단
    unsigned char filler1[3];

    int cb_time;             // 시간           C,B 중단시 유효
    int cur_price;           // 현재가
    int open_price;          // 시가
    int high_price;          // 고가
    int low_price;           // 저가
    int volume;              // 누적 거래량
    int cash1;               // 누적 거래대금1 단위: 백만원
    int cash2;               // 누적 거래대금2 단위: 천원
    int daebi;               // 전대비 : 현재가 - master(전일종가)
    int daebi_rate;          // 등락률

    int tot_sell_vol;        // 매도호가 총 수량
    int tot_buy_vol;         // 매수호가 총 수량
    int tot_sell_quantity;   // 매도호가 총 건수
    int tot_buy_quantity;    // 매수호가 총 수량
    int not_deal_vol1;       // 미결재 약정 수량 1 당일 확정
    int not_deal_vol2;       // 미결재 약정 수량 2 당일 확정
    int tick_no;             // 틱번호

    int kospi200;            // kospi200

    int real_remain_sec;     // 실잔존초
    int remain_sec;          // 캘린더잔존초

    int future_cur_price;    // 선물 현재가
    int seq_no;              // 호가 시퀀스 넘버

    // 이하는 계산해서 값을 구함
    int fair_price;         // 이론가
    int disparate_ratio;    // 괴리율
    int hist_volatility;    // 역사적 변동성 (Historical Volatility)
    int impl_volatility;    // 내재 변동성 (Implied Volatility)

    int delta;              // 델타
    int gamma;              // 감마
    int theta;              // 쎄타
    int vega;               // 베가
    int rho;                // 로

    // 서버에서 받은 값
    char chegyul_gubun;     // 매도체결: 1, 매수체결: 2
    unsigned char filler2[3];
    int time_vol;           // 순간 체결량

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
//                       O3 호가 패킷                                    //
///////////////////////////////////////////////////////////////////////////

struct SMALL_O_HOGA
{
    unsigned short sell_price;        // 매도호가
    unsigned short buy_price;         // 매수호가
    int sell_vol;          // 매도호가 잔량
    int buy_vol;           // 매수호가 잔량
    unsigned short sell_quantity;     // 매도호가 잔량
    unsigned short buy_quantity;      // 매수호가 잔량
};

struct O3_BODY
{
    SMALL_O_HOGA hoga[OPTION_HOGA_NUM];  // OPTION_HOGA_NUM = 5

    int time;                // 시간     형식 : HHMMSS

    short jang;              // 장구분,
                             // 1: 장전 동시호가 3: 장중 5:시간외 종가
                             // KOSPI200 장종료:1100000만 존재 9: 장종료
                             // KOSDAQ50 장종료:1100000만 존재 9: 장종료
    short filler1;

    int tot_sell_vol;        // 매도호가 총 수량
    int tot_buy_vol;         // 매수호가 총 수량
    int tot_sell_quantity;   // 매도호가 총 건수
    int tot_buy_quantity;    // 매수호가 총 건수

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

// 투자자 시세 패킷
struct T1_BODY
{
    INVEST_HOGA hoga[INVEST_HOGA_NUM];         // 투자자 구분에 다른 100 ~ 10000 까지 12개
                                               // 0 개인
                                               // 1 외국인
                                               // 2 기관계
                                               // 3 증권회사
                                               // 4 보험회사
                                               // 5 투자신탁회사
                                               // 6 은행
                                               // 7 종금
                                               // 8 기금
                                               // 9 기타
    int date;                                  // 생성일자
    int time;                                  // 데이터 시간

    int code;                                  // 옵션 투자자 코드
    int code_no;                               // 000001 부터
    char data_gb[4];                           // 데이타 구분 : ’01’:전일확정치
                                               //    ’02’:당일확정치->’03’:당일확정치

    int crt_time;                              // 생성 시작
    short trade_gb;                            // 투자 구분
    unsigned char filler1[2];

    int future_jisu_price;                     // 최근 월물 선물 지수 종가
    int daebi_price;                           // 최근 월물 선물 전일비

    unsigned char filler2;
    unsigned char ff;                                  // FF     '0xff'
    unsigned char cr;                                  // CR     '0x0d'
    unsigned char lf;                                  // LF     '0x0a‘
};

struct T1_PACKET
{
    REAL_HEADER hdr; // packet_type: ID_T1_PACKET

    T1_BODY body;
};

// P/C Ratio 시세 패킷

struct PC1_BODY
{
    int date;                     // 날짜
    int time;                      // 시간

    int put_vol;                  // PUT 전체 거래량
    int put_cash;                 // PUT 전체 거래대금
    int put_notdeal;              // PUT 전체 미결제약정
    int call_vol;                 // CALL 전체 거래량
    int call_cash;                // CALL 전체 거래대금
    int call_notdeal;             // CALL 전체 미결제약정

    int option_put_rep_iv;        // PUT 옵션 대표 내재 변동성
    int option_call_rep_iv;       // CALL 옵션 대표 내재 변동성
    int option_put_atm_iv;        // PUT 옵션 등가격 내재 변동성
    int option_call_atm_iv;       // CALL 옵션 등가격 내재 변동성

    int tick_no;                  // 틱번호

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

// 포지션분석 시세 패킷                // 프로그램에서 사용하는 패킷
struct P1_HOGA
{
    int buy_avg_price;                // 매수평균가
    int buy_vol;                   // 매수 수량
    int sell_avg_price;               // 매도 평균가
    int sell_vol;                  // 매도 수량
};

struct P1_BODY
{
    P1_HOGA hoga[INVEST_HOGA_NUM];    // INVEST_HOGA_NUM = 12

    int date;                         // 날짜
    int time;                         // 시간

    int info_acode;                   // 포지션 코드

    int tick_no;                      // 틱번호

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

// 해외 시세 패킷
struct U1_BODY
{
    int date;                // 날짜     형식 : YYYYMMDD
    int time;                // 시간     형식 : HHMMSS

    char daebi_tag;          // 등락 구분
                             // '0':거래무, '1':상한, '2':상승
                             // '3':보합, '4':하한, '5':하락
    unsigned char filler1[3];

    int cur_price;           // 현재가
    int open_price;          // 시가
    int high_price;          // 고가
    int low_price;           // 저가
    int volume;              // 거래량. 단위: 천주
    int daebi;               // 대비값을 보낸다. 현재가 - master(전일종가)
    int daebi_rate;          // 등락율
    int seq_no;
    int time_vol;             // 직전거래량 대비

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

// 뉴스 실시간 패킷
struct N1_BODY
{
    int date;                // 날짜     형식 : YYYYMMDD
    int time;                // 시간     형식 : HHMMSS

    char db_num[20];

    short info_code;         //  송신사 구분
                             // 00:공시, 01:edaily, 02:joins, 03:프라임경제,
                             // 04:파이낸셜뉴스, 05:etoday,
                             // 06:한국경제,  07:Financial Point
                             // 08:머니투데이,  09:연합뉴스, 10:뉴스핌

    short class_code;        // 뉴스 종류
                             // 1:증권, 2:경제, 4:정보통신,
                             // 8:산업, 16:해외경제, 128:기타

    char title[136];         // 뉴스 제목
    int reserved;
    char market_tag;         // 시장구분 '1':거래소, '2':코스닥, '3':선물, '4':채권

    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

struct N1_PACKET
{
    REAL_HEADER hdr; // packet_type: ID_N1_PACKET

    N1_BODY body;
};

// 테마 실시간 패킷              // 프로그램에서 사용하는 패킷
struct ST2_BODY
{
    char theme_code[4];                 // 테마코드
    char theme_name[64];                // 테마명
    int date;                           // 날짜
    int time;                           // 시간
    int tot_count;        // 테마 종속 종목수
    int upcount;                        // 상승 종목수
    int highcount;        // 상한 종목수
    int downcount;                      // 하락 종목수
    int lowcount;            // 하한 종목수
    int avg_rate;                       // 평균 등락율

};

struct ST2_PACKET
{
    REAL_HEADER hdr;     // packet_type: ID_ST2_PACKET
    ST2_BODY body[10];
};

// 거래원 실시간 패킷              // 프로그램에서 사용하는 패킷
struct R1_HOGA
{
    short sell_no;                    // 매도 거래원번호
    short buy_no;                     // 매수 거래원번호
    int tot_sell_vol;                 // 매도 수량
    int tot_buy_vol;                  // 매수 수량
};

struct R1_BODY
{
    R1_HOGA hoga[5];                  //

    int date;                         // 날짜
    int time;                         // 시간

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

// 전체업종 실시간 패킷              // 프로그램에서 사용하는 패킷
struct UP1_BODY
{
    int acode;                  // anchor code
    int date;                   // 날짜
    int time;                   // 시간
    int cur_price;              // 현제가
    int open_price;             // 시가
    int high_price;             // 고가
    int low_price;              // 저가
    int volume;                 // 누적 거래량
    int daebi;                  // 전일대비
    int daebi_rate;             // 등락율
    char daebi_tag;             // 등락 구분
    char filler[3];
};

struct UP1_PACKET
{
    REAL_HEADER hdr;     // packet_type: ID_UP1_PACKET
    UP1_BODY  body[10];
};

// 주식 실시간 마스터
struct SM_PACKET
{
    REAL_HEADER hdr;     // packet_type: ID_SM_PACKET

    MASTER_STOCK_PACKET body;
};

//--------------------------------------------------------------------------
// Query 분봉, 일봉 TR
//--------------------------------------------------------------------------
// 분봉, 일봉 요청 패킷
struct B1_BODY_REQ
{
    int acode;              // anchor code
    int count;              // 데이터 요청 갯수. 우선순
    int s_date;             // 시작일     YYYYMMDD
    int e_date;             // 종료일     YYYYMMDD

    short time_unit;        // 1, 5, 10, 20, 40, 60 등등
    short term;             // 0: 일, 1: 주, 2: 월, 3: 분,
                            // 4: 초, 5: 틱, 6: 일중

    char sujung;            // ‘0’: 수정주가미처리
                            // ‘1’: 수정주가처리
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

// 분봉, 일봉 응답 헤더
struct B1_HEADER_REP
{
    QUERY_HEADER hdr;

    int acode;               // anchor code

    short time_unit;         // 1, 5, 10, 20, 40, 60 등등
    short term;              // 0: 일, 1: 주, 2: 월, 3: 분,
                             // 4: 초, 5: 틱, 6: 일중

    int cur_price;           // 현재가
    int daebi;               // 대비
    int daebi_rate;          // 등락율
    int count;               // 데이터 갯수

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

// 분봉, 일봉 응답 패킷
struct B1_DATA_REP
{
    int acode;               // Anchor code
    int date;                // 날짜
    int time;                // 시간   형식:HHMM00

    int cur_price;           // 현재가
    int open_price;          // 시가
    int high_price;          // 고가
    int low_price;           // 저가
    int volume;              // 거래량
    int seq_no;              // n틱용 시퀀스 넘버
    int time_vol;               // 순간 체결량
};

struct B1_PACKET_REP
{
    B1_HEADER_REP hdr;          // packet_type: ID_B1_PACKET_REP

    B1_DATA_REP* body;          // Header 의 count 갯수

    QUERY_FOOTER footer;        // packet_type: ID_B1_PACKET_REP
};
//--------------------------------------------------------------------------
// Query 체결데이터 TR
//--------------------------------------------------------------------------
// 체결데이터 요청 패킷
struct B2_BODY_REQ
{
    int acode;              // Anchor code
    int count;              // 데이터 요청 갯수. 우선순

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

// 체결데이터 응답 헤더
struct B2_HEADER_REP
{
    QUERY_HEADER hdr;

    int acode;               // anchor code
    int cur_price;           // 현재가
    int daebi;               // 대비
    int daebi_rate;          // 등락율

    int count;               // 데이터갯수

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

// 체결데이터 응답 패킷
struct B2_DATA_REP
{
    int date;                // 날짜
    int time;                // 시간   형식:HHMM00
    int cur_price;           // 현재가
    int volume;              // 누적 거래량
    int value;               // 선/옵인 경우는 미결제약정, 주식 0
    int tick_no;             // 틱 카운트
    char buy_flag;           // ‘0’: 보합, ‘1’: 매수체결
    unsigned char filler[3];
    int time_vol;
};

struct B2_PACKET_REP
{
    B2_HEADER_REP hdr;       // packet_type: ID_B2_PACKET_REP

    B2_DATA_REP* body;       // Header 의 count 갯수

    QUERY_FOOTER footer;    // packet_type: ID_B2_PACKET_REP
};

// 투자자 분봉, 일봉 요청 패킷
struct B3_BODY_REQ
{
    int acode;               // anchor code
    int count;               // 데이터 요청 갯수. 우선순
    int s_date;              // 시작일   YYYYMMDD
    int e_date;              // 종료일   YYYYMMDD

    short time_unit;         // 1, 5, 10, 20, 40, 60 등등
    short term;              // 0: 일, 1: 주, 2: 월, 3: 분,
                             // 4: 초, 5: 틱, 6: 일중

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

// 투자자 분봉, 일봉 응답 헤더
struct B3_HEADER_REP
{
    QUERY_HEADER hdr;

    int acode;               // anchor code

    short time_unit;         // 1, 5, 10, 20, 40, 60 등등
    short term;              // 0: 일, 1: 주, 2: 월, 3: 분,
                             // 4: 초, 5: 틱, 6: 일중

    int count;               // 데이터 갯수

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

// 투자자 분봉, 일봉 응답 패킷
struct B3_DATA_REP
{
    int acode;                  // Anchor code
    int date;                   // 날짜
    int time;                   // 시간   형식:HHMM00

    int future_jisu_price;      // 최근 월물 선물 지수 종가
    int daebi_price;            // 전일비

    INVEST_HOGA hoga[INVEST_HOGA_NUM]; // INVEST_HOGA_NUM = 12
};

struct B3_PACKET_REP
{
    B3_HEADER_REP hdr;          // packet_type: ID_B3_PACKET_REP

    B3_DATA_REP* body;          // Header 의 count 갯수

    QUERY_FOOTER footer;       // packet_type: ID_B3_PACKET_REP
};

// PC ratio 분봉, 일봉 요청 패킷
struct B4_BODY_REQ
{
    int acode;               // anchor code
    int count;               // 데이터 요청 갯수. 우선순
    int s_date;              // 시작일   YYYYMMDD
    int e_date;              // 종료일   YYYYMMDD
     
    short time_unit;         // 1, 5, 10, 20, 40, 60 등등
    short term;              // 0: 일, 1: 주, 2: 월, 3: 분,
                             // 4: 초, 5: 틱, 6: 일중

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

// PC ratio분봉, 일봉 응답 헤더
struct B4_HEADER_REP
{
    QUERY_HEADER hdr;

    int acode;               // anchor code

    short time_unit;         // 1, 5, 10, 20, 40, 60 등등
    short term;              // 0: 일, 1: 주, 2: 월, 3: 분,
                             // 4: 초, 5: 틱, 6: 일중

    int count;               // 데이터 갯수

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

// PC ratio 분봉, 일봉 응답 패킷
struct B4_DATA_REP
{
    int acode;                          // anchor code
    int date;                           // 날짜
    int time;                           // 시간

    int put_vol;                        // PUT 전체 거래량 (단위 1주)
    int put_cash;                       // PUT 전체 거래대금 (단위 백만원)
    int put_notdeal;                    // PUT 전체 미결재약정 (단위 1주)
    int call_vol;                       // CALL 전체 거래량 (단위 1주)
    int call_cash;                      // CALL 전체 거래대금  (단위 백만원)
    int call_notdeal;                   // CALL 전체 미결재약정 (단위 1주)

    int option_put_rep_iv;              // PUT 옵션 대표 내재 변동성 (단위 0.0001)
    int option_call_rep_iv;             // CALL 옵션 대표 내재 변동성 (단위 0.0001)
    int option_put_atm_iv;              // PUT 옵션 등가격 내재 변동성 (단위 0.0001)
    int option_call_atm_iv;             // CALL 옵션 등가격 내재 변동성 (단위 0.0001)

    int tick_no;                        // 틱번호

    int reserved[7];                    // reserved1 ~ reserved7
};

struct B4_PACKET_REP
{
    B4_HEADER_REP hdr;          // packet_type: ID_B4_PACKET_REP

    B4_DATA_REP* body;          // Header 의 count 갯수

    QUERY_FOOTER footer;       // packet_type: ID_B4_PACKET_REP
};

// Position 분봉, 일봉 요청 패킷
struct B5_BODY_REQ
{
    int acode;               // anchor code
    int count;               // 데이터 요청 갯수. 우선순
    int s_date;              // 시작일   YYYYMMDD
    int e_date;              // 종료일   YYYYMMDD

    short time_unit;         // 1, 5, 10, 20, 40, 60 등등
    short term;              // 0: 일, 1: 주, 2: 월, 3: 분,
                             // 4: 초, 5: 틱, 6: 일중

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

// Position 분봉, 일봉 응답 헤더
struct B5_HEADER_REP
{
    QUERY_HEADER hdr;

    int acode;               // anchor code

    short time_unit;         // 1, 5, 10, 20, 40, 60 등등
    short term;              // 0: 일, 1: 주, 2: 월, 3: 분,
                             // 4: 초, 5: 틱, 6: 일중

    int count;               // 데이터 갯수

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

// Position 분봉, 일봉 응답 패킷
struct B5_DATA_REP
{
    int acode;                   // anchor code
    int date;                    // 날짜
    int time;                    // 시간

    int info_acode;              // 포지션코드

    P1_HOGA hoga[INVEST_HOGA_NUM];  // INVEST_HOGA_NUM = 12

    int tick_no;                 // 틱번호
};

struct B5_PACKET_REP
{
    B5_HEADER_REP hdr;          // packet_type: ID_B5_PACKET_REP

    B5_DATA_REP* body;          // Header 의 count 갯수

    QUERY_FOOTER footer;        // packet_type: ID_B5_PACKET_REP
};

// 시세 분봉, 일봉 요청 패킷
struct B6_BODY_REQ
{
    int acode;                  // anchor code(단일 종목 요청시)
    int date;                   // 요청날짜
    short market;               // 거래소=0x0001, 코스닥=0x0002, 지수=0x0004,
                                // 선물=0x0008, 옵션=0x0010, ELW = 0x0020,
                                // 해외=0x0040
    short rq_type;              // 0:전종목,
                                 // 1. 상한가 2. 하한가 3. 상한가 임박 4. 하한가 임박
                                // 5. 상한가 이탈 6. 하한가 이탈 7. (매도)잔량 남은 상한가
                                // 8. (매수)잔량 남은 하한가 9. 전일 상한가 10. 전일 하한가
                                // 11. 갭동반 상한가 12. 갭동반 상한가 13. 상승율 상위
                                // 14. 하락율 상위 15. 보합 16. 상승갭 상위 17. 하락갭 상위
                                // 18. 거래량 상위 19. 회전율상위 20. 거래대금 상위
                                // 21. 시가총액 상위 22. 전일대비 거래량상위 23. 전일거래량 돌파
                                // 24. 전일거래량 돌파 임박 25. 당일 고가 돌파 임박
                                // 26. 당일 시가 돌파 임박 27. 전일 고가 돌파 임박
                                // 28. 전일 종가 돌파 임박 29. 당일변동폭상위 30. 액면가미달
                                // 31. 52주 최고가 32. 52주 최저가 33. 52주 최고가 돌파 임박
                                // 34. 52주 최저가 돌파 임박 35. 연중최고가 36. 연중 최저가
                                // 37. 연중최고가 돌파 임박 38. 연중최저가 돌파 임박
                                // 39. 상장주식수 상위 40. 신규상장 종목 (상장 3개월 이내)
                                // 41. 관리종목 42. 투자위험/경고/주의 43. 거래중지
    int con_value;              // 조건율

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

// 시세 분봉, 일봉 응답 헤더
struct B6_HEADER_REP
{
    QUERY_HEADER hdr;

    int count;              // 데이터 갯수

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

// 시세 분봉, 일봉 응답 패킷
struct B6_DATA_REP
{
    int acode;                  // anchor code
    int date;                   // 날짜
    int time;                   // 시간

    int cur_price;              // 현제가
    int open_price;             // 시가
    int high_price;             // 고가
    int low_price;              // 저가
    int volume;                 // 누적 거래량
    int daebi;                  // 전일대비
    int daebi_rate;             // 등락율
    char daebi_tag;             // 등락 구분
    unsigned char filler1[3];
    int ch_rate;                // 변동율
    int ch_value;               // 변동폭
    int prv_volume;             // 전일거래량
    int buy_price;              // 매수호가
    int sell_price;             // 매도호가
    int buy_vol;                // 매수잔량
    int sell_vol;               // 매도잔량
    int buy_vol_rate;           // 1호가매수잔량/총매수잔량
    int sell_vol_rate;          // 1호가매도잔량/총매도잔량
    int tot_buy_vol;            // 총매수잔량
    int tot_sell_vol;           // 총매도잔량
    int tot_rate;               // 총매수/총매도
    int tot_buy_rate;           // 총매수/거래량
    int tot_trade_rate;         // 회전율
    int cash;                   // 거래대금
    int exp_vol;                // 예상체결량
    int volume_rate;            // 거래량대비
    int year_high_price;        // 연중최고가
    int year_low_price;         // 연중최저가
    int week_high_price_52;     // 52주최고가
    int week_low_price_52;      // 52주최저가
    int list_value;             // 시가총액
    int face_price;             // 액면가
};

struct B6_PACKET_REP
{
    B6_HEADER_REP hdr;          // packet_type: ID_B6_PACKET_REP

    B6_DATA_REP* body;          // Header 의 count 갯수

    QUERY_FOOTER footer;       // packet_type: ID_B6_PACKET_REP
};

// 선물이론가 분봉, 일봉 요청 패킷
struct B7_BODY_REQ
{
    int acode;               // anchor code
    int count;               // 데이터 요청 갯수. 우선순
    int s_date;              // 시작일   YYYYMMDD
    int e_date;              // 종료일   YYYYMMDD
     
    short time_unit;         // 1, 5, 10, 20, 40, 60 등등
    short term;              // 0: 일, 1: 주, 2: 월, 3: 분,
                             // 4: 초, 5: 틱, 6: 일중

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

// 선물이론가 분봉, 일봉 응답 헤더
struct B7_HEADER_REP
{
    QUERY_HEADER hdr;

    int acode;               // anchor code

    short time_unit;         // 1, 5, 10, 20, 40, 60 등등
    short term;              // 0: 일, 1: 주, 2: 월, 3: 분,
                             // 4: 초, 5: 틱, 6: 일중

    int count;               // 데이터 갯수

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

// 선물이론가 분봉, 일봉 응답 패킷
struct B7_DATA_REP
{
    int acode;                  // anchor code
    int date;                   // 날짜
    int time;                   // 시간
    int cur_price;              // 현제가
    int volume;                 // 누적거래량
    int kospi200;               // Kospi200
    int remain_sec;             // 캘린더잔존초
    int real_remain_sec;        // 실잔존초
    int cd_rate;                // cd금리
};

struct B7_PACKET_REP
{
    B7_HEADER_REP hdr;          // packet_type: ID_B7_PACKET_REP

    B7_DATA_REP* body;          // Header 의 count 갯수

    QUERY_FOOTER footer;       // packet_type: ID_B7_PACKET_REP
};

// 선옵 미결제약정 분봉, 일봉 요청 패킷
struct B8_BODY_REQ
{
    int acode;               // anchor code
    int count;               // 데이터 요청 갯수. 우선순
    int s_date;              // 시작일   YYYYMMDD
    int e_date;              // 종료일   YYYYMMDD

    short time_unit;         // 1, 5, 10, 20, 40, 60 등등
    short term;              // 0: 일, 1: 주, 2: 월, 3: 분,
                             // 4: 초, 5: 틱, 6: 일중

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

// 선옵 미결제약정 분봉, 일봉 응답 헤더
struct B8_HEADER_REP
{
    QUERY_HEADER hdr;

    int acode;               // anchor code

    short time_unit;         // 1, 5, 10, 20, 40, 60 등등
    short term;              // 0: 일, 1: 주, 2: 월, 3: 분,
                             // 4: 초, 5: 틱, 6: 일중

    int count;               // 데이터 갯수

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

// 선옵 미결제약정 분봉, 일봉 응답 패킷
struct B8_DATA_REP
{
    int acode;                  // anchor code
    int date;                   // 날짜
    int time;                   // 시간

    int cur_price;              // 현제가
    int volume;                 // 누적거래량
    int not_deal_vol;           // 미결재 약정수량
    int value;                  // 미결재 비교가격(선.옵 서로 다름)
};

struct B8_PACKET_REP
{
    B8_HEADER_REP hdr;          // packet_type: ID_B8_PACKET_REP

    B8_DATA_REP* body;          // Header 의 count 갯수

    QUERY_FOOTER footer;       // packet_type: ID_B8_PACKET_REP
};

// 베이시스 분봉, 일봉 요청 패킷
struct B9_BODY_REQ
{
    int acode;               // anchor code
    int count;               // 데이터 요청 갯수. 우선순
    int s_date;              // 시작일   YYYYMMDD
    int e_date;              // 종료일   YYYYMMDD

    short time_unit;         // 1, 5, 10, 20, 40, 60 등등
    short term;              // 0: 일, 1: 주, 2: 월, 3: 분,
                             // 4: 초, 5: 틱, 6: 일중

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

// 베이시스 분봉, 일봉 응답 헤더
struct B9_HEADER_REP
{
    QUERY_HEADER hdr;

    int acode;               // anchor code

    short time_unit;         // 1, 5, 10, 20, 40, 60 등등
    short term;              // 0: 일, 1: 주, 2: 월, 3: 분,
                             // 4: 초, 5: 틱, 6: 일중

    int count;               // 데이터 갯수

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

// 베이시스 분봉, 일봉 응답 패킷
struct B9_DATA_REP
{
    int acode;                  // anchor code
    int date;                   // 날짜
    int time;                   // 시간
    int cur_price;              // 현제가
    int volume;                 // 누적거래량
    int kospi200;               // Kospi200
    int fair_value;             // 이론가
};

struct B9_PACKET_REP
{
    B9_HEADER_REP hdr;          // packet_type: ID_B9_PACKET_REP

    B9_DATA_REP* body;          // Header 의 count 갯수

    QUERY_FOOTER footer;       // packet_type: ID_B9_PACKET_REP
};

// 옵션이론가 분봉, 일봉 요청 패킷
struct B10_BODY_REQ
{
    int acode;               // anchor code
    int count;               // 데이터 요청 갯수. 우선순
    int s_date;              // 시작일   YYYYMMDD
    int e_date;              // 종료일   YYYYMMDD

    short time_unit;         // 1, 5, 10, 20, 40, 60 등등
    short term;              // 0: 일, 1: 주, 2: 월, 3: 분,
                             // 4: 초, 5: 틱, 6: 일중

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

// 옵션이론가 분봉, 일봉 응답 헤더
struct B10_HEADER_REP
{
    QUERY_HEADER hdr;

    int acode;               // anchor code

    short time_unit;         // 1, 5, 10, 20, 40, 60 등등
    short term;              // 0: 일, 1: 주, 2: 월, 3: 분,
                             // 4: 초, 5: 틱, 6: 일중

    int count;               // 데이터 갯수

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

// 옵션이론가 분봉, 일봉 응답 패킷
struct B10_DATA_REP
{
    int acode;                  // anchor code
    int date;                   // 날짜
    int time;                   // 시간
    int cur_price;              // 현제가
    int kospi200;               // kospi200
    int future_cur_price;       // 선물 현제가
    int remain_sec;             // 캘런더잔존초
    int real_remain_sec;        // 실잔존초
    int cd_rate;                // cd금리
};

struct B10_PACKET_REP
{
    B10_HEADER_REP hdr;          // packet_type: ID_B10_PACKET_REP

    B10_DATA_REP* body;          // Header 의 count 갯수

    QUERY_FOOTER footer;       // packet_type: ID_B10_PACKET_REP
};

// 옵션 역사적변동 분봉, 일봉 요청 패킷
struct B11_BODY_REQ
{
    int acode;               // anchor code
    int count;               // 데이터 요청 갯수. 우선순
    int s_date;              // 시작일   YYYYMMDD
    int e_date;              // 종료일   YYYYMMDD

    short time_unit;         // 1, 5, 10, 20, 40, 60 등등
    short term;              // 0: 일, 1: 주, 2: 월, 3: 분,
                             // 4: 초, 5: 틱, 6: 일중

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

// 옵션 역사적변동 분봉, 일봉 응답 헤더
struct B11_HEADER_REP
{
    QUERY_HEADER hdr;

    int acode;               // anchor code

    short time_unit;         // 1, 5, 10, 20, 40, 60 등등
    short term;              // 0: 일, 1: 주, 2: 월, 3: 분,
                             // 4: 초, 5: 틱, 6: 일중

    int count;               // 데이터 갯수

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

// 옵션 역사적변동 분봉, 일봉 응답 패킷
struct B11_DATA_REP
{
    int acode;                   // anchor code
    int date;                    // 날짜
    int time;                    // 시간
    int kospi200;                // kospi200
    int future_cur_price;        // 선물 현제가
};

struct B11_PACKET_REP
{
    B11_HEADER_REP hdr;          // packet_type: ID_B11_PACKET_REP

    B11_DATA_REP* body;          // Header 의 count 갯수

    QUERY_FOOTER footer;       // packet_type: ID_B11_PACKET_REP
};

// 뉴스리스트 요청 패킷
struct B12_BODY_REQ
{
    int acode;                   // anchor code
    char db_num[20];             // db_num
                                 // 사용방법: 처음 조회시에는 db_num를 모르므로 
                                 // 0로 넘기고
                                 // 다음 버튼 클릭시 db_num을 주면 그 다음부터
    int date;                    // 검색일   YYYYMMDD
    int info_code;               // 송신사 구분
                                 // 00:전체(공시/뉴스)
                                 // 01:edaily, 02:joins, 03:프라임경제, 04:파이낸셜뉴스,
                                 // 05:etoday,  06:한국경제,  07:Financial Point
                                 // 08:머니투데이,  09:연합뉴스, 10:뉴스핌 99:공시
    int class_code;              // 뉴스 종류
    char sword[20];              // 검색어

    int count;                   // 데이터 요청 갯수

    unsigned char by_chart;              // 'D' : 일봉차트에서 뉴스데이터가 하루에 하나씩
                                 // '\0'  : 기본값
    unsigned char filler1;
    short site;                  // 0: 씽크, 1: 와우, 2: SK

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

// 뉴스리스트 응답 헤더
struct B12_HEADER_REP
{
    QUERY_HEADER hdr;

    int count;               // 데이터 갯수

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

// 뉴스리스트 응답 패킷
struct B12_DATA_REP
{
    char db_num[20];            // db_num Primary_KEY
    int date;                   // 날짜
    int time;                   // 시간
    int info_code;              // 송신사 구분
    int class_code;             // 뉴스 종류
    int acode;                  // anchor code
    char title[136];            // 뉴스 제목
};

struct B12_PACKET_REP
{
    B12_HEADER_REP hdr;          // packet_type: ID_B12_PACKET_REP

    B12_DATA_REP* body;          // Header 의 count 갯수

    QUERY_FOOTER footer;         // packet_type: ID_B12_PACKET_REP
};

// 뉴스본문 요청 패킷
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

// 뉴스본문 응답 헤더
struct B13_HEADER_REP
{
    QUERY_HEADER hdr;

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

// 뉴스본문 응답 패킷
// Component 안에서는 메모리 관리를 한다.
// 따라서 Strcutor pointer 로 파싱하면 다른 영역을 침범한 것으로 간주하여 에러난다.
struct B13_DATA_REP
{
    char db_num[20];       // db_num Primary_KEY
    int length;           // 본문 길이
    char* content;  // 본문
};

struct B13_PACKET_REP
{
    B13_HEADER_REP hdr;          // packet_type: ID_B13_PACKET_REP

    B13_DATA_REP body;

    QUERY_FOOTER footer;       // packet_type: ID_B13_PACKET_REP
};

// 종목 sort 요청 패킷
struct B14_BODY_REQ
{
    int sort_type;    // sort 타입
        // 1 : 현재가                 cur_price
        // 2 : 시가                   open_price
        // 3 : 고가                   high_price
        // 4 : 저가                   low_price
        // 5 : 누적 거래량            volume
        // 6 : 누적 거래대금          cash
        // 7 : 매도호가                 hoga[0].sel_price
        // 8 : 매수호가               hoga[0].buy_price
        // 9 : 매도호가 잔량          hoga[0].sell_vol
        // 10: 매수호가 잔량          hoga[0].buy_vol
        // 11: 시간외 총매도 잔량     timeout_sell_vol
        // 12: 시간외 총매수 잔량     timeout_buy_vol
        // 13: 10단계 총매도호가 잔량 tot10_sell_vol
        // 14: 10단계 총매수호가 잔량 tot0_buy_vol
        // 15: 변동율                 (고가-저가)*100/(종가)
        // 16: 변동폭                 고가 - 저가
        // 17: 매수호가잔량/거래량    hoga[0].buy_vol/volume
        // 18: 1차호가/총매수(%)      hoga[0].buy_price/tot10_buy_vol
        // 19: 매도호가잔량/거래량    hoga[0].sell_vol/volume
        // 20: 1차호가/총매도(%)      hoga[0].sell_price/tot10_sell_vol
        // 21: 총매수/총매도(%)       tot10_buy_vol*100/tot10_sell_vol
        // 22: 총매수/총거래량(%)     tot10_sell_vol*100/volume
        // 31:대비                    현재가 - 전일종가
        // 32:등락
         // 33:회전율

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

// 종목 sort 응답 헤더
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

// 종목 sort 응답 패킷
struct B14_DATA_REP
{
    int acode;            // 앵커코드
    int value;                      // 해당 sort 값
};

struct B14_PACKET_REP
{
    B14_HEADER_REP hdr;          // packet_type: ID_B14_PACKET_REP

    B14_DATA_REP* body;

    QUERY_FOOTER footer;       // packet_type: ID_B14_PACKET_REP
};

// 테마 조회 요청 패킷
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

// 테마 조회 응답 헤더
struct B15_HEADER_REP
{
    QUERY_HEADER hdr;
    int count;

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

// 테마 조회 응답 패킷
struct B15_DATA_REP
{
    char theme_code[4];                 // 테마코드
    char theme_name[64];                // 테마명
    int date;                           // 날짜
    int time;                           // 시간
    int tot_count;        // 테마 종속 종목수
    int upcount;                        // 상승 종목수
    int high_count;                     // 상한 종목수
    int downcount;                      // 하락 종목수
    int low_count;                      // 하락 종목수
    int avg_rate;                       // 평균 등락율
};

struct B15_PACKET_REP
{
    B15_HEADER_REP hdr;          // packet_type: ID_B15_PACKET_REP

    B15_DATA_REP* body;

    QUERY_FOOTER footer;       // packet_type: ID_B15_PACKET_REP
};

// 일별 외국인 조회 요청 패킷
struct B16_BODY_REQ
{
    int acode;               // anchor code
    int count;               // 데이터 요청 갯수. 우선순
    int s_date;              // 시작일   YYYYMMDD
    int e_date;              // 종료일   YYYYMMDD

    short time_unit;         // 1, 5, 10, 20, 40, 60 등등
    short term;              // 0: 일, 1: 주, 2: 월, 3: 분,
                             // 4: 초, 5: 틱, 6: 일중
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

// 일별 외국인 조회 응답 헤더
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

// 일별 외국인 조회 응답 패킷
struct B16_DATA_REP
{
    int acode;                        // 앵커코드
    int date;                         // 날짜
    int reg_volume;                   // 상장주식수
    int prv_close_price;              // 전일종가
    int prv_volume;                   // 전일거래량
    int buy_max_vol;                  // 주문가능수량
    int buy_min_vol;                  // 주문가능수량
    int limit_max_vol;                // 한도수량
    int limit_min_vol;                // 한도수량
    int limit_ratio;                  // 한도비율
    int chg_max_vol;                  // 변동수량
    int chg_min_vol;                  // 변동수량        단위:주
    int reserved_max_vol;             // 보유주식수        단위:억주
    int reserved_min_vol;             // 보유주식수        단위:주
    int reserved_ratio;               // 보유비율
    int vanish_ratio;                 // 한도소진율
};

struct B16_PACKET_REP
{
    B16_HEADER_REP hdr;          // packet_type: ID_B16_PACKET_REP

    B16_DATA_REP* body;

    QUERY_FOOTER footer;       // packet_type: ID_B16_PACKET_REP
};
//--------------------------------------------------------------------------
//섹터 조회 요청 패킷
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

//섹터 조회 응답 헤더
struct B17_HEADER_REP
{
    QUERY_HEADER hdr;
    int count;

    unsigned char filler1;
    unsigned char ff;
    unsigned char cr;
    unsigned char lf;
};

// 섹터 조회 응답 패킷
struct B17_DATA_REP
{
    char sector_code[4];                // 섹터 코드
    char sector_name[64];               // 섹터 명
    int date;                           // 날짜
    int time;                           // 시간
    int tot_count;                        // 섹터 종속 종목수
    int avg_rate;                       // 평균 등락율
};

struct B17_PACKET_REP
{
    B17_HEADER_REP hdr;          // packet_type: ID_B17_PACKET_REP

    B17_DATA_REP* body;

    QUERY_FOOTER footer;       // packet_type: ID_B17_PACKET_REP
};

//--------------------------------------------------------------------------
// 핵투쪽지 히스토리 조회 요청 패킷
struct B18_BODY_REQ
{
    int req_count;           // 히스토리 요청 갯수
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

// 핵투쪽지 히스토리 조회 응답 헤더
struct B18_HEADER_REP
{
    QUERY_HEADER hdr;

    int count;
};

// 핵투쪽지 히스토리 조회 응답 패킷
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
// 핵투 핵심주 리스트 조회 요청
struct B19_BODY_REQ
{
    int bdate;              // 기준일

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

// 핵투 핵심주 리스트 조회 응답
struct B19_HEADER_REP
{
    QUERY_HEADER hdr;

    int count;
};

// 핵투쪽지 히스토리 조회 응답 패킷
struct B19_DATA_REP
{
    int date;
    int acode;
    int time;                   // 시간
    int cur_price;              // 현재가
    int open_price;             // 시가
    int high_price;             // 고가
    int low_price;              // 저가
    int volume;                 // 누적 거래량
    int prv_close_price;        // 전일종가
    int daebi;                  // 전일대비
    int daebi_rate;             // 등락율
    int volume_rate;            // 거래량대비
    char comment[MAX_TODAY_COMMENT_NUM];         // 핵심주 코멘트
};

struct B19_PACKET_REP
{
    B19_HEADER_REP hdr;          // packet_type: ID_B19_PACKET_REP

    B19_DATA_REP* body;

    QUERY_FOOTER footer;
};
#endif
