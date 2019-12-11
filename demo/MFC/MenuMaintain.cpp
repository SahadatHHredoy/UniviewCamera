// DlgMenuMaintainainance.cpp : 
//

#include "stdafx.h"
#include "NetDemo.h"
#include "MenuMaintain.h"


// CMenuMaintain 

IMPLEMENT_DYNAMIC(CMenuMaintain, CDialog)

CMenuMaintain::CMenuMaintain(CWnd* pParent /*=NULL*/)
    : CDialog(CMenuMaintain::IDD, pParent)
{

}

CMenuMaintain::~CMenuMaintain()
{
}

void CMenuMaintain::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMenuMaintain, CDialog)
    ON_BN_CLICKED(IDC_BUTTON_REBOOT, &CMenuMaintain::OnBnClickedReboot)
    ON_BN_CLICKED(IDC_BUTTON_FACTORY_DEFAULT, &CMenuMaintain::OnBnClickedFactoryDefault)
    ON_BN_CLICKED(IDC_BUTTON_START_RECORD, &CMenuMaintain::OnBnClickedButtonStartRecord)
    ON_BN_CLICKED(IDC_BUTTON_STOP_RECORD, &CMenuMaintain::OnBnClickedButtonStopRecord)
END_MESSAGE_MAP()



void CMenuMaintain::OnBnClickedReboot()
{
    INT32 dwChannelID = ga_pMainDlg->GetChlID();
    if (0 == dwChannelID)
    {
        if (IDOK != MessageBox("Do you want to restart the device?", "Info",IDOK))
        {
            return;
        }

        LPVOID lpDevHandle = ga_pMainDlg->GetDevHandle();

        BOOL bRet = NETDEV_Reboot(lpDevHandle);
        if(TRUE != bRet)
        {
            NETDEMO_LOG_ERROR(NULL, "Reboot");
        }
        else
        {
            NETDEMO_LOG_SUCC(NULL, "Reboot");
            ga_pMainDlg->OnDeviceoperLogout();
        }
    }
    else
    {
        NETDEMO_LOG_ERROR(NULL, "Cannot reboot channel");
    }

    return;
}

void CMenuMaintain::OnBnClickedFactoryDefault()
{
    INT32 dwChannelID = ga_pMainDlg->GetChlID();
    if (0 == dwChannelID)
    {
        if (IDOK != MessageBox("Restoring the default will restart the device. Do you want to continue?", "Info", IDOK))
        {
            return;
        }

        LPVOID lpDevHandle = ga_pMainDlg->GetDevHandle();
        BOOL bRet = NETDEV_RestoreConfig(lpDevHandle);
        if(TRUE != bRet)
        {
            NETDEMO_LOG_ERROR(NULL, "Restore Config");
        }
        else
        {
            NETDEMO_LOG_SUCC(NULL, "Restore Config");
            ga_pMainDlg->OnDeviceoperLogout();
        }
    }
    else
    {
        NETDEMO_LOG_ERROR(NULL, "Cannot restore channel config");
    }

    return;
}

void CMenuMaintain::OnBnClickedButtonStartRecord()
{
    LPVOID lpDevHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwCurDevIndex = ga_pMainDlg->GetCurDeviceIndex();
    INT32 dwCurChnID = ga_pMainDlg->GetCurChlIndex();

    NETDEV_MANUAL_RECORD_CFG_S stManualRecordCfg = {0};
    stManualRecordCfg.dwChannelID = ga_pMainDlg->GetChlID();
    stManualRecordCfg.enRecordType = NETDEV_RECORD_TYPE_MANUAL;
    BOOL bRet = NETDEV_StartManualRecord(lpDevHandle, &stManualRecordCfg);
    if (TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Start Manual Record");
        return;
    }
    NETDEMO_LOG_SUCC(NULL, "Start Manual Record");

    return;
}

void CMenuMaintain::OnBnClickedButtonStopRecord()
{
    LPVOID lpDevHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwCurDevIndex = ga_pMainDlg->GetCurDeviceIndex();
    INT32 dwCurChnID = ga_pMainDlg->GetCurChlIndex();

    NETDEV_MANUAL_RECORD_CFG_S stManualRecordCfg = {0};
    stManualRecordCfg.dwChannelID = ga_pMainDlg->GetChlID();
    stManualRecordCfg.enRecordType = NETDEV_RECORD_TYPE_MANUAL;
    BOOL bRet = NETDEV_StopManualRecord(lpDevHandle, &stManualRecordCfg);
    if (TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Stop Manual Record");
        return;
    }
    NETDEMO_LOG_SUCC(NULL, "Stop Manual Record");

    return;
}