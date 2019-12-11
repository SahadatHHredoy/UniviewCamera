#pragma once

class CMenuMaintain : public CDialog
{
    DECLARE_DYNAMIC(CMenuMaintain)

public:
    CMenuMaintain(CWnd* pParent = NULL);
    virtual ~CMenuMaintain();

    enum { IDD = IDD_MENU_MAINTAIN };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedReboot();
    afx_msg void OnBnClickedFactoryDefault();
    afx_msg void OnBnClickedButtonStartRecord();
    afx_msg void OnBnClickedButtonStopRecord();
};
