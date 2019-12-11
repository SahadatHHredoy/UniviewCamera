#pragma once


// CDlgLocalSetting 

class CDlgLocalSetting : public CDialog
{
    DECLARE_DYNAMIC(CDlgLocalSetting)

public:
    CDlgLocalSetting(CWnd* pParent = NULL);
    virtual ~CDlgLocalSetting();

    enum { IDD = IDD_DLG_LOCAL_SETTING };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);

    DECLARE_MESSAGE_MAP()

public:
    CString m_strLogPath;
    CString m_strSnapshotPath;
    CString m_strLocalRecordPath;
    INT32 m_dwWaitTime;
    INT32 m_dwTryTimes;
    INT32 m_dwReceiveTimeout;
    INT32 m_dwFileTimeout;
    BOOL m_bChkAutoSaveLog;
    BOOL m_bChkSuccLog;
    BOOL m_bChkFailLog;
    FILE *m_pfLog;

    BOOL m_bRatioMain;
    BOOL m_bRatioSub;
    BOOL m_bRatioThird;

    void CreateNewLogFile(BOOL bCreate);
    afx_msg void OnBnClickedButtonSetLogpath();
    afx_msg void OnBnClickedButtonSetOperationLog();
    afx_msg void OnBnClickedButtonSetKeeplive();
    afx_msg void OnBnClickedButtonSetTimeout();
    afx_msg void OnBnClickedBtnSaveStreamType();
};
