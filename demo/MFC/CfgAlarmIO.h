#pragma once
#include "afxcmn.h"


// CCfgAlarm 

class CCfgAlarmIO : public CDialog
{
    DECLARE_DYNAMIC(CCfgAlarmIO)

public:
    CCfgAlarmIO(CWnd* pParent = NULL); 
    virtual ~CCfgAlarmIO();

    enum { IDD = IDD_CFG_ALARM_IO };
    void ReadGlobeToAlarmIO();

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()

    void initAlarmInputList();

    void getAlarmInputInfo();

    void getAlarmOutputInfo();

    void showByIndex(INT32 dwIndex);

private:
    CListCtrl m_oAlarmInputList;
    NETDEV_ALARM_OUTPUT_LIST_S m_stAlarmOutputList;

    CComboBox m_oCBoxAlarmOutputIndex;
    CComboBox m_oCBoxAlarmOutputStatus;

    CString m_strAlarmOutputName;
    INT32 m_dwAlarmOutputChnID;
    INT32 m_dwAlarmOutputDuration;

public:
    afx_msg void OnBnClickedRefresh();
    afx_msg void OnBnClickedSaveAlarmOutCfg();
    afx_msg void OnCbnSelchangeComboAlarmOutputIndex();
    afx_msg void OnEnKillfocusEditAlarmOutputName();
    afx_msg void OnCbnSelchangeComboAlarmOutputStatus();
    afx_msg void OnEnChangeEditAlarmOutputChnId();
    afx_msg void OnEnChangeEditAlarmOutputDuration();
    afx_msg void OnBnClickedTriggerAlarmOut();
};
