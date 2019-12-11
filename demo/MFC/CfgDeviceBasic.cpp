// DLgDeviceParaSetting.cpp : 
//

#include "stdafx.h"
#include "NetDemo.h"
#include "CfgDeviceBasic.h"

#define COL_DISK_SLOT_INDEX         0
#define COL_DISK_TOTAL_CAP          1
#define COL_DISK_FREE_SPACE         2
#define COL_DISK_STATUS             3
#define COL_DISK_MANU_FACTURER      4

// CCfgDeviceBasic 

IMPLEMENT_DYNAMIC(CCfgDeviceBasic, CDialog)

CCfgDeviceBasic::CCfgDeviceBasic(CWnd* pParent /*=NULL*/)
    : CDialog(CCfgDeviceBasic::IDD, pParent)
{

}

CCfgDeviceBasic::~CCfgDeviceBasic()
{
}

void CCfgDeviceBasic::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_DEV_NAME, m_strDeviceName);
    DDX_Control(pDX, IDC_LIST_DISKS_INFO, m_oDiskInfoList);
    DDX_Control(pDX, IDC_DEV_SYSTEM_DATE, m_oDevSysDate);
    DDX_Control(pDX, IDC_DEV_SYSTEM_TIME, m_oDevSysTime);
    DDX_Control(pDX, IDC_COMBO_TIME_ZONE, m_oCBoxTimeZone);
}

BOOL CCfgDeviceBasic::OnInitDialog()
{
    CDialog::OnInitDialog();
    CRect rc(0, 0, 0, 0);
    GetParent()->GetClientRect(&rc);
    ((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
    MoveWindow(&rc);

    initDiskInfoList();

    initTimeZone();

    return TRUE;
}

BEGIN_MESSAGE_MAP(CCfgDeviceBasic, CDialog)
    ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_CONFIGURE_DISKS_INFO, &CCfgDeviceBasic::OnLvnItemchangedListDisksInfo)
    ON_BN_CLICKED(IDC_SAVE_DEV_NAME, &CCfgDeviceBasic::OnBnClickedSaveDevName)
    ON_BN_CLICKED(IDC_REFRESH, &CCfgDeviceBasic::OnBnClickedRefresh)
    ON_BN_CLICKED(IDC_SAVE_SYSTEM_TIME, &CCfgDeviceBasic::OnBnClickedSaveSystemTime)
END_MESSAGE_MAP()

void CCfgDeviceBasic::initDiskInfoList()
{
    CString str = "No.";
    m_oDiskInfoList.InsertColumn(COL_DISK_SLOT_INDEX, str, LVCFMT_LEFT, 80, 30);

    str = "Total Capacity(GB)";
    m_oDiskInfoList.InsertColumn(COL_DISK_TOTAL_CAP, str, LVCFMT_LEFT, 150); 

    str = "Free Space(GB)";
    m_oDiskInfoList.InsertColumn(COL_DISK_FREE_SPACE, str, LVCFMT_LEFT, 150);

    str = "Status";
    m_oDiskInfoList.InsertColumn(COL_DISK_STATUS, str, LVCFMT_LEFT, 100);

    str = "Manufacturer";
    m_oDiskInfoList.InsertColumn(COL_DISK_MANU_FACTURER, str, LVCFMT_LEFT, 100);

    m_oDiskInfoList.SetExtendedStyle(m_oDiskInfoList.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES);
}

void CCfgDeviceBasic::initTimeZone()
{
    m_oCBoxTimeZone.InsertString(NETDEV_TIME_ZONE_W1200, _T("GMT-12:00 International Date Line West"));
    m_oCBoxTimeZone.InsertString(NETDEV_TIME_ZONE_W1100, _T("GMT-11:00 Midway Island, Samoa"));
    m_oCBoxTimeZone.InsertString(NETDEV_TIME_ZONE_W1000, _T("GMT-10:00 Hawaii"));
    m_oCBoxTimeZone.InsertString(NETDEV_TIME_ZONE_W0900, _T("GMT-09:00 Alaska"));
    m_oCBoxTimeZone.InsertString(NETDEV_TIME_ZONE_W0800, _T("GMT-08:00 Pacific Time (U.S. & Canada)"));
    m_oCBoxTimeZone.InsertString(NETDEV_TIME_ZONE_W0700, _T("GMT-07:00 Mountain Time (U.S. & Canada)"));
    m_oCBoxTimeZone.InsertString(NETDEV_TIME_ZONE_W0600, _T("GMT-06:00 Central Time (U.S. & Canada)"));
    m_oCBoxTimeZone.InsertString(NETDEV_TIME_ZONE_W0500, _T("GMT-05:00 Eastern Time (U.S. & Canada)"));
    m_oCBoxTimeZone.InsertString(NETDEV_TIME_ZONE_W0430, _T("GMT-04:30 Caracas"));
    m_oCBoxTimeZone.InsertString(NETDEV_TIME_ZONE_W0400, _T("GMT-04:00 Atlantic Time (Canada)"));
    m_oCBoxTimeZone.InsertString(NETDEV_TIME_ZONE_W0330, _T("GMT-03:30 Newfoundland"));
    m_oCBoxTimeZone.InsertString(NETDEV_TIME_ZONE_W0300, _T("GMT-03:00 Georgetown, Brasilia"));
    m_oCBoxTimeZone.InsertString(NETDEV_TIME_ZONE_W0200, _T("GMT-02:00 Mid-Atlantic"));
    m_oCBoxTimeZone.InsertString(NETDEV_TIME_ZONE_W0100, _T("GMT-01:00 Cape verde Islands, Azores"));
    m_oCBoxTimeZone.InsertString(NETDEV_TIME_ZONE_0000, _T("GMT+00:00 Dublin, Edinburgh, London"));
    m_oCBoxTimeZone.InsertString(NETDEV_TIME_ZONE_E0100, _T("GMT+01:00 Amsterdam, Berlin, Rome, Paris"));
    m_oCBoxTimeZone.InsertString(NETDEV_TIME_ZONE_E0200, _T("GMT+02:00 Athens, Jerusalem, Istanbul"));
    m_oCBoxTimeZone.InsertString(NETDEV_TIME_ZONE_E0300, _T("GMT+03:00 Baghdad, Kuwait, Moscow"));
    m_oCBoxTimeZone.InsertString(NETDEV_TIME_ZONE_E0330, _T("GMT+03:30 Tehran"));
    m_oCBoxTimeZone.InsertString(NETDEV_TIME_ZONE_E0400, _T("GMT+04:00 Caucasus Standard Time"));
    m_oCBoxTimeZone.InsertString(NETDEV_TIME_ZONE_E0430, _T("GMT+04:30 Kabul"));
    m_oCBoxTimeZone.InsertString(NETDEV_TIME_ZONE_E0500, _T("GMT+05:00 Islamabad, Karachi, Tashkent"));
    m_oCBoxTimeZone.InsertString(NETDEV_TIME_ZONE_E0530, _T("GMT+05:30 Madras, Bombay, New Delhi"));
    m_oCBoxTimeZone.InsertString(NETDEV_TIME_ZONE_E0545, _T("GMT+05:45 Kathmandu"));
    m_oCBoxTimeZone.InsertString(NETDEV_TIME_ZONE_E0600, _T("GMT+06:00 Almaty, Novosibirsk, Dhaka"));
    m_oCBoxTimeZone.InsertString(NETDEV_TIME_ZONE_E0630, _T("GMT+06:30 Yangon"));
    m_oCBoxTimeZone.InsertString(NETDEV_TIME_ZONE_E0700, _T("GMT+07:00 Bangkok, Hanoi, Jakarta"));
    m_oCBoxTimeZone.InsertString(NETDEV_TIME_ZONE_E0800, _T("GMT+08:00 Beijing, Hong Kong, Urumqi, Singapore, Taipei"));
    m_oCBoxTimeZone.InsertString(NETDEV_TIME_ZONE_E0900, _T("GMT+09:00 Seoul, Tokyo, Osaka, Sapporo"));
    m_oCBoxTimeZone.InsertString(NETDEV_TIME_ZONE_E0930, _T("GMT+09:30 Adelaide, Darwin"));
    m_oCBoxTimeZone.InsertString(NETDEV_TIME_ZONE_E1000, _T("GMT+10:00 Melbourne, Sydney, Canberra"));
    m_oCBoxTimeZone.InsertString(NETDEV_TIME_ZONE_E1100, _T("GMT+11:00 Magadan, Solomon Islands"));
    m_oCBoxTimeZone.InsertString(NETDEV_TIME_ZONE_E1200, _T("GMT+12:00 Auckland, Wellington"));
    m_oCBoxTimeZone.InsertString(NETDEV_TIME_ZONE_E1300, _T("GMT+13:00 Nuku'alofa"));

    m_oCBoxTimeZone.SetCurSel(0);
    return;
}

void CCfgDeviceBasic::OnLvnItemchangedListDisksInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
    *pResult = 0;
    
}

/* Get Device Name */
void CCfgDeviceBasic::getDevName()
{
    LPVOID lpDevHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChannelID = ga_pMainDlg->GetChlID();
    INT32 dwCurDevIndex = ga_pMainDlg ->GetCurDeviceIndex();
    INT32 dwCurChlIndex = ga_pMainDlg->GetCurChlIndex();
    
    NETDEV_DEVICE_BASICINFO_S stDeviceInfo = {0};
    INT32 dwBytesReturned = 0;
    BOOL bRet = NETDEV_GetDevConfig(lpDevHandle, dwChannelID, NETDEV_GET_DEVICECFG, &stDeviceInfo, sizeof(NETDEV_DEVICE_BASICINFO_S), &dwBytesReturned );
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Get device name");
        return;
    }

    CHAR szTmp[NETDEV_LEN_64] = {0};
    UTF8ToMB(stDeviceInfo.szDeviceName, szTmp, sizeof(szTmp) - 1);
    m_strDeviceName = szTmp;
    strncpy(gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstBasicInfo->szDeviceName, szTmp, sizeof(szTmp) - 1);
    NETDEMO_LOG_SUCC(NULL, "Get device name");

    UpdateData(FALSE);
    return;
}

/* Save Device Name */
void CCfgDeviceBasic::OnBnClickedSaveDevName()
{
    UpdateData(TRUE);

    LPVOID lpDevHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwCurDevIndex = ga_pMainDlg ->GetCurDeviceIndex();
    INT32 dwCurChlIndex = ga_pMainDlg->GetCurChlIndex();

    CHAR szTmp[NETDEV_LEN_64] = {0};
    MBToUTF8(m_strDeviceName.GetBuffer(0), szTmp, sizeof(szTmp) - 1);
    BOOL bRet = NETDEV_ModifyDeviceName(lpDevHandle, szTmp);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Save device name");
        return;
    }
    memset(gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstBasicInfo->szDeviceName, 0,
        sizeof(gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstBasicInfo->szDeviceName));
    strncpy(gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstBasicInfo->szDeviceName, szTmp, sizeof(szTmp) - 1);
    NETDEMO_LOG_SUCC(NULL, "Save device name");

    return;
}

/* Get System Time */
void CCfgDeviceBasic::getSystemTime()
{
    LPVOID lpDevHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChannelID = ga_pMainDlg->GetChlID();
    INT32 dwCurDevIndex = ga_pMainDlg ->GetCurDeviceIndex();
    INT32 dwCurChlIndex = ga_pMainDlg->GetCurChlIndex();

    /* Get Device System time */
    if (0 == dwChannelID)
    {
        NETDEV_TIME_CFG_S stTimeCfg;
        memset(&stTimeCfg, 0, sizeof(stTimeCfg));
        BOOL bRet = NETDEV_GetSystemTimeCfg(lpDevHandle, &stTimeCfg);
        if(TRUE != bRet)
        {
            NETDEMO_LOG_ERROR(NULL, "Get device system time");
            return;
        }
        else
        {
            SYSTEMTIME oSysTime = {0};
            oSysTime.wYear = stTimeCfg.stTime.dwYear;
            oSysTime.wMonth = stTimeCfg.stTime.dwMonth;
            oSysTime.wDay = stTimeCfg.stTime.dwDay;
            oSysTime.wHour = stTimeCfg.stTime.dwHour;
            oSysTime.wMinute = stTimeCfg.stTime.dwMinute;
            oSysTime.wSecond = stTimeCfg.stTime.dwSecond;

            m_oDevSysDate.SetTime(&oSysTime);
            m_oDevSysTime.SetTime(&oSysTime);

            m_oCBoxTimeZone.SetCurSel(stTimeCfg.dwTimeZone);
            gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstBasicInfo->stSystemTime = stTimeCfg;
            UpdateData(FALSE);
            NETDEMO_LOG_SUCC(NULL, "Get device system time");
        }
    }
    else
    {
        NETDEMO_LOG_ERROR(NULL, "Cannot get channel system time.");
    }

    return;
}

/* Save system time */
void CCfgDeviceBasic::OnBnClickedSaveSystemTime()
{
    UpdateData(TRUE);

    LPVOID lpDevHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChannelID = ga_pMainDlg->GetChlID();
    INT32 dwCurDevIndex = ga_pMainDlg ->GetCurDeviceIndex();
    INT32 dwCurChlIndex = ga_pMainDlg->GetCurChlIndex();
  
    /* Save system time */
    if (0 == dwChannelID)
    {
        NETDEV_TIME_CFG_S stTimeCfg;
        memset(&stTimeCfg, 0, sizeof(stTimeCfg));

        CTime tSysDate;
        m_oDevSysDate.GetTime(tSysDate);
        CString strDate = tSysDate.Format("%Y/%m/%d");
        sscanf(strDate.GetBuffer(0), "%d/%d/%d", &stTimeCfg.stTime.dwYear, &stTimeCfg.stTime.dwMonth, &stTimeCfg.stTime.dwDay);

        CTime tSysTime;
        m_oDevSysTime.GetTime(tSysTime);
        CString strTime = tSysTime.Format("%H:%M:%S");
        sscanf(strTime.GetBuffer(0), "%d:%d:%d", &stTimeCfg.stTime.dwHour, &stTimeCfg.stTime.dwMinute, &stTimeCfg.stTime.dwSecond);

        stTimeCfg.dwTimeZone = (NETDEV_TIME_ZONE_E)m_oCBoxTimeZone.GetCurSel();

        BOOL bRet = NETDEV_SetSystemTimeCfg(lpDevHandle, &stTimeCfg);
        if(TRUE != bRet)
        {
            NETDEMO_LOG_ERROR(NULL, "Save device system time");
            return;
        }

        gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstBasicInfo->stSystemTime = stTimeCfg;
        NETDEMO_LOG_SUCC(NULL, "Save device system time");
    }
    else
    {
        NETDEMO_LOG_ERROR(NULL, "Cannot save channel system time.");
    }

    return;
}

/* Get Disk Info */
void CCfgDeviceBasic::getDiskInfo()
{
    m_oDiskInfoList.DeleteAllItems();

    LPVOID lpDevHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChannelID = ga_pMainDlg->GetChlID();
    INT32 dwCurDevIndex = ga_pMainDlg ->GetCurDeviceIndex();
    INT32 dwCurChlIndex = ga_pMainDlg->GetCurChlIndex();

    INT32 dwBytesReturned = 0;
    NETDEV_DISK_INFO_LIST_S stDiskInfoList = {0};
    BOOL bRet = NETDEV_GetDevConfig(lpDevHandle, dwChannelID, NETDEV_GET_DISKSINFO, &stDiskInfoList, sizeof(NETDEV_DISK_INFO_LIST_S), &dwBytesReturned);
    if (TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Get disk info");
        return;
    }

    CHAR szBuf[64] = {0};
    int iRow = 0;
    for (INT32 i = 0; i < stDiskInfoList.dwSize; i++)
    {
        /* slot index */
        _snprintf(szBuf, sizeof(szBuf), "%d", stDiskInfoList.astDisksInfo[i].dwSlotIndex);
        iRow = m_oDiskInfoList.InsertItem(i, szBuf);

        /* Total capcity */
        memset(szBuf, 0, sizeof(szBuf));
        float fTotalCap = (float)stDiskInfoList.astDisksInfo[i].dwTotalCapacity / 1024;
        _snprintf(szBuf, sizeof(szBuf), "%.2f", fTotalCap);
        m_oDiskInfoList.SetItemText(iRow, COL_DISK_TOTAL_CAP, szBuf);

        /* Free space */
        memset(szBuf, 0, sizeof(szBuf));
        float fUsedCap = (float)stDiskInfoList.astDisksInfo[i].dwUsedCapacity / 1024;
        float fFreeSpace = fTotalCap - fUsedCap;
        _snprintf(szBuf, sizeof(szBuf), "%.2f", fFreeSpace);
        m_oDiskInfoList.SetItemText(iRow, COL_DISK_FREE_SPACE, szBuf);

        /* disk status */
        CString str;
        switch(stDiskInfoList.astDisksInfo[i].enStatus)
        {
        case NETDEV_DISK_WORK_STATUS_EMPTY:             /*  Empty/No Disk */
            str = "No Disk";
            break;
        case NETDEV_DISK_WORK_STATUS_UNFORMAT:          /*  Unformat */
            str = "Unformat";
            break;
        case NETDEV_DISK_WORK_STATUS_FORMATING:         /*  Formating */
            str = "Formating";
            break;
        case NETDEV_DISK_WORK_STATUS_RUNNING:           /*  Running/Normal */
            str = "Normal";
            break;
        case NETDEV_DISK_WORK_STATUS_HIBERNATE:         /*  Hibernate */
            str = "Hibernate";
            break;
        case NETDEV_DISK_WORK_STATUS_ABNORMAL:          /*  Abnormal */
            str = "Abnormal";
            break;
        default:                                        /*  Unknown */
            str = "Unknown";
            break;
        }

        m_oDiskInfoList.SetItemText(iRow, COL_DISK_STATUS, str);

        /* Manufacturer */
        m_oDiskInfoList.SetItemText(iRow, COL_DISK_MANU_FACTURER, stDiskInfoList.astDisksInfo[i].szManufacturer);
        
    }

    gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstBasicInfo->stDiskInfoList = stDiskInfoList;
    NETDEMO_LOG_SUCC(NULL, "Get disk info");

    UpdateData(FALSE);
    return;
}

void CCfgDeviceBasic::ReadGlobeToBasic()
{
    INT32 dwCurDevIndex = ga_pMainDlg ->GetCurDeviceIndex();
    INT32 dwCurChlIndex = ga_pMainDlg->GetCurChlIndex();
    NETDEV_TIME_CFG_S  stTimeCfg = gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstBasicInfo->stSystemTime;

    SYSTEMTIME oSysTime = {0};
    oSysTime.wYear = stTimeCfg.stTime.dwYear;
    oSysTime.wMonth = stTimeCfg.stTime.dwMonth;
    oSysTime.wDay = stTimeCfg.stTime.dwDay;
    oSysTime.wHour = stTimeCfg.stTime.dwHour;
    oSysTime.wMinute = stTimeCfg.stTime.dwMinute;
    oSysTime.wSecond = stTimeCfg.stTime.dwSecond;

    m_oDevSysDate.SetTime(&oSysTime);
    m_oDevSysTime.SetTime(&oSysTime);
    m_oCBoxTimeZone.SetCurSel(stTimeCfg.dwTimeZone);

    m_strDeviceName = gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstBasicInfo->szDeviceName;

    m_oDiskInfoList.DeleteAllItems();
    NETDEV_DISK_INFO_LIST_S stDiskInfoList;
    memset(&stDiskInfoList,0,sizeof(stDiskInfoList));
    memcpy(&stDiskInfoList,&(gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstBasicInfo->stDiskInfoList),sizeof(stDiskInfoList));     
    CHAR szBuf[64] = {0};
    INT32 iRow = 0;
    m_oDiskInfoList.DeleteAllItems();

    for (INT32 i = 0; i < stDiskInfoList.dwSize; i++)
    {
        /* slot index */
        _snprintf(szBuf, sizeof(szBuf), "%d", stDiskInfoList.astDisksInfo[i].dwSlotIndex);
        iRow = m_oDiskInfoList.InsertItem(i, szBuf);

        /* Total capcity */
        memset(szBuf, 0, sizeof(szBuf));
        float fTotalCap = (float)stDiskInfoList.astDisksInfo[i].dwTotalCapacity / 1024;
        _snprintf(szBuf, sizeof(szBuf), "%.2f", fTotalCap);
        m_oDiskInfoList.SetItemText(iRow, COL_DISK_TOTAL_CAP, szBuf);

        /* Free space */
        memset(szBuf, 0, sizeof(szBuf));
        float fUsedCap = (float)stDiskInfoList.astDisksInfo[i].dwUsedCapacity / 1024;
        float fFreeSpace = fTotalCap - fUsedCap;
        _snprintf(szBuf, sizeof(szBuf), "%.2f", fFreeSpace);
        m_oDiskInfoList.SetItemText(iRow, COL_DISK_FREE_SPACE, szBuf);

        /* disk status */
        CString str;
        switch(stDiskInfoList.astDisksInfo[i].enStatus)
        {
        case NETDEV_DISK_WORK_STATUS_EMPTY:             /*  Empty/No Disk */
            str = "No Disk";
            break;
        case NETDEV_DISK_WORK_STATUS_UNFORMAT:          /*  Unformat */
            str = "Unformat";
            break;
        case NETDEV_DISK_WORK_STATUS_FORMATING:         /*  Formating */
            str = "Formating";
            break;
        case NETDEV_DISK_WORK_STATUS_RUNNING:           /*  Running/Normal */
            str = "Normal";
            break;
        case NETDEV_DISK_WORK_STATUS_HIBERNATE:         /*  Hibernate */
            str = "Hibernate";
            break;
        case NETDEV_DISK_WORK_STATUS_ABNORMAL:          /*  Abnormal */
            str = "Abnormal";
            break;
        default:                                        /*  Unknown */
            str = "Unknown";
            break;
        }

        m_oDiskInfoList.SetItemText(iRow, COL_DISK_STATUS, str);

        /* Manufacturer */
        m_oDiskInfoList.SetItemText(iRow, COL_DISK_MANU_FACTURER, stDiskInfoList.astDisksInfo[i].szManufacturer);
    }

    UpdateData(FALSE);
}

/* Refresh */
void CCfgDeviceBasic::OnBnClickedRefresh()
{
    INT32 dwCurDevIndex = ga_pMainDlg ->GetCurDeviceIndex();
    INT32 dwCurChlIndex = ga_pMainDlg->GetCurChlIndex();
    if(dwCurChlIndex < 0 )
    {
        return;
    }

    if (NULL != gastDeviceInfo && NULL != gastDeviceInfo[dwCurDevIndex].pstChlInfo)
    {
        if(NULL == gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstBasicInfo)
        {
            gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstBasicInfo = new NETDEMO_BASIC_INFO_S;
        }

        memset(gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstBasicInfo ,0,sizeof(NETDEMO_BASIC_INFO_S));

        /* Get Device System time */
        getSystemTime();

        /* Get Device name */
        getDevName();

        /* Get disk info */
        getDiskInfo();
    }

    UpdateData(FALSE);
    return;
}
