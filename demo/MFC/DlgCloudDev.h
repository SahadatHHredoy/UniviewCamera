#pragma once


// CDlgCloudDev 

class CDlgCloudDev : public CDialog
{
    DECLARE_DYNAMIC(CDlgCloudDev)

public:
    CDlgCloudDev(CWnd* pParent = NULL);
    virtual ~CDlgCloudDev();

    enum { IDD = IDD_DLG_CLOUD_DEV };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()

private:
    CString m_strUrl;
    CString m_strUserName;
    CString m_strPassword;

public:
    afx_msg void OnBnClickedButtonCloudSave();
    afx_msg void OnBnClickedButtonCloudCancel();
};
