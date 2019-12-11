
#include "stdafx.h"
#include "NetDemo.h"
#include "DlgCycleMonitor.h"

IMPLEMENT_DYNAMIC(CDlgCycleMonitor, CDialog)

CDlgCycleMonitor::CDlgCycleMonitor(CWnd* pParent /*=NULL*/)
    : CDialog(CDlgCycleMonitor::IDD, pParent)
    , m_dwIntervalTime(NETDEMO_CYCLE_MIN_INTERVAL)
{

}

CDlgCycleMonitor::~CDlgCycleMonitor()
{
}

void CDlgCycleMonitor::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_CYCLE_ALLCHANNEL, m_oCycleAllChlList);
    DDX_Control(pDX, IDC_LIST_CYCLE_SCREEN, m_oCycleScreenList);
    DDX_Control(pDX, IDC_COMBO_CYCLE_TYPE, m_oCBoxCycleType);
    DDX_Control(pDX, IDC_COMBO_WIN_INDEX, m_oCBoxCycleWinID);
    DDX_Text(pDX, IDC_EDIT_CYCLE_INTERVALTIME, m_dwIntervalTime);
}

BEGIN_MESSAGE_MAP(CDlgCycleMonitor, CDialog)
    ON_BN_CLICKED(IDC_BTN_CYCLE_ADDALL, &CDlgCycleMonitor::OnBnClickedBtnCycleAddall)
    ON_BN_CLICKED(IDC_BTN_DELALL, &CDlgCycleMonitor::OnBnClickedBtnDelall)
    ON_BN_CLICKED(IDC_BTN_CYCLE_ADD, &CDlgCycleMonitor::OnBnClickedBtnCycleAdd)
    ON_BN_CLICKED(IDC_BTN_CYCLE_DEL, &CDlgCycleMonitor::OnBnClickedBtnCycleDel)
    ON_CBN_SELCHANGE(IDC_COMBO_CYCLE_TYPE, &CDlgCycleMonitor::OnCbnSelchangeComboCycleType)
    ON_CBN_SELCHANGE(IDC_COMBO_WIN_INDEX, &CDlgCycleMonitor::OnCbnSelchangeComboWinIndex)
    ON_BN_CLICKED(IDOK, &CDlgCycleMonitor::OnBnClickedOk)
    ON_BN_CLICKED(IDC_BTN_CYCLE_STOP_PLAY, &CDlgCycleMonitor::OnBnClickedBtnCycleStopPlay)
    ON_BN_CLICKED(IDC_BTN_CYCLE_CANCEL, &CDlgCycleMonitor::OnBnClickedBtnCycleStopCancel)
    ON_EN_KILLFOCUS(IDC_EDIT_CYCLE_INTERVALTIME, &CDlgCycleMonitor::OnEnKillfocusEditCycleIntervaltime)
END_MESSAGE_MAP()

BOOL CDlgCycleMonitor::OnInitDialog()
{
    ::EnableMenuItem(::GetSystemMenu(this->m_hWnd, false), SC_CLOSE, MF_BYCOMMAND | MF_GRAYED);

    CDialog::OnInitDialog();

    m_oCycleAllChlList.SetExtendedStyle(m_oCycleAllChlList.GetExtendedStyle()|LVS_EX_FULLROWSELECT);
    m_oCycleAllChlList.InsertColumn(0,"ga_index", LVCFMT_LEFT, 0, 0); //disable view
    m_oCycleAllChlList.InsertColumn(1,"Device", LVCFMT_LEFT, 90, 0);
    m_oCycleAllChlList.InsertColumn(2, "Channel", LVCFMT_LEFT, 70, 1);

    m_oCycleScreenList.SetExtendedStyle(m_oCycleScreenList.GetExtendedStyle()|LVS_EX_FULLROWSELECT);
    m_oCycleScreenList.InsertColumn(0,"ga_index", LVCFMT_LEFT, 0, 0); //disable view
    m_oCycleScreenList.InsertColumn(1,"Device", LVCFMT_LEFT, 90, 0);
    m_oCycleScreenList.InsertColumn(2, "Channel", LVCFMT_LEFT, 70, 1);
   
    m_oCBoxCycleType.AddString("Single Screen");
    m_oCBoxCycleType.AddString("All Screen");
    
    char temp[NETDEV_LEN_16];
    for (INT32 i=1;i<=NETDEMO_MAX_SCREENNUM;i++)
    {
        memset(temp,0,sizeof(NETDEV_LEN_16));
        itoa(i,temp,10);
        m_oCBoxCycleWinID.AddString(temp);
    }

    m_oCBoxCycleType.SetCurSel(0);
    m_oCBoxCycleWinID.SetCurSel(0);
    return TRUE;
}

void CDlgCycleMonitor::InitAllChannelList()
{
    if(FALSE == ga_pMainDlg->GetCycleMonitor())
    { 
        m_oCycleAllChlList.DeleteAllItems();
        m_oCycleScreenList.DeleteAllItems();
        EnabledWindow(TRUE);

        INT32 dwCount = 0;
        for (INT32 i = 0; i < NETDEMO_MAX_DEVICES; i++)
        {
            NETDEMO_DEVICE_INFO stDevinfo = gastDeviceInfo[i];
            char szGaIndex[10] = {0}; //ga_struDeviceInfo Index
            itoa(i,szGaIndex,10);
            if (stDevinfo.dwMaxChnNum <= 0)
            {
                return;
            }

            for (INT32 j = 0; j < stDevinfo.dwMaxChnNum; j++)
            {
                LPNETDEMO_CHANNEL_INFO pstChnInfo = &stDevinfo.pstChlInfo[j];
                char szChannel[64] = {0};
                if (NETDEV_CHL_STATUS_ONLINE != pstChnInfo->stChlDetailInfo.enStatus)
                {
                    continue;
                }
                if (NETDEMO_LOGTYPE_LOCAL == stDevinfo.dwLoginType)
                {
                    itoa(stDevinfo.pstChlInfo[j].dwChlID,szChannel,10);
                    INT32 dwRow = m_oCycleAllChlList.InsertItem(dwCount, "");
                    m_oCycleAllChlList.SetItemText(dwRow, 0, szGaIndex); //add ga_struDeviceInfo Index
                    m_oCycleAllChlList.SetItemText(dwRow, 1, stDevinfo.szIPAddr);
                    m_oCycleAllChlList.SetItemText(dwRow, 2, szChannel);
                }
                else
                {
                    itoa(stDevinfo.pstChlInfo[j].dwChlID,szChannel,10);
                    INT32 dwRow = m_oCycleAllChlList.InsertItem(dwCount, "");
                    m_oCycleAllChlList.SetItemText(dwRow, 0, szGaIndex);
                    m_oCycleAllChlList.SetItemText(dwRow, 1, stDevinfo.stCloudDevinfo.szDevName);
                    m_oCycleAllChlList.SetItemText(dwRow, 2, szChannel);
                }

                dwCount++;
            }
        }
    }
    else
    {
        EnabledWindow(FALSE);
    }
 
    return;
}

void CDlgCycleMonitor::OnBnClickedBtnCycleAddall()
{
    UpdateData(TRUE);

    for (INT32 i=0;i<m_oCycleAllChlList.GetItemCount();i++)
    {
        CString strGaIndex = m_oCycleAllChlList.GetItemText(i,0);
        CString Device = m_oCycleAllChlList.GetItemText(i,1);
        CString Channel = m_oCycleAllChlList.GetItemText(i,2);
        
        INT32 dwRow = m_oCycleScreenList.InsertItem(i, "");
        m_oCycleScreenList.SetItemText(dwRow, 0, strGaIndex);
        m_oCycleScreenList.SetItemText(dwRow, 1, Device);
        m_oCycleScreenList.SetItemText(dwRow, 2, Channel);
    }

    m_oCycleAllChlList.DeleteAllItems();
    SaveCycInfo();

    return;
}

void CDlgCycleMonitor::OnBnClickedBtnDelall()
{
    for (INT32 i=0;i<m_oCycleScreenList.GetItemCount();i++)
    {
        CString strGaIndex = m_oCycleScreenList.GetItemText(i,0);
        CString Device = m_oCycleScreenList.GetItemText(i,1);
        CString Channel = m_oCycleScreenList.GetItemText(i,2);

        INT32 dwRow = m_oCycleAllChlList.InsertItem(i, "");
        m_oCycleAllChlList.SetItemText(dwRow, 0, strGaIndex);
        m_oCycleAllChlList.SetItemText(dwRow, 1, Device);
        m_oCycleAllChlList.SetItemText(dwRow, 2, Channel);
    }

    m_oCycleScreenList.DeleteAllItems();
    SaveCycInfo();

    return;
}

void CDlgCycleMonitor::OnBnClickedBtnCycleAdd()
{
    if ( 0 == m_oCycleAllChlList.GetItemCount() ||
        m_oCycleAllChlList.GetSelectionMark() < 0)
    {
        return;
    }

    INT32 dwIndex = m_oCycleAllChlList.GetSelectionMark();
    INT32 dwScrCount = m_oCycleScreenList.GetItemCount();

    CString strGaIndex = m_oCycleAllChlList.GetItemText(dwIndex,0);
    CString Device = m_oCycleAllChlList.GetItemText(dwIndex,1);
    CString Channel = m_oCycleAllChlList.GetItemText(dwIndex,2);

    INT32 dwRow = m_oCycleScreenList.InsertItem(dwScrCount, "");
    m_oCycleScreenList.SetItemText(dwRow, 0, strGaIndex);
    m_oCycleScreenList.SetItemText(dwRow, 1, Device);
    m_oCycleScreenList.SetItemText(dwRow, 2, Channel);

    m_oCycleAllChlList.DeleteItem(dwIndex);
    m_oCycleAllChlList.SetSelectionMark(-1);
    SaveCycInfo();
    return;
}

void CDlgCycleMonitor::OnBnClickedBtnCycleDel()
{
    if ( 0 == m_oCycleScreenList.GetItemCount() ||
         m_oCycleScreenList.GetSelectionMark() < 0)
    {
        return;
    }
    INT32 dwIndex = m_oCycleScreenList.GetSelectionMark();
    INT32 dwScrCount = m_oCycleAllChlList.GetItemCount();

    CString strGaIndex = m_oCycleScreenList.GetItemText(dwIndex,0);
    CString Device = m_oCycleScreenList.GetItemText(dwIndex,1);
    CString Channel = m_oCycleScreenList.GetItemText(dwIndex,2);

    INT32 dwRow = m_oCycleAllChlList.InsertItem(dwScrCount, "");
    m_oCycleAllChlList.SetItemText(dwRow, 0, strGaIndex);
    m_oCycleAllChlList.SetItemText(dwRow, 1, Device);
    m_oCycleAllChlList.SetItemText(dwRow, 2, Channel);

    m_oCycleScreenList.DeleteItem(dwIndex);
    m_oCycleScreenList.SetSelectionMark(-1);
    SaveCycInfo();

    return;
}

void CDlgCycleMonitor::OnCbnSelchangeComboCycleType()
{
    INT32 dwtype = m_oCBoxCycleType.GetCurSel();
    if (NETDEMO_CYCLETYPE_SINGLE == dwtype)
    {
        m_oCBoxCycleWinID.EnableWindow(TRUE);
    }
    else if (NETDEMO_CYCLETYPE_ALLSCREEN == dwtype)
    {
        m_oCycleScreenList.DeleteAllItems(); 
        m_oCBoxCycleWinID.SetCurSel(0);
        m_oCBoxCycleWinID.EnableWindow(FALSE);    
    }

    memset(&ga_pMainDlg->m_stCycleInfo,0,sizeof(ga_pMainDlg->m_stCycleInfo));
    ga_pMainDlg->SetCycleMonitor(FALSE);
    InitAllChannelList();

    return;
}


void CDlgCycleMonitor::SaveCycInfo()
{
    UpdateData(TRUE);
    INT32 dwDevCount = 0;
    INT32 dwWinIndex = m_oCBoxCycleWinID.GetCurSel();
    memset(&ga_pMainDlg->m_stCycleInfo.szCycleWinInfo[dwWinIndex],0,sizeof(ga_pMainDlg->m_stCycleInfo.szCycleWinInfo[dwWinIndex]));

    for (INT32 i=0;i<m_oCycleScreenList.GetItemCount();i++)
    {
        CString strGaIndex = m_oCycleScreenList.GetItemText(i,0);
        CString Device = m_oCycleScreenList.GetItemText(i,1);
        CString Channel = m_oCycleScreenList.GetItemText(i,2);
        
        ga_pMainDlg->m_stCycleInfo.szCycleWinInfo[dwWinIndex].szCycleDevInfo[i].dwGaIndex =  atoi(strGaIndex.GetBuffer(0));
        ga_pMainDlg->m_stCycleInfo.szCycleWinInfo[dwWinIndex].szCycleDevInfo[i].dwChnID =  atoi(Channel.GetBuffer(0)); 
        strncpy(ga_pMainDlg->m_stCycleInfo.szCycleWinInfo[dwWinIndex].szCycleDevInfo[i].szDevName,
            Device.GetBuffer(0), 
            sizeof(ga_pMainDlg->m_stCycleInfo.szCycleWinInfo[dwWinIndex].szCycleDevInfo[i].szDevName) - 1);
        dwDevCount++;
    }

    ga_pMainDlg->m_stCycleInfo.szCycleWinInfo[dwWinIndex].dwWinID = dwWinIndex;
    ga_pMainDlg->m_stCycleInfo.szCycleWinInfo[dwWinIndex].dwDevCount = dwDevCount;
    ga_pMainDlg->m_stCycleInfo.dwCycleType = m_oCBoxCycleType.GetCurSel();
    ga_pMainDlg->m_stCycleInfo.dwIntervalTime = m_dwIntervalTime;

    return;
}

void CDlgCycleMonitor::OnCbnSelchangeComboWinIndex()
{
    m_oCycleScreenList.DeleteAllItems();
    InitAllChannelList();

    INT32 dwDevCount = 0;
    INT32 dwWinIndex = m_oCBoxCycleWinID.GetCurSel();

    for (INT32 i=0;i< ga_pMainDlg->m_stCycleInfo.szCycleWinInfo[dwWinIndex].dwDevCount;i++)
    {
        char szGaIndex[NETDEV_LEN_16] = {0};
        char szChnId[NETDEV_LEN_16] = {0};
        INT32 dwGaIndex = ga_pMainDlg->m_stCycleInfo.szCycleWinInfo[dwWinIndex].szCycleDevInfo[i].dwGaIndex;
        INT32 dwChnID = ga_pMainDlg->m_stCycleInfo.szCycleWinInfo[dwWinIndex].szCycleDevInfo[i].dwChnID;
        CString DevName = ga_pMainDlg->m_stCycleInfo.szCycleWinInfo[dwWinIndex].szCycleDevInfo[i].szDevName;
        m_dwIntervalTime = ga_pMainDlg->m_stCycleInfo.dwIntervalTime;
        itoa(dwGaIndex,szGaIndex,10);
        itoa(dwChnID,szChnId,10);
        
        INT32 dwRow = m_oCycleScreenList.InsertItem(i, "");
        m_oCycleScreenList.SetItemText(dwRow, 0, szGaIndex);
        m_oCycleScreenList.SetItemText(dwRow, 1, DevName);
        m_oCycleScreenList.SetItemText(dwRow, 2, szChnId);

        dwDevCount++;
    }

    UpdateData(FALSE);
    return;
}

void CDlgCycleMonitor::OnBnClickedOk()
{
    UpdateData(TRUE);
    BOOL bCycInfo = FALSE;

    for (int i=0; i < NETDEMO_MAX_SCREENNUM;i++)
    {
        if (0 != ga_pMainDlg->m_stCycleInfo.szCycleWinInfo[i].dwDevCount)
        {
            bCycInfo = TRUE;
            break;
        }
    }

    if (TRUE != bCycInfo)
    {
        NETDEMO_LOG_ERROR(NULL, "Please add cycle monitor plan");
        return ;
    }

    ga_pMainDlg->StartCycleMonitor();
    EnabledWindow(false);
    return;
}

void CDlgCycleMonitor::OnBnClickedBtnCycleStopPlay()
{
    m_oCycleScreenList.DeleteAllItems();

    ga_pMainDlg->StopCycMonitor();
    ga_pMainDlg->SetCycleMonitor(FALSE);

    memset(&ga_pMainDlg->m_stCycleInfo,0,sizeof(ga_pMainDlg->m_stCycleInfo));

    InitAllChannelList();
    EnabledWindow(TRUE);

    return;
}

void CDlgCycleMonitor::EnabledWindow(bool bEnable)
{
    (CButton *)GetDlgItem(IDOK)->EnableWindow(bEnable);
    (CButton *)GetDlgItem(IDC_BTN_CYCLE_ADDALL)->EnableWindow(bEnable);
    (CButton *)GetDlgItem(IDC_BTN_CYCLE_ADD)->EnableWindow(bEnable);
    (CButton *)GetDlgItem(IDC_BTN_CYCLE_DEL)->EnableWindow(bEnable);
    (CButton *)GetDlgItem(IDC_BTN_DELALL)->EnableWindow(bEnable);
    
    (CButton *)GetDlgItem(IDC_EDIT_CYCLE_INTERVALTIME)->EnableWindow(bEnable);
    (CButton *)GetDlgItem(IDC_COMBO_CYCLE_TYPE)->EnableWindow(bEnable); 

    return;
}

void CDlgCycleMonitor::OnBnClickedBtnCycleStopCancel()
{
    EnabledWindow(TRUE);
    EndDialog(-1);

    return;
}

void CDlgCycleMonitor::OnEnKillfocusEditCycleIntervaltime()
{
    UpdateData(TRUE);

    if (NETDEMO_CYCLE_MIN_INTERVAL >= m_dwIntervalTime)
    {
        m_dwIntervalTime = NETDEMO_CYCLE_MIN_INTERVAL;
    }
    else if (NETDEMO_CYCLE_MAX_INTERVAL <= m_dwIntervalTime)
    {
        m_dwIntervalTime = NETDEMO_CYCLE_MAX_INTERVAL;
    }

    ga_pMainDlg->m_stCycleInfo.dwIntervalTime = m_dwIntervalTime;

    UpdateData(FALSE);
    return;
}
