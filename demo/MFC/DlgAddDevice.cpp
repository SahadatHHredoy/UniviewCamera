// CCDLgAddDevice.cpp : 
//

#include "stdafx.h"
#include "NetDemo.h"
#include "DLgAddDevice.h"


// CDLgAddDevice 

IMPLEMENT_DYNAMIC(CDlgAddDevice, CDialog)

CDlgAddDevice::CDlgAddDevice(CWnd* pParent /*=NULL*/)
    : CDialog(CDlgAddDevice::IDD, pParent)
{
    m_dwPort = 80;
}

CDlgAddDevice::~CDlgAddDevice()
{
}

void CDlgAddDevice::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    DDX_Text(pDX, IDC_EDIT_IP_DOMAIN_NAME, m_strIP);
    DDX_Text(pDX, IDC_EDIT_PORT, m_dwPort);
    DDX_Text(pDX, IDC_EDIT_NAME, m_strUserName);
    DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPasswd);
}

BOOL CDlgAddDevice::OnInitDialog()
{
    CDialog::OnInitDialog();

    return TRUE;
}

BEGIN_MESSAGE_MAP(CDlgAddDevice, CDialog)
    ON_BN_CLICKED(IDC_ADD_DEVICE, &CDlgAddDevice::OnBnClickedAddDevice)
    ON_BN_CLICKED(IDC_CANCEL, &CDlgAddDevice::OnBnClickedCancel)
END_MESSAGE_MAP()


void CDlgAddDevice::OnBnClickedAddDevice()
{
    CDialog::OnOK();

    UpdateData();

    NETDEMO_DEVICE_INFO stLocalDeviceInfo;
    memset(&stLocalDeviceInfo, 0, sizeof(stLocalDeviceInfo));

    strncpy(stLocalDeviceInfo.szIPAddr, m_strIP.GetBuffer(0), sizeof(stLocalDeviceInfo.szIPAddr) - 1);
    stLocalDeviceInfo.dwDevPort = m_dwPort;
    strncpy(stLocalDeviceInfo.szDevUserName, m_strUserName.GetBuffer(0), sizeof(stLocalDeviceInfo.szDevUserName) - 1);
    strncpy(stLocalDeviceInfo.szPassword, m_strPasswd.GetBuffer(0), sizeof(stLocalDeviceInfo.szPassword) - 1);

    stLocalDeviceInfo.dwLoginType = NETDEMO_LOGTYPE_LOCAL;
    stLocalDeviceInfo.dwDeviceIndex = -1;
    GetParent()->SendMessage(WM_ADD_DEVICE, WPARAM(NETDEMO_LOGTYPE_LOCAL), (LPARAM)&stLocalDeviceInfo);
}

void CDlgAddDevice::OnBnClickedCancel()
{
    EndDialog(-1);
}

