#pragma once


// CCfgImage 

class CCfgImage sealed : public CDialog
{
    DECLARE_DYNAMIC(CCfgImage)

public:
    CCfgImage(CWnd* pParent = NULL);
    virtual ~CCfgImage();

    enum { IDD = IDD_CFG_IMAGE};
    void ReadGlobeToImage();

protected:
    virtual void DoDataExchange(CDataExchange* pDX); 
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()

    void getImageCfg();

private:
    INT32 m_dwBrightness;
    INT32 m_dwSharpness;
    INT32 m_dwContrast;
    INT32 m_dwSaturation;
    
    CSliderCtrl m_oSldBrightness;
    CSliderCtrl m_oSldSharpness;
    CSliderCtrl m_oSldContrast;
    CSliderCtrl m_oSldSaturation;

public:
    afx_msg void OnBnClickedSaveImageInfo();
    afx_msg void OnBnClickedRefresh();
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnEnChangeEditBrightness();
    afx_msg void OnEnKillfocusEditBrightness();
    afx_msg void OnEnChangeEditSaturation();
    afx_msg void OnEnKillfocusEditSaturation();
    afx_msg void OnEnChangeEditContrast();
    afx_msg void OnEnKillfocusEditContrast();
    afx_msg void OnEnKillfocusEditSharpness();
    afx_msg void OnEnChangeEditSharpness();
};
