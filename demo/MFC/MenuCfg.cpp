#include "stdafx.h"
#include "NetDemo.h"
#include "MenuCfg.h"

IMPLEMENT_DYNAMIC(CMenuCfg, CDialog)

CMenuCfg::CMenuCfg(CWnd* pParent /*=NULL*/)
    : CDialog(CMenuCfg::IDD, pParent)
{

}

CMenuCfg::~CMenuCfg()
{
}

void CMenuCfg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TAB_PRIMARYMENU, m_oTabConfigure);
}

/* Tab index */
typedef enum tabIndexConfig
{
    TAB_INDEX_DEVICE_BASIC  = 0,
    TAB_INDEX_NETWORK,
    TAB_INDEX_VIDEO_STREAM,
    TAB_INDEX_IMAGE,
    TAB_INDEX_OSD,
    TAB_INDEX_ALARM_IO,
    TAB_INDEX_PRIVACY_MASK,
    TAB_INDEX_MOTION,
    TAB_INDEX_TEMPER
};


BOOL CMenuCfg::OnInitDialog()
{
    CDialog::OnInitDialog();

    CString str = "Basic";
    m_oTabConfigure.InsertItem(TAB_INDEX_DEVICE_BASIC, str);
    m_oDlgDeviceBasic.Create(IDD_CFG_DEVICE_BASIC, &m_oTabConfigure);
    m_oDlgDeviceBasic.ShowWindow(SW_SHOW);

    str ="Network";
    m_oTabConfigure.InsertItem(TAB_INDEX_NETWORK, str);
    m_oDlgNetwork.Create(IDD_CHILD_CFG_NETWORK, &m_oTabConfigure);
    m_oDlgNetwork.ShowWindow(SW_HIDE);

    str = "Video";
    m_oTabConfigure.InsertItem(TAB_INDEX_VIDEO_STREAM, str);
    m_oDlgVideoStream.Create(IDD_CFG_STREAM, &m_oTabConfigure);
    m_oDlgVideoStream.ShowWindow(SW_HIDE);

    str = "Image";
    m_oTabConfigure.InsertItem(TAB_INDEX_IMAGE, str);
    m_oDlgImage.Create(IDD_CFG_IMAGE, &m_oTabConfigure);
    m_oDlgImage.ShowWindow(SW_HIDE);

    str = "OSD";
    m_oTabConfigure.InsertItem(TAB_INDEX_OSD, str);
    m_oDlgOSD.Create(IDD_CFG_OSD, &m_oTabConfigure);
    m_oDlgOSD.ShowWindow(SW_HIDE);

    str = "I/O";
    m_oTabConfigure.InsertItem(TAB_INDEX_ALARM_IO, str);
    m_oDlgAlarmIO.Create(IDD_CFG_ALARM_IO, &m_oTabConfigure);
    m_oDlgAlarmIO.ShowWindow(SW_HIDE);

    str = "Privacy Mask";
    m_oTabConfigure.InsertItem(TAB_INDEX_PRIVACY_MASK, str);
    m_oDlgPrivacyMask.Create(IDD_CFG_PRIVACY_MASK, &m_oTabConfigure);
    m_oDlgPrivacyMask.ShowWindow(SW_HIDE);

    str ="Motion";
    m_oTabConfigure.InsertItem(TAB_INDEX_MOTION, str);
    m_oDlgMotion.Create(IDD_CHILD_CFG_MOTION, &m_oTabConfigure);
    m_oDlgMotion.ShowWindow(SW_HIDE);

    str ="Temper";
    m_oTabConfigure.InsertItem(TAB_INDEX_TEMPER, str);
    m_oDlgTamper.Create(IDD_CFG_TAMPER, &m_oTabConfigure);
    m_oDlgTamper.ShowWindow(SW_HIDE);

    m_dwCfgType = NETDEMO_CFG_DEVICE;
    UpdateData(FALSE);
    return TRUE;
}

BEGIN_MESSAGE_MAP(CMenuCfg, CDialog)
    ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_PRIMARYMENU, &CMenuCfg::OnTcnSelchangeTabPrimarymenu)
END_MESSAGE_MAP()

void CMenuCfg::refreshCfgTab()
{
    INT32 dwCurDevIndex = ga_pMainDlg ->GetCurDeviceIndex();
    INT32 dwCurChlIndex = ga_pMainDlg->GetCurChlIndex();
    
    switch(m_dwCfgType)
    {
    case NETDEMO_CFG_DEVICE:
        m_oDlgTamper.ShowWindow(SW_HIDE);
        m_oDlgMotion.ShowWindow(SW_HIDE);
        m_oDlgDeviceBasic.ShowWindow(SW_SHOW);
        m_oDlgNetwork.ShowWindow(SW_HIDE);
        m_oDlgVideoStream.ShowWindow(SW_HIDE);
        m_oDlgOSD.ShowWindow(SW_HIDE);
        m_oDlgImage.ShowWindow(SW_HIDE);
        m_oDlgAlarmIO.ShowWindow(SW_HIDE);
        m_oDlgPrivacyMask.ShowWindow(SW_HIDE);
        if( dwCurChlIndex < 0 || dwCurDevIndex<0 || dwCurChlIndex>gastDeviceInfo[dwCurDevIndex].dwMaxChnNum)
        {
            return;
        }
        if(NULL != gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstBasicInfo)
        {
        //    NETDEMO_LOG_ERROR(NULL, "CMenuCfg::refreshCfgTab() dwCurChlIndex < 0 ");
            m_oDlgDeviceBasic.ReadGlobeToBasic();
        }
        else
        {
            m_oDlgDeviceBasic.OnBnClickedRefresh();
        }
        break;
    case NETDEMO_CFG_NETWORK:
        m_oDlgTamper.ShowWindow(SW_HIDE);
        m_oDlgMotion.ShowWindow(SW_HIDE);
        m_oDlgDeviceBasic.ShowWindow(SW_HIDE);
        m_oDlgNetwork.ShowWindow(SW_SHOW);
        m_oDlgVideoStream.ShowWindow(SW_HIDE);
        m_oDlgOSD.ShowWindow(SW_HIDE);
        m_oDlgImage.ShowWindow(SW_HIDE);
        m_oDlgAlarmIO.ShowWindow(SW_HIDE);
        m_oDlgPrivacyMask.ShowWindow(SW_HIDE);
        if(dwCurChlIndex < 0 || dwCurDevIndex<0 || dwCurChlIndex>gastDeviceInfo[dwCurDevIndex].dwMaxChnNum)
        {
            return;
        }

        if(NULL != gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstNetworkInfo)
        {
            m_oDlgNetwork.ReadGlobeToNetwork();
        }
        else
        {
            m_oDlgNetwork.OnBnClickedRefresh();
        }

        break;
    case NETDEMO_CFG_STREAM:
        m_oDlgTamper.ShowWindow(SW_HIDE);
        m_oDlgMotion.ShowWindow(SW_HIDE);
        m_oDlgDeviceBasic.ShowWindow(SW_HIDE);
        m_oDlgNetwork.ShowWindow(SW_HIDE);
        m_oDlgVideoStream.ShowWindow(SW_SHOW);
        m_oDlgOSD.ShowWindow(SW_HIDE);
        m_oDlgImage.ShowWindow(SW_HIDE);
        m_oDlgAlarmIO.ShowWindow(SW_HIDE);
        m_oDlgPrivacyMask.ShowWindow(SW_HIDE);
        if(dwCurChlIndex < 0 || dwCurDevIndex<0 || dwCurChlIndex>gastDeviceInfo[dwCurDevIndex].dwMaxChnNum)
        {
            return;
        }

        if(NULL != gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstVideoStreamInfo)
        {
            m_oDlgVideoStream.ReadGlobeToVideoStream();
        }
        else
        {
            m_oDlgVideoStream.OnBnClickedRefresh();
        }

        break;
    case NETDEMO_CFG_IMAGE:
        m_oDlgTamper.ShowWindow(SW_HIDE);
        m_oDlgMotion.ShowWindow(SW_HIDE);
        m_oDlgDeviceBasic.ShowWindow(SW_HIDE);
        m_oDlgNetwork.ShowWindow(SW_HIDE);
        m_oDlgVideoStream.ShowWindow(SW_HIDE);
        m_oDlgOSD.ShowWindow(SW_HIDE);
        m_oDlgImage.ShowWindow(SW_SHOW);
        m_oDlgAlarmIO.ShowWindow(SW_HIDE);
        m_oDlgPrivacyMask.ShowWindow(SW_HIDE);
        if(dwCurChlIndex < 0 || dwCurDevIndex<0 || dwCurChlIndex>gastDeviceInfo[dwCurDevIndex].dwMaxChnNum)
        {
            return;
        }

        if(NULL != gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstImageInfo)
        {
            m_oDlgImage.ReadGlobeToImage();
        }
        else
        {
            m_oDlgImage.OnBnClickedRefresh();
        }

        break;
    case NETDEMO_CFG_OSD:
        m_oDlgTamper.ShowWindow(SW_HIDE);
        m_oDlgMotion.ShowWindow(SW_HIDE);
        m_oDlgDeviceBasic.ShowWindow(SW_HIDE);
        m_oDlgNetwork.ShowWindow(SW_HIDE);
        m_oDlgVideoStream.ShowWindow(SW_HIDE);
        m_oDlgOSD.ShowWindow(SW_SHOW);
        m_oDlgImage.ShowWindow(SW_HIDE);
        m_oDlgAlarmIO.ShowWindow(SW_HIDE);
        m_oDlgPrivacyMask.ShowWindow(SW_HIDE);
        if(dwCurChlIndex < 0 || dwCurDevIndex<0 || dwCurChlIndex>gastDeviceInfo[dwCurDevIndex].dwMaxChnNum)
        {
            return;
        }

        if(NULL != gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstOSDInfo)
        {
            m_oDlgOSD.ReadGlobeToOSD();
        }
        else
        {
            m_oDlgOSD.OnBnClickedRefresh();
        }

        break;
    case NETDEMO_CFG_ALARM:
        m_oDlgTamper.ShowWindow(SW_HIDE);
        m_oDlgMotion.ShowWindow(SW_HIDE);
        m_oDlgDeviceBasic.ShowWindow(SW_HIDE);
        m_oDlgNetwork.ShowWindow(SW_HIDE);
        m_oDlgVideoStream.ShowWindow(SW_HIDE);
        m_oDlgOSD.ShowWindow(SW_HIDE);
        m_oDlgImage.ShowWindow(SW_HIDE);
        m_oDlgAlarmIO.ShowWindow(SW_SHOW);
        m_oDlgPrivacyMask.ShowWindow(SW_HIDE);
        if(dwCurChlIndex < 0 || dwCurDevIndex<0 || dwCurChlIndex>gastDeviceInfo[dwCurDevIndex].dwMaxChnNum)
        {
            return;
        }

        if(NULL != gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstIOInfo)
        {
             m_oDlgAlarmIO.ReadGlobeToAlarmIO();
        }
        else
        {
            m_oDlgAlarmIO.OnBnClickedRefresh();
        }

        break;
    case NETDEMO_CFG_PRIVACYMASK:
        m_oDlgTamper.ShowWindow(SW_HIDE);
        m_oDlgMotion.ShowWindow(SW_HIDE);
        m_oDlgDeviceBasic.ShowWindow(SW_HIDE);
        m_oDlgNetwork.ShowWindow(SW_HIDE);
        m_oDlgVideoStream.ShowWindow(SW_HIDE);
        m_oDlgOSD.ShowWindow(SW_HIDE);
        m_oDlgImage.ShowWindow(SW_HIDE);
        m_oDlgAlarmIO.ShowWindow(SW_HIDE);
        m_oDlgPrivacyMask.ShowWindow(SW_SHOW);
        if(dwCurChlIndex < 0 || dwCurDevIndex<0 || dwCurChlIndex>gastDeviceInfo[dwCurDevIndex].dwMaxChnNum)
        {
            return;
        }

        if(NULL != gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstPrivacyMaskInfo)
        {
            m_oDlgPrivacyMask.ReadGlobeToPrivacyMask();
        }
        else
        {
            m_oDlgPrivacyMask.OnBnClickedRefresh();
        }

        break;
    case NETDEMO_CFG_MOTION:
        m_oDlgTamper.ShowWindow(SW_HIDE);
        m_oDlgMotion.ShowWindow(SW_SHOW);
        m_oDlgDeviceBasic.ShowWindow(SW_HIDE);
        m_oDlgNetwork.ShowWindow(SW_HIDE);
        m_oDlgVideoStream.ShowWindow(SW_HIDE);
        m_oDlgOSD.ShowWindow(SW_HIDE);
        m_oDlgImage.ShowWindow(SW_HIDE);
        m_oDlgAlarmIO.ShowWindow(SW_HIDE);
        m_oDlgPrivacyMask.ShowWindow(SW_HIDE);
        if(dwCurChlIndex < 0 || dwCurDevIndex<0 || dwCurChlIndex>gastDeviceInfo[dwCurDevIndex].dwMaxChnNum)
        {
            return;
        }

        if(NULL != gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstMotionAlarmInfo)
        {
            m_oDlgMotion.ReadGlobeToMotion();
        }
        else
        {
            m_oDlgMotion.OnBnClickedRefresh();
        }

        break;
    case NETDEMO_CFG_TAMPER:
        m_oDlgTamper.ShowWindow(SW_SHOW);
        m_oDlgMotion.ShowWindow(SW_HIDE);
        m_oDlgDeviceBasic.ShowWindow(SW_HIDE);
        m_oDlgNetwork.ShowWindow(SW_HIDE);
        m_oDlgVideoStream.ShowWindow(SW_HIDE);
        m_oDlgOSD.ShowWindow(SW_HIDE);
        m_oDlgImage.ShowWindow(SW_HIDE);
        m_oDlgAlarmIO.ShowWindow(SW_HIDE);
        m_oDlgPrivacyMask.ShowWindow(SW_HIDE);
        if(dwCurChlIndex < 0 || dwCurDevIndex<0 || dwCurChlIndex>gastDeviceInfo[dwCurDevIndex].dwMaxChnNum)
        {
            return;
        }

        if(NULL != gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstTamperAlarmInfo)
        {
            m_oDlgTamper.ReadGlobeToTamper();
        }
        else
        {
            m_oDlgTamper.OnBnClickedRefresh();
        }

        break;
    default:
        break;
    }
}

void CMenuCfg::OnTcnSelchangeTabPrimarymenu(NMHDR *pNMHDR, LRESULT *pResult)
{
    UpdateData(TRUE);
    m_dwCfgType =  m_oTabConfigure.GetCurSel();
    refreshCfgTab();
    *pResult = 0;
}
