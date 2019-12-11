#pragma once


// CCfgTamper 

class CCfgTamper : public CDialog
{
    DECLARE_DYNAMIC(CCfgTamper)

public:
    CCfgTamper(CWnd* pParent = NULL);
    virtual ~CCfgTamper();

    enum { IDD = IDD_CFG_TAMPER };
    void ReadGlobeToTamper();

protected:
    virtual void DoDataExchange(CDataExchange* pDX); 
    virtual BOOL OnInitDialog();

    void getTemperCfg();

    DECLARE_MESSAGE_MAP()

private:
    CSliderCtrl m_oSldSensitivity;
    INT32 m_dwSensitivity;

public:
    afx_msg void OnBnClickedSaveTemperCfg();
    afx_msg void OnBnClickedRefresh();
    afx_msg void OnEnChangeEditSensitivity();
    afx_msg void OnEnKillfocusEditSensitivity();
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
