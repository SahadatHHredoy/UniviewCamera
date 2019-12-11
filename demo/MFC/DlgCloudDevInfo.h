#pragma once

// CDlgCloudDevInfo 


class CDlgCloudDevInfo : public CDialog
{
    DECLARE_DYNAMIC(CDlgCloudDevInfo)

public:
    CDlgCloudDevInfo(CWnd* pParent = NULL);   // 
    virtual ~CDlgCloudDevInfo();

    enum { IDD = IDD_DLG_CLOUD_DEVICE_INFO };

protected:
    virtual void DoDataExchange(CDataExchange* pDX); 

    DECLARE_MESSAGE_MAP()

public:
    CString m_strURL;
    CString m_strUserName;
    CString m_strPassword;
    CString m_strIP;
    INT32 m_dwPort;
    CString m_strDevUserName;
    CString m_strDevName;
    CString m_strDevModel;
    CString m_strDevSerialNum;
    INT32 m_dwOrgID;

public:
    afx_msg void OnBnClickedCloudAttributeSave();
    afx_msg void OnBnClickedCloudAttributeCancel();
};
