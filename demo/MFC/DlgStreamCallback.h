#pragma once


// CDlgStreamCallback

class CDlgStreamCallback : public CDialog
{
    DECLARE_DYNAMIC(CDlgStreamCallback)

public:
    CDlgStreamCallback(CWnd* pParent = NULL);   
    virtual ~CDlgStreamCallback();

    enum { IDD = IDD_DLG_STREAM_CALLBACK };

public:
    void CloseAllCallback();

protected:
    virtual void DoDataExchange(CDataExchange* pDX);   

    DECLARE_MESSAGE_MAP()

private:
    BOOL m_bStreamClosed;
    BOOL m_bDecodeClosed;
    BOOL m_bDisplayClosed;
    BOOL m_bParseClosed;

public:
    afx_msg void OnBnClickedButtonRealtimeReg();
    afx_msg void OnBnClickedButtonRealtimeClose();
    afx_msg void OnBnClickedButtonDecodeReg();
    afx_msg void OnBnClickedButtonDecodeClose();
    afx_msg void OnBnClickedButtonDisplayReg();
    afx_msg void OnBnClickedButtonDisplayClose();
    afx_msg void OnBnClickedButtonFrameReg();
    afx_msg void OnBnClickedButtonFrameClose();
};
