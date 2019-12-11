#pragma once


// CCfgOSD 

class CCfgOSD : public CDialog
{
    DECLARE_DYNAMIC(CCfgOSD)

public:
    CCfgOSD(CWnd* pParent = NULL);
    virtual ~CCfgOSD();

    enum { IDD = IDD_CFG_OSD };
    void ReadGlobeToOSD();

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()

    void getOSD();

private:
    BOOL m_bEnableOSDTime;
    BOOL m_bEnableOSDName;
    BOOL m_bEnableText1;
    BOOL m_bEnableText2;
    BOOL m_bEnableText3;
    BOOL m_bEnableText4;
    BOOL m_bEnableText5;
    BOOL m_bEnableText6;

    INT32 m_dwOSDTimePosX;
    INT32 m_dwOSDTimePosY;
    INT32 m_dwOSDNamePosX;
    INT32 m_dwOSDNamePosY;

    CComboBox m_oCBoxDateFormat;
    CComboBox m_oCBoxTimeFormat;

    CString m_strOSDName;
    CString m_strOSDText_1;
    CString m_strOSDText_2;
    CString m_strOSDText_3;
    CString m_strOSDText_4;
    CString m_strOSDText_5;
    CString m_strOSDText_6;

    INT32 m_dwOSDText_1_PosX;
    INT32 m_dwOSDText_1_PosY;
    INT32 m_dwOSDText_2_PosX;
    INT32 m_dwOSDText_2_PosY;
    INT32 m_dwOSDText_3_PosX;
    INT32 m_dwOSDText_3_PosY;
    INT32 m_dwOSDText_4_PosX;
    INT32 m_dwOSDText_4_PosY;
    INT32 m_dwOSDText_5_PosX;
    INT32 m_dwOSDText_5_PosY;
    INT32 m_dwOSDText_6_PosX;
    INT32 m_dwOSDText_6_PosY;

public:
    afx_msg void OnBnClickedSaveOsd();
    afx_msg void OnBnClickedRefresh();
};
