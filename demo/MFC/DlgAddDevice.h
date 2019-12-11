#pragma once

class CDlgAddDevice : public CDialog
{
    DECLARE_DYNAMIC(CDlgAddDevice)

public:
    CDlgAddDevice(CWnd* pParent = NULL);
    virtual ~CDlgAddDevice();

    enum { IDD = IDD_DLG_ADD_DEVICE };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()

private:
    CString m_strIP;
    INT32 m_dwPort;
    CString m_strUserName;
    CString m_strPasswd;

public:
    afx_msg void OnBnClickedAddDevice();
    afx_msg void OnBnClickedCancel();
};
