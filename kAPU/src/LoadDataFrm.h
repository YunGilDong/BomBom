//---------------------------------------------------------------------------

#ifndef LoadDataFrmH
#define LoadDataFrmH

#include "mst.h"
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TLoadDataF : public TForm
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
	__fastcall TLoadDataF(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLoadDataF *LoadDataF;
extern PACKAGE st_LoginInfo sLoginInfo;
extern PACKAGE st_jBasic_Info jBasicInfo;
extern PACKAGE st_MyAccount_Info MyAccountInfo;
extern PACKAGE st_OrderInfo OrderInfo;
//---------------------------------------------------------------------------
#endif
