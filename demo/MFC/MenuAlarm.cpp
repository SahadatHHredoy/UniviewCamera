
#include "stdafx.h"
#include "NetDemo.h"
#include "MenuAlarm.h"



IMPLEMENT_DYNAMIC(CMenuAlarm, CDialog)

CMenuAlarm::CMenuAlarm(CWnd* pParent /*=NULL*/)
: CDialog(CMenuAlarm::IDD, pParent)
{

}

CMenuAlarm::~CMenuAlarm()
{
}

void CMenuAlarm::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TAB_WARNING, m_oTabAlarm);
}


BEGIN_MESSAGE_MAP(CMenuAlarm, CDialog)
    ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_WARNING, &CMenuAlarm::OnTcnSelchangeTabWarning)
END_MESSAGE_MAP()


void CMenuAlarm::OnTcnSelchangeTabWarning(NMHDR *pNMHDR, LRESULT *pResult)
{
    UpdateData(TRUE);
    m_dwCfgType =  m_oTabAlarm.GetCurSel();
    ConfigureWithUpdate();
    *pResult = 0;
}

void CMenuAlarm::ConfigureWithUpdate()
{
    switch(m_dwCfgType)
    {
    case NETDEMO_REAL_ALARM:
        m_oDlgRealTimeAlarm.ShowWindow(SW_SHOW);
        break;
    default:
        break;
    }

    return;
}

BOOL CMenuAlarm::OnInitDialog()
{
    CDialog::OnInitDialog();
    ShowMainMenu();
    UpdateData(FALSE);
    return TRUE;
}

void CMenuAlarm::ShowMainMenu()
{
    CString str ="Real-time Alarm";
    m_oTabAlarm.InsertItem(NETDEMO_REAL_ALARM, str);
    m_oDlgRealTimeAlarm.Create(IDD_ALARM_REPORT, &m_oTabAlarm);
    m_oDlgRealTimeAlarm.ShowWindow(SW_SHOW);

    return;
}

void CMenuAlarm::handleRealWarning(LPVOID  dwUserID,
                                   NETDEV_ALARM_INFO_EX_S stAlarmInfo)
{
    m_oDlgRealTimeAlarm.handleRealTimeAlarm(dwUserID,stAlarmInfo);

    return;
}

void CMenuAlarm::handleRealWarning(LPVOID  dwUserID,
                                   INT32  dwType)
{
    m_oDlgRealTimeAlarm.handleRealTimeAlarm(dwUserID, dwType);

    return;
}
