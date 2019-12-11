#pragma once

#include "DlgPTZExtend.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "DlgPTZPreset.h"

class CPannelPTZ : public CDialog
{
    DECLARE_DYNAMIC(CPannelPTZ)

public:
    CPannelPTZ(CWnd* pParent = NULL);   
    virtual ~CPannelPTZ();

    enum { IDD = IDD_PANNEL_PTZ };

protected:
    virtual void DoDataExchange(CDataExchange* pDX); 
    virtual BOOL OnInitDialog();
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    DECLARE_MESSAGE_MAP()
public:
    CDlgPTZExtend m_oDlgPTZExtend;
    afx_msg void OnBnClickedButtonPtzExtend();

    void initButtonIco();
    CComboBox m_BoxPreset;
private:
    HICON m_hLeftIcon;
    HICON m_hRightIcon;
    HICON m_hUpIcon;
    HICON m_hDownIcon;
    HICON m_hLeftUpIcon;
    HICON m_hRightUpIcon;
    HICON m_hLeftDownIcon;
    HICON m_hRighDowntIcon;
    HICON m_hStopIcon;
private:
    INT32 m_dwPtzSpeed;
    CToolTipCtrl     m_cToolTip;

private:
    void InitToolTipCtrl();
public:
    afx_msg void OnNMCustomdrawSliderSpeed(NMHDR *pNMHDR, LRESULT *pResult);
    CSliderCtrl m_oSldPtzSpeed;
    afx_msg void OnBnPTZUp();
    afx_msg void OnBnPTZDown();
    afx_msg void OnBnPTZLeft();
    afx_msg void OnBnPTZRight();
    afx_msg void OnBnPTZLeftup();
    afx_msg void OnBnPTZLeftdown();
    afx_msg void OnBnPTZRightup();
    afx_msg void OnBnPTZRightdown();
    afx_msg void OnBnPTZStop();
    afx_msg void OnBnPTZZoomIn();
    afx_msg void OnBnPTZZoomOut();
    afx_msg void OnBnPTZFocusNear();
    afx_msg void OnBnPTZFocusFar();
    afx_msg void OnBnPTZStopFocus();
    afx_msg void OnBnPTZStopZoomIn();
    afx_msg void OnBnPTZStopZoomOut();

    afx_msg void OnBnClickedBtnGetPreset();
    afx_msg void OnBnClickedBtnSetPreset();
    afx_msg void OnBnClickedBtnGotoPreset();
    afx_msg void OnBnClickedBtnDelPreset();
    afx_msg void OnCbnSelchangeComboPreset();
};
