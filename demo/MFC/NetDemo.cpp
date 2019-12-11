// NetDemo.cpp : 

#include "stdafx.h"
#include "NetDemo.h"
#include "NetDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


NETDEMO_DEVICE_INFO gastDeviceInfo[NETDEMO_MAX_DEVICES];
CNetDemoDlg * ga_pMainDlg = NULL;    //
int gaDeviceIndex = 0;
NETDEMO_LOCAL_PARAM  gstLocalParam;
// CNetDemoApp

void g_SaveDeviceConfig();
void g_ReadDeviceConfig();
bool MBToUTF8(const CHAR *pszMultiText, CHAR *pszUtf8Text, INT32 dwBufferSize);
bool UTF8ToMB(const CHAR *pszUtf8Text, CHAR *pszMultiText, INT32 dwBufferSize);

BEGIN_MESSAGE_MAP(CNetDemoApp, CWinApp)
    ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


bool UTF8ToMB(const CHAR *pszUtf8Text, CHAR *pszMultiText, INT32 dwBufferSize)
{
    /* UTF-8 -> Unicode */
    INT32 dwSize = ::MultiByteToWideChar(CP_UTF8, 0, pszUtf8Text, dwBufferSize, NULL, 0);
    if (0 == dwSize)
    {
        return false;
    }

    wchar_t* wszBuffer = new wchar_t[dwSize + 1];
    ::ZeroMemory(wszBuffer, (dwSize + 1) * sizeof(wchar_t));
    if (0 == ::MultiByteToWideChar(CP_UTF8, 0, pszUtf8Text, -1, wszBuffer, dwSize + 1))
    {
        delete[] wszBuffer;
        return false;
    }

    /* Unicode -> Multi byte */
    dwSize = ::WideCharToMultiByte(CP_ACP, 0, wszBuffer, -1, NULL, 0, NULL, NULL);
    if (0 == dwSize)
    {
        delete[] wszBuffer;
        return false;
    }
    char* szBuffer = new char[dwSize + 1];
    ::ZeroMemory(szBuffer, (dwSize + 1) * sizeof(char));
    if (0 == ::WideCharToMultiByte(CP_ACP, 0, wszBuffer, -1, szBuffer, dwSize + 1, NULL, NULL))
    {
        delete[] wszBuffer;
        delete[] szBuffer;
        return false;
    }
    strncpy(pszMultiText, szBuffer, dwBufferSize);
    delete[] wszBuffer;
    delete[] szBuffer;
    return true;
}

bool MBToUTF8(const CHAR *pszMultiText, CHAR *pszUtf8Text, INT32 dwBufferSize)
{
    /* Multi byte -> Unicode*/
    INT32 dwSize = ::MultiByteToWideChar(CP_ACP,  0, pszMultiText, -1, NULL,0);
    if (0 == dwSize)
    {
        return false;
    }

    wchar_t* wszBuffer = new wchar_t[dwSize + 1];
    ::ZeroMemory(wszBuffer, (dwSize + 1) * sizeof(wchar_t));
    if (0 == ::MultiByteToWideChar(CP_ACP, 0, pszMultiText, -1, wszBuffer, dwSize + 1))
    {
        delete[] wszBuffer;
        return false;
    }

    /*Unicode->UTF8*/
    dwSize = ::WideCharToMultiByte(CP_UTF8, 0, wszBuffer, -1, NULL,0,NULL,NULL);
    if (0 == dwSize)
    {
        delete[] wszBuffer;
        return false;
    }
    char* szBuffer = new char[dwSize + 1];
    ::ZeroMemory(szBuffer, (dwSize + 1) * sizeof(char));
    if (0 == ::WideCharToMultiByte(CP_UTF8,0,wszBuffer,-1,szBuffer, dwSize + 1, NULL, NULL))
    {
        delete[] wszBuffer;
        delete[] szBuffer;
        return false;
    }

    strncpy(pszUtf8Text, szBuffer, dwBufferSize);
    delete[] wszBuffer;
    delete[] szBuffer;
    return true;
}

void Log_WriteLog(char* p, int type,char* fmt,...)
{
    if ( ga_pMainDlg->m_oClientLogList.GetItemCount() >= NETDEMO_MAX_LOGNUM)
    {
        ga_pMainDlg->m_oClientLogList.DeleteAllItems();
    }

    CTime cTime = CTime::GetCurrentTime();
    CHAR szStatus[NETDEV_LEN_32] = "Fail";
    CHAR szTime[NETDEV_LEN_64] = {0};
    CHAR szDeviceInfo[NETDEV_LEN_128] = {0};
    CHAR szErrCode[NETDEV_LEN_32] = {0};
    CHAR szOperation[NETDEV_LEN_260] = {0};
    CHAR szLog[LOG_DESCRIB_TEMP] = {0};
    INT32 dwRecode = NETDEV_GetLastError();
    INT32 dwDeviceID = ga_pMainDlg->GetCurDeviceIndex();
    _snprintf(szTime, sizeof(szTime), "%s", cTime.Format("%y-%m-%d %H:%M:%S").GetBuffer(0));

    if (dwDeviceID < 0)
    {
        strncpy(szDeviceInfo,"Please select a device", sizeof(szDeviceInfo) - 1);
    }
    else
    {
        if (NULL == p)
        {
            if (NETDEMO_LOGTYPE_LOCAL == gastDeviceInfo[dwDeviceID].dwLoginType)
            {
                _snprintf(szDeviceInfo, sizeof(szDeviceInfo), "%s (Chl : %d)", gastDeviceInfo[dwDeviceID].szIPAddr, ga_pMainDlg->GetCurChlIndex() + 1);
            }
            else
            {
                _snprintf(szDeviceInfo, sizeof(szDeviceInfo), "%s (Chl : %d)", gastDeviceInfo[dwDeviceID].stCloudDevinfo.szDevName, ga_pMainDlg->GetCurChlIndex() + 1);
            }
        }
        else
        {
            _snprintf(szDeviceInfo, sizeof(szDeviceInfo), "%s", p);
        }
    }

    switch (type)
    {
    case NETDEMO_OPERATION_SUCC:
        _snprintf(szStatus, sizeof(szStatus), "Success");
        break;
    case NETDEMO_OPERATION_FAIL:
        _snprintf(szStatus, sizeof(szStatus), "Fail");
        _snprintf(szErrCode, sizeof(szErrCode), "%d", dwRecode);
        break;
    default:
        _snprintf(szStatus, sizeof(szStatus), "Unknow");
        break;
    }

    va_list args;
    va_start(args, fmt);
    (void)_vsnprintf(szOperation, sizeof(szOperation) - 1, fmt, args);

    if (ga_pMainDlg->m_oDlgLocalSetting.m_pfLog != NULL && gstLocalParam.bAutoSaveLog)
    {
        INT32 dwsize = 0;
        if(NETDEMO_OPERATION_FAIL == type)
        {
            dwsize = _snprintf(szLog, sizeof(szLog), "[%s] [%s] %s, %s, recode:%s\n", szTime, szDeviceInfo, szOperation, szStatus,szErrCode);
        }
        else
        {
            dwsize = _snprintf(szLog, sizeof(szLog), "[%s] [%s] %s, %s\n", szTime, szDeviceInfo, szOperation, szStatus);

        }
        if (fwrite(szLog, 1, dwsize, ga_pMainDlg->m_oDlgLocalSetting.m_pfLog) != (unsigned)dwsize)
        {
            OutputDebugString("write err");
        }

        fflush(ga_pMainDlg->m_oDlgLocalSetting.m_pfLog);
    }

    if (gstLocalParam.bSuccLog || gstLocalParam.bFailLog)
    {
        if ( (0 == strcmp("Fail",szStatus)) && gstLocalParam.bFailLog)
        {
            ga_pMainDlg->m_oClientLogList.InsertItem(0, "",-1);
            ga_pMainDlg->m_oClientLogList.SetItemText(0, COL_INDEX_LOG_LIST_TIME, szTime);
            ga_pMainDlg->m_oClientLogList.SetItemText(0, COL_INDEX_LOG_LIST_DEV_INFO, szDeviceInfo);
            ga_pMainDlg->m_oClientLogList.SetItemText(0, COL_INDEX_LOG_LIST_OPERATION, szOperation);
            ga_pMainDlg->m_oClientLogList.SetItemText(0, COL_INDEX_LOG_LIST_STATUS, szStatus);
            ga_pMainDlg->m_oClientLogList.SetItemText(0, COL_INDEX_LOG_LIST_ERRCODE, szErrCode);
            ga_pMainDlg->m_oClientLogList.Invalidate();
            ga_pMainDlg->m_oClientLogList.UpdateWindow();
        }

        if ( (0 == strcmp("Success",szStatus)) && gstLocalParam.bSuccLog)
        {
            ga_pMainDlg->m_oClientLogList.InsertItem(0, "",-1);
            ga_pMainDlg->m_oClientLogList.SetItemText(0, COL_INDEX_LOG_LIST_TIME, szTime);
            ga_pMainDlg->m_oClientLogList.SetItemText(0, COL_INDEX_LOG_LIST_DEV_INFO, szDeviceInfo);
            ga_pMainDlg->m_oClientLogList.SetItemText(0, COL_INDEX_LOG_LIST_OPERATION, szOperation);
            ga_pMainDlg->m_oClientLogList.SetItemText(0, COL_INDEX_LOG_LIST_STATUS, szStatus);
            ga_pMainDlg->m_oClientLogList.SetItemText(0, COL_INDEX_LOG_LIST_ERRCODE, szErrCode);
            ga_pMainDlg->m_oClientLogList.Invalidate();
            ga_pMainDlg->m_oClientLogList.UpdateWindow();
        }
    }

    return;
}


CNetDemoApp::CNetDemoApp()
{

}

CNetDemoApp oNetDemoApp;

BOOL CNetDemoApp::InitInstance()
{
    INITCOMMONCONTROLSEX InitCtrls;
    InitCtrls.dwSize = sizeof(InitCtrls);
    InitCtrls.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&InitCtrls);

    CWinApp::InitInstance();

    AfxEnableControlContainer();

    CNetDemoDlg dlg;
    m_pMainWnd = &dlg;
    INT_PTR nResponse = dlg.DoModal();
    if (nResponse == IDOK)
    {

    }
    else if (nResponse == IDCANCEL)
    {

    }

    return FALSE;
}

int g_buflen(char *buf)
{
    char *pszPos = NULL;
    int iBufLen = 0;
    pszPos = strchr(buf, '\r');
    if (pszPos != NULL)
    {
        iBufLen = pszPos - buf;
        return iBufLen;
    }
    pszPos = strchr(buf, '\n');
    if (pszPos != NULL)
    {
        iBufLen = pszPos - buf;
    }

    return iBufLen;
}

void g_SaveDeviceConfig()
{
    INT32 i = 0;
    INT32 j = 0;
    char buf[NETDEV_LEN_128] = {0};
    CStdioFile oFile;

    if (oFile.Open(NETDEMO_DEV_CFG_FILE_NAME, CFile::modeCreate|CFile::modeWrite) == FALSE)
    {
        return;
    }
    for (i = 0,j = 0; i < NETDEMO_MAX_DEVICES; i++)
    {
        if (gastDeviceInfo[i].dwMaxChnNum != -1) //find dev
        {
            sprintf(buf,"$S\r\n");
            oFile.WriteString(buf);

            sprintf(buf,"%d\r\n",j);
            oFile.WriteString(buf);
            
            //save local dev info
            sprintf(buf,"%d\r\n",gastDeviceInfo[i].dwLoginType);
            oFile.WriteString(buf);
            sprintf(buf,"%d\r\n",gastDeviceInfo[i].dwMaxChnNum);
            oFile.WriteString(buf);

            sprintf(buf,"%s\r\n",gastDeviceInfo[i].szIPAddr);
            oFile.WriteString(buf);

            sprintf(buf,"%d\r\n",gastDeviceInfo[i].dwDevPort);
            oFile.WriteString(buf);

            sprintf(buf,"%s\r\n",gastDeviceInfo[i].szDevUserName);
            oFile.WriteString(buf);

            sprintf(buf,"%s\r\n",gastDeviceInfo[i].szPassword);
            oFile.WriteString(buf);

            //save local dev ifno
            sprintf(buf,"%d\r\n",gastDeviceInfo[i].stDevInfo.dwDevType);
            oFile.WriteString(buf);

            sprintf(buf,"%d\r\n",gastDeviceInfo[i].stDevInfo.dwChannelNum);
            oFile.WriteString(buf);

            sprintf(buf,"%d\r\n",gastDeviceInfo[i].stDevInfo.wAlarmInPortNum);
            oFile.WriteString(buf);

            sprintf(buf,"%d\r\n",gastDeviceInfo[i].stDevInfo.wAlarmOutPortNum);
            oFile.WriteString(buf);

            //save cloud  info
            sprintf(buf,"%s\r\n",gastDeviceInfo[i].szCloudUrl);
            oFile.WriteString(buf);
            sprintf(buf,"%s\r\n",gastDeviceInfo[i].szCloudName);
            oFile.WriteString(buf);
            sprintf(buf,"%s\r\n",gastDeviceInfo[i].szCloudPasswd);
            oFile.WriteString(buf);

            //save cloud dev info
            sprintf(buf,"%s\r\n",gastDeviceInfo[i].stCloudDevinfo.szIPAddr);
            oFile.WriteString(buf);
            sprintf(buf,"%s\r\n",gastDeviceInfo[i].stCloudDevinfo.szDevUserName);
            oFile.WriteString(buf);
            sprintf(buf,"%s\r\n",gastDeviceInfo[i].stCloudDevinfo.szDevName);
            oFile.WriteString(buf);
            sprintf(buf,"%s\r\n",gastDeviceInfo[i].stCloudDevinfo.szDevModel);
            oFile.WriteString(buf);
            sprintf(buf,"%s\r\n",gastDeviceInfo[i].stCloudDevinfo.szDevSerialNum);
            oFile.WriteString(buf);
            sprintf(buf,"%d\r\n",gastDeviceInfo[i].stCloudDevinfo.dwOrgID);
            oFile.WriteString(buf);
            sprintf(buf,"%d\r\n",gastDeviceInfo[i].stCloudDevinfo.dwDevPort);
            oFile.WriteString(buf);
            j++;
        }
    }

    oFile.Close();

    return;
}


VOID g_ReadDeviceConfig()
{
    char buf[NETDEV_LEN_128] = {0};
    CStdioFile oFile;

    if (oFile.Open(NETDEMO_DEV_CFG_FILE_NAME, CFile::modeRead) == FALSE)
    {
        oFile.Open(NETDEMO_DEV_CFG_FILE_NAME, CFile::modeCreate);
        return;
    }

    while (oFile.ReadString(buf, NETDEV_LEN_128))//25
    {
        if (buf[1]==0x53)
        {
            INT32 dwValue = 0;
            oFile.ReadString(buf,NETDEV_LEN_128);
            INT32 i = atoi(buf);
            gastDeviceInfo[i].dwDeviceIndex = i;
            oFile.ReadString(buf,NETDEV_LEN_128);
            gastDeviceInfo[i].dwLoginType = (NETDEMO_DEV_LOGIN_TYPE)atoi(buf);
            oFile.ReadString(buf,NETDEV_LEN_128);
            gastDeviceInfo[i].dwMaxChnNum = (NETDEMO_DEV_LOGIN_TYPE)atoi(buf);

            gastDeviceInfo[i].pstChlInfo = new NETDEMO_CHANNEL_INFO[gastDeviceInfo[i].dwMaxChnNum];
            for (INT32 i = 0; i < gastDeviceInfo[i].dwMaxChnNum; i++)
            {
                gastDeviceInfo[i].pstChlInfo[i].dwChlID = i + 1;
            }

            oFile.ReadString(buf,NETDEV_LEN_128);
            strncpy(gastDeviceInfo[i].szIPAddr, buf,g_buflen(buf));

            oFile.ReadString(buf,NETDEV_LEN_128);
            gastDeviceInfo[i].dwDevPort = (NETDEMO_DEV_LOGIN_TYPE)atoi(buf);

            oFile.ReadString(buf,NETDEV_LEN_128);
            strncpy(gastDeviceInfo[i].szDevUserName, buf,g_buflen(buf));

            oFile.ReadString(buf,NETDEV_LEN_128);
            strncpy(gastDeviceInfo[i].szPassword, buf,g_buflen(buf));
            
            //read local dev ifno
            oFile.ReadString(buf,NETDEV_LEN_128);
            dwValue = atoi(buf);
            gastDeviceInfo[i].stDevInfo.dwDevType = dwValue;

            oFile.ReadString(buf,NETDEV_LEN_128);
            dwValue = atoi(buf);
            gastDeviceInfo[i].stDevInfo.dwChannelNum = dwValue;
            
            oFile.ReadString(buf,NETDEV_LEN_128);
            dwValue = atoi(buf);
            gastDeviceInfo[i].stDevInfo.wAlarmInPortNum = dwValue;
            
            oFile.ReadString(buf,NETDEV_LEN_128);
            dwValue = atoi(buf);
            gastDeviceInfo[i].stDevInfo.wAlarmOutPortNum = dwValue;

            //read Cloud Info
            oFile.ReadString(buf,NETDEV_LEN_128);
            strncpy(gastDeviceInfo[i].szCloudUrl, buf,g_buflen(buf));
            oFile.ReadString(buf,NETDEV_LEN_128);
            strncpy(gastDeviceInfo[i].szCloudName, buf,g_buflen(buf));
            oFile.ReadString(buf,NETDEV_LEN_128);
            strncpy(gastDeviceInfo[i].szCloudPasswd, buf,g_buflen(buf));

            //read Cloud Dev
            oFile.ReadString(buf,NETDEV_LEN_128);
            strncpy(gastDeviceInfo[i].stCloudDevinfo.szIPAddr, buf,g_buflen(buf));
            oFile.ReadString(buf,NETDEV_LEN_128);
            strncpy(gastDeviceInfo[i].stCloudDevinfo.szDevUserName, buf,g_buflen(buf));
            oFile.ReadString(buf,NETDEV_LEN_128);
            strncpy(gastDeviceInfo[i].stCloudDevinfo.szDevName, buf,g_buflen(buf));
            oFile.ReadString(buf,NETDEV_LEN_128);
            strncpy(gastDeviceInfo[i].stCloudDevinfo.szDevModel, buf,g_buflen(buf));
            oFile.ReadString(buf,NETDEV_LEN_128);
            strncpy(gastDeviceInfo[i].stCloudDevinfo.szDevSerialNum, buf,g_buflen(buf));
            oFile.ReadString(buf,NETDEV_LEN_128);
            gastDeviceInfo[i].dwOrgID = atoi(buf);
            oFile.ReadString(buf,NETDEV_LEN_128);
            gastDeviceInfo[i].dwDevPort = atoi(buf);
        }
    }

    return;
}
