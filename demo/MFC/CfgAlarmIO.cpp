// DlgConfigureAlarm.cpp : 
//

#include "stdafx.h"
#include "NetDemo.h"
#include "CfgAlarmIO.h"


// CCfgAlarm 

#define INDEX_ALARMOUT_OPEN         0       // NETDEV_BOOLEAN_MODE_OPEN - 1
#define INDEX_ALARMOUT_CLOSED       1       // NETDEV_BOOLEAN_MODE_CLOSE - 1

IMPLEMENT_DYNAMIC(CCfgAlarmIO, CDialog)

CCfgAlarmIO::CCfgAlarmIO(CWnd* pParent /*=NULL*/)
    : CDialog(CCfgAlarmIO::IDD, pParent)
    , m_dwAlarmOutputChnID(0)
    , m_dwAlarmOutputDuration(0)
{
    memset(&m_stAlarmOutputList, 0, sizeof(m_stAlarmOutputList));
}

CCfgAlarmIO::~CCfgAlarmIO()
{
}

void CCfgAlarmIO::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_ALARM_INPUT, m_oAlarmInputList);
    DDX_Control(pDX, IDC_COMBO_ALARM_OUTPUT_INDEX, m_oCBoxAlarmOutputIndex);
    DDX_Control(pDX, IDC_COMBO_ALARM_OUTPUT_STATUS, m_oCBoxAlarmOutputStatus);

    DDX_Text(pDX, IDC_EDIT_ALARM_OUTPUT_NAME, m_strAlarmOutputName);
    DDX_Text(pDX, IDC_EDIT_ALARM_OUTPUT_CHN_ID, m_dwAlarmOutputChnID);
    DDX_Text(pDX, IDC_EDIT_ALARM_OUTPUT_DURATION, m_dwAlarmOutputDuration);
}


BEGIN_MESSAGE_MAP(CCfgAlarmIO, CDialog)
    ON_BN_CLICKED(IDC_REFRESH, &CCfgAlarmIO::OnBnClickedRefresh)
    ON_BN_CLICKED(IDC_SAVE_ALARM_OUT_CFG, &CCfgAlarmIO::OnBnClickedSaveAlarmOutCfg)
    ON_CBN_SELCHANGE(IDC_COMBO_ALARM_OUTPUT_INDEX, &CCfgAlarmIO::OnCbnSelchangeComboAlarmOutputIndex)
    ON_EN_KILLFOCUS(IDC_EDIT_ALARM_OUTPUT_NAME, &CCfgAlarmIO::OnEnKillfocusEditAlarmOutputName)
    ON_CBN_SELCHANGE(IDC_COMBO_ALARM_OUTPUT_STATUS, &CCfgAlarmIO::OnCbnSelchangeComboAlarmOutputStatus)
    ON_EN_CHANGE(IDC_EDIT_ALARM_OUTPUT_CHN_ID, &CCfgAlarmIO::OnEnChangeEditAlarmOutputChnId)
    ON_EN_CHANGE(IDC_EDIT_ALARM_OUTPUT_DURATION, &CCfgAlarmIO::OnEnChangeEditAlarmOutputDuration)
    ON_BN_CLICKED(IDC_TRIGGER_ALARM_OUT, &CCfgAlarmIO::OnBnClickedTriggerAlarmOut)
END_MESSAGE_MAP()

BOOL CCfgAlarmIO::OnInitDialog()
{
    CDialog::OnInitDialog();
    CRect rc(0, 0, 0, 0);
    GetParent()->GetClientRect(&rc);
    ((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
    MoveWindow(&rc);

    initAlarmInputList();

    m_oCBoxAlarmOutputStatus.InsertString(INDEX_ALARMOUT_OPEN, _T("Normally Open"));
    m_oCBoxAlarmOutputStatus.InsertString(INDEX_ALARMOUT_CLOSED, _T("Normally Closed"));
    return TRUE;
}

void CCfgAlarmIO::initAlarmInputList()
{
    CString str="Alarm Name";
    m_oAlarmInputList.InsertColumn(0, str, LVCFMT_LEFT, 200, 50); 
    m_oAlarmInputList.SetExtendedStyle(m_oAlarmInputList.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES);
}

void CCfgAlarmIO::showByIndex(INT32 dwIndex)
{
    if (dwIndex < 0 || dwIndex > NETDEV_MAX_ALARM_OUT_NUM)
    {
        return;
    }

    m_dwAlarmOutputDuration = m_stAlarmOutputList.astAlarmOutputInfo[dwIndex].dwDurationSec;
    m_dwAlarmOutputChnID = m_stAlarmOutputList.astAlarmOutputInfo[dwIndex].dwChancelId;

    if (NETDEV_BOOLEAN_MODE_OPEN == m_stAlarmOutputList.astAlarmOutputInfo[dwIndex].enDefaultStatus)
    {
        m_oCBoxAlarmOutputStatus.SetCurSel(INDEX_ALARMOUT_OPEN);
    }
    else
    {
        m_oCBoxAlarmOutputStatus.SetCurSel(INDEX_ALARMOUT_CLOSED);
    }

    CHAR szTmp[NETDEV_LEN_64] = {0};
    UTF8ToMB(m_stAlarmOutputList.astAlarmOutputInfo[dwIndex].szName, szTmp, sizeof(szTmp) - 1);
    m_strAlarmOutputName = szTmp;

    UpdateData(FALSE);
    return;
}

/* Get Alarm Input List */
void CCfgAlarmIO::getAlarmInputInfo()
{
    LPVOID lpDevHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChannelID = ga_pMainDlg->GetChlID();
    INT32 dwCurDevIndex = ga_pMainDlg ->GetCurDeviceIndex();
    INT32 dwCurChlIndex = ga_pMainDlg->GetCurChlIndex();

    NETDEV_ALARM_INPUT_LIST_S stAlarmInputList ={0};

    INT32 dwBytesReturned = 0;
    BOOL bRet = NETDEV_GetDevConfig(lpDevHandle, dwChannelID, NETDEV_GET_ALARM_INPUTCFG, &stAlarmInputList, sizeof(stAlarmInputList), &dwBytesReturned);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Get alarm input info");
        return;
    }

    m_oAlarmInputList.DeleteAllItems();
    for(INT32 i = 0; i < stAlarmInputList.dwSize; i++)
    {
        CHAR szTmp[NETDEV_LEN_64] = {0};
        UTF8ToMB(stAlarmInputList.astAlarmInputInfo[i].szName, szTmp, sizeof(szTmp) - 1);
        strncpy(stAlarmInputList.astAlarmInputInfo[i].szName, szTmp, sizeof(stAlarmInputList.astAlarmInputInfo[i].szName) - 1);
        m_oAlarmInputList.InsertItem(i, szTmp);
    }
    gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstIOInfo->stInPutInfo = stAlarmInputList ;
    NETDEMO_LOG_SUCC(NULL, "Get alarm input info");

    UpdateData(FALSE);
    return;
}

/* Get alarm output info */
void CCfgAlarmIO::getAlarmOutputInfo()
{
    LPVOID lpDevHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChannelID = ga_pMainDlg->GetChlID();
    INT32 dwCurDevIndex = ga_pMainDlg ->GetCurDeviceIndex();
    INT32 dwCurChlIndex = ga_pMainDlg->GetCurChlIndex();

    INT32 dwBytesReturned = 0;
    BOOL bRet = NETDEV_GetDevConfig(lpDevHandle, dwChannelID, NETDEV_GET_ALARM_OUTPUTCFG, &m_stAlarmOutputList, sizeof(m_stAlarmOutputList), &dwBytesReturned);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Get alarm output info");
        return;
    }

    m_oCBoxAlarmOutputIndex.ResetContent();
    for (INT32 i = 0; i < m_stAlarmOutputList.dwSize; i++)
    {
        CString str;
        str.Format("%d", i);
        m_oCBoxAlarmOutputIndex.InsertString(i, str);
    }

    m_oCBoxAlarmOutputIndex.SetCurSel(0);
    showByIndex(0);
    gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstIOInfo->stOutPutInfo = m_stAlarmOutputList;
    NETDEMO_LOG_SUCC(NULL, "Get alarm output info"); 
    UpdateData(FALSE);
    return;
}

void CCfgAlarmIO::ReadGlobeToAlarmIO()
{
    INT32 dwCurDevIndex = ga_pMainDlg ->GetCurDeviceIndex();
    INT32 dwCurChlIndex = ga_pMainDlg->GetCurChlIndex();
    
    NETDEV_ALARM_INPUT_LIST_S stAlarmInputList = {0};
    if (NULL != gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstIOInfo)
    {
         stAlarmInputList = gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstIOInfo->stInPutInfo;
    }
    m_oAlarmInputList.DeleteAllItems();
    for(INT32 i = 0; i < stAlarmInputList.dwSize; i++)
    {
        m_oAlarmInputList.InsertItem(i, stAlarmInputList.astAlarmInputInfo[i].szName);
    }

    m_stAlarmOutputList = gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstIOInfo->stOutPutInfo;
    m_oCBoxAlarmOutputIndex.ResetContent();
    for (INT32 i = 0; i < m_stAlarmOutputList.dwSize; i++)
    {
        CString str;
        str.Format("%d", i);
        m_oCBoxAlarmOutputIndex.InsertString(i, str);
    }

    m_oCBoxAlarmOutputIndex.SetCurSel(0);
    showByIndex(0);
    
    UpdateData(FALSE);
}

void CCfgAlarmIO::OnBnClickedRefresh()
{
    INT32 dwCurDevIndex = ga_pMainDlg ->GetCurDeviceIndex();
    INT32 dwCurChlIndex = ga_pMainDlg->GetCurChlIndex();
    if(dwCurChlIndex <0 )
    {
        return;
    }

    if (NULL != gastDeviceInfo && NULL != gastDeviceInfo[dwCurDevIndex].pstChlInfo)
    {
        if(NULL == gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstIOInfo)
        {
            gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstIOInfo = new NETDEMO_INPUT_INFO_S();
        }

        /* Get alarm input info */
        getAlarmInputInfo();

        /* Get alarm output info */
        getAlarmOutputInfo();
    }

    UpdateData(FALSE);
    return;
}

void CCfgAlarmIO::OnBnClickedSaveAlarmOutCfg()
{
    LPVOID lpDevHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChannelID = ga_pMainDlg->GetChlID();
    INT32 dwCurDevIndex = ga_pMainDlg ->GetCurDeviceIndex();
    INT32 dwCurChlIndex = ga_pMainDlg->GetCurChlIndex();

    NETDEV_ALARM_OUTPUT_INFO_S stAlarmOutputInfo = {0};

    INT32 dwIndex = m_oCBoxAlarmOutputIndex.GetCurSel();
    if (dwIndex < 0 || dwIndex > NETDEV_MAX_ALARM_OUT_NUM)
    {
        return;
    }
    
    stAlarmOutputInfo = m_stAlarmOutputList.astAlarmOutputInfo[dwIndex];
    BOOL bRet = NETDEV_SetDevConfig(lpDevHandle, dwChannelID, NETDEV_SET_ALARM_OUTPUTCFG, &stAlarmOutputInfo, sizeof(stAlarmOutputInfo));
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Save alarm output");
        return;
    }
    gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstIOInfo->stOutPutInfo = m_stAlarmOutputList;
    NETDEMO_LOG_SUCC(NULL, "Save alarm output");

    return;
}

void CCfgAlarmIO::OnCbnSelchangeComboAlarmOutputIndex()
{
    INT32 dwIndex = m_oCBoxAlarmOutputIndex.GetCurSel();

    showByIndex(dwIndex);

    UpdateData(FALSE);
    return;
}

void CCfgAlarmIO::OnEnKillfocusEditAlarmOutputName()
{
    UpdateData(TRUE);

    INT32 dwIndex = m_oCBoxAlarmOutputIndex.GetCurSel();
    if (dwIndex < 0 || dwIndex > NETDEV_MAX_ALARM_OUT_NUM)
    {
        return;
    }

    strncpy(m_stAlarmOutputList.astAlarmOutputInfo[dwIndex].szName, m_strAlarmOutputName.GetBuffer(0), sizeof(m_stAlarmOutputList.astAlarmOutputInfo[dwIndex].szName) - 1);

    return;
}

void CCfgAlarmIO::OnCbnSelchangeComboAlarmOutputStatus()
{
    UpdateData(TRUE);

    INT32 dwIndex = m_oCBoxAlarmOutputIndex.GetCurSel();
    if (dwIndex < 0 || dwIndex > NETDEV_MAX_ALARM_OUT_NUM)
    {
        return;
    }

    if (INDEX_ALARMOUT_OPEN == m_oCBoxAlarmOutputStatus.GetCurSel())
    {
        m_stAlarmOutputList.astAlarmOutputInfo[dwIndex].enDefaultStatus = NETDEV_BOOLEAN_MODE_OPEN;
    }
    else
    {
        m_stAlarmOutputList.astAlarmOutputInfo[dwIndex].enDefaultStatus = NETDEV_BOOLEAN_MODE_CLOSE;
    }

    return;
}

void CCfgAlarmIO::OnEnChangeEditAlarmOutputChnId()
{
    UpdateData(TRUE);

    INT32 dwIndex = m_oCBoxAlarmOutputIndex.GetCurSel();
    if (dwIndex < 0 || dwIndex > NETDEV_MAX_ALARM_OUT_NUM)
    {
        return;
    }

    m_stAlarmOutputList.astAlarmOutputInfo[dwIndex].dwChancelId = m_dwAlarmOutputChnID;

    return;
}

void CCfgAlarmIO::OnEnChangeEditAlarmOutputDuration()
{
    UpdateData(TRUE);

    INT32 dwIndex = m_oCBoxAlarmOutputIndex.GetCurSel();
    if (dwIndex < 0 || dwIndex > NETDEV_MAX_ALARM_OUT_NUM)
    {
        return;
    }

    m_stAlarmOutputList.astAlarmOutputInfo[dwIndex].dwDurationSec = m_dwAlarmOutputDuration;

    return;
}

void CCfgAlarmIO::OnBnClickedTriggerAlarmOut()
{
    UpdateData(TRUE);

    LPVOID lpDevHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChannelID = ga_pMainDlg->GetChlID();

    INT32 dwIndex = m_oCBoxAlarmOutputIndex.GetCurSel();
    if (dwIndex < 0 || dwIndex > NETDEV_MAX_ALARM_OUT_NUM)
    {
        return;
    }

    NETDEV_TRIGGER_ALARM_OUTPUT_S stTriggerAlarmOutput;
    memset(&stTriggerAlarmOutput, 0, sizeof(NETDEV_TRIGGER_ALARM_OUTPUT_S));

    strncpy(stTriggerAlarmOutput.szName, m_stAlarmOutputList.astAlarmOutputInfo[dwIndex].szName, sizeof(stTriggerAlarmOutput.szName) - 1);

    stTriggerAlarmOutput.enOutputState = NETDEV_BOOLEAN_STATUS_ACTIVE;

    BOOL bRet = NETDEV_SetDevConfig(lpDevHandle, dwChannelID, NETDEV_TRIGGER_ALARM_OUTPUT, &stTriggerAlarmOutput, sizeof(NETDEV_TRIGGER_ALARM_OUTPUT_S));
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Trigger alarm out");
        return;
    }

    NETDEMO_LOG_SUCC(NULL, "Trigger alarm out");

    return;
}
