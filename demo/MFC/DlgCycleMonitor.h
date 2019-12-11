#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CDlgCycleMonitor 

class CDlgCycleMonitor : public CDialog
{
    DECLARE_DYNAMIC(CDlgCycleMonitor)

public:
    CDlgCycleMonitor(CWnd* pParent = NULL);
    virtual ~CDlgCycleMonitor();

    enum { IDD = IDD_DLG_CYCLE_MONITOR };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()

public:
    void InitAllChannelList();
    void SaveCycInfo();
    void EnabledWindow(bool bEnable);

public:
    INT32 m_dwIntervalTime;

    CListCtrl m_oCycleAllChlList;
    CListCtrl m_oCycleScreenList;
    CComboBox m_oCBoxCycleType;
    CComboBox m_oCBoxCycleWinID;

public:
    afx_msg void OnBnClickedBtnCycleAddall();
    afx_msg void OnBnClickedBtnDelall();
    afx_msg void OnBnClickedBtnCycleAdd();
    afx_msg void OnBnClickedBtnCycleDel();
    afx_msg void OnCbnSelchangeComboCycleType();
    afx_msg void OnCbnSelchangeComboWinIndex();
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedBtnCycleStopPlay();
    afx_msg void OnBnClickedBtnCycleStopCancel();
    afx_msg void OnEnKillfocusEditCycleIntervaltime();
};
