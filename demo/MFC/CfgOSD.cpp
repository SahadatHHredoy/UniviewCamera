#include "stdafx.h"
#include "NetDemo.h"
#include "CfgOSD.h"

IMPLEMENT_DYNAMIC(CCfgOSD, CDialog)

CCfgOSD::CCfgOSD(CWnd* pParent /*=NULL*/)
    : CDialog(CCfgOSD::IDD, pParent)
    , m_strOSDName("")
    , m_strOSDText_1("")
    , m_strOSDText_2("")
    , m_strOSDText_3("")
    , m_strOSDText_4("")
    , m_strOSDText_5("")
    , m_strOSDText_6("")
    , m_dwOSDNamePosX(0)
    , m_dwOSDNamePosY(0)
    , m_dwOSDTimePosX(0)
    , m_dwOSDTimePosY(0)
    , m_dwOSDText_1_PosX(0)
    , m_dwOSDText_1_PosY(0)
    , m_dwOSDText_2_PosX(0)
    , m_dwOSDText_2_PosY(0)
    , m_dwOSDText_3_PosX(0)
    , m_dwOSDText_3_PosY(0)
    , m_dwOSDText_4_PosX(0)
    , m_dwOSDText_4_PosY(0)
    , m_dwOSDText_5_PosX(0)
    , m_dwOSDText_5_PosY(0)
    , m_dwOSDText_6_PosX(0)
    , m_dwOSDText_6_PosY(0)
{
    m_bEnableOSDTime = FALSE;
    m_bEnableOSDName = FALSE;
    m_bEnableText1 = FALSE;
    m_bEnableText2 = FALSE;
    m_bEnableText3 = FALSE;
    m_bEnableText4 = FALSE;
    m_bEnableText5 = FALSE;
    m_bEnableText6 = FALSE;
}

CCfgOSD::~CCfgOSD()
{
}

void CCfgOSD::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    DDX_Check(pDX, IDC_CHECK_ENABLE_TIME, m_bEnableOSDTime);
    DDX_Control(pDX, IDC_COMBO_DATE_FORMAT, m_oCBoxDateFormat);
    DDX_Control(pDX, IDC_COMBO_TIME_FORMAT, m_oCBoxTimeFormat);

    DDX_Check(pDX, IDC_CHECK_ENABLE_NAME, m_bEnableOSDName);
    DDX_Check(pDX, IDC_CHECK_ENABLE_OSD_TEXT_1, m_bEnableText1);
    DDX_Check(pDX, IDC_CHECK_ENABLE_OSD_TEXT_2, m_bEnableText2);
    DDX_Check(pDX, IDC_CHECK_ENABLE_OSD_TEXT_3, m_bEnableText3);
    DDX_Check(pDX, IDC_CHECK_ENABLE_OSD_TEXT_4, m_bEnableText4);
    DDX_Check(pDX, IDC_CHECK_ENABLE_OSD_TEXT_5, m_bEnableText5);
    DDX_Check(pDX, IDC_CHECK_ENABLE_OSD_TEXT_6, m_bEnableText6);

    DDX_Text(pDX, IDC_EDIT_OSD_NAME, m_strOSDName);
    DDX_Text(pDX, IDC_EDIT_OSD_TEXT_1, m_strOSDText_1);
    DDX_Text(pDX, IDC_EDIT_OSD_TEXT_2, m_strOSDText_2);
    DDX_Text(pDX, IDC_EDIT_OSD_TEXT_3, m_strOSDText_3);
    DDX_Text(pDX, IDC_EDIT_OSD_TEXT_4, m_strOSDText_4);
    DDX_Text(pDX, IDC_EDIT_OSD_TEXT_5, m_strOSDText_5);
    DDX_Text(pDX, IDC_EDIT_OSD_TEXT_6, m_strOSDText_6);

    DDX_Text(pDX, IDC_EDIT_TIME_POS_X, m_dwOSDTimePosX);
    DDX_Text(pDX, IDC_EDIT_TIME_POS_Y, m_dwOSDTimePosY);
    DDX_Text(pDX, IDC_EDIT_NAME_POS_X, m_dwOSDNamePosX);
    DDX_Text(pDX, IDC_EDIT_NAME_POS_Y, m_dwOSDNamePosY);
    DDX_Text(pDX, IDC_EDIT_TEXT_1_POS_X, m_dwOSDText_1_PosX);
    DDX_Text(pDX, IDC_EDIT_TEXT_1_POS_Y, m_dwOSDText_1_PosY);
    DDX_Text(pDX, IDC_EDIT_TEXT_2_POS_X, m_dwOSDText_2_PosX);
    DDX_Text(pDX, IDC_EDIT_TEXT_2_POS_Y, m_dwOSDText_2_PosY);
    DDX_Text(pDX, IDC_EDIT_TEXT_3_POS_X, m_dwOSDText_3_PosX);
    DDX_Text(pDX, IDC_EDIT_TEXT_3_POS_Y, m_dwOSDText_3_PosY);
    DDX_Text(pDX, IDC_EDIT_TEXT_4_POS_X, m_dwOSDText_4_PosX);
    DDX_Text(pDX, IDC_EDIT_TEXT_4_POS_Y, m_dwOSDText_4_PosY);
    DDX_Text(pDX, IDC_EDIT_TEXT_5_POS_X, m_dwOSDText_5_PosX);
    DDX_Text(pDX, IDC_EDIT_TEXT_5_POS_Y, m_dwOSDText_5_PosY);
    DDX_Text(pDX, IDC_EDIT_TEXT_6_POS_X, m_dwOSDText_6_PosX);
    DDX_Text(pDX, IDC_EDIT_TEXT_6_POS_Y, m_dwOSDText_6_PosY);
}


BEGIN_MESSAGE_MAP(CCfgOSD, CDialog)
    ON_BN_CLICKED(IDC_SAVE_OSD, &CCfgOSD::OnBnClickedSaveOsd)
    ON_BN_CLICKED(IDC_REFRESH, &CCfgOSD::OnBnClickedRefresh)
END_MESSAGE_MAP()

BOOL CCfgOSD::OnInitDialog()
{
    CDialog::OnInitDialog();
    CRect rc(0, 0, 0, 0);
    GetParent()->GetClientRect(&rc);
    ((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
    MoveWindow(&rc);

    m_oCBoxDateFormat.InsertString(NETDEV_OSD_DATE_FORMAT_CAP_MD_YYYY, _T("M/d/yyyy"));
    m_oCBoxDateFormat.InsertString(NETDEV_OSD_DATE_FORMAT_CAP_MMDD_YYYY, _T("MM/dd/yyyy"));
    m_oCBoxDateFormat.InsertString(NETDEV_OSD_DATE_FORMAT_CAP_DDMM_YYYY, _T("dd/MM/yyyy"));
    m_oCBoxDateFormat.InsertString(NETDEV_OSD_DATE_FORMAT_CAP_YYYY_MMDD, _T("yyyy/MM/dd"));
    m_oCBoxDateFormat.InsertString(NETDEV_OSD_DATE_FORMAT_CAP_YYYYMMDDB, _T("yyyy-MM-dd"));
    m_oCBoxDateFormat.InsertString(NETDEV_OSD_DATE_FORMAT_CAP_XX_MMDD_YYYY, _T("dddd, MMMM dd, yyyy"));
    m_oCBoxDateFormat.InsertString(NETDEV_OSD_DATE_FORMAT_CAP_MMMMDD_YYYY, _T("MMMM dd, yyyy"));
    m_oCBoxDateFormat.InsertString(NETDEV_OSD_DATE_FORMAT_CAP_DDMMMM_YYYY, _T("dd MMMM, yyyy"));
    m_oCBoxDateFormat.SetCurSel(0);

    m_oCBoxTimeFormat.InsertString(NETDEV_OSD_TIME_FORMAT_CAP_HHMMSS , _T("HH:mm:ss"));
    m_oCBoxTimeFormat.InsertString(NETDEV_OSD_TIME_FORMAT_CAP_HH_MM_SS_PM , _T("hh:mm:ss tt"));
    m_oCBoxTimeFormat.SetCurSel(NETDEV_OSD_TIME_FORMAT_CAP_HHMMSS);

    return TRUE;
}

/* Get OSD */
void CCfgOSD::getOSD()
{
    LPVOID lpDevHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChannelID = ga_pMainDlg->GetChlID();
    INT32 dwCurDevIndex = ga_pMainDlg ->GetCurDeviceIndex();
    INT32 dwCurChlIndex = ga_pMainDlg->GetCurChlIndex();

    NETDEV_VIDEO_OSD_CFG_S stOSDInfo = {0};

    INT32 dwBytesReturned = 0;
    BOOL bRet = NETDEV_GetDevConfig(lpDevHandle, dwChannelID, NETDEV_GET_OSDCFG, &stOSDInfo, sizeof(stOSDInfo), &dwBytesReturned);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Get OSD cfg");
        return;
    }
    
    /* Time */
    m_bEnableOSDTime = stOSDInfo.stTimeOSD.bEnableFlag;
    m_dwOSDTimePosX = stOSDInfo.stTimeOSD.stAreaScope.dwLocateX;
    m_dwOSDTimePosY = stOSDInfo.stTimeOSD.stAreaScope.dwLocateY;
    m_oCBoxDateFormat.SetCurSel(stOSDInfo.stTimeOSD.udwDateFormat);
    m_oCBoxTimeFormat.SetCurSel(stOSDInfo.stTimeOSD.udwTimeFormat);

    /* NAME */
    m_bEnableOSDName = stOSDInfo.stNameOSD.bEnableFlag;

    CHAR szTmp[NETDEV_LEN_64] = {0};
    UTF8ToMB(stOSDInfo.stNameOSD.szOSDText, szTmp, sizeof(szTmp) - 1);
    m_strOSDName = szTmp;
    m_dwOSDNamePosX = stOSDInfo.stNameOSD.stAreaScope.dwLocateX;
    m_dwOSDNamePosY = stOSDInfo.stNameOSD.stAreaScope.dwLocateY;

    /* Text */
    m_bEnableText1 = stOSDInfo.astTextOverlay[0].bEnableFlag;
    memset(szTmp, 0, sizeof(szTmp));
    UTF8ToMB(stOSDInfo.astTextOverlay[0].szOSDText, szTmp, sizeof(szTmp) - 1);
    m_strOSDText_1 = szTmp;
    m_dwOSDText_1_PosX = stOSDInfo.astTextOverlay[0].stAreaScope.dwLocateX;
    m_dwOSDText_1_PosY = stOSDInfo.astTextOverlay[0].stAreaScope.dwLocateY;

    memset(szTmp, 0, sizeof(szTmp));
    UTF8ToMB(stOSDInfo.astTextOverlay[1].szOSDText, szTmp, sizeof(szTmp) - 1);
    m_bEnableText2 = stOSDInfo.astTextOverlay[1].bEnableFlag;
    m_strOSDText_2 = szTmp;
    m_dwOSDText_2_PosX = stOSDInfo.astTextOverlay[1].stAreaScope.dwLocateX;
    m_dwOSDText_2_PosY = stOSDInfo.astTextOverlay[1].stAreaScope.dwLocateY;

    m_bEnableText3 = stOSDInfo.astTextOverlay[2].bEnableFlag;
    memset(szTmp, 0, sizeof(szTmp));
    UTF8ToMB(stOSDInfo.astTextOverlay[2].szOSDText, szTmp, sizeof(szTmp) - 1);
    m_strOSDText_3 = szTmp;
    m_dwOSDText_3_PosX = stOSDInfo.astTextOverlay[2].stAreaScope.dwLocateX;
    m_dwOSDText_3_PosY = stOSDInfo.astTextOverlay[2].stAreaScope.dwLocateY;

    m_bEnableText4 = stOSDInfo.astTextOverlay[3].bEnableFlag;
    memset(szTmp, 0, sizeof(szTmp));
    UTF8ToMB(stOSDInfo.astTextOverlay[3].szOSDText, szTmp, sizeof(szTmp) - 1);
    m_strOSDText_4 = szTmp;
    m_dwOSDText_4_PosX = stOSDInfo.astTextOverlay[3].stAreaScope.dwLocateX;
    m_dwOSDText_4_PosY = stOSDInfo.astTextOverlay[3].stAreaScope.dwLocateY;

    m_bEnableText5 = stOSDInfo.astTextOverlay[4].bEnableFlag;
    memset(szTmp, 0, sizeof(szTmp));
    UTF8ToMB(stOSDInfo.astTextOverlay[4].szOSDText, szTmp, sizeof(szTmp) - 1);
    m_strOSDText_5 = szTmp;
    m_dwOSDText_5_PosX = stOSDInfo.astTextOverlay[4].stAreaScope.dwLocateX;
    m_dwOSDText_5_PosY = stOSDInfo.astTextOverlay[4].stAreaScope.dwLocateY;

    m_bEnableText6 = stOSDInfo.astTextOverlay[5].bEnableFlag;
    memset(szTmp, 0, sizeof(szTmp));
    UTF8ToMB(stOSDInfo.astTextOverlay[5].szOSDText, szTmp, sizeof(szTmp) - 1);
    m_strOSDText_6 = szTmp;
    m_dwOSDText_6_PosX = stOSDInfo.astTextOverlay[5].stAreaScope.dwLocateX;
    m_dwOSDText_6_PosY = stOSDInfo.astTextOverlay[5].stAreaScope.dwLocateY;

    NETDEMO_LOG_SUCC(NULL, "Get OSD cfg");
    memcpy(gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstOSDInfo, &stOSDInfo,sizeof(stOSDInfo));
    UpdateData(FALSE);
    return;
}

/* Save OSD */
void CCfgOSD::OnBnClickedSaveOsd()
{
    UpdateData(TRUE);

    LPVOID lpDevHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChannelID = ga_pMainDlg->GetChlID();
    INT32 dwCurDevIndex = ga_pMainDlg ->GetCurDeviceIndex();
    INT32 dwCurChlIndex = ga_pMainDlg->GetCurChlIndex();


    NETDEV_VIDEO_OSD_CFG_S stOSDInfo = {0};

    /* Time */
    stOSDInfo.stTimeOSD.bEnableFlag = 1;
    stOSDInfo.stTimeOSD.stAreaScope.dwLocateX = m_dwOSDTimePosX;
    stOSDInfo.stTimeOSD.stAreaScope.dwLocateY = m_dwOSDTimePosY;
    stOSDInfo.stTimeOSD.udwDateFormat = m_oCBoxDateFormat.GetCurSel();
    stOSDInfo.stTimeOSD.udwTimeFormat = m_oCBoxTimeFormat.GetCurSel();

    CHAR szTmp[NETDEV_LEN_64] = {0};

    /* NAME */
    if (m_strOSDName.GetLength() > 0)
    {
        stOSDInfo.stNameOSD.bEnableFlag = 1;
        MBToUTF8(m_strOSDName.GetBuffer(0), szTmp, sizeof(szTmp) - 1);
        strncpy(stOSDInfo.stNameOSD.szOSDText, szTmp, sizeof(szTmp) - 1);
        stOSDInfo.stNameOSD.stAreaScope.dwLocateX = m_dwOSDNamePosX;
        stOSDInfo.stNameOSD.stAreaScope.dwLocateY = m_dwOSDNamePosY;
    }

    /* Text */
    if (m_strOSDText_1.GetLength() > 0)
    {
        stOSDInfo.astTextOverlay[0].bEnableFlag = 1;
        MBToUTF8(m_strOSDText_1.GetBuffer(0), szTmp, sizeof(szTmp) - 1);
        strncpy(stOSDInfo.astTextOverlay[0].szOSDText, szTmp, sizeof(szTmp) - 1);
        stOSDInfo.astTextOverlay[0].stAreaScope.dwLocateX = m_dwOSDText_1_PosX;
        stOSDInfo.astTextOverlay[0].stAreaScope.dwLocateY = m_dwOSDText_1_PosY;

    }
    
    if (m_strOSDText_2.GetLength() > 0)
    {
        stOSDInfo.astTextOverlay[1].bEnableFlag = 1;
        memset(szTmp, 0, sizeof(szTmp));
        MBToUTF8(m_strOSDText_2.GetBuffer(0), szTmp, sizeof(szTmp) - 1);
        strncpy(stOSDInfo.astTextOverlay[1].szOSDText, szTmp, sizeof(szTmp) - 1);
        stOSDInfo.astTextOverlay[1].stAreaScope.dwLocateX = m_dwOSDText_2_PosX;
        stOSDInfo.astTextOverlay[1].stAreaScope.dwLocateY = m_dwOSDText_2_PosY;
    }

    if (m_strOSDText_3.GetLength() > 0)
    {
        stOSDInfo.astTextOverlay[2].bEnableFlag = 1;
        memset(szTmp, 0, sizeof(szTmp));
        MBToUTF8(m_strOSDText_3.GetBuffer(0), szTmp, sizeof(szTmp) - 1);
        strncpy(stOSDInfo.astTextOverlay[2].szOSDText, szTmp, sizeof(szTmp) - 1);
        stOSDInfo.astTextOverlay[2].stAreaScope.dwLocateX = m_dwOSDText_3_PosX;
        stOSDInfo.astTextOverlay[2].stAreaScope.dwLocateY = m_dwOSDText_3_PosY;
    }
   

    if (m_strOSDText_4.GetLength() > 0)
    {
        stOSDInfo.astTextOverlay[3].bEnableFlag = 1;
        memset(szTmp, 0, sizeof(szTmp));
        MBToUTF8(m_strOSDText_4.GetBuffer(0), szTmp, sizeof(szTmp) - 1);
        strncpy(stOSDInfo.astTextOverlay[3].szOSDText, szTmp, sizeof(szTmp) - 1);
        stOSDInfo.astTextOverlay[3].stAreaScope.dwLocateX = m_dwOSDText_4_PosX;
        stOSDInfo.astTextOverlay[3].stAreaScope.dwLocateY = m_dwOSDText_4_PosY;
    }
    

    if (m_strOSDText_5.GetLength() > 0)
    {
        stOSDInfo.astTextOverlay[4].bEnableFlag = 1;
        memset(szTmp, 0, sizeof(szTmp));
        MBToUTF8(m_strOSDText_5.GetBuffer(0), szTmp, sizeof(szTmp) - 1);
        strncpy(stOSDInfo.astTextOverlay[4].szOSDText, szTmp, sizeof(szTmp) - 1);
        stOSDInfo.astTextOverlay[4].stAreaScope.dwLocateX = m_dwOSDText_5_PosX;
        stOSDInfo.astTextOverlay[4].stAreaScope.dwLocateY = m_dwOSDText_5_PosY;
    }
    
    if (m_strOSDText_6.GetLength() > 0)
    {
        stOSDInfo.astTextOverlay[5].bEnableFlag = 1;
        memset(szTmp, 0, sizeof(szTmp));
        MBToUTF8(m_strOSDText_6.GetBuffer(0), szTmp, sizeof(szTmp) - 1);
        strncpy(stOSDInfo.astTextOverlay[5].szOSDText, szTmp, sizeof(szTmp) - 1);
        stOSDInfo.astTextOverlay[5].stAreaScope.dwLocateX = m_dwOSDText_6_PosX;
        stOSDInfo.astTextOverlay[5].stAreaScope.dwLocateY = m_dwOSDText_6_PosY;
    }
    

    stOSDInfo.wTextNum = 6;

    BOOL bRet = NETDEV_SetDevConfig(lpDevHandle, dwChannelID, NETDEV_SET_OSDCFG, &stOSDInfo, sizeof(stOSDInfo));
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Save OSD cfg");
        return;
    }
    if(NULL != gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstOSDInfo)
    {
        memcpy(gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstOSDInfo, &stOSDInfo,sizeof(NETDEV_VIDEO_OSD_CFG_S));
    }
    NETDEMO_LOG_SUCC(NULL, "Save OSD cfg");
    return;
}

void CCfgOSD::ReadGlobeToOSD()
{
    INT32 dwCurDevIndex = ga_pMainDlg ->GetCurDeviceIndex();
    INT32 dwCurChlIndex = ga_pMainDlg->GetCurChlIndex();
    
    NETDEV_VIDEO_OSD_CFG_S stOSDInfo = {0};
    if(NULL != gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstOSDInfo)
    {
        memcpy(&stOSDInfo,gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstOSDInfo,sizeof(stOSDInfo));
    }
    
    /* Time */
    m_bEnableOSDTime = stOSDInfo.stTimeOSD.bEnableFlag;
    m_dwOSDTimePosX = stOSDInfo.stTimeOSD.stAreaScope.dwLocateX;
    m_dwOSDTimePosY = stOSDInfo.stTimeOSD.stAreaScope.dwLocateY;
    m_oCBoxDateFormat.SetCurSel(stOSDInfo.stTimeOSD.udwDateFormat);
    m_oCBoxTimeFormat.SetCurSel(stOSDInfo.stTimeOSD.udwTimeFormat);

    /* NAME */
    m_bEnableOSDName = stOSDInfo.stNameOSD.bEnableFlag;

    CHAR szTmp[NETDEV_LEN_64] = {0};
    UTF8ToMB(stOSDInfo.stNameOSD.szOSDText, szTmp, sizeof(szTmp) - 1);
    m_strOSDName = szTmp;
    m_dwOSDNamePosX = stOSDInfo.stNameOSD.stAreaScope.dwLocateX;
    m_dwOSDNamePosY = stOSDInfo.stNameOSD.stAreaScope.dwLocateY;

    /* Text */
    m_bEnableText1 = stOSDInfo.astTextOverlay[0].bEnableFlag;
    memset(szTmp, 0, sizeof(szTmp));
    UTF8ToMB(stOSDInfo.astTextOverlay[0].szOSDText, szTmp, sizeof(szTmp) - 1);
    m_strOSDText_1 = szTmp;
    m_dwOSDText_1_PosX = stOSDInfo.astTextOverlay[0].stAreaScope.dwLocateX;
    m_dwOSDText_1_PosY = stOSDInfo.astTextOverlay[0].stAreaScope.dwLocateY;

    memset(szTmp, 0, sizeof(szTmp));
    UTF8ToMB(stOSDInfo.astTextOverlay[1].szOSDText, szTmp, sizeof(szTmp) - 1);
    m_bEnableText2 = stOSDInfo.astTextOverlay[1].bEnableFlag;
    m_strOSDText_2 = szTmp;
    m_dwOSDText_2_PosX = stOSDInfo.astTextOverlay[1].stAreaScope.dwLocateX;
    m_dwOSDText_2_PosY = stOSDInfo.astTextOverlay[1].stAreaScope.dwLocateY;

    m_bEnableText3 = stOSDInfo.astTextOverlay[2].bEnableFlag;
    memset(szTmp, 0, sizeof(szTmp));
    UTF8ToMB(stOSDInfo.astTextOverlay[2].szOSDText, szTmp, sizeof(szTmp) - 1);
    m_strOSDText_3 = szTmp;
    m_dwOSDText_3_PosX = stOSDInfo.astTextOverlay[2].stAreaScope.dwLocateX;
    m_dwOSDText_3_PosY = stOSDInfo.astTextOverlay[2].stAreaScope.dwLocateY;

    m_bEnableText4 = stOSDInfo.astTextOverlay[3].bEnableFlag;
    memset(szTmp, 0, sizeof(szTmp));
    UTF8ToMB(stOSDInfo.astTextOverlay[3].szOSDText, szTmp, sizeof(szTmp) - 1);
    m_strOSDText_4 = szTmp;
    m_dwOSDText_4_PosX = stOSDInfo.astTextOverlay[3].stAreaScope.dwLocateX;
    m_dwOSDText_4_PosY = stOSDInfo.astTextOverlay[3].stAreaScope.dwLocateY;

    m_bEnableText5 = stOSDInfo.astTextOverlay[4].bEnableFlag;
    memset(szTmp, 0, sizeof(szTmp));
    UTF8ToMB(stOSDInfo.astTextOverlay[4].szOSDText, szTmp, sizeof(szTmp) - 1);
    m_strOSDText_5 = szTmp;
    m_dwOSDText_5_PosX = stOSDInfo.astTextOverlay[4].stAreaScope.dwLocateX;
    m_dwOSDText_5_PosY = stOSDInfo.astTextOverlay[4].stAreaScope.dwLocateY;

    m_bEnableText6 = stOSDInfo.astTextOverlay[5].bEnableFlag;
    memset(szTmp, 0, sizeof(szTmp));
    UTF8ToMB(stOSDInfo.astTextOverlay[5].szOSDText, szTmp, sizeof(szTmp) - 1);
    m_strOSDText_6 = szTmp;
    m_dwOSDText_6_PosX = stOSDInfo.astTextOverlay[5].stAreaScope.dwLocateX;
    m_dwOSDText_6_PosY = stOSDInfo.astTextOverlay[5].stAreaScope.dwLocateY;
    UpdateData(FALSE);
}

/* Refresh */
void CCfgOSD::OnBnClickedRefresh()
{
    INT32 dwCurDevIndex = ga_pMainDlg ->GetCurDeviceIndex();
    INT32 dwCurChlIndex = ga_pMainDlg->GetCurChlIndex();
    if(dwCurChlIndex <0 )
    {
        return;
    }
    if (NULL != gastDeviceInfo && NULL != gastDeviceInfo[dwCurDevIndex].pstChlInfo)
    {
        if(NULL == gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstOSDInfo)
        {
            gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstOSDInfo = new NETDEV_VIDEO_OSD_CFG_S;
        }
        memset(gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstOSDInfo ,0,sizeof(NETDEV_VIDEO_OSD_CFG_S));
        /* Get OSD */
        getOSD();
    }
    
    UpdateData(FALSE);
    return;
}
