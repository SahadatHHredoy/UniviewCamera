#pragma once


// CVcaPeopleCountingStatistics


#define COL_INDEX_STATISTICAL_TIME        0
#define COL_INDEX_PEOPLE_ENTERED       1
#define COL_INDEX_PEOPLE_LEFT     2

#define NETDEMO_REPORT_TYPE_DAY     0
#define NETDEMO_REPORT_TYPE_WEEK     1
#define NETDEMO_REPORT_TYPE_MONTH     2
#define NETDEMO_REPORT_TYPE_YEAR     3

#define NETDEMO_COUNTING_TYPE_IN     0
#define NETDEMO_COUNTING_TYPE_OUT     1
#define NETDEMO_COUNTING_TYPE_ALL     2

class CVcaPeopleCountingStatistics : public CDialog
{
    DECLARE_DYNAMIC(CVcaPeopleCountingStatistics)

public:
    CVcaPeopleCountingStatistics(CWnd* pParent = NULL);
    virtual ~CVcaPeopleCountingStatistics();

    enum { IDD = IDD_VCA_PEOPLE_COUNTING_STATISTICS };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()

    VOID InitListCtrl();
    VOID InitCBoxReportType();
    VOID InitCBoxCountingType();
    VOID DisplaytheStatistics(NETDEV_TRAFFIC_STATISTICS_DATA_S& stTrafficStatistic);
    VOID GetTimeInfo(INT64& tBeginTime, INT64& tEndTime);
    INT32 DateNumOfMonth(INT32 dwYear ,INT32 dwMonth);

private:
    CComboBox m_cBoxReportType;
    CComboBox m_cBoxCountingType;
    INT32 m_dwReportType;
    INT32 m_dwCountingType;
    CDateTimeCtrl m_dateCtrl;

public:
    CListCtrl m_oPeopleCountingStatisticsList;

    afx_msg void OnCbnSelchangeComboReportType();
    afx_msg void OnCbnSelchangeComboCountingType();
    afx_msg void OnBnClickedButtonCountPeople();
};
