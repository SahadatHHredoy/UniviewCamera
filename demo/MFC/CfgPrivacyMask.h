#pragma once


// CCfgPrivacyMask 

class CCfgPrivacyMask : public CDialog
{
    DECLARE_DYNAMIC(CCfgPrivacyMask)

public:
    CCfgPrivacyMask(CWnd* pParent = NULL);
    virtual ~CCfgPrivacyMask();

    enum { IDD = IDD_CFG_PRIVACY_MASK };
    void ReadGlobeToPrivacyMask();

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()

    void getPrivacyMaskCfg();

    void initPrivacyMaskList();

    void SetListItemText();

    void getListDate(OUT LPNETDEV_PRIVACY_MASK_CFG_S pstPrivacyMaskInfo);

private:

    CListCtrl m_oPrivacyMaskList;
    CEdit m_oEditSubItem;
    CString m_strItemValue;
    INT32 m_dwRow;
    INT32 m_dwCol;
    
public:
    afx_msg void OnBnClickedRefresh();
    afx_msg void OnBnClickedSavePrivacyMask();
    afx_msg void OnBnClickedDeletePrivacyMask();
    afx_msg void OnNMDblclkListPrivacyMask(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnEnKillfocusEditSubItem();
    afx_msg void OnBnClickedAddPrivacyMask();
};
