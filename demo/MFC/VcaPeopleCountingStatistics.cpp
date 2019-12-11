// VcaPeopleCountingStatistics.cpp 
//

#include "stdafx.h"
#include "NetDemo.h"
#include "VcaPeopleCountingStatistics.h"


// CVcaPeopleCountingStatistics 

IMPLEMENT_DYNAMIC(CVcaPeopleCountingStatistics, CDialog)

CVcaPeopleCountingStatistics::CVcaPeopleCountingStatistics(CWnd* pParent /*=NULL*/)
    : CDialog(CVcaPeopleCountingStatistics::IDD, pParent)
{

}

CVcaPeopleCountingStatistics::~CVcaPeopleCountingStatistics()
{
}

BOOL CVcaPeopleCountingStatistics::OnInitDialog()
{

    CDialog::OnInitDialog();
    CRect rc(0, 0, 0, 0);
    GetParent()->GetClientRect(&rc);
    ((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
    MoveWindow(&rc);

    InitListCtrl();
    InitCBoxReportType();
    InitCBoxCountingType();

    return TRUE;
}

void CVcaPeopleCountingStatistics::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_PASSENGER_FLOW_TABLE, m_oPeopleCountingStatisticsList);
    DDX_Control(pDX, IDC_COMBO_REPORT_TYPE, m_cBoxReportType);
    DDX_Control(pDX, IDC_COMBO_COUNTING_TYPE, m_cBoxCountingType);
    DDX_Control(pDX, IDC_DATETIMEPICKER_STATISTICAL_TIME, m_dateCtrl);
}


BEGIN_MESSAGE_MAP(CVcaPeopleCountingStatistics, CDialog)
    ON_CBN_SELCHANGE(IDC_COMBO_REPORT_TYPE, &CVcaPeopleCountingStatistics::OnCbnSelchangeComboReportType)
    ON_CBN_SELCHANGE(IDC_COMBO_COUNTING_TYPE, &CVcaPeopleCountingStatistics::OnCbnSelchangeComboCountingType)
    ON_BN_CLICKED(IDC_BUTTON_COUNT_PEOPLE, &CVcaPeopleCountingStatistics::OnBnClickedButtonCountPeople)
END_MESSAGE_MAP()

void CVcaPeopleCountingStatistics::InitListCtrl()
{
    CString str="Statistical Time";
    m_oPeopleCountingStatisticsList.InsertColumn(COL_INDEX_STATISTICAL_TIME,str,LVCFMT_CENTER,200);

    str = "People Entered";
    m_oPeopleCountingStatisticsList.InsertColumn(COL_INDEX_PEOPLE_ENTERED, str, LVCFMT_CENTER, 200);

    str = "People Left";
    m_oPeopleCountingStatisticsList.InsertColumn(COL_INDEX_PEOPLE_LEFT, str, LVCFMT_CENTER, 200);

    m_oPeopleCountingStatisticsList.SetExtendedStyle(m_oPeopleCountingStatisticsList.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES);

    return;
}

void CVcaPeopleCountingStatistics::InitCBoxReportType()
{
    m_cBoxReportType.InsertString(NETDEMO_REPORT_TYPE_DAY, "Daily");
    m_cBoxReportType.InsertString(NETDEMO_REPORT_TYPE_WEEK, "Weekly");
    m_cBoxReportType.InsertString(NETDEMO_REPORT_TYPE_MONTH, "Monthly");
    m_cBoxReportType.InsertString(NETDEMO_REPORT_TYPE_YEAR, "Yearly");
    m_cBoxReportType.SetCurSel(NETDEMO_REPORT_TYPE_DAY);

    return;
}

void CVcaPeopleCountingStatistics::InitCBoxCountingType()
{
    m_cBoxCountingType.InsertString(NETDEMO_COUNTING_TYPE_IN, "People Entered");
    m_cBoxCountingType.InsertString(NETDEMO_COUNTING_TYPE_OUT, "People Left");
    m_cBoxCountingType.InsertString(NETDEMO_COUNTING_TYPE_ALL, "Total");
    m_cBoxCountingType.SetCurSel(NETDEMO_COUNTING_TYPE_IN);

    return;
}

INT32 CVcaPeopleCountingStatistics::DateNumOfMonth(INT32 dwYear , INT32 dwMonth)
{
    INT32 aDays[]={31,28,31,30,31,30,31,31,30,31,30,31};
    if(((dwYear % 4 == 0)&& (dwYear % 100 != 0))||dwYear % 400 == 0)
    {
        aDays[1]=29;
    }

    return aDays[dwMonth];
}

VOID CVcaPeopleCountingStatistics::GetTimeInfo(INT64& tBeginTime, INT64& tEndTime)
{
    struct tm stm;
    memset(&stm,0,sizeof(stm));

    CTime m_date;
    m_dateCtrl.GetTime(m_date);
    INT32 dwYear = m_date.GetYear();
    INT32 dwMonth = m_date.GetMonth();
    INT32 dwDay = m_date.GetDay();
    INT32 dwDayOfWeek = 0;
    if (1 == m_date.GetDayOfWeek())
    {
        dwDayOfWeek = 7;
    } 
    else
    {
        dwDayOfWeek = m_date.GetDayOfWeek() - 1;
    }

    switch(m_dwReportType)
    {
    case NETDEV_FORM_TYPE_DAY:
        {
            stm.tm_year=dwYear - 1900;
            stm.tm_mon=dwMonth - 1;
            stm.tm_mday=dwDay;
            tBeginTime = mktime(&stm);
            tEndTime = tBeginTime + (3600 * 24 -1);
        }
        break;
    case NETDEV_FORM_TYPE_WEEK:
        {
            if (dwDay- dwDayOfWeek >= 0)
            {
                stm.tm_year = dwYear - 1900;
                stm.tm_mon = dwMonth - 1;
                stm.tm_mday = dwDay- dwDayOfWeek +1 ;
                tBeginTime = mktime(&stm);
                tEndTime = tBeginTime + (3600 * 24 * 7 -1);
            }
            else
            {
                stm.tm_year=dwYear - 1900;
                stm.tm_mon=dwMonth - 2;
                stm.tm_mday=dwDay- dwDayOfWeek + 1 + DateNumOfMonth(dwYear, dwMonth);
                tBeginTime = mktime(&stm);
                tEndTime = tBeginTime + (3600 * 24 * 7 -1);
            } 
        }
        break;
    case NETDEV_FORM_TYPE_MONTH:
        {
            stm.tm_year=dwYear - 1900;
            stm.tm_mon=dwMonth - 1;
            tBeginTime = mktime(&stm) + (3600 * 24);
            stm.tm_mon=dwMonth;
            tEndTime = mktime(&stm) - 1;
        }
        break;
    case NETDEV_FORM_TYPE_YEAR:
        {
            stm.tm_year=dwYear - 1900;
            tBeginTime = mktime(&stm);
            stm.tm_year=dwYear - 1900 + 1;
            tEndTime = mktime(&stm) - 1;
        }
        break;
    default:
        break;
    }
}

VOID CVcaPeopleCountingStatistics::DisplaytheStatistics(NETDEV_TRAFFIC_STATISTICS_DATA_S& stTrafficStatistic)
{
    CHAR szTime[NETDEV_LEN_32] = {0};
    CHAR szEnterCount[NETDEV_LEN_32] = {0};
    CHAR szExitCount[NETDEV_LEN_32] = {0};
    CHAR* szWeekly[] = {"Mon", "Tue", "Wed", "Thu" ,"Fri" ,"Sat", "Sun"};
    CHAR* szYearly[] = {"Jan", "Feb", "Mar", "Apr" ,"May" ,"Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    m_oPeopleCountingStatisticsList.DeleteAllItems();

    for(INT32 i = 0; i < stTrafficStatistic.dwSize; i++)
    {
        if ((0 != stTrafficStatistic.adwEnterCount[i]) || (0 != stTrafficStatistic.adwExitCount[i]))
        {
            INT32 dwCount = m_oPeopleCountingStatisticsList.GetItemCount();
            INT32 dwRow = m_oPeopleCountingStatisticsList.InsertItem(dwCount, "");
            switch(m_dwReportType)
            {
            case NETDEV_FORM_TYPE_DAY:
                {
                    _snprintf(szTime, sizeof(szTime), "%02d:00 - %02d:00" , i, i+1);
                    m_oPeopleCountingStatisticsList.SetItemText(dwRow, COL_INDEX_STATISTICAL_TIME, szTime);
                }
                break;
            case NETDEV_FORM_TYPE_WEEK:
                {
                    _snprintf(szTime, sizeof(szTime), "%s" , szWeekly[i]);
                    m_oPeopleCountingStatisticsList.SetItemText(dwRow, COL_INDEX_STATISTICAL_TIME, szTime);
                }
                break;
            case NETDEV_FORM_TYPE_MONTH:
                {
                    _snprintf(szTime, sizeof(szTime), "%d" , i+1);
                    m_oPeopleCountingStatisticsList.SetItemText(dwRow, COL_INDEX_STATISTICAL_TIME, szTime);
                }
                break;
            case NETDEV_FORM_TYPE_YEAR:
                {
                    _snprintf(szTime, sizeof(szTime), "%s" , szYearly[i]);
                    m_oPeopleCountingStatisticsList.SetItemText(dwRow, COL_INDEX_STATISTICAL_TIME, szTime);
                }
                break;
            default:
                break;
            }

            _snprintf(szEnterCount, sizeof(szEnterCount), "%d", stTrafficStatistic.adwEnterCount[i]);
            m_oPeopleCountingStatisticsList.SetItemText(dwRow, COL_INDEX_PEOPLE_ENTERED, szEnterCount);
            _snprintf(szExitCount, sizeof(szExitCount), "%d", stTrafficStatistic.adwExitCount[i]);
            m_oPeopleCountingStatisticsList.SetItemText(dwRow, COL_INDEX_PEOPLE_LEFT, szExitCount);
            m_oPeopleCountingStatisticsList.Invalidate();
            m_oPeopleCountingStatisticsList.UpdateWindow();
        }
    }

    return;
}

void CVcaPeopleCountingStatistics::OnCbnSelchangeComboReportType()
{
    INT32 index = m_cBoxReportType.GetCurSel();
    switch(index)
    {
    case NETDEMO_REPORT_TYPE_DAY:
        {
            m_dwReportType = NETDEV_FORM_TYPE_DAY;
        }
        break;
    case NETDEMO_REPORT_TYPE_WEEK:
        {
            m_dwReportType = NETDEV_FORM_TYPE_WEEK;
        }
        break;
    case NETDEMO_REPORT_TYPE_MONTH:
        {
            m_dwReportType = NETDEV_FORM_TYPE_MONTH;
        }
        break;
    case NETDEMO_REPORT_TYPE_YEAR:
        {
            m_dwReportType = NETDEV_FORM_TYPE_YEAR;
        }
        break;
    default:
        break;
    }

    return;
}

void CVcaPeopleCountingStatistics::OnCbnSelchangeComboCountingType()
{
    INT32 index = m_cBoxCountingType.GetCurSel();
    switch(index)
    {
    case NETDEMO_COUNTING_TYPE_IN:
        {
            m_dwCountingType = NETDEV_TRAFFIC_STATISTICS_TYPE_IN;
        }
        break;
    case NETDEMO_COUNTING_TYPE_OUT:
        {
            m_dwCountingType = NETDEV_TRAFFIC_STATISTICS_TYPE_OUT;
        }
        break;
    case NETDEMO_COUNTING_TYPE_ALL:
        {
            m_dwCountingType = NETDEV_TRAFFIC_STATISTICS_TYPE_ALL;
        }
        break;
    default:
        break;
    }

    return;
}

void CVcaPeopleCountingStatistics::OnBnClickedButtonCountPeople()
{

    LPVOID lpDevHandle = ga_pMainDlg->GetDevHandle();
    NETDEV_TRAFFIC_STATISTICS_COND_S stStatisticCond = {0};
    NETDEV_TRAFFIC_STATISTICS_DATA_S stTrafficStatistic = {0};

    stStatisticCond.dwChannelID = ga_pMainDlg->GetCurChlIndex()+1;

    GetTimeInfo(stStatisticCond.tBeginTime, stStatisticCond.tEndTime);
    stStatisticCond.dwFormType = m_dwReportType;
    stStatisticCond.dwStatisticsType = m_dwCountingType;

    BOOL bRet = NETDEV_GetTrafficStatistic(lpDevHandle, &stStatisticCond, &stTrafficStatistic);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Get Traffic Statistic");
        m_oPeopleCountingStatisticsList.DeleteAllItems();
        return;
    }
    else
    {
        NETDEMO_LOG_SUCC(NULL, "Get Traffic Statistic");
        DisplaytheStatistics(stTrafficStatistic);
    }

    return;
}
