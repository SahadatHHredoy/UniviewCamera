
#include "stdafx.h"
#include "NetDemo.h"
#include "CfgMotion.h"
#define MAXMOTIONOBJECTSIZE 100


IMPLEMENT_DYNAMIC(CCfgMotion, CDialog)

CCfgMotion::CCfgMotion(CWnd* pParent /*=NULL*/)
    : CDialog(CCfgMotion::IDD, pParent)
    , m_dwObjSize(50)
    , m_dwHistory(50)
    , m_dwSensitivity(50)
{

}

CCfgMotion::~CCfgMotion()
{
}

void CCfgMotion::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    DDX_Text(pDX, IDC_EDIT_OBJ_SIZE, m_dwObjSize);
    DDX_Text(pDX, IDC_EDIT_HISTORY, m_dwHistory);
    DDX_Text(pDX, IDC_EDIT_SENSITIVITY, m_dwSensitivity);
    DDX_Control(pDX, IDC_SLIDER_SENSITIVITY, m_oSldSensitivity);
    DDX_Control(pDX, IDC_SLIDER_OBJ_SIZE, m_oSldObjSize);
    DDX_Control(pDX, IDC_SLIDER_HISTORY, m_oSldHistory);
}


BEGIN_MESSAGE_MAP(CCfgMotion, CDialog)
    ON_BN_CLICKED(IDC_SAVE_MOTION_CFG, &CCfgMotion::OnBnClickedSaveMotionCfg)
    ON_BN_CLICKED(IDC_REFRESH, &CCfgMotion::OnBnClickedRefresh)
    ON_WM_HSCROLL()
    ON_EN_CHANGE(IDC_EDIT_SENSITIVITY, &CCfgMotion::OnEnChangeEditSensitivity)
    ON_EN_KILLFOCUS(IDC_EDIT_SENSITIVITY, &CCfgMotion::OnEnKillfocusEditSensitivity)
    ON_EN_CHANGE(IDC_EDIT_OBJ_SIZE, &CCfgMotion::OnEnChangeEditObjSize)
    ON_EN_KILLFOCUS(IDC_EDIT_OBJ_SIZE, &CCfgMotion::OnEnKillfocusEditObjSize)
    ON_EN_CHANGE(IDC_EDIT_HISTORY, &CCfgMotion::OnEnChangeEditHistory)
    ON_EN_KILLFOCUS(IDC_EDIT_HISTORY, &CCfgMotion::OnEnKillfocusEditHistory)
END_MESSAGE_MAP()

BOOL CCfgMotion::OnInitDialog()
{
    CDialog::OnInitDialog();
    CRect rc(0, 0, 0, 0);
    GetParent()->GetClientRect(&rc);
    ((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
    MoveWindow(&rc);

    m_oSldSensitivity.SetRange(1, 100);
    m_oSldSensitivity.SetTicFreq(1);
    m_oSldSensitivity.SetPos(50);

    m_oSldObjSize.SetRange(1, 100);
    m_oSldObjSize.SetTicFreq(1);
    m_oSldObjSize.SetPos(50);

    m_oSldHistory.SetRange(1, 100);
    m_oSldHistory.SetTicFreq(1);
    m_oSldHistory.SetPos(50);

    return TRUE;
}


void CCfgMotion::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    char szTmp[16] = {0};
    if(IDC_SLIDER_SENSITIVITY == pScrollBar->GetDlgCtrlID())
    {
        nPos = m_oSldSensitivity.GetPos();
        sprintf_s(szTmp, sizeof(szTmp), "%d", nPos);
        GetDlgItem(IDC_SLIDER_SENSITIVITY)->SetWindowText(szTmp);
        m_dwSensitivity = nPos;
    }

    if(IDC_SLIDER_OBJ_SIZE == pScrollBar->GetDlgCtrlID())
    {
        nPos = m_oSldObjSize.GetPos();
        sprintf_s(szTmp, sizeof(szTmp), "%d", nPos);
        GetDlgItem(IDC_SLIDER_OBJ_SIZE)->SetWindowText(szTmp);
        m_dwObjSize = nPos;
    }

    if(IDC_SLIDER_HISTORY == pScrollBar->GetDlgCtrlID())
    {
        nPos = m_oSldHistory.GetPos();
        sprintf_s(szTmp, sizeof(szTmp), "%d", nPos);
        GetDlgItem(IDC_SLIDER_HISTORY)->SetWindowText(szTmp);
        m_dwHistory = nPos;
    }

    CDialog::OnHScroll(nSBCode, nPos, pScrollBar);

    UpdateData(FALSE);
    return;
}

/* Get Motion Config */
void CCfgMotion::getMotionCfg()
{
    LPVOID lpDevHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChannelID = ga_pMainDlg->GetChlID();
    INT32 dwCurDevIndex = ga_pMainDlg ->GetCurDeviceIndex();
    INT32 dwCurChlIndex = ga_pMainDlg->GetCurChlIndex();

    NETDEV_MOTION_ALARM_INFO_S stMotionAlarmInfo = {0};
    INT32 dwBytesReturned = 0;
    BOOL bRet = NETDEV_GetDevConfig(lpDevHandle, dwChannelID, NETDEV_GET_MOTIONALARM, &stMotionAlarmInfo, sizeof(NETDEV_MOTION_ALARM_INFO_S), &dwBytesReturned);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Get motion cfg");
        return;
    }

    m_dwSensitivity = stMotionAlarmInfo.dwSensitivity;
    m_oSldSensitivity.SetPos(m_dwSensitivity);

    if(stMotionAlarmInfo.dwObjectSize > MAXMOTIONOBJECTSIZE)
    {
        stMotionAlarmInfo.dwObjectSize = MAXMOTIONOBJECTSIZE;
    }

    m_dwObjSize = stMotionAlarmInfo.dwObjectSize;
    m_oSldObjSize.SetPos(m_dwObjSize);

    m_dwHistory = stMotionAlarmInfo.dwHistory;
    m_oSldHistory.SetPos(m_dwHistory);
    LPNETDEV_MOTION_ALARM_INFO_S ptmpReplace = gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstMotionAlarmInfo;
    memcpy(ptmpReplace, &stMotionAlarmInfo,sizeof(stMotionAlarmInfo));

    NETDEMO_LOG_SUCC(NULL, "Get motion cfg");
    UpdateData(FALSE);
    return;
}

void CCfgMotion::OnBnClickedSaveMotionCfg()
{
    UpdateData(TRUE);
    LPVOID lpDevHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChannelID = ga_pMainDlg->GetChlID();
    INT32 dwCurDevIndex = ga_pMainDlg ->GetCurDeviceIndex();
    INT32 dwCurChlIndex = ga_pMainDlg->GetCurChlIndex();

    NETDEV_MOTION_ALARM_INFO_S stMotionAlarmInfo = {0};
    INT32 dwBytesReturned = 0;
    
    memset(&stMotionAlarmInfo.awScreenInfo, 0,sizeof(stMotionAlarmInfo.awScreenInfo));
    for(INT32 i = 0; i < NETDEV_SCREEN_INFO_ROW; i++)
    {
        for(INT32 j = 0; j < NETDEV_SCREEN_INFO_COLUMN; j++)
        {
            stMotionAlarmInfo.awScreenInfo[i][j] = 1;
        }
    }

    stMotionAlarmInfo.dwSensitivity = m_dwSensitivity;
    stMotionAlarmInfo.dwObjectSize = m_dwObjSize;
    stMotionAlarmInfo.dwHistory = m_dwHistory;

    BOOL bRet = NETDEV_SetDevConfig(lpDevHandle, dwChannelID, NETDEV_SET_MOTIONALARM, &stMotionAlarmInfo, sizeof(NETDEV_MOTION_ALARM_INFO_S));
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Save motion cfg");
        return;
    }
    LPNETDEV_MOTION_ALARM_INFO_S ptmpReplace = gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstMotionAlarmInfo;
    if(NULL != ptmpReplace)
    {
        memcpy(ptmpReplace, &stMotionAlarmInfo,sizeof(stMotionAlarmInfo));
    }
    NETDEMO_LOG_SUCC(NULL, "Save motion cfg");
    return;
}

void CCfgMotion::ReadGlobeToMotion()
{
    INT32 dwCurDevIndex = ga_pMainDlg ->GetCurDeviceIndex();
    INT32 dwCurChlIndex = ga_pMainDlg->GetCurChlIndex();

    NETDEV_MOTION_ALARM_INFO_S stMotionAlarmInfo ;
    if(NULL == gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstMotionAlarmInfo)
    {
        return;
    }
    LPNETDEV_MOTION_ALARM_INFO_S ptmpReplace = gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstMotionAlarmInfo;
    if(NULL != ptmpReplace)
    {
        memcpy(&stMotionAlarmInfo,ptmpReplace,sizeof(stMotionAlarmInfo));
    }
    m_dwSensitivity = stMotionAlarmInfo.dwSensitivity;
    m_oSldSensitivity.SetPos(m_dwSensitivity);

    m_dwObjSize = stMotionAlarmInfo.dwObjectSize;
    m_oSldObjSize.SetPos(m_dwObjSize);

    m_dwHistory = stMotionAlarmInfo.dwHistory;
    m_oSldHistory.SetPos(m_dwHistory);

    UpdateData(FALSE);
}

void CCfgMotion::OnBnClickedRefresh()
{
    INT32 dwCurDevIndex = ga_pMainDlg ->GetCurDeviceIndex();
    INT32 dwCurChlIndex = ga_pMainDlg->GetCurChlIndex();
    if(dwCurChlIndex <0 )
    {
        return;
    }
    if (NULL != gastDeviceInfo && NULL != gastDeviceInfo[dwCurDevIndex].pstChlInfo)
    {
        if(NULL == gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstMotionAlarmInfo)
        {
            gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstMotionAlarmInfo = new NETDEV_MOTION_ALARM_INFO_S;
        }
        memset(gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstMotionAlarmInfo ,0,sizeof(NETDEV_MOTION_ALARM_INFO_S));
        /* Get motion config */ 
        getMotionCfg();
    }
    
    UpdateData(FALSE);
    return;
}

void CCfgMotion::OnEnChangeEditSensitivity()
{
    UpdateData(TRUE);
    m_oSldSensitivity.SetPos(m_dwSensitivity);

    return;
}

void CCfgMotion::OnEnKillfocusEditSensitivity()
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


void CCfgMotion::OnEnChangeEditObjSize()
{
    UpdateData(TRUE);
    m_oSldObjSize.SetPos(m_dwObjSize);

    return;
}

void CCfgMotion::OnEnKillfocusEditObjSize()
{
    UpdateData(TRUE);
    if (m_dwObjSize < 1)
    {
        m_dwObjSize = 1;
    }
    else if (m_dwObjSize > 100)
    {
        m_dwObjSize = 100;
    }

    char szTmp[16] = {0};
    sprintf_s(szTmp, sizeof(szTmp), "%d", m_dwObjSize);
    GetDlgItem(IDC_EDIT_OBJ_SIZE)->SetWindowText(szTmp);

    UpdateData(FALSE);
    return;
}

void CCfgMotion::OnEnChangeEditHistory()
{
    UpdateData(TRUE);
    m_oSldHistory.SetPos(m_dwHistory);

    return;
}

void CCfgMotion::OnEnKillfocusEditHistory()
{
    UpdateData(TRUE);
    if (m_dwHistory < 1)
    {
        m_dwHistory = 1;
    }
    else if (m_dwHistory > 100)
    {
        m_dwHistory = 100;
    }

    char szTmp[16] = {0};
    sprintf_s(szTmp, sizeof(szTmp), "%d", m_dwHistory);
    GetDlgItem(IDC_EDIT_HISTORY)->SetWindowText(szTmp);

    UpdateData(FALSE);
    return;
}
