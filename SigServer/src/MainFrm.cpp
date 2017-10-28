//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainFrm.h"
#include "SigCommServer.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainF *MainF;
wzMQueue<int, String>    SysLogQ;
wzMQueue<int, SIG_COMMLOG>  SigCommLogQ;
//---------------------------------------------------------------------------
__fastcall TMainF::TMainF(TComponent* Owner)
	: TForm(Owner)
{
	APP_HOME = ExtractFilePath( Application->ExeName );
	APP_HOME.SetLength( APP_HOME.Length()-1 );
	LOG_ROOT = APP_HOME+"\\log";

	sysTime = Now();
	curTimeSec = sysTime.Val*86400;
	sysTime.DecodeDate( &sysYear, &sysMon, &sysDay );
	sysTime.DecodeTime( &sysHour, &sysMin, &sysSec, &sysMSec);

}

//---------------------------------------------------------------------------
// Init
//---------------------------------------------------------------------------
bool __fastcall TMainF::Init()
{
	bool ret = false;
	String strLog;
	/*
	if( TotalIDev == 0 )
	{
		LoadIDevInfo(false);
		LoadDataVersion();
		LoadIDevFtpSvrInfo();

		DB_READY = true;

		strLog.printf( "%s Create Comm Process", MODULE_NAME);
		MainF->SysLog(strLog.c_str(), 1, true);

		idevCommSvr = new IDevCommServer(cfg.IDevSvrPort);

		if( idevCommSvr->Init() )
		{
			idevCommSvr->StartProcess();

			tmClock->Enabled = true;
			tmStat->Enabled  = true;
			dtDBConnectTimeOut = Now().Val*24*60*60;
			ret = true;
		}
		else {
			ret = false;
		}
	}
	isInit = false; */

	sigCommSvr = new SigCommServer(12000);

	if( sigCommSvr->Init() )
	{
		sigCommSvr->StartProcess();

		tmClock->Enabled = true; 	// 시간 갱신
//		tmStat->Enabled  = true;
//		dtDBConnectTimeOut = Now().Val*24*60*60;
		ret = true;
	}

	return ret;
}

//---------------------------------------------------------------------------
// SysLog
//---------------------------------------------------------------------------
void __fastcall TMainF::SysLog( AnsiString str, int iMsgLevel, bool timeStamp )
{
	AnsiString strLog;
	if( timeStamp ){
		strLog.printf("[%02hu:%02hu:%02hu] %s", sysHour, sysMin, sysSec, str.c_str() );
	}
	else strLog=str;
	int key = SysLogQ.push(strLog);
    PostMessage(MainF->Handle, WM_SYS_LOG, (WPARAM)key, (LPARAM)iMsgLevel);
}


//---------------------------------------------------------------------------
void __fastcall TMainF::fnSysLog(TMessage Msg)
{
    int key = (int)Msg.WParam;
    int iMsgLevel = (int)Msg.LParam;
	String strLog;
	SysLogQ.pop(key, &strLog);
    fnSysLog(strLog, iMsgLevel);
}

//---------------------------------------------------------------------------
void __fastcall TMainF::fnSysLog(AnsiString strLog, int iMsgLevel)
{
    HANDLE     hFile;
    DWORD      dwWriteSize;

    strLog += "\r\n";
	logDateChange();
	if((hFile = CreateFile(strSysLogFile.c_str(),
						   GENERIC_READ|GENERIC_WRITE,
						   FILE_SHARE_READ,
						   NULL,
                           OPEN_ALWAYS,
                           FILE_ATTRIBUTE_NORMAL,
						   NULL)) == INVALID_HANDLE_VALUE) return;
	SetFilePointer(hFile, 0, NULL, FILE_END);
    WriteFile(hFile, strLog.c_str(), strLog.Length(), &dwWriteSize, NULL);
    CloseHandle(hFile);
}


//---------------------------------------------------------------------------
// logDateChange
//---------------------------------------------------------------------------
bool __fastcall TMainF::logDateChange()
{
	if( logYear != sysYear || logMon != sysMon || logDay != sysDay )
	{
		logYear = sysYear;
		logMon  = sysMon;
		logDay  = sysDay;
		logDir.sprintf(L"%s\\%hu-%02hu-%02hu", MainF->LOG_ROOT.c_str(), logYear, logMon, logDay);
		MkDir( logDir );
//		snprintf( strSysLogFile,   128, L"%s\\SYS.log",   logDir.c_str() );
		strSysLogFile.sprintf(L"%s\\SYS.log", logDir.c_str());
//		snprintf( strProxyLogFile, 128, "%s\\PROXY.log", logDir.c_str() );
//		snprintf( dbProc->strDbProcLogFile, 128, "%s\\DBPROC.log", MainF->logDir.c_str() );
//		snprintf( fileGenProc->strFileProcLogFile, 128, "%s\\FILEPROC.log", MainF->logDir.c_str() );
		return true;
	}
	return false;
}


//---------------------------------------------------------------------------
// IDevCommLog
//---------------------------------------------------------------------------
void __fastcall TMainF::SigCommLog( unsigned int mdtID, AnsiString str, int iMsgLevel, bool timeStamp )
{
	SIG_COMMLOG log;
	log.devID = mdtID;
    if( timeStamp ){
		//log.strLog.printf("[%s] %s", Now().FormatString("hh:nn:ss").t_str(), str.c_str() );
		log.strLog.printf(L"[%02hu:%02hu:%02hu] %s", sysHour, sysMin, sysSec, str.c_str() );
    }
    else log.strLog = str;

	int key = SigCommLogQ.push(log);
	PostMessage(Handle, WM_SIGCOMM_LOG, (WPARAM)key, (LPARAM)iMsgLevel);
}

//---------------------------------------------------------------------------
void __fastcall TMainF::fnSigCommLog(TMessage Msg)
{
    int key = (int)Msg.WParam;
	int iMsgLevel = (int)Msg.LParam;
	SIG_COMMLOG log;
	SigCommLogQ.pop(key, &log);
	fnSigCommLog( &log, iMsgLevel);
}

//---------------------------------------------------------------------------
void __fastcall TMainF::fnSigCommLog(SIG_COMMLOG *log, int iMsgLevel)
{
    HANDLE     hFile;
	DWORD      dwWriteSize;
	String strFName;
	/*
	if( ckViewIDevLog->Checked && iMsgLevel > 0 && log->devID == IDevInfos[cbIDev->ItemIndex].devID )
	{
		if(lbIDevComm->Items->Count >= MainF->cfg.maxMsgLine) lbIDevComm->Items->Delete(0);
		lbIDevComm->Items->Add(log->strLog);
		lbIDevComm->ItemIndex = lbIDevComm->Items->Count - 1;
	} */

	log->strLog += "\r\n";

	logDateChange();
	strFName.printf(L"%s\\IDEV_%05d.log", logDir.c_str(), log->devID);

	if((hFile = CreateFile(strFName.c_str(),
						   GENERIC_READ|GENERIC_WRITE,
						   FILE_SHARE_READ,
						   NULL,
						   OPEN_ALWAYS,
						   FILE_ATTRIBUTE_NORMAL,
						   NULL)) == INVALID_HANDLE_VALUE) return;
    SetFilePointer(hFile, 0, NULL, FILE_END);
    WriteFile(hFile, log->strLog.c_str(), log->strLog.Length(), &dwWriteSize, NULL);
    CloseHandle(hFile);
}

//---------------------------------------------------------------------------
LP_IDEVINFO __fastcall TMainF::GetIDevInfo(int devID)
{
	int idx;
	/*if( DB_READY )
	{
		if( IDevIndexs.get(devID, &idx ) )
		{
			return &IDevInfos[idx];
		}
	} */
	return NULL;
}

//---------------------------------------------------------------------------
void __fastcall TMainF::tmClockTimer(TObject *Sender)
{
	sysTime = Now();
	curTimeSec = sysTime.Val*24*60*60;
	sysTime.DecodeDate( &sysYear, &sysMon, &sysDay );
	sysTime.DecodeTime( &sysHour, &sysMin, &sysSec, &sysMSec);

	nSysDate =  sysYear*10000+sysMon*100+sysDay;
	nSysTime =  sysHour*10000+sysMin*100+sysSec;

//	strSysTime.printf("%d-%02d-%02d  %02d:%02d:%02d ", sysYear, sysMon, sysDay, sysHour, sysMin, sysSec);
}
//---------------------------------------------------------------------------
void __fastcall TMainF::FormShow(TObject *Sender)
{
    if( !Init() )
	{
		ShowMessage("program is already running or the port is being used by another application.");
        Close();
	}
}
//---------------------------------------------------------------------------

