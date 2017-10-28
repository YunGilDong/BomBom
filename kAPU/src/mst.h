#ifndef _MST_H_
#define _MST_H_

//--------------------------------------------------------------------------
// Error Code
//--------------------------------------------------------------------------
const int OP_ERR_NONE               = 0;    // 정상처리
const int OP_ERR_FAIL               = -10;  // 실패
const int OP_ERR_LOGIN              = -100; // 사용자정보교환실패
const int OP_ERR_CONNECT            = -101; // 서버접속실패
const int OP_ERR_VERSION            = -102; // 버전처리실패
const int OP_ERR_FIREWALL           = -103; // 개인방화벽실패
const int OP_ERR_MEMORY             = -104; // 메모리보호실패
const int OP_ERR_INPUT              = -105; // 함수입력값오류
const int OP_ERR_SOCKET_CLOSED      = -106; // 통신연결종료
const int OP_ERR_SISE_OVERFLOW      = -200; // 시세조회과부하
const int OP_ERR_RQ_STRUCT_FAIL     = -201; // 전문작성초기화실패
const int OP_ERR_RQ_STRING_FAIL     = -202; // 전문작성입력값오류
const int OP_ERR_NO_DATA            = -203; // 데이터없음.
const int OP_ERR_OVER_MAX_DATA      = -204; // 조회가능한종목수초과
const int OP_ERR_DATA_RCV_FAIL      = -205; // 데이터수신실패
const int OP_ERR_OVER_MAX_FID       = -206; // 조회가능한FID수초과
const int OP_ERR_REAL_CANCEL        = -207; // 실시간해제오류
const int OP_ERR_ORD_WRONG_INPUT    = -300; // 입력값오류
const int OP_ERR_ORD_WRONG_ACCTN    = -301; // 계좌비밀번호없음
const int OP_ERR_OTHER_ACC_USE      = -302; // 타인계좌사용오류
const int OP_ERR_MIS_2BILL_EXC      = -303; // 주문가격이20억원을초과
const int OP_ERR_MIS_5BILL_EXC      = -304; // 주문가격이50억원을초과
const int OP_ERR_MIS_1PER_EXC       = -305; // 주문수량이총발행주수의1%초과오류
const int OP_ERR_MIS_3PER_EXC 	    = -306;	// 주문수량은총발행주수의3%초과오류
const int OP_ERR_SEND_FAIL 		    = -307;	// 주문전송실패
const int OP_ERR_ORD_OVERFLOW 	    = -308;	// 주문전송과부하
const int OP_ERR_MIS_300CNT_EXC     = -309;	// 주문수량300계약초과
const int OP_ERR_MIS_500CNT_EXC     = -310;	// 주문수량500계약초과
const int OP_ERR_ORD_WRONG_ACCTINFO = -340;	// 계좌정보없음
const int OP_ERR_ORD_SYMCODE_EMPTY 	= -500;	// 종목코드없음
//--------------------------------------------------------------------------
// Account Info
//--------------------------------------------------------------------------
//const BSTR pMyAccNO = SysAllocString(L"6000163741");
//WideString pMyAccNO_MO = (L"8095376111");

//--------------------------------------------------------------------------
// LoginInfo
//--------------------------------------------------------------------------
/*
const BSTR pUSER_ID =SysAllocString(L"USER_ID");
const BSTR pUSER_NAME =SysAllocString(L"USER_NAME");
const BSTR pACCOUNT_CNT =SysAllocString(L"ACCOUNT_CNT");
const BSTR pACCNO =SysAllocString(L"ACCNO");
const BSTR pKEY_BSECGB=SysAllocString(L"KEY_BSECGB");
const BSTR pFIREW_SECGB =SysAllocString(L"FIREW_SECGB");
*/
//--------------------------------------------------------------------------
struct st_LoginInfo
{
	WideString rUserID;
	WideString rAccountCnT;
	WideString rAccno;
	WideString rUserName;
	WideString rKeyBsecgb;
	WideString rFirewSecgv;
};

struct st_OrderInfo
{
	// [주문체결통보]
	WideString rOrderTime;     // 주문시간
	WideString rCodeName;      // 종목명
	WideString rOrderCnt;      // 주문수량
	WideString rCheGyeolCnt;   // 체결수량
	WideString rCheGyeolPrice; // 체결가격

	//[잔고통보]
	WideString rJCode;      // 종목코드
	WideString rMyQuantity; // 보유수량
	WideString rDeposit;    // 예수금
};

//--------------------------------------------------------------------------
// SetInputValue
//--------------------------------------------------------------------------
/*
const WideString pSetCode = SysAllocString(L"종목코드");
const WideString pSetAccno = SysAllocString(L"계좌번호");
const WideString pPassWord = SysAllocString(L"비밀번호");
const WideString pStockOrder = SysAllocString(L"주식주문");
const WideString pSangPe = SysAllocString(L"상장폐지조회구분");
const WideString pPWinputType = SysAllocString(L"비밀번호입력매체구분");
const WideString pReqAccoNO = SysAllocString(L"계좌평가현황요청");
const WideString pValue00 = SysAllocString(L"00");
const WideString pValueEmpty = SysAllocString(L""); */

//===============================================================
// 주식기본정보
//===============================================================
/*
const BSTR pRQName_SB_Info = SysAllocString(L"주식기본정보");
const BSTR pJCode = SysAllocString(L"종목코드");
const BSTR pJName = SysAllocString(L"종목명");
const BSTR pCurPrice = SysAllocString(L"현재가");
const BSTR pChangeRate = SysAllocString(L"등락율");
const BSTR pVolume = SysAllocString(L"거래량");
const BSTR pStartPrice = SysAllocString(L"시가");
const BSTR pHighPrice = SysAllocString(L"고가");
const BSTR pLowPrice = SysAllocString(L"저가");
*/
//===============================================================

//===============================================================
// 계좌평가정보
//===============================================================
/*
const BSTR pDeposit     = SysAllocString(L"예수금");      // 예수금
const BSTR pDeposit_2d  = SysAllocString(L"D+2추정예수금");   // D+2추정예수금
const BSTR pToPurch     = SysAllocString(L"총매입금액");      // 총매입금액
const BSTR pOneDayRate  = SysAllocString(L"당일손익율");   // 당일손익율
const BSTR pMoaMoaRate  = SysAllocString(L"누적손익율");   // 누적손익율
const BSTR pMoaMoaPrice = SysAllocString(L"누적투자손익");  // 누적투자손익
*/
	/*
	BSTR pSetAccno;
	BSTR pMyAccNO_MO;
	BSTR pPassWord;
	BSTR pValueEmpty;
	BSTR pSangPe;
	BSTR pTemp;
	BSTR pPWinputType;
	BSTR pValue00;
	BSTR pReqAccoNO;
	BSTR pTrCode_OPW00004;
	BSTR pScreenNo_6001;     */
//===============================================================

//const WideString pTrCode_OPW00004 = SysAllocString(L"OPW00004");



//const WideString pScreenNo_6001 = SysAllocString(L"6001");


//--------------------------------------------------------------------------
struct st_InputValue
{
	BSTR jCode;
	BSTR cAccno;
};

//--------------------------------------------------------------------------
struct st_jBasic_Info
{
	WideString rJCode;
	WideString rJName;
	WideString rCurPrice;
	WideString rChangeRate;
	WideString rVolume;
	WideString rStartPrice;
	WideString rHighPrice;
	WideString rLowPrice;
};


//--------------------------------------------------------------------------
// 계좌평가
//--------------------------------------------------------------------------
struct st_MyAccount_Info
{
	WideString rDeposit;      // 예수금
	WideString rDeposit_2d;   // D+2추정예수금
	WideString rToPurch;      // 총매입금액
	WideString rOneDayRate;   // 당일손익율
	WideString rMoaMoaRate;   // 누적손익율
	WideString rMoaMoaPrice;  // 누적투자손익
};
#endif

