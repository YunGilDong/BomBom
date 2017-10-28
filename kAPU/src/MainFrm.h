//---------------------------------------------------------------------------

#ifndef MainFrmH
#define MainFrmH
//---------------------------------------------------------------------------
#include "mst.h"
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "KHOpenAPILib_OCX.h"
#include <Vcl.OleCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.WinXCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
class TMecaBackF : public TForm
{
	typedef TForm inherited;
__published:	// IDE-managed Components
	TKHOpenAPI *KHOpenAPI;
	TMemo *mmoUserInfo;
	TButton *btnReqStockInfo;
	TButton *Button4;
	TButton *btnReqAc;
	TStatusBar *statusBar;
	TMemo *mmoAccount;
	TGroupBox *GroupBox1;
	TEdit *edOrder1;
	TEdit *edOrder3;
	TEdit *edOrder4;
	TEdit *edOrder5;
	TEdit *Edit6;
	TLabel *laOrder1;
	TLabel *laOrder2;
	TLabel *laOrder3;
	TLabel *laOrder4;
	TLabel *laOrder5;
	TLabel *laOrder6;
	TButton *Button1;
	TComboBox *cbOrderType;
	TMemo *mmoOrderLog;
	TMemo *mmoCheJanLog;
	TMemo *mmoStackInfo;
	TEdit *edReqStockInfo;
	TLabel *Label1;
	void __fastcall btnReqStockInfoClick(TObject *Sender);
	void __fastcall KHOpenAPIReceiveTrData(TObject *Sender, BSTR sScrNo, BSTR sRQName,
          BSTR sTrCode, BSTR sRecordName, BSTR sPrevNext, long nDataLength, BSTR sErrorCode,
          BSTR sMessage, BSTR sSplmMsg);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall KHOpenAPIEventConnect(TObject *Sender, long nErrCode);
	void __fastcall btnReqAcClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall edOrder1KeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall KHOpenAPIReceiveChejanData(TObject *Sender, BSTR sGubun, long nItemCnt,
          BSTR sFIdList);
private:	// User declarations
	void __fastcall LoginPopUp(void);
	void __fastcall RequesMyAccouontInfo(void);
	void __fastcall RequeStockBasicInfo(void);
	void __fastcall GetMyAccouontInfo(void);
	void __fastcall GetStockBasicInfo(void);
	void __fastcall GetUserInformation(void);
	void __fastcall Start_Order(void);
	void __fastcall SendOrderVictory(void);
	void __fastcall SendOrderVictory(bool buy, String code, int price);
	void __fastcall OrderLogAdd(long orderType, UnicodeString Code,long Quantity,long Price);
	void __fastcall AutoBuy(int code, int price);
	void __fastcall AutoSell(int code, int price);
	st_InputValue SetValue;
	st_InputValue GetValue;
protected:
	virtual void __fastcall WndProc(Messages::TMessage &Message);
public:		// User declarations
	__fastcall TMecaBackF(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMecaBackF *MecaBackF;
//---------------------------------------------------------------------------
#endif
