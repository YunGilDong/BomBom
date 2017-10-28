//---------------------------------------------------------------------------

#ifndef commonFrmH
#define commonFrmH
//---------------------------------------------------------------------------
#include <Data.DB.hpp>
#include <Data.DBXOracle.hpp>
#include <Data.FMTBcd.hpp>
#include <Data.SqlExpr.hpp>
#include <System.Classes.hpp>
#include <System.DateUtils.hpp>


#include "AdvGrid.hpp"
#include "BaseGrid.hpp"

#include "Mios.h"

//#define ORAERR_NOT_LOGGED_ON   -2       // 1012
//#define ORAERR_NOT_CONNECTED   -3       // 3114

//---------------------------------------------------------------------------

void execCmd(AnsiString cmd);

//--------------------------------------------------------------------------
class TCommonF : public TForm
{
__published:
private:
public:
    int mCount;
    int DetSelectFlag;
    int DetCtlSelectFlag;
	TSQLConnection *DB;
    AnsiString logDir;

    AnsiString localFtpDir;
    AnsiString remoteFtpDir;
    AnsiString downloadFile;

	//---------------------------------------------------------------------------
	__fastcall TCommonF(TComponent* Owner);


	void __fastcall SetDB(TSQLConnection *dbase);
	bool __fastcall IsDbConnected();
    void __fastcall SetLogDir(AnsiString dir);
    //void __fastcall SetCodeToCombo(TQuery * Q, TComboBox * CB, AnsiString sCodeType, AnsiString sUserType);
    bool __fastcall IsGridEmpty(TAdvStringGrid *G);
    void __fastcall ClearGrid(TAdvStringGrid *G);
    void __fastcall SetDateTime(AnsiString sTime, TEdit * pDatetime, TEdit * pTime, TEdit * pMin);
    AnsiString  __fastcall MakeDateTime(TEdit * pDatetime, TEdit * pTime, TEdit * pMin);
    void __fastcall SaveGridToCSV(TAdvStringGrid * SG);
    AnsiString  __fastcall SubString(const AnsiString* str, char c);

    // FILE FUNCTION
    bool __fastcall GetFileDateStr(const char *fileName, AnsiString* strDate);
    void __fastcall DateTimeToFileTime(const TDateTime *localDateTime, FILETIME* utcFileTime);
    bool __fastcall SetFileDateStr(const char *fileName, AnsiString strDate);
    bool __fastcall SetFileDate(const char *fileName, int year, int mon, int day, int hour, int min, int sec);
    bool __fastcall ExistFile(AnsiString filePath, AnsiString regDate);
    bool __fastcall FindFile(AnsiString dir, AnsiString fileName, AnsiString regDate);

    // DB FUNCTION
    int  __fastcall GetOracleError(AnsiString sErrMsg);
    int  __fastcall GetOracleErrorResult(int iOraErrCode);
	int  __fastcall ExecSQL(TSQLQuery *pQry, AnsiString strSql);
	int  __fastcall ExecSQL(TSQLQuery *pQry);
	int  __fastcall OpenSQL(TSQLQuery *pQry, AnsiString strSql);
	int  __fastcall OpenSQL(TSQLQuery *pQry);
    void __fastcall WriteQueryError(AnsiString strOraErr, AnsiString strSql);

    void __fastcall SetFtpInfo( AnsiString localDir, AnsiString remoteDir,
                                AnsiString Address,  int port,
                                AnsiString user,     AnsiString passwd );
    //bool __fastcall FtpDownload(AnsiString localDir, AnsiString remoteDir, AnsiString fileName);
    void __fastcall StringSplit(AnsiString str, char delim, TStringList* result);

    //---------------------------------------------------------------------------
    void __fastcall ExtractDateTime
                    (TDateTime  dtDate, AnsiString strHHMISS, TDateTime *rtDateTime ) ;
    void __fastcall ExtractDateTime
                    (TDateTime  dtDate, AnsiString strHH, AnsiString strMI, AnsiString strSS, TDateTime *rtDateTime );
    void __fastcall ExtractDateTime
                    ( AnsiString strYYYY, AnsiString strMM, AnsiString strDD
                    , AnsiString strHH,   AnsiString strMI, AnsiString strSS, TDateTime *rtDateTime ) ;

    void __fastcall ExtractDateTime
                    (TDateTime  dtDate, bool bFirst /* 시작 : true 마지막 : false */ , TDateTime *rtDateTime );

    void __fastcall ExtractDateTime
                    (TDateTime  dtDate, AnsiString strHH, bool bFirst /* 시작 : true 마지막 : false */ , TDateTime *rtDateTime );                               

	void __fastcall StrToHHMM(AnsiString str, int* HH, int* MM);
	void __fastcall StrToDateByte(AnsiString str, char* bDate );
    //------------------------------------------------------------------------
    AnsiString __fastcall DateToString(TDateTime aDate)
    {
        return  FormatDateTime("YYYY-MM-DD",aDate);
    };

    //------------------------------------------------------------------------
    TDateTime __fastcall StringToDate(char aDate[10])
    {
        TDateTime ReturnValue;
        AnsiString tDate = aDate;
        if(tDate == ""){
            ReturnValue = NULL;
        } else {
            ReturnValue = StrToDate(tDate);
        }
        return  ReturnValue;
    };

    //------------------------------------------------------------------------
    AnsiString __fastcall StrDateToFormatStr(AnsiString aDate)
    {
		AnsiString ReturnValue;
        if(aDate == ""){
            ReturnValue = "";
        } else {
           ReturnValue = aDate.SubString(1,4)+"-"+aDate.SubString(5,2)+"-"+aDate.SubString(7,2)+
                        " "+aDate.SubString(9,2)+":"+aDate.SubString(11,2);
        }
        return  ReturnValue;
    };

    //------------------------------------------------------------------------
    BYTE __fastcall StrToHex(AnsiString sVal)
    {
        BYTE cHex = 0x00;

        for(int i=1; i<=2; i++){
            if     (sVal.SubString(i, 1) == "A") cHex |= 0x0A<<(4*(2-i));
            else if(sVal.SubString(i, 1) == "B") cHex |= 0x0B<<(4*(2-i));
            else if(sVal.SubString(i, 1) == "C") cHex |= 0x0C<<(4*(2-i));
            else if(sVal.SubString(i, 1) == "D") cHex |= 0x0D<<(4*(2-i));
            else if(sVal.SubString(i, 1) == "E") cHex |= 0x0E<<(4*(2-i));
            else if(sVal.SubString(i, 1) == "F") cHex |= 0x0F<<(4*(2-i));
            else cHex |= BYTE(StrToInt(sVal.SubString(i, 1)))<<(4*(2-i));
        }
        return cHex;
    }

   //------------------------------------------------------------------------
};

//---------------------------------------------------------------------------
extern PACKAGE TCommonF *CommonF;
//---------------------------------------------------------------------------
#endif

