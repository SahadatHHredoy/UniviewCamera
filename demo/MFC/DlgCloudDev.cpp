#include "stdafx.h"
#include "NetDemo.h"
#include "DlgCloudDev.h"

IMPLEMENT_DYNAMIC(CDlgCloudDev, CDialog)

CDlgCloudDev::CDlgCloudDev(CWnd* pParent /*=NULL*/)
    : CDialog(CDlgCloudDev::IDD, pParent)
    ,m_strUrl("en.ezcloud.uniview.com")
    ,m_strUserName("wb")
    ,m_strPassword("w04306")
{

}

CDlgCloudDev::~CDlgCloudDev()
{
}

void CDlgCloudDev::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_CLOUD_URL, m_strUrl);
    DDX_Text(pDX, IDC_EDIT_CLOUD_USERNAME, m_strUserName);
    DDX_Text(pDX, IDC_EDIT_CLOUD_PASSWD, m_strPassword);
}


BEGIN_MESSAGE_MAP(CDlgCloudDev, CDialog)
    ON_BN_CLICKED(IDC_BUTTON_CLOUD_SAVE, &CDlgCloudDev::OnBnClickedButtonCloudSave)
    ON_BN_CLICKED(IDC_BUTTON_CLOUD_CANCEL, &CDlgCloudDev::OnBnClickedButtonCloudCancel)
END_MESSAGE_MAP()



BOOL CDlgCloudDev::OnInitDialog()
{
    CDialog::OnInitDialog();

    return TRUE;
}

void CDlgCloudDev::OnBnClickedButtonCloudSave()
{
    NETDEMO_DEVICE_INFO stNetDevinfo;
    UpdateData(TRUE);

    CHAR szUrlTmp[NETDEV_LEN_260] = {0};
    for (UINT32 i = 0, j = 0; i < m_strUrl.GetLength(); i++)
    {
        if (' ' != m_strUrl[i])
        {
            szUrlTmp[j] = m_strUrl[i];
            j++;
        }
    }

    if ((0 == strlen(szUrlTmp))
        || (NETDEV_LEN_260 <= strlen(szUrlTmp))
        || (0 == m_strUserName.GetLength())
        || (NETDEV_LEN_64 <= m_strUserName.GetLength())
        || (0 == m_strPassword.GetLength())
        || (NETDEV_LEN_64 <= m_strPassword.GetLength()))
    {
        NETDEMO_LOG_ERROR(NULL, "Cloud Server Para is invalid");
        return;
    }

    LPVOID  lpCloudHandle= NETDEV_LoginCloud(szUrlTmp, m_strUserName.GetBuffer(0), m_strPassword.GetBuffer(0));
    if(NULL == lpCloudHandle)
    {
        NETDEMO_LOG_ERROR(NULL, "Login Cloud Failed, please check your URL, username and password.");
        return;
    }

    stNetDevinfo.lpCloudHandle = lpCloudHandle;
    stNetDevinfo.dwLoginType = NETDEMO_LOGTYPE_CLOUD;
    strncpy(stNetDevinfo.szCloudUrl, szUrlTmp, sizeof(stNetDevinfo.szCloudUrl) - 1);
    strncpy(stNetDevinfo.szCloudName, m_strUserName.GetBuffer(0), sizeof(stNetDevinfo.szCloudName) - 1);
    strncpy(stNetDevinfo.szCloudPasswd, m_strPassword.GetBuffer(0), sizeof(stNetDevinfo.szCloudPasswd) - 1);
    GetParent()->SendMessage(WM_ADD_DEVICE,WPARAM(NETDEMO_LOGTYPE_CLOUD),(LPARAM)&stNetDevinfo);
    CDialog::OnOK();
}

void CDlgCloudDev::OnBnClickedButtonCloudCancel()
{
    EndDialog(-1);
}
