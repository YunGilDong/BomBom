//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "LoadDataFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TLoadDataF *LoadDataF;

st_LoginInfo sLoginInfo;
st_jBasic_Info jBasicInfo;
st_MyAccount_Info MyAccountInfo;
st_OrderInfo OrderInfo;
//---------------------------------------------------------------------------
__fastcall TLoadDataF::TLoadDataF(TComponent* Owner)
	: TForm(Owner)
{

}
//---------------------------------------------------------------------------
