//---------------------------------------------------------------------------

#ifndef MainFrmH
#define MainFrmH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "wzByte.h"
#include "wzMQueue.h"
#include "wzRWLock.h"

#include "Mios.h"
#include "SigComm.h"
#include "SigCommServer.h"
#include <Vcl.ExtCtrls.hpp>

//---------------------------------------------------------------------------
typedef struct
{
    int        SystemID;
    int        ProcessID;

    AnsiString strFtpRootPath;
	int 	   connectionTimeout;
	int 	   UseIsptDate;

	AnsiString strDataSource;
    AnsiString strUserID;
    AnsiString strPasswd;

    int  IDevSvrPort;
    int  MmiSvrPort;

	int  msgDispLevel;
	int  maxMsgLine;

}APP_CONFIG;
//---------------------------------------------------------------------------
class TMainF : public TForm
{
__published:	// IDE-managed Components
	TTimer *tmClock;
	TEdit *Edit1;
	TEdit *Edit2;
	TEdit *Edit3;
	TEdit *Edit4;
	TEdit *Edit5;
	void __fastcall tmClockTimer(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
	void __fastcall fnSysLog(TMessage Msg);
	void __fastcall fnSysLog(AnsiString strLog, int iMsgLevel);
	void __fastcall fnSigCommLog(TMessage Msg);
	void __fastcall fnSigCommLog(SIG_COMMLOG *log, int iMsgLevel);
public:		// User declarations
	String APP_HOME;
	String LOG_ROOT;
	APP_CONFIG cfg;

	TDateTime      sysTime;
	unsigned short sysYear;
    unsigned short sysMon;
	unsigned short sysDay;
    unsigned short sysHour;
    unsigned short sysMin;
    unsigned short sysSec;
	unsigned short sysMSec;

	int nSysDate;
	int nSysTime;

	double curTimeSec;

	String logDir;
	String logTime;
	unsigned short logYear;
	unsigned short logMon;
	unsigned short logDay;
//	char strSysLogFile[128];
	String strSysLogFile;

	bool __fastcall Init();
	bool __fastcall logDateChange();
    LP_IDEVINFO __fastcall GetIDevInfo(int devID);
	__fastcall TMainF(TComponent* Owner);
	void __fastcall SysLog(   AnsiString str, int iMsgLevel, bool timeStamp );
	void __fastcall SigCommLog( unsigned int mdtID, AnsiString str, int iMsgLevel, bool timeStamp );

	//================================================================
	BEGIN_MESSAGE_MAP
		VCL_MESSAGE_HANDLER(WM_SYS_LOG, TMessage, fnSysLog);
		VCL_MESSAGE_HANDLER(WM_SIGCOMM_LOG,TMessage, fnSigCommLog );
	END_MESSAGE_MAP(TForm);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainF *MainF;
extern PACKAGE wzMQueue<int,String>     SysLogQ;
extern PACKAGE wzMQueue<int,SIG_COMMLOG>   SigCommLogQ;
//---------------------------------------------------------------------------
#endif
