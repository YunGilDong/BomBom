//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

//#include "mst.h"
#include <comdef.h>
#include "MainFrm.h"
#include "LoadDataFrm.h"
#include "Numstr.h"
#include "Messages.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "KHOpenAPILib_OCX"
#pragma resource "*.dfm"
TMecaBackF *MecaBackF;
/*
typedef 상으로는 BSTR은 wchar_t* 이지만 실제는 그렇지 않습니다.
BSTR은 시작되는 메모리 번지수 앞 4바이트에 스트링의 길이가 저장됩니다.
wchar_t* 이지만 wchar_t*이 아닌 이유입니다.
WideString은 BSTR과의 호환성을 위해 만들어진 클래스이므로 데이터 저장 방식이
BSTR과 일치합니다. 그래서 아무 문제가 없지만
그냥 wchar_t*로 선언해서 문자열을 던지면 문제가 생기는겁니다.
*/
//---------------------------------------------------------------------------
__fastcall TMecaBackF::TMecaBackF(TComponent* Owner): TForm(Owner)
{
//
}
//---------------------------------------------------------------------------
void __fastcall TMecaBackF::LoginPopUp(void)
{
	long Result = KHOpenAPI->CommConnect();

	if(Result != 0)
		statusBar->Panels->Items[0]->Text = "Login창 불러오기 실패";
	else
		statusBar->Panels->Items[0]->Text = "Login창 열림";
}


//---------------------------------------------------------------------------
void __fastcall TMecaBackF::GetUserInformation(void)
{
	BSTR pUSER_ID =SysAllocString(L"USER_ID");
	BSTR pUSER_NAME =SysAllocString(L"USER_NAME");
	BSTR pACCOUNT_CNT =SysAllocString(L"ACCOUNT_CNT");
	BSTR pACCNO =SysAllocString(L"ACCNO");
	BSTR pKEY_BSECGB=SysAllocString(L"KEY_BSECGB");
	BSTR pFIREW_SECGB =SysAllocString(L"FIREW_SECGB");

	sLoginInfo.rUserID = KHOpenAPI->GetLoginInfo(pUSER_ID);
	sLoginInfo.rUserName = KHOpenAPI->GetLoginInfo(pUSER_NAME);
	sLoginInfo.rAccountCnT = KHOpenAPI->GetLoginInfo(pACCOUNT_CNT);
	sLoginInfo.rAccno = KHOpenAPI->GetLoginInfo(pACCNO);
	sLoginInfo.rKeyBsecgb = KHOpenAPI->GetLoginInfo(pKEY_BSECGB);
	sLoginInfo.rFirewSecgv = KHOpenAPI->GetLoginInfo(pFIREW_SECGB);

	mmoUserInfo->Lines->Add("<접속정보>");
	mmoUserInfo->Lines->Add("ID : " + sLoginInfo.rUserID);
	mmoUserInfo->Lines->Add("사용자명 : " + sLoginInfo.rUserName);
	mmoUserInfo->Lines->Add("계좌계수 : " + sLoginInfo.rAccountCnT);
	mmoUserInfo->Lines->Add("계좌번호 : " + sLoginInfo.rAccno);
	mmoUserInfo->Lines->Add("키보드보안 : " + sLoginInfo.rKeyBsecgb); // 키보드보안 해지여부 0:정상, 1:해지
	mmoUserInfo->Lines->Add("방화벽 : " + sLoginInfo.rFirewSecgv);    // 방화벽 설정 여부. 0:미설정, 1:설정, 2:해지
}

//---------------------------------------------------------------------------
// LONG CommRqData(BSTR sRQName, BSTR sTrCode, long nPrevNext, BSTR sScreenNo)
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void __fastcall TMecaBackF::RequeStockBasicInfo(void)
{
	// 주식기본정보요청
	BSTR pRQName_SB_Info = SysAllocString(L"주식기본정보");
	BSTR pSetCode = SysAllocString(L"종목코드");
	BSTR pCode = SysAllocString(edReqStockInfo->Text.c_str());
	BSTR pTrCode_OPT10001 = SysAllocString(L"OPT10001");
	BSTR pScreenNo_0101 = SysAllocString(L"0101");
	int result;

	try
	{
		KHOpenAPI->SetInputValue(pSetCode, pCode);
		result = KHOpenAPI->CommRqData(pRQName_SB_Info, pTrCode_OPT10001, 0, pScreenNo_0101);
	}__finally
	{
		if(result == 0)
		{
			statusBar->Panels->Items[0]->Text = "정보요청 성공";
		}
		else
			statusBar->Panels->Items[0]->Text = "정보요청 실패";
	}
}

//---------------------------------------------------------------------------
void __fastcall TMecaBackF::btnReqStockInfoClick(TObject *Sender)
{
	RequeStockBasicInfo();
}
//---------------------------------------------------------------------------
void __fastcall TMecaBackF::KHOpenAPIReceiveTrData(TObject *Sender, BSTR sScrNo, BSTR sRQName,
		  BSTR sTrCode, BSTR sRecordName, BSTR sPrevNext, long nDataLength, BSTR sErrorCode,
		  BSTR sMessage, BSTR sSplmMsg)
{
	// 주식기본정보
	BSTR pRQName_SB_Info = SysAllocString(L"주식기본정보");
	BSTR pJCode = SysAllocString(L"종목코드");
	BSTR pJName = SysAllocString(L"종목명");
	BSTR pCurPrice = SysAllocString(L"현재가");
	BSTR pChangeRate = SysAllocString(L"등락율");
	BSTR pVolume = SysAllocString(L"거래량");
	BSTR pStartPrice = SysAllocString(L"시가");
	BSTR pHighPrice = SysAllocString(L"고가");
	BSTR pLowPrice = SysAllocString(L"저가");
	// 계좌평가현황
	BSTR pDeposit     = SysAllocString(L"예수금");      // 예수금
	BSTR pDeposit_2d  = SysAllocString(L"D+2추정예수금");   // D+2추정예수금
	BSTR pToPurch     = SysAllocString(L"총매입금액");      // 총매입금액
	BSTR pOneDayRate  = SysAllocString(L"당일손익율");   // 당일손익율
	BSTR pMoaMoaRate  = SysAllocString(L"누적손익율");   // 누적손익율
	BSTR pMoaMoaPrice = SysAllocString(L"누적투자손익");  // 누적투자손익

	BSTR tempValue = sRQName;
	if(wcscmp(L"주식기본정보",sRQName) == 0)
	{
		jBasicInfo.rJCode = KHOpenAPI->GetCommData(sTrCode,sRQName,0,pJCode);
		jBasicInfo.rJName = KHOpenAPI->GetCommData(sTrCode,sRQName,0,pJName);// = KHOpenAPI->GetCommData(sTrCode,sRQName,0,pJName);
		jBasicInfo.rCurPrice = KHOpenAPI->GetCommData(sTrCode,sRQName,0,pCurPrice);
		jBasicInfo.rChangeRate = KHOpenAPI->GetCommData(sTrCode,sRQName,0,pChangeRate);
		jBasicInfo.rVolume = KHOpenAPI->GetCommData(sTrCode,sRQName,0,pVolume);
		jBasicInfo.rStartPrice = KHOpenAPI->GetCommData(sTrCode,sRQName,0,pStartPrice);
		jBasicInfo.rHighPrice = KHOpenAPI->GetCommData(sTrCode,sRQName,0,pHighPrice);
		jBasicInfo.rLowPrice = KHOpenAPI->GetCommData(sTrCode,sRQName,0,pLowPrice);
		GetStockBasicInfo();
	}else if(wcscmp(L"계좌평가현황요청",sRQName) == 0)
	{
		MyAccountInfo.rDeposit = KHOpenAPI->GetCommData(SysAllocString(L"OPW00004"),SysAllocString(L"계좌평가현황요청"),0,pDeposit);
		MyAccountInfo.rDeposit_2d = KHOpenAPI->GetCommData(SysAllocString(L"OPW00004"),SysAllocString(L"계좌평가현황요청"),0,pDeposit_2d);
		MyAccountInfo.rToPurch = KHOpenAPI->GetCommData(SysAllocString(L"OPW00004"),SysAllocString(L"계좌평가현황요청"),0,pToPurch);
		MyAccountInfo.rOneDayRate = KHOpenAPI->GetCommData(SysAllocString(L"OPW00004"),SysAllocString(L"계좌평가현황요청"),0,pOneDayRate);
		MyAccountInfo.rMoaMoaRate = KHOpenAPI->GetCommData(SysAllocString(L"OPW00004"),SysAllocString(L"계좌평가현황요청"),0,pMoaMoaRate);
		MyAccountInfo.rMoaMoaPrice = KHOpenAPI->GetCommData(SysAllocString(L"OPW00004"),SysAllocString(L"계좌평가현황요청"),0,pMoaMoaPrice);
		GetMyAccouontInfo();
	}
}

//---------------------------------------------------------------------------
// nOrderType - 주문유형 (1:신규매수, 2:신규매도, 3:매수취소, 4:매도취소, 5:매수정정, 6:매도정정
//sHogaGb – 00:지정가, 03:시장가, 05:조건부지정가, 06:최유리지정가, 07:최우선지정가, 10:지정
//가IOC, 13:시장가IOC, 16:최유리IOC, 20:지정가FOK, 23:시장가FOK, 26:최유리FOK, 61:장전시간
//외종가, 62:시간외단일가, 81:장후시간외종가
//---------------------------------------------------------------------------
void __fastcall TMecaBackF::Start_Order(void)
{
	WideString pCode = "084370";
	WideString pHogaGb = "00";
//	int ret = KHOpenAPI->SendOrder(pStockOrder, pScreenNo_0101, pMyAccNO_MO, 1, pCode, 10, 21400, pHogaGb,L"");

}


//---------------------------------------------------------------------------
void __fastcall TMecaBackF::Button4Click(TObject *Sender)
{
	Start_Order();
//	pMyAccNO_MO.c_bstr();
}

//---------------------------------------------------------------------------
// 계좌조회
//---------------------------------------------------------------------------
void __fastcall TMecaBackF::RequesMyAccouontInfo(void)
{
	BSTR pSetAccno = SysAllocString(L"계좌번호");
	BSTR pMyAccNO_MO = SysAllocString(L"8095376111");
	BSTR pPassWord = SysAllocString(L"비밀번호");
	BSTR pValueEmpty = SysAllocString(L"");
	BSTR pSangPe = SysAllocString(L"상장폐지조회구분");
	BSTR pTemp  = SysAllocString(L"0");
	BSTR pPWinputType = SysAllocString(L"비밀번호입력매체구분");
	BSTR pValue00 = SysAllocString(L"00");
	BSTR pReqAccoNO = SysAllocString(L"계좌평가현황요청");
	BSTR pTrCode_OPW00004 = SysAllocString(L"OPW00004");
	BSTR pScreenNo_6001 = SysAllocString(L"6001");

	int nRet;

	try
	{
		KHOpenAPI->SetInputValue(pSetAccno, pMyAccNO_MO); // 계좌번호("계좌번호",000000000)
		KHOpenAPI->SetInputValue(pPassWord, pValueEmpty);         // 비밀번호
		KHOpenAPI->SetInputValue(pSangPe, pTemp);         // 상장폐지조회구분
		KHOpenAPI->SetInputValue(pPWinputType, pValue00);   // 비밀번호입력매체구분
		nRet = KHOpenAPI->CommRqData(pReqAccoNO, pTrCode_OPW00004, 0,pScreenNo_6001);
	}__finally
	{
		statusBar->Panels->Items[1]->Text = "결과:"+IntToStr(nRet) ;
	}
}

//---------------------------------------------------------------------------
void __fastcall TMecaBackF::GetMyAccouontInfo(void)
{
	mmoAccount->Clear();
	mmoAccount->Lines->Add("<계좌정보>");
	mmoAccount->Lines->Add("예수금         = " + Numstr::SToNForStr(MyAccountInfo.rDeposit));
	mmoAccount->Lines->Add("예수금+2      = " + Numstr::SToNForStr(MyAccountInfo.rDeposit_2d));
	mmoAccount->Lines->Add("총매입금액    = " + Numstr::SToNForStr(MyAccountInfo.rToPurch));
	mmoAccount->Lines->Add("당일손익율    = " + Numstr::SToNForStr(MyAccountInfo.rOneDayRate));
	mmoAccount->Lines->Add("누적손익율    = " + Numstr::SToNForStr(MyAccountInfo.rMoaMoaRate));
	mmoAccount->Lines->Add("누적투자손익 = " + Numstr::SToNForStr(MyAccountInfo.rMoaMoaPrice));
}

//---------------------------------------------------------------------------
// 주식기봉정보
//---------------------------------------------------------------------------
void __fastcall TMecaBackF::GetStockBasicInfo(void)
{
//	mmoStackInfo->Clear();
//	mmoStackInfo->Lines->Add("<주식기본정보>");
	mmoStackInfo->Lines->Add("종목코드       = " + StringReplace( jBasicInfo.rJCode," ", "", TReplaceFlags() << rfReplaceAll ));
	mmoStackInfo->Lines->Add("종목명     = " + StringReplace( jBasicInfo.rJName," ", "", TReplaceFlags() << rfReplaceAll ));
	mmoStackInfo->Lines->Add("현재가   = " + StringReplace( jBasicInfo.rCurPrice," ", "", TReplaceFlags() << rfReplaceAll ));
	mmoStackInfo->Lines->Add("등락율   = " + StringReplace( jBasicInfo.rChangeRate," ", "", TReplaceFlags() << rfReplaceAll ));
	mmoStackInfo->Lines->Add("거래량   = " + StringReplace( jBasicInfo.rVolume," ", "", TReplaceFlags() << rfReplaceAll ));
	mmoStackInfo->Lines->Add("시가 = " + StringReplace( jBasicInfo.rStartPrice," ", "", TReplaceFlags() << rfReplaceAll ));
	mmoStackInfo->Lines->Add("고가 = " + StringReplace( jBasicInfo.rHighPrice," ", "", TReplaceFlags() << rfReplaceAll ));
	mmoStackInfo->Lines->Add("저가 = " + StringReplace( jBasicInfo.rLowPrice," ", "", TReplaceFlags() << rfReplaceAll ));
}

//---------------------------------------------------------------------------
void __fastcall TMecaBackF::FormShow(TObject *Sender)
{
	LoginPopUp();
}

//---------------------------------------------------------------------------
void __fastcall TMecaBackF::KHOpenAPIEventConnect(TObject *Sender, long nErrCode)
{
	if(nErrCode == 0)
	{
		statusBar->Panels->Items[0]->Text = "Login 성공";
		GetUserInformation();
	}
	else
		statusBar->Panels->Items[0]->Text = "Login 실패";
}

//---------------------------------------------------------------------------
void __fastcall TMecaBackF::btnReqAcClick(TObject *Sender)
{
	RequesMyAccouontInfo();
}

//---------------------------------------------------------------------------
void __fastcall TMecaBackF::Button1Click(TObject *Sender)
{
	SendOrderVictory();
}

//---------------------------------------------------------------------------
	/*
	sRQName - 사용자 구분 요청 명
	sScreenNo - 화면번호[4]
	sAccNo - 계좌번호[10]
	nOrderType - 주문유형 (1:신규매수, 2:신규매도, 3:매수취소, 4:매도취소, 5:매수정정, 6:매도정정)
	sCode, - 주식종목코드
	nQty – 주문수량
	nPrice – 주문단가
	sHogaGb - 거래구분 00:지정가, 03:시장가, 05:조건부지정가, 06:최유리지정가, 07:최우선지정가, 10:지정가IOC, 13:시장가IOC, 16:최유리IOC, 20:지정가FOK, 23:시장가FOK, 26:최유리FOK, 61:장전시간외종가, 62:시간외단일가, 81:장후시간외종가
	sOrgOrderNo – 원주문번호
	*/
//---------------------------------------------------------------------------
// 주식주문
//---------------------------------------------------------------------------
void __fastcall TMecaBackF::SendOrderVictory()
{
	BSTR pStockOrder = SysAllocString(L"RQ_1");
	BSTR pScreenNo_0101 = SysAllocString(L"0101");
	BSTR pCode = SysAllocString(edOrder1->Text.c_str());
	BSTR pMyAccNO = SysAllocString(L"6000163741");
	BSTR pMyAccNO_MO = SysAllocString(L"8095376111");
	BSTR pValue00 = SysAllocString(L"00");
	BSTR pValueEmpty = SysAllocString(L"");
	long pOrderType = cbOrderType->ItemIndex + 1;
	long pQuantity = StrToIntDef(edOrder3->Text,0);
	long pPrice = StrToIntDef(edOrder4->Text,0);
	long result;
	try
	{
		result = KHOpenAPI->SendOrder(pStockOrder, pScreenNo_0101, pMyAccNO_MO, pOrderType, pCode, pQuantity, pPrice, pValue00, pValueEmpty);

	}__finally
	{
		ShowMessage(result);
		if(result == 0)
		{
			statusBar->Panels->Items[0]->Text = "주문전송 성공";
			OrderLogAdd(pOrderType,edOrder1->Text,pQuantity,pPrice);
		}
		else
			statusBar->Panels->Items[0]->Text = "주문전송 실패";
	}
}

//---------------------------------------------------------------------------
// 자동주식주문
//---------------------------------------------------------------------------
void __fastcall TMecaBackF::SendOrderVictory(bool buy, String code, int price)
{
	BSTR pStockOrder = SysAllocString(L"RQ_1");
	BSTR pScreenNo_0101 = SysAllocString(L"0101");
	BSTR pCode = SysAllocString(code.c_str());
	BSTR pMyAccNO = SysAllocString(L"6000163741");
	BSTR pMyAccNO_MO = SysAllocString(L"8095376111");
	BSTR pValue00 = SysAllocString(L"00");
	BSTR pValueEmpty = SysAllocString(L"");
	long pOrderType; //cbOrderType->ItemIndex + 1;
	if(buy)
	{
		pOrderType = 1;
	}else
	{
        pOrderType = 2;
    }
	long pOrderType = cbOrderType->ItemIndex + 1;

	long pQuantity = 1;//StrToIntDef(edOrder3->Text,0);
	long pPrice = price;
	long result;
	try
	{
		result = KHOpenAPI->SendOrder(pStockOrder, pScreenNo_0101, pMyAccNO_MO, pOrderType, pCode, pQuantity, pPrice, pValue00, pValueEmpty);

	}__finally
	{
		if(result == 0)
		{
			statusBar->Panels->Items[0]->Text = "주문전송 성공";
			OrderLogAdd(pOrderType,code,pQuantity,pPrice);
		}
		else
			statusBar->Panels->Items[0]->Text = "주문전송 실패";
	}
}

//---------------------------------------------------------------------------
// 숫자만
//---------------------------------------------------------------------------
void __fastcall TMecaBackF::edOrder1KeyPress(TObject *Sender, System::WideChar &Key)
{
	if(( Key >= 48 && Key <= 57 ) ||  ( Key >= 96 && Key <= 105 )){
	}
	else {
	 Key = 0;
	}
}

//---------------------------------------------------------------------------
void __fastcall TMecaBackF::OrderLogAdd(long orderType, UnicodeString Code,long Quantity,long Price)
{
	String strLog;
	strLog.sprintf(L"[주문%d][코드%s][수량%d][가격%d][시간%s]", orderType, Code, Quantity,Price, Now().FormatString("HH:NN:SS").c_str());
	mmoOrderLog->Lines->Add(strLog);
}

//---------------------------------------------------------------------------
void __fastcall TMecaBackF::KHOpenAPIReceiveChejanData(TObject *Sender, BSTR sGubun, long nItemCnt,
		  BSTR sFIdList)
{
	ShowMessage(sGubun);
	if(wcscmp(L"0",sGubun) == 0)
	{
		OrderInfo.rOrderTime = KHOpenAPI->GetChejanData(908);
		OrderInfo.rCodeName = KHOpenAPI->GetChejanData(302);
		OrderInfo.rOrderCnt = KHOpenAPI->GetChejanData(900);
		OrderInfo.rCheGyeolCnt = KHOpenAPI->GetChejanData(911);
		OrderInfo.rCheGyeolPrice = KHOpenAPI->GetChejanData(911);
		mmoCheJanLog->Lines->Add("[주문체결통보]");
		mmoCheJanLog->Lines->Add("주문/체결시간:" + StringReplace( OrderInfo.rOrderTime," ", "", TReplaceFlags() << rfReplaceAll ));
		mmoCheJanLog->Lines->Add("종목명:"   + StringReplace( OrderInfo.rCodeName," ", "", TReplaceFlags() << rfReplaceAll ));
		mmoCheJanLog->Lines->Add("주문수량:" + StringReplace( OrderInfo.rOrderCnt," ", "", TReplaceFlags() << rfReplaceAll ));
		mmoCheJanLog->Lines->Add("체경수량:" + StringReplace( OrderInfo.rCheGyeolCnt," ", "", TReplaceFlags() << rfReplaceAll ));
		mmoCheJanLog->Lines->Add("체결가격:" + StringReplace( OrderInfo.rCheGyeolPrice," ", "", TReplaceFlags() << rfReplaceAll ));
		mmoCheJanLog->Lines->Add("==============================");
	}else if(wcscmp(L"1",sGubun) == 0)
	{
		OrderInfo.rJCode = KHOpenAPI->GetChejanData(9001);
		OrderInfo.rMyQuantity = KHOpenAPI->GetChejanData(930);
		OrderInfo.rDeposit = KHOpenAPI->GetChejanData(951);
		mmoCheJanLog->Lines->Add("[잔고통보]");
		mmoCheJanLog->Lines->Add("종목코드:" + StringReplace( OrderInfo.rJCode," ", "", TReplaceFlags() << rfReplaceAll ));
		mmoCheJanLog->Lines->Add("보유수량:" + StringReplace( OrderInfo.rMyQuantity," ", "", TReplaceFlags() << rfReplaceAll ));
		mmoCheJanLog->Lines->Add("예수금:" + StringReplace( OrderInfo.rDeposit," ", "", TReplaceFlags() << rfReplaceAll ));
		mmoCheJanLog->Lines->Add("==============================");
	}else if(wcscmp(L"3",sGubun) == 0)
	{
		mmoCheJanLog->Lines->Add("[특이신호]");
		mmoCheJanLog->Lines->Add("==============================");
    }
}


//---------------------------------------------------------------------------
void __fastcall TMecaBackF::WndProc(Messages::TMessage &Message)
{
	if (Message.Msg == WM_BACKUP_B)
	{
		AutoBuy(Message.LParam,Message.WParam);
	}else if (Message.Msg == WM_BACKUP_S)
	{
		AutoSell(Message.LParam,Message.WParam);
	}

	inherited::WndProc(Message);
}

//---------------------------------------------------------------------------
void __fastcall TMecaBackF::AutoBuy(int code, int price)
{
	SendOrderVictory(true, Numstr::NumberToCode(code), price);
}

//---------------------------------------------------------------------------
void __fastcall TMecaBackF::AutoSell(int code, int price)
{
	SendOrderVictory(false, Numstr::NumberToCode(code), price);
}

