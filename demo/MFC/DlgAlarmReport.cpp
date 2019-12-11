#include "stdafx.h"
#include "NetDemo.h"
#include "DlgAlarmReport.h"
#include <sys/timeb.h>

#define COL_INDEX_ALARM_TIME            1
#define COL_INDEX_ALARM_DEV_IP          2
#define COL_INDEX_ALARM_DEV_CHL         3
#define COL_INDEX_ALARM_INFO            4

IMPLEMENT_DYNAMIC(CDlgAlarmReport, CDialog)

CDlgAlarmReport::CDlgAlarmReport(CWnd* pParent /*=NULL*/)
    : CDialog(CDlgAlarmReport::IDD, pParent)
{

}

CDlgAlarmReport::~CDlgAlarmReport()
{
}

void CDlgAlarmReport::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_ALARM, m_oAlramReportList);
}


BEGIN_MESSAGE_MAP(CDlgAlarmReport, CDialog)
    ON_BN_CLICKED(IDC_BUTTON_CLEAN_ALL, &CDlgAlarmReport::OnBnClickedButtonCleanAll)
END_MESSAGE_MAP()


BOOL CDlgAlarmReport::OnInitDialog()
{
    
    CDialog::OnInitDialog();
    CRect rc(0, 0, 0, 0);
    GetParent()->GetClientRect(&rc);
    ((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
    MoveWindow(&rc);

    initAlarmReportList();
    return TRUE;
}

void CDlgAlarmReport::initAlarmReportList()
{
    m_oAlramReportList.InsertColumn(0, "", LVCFMT_CENTER, 0, -1);

    CString str ="Time";
    m_oAlramReportList.InsertColumn(COL_INDEX_ALARM_TIME,str,LVCFMT_CENTER,150);

    str = "IP";
    m_oAlramReportList.InsertColumn(COL_INDEX_ALARM_DEV_IP, str, LVCFMT_CENTER, 180);

    str = "Channel ID";
    m_oAlramReportList.InsertColumn(COL_INDEX_ALARM_DEV_CHL, str, LVCFMT_CENTER, 110);

    str = "Info";
    m_oAlramReportList.InsertColumn(COL_INDEX_ALARM_INFO, str, LVCFMT_CENTER, 300);

    m_oAlramReportList.SetExtendedStyle(m_oAlramReportList.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES);

    return;
}

void CDlgAlarmReport::handleRealTimeAlarm(LPVOID  dwUserID,
                                          NETDEV_ALARM_INFO_EX_S stAlarmInfo)
{
    INT32 dwRow = m_oAlramReportList.InsertItem(0, "");

    CString strAlarmTime;
    UTCTime2LocalTime(stAlarmInfo.tAlarmTime, strAlarmTime);
    m_oAlramReportList.SetItemText(dwRow, COL_INDEX_ALARM_TIME, strAlarmTime);

    CString strDeviceIP;
    getDeviceIP(dwUserID, strDeviceIP);
    if (true == strDeviceIP.IsEmpty())
    {
        m_oAlramReportList.DeleteItem(0);
        return;
    }
    m_oAlramReportList.SetItemText(dwRow, COL_INDEX_ALARM_DEV_IP, strDeviceIP);

    CString strChannelInfo;
    strChannelInfo.Format("%2d", stAlarmInfo.dwChannelID);
    m_oAlramReportList.SetItemText(dwRow, COL_INDEX_ALARM_DEV_CHL, strChannelInfo);

    CString strAlarmInfo;
    getAlarmInfo(stAlarmInfo.dwAlarmType, strAlarmInfo);
    m_oAlramReportList.SetItemText(dwRow, COL_INDEX_ALARM_INFO, strAlarmInfo);

    return;
}

void CDlgAlarmReport::UTCTime2LocalTime(INT32 dwUTCtime, 
                                 CString& strAlarmTime)
{
    INT64 dwAlarmTime = dwUTCtime;
    tm *pTime = localtime((time_t*)&dwAlarmTime);
    strAlarmTime.Format("%d-%02d-%02d %02d:%02d:%02d",pTime->tm_year + 1900,pTime->tm_mon+1,pTime->tm_mday,pTime->tm_hour,pTime->tm_min,pTime->tm_sec);

    return;
}

void CDlgAlarmReport::getDeviceIP(LPVOID  dwUserID, 
                                  CString& strDeviceIP)
{
    INT32 dwDevIndex = 0;
    if (ga_pMainDlg->GetPlayWndDevIndex(dwUserID, dwDevIndex) && dwDevIndex < gaDeviceIndex)
    {
        INT32 dwCurDevIndex = ga_pMainDlg->GetCurDeviceIndex();
        if (NETDEMO_LOGTYPE_LOCAL == gastDeviceInfo[dwCurDevIndex].dwLoginType)
        {
            strDeviceIP.Format("%s", gastDeviceInfo[dwCurDevIndex].szIPAddr);
        }
        else if (NETDEMO_LOGTYPE_CLOUD == gastDeviceInfo[dwCurDevIndex].dwLoginType)
        {
            strDeviceIP.Format("%s", gastDeviceInfo[dwCurDevIndex].stCloudDevinfo.szIPAddr);
        }

        return;
    }

    for (int i = 0; i< gaDeviceIndex; i++)
    {
        if (dwUserID == gastDeviceInfo[i].lpDevHandle)
        {
            if (NETDEMO_LOGTYPE_LOCAL == gastDeviceInfo[i].dwLoginType)
            {
                strDeviceIP.Format("%s", gastDeviceInfo[i].szIPAddr);
            }
            else if (NETDEMO_LOGTYPE_CLOUD == gastDeviceInfo[i].dwLoginType)
            {
                strDeviceIP.Format("%s", gastDeviceInfo[i].stCloudDevinfo.szIPAddr);
            }

            return;
        }
    }

    strDeviceIP = "Unknown ip";

    return;
}

void CDlgAlarmReport::getAlarmInfo(INT32 dwAlarmType,
                                   CString& strAlarmInfo)
{
    UINT32 udwSize = sizeof(gastNETDemoAlarmInfo) / sizeof(NETDEMO_ALARM_INFO);
    for (UINT32 udwAlatmInfo = 0; udwAlatmInfo < udwSize; udwAlatmInfo++)
    {
        if (dwAlarmType == gastNETDemoAlarmInfo[udwAlatmInfo].ulAlarmType)
        {
            strAlarmInfo = gastNETDemoAlarmInfo[udwAlatmInfo].pcReportAlarm;
            return;
        }
    }

    strAlarmInfo = "Unknown alarm";

    return;
}

void CDlgAlarmReport::handleRealTimeAlarm(LPVOID  dwUserID, 
                                        INT32  dwType)
{
    INT32 dwRow = m_oAlramReportList.InsertItem(0, "");

    CString strDeviceIP;
    getDeviceIP(dwUserID, strDeviceIP);
    m_oAlramReportList.SetItemText(dwRow, COL_INDEX_ALARM_DEV_IP, strDeviceIP);

    CString strAlarmTime;
    UTCTime2LocalTime(time(NULL), strAlarmTime);
    m_oAlramReportList.SetItemText(dwRow, COL_INDEX_ALARM_TIME, strAlarmTime);

    CString strAlarmInfo;
    getAlarmInfo(dwType, strAlarmInfo);
    m_oAlramReportList.SetItemText(dwRow, COL_INDEX_ALARM_INFO, strAlarmInfo);

    return;
}

void CDlgAlarmReport::OnBnClickedButtonCleanAll()
{
    m_oAlramReportList.DeleteAllItems();

    return;
}
