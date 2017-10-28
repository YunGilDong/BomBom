//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CommonFrm.h"
#include "MainU.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TCommonF *CommonF;

//---------------------------------------------------------------------------
void execCmd(AnsiString cmd)
{ 
    HWND                    hdWindow;
    STARTUPINFO             siParam;
    PROCESS_INFORMATION     piParam;
    DWORD                   dwExitCode;

    // 초기화
    FillMemory(&siParam, sizeof(STARTUPINFO), 0);
    FillMemory(&piParam, sizeof(PROCESS_INFORMATION), 0);

    // Param 섯팅
    siParam.cb          = sizeof(STARTUPINFO);
    siParam.dwFlags     = STARTF_USESHOWWINDOW;
    siParam.wShowWindow = SW_SHOW;

    CreateProcess(NULL, cmd.c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &siParam, &piParam);
    /*
    // 프로세스가 종료될때까지 대기함
    WaitForInputIdle(GetCurrentProcess(), INFINITE);
    if(piParam.hProcess)
    {
        dwExitCode = STILL_ACTIVE;

        while(dwExitCode == STILL_ACTIVE)
        {
            WaitForSingleObject(piParam.hProcess, 1000);
            GetExitCodeProcess(piParam.hProcess, &dwExitCode);
            UpdateWindow(Handle);
        }
    }
    */
}


//---------------------------------------------------------------------------
__fastcall TCommonF::TCommonF(TComponent* Owner) : TForm(Owner)
{
}

//---------------------------------------------------------------------------
// HH:MM
//---------------------------------------------------------------------------
void __fastcall TCommonF::StrToHHMM(AnsiString str, int* HH, int* MM)
{
    AnsiString strHour;
    AnsiString strMin;

    strHour  = str.SubString(1,2);
    strMin   = str.SubString(4,2);
    *HH = StrToIntDef( strHour, 0);
    *MM = StrToIntDef( strMin, 0);
}

//---------------------------------------------------------------------------
// YYYYMMDDHHMMSS
//---------------------------------------------------------------------------
void __fastcall TCommonF::StrToDateByte(AnsiString str, char* bDate )
{
	bDate[0] = StrToIntDef( str.SubString( 3, 2), 0);
	bDate[1] = StrToIntDef( str.SubString( 5, 2), 0);
	bDate[2] = StrToIntDef( str.SubString( 7, 2), 0);
	bDate[3] = StrToIntDef( str.SubString( 9, 2), 0);
	bDate[4] = StrToIntDef( str.SubString(11, 2), 0);
	bDate[5] = StrToIntDef( str.SubString(13, 2), 0);
}

//---------------------------------------------------------------------------
bool __fastcall TCommonF::IsGridEmpty(TAdvStringGrid *G)
{
    int iCnt;
    if(G->RowCount == G->FixedRows + 1){
        for(iCnt=0; iCnt<G->ColCount; iCnt++){
            if(G->Cells[iCnt][G->FixedRows].Length() > 0) break;
        }
        if(iCnt == G->ColCount) return true;
        return false;
    }
    return false;
}
//---------------------------------------------------------------------------
void __fastcall TCommonF::ClearGrid(TAdvStringGrid *G)
{
    G->RowCount = G->FixedRows + 1;
    for(int iCnt=0; iCnt<G->ColCount; iCnt++)
        G->Cells[iCnt][G->FixedRows] = "";
}
//---------------------------------------------------------------------------
// Datetime 을 각 에디트 박스에 넣어주기
void  __fastcall TCommonF::SetDateTime(AnsiString sTime,TEdit * pDatetime,
      TEdit * pTime, TEdit * pMin)
{
    /*
    if(sTime.Trim() == ""){
        pDatetime->SetDate(0,0,0);
        pTime->Text      = "00";
        pMin->Text       = "00";
    } else {
        pDatetime->SetDate(StrToInt(sTime.SubString(1,4)),StrToInt(sTime.SubString(5,2)) ,StrToInt(sTime.SubString(7,2)) );
        pTime->Text = sTime.SubString(9,2);
        pMin->Text  = sTime.SubString(11,2);
    }
    */
}

//---------------------------------------------------------------------------
AnsiString  __fastcall TCommonF::MakeDateTime(TEdit * pDatetime, TEdit * pTime, TEdit * pMin)
{
    AnsiString ReturnValue, yy,mm,dd,hh,mi;
    /*
    if(pDatetime->Year.Trim().Length() <= 3 ){
        ReturnValue = " ";
    } else {
        yy = FormatFloat("0000",StrToInt(pDatetime->Year));
        mm = FormatFloat("00"  ,StrToInt(pDatetime->Month));
        dd = FormatFloat("00"  ,StrToInt(pDatetime->Day));
        if(pTime->Text.Trim().Length() == 0){
           hh = "00";
        } else {
           hh = FormatFloat("00",StrToInt(pTime->Text));
        }
        if(pMin->Text.Trim().Length() == 0){
           mi = "00";
        } else {
           mi = FormatFloat("00",StrToInt(pMin->Text));
        }
        ReturnValue = yy+mm+dd+hh+mi;
    }
    */
    return ReturnValue;
}

//---------------------------------------------------------------------------
AnsiString  __fastcall TCommonF::SubString(const AnsiString* str, char c)
{
    AnsiString retStr;
    char* pStr = str->c_str();
    int len = str->Length();

    for( int i=0; i<len; i++)
    {
        if( pStr[i]==c){
            retStr = str->SubString(0, i);
            return retStr;
        }
    }
    retStr = *str;
    return retStr;
}

//---------------------------------------------------------------------------
// Grid 를 CSV 파일로 저장하기
//---------------------------------------------------------------------------
void __fastcall TCommonF::SaveGridToCSV(TAdvStringGrid * SG)
{
    TSaveDialog * SD = new TSaveDialog(this);
    SD->DefaultExt = "csv";
    SD->InitialDir = GetCurrentDir();
    if(!SD->Execute()){return;}
    TFileStream * FS = new TFileStream(SD->FileName,fmCreate);
    AnsiString sTmp;
    for (int i=0;i< SG->RowCount ;i++){
        sTmp = "";
        for(int j=0;j< SG->ColCount ;j++){
            sTmp += SG->Cells[j][i]+",";
        }
        sTmp += "\r\n";
        FS->Write(sTmp.c_str(),sTmp.Length());
    }
    delete FS;
}

//---------------------------------------------------------------------------
void __fastcall TCommonF::DateTimeToFileTime(const TDateTime *localDateTime, FILETIME* utcFileTime)
{
    SYSTEMTIME  localSystemTime;
    FILETIME    localFileTime;

    if( localDateTime != NULL){
        DateTimeToSystemTime(*localDateTime,   localSystemTime);
        SystemTimeToFileTime(&localSystemTime, &localFileTime);
        LocalFileTimeToFileTime(&localFileTime, utcFileTime); // LocalFileTime => UTC Base
    }
    else
    {
        utcFileTime->dwLowDateTime  = 0;
        utcFileTime->dwHighDateTime = 0;
    }
}

//---------------------------------------------------------------------------
bool __fastcall TCommonF::GetFileDateStr(const char *fileName, AnsiString* strDate)
{
    FILETIME ftCreationTime, ftLastAccessTime, ftLastWriteTime;
    TDateTime dateTime;
    FILETIME ftLocalFileTime;
    SYSTEMTIME lastWriteTime;

    HANDLE hFile;
    hFile=(void *)FileOpen( fileName, fmOpenWrite );
    if( hFile < 0 ) return false;
    GetFileTime( hFile, &ftCreationTime, &ftLastAccessTime, &ftLastWriteTime );

    FileTimeToLocalFileTime(&ftLastWriteTime, &ftLocalFileTime);  //UTC => Local Time
    FileTimeToSystemTime( &ftLocalFileTime, &lastWriteTime );
    strDate->sprintf("%4d-%02d-%02d %02d:%02d:%02d",
                        lastWriteTime.wYear,lastWriteTime.wMonth, lastWriteTime.wDay,
                        lastWriteTime.wHour,lastWriteTime.wMinute,lastWriteTime.wSecond);

    FileClose((int)hFile);
    return true;
}

//---------------------------------------------------------------------------
bool __fastcall TCommonF::SetFileDateStr(const char *fileName, AnsiString strDate)
{
    FILETIME ftCreationTime, ftLastAccessTime, ftLastWriteTime;
    TDateTime dateTime;

    HANDLE hFile;
    hFile=(void *)FileOpen( fileName, fmOpenWrite );
    if( hFile < 0 ) return false;
    GetFileTime( hFile, &ftCreationTime, &ftLastAccessTime, &ftLastWriteTime );

    dateTime = StrToDateTime(strDate);
    DateTimeToFileTime( &dateTime, &ftLastWriteTime);
    SetFileTime( hFile, &ftCreationTime, &ftLastAccessTime, &ftLastWriteTime );
    FileClose((int)hFile);
    return true;
}

//---------------------------------------------------------------------------
bool __fastcall TCommonF::SetFileDate(const char *fileName, int year, int mon, int day, int hour, int min, int sec)
{
    FILETIME creationTime, lastAccessTime, lastWriteTime;
    TDateTime dateTime;

    HANDLE hFile;
    hFile=(void *)FileOpen( fileName, fmOpenWrite );
    GetFileTime( hFile, &creationTime, &lastAccessTime, &lastWriteTime );

	dateTime = EncodeDateTime(year, mon, day, hour, min, sec, 100);
    DateTimeToFileTime( &dateTime, &lastWriteTime);
    SetFileTime( hFile, &creationTime, &lastAccessTime, &lastWriteTime );
    FileClose((int)hFile);
    return true;
}

//---------------------------------------------------------------------------
bool __fastcall TCommonF::ExistFile(AnsiString filePath, AnsiString regDate)
{
    AnsiString strDate;
    if( GetFileDateStr(filePath.c_str(), &strDate) )
    {        
        if( regDate == strDate )
        {
            return true;           
        }
    }
    return false;
}

//---------------------------------------------------------------------------
bool __fastcall TCommonF::FindFile(AnsiString dir, AnsiString fileName, AnsiString regDate)
{
    TSearchRec sr;
    int iAttributes = 0;
    SYSTEMTIME lastWriteTime;
    FILETIME localFileTime;
    AnsiString strDate;
    bool result=false;

    iAttributes |= faReadOnly;
    iAttributes |= faHidden;
    //iAttributes |= faSysFile;
    //iAttributes |= faVolumeID;
    //iAttributes |= faDirectory;
    iAttributes |= faArchive;
    iAttributes |= faAnyFile;

    if (FindFirst(dir+"\\*.*", iAttributes, sr) == 0)
    {
        do
        {
            if( (sr.Attr & faDirectory) == 0)
            {
                if( sr.Name == fileName )
                {
                    FileTimeToLocalFileTime(&sr.FindData.ftLastWriteTime, &localFileTime);  //UTC => Local Time
                    FileTimeToSystemTime( &localFileTime, &lastWriteTime );
                    strDate.sprintf("%4d-%02d-%02d %02d:%02d:%02d",
                        lastWriteTime.wYear,lastWriteTime.wMonth, lastWriteTime.wDay,
                        lastWriteTime.wHour,lastWriteTime.wMinute,lastWriteTime.wSecond);
                    if( strDate == regDate ) {
                        result=true;
                        break;
                    }
                }
            }
        } while ( FindNext(sr) == 0);
        FindClose(sr);
    }
    return result;
}


//---------------------------------------------------------------------------
// 데이터 베이스 FUNCTION
//---------------------------------------------------------------------------
void __fastcall TCommonF::SetDB(TSQLConnection *dbase)
{
    DB = dbase;
}

bool __fastcall TCommonF::IsDbConnected()
{
    return DB->Connected;
}

void __fastcall TCommonF::SetLogDir(AnsiString dir)
{
    logDir = dir;
}

//---------------------------------------------------------------------------
int  __fastcall TCommonF::ExecSQL(TSQLQuery *pQry)
{
    int iOraErr;
    int iResult = -1;

    try{
        if(!DB->Connected) return ORAERR_NOT_CONNECTED;
        if(pQry->Active) pQry->Close();
        pQry->ExecSQL();
        iResult = pQry->RowsAffected;
    }catch(const Exception &E){
        iOraErr = GetOracleError(E.Message);
        iResult = GetOracleErrorResult( iOraErr );
        WriteQueryError(E.Message, pQry->SQL->Text);
    }
    return iResult;
}

//---------------------------------------------------------------------------
int  __fastcall TCommonF::ExecSQL(TSQLQuery *pQry, AnsiString strSql)
{
    int iOraErr;
    int iResult = -1;

    try{
        if(!DB->Connected) return ORAERR_NOT_CONNECTED;
        if(pQry->Active) pQry->Close();
        pQry->SQL->Text = strSql;

        pQry->ExecSQL();
        iResult = pQry->RowsAffected;
    }catch(const Exception &E){
        iOraErr = GetOracleError(E.Message);
        iResult = GetOracleErrorResult( iOraErr );
        WriteQueryError(E.Message, strSql);
    }
    return iResult;
}

//---------------------------------------------------------------------------
int  __fastcall TCommonF::OpenSQL(TSQLQuery *pQry, AnsiString strSql)
{
    int iOraErr;
    int iResult = 1;

    try{
        if(!DB->Connected) return ORAERR_NOT_CONNECTED;
        if(pQry->Active) pQry->Close();
        pQry->SQL->Text = strSql;
        pQry->Open();
    }catch(const Exception &E){
		iOraErr = GetOracleError(E.Message);
		//ShowMessage( iOraErr );
		iResult = GetOracleErrorResult( iOraErr );
		WriteQueryError(E.Message, strSql);
		//ShowMessage( iResult );
    }
	return iResult;
}

//---------------------------------------------------------------------------
int  __fastcall TCommonF::OpenSQL(TSQLQuery *pQry)
{
    int iOraErr;
	int iResult = 1;

    try{
        if(!DB->Connected) return ORAERR_NOT_CONNECTED;
        if(pQry->Active) pQry->Close();
        pQry->Open();
	}catch(const Exception &E){
        iOraErr = GetOracleError(E.Message);
        iResult = GetOracleErrorResult( iOraErr );
        WriteQueryError(E.Message, pQry->SQL->Text);
    }
    return iResult;
}

//---------------------------------------------------------------------------
int  __fastcall TCommonF::GetOracleError(AnsiString sErrMsg)
{
    int iErrNo = 0;
    for(int i=1; i<sErrMsg.Length()-7; i++)
    {
        if(sErrMsg.SubString(i, 4) == "ORA-"){
            iErrNo = StrToIntDef( sErrMsg.SubString(i+4, 5), 0);
            break;
        }
    }
    return iErrNo;
}

//---------------------------------------------------------------------------
int  __fastcall TCommonF::GetOracleErrorResult(int iOraErrCode)
{
	int iResult;
	switch( iOraErrCode )
	{
		case 1012	: iResult = ORAERR_NOT_LOGGED_ON;  break;
		case 3114	:
		case 12150	:
		case 12151	:
		case 12152	:
		case 12153  : iResult = ORAERR_NOT_CONNECTED;  break;
		default		: iResult = 1;
	}
	return iResult;
}

//---------------------------------------------------------------------------
void __fastcall TCommonF::WriteQueryError(AnsiString strOraErr, AnsiString strSql)
{
    HANDLE     hFile;
    DWORD      dwWriteSize;
    AnsiString strFName;
    AnsiString strMsg;

	//strFName = logDir + "\\ESQL_" + Now().FormatString("yyyy-mm-dd") + ".txt";

	strFName.printf("%s\\ORAERR_%hu-%02hu-%02hu.txt",
		MainF->LOG_ROOT, MainF->sysYear, MainF->sysMon, MainF->sysDay );
    if((hFile = CreateFile(strFName.c_str(),
                        GENERIC_READ|GENERIC_WRITE,
                        FILE_SHARE_READ,
                        NULL,
                        OPEN_ALWAYS,
                        FILE_ATTRIBUTE_NORMAL,
						NULL)) == INVALID_HANDLE_VALUE) return;

    SetFilePointer(hFile, 0, NULL, FILE_END);
    strMsg = Now().FormatString("yyyy-mm-dd hh:nn:ss") + "\r\n";
    WriteFile(hFile, strMsg.c_str(), strMsg.Length(), &dwWriteSize, NULL);
    strMsg = strOraErr + "\r\n";
    WriteFile(hFile, strMsg.c_str(), strMsg.Length(), &dwWriteSize, NULL);
    strMsg = strSql + "\r\n";
    WriteFile(hFile, strMsg.c_str(), strMsg.Length(), &dwWriteSize, NULL);
    CloseHandle(hFile);
}

//---------------------------------------------------------------------------
void __fastcall TCommonF::StringSplit(AnsiString str, char delim, TStringList* result)
{ 
    AnsiString strTemp;
    int len=0;

    result->Clear();
    char* ptr = str.c_str();
    while ( *ptr != NULL )
    {
        if ( *ptr != delim ){
            strTemp += *ptr;
            len++;
        }
        if( *ptr == delim && len > 0  )
        {
            result->Add(strTemp);
            strTemp = "";
            len = 0;
        }
        ptr++;
    }
    if(len > 0 ) result->Add(strTemp);
} 

//---------------------------------------------------------------------------
void __fastcall TCommonF::ExtractDateTime(TDateTime  dtDate, AnsiString strHHMISS, TDateTime *rtDateTime )
{
    *rtDateTime = dtDate + StrToTime(strHHMISS);
    return;
}

//---------------------------------------------------------------------------
void __fastcall TCommonF::ExtractDateTime( TDateTime  dtDate, AnsiString strHH, 
											AnsiString strMI, AnsiString strSS, TDateTime *rtDateTime )
{
    AnsiString strHHMISS;
    strHHMISS.printf("%s:%s:%s", strHH, strMI, strSS);
    ExtractDateTime( dtDate,strHHMISS,rtDateTime );
    return;
}

//---------------------------------------------------------------------------
void __fastcall TCommonF::ExtractDateTime( AnsiString strYYYY, AnsiString strMM, 
										   AnsiString strDD, AnsiString strHH,   
										   AnsiString strMI, AnsiString strSS, TDateTime *rtDateTime )
{
    AnsiString str;
    TDateTime dtYMD;
    AnsiString strHHMISS;

    str.printf( "%s-%s-%s",strYYYY, strMM, strDD ) ;
    strHHMISS.printf("%s:%s:%s", strHH, strMI, strSS);
    ExtractDateTime( StrToDate(str),strHHMISS,rtDateTime );
    return;
}

//---------------------------------------------------------------------------
void __fastcall TCommonF::ExtractDateTime(  TDateTime  dtDate, bool bFirst /* 시작 : true 마지막 : false */, 
											TDateTime *rtDateTime )
{
    AnsiString strHH;
    if( bFirst ) strHH = "00";
    else         strHH = "23";

    ExtractDateTime( dtDate, strHH, bFirst, rtDateTime );
    return;
}

//---------------------------------------------------------------------------
void __fastcall TCommonF::ExtractDateTime(TDateTime  dtDate, AnsiString strHH, 
										  bool bFirst /* 시작 : true 마지막 : false */, TDateTime *rtDateTime )
{
    AnsiString strTemp;

    if( strHH == "00" ) strTemp = strHH;
    else if( strHH == "01" ) strTemp = strHH;
    else if( strHH == "02" ) strTemp = strHH;
    else if( strHH == "03" ) strTemp = strHH;
    else if( strHH == "04" ) strTemp = strHH;
    else if( strHH == "05" ) strTemp = strHH;
    else if( strHH == "06" ) strTemp = strHH;
    else if( strHH == "07" ) strTemp = strHH;
    else if( strHH == "08" ) strTemp = strHH;
    else if( strHH == "09" ) strTemp = strHH;
    else if( strHH == "10" ) strTemp = strHH;
    else if( strHH == "11" ) strTemp = strHH;
    else if( strHH == "12" ) strTemp = strHH;
    else if( strHH == "13" ) strTemp = strHH;
    else if( strHH == "14" ) strTemp = strHH;
    else if( strHH == "15" ) strTemp = strHH;
    else if( strHH == "16" ) strTemp = strHH;
    else if( strHH == "17" ) strTemp = strHH;
    else if( strHH == "18" ) strTemp = strHH;
    else if( strHH == "19" ) strTemp = strHH;
    else if( strHH == "20" ) strTemp = strHH;
    else if( strHH == "21" ) strTemp = strHH;
    else if( strHH == "22" ) strTemp = strHH;
    else if( strHH == "23" ) strTemp = strHH;
    else    strTemp = "23";

    if( bFirst ) *rtDateTime = dtDate + StrToTime(strTemp + ":00:00");
    else         *rtDateTime = dtDate + StrToTime(strTemp + ":59:59");
    
    return;
}
//---------------------------------------------------------------------------


