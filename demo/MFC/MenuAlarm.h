#pragma once
#include "afxcmn.h"
#include "GeneralDef.h"
#include "DlgAlarmReport.h"


// CMenuAlarm 
class CMenuAlarm : public CDialog
{
    DECLARE_DYNAMIC(CMenuAlarm)

public:
    CMenuAlarm(CWnd* pParent = NULL);
    virtual ~CMenuAlarm();

    enum { IDD = IDD_MENU_ALARM };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnTcnSelchangeTabWarning(NMHDR *pNMHDR, LRESULT *pResult);


public:
    void ConfigureWithUpdate();

    void ShowMainMenu();

    void handleRealWarning(LPVOID  dwUserID, NETDEV_ALARM_INFO_EX_S stAlarmInfo);

    void handleRealWarning(LPVOID  dwUserID, INT32  dwType);
private:
    INT32 m_dwCfgType;
    CDlgAlarmReport m_oDlgRealTimeAlarm;
    CTabCtrl m_oTabAlarm;

};
