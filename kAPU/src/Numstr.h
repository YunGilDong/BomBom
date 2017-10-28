//---------------------------------------------------------------------------
#ifndef NumstrH
#define NumstrH
//---------------------------------------------------------------------------
#include <System.hpp>
#include <System.SysUtils.hpp>
//---------------------------------------------------------------------------
namespace Numstr {

int __fastcall TimeStrToInt(const String AValue);
int __fastcall TimeToInt(const int AValue); // hhnnss -> s
int __fastcall IntToTime(const int AValue); // s -> hhnnss
String __fastcall ChangeUnit(const String AValue, int AUnit);
String __fastcall IntToDateStr(int AValue);
String __fastcall IntToTimeStr(int AValue);
String __fastcall IntToChartTimeStr(int AValue);
String __fastcall SToNForStr(String AValue);
String __fastcall NumberToCode(int nCode);

inline String __fastcall RemoveComma(const String AValue)
{
    return StringReplace(AValue, ",", "", TReplaceFlags() << rfReplaceAll);
}

template <class T>
inline String __fastcall NumberToString(T AValue, const String AFormat = "#,##0")
{
    return FormatFloat(AFormat, AValue);
}

};
//---------------------------------------------------------------------------
#endif
