//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Numstr.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
int __fastcall Numstr::TimeStrToInt(const String AValue)
{
    return AValue.SubString(1, 2).ToInt() * 60 * 60
        + AValue.SubString(4, 2).ToInt() * 60
        + AValue.SubString(7, 2).ToInt();
}
//---------------------------------------------------------------------------
int __fastcall Numstr::TimeToInt(const int AValue)
{
    return (AValue / 10000) * 60 * 60
        + (AValue / 100 % 100) * 60
        + (AValue % 100);
}
//---------------------------------------------------------------------------
int __fastcall Numstr::IntToTime(const int AValue)
{
    int Hour = (AValue / 3600) * 10000;
    int Minute = AValue % 3600;
    return Hour + ((Minute / 60) * 100) + (Minute % 60);
}
//---------------------------------------------------------------------------
String __fastcall Numstr::ChangeUnit(const String AValue, int AUnit)
{
    if (AValue.IsEmpty()) {
        return AValue;
    }
    __int64 i64Value = StrToInt64Def(RemoveComma(AValue), 0);
    for (int a = AUnit - 1; a-- > 0; i64Value /= 10);
    i64Value += 5;
    i64Value /= 10;
    return FormatFloat("#,##0", i64Value);
}
//---------------------------------------------------------------------------
String __fastcall Numstr::IntToDateStr(int AValue)
{
    return String().sprintf(_T("%04d-%02d-%02d"), AValue / 10000, AValue / 100 % 100, AValue % 100);
}
//---------------------------------------------------------------------------
String __fastcall Numstr::IntToTimeStr(int AValue)
{
    return String().sprintf(_T("%02d:%02d:%02d"), AValue / 10000, AValue / 100 % 100, AValue % 100);
}
//---------------------------------------------------------------------------
String __fastcall Numstr::IntToChartTimeStr(int AValue)
{
	return String().sprintf(_T("%02d:%02d"), AValue / 10000, AValue / 100 % 100);
}

//---------------------------------------------------------------------------
String __fastcall Numstr::SToNForStr(String AValue)
{
    if (AValue.IsEmpty()) {
		return AValue;
	}
	int cNumber = StrToIntDef(AValue,0);
	return FormatFloat("#,##0", cNumber);
}

//---------------------------------------------------------------------------
String __fastcall Numstr::NumberToCode(int nCode)
{
	return String().sprintf(_T("%06d"),nCode);
}
