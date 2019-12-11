
#include "stdafx.h"
#include "NetDemo.h"
#include "DlgLocalSetting.h"
#include <Shlwapi.h>
IMPLEMENT_DYNAMIC(CDlgLocalSetting, CDialog)


CString GetCurrentPath()
{
    char szExePathName[255] = {0};
    char szExePath[255] = {0};
    char szExeName[255] = {0};
    char szExeDrive[16] = {0};
    char szExeExt[16] = {0};

    GetModuleFileName(NULL, szExePathName, sizeof(szExePathName));
    _splitpath(szExePathName,szExeDrive,szExePath,szExeName,szExeExt);

    char szIniPathName[255] = {0};
    char szTmpFolderName[255] = {0};
    char szCurrentExePath[260] = {0};

    strncpy(szIniPathName,szExeDrive, sizeof(szIniPathName) - 1);
    strcat(szIniPathName,szExePath);

    strncpy(szTmpFolderName, szIniPathName, sizeof(szTmpFolderName) - 1);
    strncpy(szCurrentExePath, szIniPathName, sizeof(szCurrentExePath) - 1);

    CString strCurrentPath;
    strCurrentPath.Format("%s",szCurrentExePath);

    return strCurrentPath;
}

CDlgLocalSetting::CDlgLocalSetting(CWnd* pParent /*=NULL*/)
    : CDialog(CDlgLocalSetting::IDD, pParent)
    , m_bChkAutoSaveLog(TRUE)
    , m_bChkFailLog(TRUE)
    , m_bChkSuccLog(TRUE)
{
    m_pfLog = NULL;
    m_dwWaitTime = 15;
    m_dwTryTimes = 3;
    m_dwReceiveTimeout = 5;
    m_dwFileTimeout = 60;

    CString strCurrentPath = GetCurrentPath();
    m_strLogPath = strCurrentPath + "\\log";
    m_strSnapshotPath = strCurrentPath + "\\Pic";
    m_strLocalRecordPath = strCurrentPath + "\\Record";

    CreateDirectory(m_strLogPath, NULL);
    CreateDirectory(m_strSnapshotPath, NULL);
    CreateDirectory(m_strLocalRecordPath, NULL);

    strncpy(gstLocalParam.szLogpath, m_strLogPath.GetBuffer(0), sizeof(gstLocalParam.szLogpath) - 1);
    strncpy(gstLocalParam.szLocalRecordPath, m_strLocalRecordPath.GetBuffer(0), sizeof(gstLocalParam.szLocalRecordPath) - 1);
    strncpy(gstLocalParam.szPictureSavePath, m_strSnapshotPath.GetBuffer(0), sizeof(gstLocalParam.szPictureSavePath) - 1);

    CreateNewLogFile(m_bChkAutoSaveLog);

    m_bRatioMain = TRUE;
    m_bRatioSub = FALSE;
    m_bRatioThird = TRUE;
}

CDlgLocalSetting::~CDlgLocalSetting()
{
    if (NULL != m_pfLog)
    {
        fclose(m_pfLog);
    }
}

void CDlgLocalSetting::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_LOG_PATH, m_strLogPath);
    DDX_Text(pDX, IDC_EDIT_SNAPSHOT_PATH, m_strSnapshotPath);
    DDX_Text(pDX, IDC_EDIT_RECORD_PATH, m_strLocalRecordPath);
    DDX_Text(pDX, IDC_EDIT_WAIT_TIME, m_dwWaitTime);
    DDX_Text(pDX, IDC_EDIT_TRY_TIME, m_dwTryTimes);
    DDX_Text(pDX, IDC_EDIT_RECEIVE_TIMEOUT, m_dwReceiveTimeout);
    DDX_Text(pDX, IDC_EDIT_FILE_TIMEOUT, m_dwFileTimeout);
    DDX_Check(pDX, IDC_CHECK_AUTO_SAVE_LOG, m_bChkAutoSaveLog);
    DDX_Check(pDX, IDC_CHECK_SUCCESSFUL_LOG, m_bChkSuccLog);
    DDX_Check(pDX, IDC_CHECK_FAILURE_LOG, m_bChkFailLog);
    DDX_Radio(pDX, IDC_RADIO_MAIN_STREAM, m_bRatioMain);
    DDX_Radio(pDX, IDC_RADIO_SUB_STREAM, m_bRatioSub);
    DDX_Radio(pDX, IDC_RADIO_THIRD_STREAM, m_bRatioThird);
}


BEGIN_MESSAGE_MAP(CDlgLocalSetting, CDialog)
    ON_BN_CLICKED(IDC_BUTTON_SET_LOGPATH, &CDlgLocalSetting::OnBnClickedButtonSetLogpath)
    ON_BN_CLICKED(IDC_BUTTON_SET_OPREATION_LOG, &CDlgLocalSetting::OnBnClickedButtonSetOperationLog)
    ON_BN_CLICKED(IDC_BUTTON_SET_KEEPLIVE, &CDlgLocalSetting::OnBnClickedButtonSetKeeplive)
    ON_BN_CLICKED(IDC_BUTTON_SET_TIMEOUT, &CDlgLocalSetting::OnBnClickedButtonSetTimeout)
    ON_BN_CLICKED(IDC_BTN_SAVE_STREAM_TYPE, &CDlgLocalSetting::OnBnClickedBtnSaveStreamType)
END_MESSAGE_MAP()


void CDlgLocalSetting::OnBnClickedButtonSetLogpath()
{
    UpdateData(TRUE);
    if (INVALID_FILE_ATTRIBUTES == GetFileAttributes(m_strLogPath))
    {
        if (0 == CreateDirectory(m_strLogPath, NULL))
        {
            NETDEMO_LOG_ERROR(NULL, "Invalid Log Path");
            return;
        }
    }

    if (INVALID_FILE_ATTRIBUTES == GetFileAttributes(m_strLocalRecordPath))
    {
        if (0 == CreateDirectory(m_strLocalRecordPath, NULL))
        {
            NETDEMO_LOG_ERROR(NULL, "Invalid record path");
            return;
        }
    }

    if (INVALID_FILE_ATTRIBUTES == GetFileAttributes(m_strSnapshotPath))
    {
        if (0 == CreateDirectory(m_strSnapshotPath, NULL))
        {
            NETDEMO_LOG_ERROR(NULL, "Invalid snapshot path");
            return;
        }
    }

    BOOL bRet = NETDEV_SetLogPath(m_strLogPath.GetBuffer());
    if (TRUE !=bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Set log path");
    }
    else
    {
        strncpy(gstLocalParam.szLogpath, m_strLogPath.GetBuffer(0), sizeof(gstLocalParam.szLogpath) - 1);
        CreateNewLogFile(TRUE);
        NETDEMO_LOG_SUCC(NULL, "Set log path");
    }

    strncpy(gstLocalParam.szLocalRecordPath, m_strLocalRecordPath.GetBuffer(0), sizeof(gstLocalParam.szLocalRecordPath) - 1);
    strncpy(gstLocalParam.szPictureSavePath, m_strSnapshotPath.GetBuffer(0), sizeof(gstLocalParam.szPictureSavePath) - 1);
    
    return;
}


void CDlgLocalSetting::CreateNewLogFile(BOOL bCreate)
{
    CString strLogFile;

    if (NULL != m_pfLog)
    {
        fclose(m_pfLog);
    }

    if (TRUE != bCreate)
    {
        return;
    }

    COleDateTime dtCurTime = COleDateTime::GetCurrentTime();
    strLogFile.Format("%s\\NetDemoLogFile_%4d%02d%02d.txt",\
        gstLocalParam.szLogpath, dtCurTime.GetYear(), dtCurTime.GetMonth(),\
        dtCurTime.GetDay());

    if (NULL == (m_pfLog = fopen(strLogFile.GetBuffer(0), "a+")))
    {
        GetDlgItem(IDC_SAVE_CLINETLOG)->EnableWindow(FALSE);
        m_bChkAutoSaveLog = FALSE;
    }

    return;
}
void CDlgLocalSetting::OnBnClickedButtonSetOperationLog()
{
    UpdateData(TRUE);

    CreateNewLogFile(m_bChkAutoSaveLog);
    gstLocalParam.bAutoSaveLog = m_bChkAutoSaveLog;
    gstLocalParam.bSuccLog = m_bChkSuccLog;
    gstLocalParam.bFailLog = m_bChkFailLog;

    NETDEMO_LOG_SUCC(NULL, "Set Operation Log");
    CDialog::OnOK();

    return;
}

void CDlgLocalSetting::OnBnClickedButtonSetKeeplive()
{
    UpdateData(TRUE);

    BOOL bRet = NETDEV_SetConnectTime(m_dwWaitTime, m_dwTryTimes);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Set Connect Time");
        return;
    }

    NETDEMO_LOG_SUCC(NULL, "Set Connect Time");
    return;
}

void CDlgLocalSetting::OnBnClickedButtonSetTimeout()
{
    UpdateData(TRUE);
    NETDEV_REV_TIMEOUT_S stRevTimeout ={0};
    stRevTimeout.dwRevTimeOut = m_dwReceiveTimeout;
    stRevTimeout.dwFileReportTimeOut = m_dwFileTimeout;

    BOOL bRet = NETDEV_SetRevTimeOut( &stRevTimeout);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Set Connect Time");
        return;
    }

    NETDEMO_LOG_SUCC(NULL, "Set Connect Time");
    return;
}

void CDlgLocalSetting::OnBnClickedBtnSaveStreamType()
{
    UpdateData(TRUE);
    if (FALSE == m_bRatioMain)
    {
        gstLocalParam.dwStreamType = NETDEV_LIVE_STREAM_INDEX_MAIN;
    }
    else if (FALSE == m_bRatioSub)
    {
        gstLocalParam.dwStreamType = NETDEV_LIVE_STREAM_INDEX_AUX;
    }
    else if (FALSE == m_bRatioThird)
    {
        gstLocalParam.dwStreamType = NETDEV_LIVE_STREAM_INDEX_THIRD;
    }

    return;
}
