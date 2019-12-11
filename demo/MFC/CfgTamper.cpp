
#include "stdafx.h"
#include "NetDemo.h"
#include "CfgTamper.h"


// CCfgTamper 

IMPLEMENT_DYNAMIC(CCfgTamper, CDialog)

CCfgTamper::CCfgTamper(CWnd* pParent /*=NULL*/)
    : CDialog(CCfgTamper::IDD, pParent)
    , m_dwSensitivity(50)
{

}

CCfgTamper::~CCfgTamper()
{
}

void CCfgTamper::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_SENSITIVITY, m_dwSensitivity);
    DDX_Control(pDX, IDC_SLIDER_SENSITIVITY, m_oSldSensitivity);
}


BEGIN_MESSAGE_MAP(CCfgTamper, CDialog)
    ON_BN_CLICKED(IDC_SAVE_TEMPER_CFG, &CCfgTamper::OnBnClickedSaveTemperCfg)
    ON_BN_CLICKED(IDC_REFRESH, &CCfgTamper::OnBnClickedRefresh)
    ON_EN_CHANGE(IDC_EDIT_SENSITIVITY, &CCfgTamper::OnEnChangeEditSensitivity)
    ON_EN_KILLFOCUS(IDC_EDIT_SENSITIVITY, &CCfgTamper::OnEnKillfocusEditSensitivity)
    ON_WM_HSCROLL()
END_MESSAGE_MAP()

BOOL CCfgTamper::OnInitDialog()
{
    CDialog::OnInitDialog();
    CRect rc(0, 0, 0, 0);
    GetParent()->GetClientRect(&rc);
    ((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
    MoveWindow(&rc);

    m_oSldSensitivity.SetRange(1, 100);
    m_oSldSensitivity.SetTicFreq(1);
    m_oSldSensitivity.SetPos(50);
    
    return TRUE;
}

void CCfgTamper::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    char szTmp[16] = {0};
    if(IDC_SLIDER_SENSITIVITY == pScrollBar->GetDlgCtrlID())
    {
        nPos = m_oSldSensitivity.GetPos();
        sprintf_s(szTmp, sizeof(szTmp), "%d", nPos);
        GetDlgItem(IDC_SLIDER_SENSITIVITY)->SetWindowText(szTmp);
        m_dwSensitivity = nPos;
    }

    CDialog::OnHScroll(nSBCode, nPos, pScrollBar);

    UpdateData(FALSE);
    return;
}


/* Get Temper Config */
void CCfgTamper::getTemperCfg()
{
    LPVOID lpDevHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChannelID = ga_pMainDlg->GetChlID();
    INT32 dwCurDevIndex = ga_pMainDlg ->GetCurDeviceIndex();
    INT32 dwCurChlIndex = ga_pMainDlg->GetCurChlIndex();

    NETDEV_TAMPER_ALARM_INFO_S stTamperAlarmInfo;
    memset(&stTamperAlarmInfo, 0, sizeof(stTamperAlarmInfo));
    INT32 dwBytesReturned = 0;
    BOOL bRet = NETDEV_GetDevConfig(lpDevHandle, dwChannelID, NETDEV_GET_TAMPERALARM, &stTamperAlarmInfo, sizeof(stTamperAlarmInfo), &dwBytesReturned);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Get tamper alarm info");
        return;
    }

    m_dwSensitivity = stTamperAlarmInfo.dwSensitivity;

    m_oSldSensitivity.SetPos(m_dwSensitivity);
    LPNETDEV_TAMPER_ALARM_INFO_S ptmpReplace = gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstTamperAlarmInfo;
    memcpy(ptmpReplace ,&stTamperAlarmInfo,sizeof(stTamperAlarmInfo));
    NETDEMO_LOG_SUCC(NULL, "Get tamper alarm info");

    UpdateData(FALSE);
    return;
}


/* Save Temper Config */
void CCfgTamper::OnBnClickedSaveTemperCfg()
{
    UpdateData(TRUE);

    LPVOID lpDevHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChannelID = ga_pMainDlg->GetChlID();
    INT32 dwCurDevIndex = ga_pMainDlg ->GetCurDeviceIndex();
    INT32 dwCurChlIndex = ga_pMainDlg->GetCurChlIndex();

    NETDEV_TAMPER_ALARM_INFO_S stTamperAlarmInfo;
    memset(&stTamperAlarmInfo, 0, sizeof(NETDEV_TAMPER_ALARM_INFO_S));

    stTamperAlarmInfo.dwSensitivity = m_dwSensitivity;
    BOOL bRet = NETDEV_SetDevConfig(lpDevHandle, dwChannelID, NETDEV_SET_TAMPERALARM, &stTamperAlarmInfo, sizeof(stTamperAlarmInfo));
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Save tamper alarm info");
        return;
    }
    LPNETDEV_TAMPER_ALARM_INFO_S ptmpReplace= gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstTamperAlarmInfo;
    if(NULL != ptmpReplace)
    {
         memcpy( ptmpReplace,&stTamperAlarmInfo,sizeof(stTamperAlarmInfo));
    }
    NETDEMO_LOG_SUCC(NULL, "Save tamper alarm info");

    return;
}

void CCfgTamper::ReadGlobeToTamper()
{
    INT32 dwCurDevIndex = ga_pMainDlg ->GetCurDeviceIndex();
    INT32 dwCurChlIndex = ga_pMainDlg->GetCurChlIndex();
    NETDEV_TAMPER_ALARM_INFO_S stTamperAlarmInfo ;
    LPNETDEV_TAMPER_ALARM_INFO_S ptmpReplace = gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstTamperAlarmInfo;
    if(NULL != ptmpReplace)
    {
        memcpy(&stTamperAlarmInfo,ptmpReplace,sizeof(stTamperAlarmInfo));
    }
    m_dwSensitivity = stTamperAlarmInfo.dwSensitivity;
    m_oSldSensitivity.SetPos(m_dwSensitivity);

    UpdateData(FALSE);
}


/* Refresh */
void CCfgTamper::OnBnClickedRefresh()
{
    INT32 dwCurDevIndex = ga_pMainDlg ->GetCurDeviceIndex();
    INT32 dwCurChlIndex = ga_pMainDlg->GetCurChlIndex();
    if(dwCurChlIndex <0 )
    {
        return;
    }
    if (NULL != gastDeviceInfo && NULL != gastDeviceInfo[dwCurDevIndex].pstChlInfo)
    {
        if(NULL == gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstTamperAlarmInfo)
        {
            gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstTamperAlarmInfo =  new NETDEV_TAMPER_ALARM_INFO_S;
        }

        memset(gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstTamperAlarmInfo ,0,sizeof(NETDEV_TAMPER_ALARM_INFO_S));

        /* Get Temper Config */
        getTemperCfg();
    }

    UpdateData(FALSE);
    return;
}

void CCfgTamper::OnEnChangeEditSensitivity()
{
    UpdateData(TRUE);
    m_oSldSensitivity.SetPos(m_dwSensitivity);

    return;
}

void CCfgTamper::OnEnKillfocusEditSensitivity()
{
    UpdateData(TRUE);
    if (m_dwSensitivity < 1)
    {
        m_dwSensitivity = 1;
    }
    else if (m_dwSensitivity > 100)
    {
        m_dwSensitivity = 100;
    }

    char szTmp[16] = {0};
    sprintf_s(szTmp, sizeof(szTmp), "%d", m_dwSensitivity);
    GetDlgItem(IDC_EDIT_SENSITIVITY)->SetWindowText(szTmp);

    UpdateData(FALSE);
    return;
}
