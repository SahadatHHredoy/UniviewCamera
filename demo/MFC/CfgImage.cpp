// DlgConfigureImage.cpp : 
//

#include "stdafx.h"
#include "NetDemo.h"
#include "CfgImage.h"


// CCfgImage 

IMPLEMENT_DYNAMIC(CCfgImage, CDialog)

CCfgImage::CCfgImage(CWnd* pParent /*=NULL*/)
    : CDialog(CCfgImage::IDD, pParent)
    , m_dwBrightness(128)
    , m_dwContrast(128)
    , m_dwSaturation(128)
    , m_dwSharpness(128)
{

}

CCfgImage::~CCfgImage()
{
}

void CCfgImage::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    DDX_Text(pDX, IDC_EDIT_BRIGHTNESS, m_dwBrightness);
    DDX_Text(pDX, IDC_EDIT_SHARPNESS, m_dwSharpness);
    DDX_Text(pDX, IDC_EDIT_CONTRAST, m_dwContrast);
    DDX_Text(pDX, IDC_EDIT_SATURATION, m_dwSaturation);

    DDX_Control(pDX, IDC_SLIDER_BRIGHTNESS, m_oSldBrightness);
    DDX_Control(pDX, IDC_SLIDER_CONTRAST, m_oSldContrast);
    DDX_Control(pDX, IDC_SLIDER_SATURATION, m_oSldSaturation);
    DDX_Control(pDX, IDC_SLIDER_SHARPNESS, m_oSldSharpness);
}


BEGIN_MESSAGE_MAP(CCfgImage, CDialog)
    ON_BN_CLICKED(IDC_SAVE_IMAGE_INFO, &CCfgImage::OnBnClickedSaveImageInfo)
    ON_BN_CLICKED(IDC_REFRESH_IMAGE_CFG, &CCfgImage::OnBnClickedRefresh)
    ON_WM_HSCROLL()
    ON_EN_CHANGE(IDC_EDIT_BRIGHTNESS, &CCfgImage::OnEnChangeEditBrightness)
    ON_EN_KILLFOCUS(IDC_EDIT_BRIGHTNESS, &CCfgImage::OnEnKillfocusEditBrightness)
    ON_EN_CHANGE(IDC_EDIT_SATURATION, &CCfgImage::OnEnChangeEditSaturation)
    ON_EN_KILLFOCUS(IDC_EDIT_SATURATION, &CCfgImage::OnEnKillfocusEditSaturation)
    ON_EN_CHANGE(IDC_EDIT_CONTRAST, &CCfgImage::OnEnChangeEditContrast)
    ON_EN_KILLFOCUS(IDC_EDIT_CONTRAST, &CCfgImage::OnEnKillfocusEditContrast)
    ON_EN_KILLFOCUS(IDC_EDIT_SHARPNESS, &CCfgImage::OnEnKillfocusEditSharpness)
    ON_EN_CHANGE(IDC_EDIT_SHARPNESS, &CCfgImage::OnEnChangeEditSharpness)
END_MESSAGE_MAP()


BOOL CCfgImage::OnInitDialog()
{
    CDialog::OnInitDialog();
    CRect rc(0, 0, 0, 0);
    GetParent()->GetClientRect(&rc);
    ((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
    MoveWindow(&rc);

    m_oSldBrightness.SetRange(0, 255);
    m_oSldBrightness.SetTicFreq(1);
    m_oSldBrightness.SetPos(128);

    m_oSldContrast.SetRange(0, 255);
    m_oSldContrast.SetTicFreq(1);
    m_oSldContrast.SetPos(128);

    m_oSldSaturation.SetRange(0, 255);
    m_oSldSaturation.SetTicFreq(1);
    m_oSldSaturation.SetPos(128);

    m_oSldSharpness.SetRange(0, 255);
    m_oSldSharpness.SetTicFreq(1);
    m_oSldSharpness.SetPos(128);

    return TRUE;
}

void CCfgImage::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    char szTmp[16] = {0};
    if(IDC_SLIDER_BRIGHTNESS == pScrollBar->GetDlgCtrlID())
    {
        nPos = m_oSldBrightness.GetPos();
        sprintf_s(szTmp, sizeof(szTmp), "%d", nPos);
        GetDlgItem(IDC_EDIT_BRIGHTNESS)->SetWindowText(szTmp);
        m_dwBrightness = nPos;
    }

    if(IDC_SLIDER_CONTRAST == pScrollBar->GetDlgCtrlID())
    {
        nPos = m_oSldContrast.GetPos();
        sprintf_s(szTmp, sizeof(szTmp), "%d", nPos);
        GetDlgItem(IDC_EDIT_CONTRAST)->SetWindowText(szTmp);
        m_dwContrast = nPos;
    }

    if(IDC_SLIDER_SATURATION == pScrollBar->GetDlgCtrlID())
    {
        nPos = m_oSldSaturation.GetPos();
        sprintf_s(szTmp, sizeof(szTmp), "%d", nPos);
        GetDlgItem(IDC_EDIT_SATURATION)->SetWindowText(szTmp);
        m_dwSaturation = nPos;
    }

    if(IDC_SLIDER_SHARPNESS == pScrollBar->GetDlgCtrlID())
    {
        nPos = m_oSldSharpness.GetPos();
        sprintf_s(szTmp, sizeof(szTmp), "%d", nPos);
        GetDlgItem(IDC_EDIT_SHARPNESS)->SetWindowText(szTmp);
        m_dwSharpness = nPos;
    }

    CDialog::OnHScroll(nSBCode, nPos, pScrollBar);

    UpdateData(FALSE);
    return;
}

/* Get Image Config */
void CCfgImage::getImageCfg()
{
    LPVOID lpDevHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChannelID = ga_pMainDlg->GetChlID();
    INT32 dwCurDevIndex = ga_pMainDlg ->GetCurDeviceIndex();
    INT32 dwCurChlIndex = ga_pMainDlg->GetCurChlIndex();

    INT32 dwBytesReturned = 0;
    NETDEV_IMAGE_SETTING_S stImageInfo = {0};

    BOOL bRet = NETDEV_GetDevConfig(lpDevHandle, dwChannelID, NETDEV_GET_IMAGECFG, &stImageInfo, sizeof(NETDEV_IMAGE_SETTING_S), &dwBytesReturned);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Get image info");
        return;
    }

    m_dwBrightness = stImageInfo.dwBrightness;
    m_dwContrast = stImageInfo.dwContrast;
    m_dwSaturation = stImageInfo.dwSaturation;
    m_dwSharpness = stImageInfo.dwSharpness;

    m_oSldBrightness.SetPos(m_dwBrightness);
    m_oSldSaturation.SetPos(m_dwSaturation);
    m_oSldSharpness.SetPos(m_dwSharpness);
    m_oSldContrast.SetPos(m_dwContrast);
    memcpy(gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstImageInfo, &stImageInfo,sizeof(NETDEV_IMAGE_SETTING_S));

    NETDEMO_LOG_SUCC(NULL, "Get image info");

    UpdateData(FALSE);
    return;
}

void CCfgImage::OnBnClickedSaveImageInfo()
{
    UpdateData(TRUE);

    LPVOID lpDevHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChannelID = ga_pMainDlg->GetChlID();
    INT32 dwCurDevIndex = ga_pMainDlg ->GetCurDeviceIndex();
    INT32 dwCurChlIndex = ga_pMainDlg->GetCurChlIndex();

    NETDEV_IMAGE_SETTING_S stImageInfo = {0};

    stImageInfo.dwContrast = m_dwContrast;
    stImageInfo.dwBrightness = m_dwBrightness;
    stImageInfo.dwSaturation = m_dwSaturation;
    stImageInfo.dwSharpness = m_dwSharpness;

    BOOL bRet = NETDEV_SetDevConfig(lpDevHandle, dwChannelID, NETDEV_SET_IMAGECFG, &stImageInfo, sizeof(NETDEV_IMAGE_SETTING_S));
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Save image info");
        return;
    }
    if(NULL != gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstImageInfo)
    {
        memcpy(gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstImageInfo, &stImageInfo,sizeof(NETDEV_IMAGE_SETTING_S));
    }
    NETDEMO_LOG_SUCC(NULL, "Save image info");

    return;
}

void CCfgImage::ReadGlobeToImage()
{
    INT32 dwCurDevIndex = ga_pMainDlg ->GetCurDeviceIndex();
    INT32 dwCurChlIndex = ga_pMainDlg->GetCurChlIndex();
    
    NETDEV_IMAGE_SETTING_S stImageInfo;
    if(NULL != gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstImageInfo)
    {
        memcpy(&stImageInfo,gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstImageInfo,sizeof(NETDEV_IMAGE_SETTING_S));
    }
    m_dwBrightness = stImageInfo.dwBrightness;
    m_dwContrast = stImageInfo.dwContrast;
    m_dwSaturation = stImageInfo.dwSaturation;
    m_dwSharpness = stImageInfo.dwSharpness;

    m_oSldBrightness.SetPos(m_dwBrightness);
    m_oSldSaturation.SetPos(m_dwSaturation);
    m_oSldSharpness.SetPos(m_dwSharpness);
    m_oSldContrast.SetPos(m_dwContrast);
    UpdateData(FALSE);
}

void CCfgImage::OnBnClickedRefresh()
{
    INT32 dwCurDevIndex = ga_pMainDlg ->GetCurDeviceIndex();
    INT32 dwCurChlIndex = ga_pMainDlg->GetCurChlIndex();
    if(dwCurChlIndex <0 )
    {
        return;
    }
    if (NULL != gastDeviceInfo && NULL != gastDeviceInfo[dwCurDevIndex].pstChlInfo)
    {
        if(NULL == gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstImageInfo)
        {
            gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstImageInfo = new NETDEV_IMAGE_SETTING_S;
        }
        memset(gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstImageInfo ,0,sizeof(NETDEV_IMAGE_SETTING_S));
        /* Get Image Config */
        getImageCfg();
    }

    UpdateData(FALSE);
    return;
}


void CCfgImage::OnEnChangeEditBrightness()
{
    UpdateData(TRUE);
    m_oSldBrightness.SetPos(m_dwBrightness);

    return;
}

void CCfgImage::OnEnKillfocusEditBrightness()
{
    UpdateData(TRUE);
    if (m_dwBrightness < 0)
    {
        m_dwBrightness = 0;
    }
    else if (m_dwBrightness > 255)
    {
        m_dwBrightness = 255;
    }

    char szTmp[16] = {0};
    sprintf_s(szTmp, sizeof(szTmp), "%d", m_dwBrightness);
    GetDlgItem(IDC_EDIT_BRIGHTNESS)->SetWindowText(szTmp);

    UpdateData(FALSE);
    return;
}

void CCfgImage::OnEnChangeEditSaturation()
{
    UpdateData(TRUE);
    m_oSldSaturation.SetPos(m_dwSaturation);

    return;
}

void CCfgImage::OnEnKillfocusEditSaturation()
{
    UpdateData(TRUE);
    if (m_dwSaturation < 0)
    {
        m_dwSaturation = 0;
    }
    else if (m_dwSaturation > 255)
    {
        m_dwSaturation = 255;
    }

    char szTmp[16] = {0};
    sprintf_s(szTmp, sizeof(szTmp), "%d", m_dwSaturation);
    GetDlgItem(IDC_EDIT_SATURATION)->SetWindowText(szTmp);

    UpdateData(FALSE);
    return;
}

void CCfgImage::OnEnChangeEditContrast()
{
    UpdateData(TRUE);
    m_oSldContrast.SetPos(m_dwContrast);

    return;
}

void CCfgImage::OnEnKillfocusEditContrast()
{
    UpdateData(TRUE);
    if (m_dwContrast < 0)
    {
        m_dwContrast = 0;
    }
    else if (m_dwContrast > 255)
    {
        m_dwContrast = 255;
    }

    char szTmp[16] = {0};
    sprintf_s(szTmp, sizeof(szTmp), "%d", m_dwContrast);
    GetDlgItem(IDC_EDIT_CONTRAST)->SetWindowText(szTmp);

    UpdateData(FALSE);
    return;
}

void CCfgImage::OnEnChangeEditSharpness()
{
    UpdateData(TRUE);
    m_oSldSharpness.SetPos(m_dwSharpness);

    return;
}


void CCfgImage::OnEnKillfocusEditSharpness()
{
    UpdateData(TRUE);
    if (m_dwSharpness < 0)
    {
        m_dwSharpness = 0;
    }
    else if (m_dwSharpness > 255)
    {
        m_dwSharpness = 255;
    }

    char szTmp[16] = {0};
    sprintf_s(szTmp, sizeof(szTmp), "%d", m_dwSharpness);
    GetDlgItem(IDC_EDIT_SHARPNESS)->SetWindowText(szTmp);

    UpdateData(FALSE);
    return;
}

