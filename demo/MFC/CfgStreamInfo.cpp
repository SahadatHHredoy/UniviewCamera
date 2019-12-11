#include "stdafx.h"
#include "NetDemo.h"
#include "CfgStreamInfo.h"


typedef enum tagNetDEMOVideoQualityIndex
{
    INDEX_VQ_L0 = 0,
    INDEX_VQ_L1,
    INDEX_VQ_L2,
    INDEX_VQ_L3,
    INDEX_VQ_L4,
    INDEX_VQ_L5,
    INDEX_VQ_L6,
    INDEX_VQ_L7,
    INDEX_VQ_L8,
    INDEX_VQ_L9,
    INDEX_VQ_LEVEL_INVALID = 0XFF

}NETDEMO_VIDEO_QUALITY_INDEX_E;

typedef struct tagNetDEVVideoQualityIndexConv
{
    INT32 dwComboIndex;                 /* combo index */
    INT32 dwVideoQualityEnum;           /* video quality enum */
}NETDEMO_VIDEO_QUALITY_INDEX_MAP_S;

static NETDEMO_VIDEO_QUALITY_INDEX_MAP_S gastVideoQualityMap[] = 
{
    {INDEX_VQ_L0, NETDEV_VQ_L0}, 
    {INDEX_VQ_L1, NETDEV_VQ_L1}, 
    {INDEX_VQ_L2, NETDEV_VQ_L2}, 
    {INDEX_VQ_L3, NETDEV_VQ_L3}, 
    {INDEX_VQ_L4, NETDEV_VQ_L4}, 
    {INDEX_VQ_L5, NETDEV_VQ_L5}, 
    {INDEX_VQ_L6, NETDEV_VQ_L6}, 
    {INDEX_VQ_L7, NETDEV_VQ_L7}, 
    {INDEX_VQ_L8, NETDEV_VQ_L8}, 
    {INDEX_VQ_L9, NETDEV_VQ_L9}
};

INT32 getVideoQualityEnmu(INT32 dwComboIndex)
{
    INT32 dwVQEnmu = 0XFF;
    INT32 dwSize = sizeof(gastVideoQualityMap) / sizeof(NETDEMO_VIDEO_QUALITY_INDEX_MAP_S);
    for (INT32 i = 0; i < dwSize; i++)
    {
        if (dwComboIndex == gastVideoQualityMap[i].dwComboIndex)
        {
            dwVQEnmu = gastVideoQualityMap[i].dwVideoQualityEnum;
            break;
        }
    }

    return dwVQEnmu;
}


INT32 getVideoQualityComboIndex(INT32 dwVideoQualityEnum)
{
    INT32 dwComboIndex = 0xff;
    INT32 dwSize = sizeof(gastVideoQualityMap) / sizeof(NETDEMO_VIDEO_QUALITY_INDEX_MAP_S);
    for (INT32 i = 0; i < dwSize; i++)
    {
        if (dwVideoQualityEnum == gastVideoQualityMap[i].dwVideoQualityEnum)
        {
            dwComboIndex = gastVideoQualityMap[i].dwComboIndex;
            break;
        }
    }

    return dwComboIndex;
}

IMPLEMENT_DYNAMIC(CCfgStreamInfo, CDialog)

CCfgStreamInfo::CCfgStreamInfo(CWnd* pParent /*=NULL*/)
    : CDialog(CCfgStreamInfo::IDD, pParent)
    , m_dwResWidth(0)
    , m_dwResHight(0)
    , m_dwBitRate(0)
    , m_dwFrameRate(0)
    , m_dwGOP(0)
{

}

CCfgStreamInfo::~CCfgStreamInfo()
{
}

void CCfgStreamInfo::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    DDX_Text(pDX, IDC_EDIT_BIT_RATE, m_dwBitRate);
    DDX_Text(pDX, IDC_EDIT_FRAME_RATE, m_dwFrameRate);
    DDX_Text(pDX, IDC_EDIT_RES_HIGHT, m_dwResHight);
    DDX_Text(pDX, IDC_EDIT_RES_WIDTH, m_dwResWidth);
    DDX_Text(pDX, IDC_EDIT_GOP, m_dwGOP);

    DDX_Control(pDX, IDC_COMBO_STREAM_INDEX, m_oCBoxStreamIndex);
    DDX_Control(pDX, IDC_COMBO_ENCODE_FORMAT, m_oCBoxEncodeFormat);
    DDX_Control(pDX, IDC_COMBO_QUALITY, m_oCBoxQuality);
}


BEGIN_MESSAGE_MAP(CCfgStreamInfo, CDialog)
    ON_BN_CLICKED(IDC_SAVE_VIDEO_STREAM, &CCfgStreamInfo::OnBnClickedSaveVideoStream)
    ON_BN_CLICKED(IDC_REFRESH, &CCfgStreamInfo::OnBnClickedRefresh)
    ON_CBN_SELCHANGE(IDC_COMBO_STREAM_INDEX, &CCfgStreamInfo::OnCbnSelchangeComboStreamIndex)
    ON_CBN_SELCHANGE(IDC_COMBO_ENCODE_FORMAT, &CCfgStreamInfo::OnCbnSelchangeComboEncodeFormat)
    ON_CBN_SELCHANGE(IDC_COMBO_QUALITY, &CCfgStreamInfo::OnCbnSelchangeComboQuality)
END_MESSAGE_MAP()

BOOL CCfgStreamInfo::OnInitDialog()
{
    CDialog::OnInitDialog();
    CRect rc(0, 0, 0, 0);
    GetParent()->GetClientRect(&rc);
    ((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
    MoveWindow(&rc);

    m_oCBoxStreamIndex.InsertString(NETDEV_LIVE_STREAM_INDEX_MAIN, _T("Main Stream"));
    m_oCBoxStreamIndex.InsertString(NETDEV_LIVE_STREAM_INDEX_AUX, _T("Sub Stream"));
    m_oCBoxStreamIndex.InsertString(NETDEV_LIVE_STREAM_INDEX_THIRD, _T("Third Stream"));
    m_oCBoxStreamIndex.SetCurSel(0);

    m_oCBoxEncodeFormat.InsertString(NETDEV_VIDEO_CODE_MJPEG, _T("MJPEG"));
    m_oCBoxEncodeFormat.InsertString(NETDEV_VIDEO_CODE_H264, _T("H.264"));
    m_oCBoxEncodeFormat.InsertString(NETDEV_VIDEO_CODE_H265, _T("H.265"));
    m_oCBoxEncodeFormat.SetCurSel(0);
    
    m_oCBoxQuality.InsertString(INDEX_VQ_L0, _T("1"));
    m_oCBoxQuality.InsertString(INDEX_VQ_L1, _T("2"));
    m_oCBoxQuality.InsertString(INDEX_VQ_L2, _T("3"));
    m_oCBoxQuality.InsertString(INDEX_VQ_L3, _T("4"));
    m_oCBoxQuality.InsertString(INDEX_VQ_L4, _T("5"));
    m_oCBoxQuality.InsertString(INDEX_VQ_L5, _T("6"));
    m_oCBoxQuality.InsertString(INDEX_VQ_L6, _T("7"));
    m_oCBoxQuality.InsertString(INDEX_VQ_L7, _T("8"));
    m_oCBoxQuality.InsertString(INDEX_VQ_L8, _T("9"));
    m_oCBoxQuality.InsertString(INDEX_VQ_L9, _T("10"));

    return TRUE;
}

void CCfgStreamInfo::showByIndex(INT32 dwIndex)
{
    if (dwIndex < 0 || dwIndex > 2)
    {
        return;
    }

    m_dwBitRate = m_astStreamInfo[dwIndex].dwBitRate;
    m_dwFrameRate = m_astStreamInfo[dwIndex].dwFrameRate;
    m_dwGOP = m_astStreamInfo[dwIndex].dwGop;
    m_dwResHight = m_astStreamInfo[dwIndex].dwHeight;
    m_dwResWidth = m_astStreamInfo[dwIndex].dwWidth;
    m_oCBoxQuality.SetCurSel(getVideoQualityComboIndex(m_astStreamInfo[dwIndex].enQuality));
    m_oCBoxEncodeFormat.SetCurSel(m_astStreamInfo[dwIndex].enCodeType);

    UpdateData(FALSE);
    return;
}


/* Get Stream Info */
void CCfgStreamInfo::getStreamInfo()
{
    LPVOID lpDevHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChannelID = ga_pMainDlg->GetChlID();
    INT32 dwCurDevIndex = ga_pMainDlg ->GetCurDeviceIndex();
    INT32 dwCurChlIndex = ga_pMainDlg->GetCurChlIndex();

    INT32 dwBytesReturned = 0;
    memset(&m_astStreamInfo, 0, sizeof(m_astStreamInfo));
    
    for (INT32 i = 0; i < 3; i++)
    {
        LPNETDEV_VIDEO_STREAM_INFO_S pstStreamInfo = &m_astStreamInfo[i];
        pstStreamInfo->enStreamType = (NETDEV_LIVE_STREAM_INDEX_E)i;

        BOOL bRet = NETDEV_GetDevConfig(lpDevHandle, dwChannelID, NETDEV_GET_STREAMCFG, pstStreamInfo, sizeof(NETDEV_VIDEO_STREAM_INFO_S), &dwBytesReturned);
        if (TRUE != bRet)
        {
            NETDEMO_LOG_ERROR(NULL, "Get stream info, stream type : %d", pstStreamInfo->enStreamType);
        }

        gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstVideoStreamInfo[i] =  m_astStreamInfo[i];
    }

    showByIndex(0);
    NETDEMO_LOG_SUCC(NULL, "Get stream info");
    UpdateData(FALSE);
    return;
}

/* Save video stream */
void CCfgStreamInfo::OnBnClickedSaveVideoStream()
{
    UpdateData(TRUE);

    INT32 dwIndex = m_oCBoxStreamIndex.GetCurSel();
    if (dwIndex < 0 || dwIndex > 2)
    {
        return;
    }

    LPVOID lpDevHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChannelID = ga_pMainDlg->GetChlID();
    INT32 dwCurDevIndex = ga_pMainDlg ->GetCurDeviceIndex();
    INT32 dwCurChlIndex = ga_pMainDlg->GetCurChlIndex();

    LPNETDEV_VIDEO_STREAM_INFO_S pstStreamInfo = &m_astStreamInfo[dwIndex];

    pstStreamInfo->enStreamType = (NETDEV_LIVE_STREAM_INDEX_E)dwIndex;
    pstStreamInfo->dwBitRate = m_dwBitRate;
    pstStreamInfo->dwFrameRate = m_dwFrameRate;
    pstStreamInfo->dwGop = m_dwGOP;

    dwIndex = m_oCBoxQuality.GetCurSel();
    pstStreamInfo->enQuality = (NETDEV_VIDEO_QUALITY_E)getVideoQualityEnmu(dwIndex);
    pstStreamInfo->dwHeight = m_dwResHight;
    pstStreamInfo->dwWidth = m_dwResWidth;

    BOOL bRet = NETDEV_SetDevConfig(lpDevHandle, dwChannelID, NETDEV_SET_STREAMCFG, pstStreamInfo, sizeof(NETDEV_VIDEO_STREAM_INFO_S));
    if (TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Save stream info");
        return;
    }

    if(gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstVideoStreamInfo != NULL)
    {
        gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstVideoStreamInfo[dwIndex] = m_astStreamInfo[dwIndex];

    }
    
    NETDEMO_LOG_SUCC(NULL, "Save stream info");

    return;
}

void CCfgStreamInfo::ReadGlobeToVideoStream()
{
    INT32 dwCurDevIndex = ga_pMainDlg ->GetCurDeviceIndex();
    INT32 dwCurChlIndex = ga_pMainDlg->GetCurChlIndex();

    if(NULL != gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstVideoStreamInfo)
    {
        memcpy(m_astStreamInfo, gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstVideoStreamInfo, sizeof(m_astStreamInfo));
    }
    
    showByIndex(0);
    UpdateData(FALSE);

    return;
}

/* Refresh */
void CCfgStreamInfo::OnBnClickedRefresh()
{
    INT32 dwCurDevIndex = ga_pMainDlg ->GetCurDeviceIndex();
    INT32 dwCurChlIndex = ga_pMainDlg->GetCurChlIndex();
    if(dwCurChlIndex <0 )
    {
        return;
    }

    if (NULL != gastDeviceInfo && NULL != gastDeviceInfo[dwCurDevIndex].pstChlInfo)
    {
        if(NULL == gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstVideoStreamInfo)
        {
            gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstVideoStreamInfo = new NETDEV_VIDEO_STREAM_INFO_S[3];
        }

        memset(gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstVideoStreamInfo ,0,sizeof(NETDEV_VIDEO_STREAM_INFO_S)*3);

        /* Get video stream info */
        getStreamInfo();
    }

    UpdateData(FALSE);
    return;
}

void CCfgStreamInfo::OnCbnSelchangeComboStreamIndex()
{
    UpdateData(TRUE);
    
    INT32 dwIndex = m_oCBoxStreamIndex.GetCurSel();
    if (dwIndex < 0 || dwIndex > 2)
    {
        return;
    }

    showByIndex(dwIndex);

    UpdateData(FALSE);
    return;
}


void CCfgStreamInfo::OnCbnSelchangeComboEncodeFormat()
{
    UpdateData(TRUE);

    INT32 dwIndex = m_oCBoxStreamIndex.GetCurSel();
    if (dwIndex < 0 || dwIndex > 2)
    {
        return;
    }

    m_astStreamInfo[dwIndex].enCodeType = (NETDEV_VIDEO_CODE_TYPE_E)m_oCBoxEncodeFormat.GetCurSel();

    return;
}

void CCfgStreamInfo::OnCbnSelchangeComboQuality()
{
    UpdateData(TRUE);

    INT32 dwIndex = m_oCBoxStreamIndex.GetCurSel();
    if (dwIndex < 0 || dwIndex > 2)
    {
        return;
    }

    dwIndex = m_oCBoxQuality.GetCurSel();
    m_astStreamInfo[dwIndex].enQuality = (NETDEV_VIDEO_QUALITY_E) getVideoQualityEnmu(dwIndex);
    return;
}
