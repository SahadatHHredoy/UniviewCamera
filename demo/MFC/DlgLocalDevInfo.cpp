// DlgLocalDevInfo.cpp : 
//

#include "stdafx.h"
#include "NetDemo.h"
#include "DlgLocalDevInfo.h"

IMPLEMENT_DYNAMIC(CDlgLocalDevInfo, CDialog)

CDlgLocalDevInfo::CDlgLocalDevInfo(CWnd* pParent /*=NULL*/)
    : CDialog(CDlgLocalDevInfo::IDD, pParent)
    , m_dwPort(80)
    , m_strUserName(_T(""))
    , m_strPasswd(_T(""))
    , m_dwChnNum(0)
    , m_strDevType(_T(""))
    , m_dwInputNum(0)
    , m_dwOutputNum(0)
    , m_strIP(_T(""))
{

}

CDlgLocalDevInfo::~CDlgLocalDevInfo()
{
}

void CDlgLocalDevInfo::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_LOCAL_ATTRIBUTE_PORT, m_dwPort);
    DDX_Text(pDX, IDC_LOCAL_ATTRIBUTE_NAME, m_strUserName);
    DDX_Text(pDX, IDC_LOCAL_ATTRIBUTE_PWD, m_strPasswd);
    DDX_Text(pDX, IDC_LOCAL_ATTRIBUTE_ALARM_CHANNELNUM, m_dwChnNum);
    DDX_Text(pDX, IDC_LOCAL_ATTRIBUTE_DEVTYPE, m_strDevType);
    DDX_Text(pDX, IDC_LOCAL_ATTRIBUTE_ALARM_INPUTNUM, m_dwInputNum);
    DDX_Text(pDX, IDC_LOCAL_ATTRIBUTE_ALARM_OUTPUTNUM, m_dwOutputNum);
    DDX_Text(pDX, IDC_IPADD_LOCAL_ATTRIBUTE, m_strIP);
}


BEGIN_MESSAGE_MAP(CDlgLocalDevInfo, CDialog)
    ON_BN_CLICKED(IDC_LOCAL_ATTRIBUTE_SAVE, &CDlgLocalDevInfo::OnBnClickedLocalAttributeSave)
    ON_BN_CLICKED(IDC_LOCAL_ATTRIBUTE_CANCEL, &CDlgLocalDevInfo::OnBnClickedLocalAttributeCancel)
END_MESSAGE_MAP()


void CDlgLocalDevInfo::OnBnClickedLocalAttributeSave()
{
    CDialog::OnOK();
}

void CDlgLocalDevInfo::OnBnClickedLocalAttributeCancel()
{
    EndDialog(-1);
}
