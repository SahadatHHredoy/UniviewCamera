#pragma once
#include "afxcmn.h"


// CDlgAlarmReport 

class CDlgAlarmReport : public CDialog
{
    DECLARE_DYNAMIC(CDlgAlarmReport)

public:
    CDlgAlarmReport(CWnd* pParent = NULL);
    virtual ~CDlgAlarmReport();

    enum { IDD = IDD_ALARM_REPORT };
protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();

    DECLARE_MESSAGE_MAP()

private:
    void initAlarmReportList();

    void UTCTime2LocalTime(INT32 dwUTCtime, CString& strAlarmTime);

    void getDeviceIP(LPVOID  dwUserID, CString& strDeviceIP);

    void getAlarmInfo(INT32 dwAlarmType, CString& strAlarmInfo);

public:
    void handleRealTimeAlarm(LPVOID  dwUserID, NETDEV_ALARM_INFO_EX_S stAlarmInfo);
    void handleRealTimeAlarm(LPVOID  dwUserID, INT32  dwType);

public:
    CListCtrl m_oAlramReportList;
    afx_msg void OnBnClickedButtonCleanAll();
};
