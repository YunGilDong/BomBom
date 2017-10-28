//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Master.h"
#include <algorithm>
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TMaster::TMaster(void)
	: FData(_STD make_unique<TMemoryStream>())
{

}
//---------------------------------------------------------------------------
TMasterItem* __fastcall TMaster::GetItem(int Index)
{
    return &FItems[Index];
}
//---------------------------------------------------------------------------
void __fastcall TMaster::LoadFromFile(const String AFilename)
{
	FData->LoadFromFile(AFilename);
	FItems = (TMasterItem *)FData->Memory;
	FCount = FData->Size / sizeof(TMasterItem);
	Indexing();
}
//---------------------------------------------------------------------------
void __fastcall TMaster::Indexing(void)
{
	for (int i = 0, a = FCount; a-- > 0; i++)
	{
		FCodeIndex[TMaster::GetCode(Items[i])] = i;
		FACodeIndex[Items[i]->acode] = i;
	}
}
//---------------------------------------------------------------------------
TMasterItem* __fastcall TMaster::FindCode(const String ACode)
{
    if (ACode.IsEmpty()) {
        return nullptr;
    }
	TCodeIndex::iterator it = FCodeIndex.find(ACode);
	return (it != _STD end(FCodeIndex)? Items[it->second]: nullptr);
}
//---------------------------------------------------------------------------
TMasterItem* __fastcall TMaster::FindACode(const int AACode)
{
	TACodeIndex::iterator it = FACodeIndex.find(AACode);
	return (it != _STD end(FACodeIndex)? Items[it->second]: nullptr);
}
//---------------------------------------------------------------------------
template<class _Pr>
TMasterItem* __fastcall TMaster::Like(_Pr _Pred)
{
    TMasterItem *end = &FItems[FCount];
    TMasterItem *pResult = _STD find_if(FItems, end, _Pred);
    return (pResult != end? pResult: nullptr);
}
//---------------------------------------------------------------------------
TMasterItem* __fastcall TMaster::LikeCode(const String ACode)
{
    if (ACode.IsEmpty()) {
        return nullptr;
    }
    return Like([&ACode](const TMasterItem &Item) {
        return (TMaster::GetCode(&Item).Pos(ACode) == 1);
    });
}
//---------------------------------------------------------------------------
TMasterItem* __fastcall TMaster::LikeName(const String AName)
{
    String sName = AName.Trim().UpperCase();
    if (sName.IsEmpty()) {
        return nullptr;
    }
    return Like([&sName](const TMasterItem &Item) {

        return (TMaster::GetName(&Item).UpperCase().Pos(sName) == 1);
    });
}
//---------------------------------------------------------------------------
int __fastcall TMaster::CodeToACode(const String ACode)
{
    TMasterItem *pItem = FindCode(ACode);
    return (pItem? pItem->acode: 0);
}
//---------------------------------------------------------------------------
String __fastcall TMaster::ACodeToCode(const int AACode)
{
    return TMaster::GetCode(FindACode(AACode));
}
//---------------------------------------------------------------------------
String __fastcall TMaster::GetCode(const TMasterItem *AValue)
{
    return (String)(AValue != nullptr? AnsiString(AValue->code, 9).Trim(): "");
}
//---------------------------------------------------------------------------
String __fastcall TMaster::GetName(const TMasterItem *AValue)
{
    String sName = (String)(AValue != nullptr? AnsiString(AValue->name, 44).Trim(): "");
    sName = StringReplace(sName, "&", "&&", TReplaceFlags() << rfReplaceAll);
    return sName;
}
//---------------------------------------------------------------------------

