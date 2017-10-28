//---------------------------------------------------------------------------
#ifndef MasterH
#define MasterH
//---------------------------------------------------------------------------
#include <memory>
#include <map>
#include "sb_com_packet.h"
//---------------------------------------------------------------------------
typedef MASTER_STOCK_PACKET TMasterItem;
typedef TMasterItem *PMasterItem;
//---------------------------------------------------------------------------
class TMaster
{
private:
    const _STD unique_ptr<TMemoryStream> FData;
    TMasterItem *FItems;
    int FCount;

    typedef _STD map<String, int> TCodeIndex;
    typedef _STD map<int, int> TACodeIndex;
    TCodeIndex FCodeIndex;
    TACodeIndex FACodeIndex;
    void __fastcall Indexing(void);

    TMasterItem* __fastcall GetItem(int Index);

public:
    __fastcall TMaster(void);

    void __fastcall LoadFromFile(const String AFilename);

    TMasterItem* __fastcall FindCode(const String ACode);
    TMasterItem* __fastcall FindACode(const int AACode);

    template<class _Pr>
        TMasterItem* __fastcall Like(_Pr _Pred);

    TMasterItem* __fastcall LikeCode(const String ACode);
    TMasterItem* __fastcall LikeName(const String AName);

    int __fastcall CodeToACode(const String ACode);
    String __fastcall ACodeToCode(const int AACode);

    __property TMasterItem *Items[int Index] = {read = GetItem};
    __property int Count = {read = FCount};

    static String __fastcall GetCode(const TMasterItem *AValue);
    static String __fastcall GetName(const TMasterItem *AValue);

};
//---------------------------------------------------------------------------
#endif
