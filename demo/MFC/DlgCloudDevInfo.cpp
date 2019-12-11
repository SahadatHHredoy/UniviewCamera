// DlgCloudDevInfo.cpp :
//

#include "stdafx.h"
#include "NetDemo.h"
#include "DlgCloudDevInfo.h"


// CDlgCloudDevInfo

IMPLEMENT_DYNAMIC(CDlgCloudDevInfo, CDialog)

CDlgCloudDevInfo::CDlgCloudDevInfo(CWnd* pParent /*=NULL*/)
    : CDialog(CDlgCloudDevInfo::IDD, pParent)
    , m_strURL(_T(""))
    , m_strUserName(_T(""))
    , m_strPassword(_T(""))
    , m_strIP(_T(""))
    , m_dwPort(0)
    , m_strDevUserName(_T(""))
    , m_strDevName(_T(""))
    , m_strDevModel(_T(""))
    , m_strDevSerialNum(_T(""))
    , m_dwOrgID()
{

}

CDlgCloudDevInfo::~CDlgCloudDevInfo()
{
}

void CDlgCloudDevInfo::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_CLOUD_ATTRIBUTE_URL, m_strURL);
    DDX_Text(pDX, IDC_CLOUD_ATTRIBUTE_USER, m_strUserName);
    DDX_Text(pDX, IDC_CLOUD_ATTRIBUTE_USER_PWD, m_strPassword);
    DDX_Text(pDX, IDC_CLOUD_ATTRIBUTE_DEV_IP, m_strIP);
    DDX_Text(pDX, IDC_CLOUD_ATTRIBUTE_DEV_PORT, m_dwPort);
    DDX_Text(pDX, IDC_CLOUD_ATTRIBUTE_DEV_USER, m_strDevUserName);
    DDX_Text(pDX, IDC_CLOUD_ATTRIBUTE_DEV_NAME, m_strDevName);
    DDX_Text(pDX, IDC_CLOUD_ATTRIBUTE_DEV_MODEL, m_strDevModel);
    DDX_Text(pDX, IDC_CLOUD_ATTRIBUTE_DEV_SERIAL, m_strDevSerialNum);
    DDX_Text(pDX, IDC_CLOUD_ATTRIBUTE_ORG_ID, m_dwOrgID);
}


BEGIN_MESSAGE_MAP(CDlgCloudDevInfo, CDialog)
    ON_BN_CLICKED(IDC_CLOUD_ATTRIBUTE_SAVE, &CDlgCloudDevInfo::OnBnClickedCloudAttributeSave)
    ON_BN_CLICKED(IDC_CLOUD_ATTRIBUTE_CANCEL, &CDlgCloudDevInfo::OnBnClickedCloudAttributeCancel)
END_MESSAGE_MAP()

void CDlgCloudDevInfo::OnBnClickedCloudAttributeSave()
{
    CDialog::OnOK();
}

void CDlgCloudDevInfo::OnBnClickedCloudAttributeCancel()
{
    EndDialog(-1);
}
