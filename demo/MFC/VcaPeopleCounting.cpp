#include "stdafx.h"
#include "NetDemo.h"
#include "VcaPeopleCounting.h"
#include <string>

// CVcaPeopleCounting 

#define COL_INDEX_DEVICE_IP         0
#define COL_INDEX_CHANNEL_ID        1
#define COL_INDEX_REPORT_TIME       2
#define COL_INDEX_INTERVAL_TIME     3
#define COL_INDEX_ENTER_NUM         4
#define COL_INDEX_EXIT_NUM          5
#define COL_INDEX_TOTAL_ENTER_NUM   6
#define COL_INDEX_TOTAL_EXIT_NUM    7

IMPLEMENT_DYNAMIC(CVcaPeopleCounting, CDialog)

CVcaPeopleCounting::CVcaPeopleCounting(CWnd* pParent /*=NULL*/)
    : CDialog(CVcaPeopleCounting::IDD, pParent)
{

}

CVcaPeopleCounting::~CVcaPeopleCounting()
{
}

void CVcaPeopleCounting::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_PASSENGER_FLOW_LIST, m_oPeopleCountingList);
}


BEGIN_MESSAGE_MAP(CVcaPeopleCounting, CDialog)
    ON_BN_CLICKED(IDC_REGISTER_PASSENGER_FLOW_SET_CALLBACK, &CVcaPeopleCounting::OnBnClickedRegisterPassengerFlowSetCallback)
    ON_BN_CLICKED(IDC_UNREGISTER_PASSENGER_FLOW_SET_CALLBACK, &CVcaPeopleCounting::OnBnClickedUnRegisterPassengerFlowSetCallback)
    ON_BN_CLICKED(IDC_CLEAR_PASSENGER_FLOW_LIST, &CVcaPeopleCounting::OnBnClickedClearPassengerFlowList)
END_MESSAGE_MAP()

BOOL CVcaPeopleCounting::OnInitDialog()
{

    CDialog::OnInitDialog();
    CRect rc(0, 0, 0, 0);
    GetParent()->GetClientRect(&rc);
    ((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
    MoveWindow(&rc);

    InitListCtrl();

    return TRUE;
}

void CVcaPeopleCounting::InitListCtrl()
{
    CString str="Device IP";
    m_oPeopleCountingList.InsertColumn(COL_INDEX_CHANNEL_ID,str,LVCFMT_CENTER,80);

    str="Channel ID";
    m_oPeopleCountingList.InsertColumn(COL_INDEX_CHANNEL_ID,str,LVCFMT_CENTER,70);

    str = "Report Time";
    m_oPeopleCountingList.InsertColumn(COL_INDEX_REPORT_TIME, str, LVCFMT_CENTER, 130);

    str = "Interval Time";
    m_oPeopleCountingList.InsertColumn(COL_INDEX_INTERVAL_TIME, str, LVCFMT_CENTER, 80);

    str = "Enter Number";
    m_oPeopleCountingList.InsertColumn(COL_INDEX_ENTER_NUM, str, LVCFMT_CENTER, 90);

    str = "Exit Number";
    m_oPeopleCountingList.InsertColumn(COL_INDEX_EXIT_NUM, str, LVCFMT_CENTER, 70);

    str = "Total Enter Number";
    m_oPeopleCountingList.InsertColumn(COL_INDEX_TOTAL_ENTER_NUM, str, LVCFMT_CENTER, 110);

    str = "Total Exit Number";
    m_oPeopleCountingList.InsertColumn(COL_INDEX_TOTAL_EXIT_NUM, str, LVCFMT_CENTER, 100);

    m_oPeopleCountingList.SetExtendedStyle(m_oPeopleCountingList.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES);

    return;
}

void STDCALL NETDEV_PassengerFlowStatisticCallBackFunc(IN LPVOID lpUserID,  IN LPNETDEV_PASSENGER_FLOW_STATISTIC_DATA_S pstPassengerFlowData, IN LPVOID lpUserData)
{
     CString m_strIP = ga_pMainDlg->GetDevIPByDevHandle(lpUserID);

     CHAR szChannelID[NETDEV_LEN_32] = {0};
     CHAR szInterval[NETDEV_LEN_32] = {0};
     CHAR szEnterNum[NETDEV_LEN_32] = {0};
     CHAR szExitNum[NETDEV_LEN_32] = {0};
     CHAR szTotalEnterNum[NETDEV_LEN_32] = {0};
     CHAR szTotalExitNum[NETDEV_LEN_32] = {0};

     _snprintf(szChannelID, sizeof(szChannelID), "%d", pstPassengerFlowData->dwChannelID);
     _snprintf(szInterval, sizeof(szInterval), "%d", pstPassengerFlowData->tInterval);
     _snprintf(szEnterNum, sizeof(szEnterNum), "%d", pstPassengerFlowData->dwEnterNum);
     _snprintf(szExitNum, sizeof(szExitNum), "%d", pstPassengerFlowData->dwExitNum);
     _snprintf(szTotalEnterNum, sizeof(szTotalEnterNum), "%d", pstPassengerFlowData->dwTotalEnterNum);
     _snprintf(szTotalExitNum, sizeof(szTotalExitNum), "%d",pstPassengerFlowData->dwTotalExitNum);

     CString strReportTime;
     tm *pTime = localtime((time_t*)&pstPassengerFlowData->tReportTime);
     strReportTime.Format("%d-%02d-%02d %02d:%02d:%02d",pTime->tm_year + 1900,pTime->tm_mon+1,pTime->tm_mday,pTime->tm_hour,pTime->tm_min,pTime->tm_sec);

     INT32 dwCount = ga_pMainDlg->m_oDlgVCA.m_oDlgPeopleCounting.m_oPeopleCountingList.GetItemCount();
     INT32 dwRow = ga_pMainDlg->m_oDlgVCA.m_oDlgPeopleCounting.m_oPeopleCountingList.InsertItem(dwCount, "");
     
     ga_pMainDlg->m_oDlgVCA.m_oDlgPeopleCounting.m_oPeopleCountingList.SetItemText(dwRow, COL_INDEX_DEVICE_IP, m_strIP);
     ga_pMainDlg->m_oDlgVCA.m_oDlgPeopleCounting.m_oPeopleCountingList.SetItemText(dwRow, COL_INDEX_CHANNEL_ID, szChannelID);
     ga_pMainDlg->m_oDlgVCA.m_oDlgPeopleCounting.m_oPeopleCountingList.SetItemText(dwRow, COL_INDEX_REPORT_TIME, strReportTime.GetBuffer());
     ga_pMainDlg->m_oDlgVCA.m_oDlgPeopleCounting.m_oPeopleCountingList.SetItemText(dwRow, COL_INDEX_INTERVAL_TIME, szInterval);
     ga_pMainDlg->m_oDlgVCA.m_oDlgPeopleCounting.m_oPeopleCountingList.SetItemText(dwRow, COL_INDEX_ENTER_NUM, szEnterNum);
     ga_pMainDlg->m_oDlgVCA.m_oDlgPeopleCounting.m_oPeopleCountingList.SetItemText(dwRow, COL_INDEX_EXIT_NUM, szExitNum);
     ga_pMainDlg->m_oDlgVCA.m_oDlgPeopleCounting.m_oPeopleCountingList.SetItemText(dwRow, COL_INDEX_TOTAL_ENTER_NUM, szTotalEnterNum);
     ga_pMainDlg->m_oDlgVCA.m_oDlgPeopleCounting.m_oPeopleCountingList.SetItemText(dwRow, COL_INDEX_TOTAL_EXIT_NUM, szTotalExitNum);
     ga_pMainDlg->m_oDlgVCA.m_oDlgPeopleCounting.m_oPeopleCountingList.Invalidate();
     ga_pMainDlg->m_oDlgVCA.m_oDlgPeopleCounting.m_oPeopleCountingList.UpdateWindow();

     return;
}

void CVcaPeopleCounting::OnBnClickedRegisterPassengerFlowSetCallback()
{
    LPVOID lpDevHandle = ga_pMainDlg->GetDevHandle();
    BOOL bRet = NETDEV_SetPassengerFlowStatisticCallBack(lpDevHandle, NETDEV_PassengerFlowStatisticCallBackFunc, NULL);
    if (TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Set Passenger Flow Statistic Call Back");
        return;
    }
    
    NETDEMO_LOG_SUCC(NULL, "Set Passenger Flow Statistic Call Back");
    return;
}

void CVcaPeopleCounting::OnBnClickedUnRegisterPassengerFlowSetCallback()
{
    LPVOID lpDevHandle = ga_pMainDlg->GetDevHandle();
    BOOL bRet = NETDEV_SetPassengerFlowStatisticCallBack(lpDevHandle, NULL, NULL);
    if (TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "UnRegister Passenger Flow Statistic Call back");
        return;
    }

    NETDEMO_LOG_SUCC(NULL, "UnRegister Passenger Flow Callback");
    return;
}

void CVcaPeopleCounting::OnBnClickedClearPassengerFlowList()
{
    if (IDOK==MessageBox("Clear the PeopleCounting list?","Warning",IDOK))
    {
        ga_pMainDlg->m_oDlgVCA.m_oDlgPeopleCounting.m_oPeopleCountingList.DeleteAllItems();
    }

    return;
}