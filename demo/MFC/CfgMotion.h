#pragma once


// CCfgMotion

class CCfgMotion : public CDialog
{
    DECLARE_DYNAMIC(CCfgMotion)

public:
    CCfgMotion(CWnd* pParent = NULL);
    virtual ~CCfgMotion();

    enum { IDD = IDD_CFG_MOTION };
    void ReadGlobeToMotion();

protected:
    virtual void DoDataExchange(CDataExchange* pDX); 
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()

    void getMotionCfg();

private:

    INT32 m_dwObjSize;
    INT32 m_dwHistory;
    INT32 m_dwSensitivity;

    CSliderCtrl m_oSldSensitivity;
    CSliderCtrl m_oSldObjSize;
    CSliderCtrl m_oSldHistory;

public:
    afx_msg void OnBnClickedSaveMotionCfg();
    afx_msg void OnBnClickedRefresh();
    afx_msg void OnEnChangeEditSensitivity();
    afx_msg void OnEnKillfocusEditSensitivity();
    afx_msg void OnEnChangeEditObjSize();
    afx_msg void OnEnKillfocusEditObjSize();
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnEnChangeEditHistory();
    afx_msg void OnEnKillfocusEditHistory();
};
