#pragma once


// CDlgLocalDevInfo 

class CDlgLocalDevInfo : public CDialog
{
    DECLARE_DYNAMIC(CDlgLocalDevInfo)

public:
    CDlgLocalDevInfo(CWnd* pParent = NULL);  
    virtual ~CDlgLocalDevInfo();

    enum { IDD = IDD_DLG_LOCAL_DEVICE_INFO };

protected:
    virtual void DoDataExchange(CDataExchange* pDX); 
    DECLARE_MESSAGE_MAP()

public:
    CString m_strIP;
    INT32 m_dwPort;
    CString m_strUserName;
    CString m_strPasswd;

    INT32 m_dwChnNum;
    CString m_strDevType;
    INT32 m_dwInputNum;
    INT32 m_dwOutputNum;

    afx_msg void OnBnClickedLocalAttributeSave();
    afx_msg void OnBnClickedLocalAttributeCancel();
};
