// NetDemo.h : PROJECT_NAME 
//

#pragma once

#include "resource.h"
#include "NetDemoDlg.h"

extern NETDEMO_DEVICE_INFO gastDeviceInfo[NETDEMO_MAX_DEVICES];
extern CNetDemoDlg * ga_pMainDlg;//
extern int gaDeviceIndex;
extern NETDEMO_LOCAL_PARAM gstLocalParam;

void Log_WriteLog(char* p, int type, char* fmt,...);

#define NETDEMO_LOG_SUCC(p, fmt, ...)     Log_WriteLog(p,NETDEMO_OPERATION_SUCC, fmt, ##__VA_ARGS__)
#define NETDEMO_LOG_ERROR(p, fmt, ...)     Log_WriteLog(p,NETDEMO_OPERATION_FAIL, fmt, ##__VA_ARGS__)

extern bool MBToUTF8(const CHAR *pszMultiText, CHAR *pszUtf8Text, INT32 dwBufferSize);
extern bool UTF8ToMB(const CHAR *pszUtf8Text, CHAR *pszMultiText, INT32 dwBufferSize);
extern void g_SaveDeviceConfig();
extern void g_ReadDeviceConfig();
// CNetDemoApp:

class CNetDemoApp : public CWinApp
{
public:
    CNetDemoApp();

    public:
    virtual BOOL InitInstance();

    DECLARE_MESSAGE_MAP()
};

extern CNetDemoApp oNetDemoApp;