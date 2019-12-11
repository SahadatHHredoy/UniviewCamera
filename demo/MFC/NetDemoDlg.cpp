// NetDemoDlg.cpp : 
//

#include "stdafx.h"
#include "NetDemo.h"
#include "NetDemoDlg.h"
#include "NetDEVSDK.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define NETDEMO_TREE_ALL                0
#define NETDEMO_DEVICE_LOCAL            1
#define NETDEMO_DEVICE_CLOUD            2
#define NETDEMO_DEVICE_LOCAL_LOGOUT     3
#define NETDEMO_DEVICE_CLOUD_LOGOUT     4
#define NETDEMO_CHANNEL_LOGIN           5
#define NETDEMO_CHANNEL_LOGOUT          6

#define MANU_TAB_INDEX_LIVEVIEW             0
#define MANU_TAB_INDEX_PLAYBACK             1
#define MANU_TAB_INDEX_CFG                  2
#define MANU_TAB_INDEX_ALARMRECORDS         3
#define MANU_TAB_INDEX_VCA                  4
#define MANU_TAB_INDEX_MAINTAIN             5
#define MANU_TAB_INDEX_USERCFG              6

void STDCALL AlarmCallBack_PF(IN LPVOID    lpUserID,
                                 IN NETDEV_ALARM_INFO_EX_S   stAlarmInfo,
                                 IN LPVOID    lpUserData
                              )
{
    CMenuAlarm* pDlgAlarm = (CMenuAlarm*)lpUserData;
    pDlgAlarm->handleRealWarning(lpUserID, stAlarmInfo);
}

void STDCALL ExceptionCallBack_PF(IN LPVOID dwUserID,
                                  IN INT32  dwType,
                                  IN LPVOID dwHandle,
                                  IN LPVOID  dwUserData
                                  )
{
    CMenuAlarm* pDlgAlarm = (CMenuAlarm*)dwUserData;
    pDlgAlarm->handleRealWarning(dwUserID, dwType);
    if(NETDEV_EXCEPTION_EXCHANGE == dwType)
    {
        for (int dwIndex=0; dwIndex<NETDEMO_MAX_DEVICES; dwIndex++)
        {
            if (gastDeviceInfo[dwIndex].lpDevHandle == dwUserID)
            {
                ga_pMainDlg->Logout(gastDeviceInfo[dwIndex]);
                gastDeviceInfo[dwIndex].lpDevHandle = NULL;
                NETDEMO_DEVICE_INFO &stNetDevInfo = gastDeviceInfo[dwIndex];
                stNetDevInfo.lpDevHandle = NULL;
                for (int i = 0;i<stNetDevInfo.dwMaxChnNum;i++)
                {
                    stNetDevInfo.pstChlInfo[i].stChlDetailInfo.enStatus = NETDEV_CHL_STATUS_OFFLINE;
                }

                ga_pMainDlg->UpdateDevState(gastDeviceInfo[dwIndex].hTreeItem, stNetDevInfo);
                return;
            }
        }
    }
}

void STDCALL FaceCallBack_PF(IN LPVOID lpUserID,IN LPNETDEV_TMS_FACE_SNAPSHOT_PIC_INFO_S pstFaceSnapShotData,IN LPVOID lpUserData )
{

    CFile file;


    SYSTEMTIME st;

    CString strTime;

    GetLocalTime(&st);

    strTime.Format("%s_%s-%02d%02d%02d%03d",pstFaceSnapShotData->szPassTime, pstFaceSnapShotData->szRecordID, st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);

    CString FileName = gstLocalParam.szPictureSavePath + CString("\\") + strTime + CString("face.jpg");
    file.Open(FileName, CFile::modeCreate | CFile::modeWrite|CFile::typeBinary);
    file.Write(pstFaceSnapShotData->pcPicBuff, pstFaceSnapShotData->udwPicBuffLen);//CString m_data
    file.Close();

    return;
}

void STDCALL CarPlateCallBack_PF(IN LPVOID lpUserID,IN LPNETDEV_TMS_CAR_PLATE_INFO_S pstCarPlateData,IN LPVOID lpUserData )
{
    if(pstCarPlateData->udwPicNum != 0)
    {
        for(int i=0;i<pstCarPlateData->udwPicNum;i++)
        {
            CFile file;

            SYSTEMTIME st;

            CString strTime;

            GetLocalTime(&st);

            strTime.Format("CamID-%sRecord-%sTollgateID-%sLaneID-%s-%2d-%2d-%2d",pstCarPlateData->stTmsXmlInfo.szCamID,pstCarPlateData->stTmsXmlInfo.szRecordID,pstCarPlateData->stTmsXmlInfo.szTollgateID,pstCarPlateData->stTmsXmlInfo.szLaneID, st.wHour,st.wMinute,st.wSecond);

            CString FileName = gstLocalParam.szPictureSavePath + CString("\\") + strTime + CString("CarPlate.jpg");
            file.Open(FileName, CFile::modeCreate | CFile::modeWrite|CFile::typeBinary);
            file.Write(pstCarPlateData->stTmsPicInfo[i].pcPicData,pstCarPlateData->stTmsPicInfo[i].udwPicSize);
            file.Close();
        }
    }
    return ;

}

class CAboutDlg : public CDialog
{
public:
    CAboutDlg();

    enum { IDD = IDD_DLG_ABOUTBOX };

    protected:
    virtual void DoDataExchange(CDataExchange* pDX);

protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


DWORD WINAPI CNetDemoDlg::CycleMonitorThread(LPVOID lpArg)
{
    CNetDemoDlg* pThis = reinterpret_cast<CNetDemoDlg*>(lpArg);
    while(pThis->m_bStopCycFlag)
    {
        while(pThis->m_bCycleMonitor)
        {
            if (NETDEMO_CYCLETYPE_ALLSCREEN == pThis->m_stCycleInfo.dwCycleType)
            {
                if(pThis->m_stCycleInfo.szCycleWinInfo[0].dwCurDevPlayIndex >= pThis->m_stCycleInfo.szCycleWinInfo[0].dwDevCount)
                {
                    pThis->m_stCycleInfo.szCycleWinInfo[0].dwCurDevPlayIndex = 0;
                }

                for (INT32 screenNo = 0; screenNo < NETDEMO_MAX_SCREENNUM; screenNo++)
                {
                    pThis->StopVideoByIndex(screenNo);
                    if (pThis->m_stCycleInfo.szCycleWinInfo[0].dwCurDevPlayIndex >= pThis->m_stCycleInfo.szCycleWinInfo[0].dwDevCount)
                    {
                        continue;
                    }
                    NETDEV_PREVIEWINFO_S stNetInfo = {0};
                    INT32 dwCurPlayIndex = pThis->m_stCycleInfo.szCycleWinInfo[0].dwCurDevPlayIndex;
                    INT32 dwGaDevindex = pThis->m_stCycleInfo.szCycleWinInfo[0].szCycleDevInfo[dwCurPlayIndex].dwGaIndex;

                    CPlayWnd* pPlayWnd = (CPlayWnd *)pThis->m_oScreenPannel.GetPage(screenNo);

                    stNetInfo.hPlayWnd = pPlayWnd->m_hWnd;
                    stNetInfo.dwStreamType = NETDEV_LIVE_STREAM_INDEX_MAIN;
                    stNetInfo.dwLinkMode = NETDEV_TRANSPROTOCAL_RTPTCP;
                    stNetInfo.dwChannelID = pThis->m_stCycleInfo.szCycleWinInfo[0].szCycleDevInfo[dwCurPlayIndex].dwChnID;

                    LPVOID lpDevHandle = gastDeviceInfo[dwGaDevindex].lpDevHandle;
                    if(lpDevHandle != NULL)
                    {
                        LPVOID lpPlayHandle = NETDEV_RealPlay(lpDevHandle, &stNetInfo, NULL, 0);
                        if (lpPlayHandle != NULL)
                        {
                            pPlayWnd->SetSplitHandle(lpPlayHandle);
                            pPlayWnd->SetSplitType(NETDEMO_SPLIT_TYPE_CYCLEMONITOR);
                        }
                    }
                    pThis->m_stCycleInfo.szCycleWinInfo[0].dwCurDevPlayIndex++;
                }
            }
            else if (NETDEMO_CYCLETYPE_SINGLE == pThis->m_stCycleInfo.dwCycleType)
            {
                 for (INT32 i=0;i<NETDEMO_MAX_SCREENNUM;i++)
                 {
                     if (pThis->m_stCycleInfo.szCycleWinInfo[i].dwDevCount > 0 && 
                         pThis->m_stCycleInfo.szCycleWinInfo[i].dwWinID == ga_pMainDlg->m_oDlgCycleMonitor.m_oCBoxCycleWinID.GetCurSel())
                     {
                         pThis->CycMonitorControl(i);
                     }
                 }
            }
            Sleep(pThis->m_stCycleInfo.dwIntervalTime * 1000);
        }
    }
    return 0;
}

DWORD WINAPI CNetDemoDlg::DevLoginThread(LPVOID lpArg)
{
    CNetDemoDlg* pThis = reinterpret_cast<CNetDemoDlg*>(lpArg);
    while(pThis->m_bStopLoginFlag)
    {
        while(pThis->m_bLoginThread)
        {
            if ( 0 < pThis->m_oListDevInfoBuffer.size())
            {
                std::list<NETDEMO_DEVICE_INFO>::iterator itor = pThis->m_oListDevInfoBuffer.begin();
                NETDEMO_DEVICE_INFO stNetDevInfo = (*itor);
                if ( 0 >= stNetDevInfo.dwMaxChnNum) // login and draw
                {
                    pThis->AddDevice(stNetDevInfo);
                }
                else
                {
                    pThis->DeviceoperLogin(stNetDevInfo);
                }
                pThis->m_oListDevInfoBuffer.pop_front();
            }
        }
    }

    return 0;
}

CNetDemoDlg::CNetDemoDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CNetDemoDlg::IDD, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    
    m_dwCurDevIndex = 0;
    m_dwCurChlIndex = 0;
    m_lpTalkID = NULL;

    memset(&m_stCycleInfo,0,sizeof(m_stCycleInfo));
    m_bStopCycFlag = FALSE;
    m_bCycleMonitor = FALSE;


    m_bStopLoginFlag  = FALSE;
    m_bLoginThread = FALSE;

    m_bClientLogListEnlarge = FALSE;

    m_dwCurSelectType = NETDEMO_TYPE_DEVICE;
}

CNetDemoDlg::~CNetDemoDlg()
{
}

void CNetDemoDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TREE_DEVICE_LIST, m_oDeviceTreeList);
    DDX_Control(pDX, IDC_TAB_MAIN_MENU, m_oTabManu);
    DDX_Control(pDX, IDC_LIST_ALL_LOG, m_oClientLogList);
}

BEGIN_MESSAGE_MAP(CNetDemoDlg, CDialog)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_TIMER()
    ON_WM_QUERYDRAGICON()
    ON_NOTIFY(NM_RCLICK, IDC_TREE_DEVICE_LIST, &CNetDemoDlg::OnNMRClickTreeDeviceList)
    ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN_MENU, &CNetDemoDlg::OnTcnSelchangeTabMainMenu)
    ON_BN_CLICKED(IDC_BUTTON_LOCAL_SETTING, &CNetDemoDlg::OnBnClickedButtonLocalSetting)
    ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_DEVICE_LIST, &CNetDemoDlg::OnTvnSelchangedTreeDeviceList)
    ON_COMMAND(ID_DEVICEOPER_LOGIN, &CNetDemoDlg::OnDeviceoperLogin)
    ON_BN_CLICKED(IDC_BUTTON_DISCOVERY, &CNetDemoDlg::OnBnClickedButtonDiscovery)
    ON_MESSAGE(WM_ADD_DEVICE, OnAddDevice)
    ON_COMMAND(ID_MENU_LOGIN_CLOUD, &CNetDemoDlg::OnLoginByCloud)
    ON_COMMAND(ID_MENU_LOGIN_DEVICE, &CNetDemoDlg::OnLoginByLocal)
    ON_COMMAND(ID_DEVICEOPER_DELETE, &CNetDemoDlg::OnDeleteDevice)
    ON_WM_CLOSE()
    ON_COMMAND(ID_DEVICEOPER_LOGOUT, &CNetDemoDlg::OnDeviceoperLogout)
    ON_COMMAND(ID_MENU_DEVICEOPER_ATTRIBUTE, &CNetDemoDlg::OnDeviceAttribute)
    ON_NOTIFY(NM_DBLCLK, IDC_TREE_DEVICE_LIST, &CNetDemoDlg::OnNMDblclkTreeDeviceList)
    ON_MESSAGE(WM_CLICK_REALPLAY_WND,&CNetDemoDlg::OnClickPlayWindow)
    ON_MESSAGE(WM_REALPLAY_SET_AUDIO_PARA,&CNetDemoDlg::OnSetDevAudioPara)
    ON_WM_HSCROLL()
    ON_BN_CLICKED(IDC_CLEAN_CLINTLOG, &CNetDemoDlg::OnBnClickedCleanClintlog)
    ON_BN_CLICKED(IDC_SAVE_CLINETLOG, &CNetDemoDlg::OnBnClickedSaveClinetlog)
    ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_ALL_LOG, &CNetDemoDlg::OnLvnColumnclickListAllLog)
END_MESSAGE_MAP()



BOOL CNetDemoDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL)
    {
        CString strAboutMenu;
        strAboutMenu.LoadString(IDS_ABOUTBOX);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    SetIcon(m_hIcon, TRUE);
    SetIcon(m_hIcon, FALSE);

    InitGlobalSysInfo();
    LoadTreeImage();
    g_ReadDeviceConfig();
    CreateTree();
    
    InitMainMenuUI();
    InitClientLogList();
    InitGlobalSysInfo();
    m_oScreenPannel.Create(
        NULL,
        NULL,
        WS_CHILD|WS_VISIBLE, 
        CRect(0,0,0,0), 
        this, 
        1981);

    m_oPtzPannel.Create(IDD_PANNEL_PTZ, this);
    m_oPannelPlayControl.Create(IDD_PANNEL_PLAYCONTROL,this);
    m_oDlgCfg.Create(IDD_MENU_CFG,this);
    m_oDlgPlayback.Create(IDD_MENU_PLAYBACK,this);
    m_oDlgAlarm.Create(IDD_MENU_ALARM,this);
    m_oDlgMaintain.Create(IDD_MENU_MAINTAIN,this);
    m_oDlgVCA.Create(IDD_MENU_VCA,this);
    m_oDlgDiscovery.Create(IDD_DLG_DISCOVERY,this);
    m_oDlgCycleMonitor.Create(IDD_DLG_PLAY_CYCLE,this);
    m_oDlgUserCfg.Create(IDD_MENU_USERCFG, this);
    m_oScreenPannel.ShowWindow(SW_SHOW);
    UpdatePannelPosition();

    m_oScreenPannel.SetShowPlayWin(NETDEMO_SPLIT16, m_dwActiveScreen);
    m_oPtzPannel.ShowWindow(SW_SHOW);
    m_oPannelPlayControl.ShowWindow(SW_SHOW);

    InitializeCriticalSection(&m_stCycCs);

    BOOL bRet = NETDEV_Init();
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Init SDK failed. Please run this program as administrator.");
    }

    CHAR *pszClientID = "48ea631a9664";
    NETDEV_SetClientID(pszClientID);
    
    if (TRUE != m_bStopLoginFlag)
    {
        m_bStopLoginFlag = TRUE;
        m_bLoginThread = TRUE;
        DWORD dwThreadId = 0;
        m_hLoginThread = CreateThread(NULL,0,LPTHREAD_START_ROUTINE(DevLoginThread), this, 0, &dwThreadId);
    }

    return TRUE;
}

void CNetDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialog::OnSysCommand(nID, lParam);
    }
}


void CNetDemoDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); 

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        INT32 cxIcon = GetSystemMetrics(SM_CXICON);
        INT32 cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        INT32 x = (rect.Width() - cxIcon + 1) / 2;
        INT32 y = (rect.Height() - cyIcon + 1) / 2;

        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialog::OnPaint();
    }
}

HCURSOR CNetDemoDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

void CNetDemoDlg::InitGlobalSysInfo()
{
    ga_pMainDlg = this;
}

void CNetDemoDlg::CreateTree(void)
{
    m_oDeviceTreeList.DeleteAllItems();
    CString str("(Right Click to Add Device)");
    m_hDevtree = m_oDeviceTreeList.InsertItem(str.GetBuffer(), 0, 0);
    m_oDeviceTreeList.Select(m_hDevtree,TVGN_CARET);

    for (INT32 i=0; i<NETDEMO_MAX_DEVICES;i++)
    {
        if (0 < gastDeviceInfo[i].dwMaxChnNum)
        {
            DrawTree(gastDeviceInfo[i]);
            m_oListDevInfoBuffer.push_back(gastDeviceInfo[i]);
        }
    }
}

void CNetDemoDlg::OnNMRClickTreeDeviceList(NMHDR *pNMHDR, LRESULT *pResult)
{
    CMenu pMenu;
    CPoint pt(0,0);
    GetCursorPos(&pt);
    HTREEITEM hRoot = m_oDeviceTreeList.GetRootItem();
    if (hRoot == NULL)
    {
        return;
    }
    else
    {
        CRect rect(0,0,0,0);
        ScreenToClient(&pt);
        GetDlgItem(IDC_TREE_DEVICE_LIST)->GetWindowRect(&rect);
        ScreenToClient(&rect);

        pt.x = pt.x-rect.left;
        pt.y = pt.y-rect.top;
        //while select first node or blank
        //HTREEITEM hSelect = m_oDeviceTreeList.GetSelectedItem();
        UINT uFlags = 0;
        HTREEITEM hSelect = m_oDeviceTreeList.HitTest(pt,&uFlags);
        if (hSelect == NULL )//|| m_iMainType != PREVIEW_T
        {
            return;
        }

        m_oDeviceTreeList.SelectItem(hSelect);
        INT32 sie = INT32(m_oDeviceTreeList.GetItemData(hSelect));
        INT32 iType = INT32(m_oDeviceTreeList.GetItemData(hSelect) / 1000);
    
        switch (iType)
        {
        case NETDEMO_NETDEMO_TREE_ALL_T:
            if (!pMenu.LoadMenu(IDR_MENU_LOGIN_TYPE))
            {
                return;
            }
            break;
        case NETDEMO_TYPE_DEVICE:
            if (!pMenu.LoadMenu(IDR_MENU_DEVICE))
            {
                return;
            }
            break;
        case NETDEMO_TYPE_CHANNEL:     
            return;
            break;
        default:
            break;
        }
    }
    GetCursorPos(&pt);
    pMenu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN,pt.x ,pt.y,this);    
    *pResult = 0;
}

HTREEITEM CNetDemoDlg::GetAfterItem(HTREEITEM hRoot)
{
    HTREEITEM hReturn = TVI_FIRST;
    HTREEITEM hChild = m_oDeviceTreeList.GetChildItem(hRoot);

    while (hChild)
    {
        if (0 ==  m_oDeviceTreeList.GetItemData(hChild) / 1000)   //break if it si device tree node
        {
            break;
        }

        hReturn = hChild;
        hChild = m_oDeviceTreeList.GetNextSiblingItem(hChild);
    }

    return hReturn;
}

void CNetDemoDlg::UpdateMainMenu()
{
    switch(m_dwMainMenuType)
    {
    case NETDEMO_MANU_INDEX_LIVEVIEW:
        m_oDlgCfg.ShowWindow(SW_HIDE);
        m_oScreenPannel.ShowWindow(SW_SHOW);
        m_oPtzPannel.ShowWindow(SW_SHOW);
        m_oDlgPlayback.ShowWindow(SW_HIDE);
        m_oDlgAlarm.ShowWindow(SW_HIDE);
        m_oDlgMaintain.ShowWindow(SW_HIDE);
        m_oDlgVCA.ShowWindow(SW_HIDE);
        m_oPannelPlayControl.ShowWindow(SW_SHOW);
        m_oDlgUserCfg.ShowWindow(SW_HIDE);
        break;
    case NETDEMO_MANU_INDEX_PLAYBACK:
        m_oDlgCfg.ShowWindow(SW_HIDE);
        m_oDlgAlarm.ShowWindow(SW_HIDE);
        m_oDlgMaintain.ShowWindow(SW_HIDE);
        m_oDlgVCA.ShowWindow(SW_HIDE);
        m_oScreenPannel.ShowWindow(SW_HIDE);
        m_oPtzPannel.ShowWindow(SW_HIDE);
        m_oPannelPlayControl.ShowWindow(SW_HIDE);
        m_oDlgUserCfg.ShowWindow(SW_HIDE);
        InitPlaybackUI();
        break;
    case NETDEMO_MANU_INDEX_CFG:
        m_oDlgAlarm.ShowWindow(SW_HIDE);
        m_oDlgCfg.ShowWindow(SW_HIDE);
        m_oDlgPlayback.ShowWindow(SW_HIDE);
        m_oDlgMaintain.ShowWindow(SW_HIDE);
        m_oDlgVCA.ShowWindow(SW_HIDE);
        m_oScreenPannel.ShowWindow(SW_HIDE);
        m_oPtzPannel.ShowWindow(SW_HIDE);
        m_oPannelPlayControl.ShowWindow(SW_HIDE);
        m_oDlgUserCfg.ShowWindow(SW_HIDE);
        InitCfgUI();    
        m_oDlgCfg.refreshCfgTab();
        break;
    case NETDEMO_MANU_INDEX_ALARMRECORDS:
        InitWarningUI();
        m_oDlgCfg.ShowWindow(SW_HIDE);
        m_oDlgPlayback.ShowWindow(SW_HIDE);
        m_oDlgMaintain.ShowWindow(SW_HIDE);
        m_oDlgVCA.ShowWindow(SW_HIDE);
        m_oScreenPannel.ShowWindow(SW_HIDE);
        m_oPtzPannel.ShowWindow(SW_HIDE);
        m_oPannelPlayControl.ShowWindow(SW_HIDE);
        m_oDlgUserCfg.ShowWindow(SW_HIDE);
        break;
    case NETDEMO_MANU_INDEX_VCA:
        InitVCAUI();
        m_oDlgAlarm.ShowWindow(SW_HIDE);
        m_oDlgCfg.ShowWindow(SW_HIDE);
        m_oDlgPlayback.ShowWindow(SW_HIDE);
        m_oDlgMaintain.ShowWindow(SW_HIDE);
        m_oScreenPannel.ShowWindow(SW_HIDE);
        m_oPtzPannel.ShowWindow(SW_HIDE);
        m_oPannelPlayControl.ShowWindow(SW_HIDE);
        m_oDlgUserCfg.ShowWindow(SW_HIDE);
        break;
    case NETDEMO_MANU_INDEX_MAINTAIN:
        InitMainTainUI();
        m_oDlgAlarm.ShowWindow(SW_HIDE);
        m_oDlgCfg.ShowWindow(SW_HIDE);
        m_oDlgPlayback.ShowWindow(SW_HIDE);
        m_oDlgVCA.ShowWindow(SW_HIDE);
        m_oScreenPannel.ShowWindow(SW_HIDE);
        m_oPtzPannel.ShowWindow(SW_HIDE);
        m_oPannelPlayControl.ShowWindow(SW_HIDE);
        m_oDlgUserCfg.ShowWindow(SW_HIDE);
        break;
    case NETDEMO_MANU_INDEX_USERCFG:
        InitUserCfgUI();
        m_oDlgAlarm.ShowWindow(SW_HIDE);
        m_oDlgCfg.ShowWindow(SW_HIDE);
        m_oDlgPlayback.ShowWindow(SW_HIDE);
        m_oDlgMaintain.ShowWindow(SW_HIDE);
        m_oDlgVCA.ShowWindow(SW_HIDE);
        m_oScreenPannel.ShowWindow(SW_HIDE);
        m_oPtzPannel.ShowWindow(SW_HIDE);
        m_oPannelPlayControl.ShowWindow(SW_HIDE);
        break;
    default:
        break;
    }
}

void CNetDemoDlg::OnTcnSelchangeTabMainMenu(NMHDR *pNMHDR, LRESULT *pResult)
{
    UpdateData(TRUE);
    m_dwMainMenuType = m_oTabManu.GetCurSel();
    if (m_bClientLogListEnlarge)
    {
        EnlargeList(FALSE);
        m_bClientLogListEnlarge = FALSE;
    }
    UpdateMainMenu();
    *pResult = 0;
}


void CNetDemoDlg::InitMainMenuUI()
{
    CString str ="Live View";
    m_oTabManu.InsertItem(MANU_TAB_INDEX_LIVEVIEW, str);

    str = "Playback";
    m_oTabManu.InsertItem(MANU_TAB_INDEX_PLAYBACK, str);

    str = "Configure";
    m_oTabManu.InsertItem(MANU_TAB_INDEX_CFG, str);

    str = "Alarm Records";
    m_oTabManu.InsertItem(MANU_TAB_INDEX_ALARMRECORDS, str);
    
    str = "VCA";
    m_oTabManu.InsertItem(MANU_TAB_INDEX_VCA, str);

    str = "Maintenance";
    m_oTabManu.InsertItem(MANU_TAB_INDEX_MAINTAIN, str);

    str = "User";
    m_oTabManu.InsertItem(MANU_TAB_INDEX_USERCFG, str);
}



void CNetDemoDlg::InitClientLogList()
{
    CString str = "Time";
    m_oClientLogList.InsertColumn(COL_INDEX_LOG_LIST_TIME, str, LVCFMT_CENTER, 120);

    str = "Device Info";
    m_oClientLogList.InsertColumn(COL_INDEX_LOG_LIST_DEV_INFO,str,LVCFMT_CENTER,180);

    str = "Operation";
    m_oClientLogList.InsertColumn(COL_INDEX_LOG_LIST_OPERATION, str, LVCFMT_CENTER, 230);

    str = "Status";
    m_oClientLogList.InsertColumn(COL_INDEX_LOG_LIST_STATUS, str, LVCFMT_CENTER, 60);

    str = "Error Code";
    m_oClientLogList.InsertColumn(COL_INDEX_LOG_LIST_ERRCODE,str,LVCFMT_CENTER,70);
    m_oClientLogList.SetExtendedStyle(m_oClientLogList.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES);
}


void CNetDemoDlg::UpdatePannelPosition()
{
    GetClientRect(&m_oClientRect);

    GetDlgItem(IDC_TREE_DEVICE_LIST)->GetWindowRect(&m_oDeviceTreeRect);
    GetDlgItem(IDC_LIST_ALL_LOG)->GetWindowRect(&m_oClientAllLogRect);
    GetDlgItem(IDC_TAB_MAIN_MENU)->GetWindowRect(&m_oPrimaryLabelRect);

    m_oPlayControlRect.bottom = m_oClientAllLogRect.top-30/* - 20*/;
    m_oPlayControlRect.top = m_oPlayControlRect.bottom -50 /* + 5*/;
    m_oPlayControlRect.left = m_oDeviceTreeRect.right/* + 10*/;
    m_oPlayControlRect.right = m_oClientAllLogRect.right-10;

    m_oScreenRect.top = m_oPrimaryLabelRect.bottom/* + 5*/;
    m_oScreenRect.bottom = m_oPlayControlRect.top/* - 20*/;
    m_oScreenRect.left = m_oDeviceTreeRect.right/* + 10*/;
    m_oScreenRect.right = m_oPlayControlRect.right;

    GetDlgItem(IDC_SCREEN_WINDOW)->MoveWindow(m_oScreenRect);
    
    m_oPTZRect.top = m_oPrimaryLabelRect.bottom/* + 5*/;
    m_oPTZRect.bottom = m_oClientAllLogRect.top-100/* - 20*/;
    m_oPTZRect.left = m_oScreenRect.right/* + 10*/;
    m_oPTZRect.right = m_oClientRect.right;


    m_oPannelPlayControl.MoveWindow(m_oPlayControlRect);
    m_oPtzPannel.MoveWindow(m_oPTZRect);
    m_oScreenPannel.MoveWindow(m_oScreenRect);
}

void CNetDemoDlg::InitCfgUI()
{
    CRect oRect(0,0,0,0);
    oRect.top = m_oPrimaryLabelRect.bottom/* + 5*/;
    oRect.bottom = m_oPlayControlRect.top/* - 20*/;
    oRect.left = m_oDeviceTreeRect.right/* + 10*/;
    oRect.right = m_oClientRect.right;
    m_oDlgCfg.MoveWindow(&oRect,true);
    m_oDlgCfg.ShowWindow(SW_SHOW);
}

void CNetDemoDlg::InitPlaybackUI()
{
    CRect oRect(0,0,0,0);
    oRect.top = m_oPrimaryLabelRect.bottom/* + 5*/;
    oRect.bottom = m_oPlayControlRect.top/* - 20*/;
    oRect.left = m_oDeviceTreeRect.right/* + 10*/;
    oRect.right = m_oClientRect.right;
    m_oDlgPlayback.MoveWindow(&oRect,true);
    m_oDlgPlayback.ShowWindow(SW_SHOW);
}

void CNetDemoDlg::InitWarningUI()
{
    CRect oRect(0,0,0,0);
    oRect.top = m_oPrimaryLabelRect.bottom/* + 5*/;
    oRect.bottom = m_oPlayControlRect.top/* - 20*/;
    oRect.left = m_oDeviceTreeRect.right/* + 10*/;
    oRect.right = m_oClientRect.right;
    m_oDlgAlarm.MoveWindow(&oRect,true);
    m_oDlgAlarm.ShowWindow(SW_SHOW); 
}

void CNetDemoDlg::InitMainTainUI()
{
    CRect oRect(0,0,0,0);
    oRect.top = m_oPrimaryLabelRect.bottom/* + 5*/;
    oRect.bottom = m_oPlayControlRect.top/* - 20*/;
    oRect.left = m_oDeviceTreeRect.right/* + 10*/;
    oRect.right = m_oClientRect.right;
    m_oDlgMaintain.MoveWindow(&oRect,true);
    m_oDlgMaintain.ShowWindow(SW_SHOW); 
}

void CNetDemoDlg::InitVCAUI()
{
    CRect oRect(0,0,0,0);
    oRect.top = m_oPrimaryLabelRect.bottom/* + 5*/;
    oRect.bottom = m_oPlayControlRect.top/* - 20*/;
    oRect.left = m_oDeviceTreeRect.right/* + 10*/;
    oRect.right = m_oClientRect.right;
    m_oDlgVCA.MoveWindow(&oRect,true);
    m_oDlgVCA.ShowWindow(SW_SHOW); 
}

void CNetDemoDlg::InitUserCfgUI()
{
    CRect oRect(0,0,0,0);
    oRect.top = m_oPrimaryLabelRect.bottom/* + 5*/;
    oRect.bottom = m_oPlayControlRect.top/* - 20*/;
    oRect.left = m_oDeviceTreeRect.right/* + 10*/;
    oRect.right = m_oClientRect.right;
    m_oDlgUserCfg.MoveWindow(&oRect,true);
    m_oDlgUserCfg.ShowWindow(SW_SHOW); 
}

void CNetDemoDlg::CycleMonitor()
{
    if(FALSE == m_bCycleMonitor)
    {
        memset(&m_stCycleInfo,0,sizeof(m_stCycleInfo));
    }

    m_oDlgCycleMonitor.ShowWindow(SW_SHOW);
    m_oDlgCycleMonitor.InitAllChannelList();
}

void CNetDemoDlg::OnBnClickedButtonLocalSetting()
{
    m_oDlgLocalSetting.DoModal();
}

void CNetDemoDlg::OnTvnSelchangedTreeDeviceList(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
    CPoint pt(0,0);
    GetCursorPos(&pt);

    CRect rect(0,0,0,0);
    ScreenToClient(&pt);
    GetDlgItem(IDC_TREE_DEVICE_LIST)->GetWindowRect(&rect);
    ScreenToClient(&rect);

    pt.x = pt.x-rect.left;
    pt.y = pt.y-rect.top;
   
    UINT uFlags = 0;
    // HTREEITEM hSelect = m_oDeviceTreeList.HitTest(pt,&uFlags);
    HTREEITEM hSelect = m_oDeviceTreeList.GetSelectedItem();
    if (hSelect == NULL)
    {
        return;
    }

    BOOL bLogined = FALSE;
    DWORD dwNoteData = m_oDeviceTreeList.GetItemData(hSelect);
    INT32 iType = dwNoteData/1000;
    INT32 iIndex = dwNoteData%1000;
    if (NETDEMO_TYPE_DEVICE == iType)
    {
        m_dwCurDevIndex = iIndex;
        m_hCurDeviceItem = hSelect;
        m_dwCurChlIndex = 0;
        m_hCurChanItem = NULL;
        m_dwCurSelectType = NETDEMO_TYPE_DEVICE;
    }
    else if (NETDEMO_TYPE_CHANNEL == iType)
    {
        m_dwCurSelectType = NETDEMO_TYPE_CHANNEL;
        m_dwCurChlIndex = iIndex + 1;
        m_hCurChanItem = hSelect;
        HTREEITEM hParent = m_oDeviceTreeList.GetParentItem(hSelect);
        if (hParent != NULL)
        {
            dwNoteData = m_oDeviceTreeList.GetItemData(hParent);
            iType = dwNoteData/1000;
            iIndex = dwNoteData%1000;
            if (NETDEMO_TYPE_DEVICE == iType)
            {
                m_dwCurDevIndex = iIndex;
                m_hCurDeviceItem = hParent;
            }
        }
    }
    else
    {
        m_dwCurDevIndex = 0;
        m_hCurDeviceItem = NULL;
        m_dwCurChlIndex = 0;
        m_hCurChanItem = NULL;
    }

    if( NETDEMO_MANU_INDEX_CFG == m_dwMainMenuType)
    {
        m_oDlgCfg.refreshCfgTab();
    }

    *pResult = 0;
}

INT32 CNetDemoDlg::GetSplit()
{
    return m_dwSplitNum;
}

void CNetDemoDlg::SetSplit(INT32 nSplit)
{
    m_dwSplitNum = nSplit;
    m_oPannelPlayControl.SetSplitNum(nSplit);
}

void CNetDemoDlg::OnDeviceoperLogin()
{
    INT32 nCurDevIndex = GetCurDeviceIndex();
    if (TRUE == IsExistInThreadBuffer(gastDeviceInfo[nCurDevIndex]))
    {
        return;
    }

    if ( NULL != gastDeviceInfo[nCurDevIndex].lpDevHandle)
    {
        NETDEMO_LOG_ERROR(NULL, "The Device already login");
        return;
    }

    NETDEMO_DEVICE_INFO stNetDevInfo = gastDeviceInfo[nCurDevIndex];
    m_oListDevInfoBuffer.push_back(stNetDevInfo);
    return;
}

void CNetDemoDlg::DeviceoperLogin(NETDEMO_DEVICE_INFO stNetDevInfo)
{
    if (NETDEMO_LOGTYPE_LOCAL == stNetDevInfo.dwLoginType)
    {
        if ( TRUE == Login(stNetDevInfo))
        {
            gastDeviceInfo[stNetDevInfo.dwDeviceIndex]  = stNetDevInfo;
            UpdateDevState(gastDeviceInfo[stNetDevInfo.dwDeviceIndex]);
        }
    }
    else
    {
        LPVOID  lpCloudHandle= NETDEV_LoginCloud(stNetDevInfo.szCloudUrl, stNetDevInfo.szCloudName, \
        stNetDevInfo.szCloudPasswd);
        if(NULL == lpCloudHandle)
        {
            NETDEMO_LOG_ERROR(NULL, "Login Cloud count failed");
            return;
        }

        stNetDevInfo.lpCloudHandle = lpCloudHandle;
        if ( TRUE ==Login(stNetDevInfo))
        {
            gastDeviceInfo[stNetDevInfo.dwDeviceIndex]  = stNetDevInfo;
            UpdateDevState(gastDeviceInfo[stNetDevInfo.dwDeviceIndex]);
        }
    }

    return;
}

void CNetDemoDlg::OnBnClickedButtonDiscovery()
{
    m_oDlgDiscovery.ShowWindow(SW_SHOW);
    return;
}

LRESULT CNetDemoDlg::OnAddDevice(WPARAM wParam, LPARAM lParam)
{
    NETDEMO_DEVICE_INFO stNetDevInfo = *((NETDEMO_DEVICE_INFO*)lParam);
    if (TRUE == IsExistInThreadBuffer(stNetDevInfo))
    {
        return NULL;
    }

    m_oListDevInfoBuffer.push_back(stNetDevInfo);
    return NULL;
}

void CNetDemoDlg::AddDevice(NETDEMO_DEVICE_INFO stNetDevInfo)
{
    if (NETDEMO_LOGTYPE_LOCAL == stNetDevInfo.dwLoginType)
    {
        HTREEITEM hChannel = NULL;
        if ( TRUE == Login(stNetDevInfo))
        {
            if (TRUE == IsExistInDevBuffer(stNetDevInfo))
            {
                NETDEMO_LOG_ERROR(NULL, "This Device is existed");
                return;
            }
            else
            {
                gastDeviceInfo[gaDeviceIndex] = stNetDevInfo;
                DrawTree(gastDeviceInfo[gaDeviceIndex]);
            }
        }  
    }
    else
    {
        LPVOID lpDevListHandle = NETDEV_FindCloudDevListEx(stNetDevInfo.lpCloudHandle);
        if(NULL == lpDevListHandle)
        {
            NETDEMO_LOG_ERROR(NULL, "Query cloud device list");
        }

        NETDEV_CLOUD_DEV_INFO_EX_S stCloudDevInfo = {0};
        
        while(NETDEV_FindNextCloudDevInfoEx(lpDevListHandle, &stCloudDevInfo))
        {
            stNetDevInfo.stCloudDevinfo = stCloudDevInfo;
            if ( TRUE == Login(stNetDevInfo))
            {
                gastDeviceInfo[gaDeviceIndex] = stNetDevInfo;
                DrawTree(gastDeviceInfo[gaDeviceIndex]);
            }
        }

        NETDEV_FindCloseCloudDevListEx(lpDevListHandle);
    }

    g_SaveDeviceConfig();
    return ;
}

void CNetDemoDlg::LoadTreeImage(void)
{
    CBitmap oaBitMap[7];

    m_oTreeImage.Create(16,16,ILC_COLOR32 | ILC_MASK,1,1);

    oaBitMap[NETDEMO_TREE_ALL].LoadBitmap(IDB_BMP_TREE);
    m_oTreeImage.Add(&oaBitMap[NETDEMO_TREE_ALL],RGB(1,1,1));

    oaBitMap[NETDEMO_DEVICE_LOCAL].LoadBitmap(IDB_BMP_DEV_LOCAL);
    m_oTreeImage.Add(&oaBitMap[NETDEMO_DEVICE_LOCAL],RGB(1,1,1));
    
    oaBitMap[NETDEMO_DEVICE_CLOUD].LoadBitmap(IDB_BMP_DEV_CLOUD);
    m_oTreeImage.Add(&oaBitMap[NETDEMO_DEVICE_CLOUD],RGB(1,1,1));

    oaBitMap[NETDEMO_DEVICE_LOCAL_LOGOUT].LoadBitmap(IDB_BMP_DEV_LOCAL_LOGOUT);
    m_oTreeImage.Add(&oaBitMap[NETDEMO_DEVICE_LOCAL_LOGOUT],RGB(1,1,1));

    oaBitMap[NETDEMO_DEVICE_CLOUD_LOGOUT].LoadBitmap(IDB_BMP_DEV_CLOUD_LOGOUT);
    m_oTreeImage.Add(&oaBitMap[NETDEMO_DEVICE_CLOUD_LOGOUT],RGB(1,1,1));
    
    oaBitMap[NETDEMO_CHANNEL_LOGIN].LoadBitmap(IDB_BMP_CHN_LOGIN);
    m_oTreeImage.Add(&oaBitMap[NETDEMO_CHANNEL_LOGIN],RGB(1,1,1));

    oaBitMap[NETDEMO_CHANNEL_LOGOUT].LoadBitmap(IDB_BMP_CHN_LOGOUT);
    m_oTreeImage.Add(&oaBitMap[NETDEMO_CHANNEL_LOGOUT],RGB(1,1,1));

    m_oDeviceTreeList.SetImageList(&m_oTreeImage, LVSIL_NORMAL);
}

void CNetDemoDlg::OnLoginByCloud()
{
    CDlgCloudDev oDlg;
    oDlg.DoModal();

    return;
}

void CNetDemoDlg::OnLoginByLocal()
{
    CDlgAddDevice oDlg;
    oDlg.DoModal();

    return;
}

int CNetDemoDlg::GetCurDeviceIndex()
{
    if (m_dwCurDevIndex < NETDEMO_MAX_DEVICES && m_dwCurDevIndex >= 0)
    {
        return m_dwCurDevIndex;
    }

    return -1;
}

int CNetDemoDlg::GetCurChlIndex()
{

    if ((m_dwCurDevIndex < NETDEMO_MAX_DEVICES) && (m_dwCurDevIndex >= 0) &&
        (m_dwCurChlIndex > 0))
    {
        return m_dwCurChlIndex - 1;
    }

    return 0;
}

LPVOID CNetDemoDlg::GetDevHandle()
{
    INT32 dwCurDevIndex = ga_pMainDlg ->GetCurDeviceIndex();
    if ((dwCurDevIndex < 0) || (dwCurDevIndex > gaDeviceIndex))
    {
        return NULL;
    }

    NETDEMO_DEVICE_INFO stNetDevInfo = gastDeviceInfo[dwCurDevIndex];
    return stNetDevInfo.lpDevHandle;
}

LPVOID CNetDemoDlg::GetActivePlayHandle()
{
    CPlayWnd* pPlayWnd = (CPlayWnd *)m_oScreenPannel.GetActivePage();
    return pPlayWnd->GetSplitHandle();
}

int CNetDemoDlg::GetChlID()
{
    if (NETDEMO_TYPE_CHANNEL == m_dwCurSelectType)
    {
        INT32 dwCurDevIndex = ga_pMainDlg ->GetCurDeviceIndex();
        INT32 dwCurChnIndex = ga_pMainDlg ->GetCurChlIndex();

        if ((dwCurDevIndex < 0) || (dwCurDevIndex > gaDeviceIndex) || (dwCurChnIndex < 0))
        {
            NETDEMO_LOG_ERROR(NULL, "Device or channel index invalid");
            return -1;
        }

        NETDEMO_DEVICE_INFO stNetDevInfo = gastDeviceInfo[dwCurDevIndex];
        return stNetDevInfo.pstChlInfo[dwCurChnIndex].dwChlID;
    }
    else
    {
        return 0;
    }
}

void CNetDemoDlg::OnDeleteDevice()
{
    INT32 dwIndex = GetCurDeviceIndex();
    NETDEMO_DEVICE_INFO &stNetDevInfo = gastDeviceInfo[dwIndex];
    
    if(NULL != stNetDevInfo.lpDevHandle)
    {
        if ( TRUE == Logout(stNetDevInfo))
        {
            NETDEMO_LOG_SUCC(NULL, "Logout");
        }
        else
        {
            NETDEMO_LOG_ERROR(NULL, "Logout");
            return ;
        }
    }

    CHAR szDevInfo[NETDEV_LEN_260] = {0};
    if (NETDEMO_LOGTYPE_LOCAL ==  stNetDevInfo.dwLoginType )
    {
        strncpy(szDevInfo, stNetDevInfo.szIPAddr, sizeof(szDevInfo) - 1);
    }
    else
    {
        strncpy(szDevInfo, stNetDevInfo.stCloudDevinfo.szDevName, sizeof(szDevInfo) - 1);
    }

    memset(&gastDeviceInfo[dwIndex],0,sizeof(gastDeviceInfo[dwIndex]));
    gastDeviceInfo[dwIndex].lpDevHandle = NULL;
    gastDeviceInfo[dwIndex].lpCloudHandle = NULL;
    gastDeviceInfo[dwIndex].dwDeviceIndex = -1;
    gastDeviceInfo[dwIndex].dwMaxChnNum = -1;
    if (NULL != gastDeviceInfo[dwIndex].pstChlInfo)
    {
        for(INT32 i=0;i<gastDeviceInfo[dwIndex].dwMaxChnNum;i++)
        {
            LPNETDEMO_CHANNEL_INFO pstChlInfo = gastDeviceInfo[dwIndex].pstChlInfo;
            if(NULL != pstChlInfo[i].pstBasicInfo)
            {
                delete pstChlInfo[i].pstBasicInfo;
                pstChlInfo[i].pstBasicInfo = NULL;
            }

            if(NULL != pstChlInfo[i].pstNetworkInfo)
            {
                delete pstChlInfo[i].pstNetworkInfo;
                pstChlInfo[i].pstNetworkInfo = NULL;
            }

            if(NULL != pstChlInfo[i].pstVideoStreamInfo)
            {
                delete pstChlInfo[i].pstVideoStreamInfo;
                pstChlInfo[i].pstVideoStreamInfo = NULL;
            }

            if(NULL != pstChlInfo[i].pstImageInfo)
            {
                delete pstChlInfo[i].pstImageInfo;
                pstChlInfo[i].pstImageInfo = NULL;
            }

            if(NULL != pstChlInfo[i].pstOSDInfo)
            {
                delete pstChlInfo[i].pstOSDInfo;
                pstChlInfo[i].pstOSDInfo = NULL;
            }
            if(NULL != pstChlInfo[i].pstIOInfo)
            {
                delete pstChlInfo[i].pstIOInfo;
                pstChlInfo[i].pstIOInfo = NULL;
            }

            if(NULL != pstChlInfo[i].pstPrivacyMaskInfo)
            {
                delete pstChlInfo[i].pstPrivacyMaskInfo;
                pstChlInfo[i].pstPrivacyMaskInfo = NULL;
            }

            if(NULL != pstChlInfo[i].pstMotionAlarmInfo)
            {
                delete pstChlInfo[i].pstMotionAlarmInfo;
                pstChlInfo[i].pstMotionAlarmInfo = NULL;
            }

            if(NULL != pstChlInfo[i].pstTamperAlarmInfo)
            {
                delete pstChlInfo[i].pstTamperAlarmInfo;
               pstChlInfo[i].pstTamperAlarmInfo = NULL;
            }
        }

        delete gastDeviceInfo[dwIndex].pstChlInfo;
        gastDeviceInfo[dwIndex].pstChlInfo = NULL;
    }

    HTREEITEM hDeviceItem = m_oDeviceTreeList.GetSelectedItem();
    m_oDeviceTreeList.DeleteItem(hDeviceItem);
    NETDEMO_LOG_SUCC(szDevInfo, "Delete Device");
    g_SaveDeviceConfig();

    return;
}


void CNetDemoDlg::SetCurWindId(int nCuWinID)
{
    m_dwActiveScreen = nCuWinID;

    return;
}

int CNetDemoDlg::GetCurWinID(void)
{
    CPlayWnd* pWnd = (CPlayWnd*)m_oScreenPannel.GetActivePage();
    if (pWnd && ::IsWindow(pWnd->GetSafeHwnd()))
    {
        return pWnd->GetWinID();
    }

    return NETDEMO_E_FAILED;
}

BOOL CNetDemoDlg::Login(NETDEMO_DEVICE_INFO& stNetDevInfo)
{
    if (NETDEMO_MAX_DEVICES <= gaDeviceIndex )
    {
        NETDEMO_LOG_ERROR(NULL, "Exceeds the maximum number of Devices");
        return TRUE;
    }

    CHAR szDevInfo[NETDEV_LEN_260] = {0};
    if (NETDEMO_LOGTYPE_LOCAL ==  stNetDevInfo.dwLoginType )
    {
        stNetDevInfo.lpDevHandle = NETDEV_Login(stNetDevInfo.szIPAddr, 
                                                stNetDevInfo.dwDevPort,
                                                stNetDevInfo.szDevUserName, 
                                                stNetDevInfo.szPassword, 
                                                &stNetDevInfo.stDevInfo);
        strncpy(szDevInfo, stNetDevInfo.szIPAddr, sizeof(szDevInfo) - 1);
    }
    else
    {
         NETDEV_CLOUD_DEV_LOGIN_EX_S stCloudInfo = {0};
         strncpy(stCloudInfo.szDeviceName, stNetDevInfo.stCloudDevinfo.szDevUserName, sizeof(stCloudInfo.szDeviceName) - 1);
         stNetDevInfo.lpDevHandle = NETDEV_LoginByDynamicEx(stNetDevInfo.lpCloudHandle, &stCloudInfo, &stNetDevInfo.stDevInfo);
         strncpy(szDevInfo, stNetDevInfo.stCloudDevinfo.szDevName, sizeof(szDevInfo) - 1);
    }

    if(NULL == stNetDevInfo.lpDevHandle)
    {
        INT32 dwLastError = NETDEV_GetLastError();
        if(NETDEV_E_USER_NO_SUCH_USER == dwLastError)
        {
            NETDEMO_LOG_ERROR(szDevInfo, "Connection timed out.");
        }
        else
        {
            NETDEMO_LOG_ERROR(szDevInfo, "Please check your username, password and port.");
        }

        return FALSE;
    }

    NETDEV_ALARM_SUB_INFO_S stSubscribeInfo = {0};
    stSubscribeInfo.dwAlarmType = NETDEV_SUBSCRIBE_ALARM_TYPE_COM;
    BOOL bRet = NETDEV_SetAlarmCallBackV2(stNetDevInfo.lpDevHandle, AlarmCallBack_PF, &stSubscribeInfo, (LPVOID)&m_oDlgAlarm);
    if (TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(szDevInfo, "Regisiter alarm call back");
    }
    else
    {
        NETDEMO_LOG_SUCC(szDevInfo, "Regisiter alarm call back");
    }

    bRet = NETDEV_SetExceptionCallBack(ExceptionCallBack_PF,(LPVOID)&m_oDlgAlarm);
    if (TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(szDevInfo, "Regisiter exception call back");
    }
    else
    {
        NETDEMO_LOG_SUCC(szDevInfo, "Regisiter exception call back");
    }

    bRet = NETDEV_SetFaceSnapshotCallBack(stNetDevInfo.lpDevHandle, FaceCallBack_PF,(LPVOID)&m_oDlgAlarm);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(szDevInfo, "Regisiter  FaceSnapshot fail");
    }
    else
    {
        NETDEMO_LOG_SUCC(szDevInfo, "Regisiter  FaceSnapshot suss");
    }

    bRet = NETDEV_SetCarPlateCallBack(stNetDevInfo.lpDevHandle, CarPlateCallBack_PF,(LPVOID)&m_oDlgAlarm);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(szDevInfo, "Regisiter CarPlate fail");
    }else
    {
        NETDEMO_LOG_SUCC(szDevInfo, "Regisiter CarPlate suss");
    }

    NETDEV_VIDEO_CHL_DETAIL_INFO_S pstVideoChlList[256] = {0};
    INT32 dwCount = 256;
    bRet = NETDEV_QueryVideoChlDetailList(stNetDevInfo.lpDevHandle, &dwCount, pstVideoChlList);
    if (TRUE == bRet)
    {
        stNetDevInfo.dwMaxChnNum = dwCount;
        if (NULL != stNetDevInfo.pstChlInfo)
        {
            delete []stNetDevInfo.pstChlInfo;
            stNetDevInfo.pstChlInfo = NULL;
        }

        LPNETDEMO_CHANNEL_INFO pstChannelInfo = new NETDEMO_CHANNEL_INFO[dwCount];
        stNetDevInfo.pstChlInfo = pstChannelInfo;
        for (int i = 0; i < dwCount; i++)
        {
            stNetDevInfo.pstChlInfo[i].stChlDetailInfo = pstVideoChlList[i];
            stNetDevInfo.pstChlInfo[i].dwChlID = pstVideoChlList[i].dwChannelID;
        }
    }

    if ( 0 > stNetDevInfo.dwDeviceIndex)
    {
        stNetDevInfo.dwDeviceIndex = gaDeviceIndex;
    }

    NETDEMO_LOG_SUCC(szDevInfo, "Device Login");

    return TRUE;
}

void CNetDemoDlg::DrawTree(NETDEMO_DEVICE_INFO& stNetDevInfo)
{
    if (stNetDevInfo.dwMaxChnNum < 1)
    {
        return;
    }

    HTREEITEM hChannel = NULL;
    HTREEITEM hDevice;
    if (NETDEMO_LOGTYPE_LOCAL == stNetDevInfo.dwLoginType)
    {
        if (NULL == stNetDevInfo.lpDevHandle)
        {
            hDevice = m_oDeviceTreeList.InsertItem(stNetDevInfo.szIPAddr, NETDEMO_DEVICE_LOCAL_LOGOUT, NETDEMO_DEVICE_LOCAL_LOGOUT,m_hDevtree,GetAfterItem(m_hDevtree));
        }
        else
        {
            hDevice = m_oDeviceTreeList.InsertItem(stNetDevInfo.szIPAddr, NETDEMO_DEVICE_LOCAL, NETDEMO_DEVICE_LOCAL,m_hDevtree,GetAfterItem(m_hDevtree));
        }   
    }
    else
    {
        if (NULL == stNetDevInfo.lpCloudHandle)
        {
            hDevice = m_oDeviceTreeList.InsertItem(stNetDevInfo.stCloudDevinfo.szDevName, NETDEMO_DEVICE_CLOUD_LOGOUT, NETDEMO_DEVICE_CLOUD_LOGOUT,m_hDevtree,GetAfterItem(m_hDevtree));
        }
        else
        {
            hDevice = m_oDeviceTreeList.InsertItem(stNetDevInfo.stCloudDevinfo.szDevName, NETDEMO_DEVICE_CLOUD, NETDEMO_DEVICE_CLOUD,m_hDevtree,GetAfterItem(m_hDevtree));
        }
        
    }

    stNetDevInfo.hTreeItem = hDevice;
    m_oDeviceTreeList.SetItemData(hDevice, (NETDEMO_TYPE_DEVICE*1000) + gaDeviceIndex);
    for (int i = 0; i < stNetDevInfo.dwMaxChnNum; i++)
    {
        char sz[10] = {0};
        itoa(i + 1, sz, 10);
        CString strInfo = CString(_T("Channel ")) + CString(sz);
        if (NETDEV_CHL_STATUS_ONLINE == stNetDevInfo.pstChlInfo[i].stChlDetailInfo.enStatus)
        {
            hChannel = m_oDeviceTreeList.InsertItem(strInfo,NETDEMO_CHANNEL_LOGIN,NETDEMO_CHANNEL_LOGIN,hDevice);
            m_oDeviceTreeList.SetItemData(hChannel, (NETDEMO_TYPE_CHANNEL*1000)+i);
        }
        else
        {
            hChannel = m_oDeviceTreeList.InsertItem(strInfo,NETDEMO_CHANNEL_LOGOUT,NETDEMO_CHANNEL_LOGOUT,hDevice);
            m_oDeviceTreeList.SetItemData(hChannel, (NETDEMO_TYPE_CHANNEL*1000)+i);
        }
    }

    m_oDeviceTreeList.Expand(m_hDevtree,TVE_EXPAND);
    m_oDeviceTreeList.Expand(hDevice,TVE_EXPAND);
    gaDeviceIndex++;

    return;
}

void CNetDemoDlg::UpdateDevState(HTREEITEM& hSelect, NETDEMO_DEVICE_INFO& stDevInfo)
{
    HTREEITEM hChildItem = m_oDeviceTreeList.GetChildItem(hSelect);
    if (NETDEMO_LOGTYPE_LOCAL == stDevInfo.dwLoginType)
    {
        if (NULL == stDevInfo.lpDevHandle)
        {
            m_oDeviceTreeList.SetItemImage(hSelect,NETDEMO_DEVICE_LOCAL_LOGOUT,NETDEMO_DEVICE_LOCAL_LOGOUT);
        }
        else
        {
            m_oDeviceTreeList.SetItemImage(hSelect,NETDEMO_DEVICE_LOCAL,NETDEMO_DEVICE_LOCAL);
        }
    }
    else
    {
        if (NULL == stDevInfo.lpCloudHandle)
        {
            m_oDeviceTreeList.SetItemImage(hSelect,NETDEMO_DEVICE_CLOUD_LOGOUT,NETDEMO_DEVICE_CLOUD_LOGOUT);
        }
        else
        {
            m_oDeviceTreeList.SetItemImage(hSelect,NETDEMO_DEVICE_CLOUD,NETDEMO_DEVICE_CLOUD);
        }
    }

    INT32 i = 0;
    do
    {
        if (NETDEV_CHL_STATUS_ONLINE == stDevInfo.pstChlInfo[i].stChlDetailInfo.enStatus)
        {
            m_oDeviceTreeList.SetItemImage(hChildItem,NETDEMO_CHANNEL_LOGIN,NETDEMO_CHANNEL_LOGIN);
        }
        else
        {
            m_oDeviceTreeList.SetItemImage(hChildItem,NETDEMO_CHANNEL_LOGOUT,NETDEMO_CHANNEL_LOGOUT);
        }

        hChildItem= m_oDeviceTreeList.GetNextItem(hChildItem,TVGN_NEXT );
        i++;

    } while (hChildItem);

    return;
}

void CNetDemoDlg::UpdateSelectDevState()
{
    INT32 dwCurDevIndex = GetCurDeviceIndex();
    HTREEITEM hSelect = m_oDeviceTreeList.GetSelectedItem();
    
    HTREEITEM hChildItem = m_oDeviceTreeList.GetChildItem(hSelect);
    NETDEMO_DEVICE_INFO stDevInfo = gastDeviceInfo[dwCurDevIndex];

    if (NETDEMO_LOGTYPE_LOCAL == stDevInfo.dwLoginType)
    {
        if (NULL == stDevInfo.lpDevHandle)
        {
            m_oDeviceTreeList.SetItemImage(hSelect,NETDEMO_DEVICE_LOCAL_LOGOUT,NETDEMO_DEVICE_LOCAL_LOGOUT);
        }
        else
        {
            m_oDeviceTreeList.SetItemImage(hSelect,NETDEMO_DEVICE_LOCAL,NETDEMO_DEVICE_LOCAL);
        }
    }
    else
    {
        if (NULL == stDevInfo.lpCloudHandle)
        {
            m_oDeviceTreeList.SetItemImage(hSelect,NETDEMO_DEVICE_CLOUD_LOGOUT,NETDEMO_DEVICE_CLOUD_LOGOUT);
        }
        else
        {
            m_oDeviceTreeList.SetItemImage(hSelect,NETDEMO_DEVICE_CLOUD,NETDEMO_DEVICE_CLOUD);
        }
    }

    INT32 i = 0;
    do 
    {
        if (NETDEV_CHL_STATUS_ONLINE == stDevInfo.pstChlInfo[i].stChlDetailInfo.enStatus)
        {
           m_oDeviceTreeList.SetItemImage(hChildItem,NETDEMO_CHANNEL_LOGIN,NETDEMO_CHANNEL_LOGIN);
        }
        else
        {
           m_oDeviceTreeList.SetItemImage(hChildItem,NETDEMO_CHANNEL_LOGOUT,NETDEMO_CHANNEL_LOGOUT);
        }

        hChildItem= m_oDeviceTreeList.GetNextItem(hChildItem,TVGN_NEXT );
        i++;

    } while (hChildItem);

    return;
}

void CNetDemoDlg::UpdateDevState(NETDEMO_DEVICE_INFO stDevInfo)
{
    INT32 dwCurDevIndex = stDevInfo.dwDeviceIndex;
    HTREEITEM hSelect = stDevInfo.hTreeItem;

    HTREEITEM hChildItem = m_oDeviceTreeList.GetChildItem(hSelect);

    if (NETDEMO_LOGTYPE_LOCAL == stDevInfo.dwLoginType)
    {
        if (NULL == stDevInfo.lpDevHandle)
        {
            m_oDeviceTreeList.SetItemImage(hSelect,NETDEMO_DEVICE_LOCAL_LOGOUT,NETDEMO_DEVICE_LOCAL_LOGOUT);
        }
        else
        {
            m_oDeviceTreeList.SetItemImage(hSelect,NETDEMO_DEVICE_LOCAL,NETDEMO_DEVICE_LOCAL);
        }
    }
    else
    {
        if (NULL == stDevInfo.lpCloudHandle)
        {
            m_oDeviceTreeList.SetItemImage(hSelect,NETDEMO_DEVICE_CLOUD_LOGOUT,NETDEMO_DEVICE_CLOUD_LOGOUT);
        }
        else
        {
            m_oDeviceTreeList.SetItemImage(hSelect,NETDEMO_DEVICE_CLOUD,NETDEMO_DEVICE_CLOUD);
        }
    }

    INT32 i = 0;
    do 
    {
        if (NETDEV_CHL_STATUS_ONLINE == stDevInfo.pstChlInfo[i].stChlDetailInfo.enStatus)
        {
            m_oDeviceTreeList.SetItemImage(hChildItem,NETDEMO_CHANNEL_LOGIN,NETDEMO_CHANNEL_LOGIN);
        }
        else
        {
            m_oDeviceTreeList.SetItemImage(hChildItem,NETDEMO_CHANNEL_LOGOUT,NETDEMO_CHANNEL_LOGOUT);
        }

        hChildItem= m_oDeviceTreeList.GetNextItem(hChildItem,TVGN_NEXT );
        i++;

    } while (hChildItem);

    return;
}

BOOL CNetDemoDlg::Logout(NETDEMO_DEVICE_INFO& stNetDevInfo)
{
    if (NULL != stNetDevInfo.lpDevHandle)
    {
        INT32 dwTalkHandle = m_oScreenPannel.GetTalkWinID();
        for (INT32 dwScreenNo = 0; dwScreenNo < NETDEMO_MAX_SCREENNUM; dwScreenNo++)
        {
            CPlayWnd* lpPlayWnd = (CPlayWnd *)m_oScreenPannel.GetPage(dwScreenNo);
            if (NULL !=lpPlayWnd->GetSplitHandle())
            {
                INT32 dwValue = lpPlayWnd->GetDevIndex();
                if (stNetDevInfo.dwDeviceIndex == dwValue) //same device
                {
                    LPVOID lpHandle = lpPlayWnd->GetSplitHandle();
                    if (NULL == lpHandle)
                    {
                        NETDEMO_LOG_ERROR(NULL, "PlayHandle is NULL, Win ID : %d",stNetDevInfo.dwDeviceIndex);
                    }
                    else
                    {
                        BOOL bRet = NETDEV_StopRealPlay(lpHandle);
                        if (!bRet)
                        {
                            NETDEMO_LOG_ERROR(NULL, "Stop Video ");
                            return FALSE;
                        }

                        lpPlayWnd->SetSplitHandle(NULL);
                        lpPlayWnd->SendMessage(WM_VIDEO_REPAINT,1,(LPARAM)this);

                        if (dwTalkHandle == dwScreenNo)
                        {
                            m_oScreenPannel.SetTalkState(FALSE);
                        }
                    }
                }
            }
        }
    }

    if (NETDEMO_MAX_DEVICES <= gaDeviceIndex)
    {
        NETDEMO_LOG_ERROR(NULL, "Exceeds the maximum number of Devices");
        return FALSE;
    }

    if(TRUE == NETDEV_Logout(stNetDevInfo.lpDevHandle))
    {
        stNetDevInfo.lpDevHandle = NULL;
        return TRUE;
    }

    return FALSE;
}

void CNetDemoDlg::OnClose()
{
    if (IDOK != MessageBox("Do you want to exit?", "Info", IDOK))
    {
        return;
    }

    StopCycMonitor();
    CloseAll();

    for (INT32 i = 0; i < NETDEMO_MAX_DEVICES; i++)
    {
        if (NULL != gastDeviceInfo[i].lpDevHandle)
        {
            Logout(gastDeviceInfo[i]);
        }
    }

    NETDEV_Cleanup();
    CDialog::OnClose();

    return;
}

void CNetDemoDlg::RealPlaySelectedDevice()
{
    INT32 dwCurDevIndex = GetCurDeviceIndex();
    INT32 dwCurChnID = GetCurChlIndex();
    INT32 dwCurWinID = GetCurWinID();

    CPlayWnd* pPlayWnd = (CPlayWnd *)m_oScreenPannel.GetPage(dwCurWinID);
    NETDEMO_DEVICE_INFO& stNetDevInfo = gastDeviceInfo[dwCurDevIndex];
    NETDEV_PREVIEWINFO_S stNetInfo = {0};

	if(NETDEV_CHL_STATUS_ONLINE != stNetDevInfo.pstChlInfo[dwCurChnID].stChlDetailInfo.enStatus)
	{
		return;
	}

    stNetInfo.dwChannelID = GetCurChlIndex()+1;
    stNetInfo.hPlayWnd = pPlayWnd->m_hWnd;
    stNetInfo.dwStreamType = gstLocalParam.dwStreamType;
    stNetInfo.dwLinkMode = NETDEV_TRANSPROTOCAL_RTPTCP;

    LPVOID lpHandle = pPlayWnd->GetSplitHandle();
    if(NULL != lpHandle)
    {
        BOOL bRet = NETDEV_StopRealPlay(lpHandle);
        if(FALSE == bRet)
        {
            NETDEMO_LOG_ERROR(NULL, "Stop real play");
        }
    }

    LPVOID Handle = NETDEV_RealPlay(stNetDevInfo.lpDevHandle, &stNetInfo, NULL, 0);
    if (NULL == Handle)
    {
        return;
    }

    HTREEITEM  hItemPos =  m_oDeviceTreeList.GetSelectedItem();
    NETDEMO_SPLITINFO_NODE stDevinfo;
    stDevinfo.hDevTreePos = hItemPos;
    stDevinfo.iHandle = Handle;
    stDevinfo.dwDevIndex = dwCurDevIndex;
    stDevinfo.dwChnIndex = dwCurChnID;
    stDevinfo.emType = NETDEMO_SPLIT_TYPE_REAL_PLAY;
    pPlayWnd->SetSplitInfo(&stDevinfo);

    SendMessage(WM_REALPLAY_SET_AUDIO_PARA, 1, (LPARAM)this);
    SendMessage(WM_CLICK_REALPLAY_WND, 1, (LPARAM)this);

    return;
}

void CNetDemoDlg::StopPlaySelectedDevice()
{
    INT32 dwCurWinID = GetCurWinID();

    CPlayWnd* pPlayWnd = (CPlayWnd *)m_oScreenPannel.GetPage(dwCurWinID);
    LPVOID lpHandle = pPlayWnd->GetSplitHandle();
    if (NULL == lpHandle)
    {
        return;
    }

    BOOL bRet = NETDEV_StopRealPlay(lpHandle);
    if (TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Stop real play");
        return;
    }

    pPlayWnd->SetSplitHandle(NULL);
    NETDEMO_LOG_SUCC(NULL, "Stop play");

    pPlayWnd->SendMessage(WM_VIDEO_REPAINT, 1, (LPARAM)this);

    return;
}


void CNetDemoDlg::OnBnClickedCleanClintlog()
{
    if (IDOK==MessageBox("Clear the log list?","Warning",IDOK))
    {
        ga_pMainDlg->m_oClientLogList.DeleteAllItems();
    }

    return;
}


void CNetDemoDlg::OnBnClickedSaveClinetlog()
{
    CString csFileName;
    CTime time;
    int i = 0;
    CString sTemp;
    CStdioFile oFile;

    int iCount = 0;
    if (gstLocalParam.bAutoSaveLog)
    {
        NETDEMO_LOG_SUCC(NULL, "Save Log");
        return;
    }

    time = CTime::GetCurrentTime();

    iCount = ga_pMainDlg->m_oClientLogList.GetItemCount();

    csFileName.Format("%s\\NetDemoLogFile_%4d%02d%02d_%02d%02d%02d.txt",\
        gstLocalParam.szLogpath, time.GetYear(), time.GetMonth(),\
        time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());

    if (iCount <=  0)
    {
        NETDEMO_LOG_ERROR(NULL, "The log list is empty");
        return;
    }

    if (oFile.Open(csFileName, CFile::modeCreate|CFile::modeWrite) == FALSE)
    {
        char szLan[128] = {0};
        strncpy(szLan, "Create file failed", sizeof(szLan) - 1);
        NETDEMO_LOG_ERROR(NULL, szLan);
        return;
    }

    for (i = iCount-1; i >= 0; i--)
    {
        {
            if (0 == strcmp("Fail", ga_pMainDlg->m_oClientLogList.GetItemText(i, COL_INDEX_LOG_LIST_STATUS).GetBuffer(0)))
            {
                sTemp.Format("[%s] [%s] %s, %s, recode:%s\n", 
                    ga_pMainDlg->m_oClientLogList.GetItemText(i, COL_INDEX_LOG_LIST_TIME).GetBuffer(0),\
                    ga_pMainDlg->m_oClientLogList.GetItemText(i, COL_INDEX_LOG_LIST_DEV_INFO).GetBuffer(0), \
                    ga_pMainDlg->m_oClientLogList.GetItemText(i, COL_INDEX_LOG_LIST_OPERATION).GetBuffer(0), \
                    ga_pMainDlg->m_oClientLogList.GetItemText(i, COL_INDEX_LOG_LIST_STATUS).GetBuffer(0), \
                    ga_pMainDlg->m_oClientLogList.GetItemText(i, COL_INDEX_LOG_LIST_ERRCODE).GetBuffer(0));
            }
            else
            {
                sTemp.Format("[%s] [%s] %s, %s\n", 
                    ga_pMainDlg->m_oClientLogList.GetItemText(i, COL_INDEX_LOG_LIST_TIME).GetBuffer(0),\
                    ga_pMainDlg->m_oClientLogList.GetItemText(i, COL_INDEX_LOG_LIST_DEV_INFO).GetBuffer(0), \
                    ga_pMainDlg->m_oClientLogList.GetItemText(i, COL_INDEX_LOG_LIST_OPERATION).GetBuffer(0), \
                    ga_pMainDlg->m_oClientLogList.GetItemText(i, COL_INDEX_LOG_LIST_STATUS).GetBuffer(0));
            }

        }

        oFile.WriteString(sTemp);
    }

    oFile.Close();
    NETDEMO_LOG_SUCC(NULL, "Save Log");

    return;
}


void CNetDemoDlg::OnDeviceoperLogout()
{
    INT32 dwIndex = GetCurDeviceIndex();
    NETDEMO_DEVICE_INFO &stNetDevInfo = gastDeviceInfo[dwIndex];

    if (TRUE == Logout(stNetDevInfo))
    {
        NETDEMO_LOG_SUCC(NULL, "Device logout");
        
        stNetDevInfo.lpDevHandle = NULL;
        for (int i = 0;i<stNetDevInfo.dwMaxChnNum;i++)
        {
            stNetDevInfo.pstChlInfo[i].stChlDetailInfo.enStatus = NETDEV_CHL_STATUS_OFFLINE;
        }

        HTREEITEM hSelect = m_oDeviceTreeList.GetSelectedItem();
        INT32 dwCurDevIndex = GetCurDeviceIndex();
        NETDEMO_DEVICE_INFO stDevInfo = gastDeviceInfo[dwCurDevIndex];
        UpdateDevState(hSelect, stDevInfo);
    }
    else
    {
        NETDEMO_LOG_ERROR(NULL, "Device logout");
    }

    return ;
}

void CNetDemoDlg::OnDeviceAttribute()
{
    CString strMeg;
    CString strOut;

    INT32 dwIndex = GetCurDeviceIndex();
    PNETDEMO_DEVICE_INFO stNetDev = &gastDeviceInfo[dwIndex];
    if (NETDEMO_LOGTYPE_LOCAL == stNetDev->dwLoginType)
    {
        CDlgLocalDevInfo oDlg;
        oDlg.m_strIP = stNetDev->szIPAddr;
        oDlg.m_dwPort = stNetDev->dwDevPort;
        oDlg.m_strUserName = stNetDev->szDevUserName;
        oDlg.m_strPasswd = stNetDev->szPassword;

        oDlg.m_dwChnNum = stNetDev->stDevInfo.dwChannelNum;

        CString strType = "";
        UINT32 udwSize = sizeof(gastNetDemoDevType) / sizeof(NETDEMO_DEVTYPE_INFO);
        for (INT32 i = 0; i < udwSize; i++)
        {
            if (stNetDev->stDevInfo.dwDevType == gastNetDemoDevType[i].dwDevType)
            {
                strType = gastNetDemoDevType[i].pcTypeInfo;
            }
        }

        oDlg.m_strDevType = strType;
        oDlg.m_dwInputNum = stNetDev->stDevInfo.wAlarmInPortNum;
        oDlg.m_dwOutputNum = stNetDev->stDevInfo.wAlarmOutPortNum;
        if(oDlg.DoModal() == IDOK)
        {
           memset(stNetDev->szDevUserName,0,sizeof(stNetDev->szDevUserName));
           memset(stNetDev->szPassword,0,sizeof(stNetDev->szPassword));

           if (strcmp(stNetDev->szDevUserName,oDlg.m_strUserName.GetBuffer(0)) != 0 ||
               strcmp(stNetDev->szPassword,oDlg.m_strPasswd.GetBuffer(0)) != 0 ||
               (stNetDev->dwDevPort != oDlg.m_dwPort))
           {
               memcpy(stNetDev->szDevUserName,oDlg.m_strUserName.GetBuffer(0),oDlg.m_strUserName.GetLength());
               memcpy(stNetDev->szPassword,oDlg.m_strPasswd.GetBuffer(0),oDlg.m_strPasswd.GetLength());
               stNetDev->dwDevPort = oDlg.m_dwPort;
               g_SaveDeviceConfig();
               OnDeviceoperLogout();
               m_oListDevInfoBuffer.push_back(gastDeviceInfo[dwIndex]);
           }
        }
    }
    else if (NETDEMO_LOGTYPE_CLOUD == stNetDev->dwLoginType)
    {
        CDlgCloudDevInfo oCloudDevInfo;
        oCloudDevInfo.m_strURL = stNetDev->szCloudUrl;
        oCloudDevInfo.m_strUserName = stNetDev->szCloudName;
        oCloudDevInfo.m_strPassword = stNetDev->szCloudPasswd;
        oCloudDevInfo.m_strIP= stNetDev->stCloudDevinfo.szIPAddr;
        oCloudDevInfo.m_dwPort  = stNetDev->stCloudDevinfo.dwDevPort;
        oCloudDevInfo.m_strDevUserName  = stNetDev->stCloudDevinfo.szDevUserName;
        oCloudDevInfo.m_strDevName  = stNetDev->stCloudDevinfo.szDevName;
        oCloudDevInfo.m_strDevModel  = stNetDev->stCloudDevinfo.szDevModel;
        oCloudDevInfo.m_strDevSerialNum  = stNetDev->stCloudDevinfo.szDevSerialNum;
        oCloudDevInfo.m_dwOrgID  = stNetDev->stCloudDevinfo.dwOrgID;
        if(oCloudDevInfo.DoModal() == IDOK)
        {
            memset(stNetDev->szCloudName,0,sizeof(stNetDev->szCloudName));
            memset(stNetDev->szCloudPasswd,0,sizeof(stNetDev->szCloudPasswd));

            memcpy(stNetDev->szCloudName,oCloudDevInfo.m_strUserName.GetBuffer(0),oCloudDevInfo.m_strUserName.GetLength());
            memcpy(stNetDev->szCloudPasswd,oCloudDevInfo.m_strPassword.GetBuffer(0),oCloudDevInfo.m_strPassword.GetLength());
            g_SaveDeviceConfig();
        }
    }

    return;
}

void CNetDemoDlg::OnNMDblclkTreeDeviceList(NMHDR *pNMHDR, LRESULT *pResult)
{
	INT32 dwCurDevIndex = GetCurDeviceIndex();
	INT32 dwCurChnID = GetCurChlIndex();
	INT32 dwCurWinID = GetCurWinID();

	CPlayWnd* pPlayWnd = (CPlayWnd *)m_oScreenPannel.GetPage(dwCurWinID);
	NETDEMO_DEVICE_INFO& stNetDevInfo = gastDeviceInfo[dwCurDevIndex];

	if(NETDEV_CHL_STATUS_ONLINE != stNetDevInfo.pstChlInfo[dwCurChnID].stChlDetailInfo.enStatus)
	{
		return;
	}

    LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
    CPoint pt(0,0);
    GetCursorPos(&pt);

    CRect oRect(0,0,0,0);
    ScreenToClient(&pt);
    GetDlgItem(IDC_TREE_DEVICE_LIST)->GetWindowRect(&oRect);
    ScreenToClient(&oRect);

    pt.x = pt.x-oRect.left;
    pt.y = pt.y-oRect.top;

    UINT uFlags = 0;
    HTREEITEM hSelect = m_oDeviceTreeList.GetSelectedItem();
    if (NULL == hSelect)
    {
        return;
    }
    BOOL bLogined = FALSE;
    DWORD dwNoteData = m_oDeviceTreeList.GetItemData(hSelect);
    INT32 iType = dwNoteData/1000;
    INT32 iIndex = dwNoteData%1000;
    if (NETDEMO_TYPE_DEVICE == iType)
    {
        
    }
    else if (NETDEMO_TYPE_CHANNEL == iType)
    {
        if (NETDEMO_SPLIT1 != m_oPannelPlayControl.GetSplitNum())
        {
            CPlayWnd* pWnd = (CPlayWnd*)m_oScreenPannel.GetActivePage();
            if (NULL != pWnd->GetSplitHandle())
            {
                m_oScreenPannel.SetNextActivePage();
                pWnd = (CPlayWnd*)m_oScreenPannel.GetActivePage();
            }
            if (NULL != pWnd->GetSplitHandle())
            {
                StopPlaySelectedDevice();
            }
        }
        StopPlaySelectedDevice();
        RealPlaySelectedDevice();
    }

    *pResult = 0;
}

void CNetDemoDlg::SnapShotSelectedDevice()
{
    CString strChnID;
    NETDEMO_DEVICE_INFO stDevInfo;
    CPlayWnd* pPlayWnd = (CPlayWnd *)m_oScreenPannel.GetActivePage();

    NETDEMO_SPLITINFO_NODE stPlayInfo;
    pPlayWnd->GetSplitInfo(&stPlayInfo);

    INT32 dwDevIndex = stPlayInfo.dwDevIndex;
    strChnID.Format("%d",stPlayInfo.dwChnIndex + 1);

    stDevInfo = gastDeviceInfo[dwDevIndex];

    CHAR szIPTmp[NETDEV_LEN_260] = {0};
    if (NETDEMO_LOGTYPE_LOCAL == stDevInfo.dwLoginType)
    {
        strncpy(szIPTmp, stDevInfo.szIPAddr, sizeof(szIPTmp) - 1);
        /* if szIPTmp is not IP address but domain name */
        if (('0' > szIPTmp[0]) || ('9' < szIPTmp[0]))
        {
            /* if domain name use https protocol */
            if ('s' == szIPTmp[4])
            {
                strncpy(szIPTmp, &szIPTmp[8], sizeof(szIPTmp) - 1);
            }
            else
            {
                strncpy(szIPTmp, &szIPTmp[7], sizeof(szIPTmp) - 1);
            }
        }

        for (UINT32 i = 0; i < strlen(szIPTmp); i++)
        {
            if ('/' == szIPTmp[i])
            {
                szIPTmp[i] = '-';
                break;
            }
        }
    }
    else if (NETDEMO_LOGTYPE_CLOUD == stDevInfo.dwLoginType)
    {
        strncpy(szIPTmp, stDevInfo.stCloudDevinfo.szIPAddr, sizeof(szIPTmp) - 1);
    }
    else
    {
        NETDEMO_LOG_ERROR(NULL, "Unkown device");
        return;
    }

    CTime oTime = CTime::GetCurrentTime();
    CString strTime = oTime.Format("%y%m%d%H%M%S");

    CString strPath = gstLocalParam.szPictureSavePath;
    strPath += "\\";
    strPath += szIPTmp;
    strPath +="_";
    strPath += strChnID;
    strPath +="_";
    strPath += strTime;

    LPVOID dwHandle = pPlayWnd->GetSplitHandle();
    if (NULL == dwHandle)
    {
        return;
    }

    CHAR szTmpPath[NETDEV_LEN_260] = {0};
    MBToUTF8(strPath.GetBuffer(0), szTmpPath, sizeof(szTmpPath) - 1);
    BOOL bRet = NETDEV_CapturePicture(dwHandle, szTmpPath, NETDEV_PICTURE_BMP);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Get capture, Path: %s", strPath.GetBuffer(0));
    }
    else
    {
        NETDEMO_LOG_SUCC(NULL, "Get capture, Path: %s", strPath.GetBuffer(0));
    }

    return;
}

void CNetDemoDlg::StartLocalRecod()
{
    CString strChnID;
    NETDEMO_DEVICE_INFO stDevInfo;
    CPlayWnd* pPlayWnd = (CPlayWnd *)m_oScreenPannel.GetActivePage();

    NETDEMO_SPLITINFO_NODE stPlayInfo;
    pPlayWnd->GetSplitInfo(&stPlayInfo);

    INT32 dwDevIndex = stPlayInfo.dwDevIndex;
    strChnID.Format("%d",stPlayInfo.dwChnIndex + 1);

    stDevInfo = gastDeviceInfo[dwDevIndex];

    CHAR szIPTmp[NETDEV_LEN_260] = {0};
    if (NETDEMO_LOGTYPE_LOCAL == stDevInfo.dwLoginType)
    {
        strncpy(szIPTmp, stDevInfo.szIPAddr, sizeof(szIPTmp) - 1);
        /* if szIPTmp is not IP address but domain name */
        if (('0' > szIPTmp[0]) || ('9' < szIPTmp[0]))
        {
            /* if domain name use https protocol */
            if ('s' == szIPTmp[4])
            {
                strncpy(szIPTmp, &szIPTmp[8], sizeof(szIPTmp) - 1);
            }
            else
            {
                strncpy(szIPTmp, &szIPTmp[7], sizeof(szIPTmp) - 1);
            }
        }

        for (UINT32 i = 0; i < strlen(szIPTmp); i++)
        {
            if ('/' == szIPTmp[i])
            {
                szIPTmp[i] = '-';
                break;
            }
        }
    }
    else if (NETDEMO_LOGTYPE_CLOUD == stDevInfo.dwLoginType)
    {
        strncpy(szIPTmp, stDevInfo.stCloudDevinfo.szIPAddr, sizeof(szIPTmp) - 1);
    }
    else
    {
        NETDEMO_LOG_ERROR(NULL, "Unkown device");
        return;
    }

    CTime cTime = CTime::GetCurrentTime();
    CString strTime = cTime.Format("%y%m%d%H%M%S");

    CString strPath = gstLocalParam.szLocalRecordPath;
    strPath += "\\";
    strPath += szIPTmp;
    strPath +="_";
    strPath += strChnID;
    strPath +="_";
    strPath += strTime;

    LPVOID dwHandle = pPlayWnd->GetSplitHandle();
    if (NULL == dwHandle)
    {
        NETDEMO_LOG_ERROR(NULL, "Save Local Record, Handle is NULL");
        return;
    }
    if (TRUE == pPlayWnd->GetLocalRecordState())
    {
        BOOL bRet = NETDEV_StopSaveRealData((LPVOID)dwHandle);
        if(TRUE != bRet)
        {
            NETDEMO_LOG_ERROR(NULL, "Stop record");
            return;
        }

        pPlayWnd->SetLocalRecordState(FALSE);
        m_oPannelPlayControl.UpdateRecordTxt("Record");
        NETDEMO_LOG_SUCC(NULL, "Stop record");
    }
    else
    {
        CHAR szTmpPath[NETDEV_LEN_260] = {0};
        MBToUTF8(strPath.GetBuffer(0), szTmpPath, sizeof(szTmpPath) - 1);
        BOOL bRet = NETDEV_SaveRealData(dwHandle, szTmpPath, NETDEV_MEDIA_FILE_MP4);
        if(TRUE != bRet)
        {
            NETDEMO_LOG_ERROR(NULL, "Start record");
        }

        m_oPannelPlayControl.UpdateRecordTxt("Stop");
        pPlayWnd->SetLocalRecordState(TRUE);
        NETDEMO_LOG_SUCC(NULL, "Start record, Path: %s", strPath.GetBuffer(0));
    }

    return;
}

LRESULT CNetDemoDlg::OnClickPlayWindow(WPARAM wParam, LPARAM lParam)
{
    CPlayWnd* pPlayWnd = (CPlayWnd *)m_oScreenPannel.GetActivePage();
    LPVOID lpHandle = pPlayWnd->GetSplitHandle();
    if (TRUE == pPlayWnd->GetLocalRecordState())
    {
        m_oPannelPlayControl.UpdateRecordTxt("Stop");
    }
    else
    {
        m_oPannelPlayControl.UpdateRecordTxt("Record");
    }

    if (NULL == lpHandle)
    {
        m_oPannelPlayControl.EnableWindowMicBtn(FALSE);
        m_oPannelPlayControl.EnableWindowSoundBtn(FALSE);
    }
    else
    {
        HTREEITEM HTreeItem = pPlayWnd->GetDevTreePos();
        if (NULL == HTreeItem)
        {
            m_dwCurChlIndex = 0;
        }
        else
        {
            m_oDeviceTreeList.Select(HTreeItem,TVGN_CARET);
        }

        INT32 dwCurMicVolume = pPlayWnd->GetMicVolume();
        INT32 dwCurSoundVolume= pPlayWnd->GetSoundVolume();

        if (TRUE == pPlayWnd->GetMicState())
        {
            m_oPannelPlayControl.SetMicState(TRUE);
            m_oPannelPlayControl.EnableWindowMicSli(TRUE);
        }
        else
        {
            m_oPannelPlayControl.SetMicState(FALSE);
            m_oPannelPlayControl.EnableWindowMicSli(FALSE);
        }
        
        if (TRUE == pPlayWnd->GetSoundState())
        {
            m_oPannelPlayControl.SetSoundState(TRUE);
            m_oPannelPlayControl.EnableWindowSoundSli(TRUE);
        }
        else
        {
            m_oPannelPlayControl.SetSoundState(FALSE);
            m_oPannelPlayControl.EnableWindowSoundSli(FALSE);
        }
        
        m_oPannelPlayControl.SetMicVolume(dwCurMicVolume);
        m_oPannelPlayControl.SetSoundVolume(dwCurSoundVolume);
        m_oPannelPlayControl.EnableWindowMicBtn(TRUE);
        m_oPannelPlayControl.EnableWindowSoundBtn(TRUE);
    }

    return NULL;
}

LRESULT CNetDemoDlg::OnSetDevAudioPara(WPARAM wParam, LPARAM lParam)
{
    CPlayWnd* pPlayWnd = (CPlayWnd *)m_oScreenPannel.GetActivePage();
    LPVOID Handle = GetActivePlayHandle();
    if (TRUE == SetNetSDKSoundVolume(NETDEV_AUDIO_SOUND_MAX_VALUE))
    {
        pPlayWnd->SetSoundVolume(NETDEV_AUDIO_SOUND_MAX_VALUE);
        pPlayWnd->SetSoundState(TRUE);
    }
    else
    {
        pPlayWnd->SetSoundVolume(0);
        pPlayWnd->SetSoundState(FALSE);
    }
    if (TRUE == SetNetSDKMicVolume(NETDEV_MIC_SOUND_MAX_VALUE))
    {
        pPlayWnd->SetMicVolume(NETDEV_MIC_SOUND_MAX_VALUE);
        pPlayWnd->SetMicState(TRUE);
    }
    else
    {
        pPlayWnd->SetMicVolume(0);
        pPlayWnd->SetMicState(FALSE);
    }

    return NULL;
}

void CNetDemoDlg::MakeKeyFrame(INT32 dwDevIndex, INT32 dwChnIndex)
{
    NETDEMO_DEVICE_INFO stDevInfo = gastDeviceInfo[dwDevIndex];
    INT32 dwBytesReturned = 0;
    NETDEV_VIDEO_STREAM_INFO_S stStreamInfo;

    memset(&stStreamInfo, 0, sizeof(stStreamInfo));
    stStreamInfo.enStreamType = NETDEV_LIVE_STREAM_INDEX_MAIN;

    if (TRUE == NETDEV_GetDevConfig(stDevInfo.lpDevHandle, dwChnIndex, NETDEV_GET_STREAMCFG, &stStreamInfo, sizeof(NETDEV_VIDEO_STREAM_INFO_S), &dwBytesReturned))
    {
        NETDEMO_LOG_SUCC(NULL, "Get Video Stream Info");
    }
    else
    {
        NETDEMO_LOG_ERROR(NULL, "Get Video Stream Info");
        return;
    }

    if (TRUE == NETDEV_MakeKeyFrame(stDevInfo.lpDevHandle,dwChnIndex,stStreamInfo.enStreamType))
    {
        NETDEMO_LOG_SUCC(NULL, "Make keyframe");
    }
    else
    {
        NETDEMO_LOG_ERROR(NULL, "Make keyframe");
    }

    return;
}


void CNetDemoDlg::SetNetPlayMode(NETDEV_PICTURE_FLUENCY_E type)
{
    CPlayWnd* pPlayWnd = (CPlayWnd *)m_oScreenPannel.GetActivePage();
    LPVOID lpHandle = pPlayWnd->GetSplitHandle();
    if (NULL == lpHandle)
    {
        NETDEMO_LOG_ERROR(NULL, "Set picture fluency, Handle is NULL");
        return;
    }

    if (TRUE == NETDEV_SetPictureFluency(lpHandle,type))
    {
        NETDEMO_LOG_SUCC(NULL, "Set picture fluency, type : %d ",type);
    }
    else
    {
        NETDEMO_LOG_ERROR(NULL, "Set picture fluency, type : %d ",type);
        return;
    }

    return;
}

BOOL CNetDemoDlg::StartTwoWayAudio()
{
    LPVOID lpHandle = GetDevHandle();
    INT32 dwChannel=  GetChlID();
    if (NULL == lpHandle)
    {
        NETDEMO_LOG_ERROR(NULL, "Start two way audio, Handle is NULL");
        return FALSE;
    }

    LPVOID lpTalkHandle = NETDEV_StartVoiceCom(lpHandle, dwChannel, NULL, NULL);
    if(NULL ==  lpTalkHandle)
    {
        NETDEMO_LOG_ERROR(NULL, "Start two way audio");
    }
    else
    {
        m_lpTalkID = lpTalkHandle;
        NETDEMO_LOG_SUCC(NULL, "Start two way audio");
        return TRUE;
    }

    return FALSE;
}

BOOL CNetDemoDlg::StopTalk()
{
    if (NULL == m_lpTalkID)
    {
        NETDEMO_LOG_ERROR(NULL, "Stop two way audio, Handle is NULL");
        return FALSE;
    }
    BOOL bRet = NETDEV_StopVoiceCom(m_lpTalkID);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Stop two way audio");
        return FALSE;
    }
    else
    {
        m_lpTalkID = NULL;
        NETDEMO_LOG_SUCC(NULL, "Stop two way audio");
        return TRUE;
    }

    return FALSE;
}


BOOL CNetDemoDlg::ControlMicVolume()
{
    CPlayWnd* pPlayWnd = (CPlayWnd *)m_oScreenPannel.GetActivePage();

    LPVOID lpPlayHandle = GetActivePlayHandle();
    if(NULL == lpPlayHandle)
    {
        NETDEMO_LOG_ERROR(NULL, "Control Sound, Handle is NULL");
        return FALSE;
    }

    if (TRUE == pPlayWnd->GetMicState())
    {
        BOOL bRet = NETDEV_CloseMic(lpPlayHandle);
        if(TRUE != bRet)
        {
            NETDEMO_LOG_ERROR(NULL, "Close Mic");
            return FALSE;
        }

        m_oPannelPlayControl.SetMicState(FALSE);
        pPlayWnd->SetMicState(FALSE);
        m_oPannelPlayControl.EnableWindowMicSli(FALSE);

        NETDEMO_LOG_SUCC(NULL, "Close Mic");
    }
    else
    {
        BOOL bRet = NETDEV_OpenMic(lpPlayHandle);
        if(TRUE != bRet)
        {
            NETDEMO_LOG_ERROR(NULL, "Open Mic");
            return FALSE;
        }
        m_oPannelPlayControl.SetMicState(TRUE);
        pPlayWnd->SetMicState(TRUE);
        m_oPannelPlayControl.EnableWindowMicSli(TRUE);
        NETDEMO_LOG_SUCC(NULL, "Open Mic");
    }

    return TRUE;
}

BOOL CNetDemoDlg::ControlSoundVolume()
{
    CPlayWnd* pPlayWnd = (CPlayWnd *)m_oScreenPannel.GetActivePage();
    LPVOID lpPlayHandle = GetActivePlayHandle();

    if(NULL == lpPlayHandle)
    {
        NETDEMO_LOG_ERROR(NULL, "Control Sound, Handle is NULL");
        return FALSE;
    }
    if (TRUE == pPlayWnd->GetSoundState())
    {
        BOOL bRet = NETDEV_CloseSound(lpPlayHandle);
        if(TRUE != bRet)
        {
            NETDEMO_LOG_ERROR(NULL, "Close Sound");
            return FALSE;
        }
        m_oPannelPlayControl.SetSoundState(FALSE);
        m_oPannelPlayControl.EnableWindowSoundSli(FALSE);
        pPlayWnd->SetSoundState(FALSE);
        NETDEMO_LOG_SUCC(NULL, "Close Sound");
    }
    else
    {
        BOOL bRet = NETDEV_OpenSound(lpPlayHandle);
        if(TRUE != bRet)
        {
            NETDEMO_LOG_ERROR(NULL, "Open Sound");
            return FALSE;
        }
        m_oPannelPlayControl.SetSoundState(TRUE);
        m_oPannelPlayControl.SetSoundState(TRUE);
        m_oPannelPlayControl.EnableWindowSoundSli(TRUE);
        pPlayWnd->SetSoundState(TRUE);
        NETDEMO_LOG_SUCC(NULL, "Open Sound");
    }

    return TRUE;
}

INT32 CNetDemoDlg::GetNetSDKMicVolume()
{
    LPVOID lpHandle = GetActivePlayHandle();
    if(NULL == lpHandle)
    {
        return 0;
    }

    INT32 dwVolume = 0;
    BOOL bRet = NETDEV_GetMicVolume(lpHandle, &dwVolume);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Get Mic Volume");
        return 0;
    }

    NETDEMO_LOG_SUCC(NULL, "Get Mic Volume, volume : %d", dwVolume);

    return dwVolume;
}

bool  CNetDemoDlg::SetNetSDKMicVolume(INT32 dwVolume)
{
    LPVOID lpHandle = GetActivePlayHandle();
    if(NULL == lpHandle)
    {
        NETDEMO_LOG_ERROR(NULL, "Control Mic Volume, Handle is NULL");
        return FALSE;
    }

    BOOL bRet = NETDEV_MicVolumeControl(lpHandle, dwVolume);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Control Mic Volume");
        return FALSE;
    }

    NETDEMO_LOG_SUCC(NULL, "Control Mic Succ,Volume:%d",dwVolume);

    return TRUE;
}

bool  CNetDemoDlg::SetNetSDKSoundVolume(INT32 dwVolume)
{
    LPVOID lpHandle = GetActivePlayHandle();
    if(NULL == lpHandle)
    {
        NETDEMO_LOG_ERROR(NULL, "Control Sound Volume, Handle is NULL");
        return FALSE;
    }
    if (TRUE == NETDEV_OpenSound(lpHandle))
    {   
        BOOL bRet = NETDEV_SoundVolumeControl(lpHandle, dwVolume);
        if(TRUE != bRet)
        {
            NETDEMO_LOG_ERROR(NULL, "Control Sound Volume ");
            return FALSE;
        }
        NETDEMO_LOG_SUCC(NULL, "Control Sound Succ, Volume : %d", dwVolume);
        return TRUE;
    }

    return FALSE;
}

INT32 CNetDemoDlg::GetNetSDKSoundVolume()
{
    INT32 dwVolume = -1;
    LPVOID lpHandle = GetActivePlayHandle();
    if(NULL == lpHandle)
    {
        NETDEMO_LOG_ERROR(NULL, "Get Sound Volume.");
        return 0;
    }

    BOOL bRet = NETDEV_GetSoundVolume(lpHandle, &dwVolume);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Get Sound Volume.");
        return -1;
    }

    NETDEMO_LOG_SUCC(NULL, "Get Sound Volume, volume : %d", dwVolume);

    return dwVolume;
}


void CNetDemoDlg::SetMultiScreen(INT32 dwSplit)
{
    if (NETDEMO_SPLIT1 == dwSplit)
    {
        m_oScreenPannel.SetMultiScreen(FALSE);
        return ;
    }
    else
    {
        m_oScreenPannel.SetMultiScreen(TRUE);
        m_oScreenPannel.SetShowPlayWin(dwSplit, m_dwActiveScreen);
    }
    m_dwSplitNum = dwSplit;
    return;
}

void CNetDemoDlg::StopCycMonitor()
{
    m_bCycleMonitor = FALSE;
}

void CNetDemoDlg::StartCycleMonitor()
{
    if (TRUE !=m_bStopCycFlag)
    {
        m_bStopCycFlag = TRUE;
        DWORD dwThreadId = 0;
        m_hCycleThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(CycleMonitorThread), this, 0, &dwThreadId);
    }

    m_bCycleMonitor = TRUE;

    return;
}


void CNetDemoDlg::CycMonitorControl(INT32 dwWinID)
{
    CPlayWnd* pPlayWnd = (CPlayWnd *)m_oScreenPannel.GetPage(dwWinID);
    LPVOID lpPlayHandle = pPlayWnd->GetSplitHandle();
    if (NULL != lpPlayHandle)
    {
        BOOL bRet = NETDEV_StopRealPlay(lpPlayHandle);
        if (lpPlayHandle== NULL)
        {
            NETDEMO_LOG_ERROR(NULL, "Stop real play");
            return;
        }

        pPlayWnd->SetSplitHandle(NULL);
        pPlayWnd->SendMessage(WM_VIDEO_REPAINT,1,(LPARAM)this);
    }

    PNETDEMO_CYCLE_WINDOW_INFO stCycInfo = &m_stCycleInfo.szCycleWinInfo[dwWinID];
    if (stCycInfo->dwCurDevPlayIndex >= stCycInfo->dwDevCount)
    {
        stCycInfo->dwCurDevPlayIndex = 0;
    }

    INT32 dwCurPlayIndex = stCycInfo->dwCurDevPlayIndex;
    INT32 dwGaDevindex = stCycInfo->szCycleDevInfo[dwCurPlayIndex].dwGaIndex;

    NETDEV_PREVIEWINFO_S stNetInfo = {0};
    stNetInfo.hPlayWnd = pPlayWnd->m_hWnd;
    stNetInfo.dwStreamType = NETDEV_LIVE_STREAM_INDEX_MAIN;
    stNetInfo.dwLinkMode = NETDEV_TRANSPROTOCAL_RTPTCP;
    stNetInfo.dwChannelID = stCycInfo->szCycleDevInfo[dwCurPlayIndex].dwChnID;

    LPVOID lpDevHandle = gastDeviceInfo[dwGaDevindex].lpDevHandle;
    if(NULL != lpDevHandle)
    {
        LPVOID lpPlayHandle = NETDEV_RealPlay(lpDevHandle, &stNetInfo, NULL, 0);
        if (lpPlayHandle != NULL)
        {
            pPlayWnd->SetSplitHandle(lpPlayHandle);
            pPlayWnd->SetSplitType(NETDEMO_SPLIT_TYPE_CYCLEMONITOR);
        }
    }

    stCycInfo->dwCurDevPlayIndex++;

    return;
}

void CNetDemoDlg::CloseAll()
{
    for (INT32 dwScreenNo = 0; dwScreenNo < NETDEMO_MAX_SCREENNUM; dwScreenNo++)
    {
        CPlayWnd* pPlayWnd = (CPlayWnd *)m_oScreenPannel.GetPage(dwScreenNo);
        LPVOID lpPlayHandle = pPlayWnd->GetSplitHandle();
        if (NULL != lpPlayHandle)
        {
            BOOL bRet = NETDEV_StopRealPlay(lpPlayHandle);
            if (lpPlayHandle== NULL)
            {
                NETDEMO_LOG_ERROR(NULL, "Stop real play");
                return;
            }

            pPlayWnd->SetSplitHandle(NULL);
            pPlayWnd->SendMessage(WM_VIDEO_REPAINT,1,(LPARAM)this);
        }
    }

    return;
}


void  CNetDemoDlg::StopVideoByIndex(INT32 dwIndex)
{
    CPlayWnd* pPlayWnd = (CPlayWnd *)m_oScreenPannel.GetPage(dwIndex);
    LPVOID lpPlayHandle = pPlayWnd->GetSplitHandle();
    if (NULL != lpPlayHandle)
    {
        BOOL bRet = NETDEV_StopRealPlay(lpPlayHandle);
        if (lpPlayHandle== NULL)
        {
            NETDEMO_LOG_ERROR(NULL, "Close video play");
            return;
        }

        pPlayWnd->SetSplitHandle(NULL);
        pPlayWnd->SendMessage(WM_VIDEO_REPAINT,1,(LPARAM)this);
    }

    return;
}

BOOL CNetDemoDlg::GetPlayWndDevIndex(LPVOID pPlayHandle, INT32& dwDevIndex)
{
    for (INT32 screenNo = 0; screenNo < NETDEMO_MAX_SCREENNUM; screenNo++)
    {
        CPlayWnd* pPlayWnd = (CPlayWnd *)m_oScreenPannel.GetPage(screenNo);
        LPVOID lpPlayHandle = pPlayWnd->GetSplitHandle();
        if (pPlayHandle == lpPlayHandle)
        {
            dwDevIndex = pPlayWnd->GetDevIndex();
            return TRUE;
        }
    }

    return FALSE;
}


void CNetDemoDlg::SetSliderSoundVolume(INT32 dwValue)
{
    CPlayWnd* pPlayWnd = (CPlayWnd *)m_oScreenPannel.GetActivePage();
    if (TRUE == SetNetSDKSoundVolume(dwValue))
    {
        pPlayWnd->SetSoundVolume(dwValue);
    }

    return;
}

void CNetDemoDlg::SetSliderMicVolume(INT32 dwValue)
{
    CPlayWnd* pPlayWnd = (CPlayWnd *)m_oScreenPannel.GetActivePage();
    if (TRUE == SetNetSDKMicVolume(dwValue))
    {
        pPlayWnd->SetMicVolume(dwValue);
    }

    return;
}

BOOL CNetDemoDlg::IsExistInThreadBuffer(NETDEMO_DEVICE_INFO stNetDevInfo)
{
    std::list<NETDEMO_DEVICE_INFO>::iterator it = m_oListDevInfoBuffer.begin();
    for (it;it!=m_oListDevInfoBuffer.end();it++)
    {
        if (NETDEMO_LOGTYPE_LOCAL == (*it).dwLoginType)
        {
            if (strcmp((*it).szIPAddr,stNetDevInfo.szIPAddr)==0 &&
                ((*it).dwDevPort == stNetDevInfo.dwDevPort))
            {
                return TRUE;
            }
        }
        else
        {
            if ((strcmp((*it).szCloudUrl,stNetDevInfo.szCloudUrl)==0) && 
                (strcmp((*it).stCloudDevinfo.szDevSerialNum,stNetDevInfo.stCloudDevinfo.szDevSerialNum)==0))
            {
                return TRUE;
            }
        }

    }

    return FALSE;
}

BOOL CNetDemoDlg::IsExistInDevBuffer(NETDEMO_DEVICE_INFO stNetDevInfo)
{
    for (INT32 i =0;i <gaDeviceIndex;i++)
    {
        NETDEMO_DEVICE_INFO stSrcDevInfo = gastDeviceInfo[i];
        if (NETDEMO_LOGTYPE_LOCAL == stSrcDevInfo.dwLoginType)
        {
            if (strcmp(stSrcDevInfo.szIPAddr,stNetDevInfo.szIPAddr)==0)
            {
                return TRUE;
            }
        }
        else
        {
            if ((strcmp(stSrcDevInfo.szCloudUrl,stNetDevInfo.szCloudUrl)==0) && 
                (strcmp(stSrcDevInfo.stCloudDevinfo.szDevSerialNum,stNetDevInfo.stCloudDevinfo.szDevSerialNum)==0))
            {
                return TRUE;
            }
        }
    }

    return FALSE;
}

void CNetDemoDlg::OnLvnColumnclickListAllLog(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

    m_bClientLogListEnlarge = (!m_bClientLogListEnlarge);
    EnlargeList(m_bClientLogListEnlarge);
    *pResult = 0;
}


void CNetDemoDlg::EnlargeList(BOOL bEnargeList)
{
    CRect rc(0,0,0,0);
    m_oClientLogList.GetWindowRect(&rc);
    ScreenToClient(&rc);

    if (TRUE == bEnargeList)
    {
        rc.top-=METDEMO_CLINETLIST_ENLARGE_HIGH;//move top upper, stretch
        m_oClientLogList.MoveWindow(&rc);
        if (m_dwMainMenuType == NETDEMO_MANU_INDEX_LIVEVIEW)
        {
            m_oScreenPannel.ShowWindow(SW_HIDE);
            m_oPtzPannel.ShowWindow(SW_HIDE);
            m_oPannelPlayControl.ShowWindow(SW_HIDE);
        }
        else if (m_dwMainMenuType == NETDEMO_MANU_INDEX_PLAYBACK)
        {
            m_oDlgPlayback.ShowWindow(SW_HIDE);    
        }
        else if(m_dwMainMenuType == NETDEMO_MANU_INDEX_CFG)
        {
            m_oDlgCfg.ShowWindow(SW_HIDE);
        }
        else if (m_dwMainMenuType == NETDEMO_MANU_INDEX_ALARMRECORDS)
        {
            m_oDlgAlarm.ShowWindow(SW_HIDE);
        }
        else if (m_dwMainMenuType == NETDEMO_MANU_INDEX_VCA)
        {
            m_oDlgVCA.ShowWindow(SW_HIDE);
        }
        else if (m_dwMainMenuType == NETDEMO_MANU_INDEX_MAINTAIN)
        {
            m_oDlgMaintain.ShowWindow(SW_HIDE);
        }

        GetDlgItem(IDC_SCREEN_WINDOW)->ShowWindow(FALSE);
    }
    else
    {
        rc.top+=METDEMO_CLINETLIST_ENLARGE_HIGH;//move top upper, stretch
        m_oClientLogList.MoveWindow(&rc);
        if (m_dwMainMenuType == NETDEMO_MANU_INDEX_LIVEVIEW)
        {
            m_oScreenPannel.ShowWindow(SW_SHOW);
            m_oPtzPannel.ShowWindow(SW_SHOW);
            m_oPannelPlayControl.ShowWindow(SW_SHOW);
        }
        else if (m_dwMainMenuType == NETDEMO_MANU_INDEX_PLAYBACK)
        {
            m_oDlgPlayback.ShowWindow(SW_SHOW);    
        }
        else if(m_dwMainMenuType == NETDEMO_MANU_INDEX_CFG)
        {
            m_oDlgCfg.ShowWindow(SW_SHOW);
        }
        else if (m_dwMainMenuType == NETDEMO_MANU_INDEX_ALARMRECORDS)
        {
            m_oDlgAlarm.ShowWindow(SW_SHOW);
        }
        else if (m_dwMainMenuType == NETDEMO_MANU_INDEX_VCA)
        {
            m_oDlgVCA.ShowWindow(SW_SHOW);
        }
        else if (m_dwMainMenuType == NETDEMO_MANU_INDEX_MAINTAIN)
        {
            m_oDlgMaintain.ShowWindow(SW_SHOW);
        }
        else if (m_dwMainMenuType == NETDEMO_MANU_INDEX_USERCFG)
        {
            m_oDlgUserCfg.ShowWindow(SW_SHOW);
        }

        GetDlgItem(IDC_SCREEN_WINDOW)->ShowWindow(TRUE);
    }

    return;
}

BOOL CNetDemoDlg::PreTranslateMessage(MSG* pMsg) 
{
    // TODO: Add your specialized code here and/or call the base class
    if (pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_ESCAPE)
    {
        if (TRUE == m_oScreenPannel.GetFullScreen())
        {
            m_oScreenPannel.SetFullScreen(FALSE);
        }
        return TRUE;
    }
    if (pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN)
    {
        return TRUE; 
    }
    else
    {
        return CDialog::PreTranslateMessage(pMsg);
    }
}

CString CNetDemoDlg::GetDevIPByDevHandle(LPVOID lpDevHandle)
{
    CString str = "Unknow IP Address";
    for (INT32 i = 0; i < NETDEMO_MAX_DEVICES;i++)
    {
        if (lpDevHandle  == gastDeviceInfo[i].lpDevHandle)
        {
            return gastDeviceInfo[i].szIPAddr;
        }
    }

    return str;
}

void CNetDemoDlg::GetCameraInfo()
{
    LPVOID lpHandle = GetActivePlayHandle();
    if(NULL == lpHandle)
    {
        NETDEMO_LOG_ERROR(NULL, "Get Sound Volume.");
        return ;
    }

    CString strTemp;
    CString strOut;

    /* Bit rate */
    INT32 ulBitRate = 0;
    BOOL bRet = NETDEV_GetBitRate(lpHandle, &ulBitRate);
    if(TRUE != bRet)
    {
        strTemp.Format("Get Bit Rate failed.\n");
    }  
    else
    {
        strTemp.Format("Bit Rate         \t %d \n", ulBitRate);
    }
    strOut += strTemp;

    /* Frame rate */
    INT32 ulFrameRate = 0;
    bRet= NETDEV_GetFrameRate(lpHandle, &ulFrameRate);
    if(TRUE != bRet)
    {
        strTemp.Format("Get Frame Rate failed\n");
    }  
    else
    {
        strTemp.Format("Frame Rate       \t %d\n", ulFrameRate);
    }
    strOut += strTemp;


    /* Encode format */
    INT32 dwFormat = 0;
    bRet = NETDEV_GetVideoEncodeFmt(lpHandle, &dwFormat);
    if(TRUE != bRet)
    {
        strTemp.Format("Get Format failed.\n");
    }  
    else
    {
        strTemp.Format("Format           \t %d\n", dwFormat);
    }
    strOut += strTemp;

    /* Resolution */
    INT32 dwWidth = 0;
    INT32 dwHeight = 0;
    bRet = NETDEV_GetResolution(lpHandle,&dwWidth, &dwHeight);
    if(TRUE != bRet)
    {
        strTemp.Format("Get Resolution failed.\n");
    }  
    else
    {
        strTemp.Format("Resolution        \t %d * %d\n",dwWidth, dwHeight);
    }
    strOut += strTemp;

    /* Lost packet rate */
    INT32 ulRecvPktNum = 0;
    INT32 ulLostPktNum = 0;
    bRet = NETDEV_GetLostPacketRate(lpHandle,&ulRecvPktNum, &ulLostPktNum);
    if(TRUE != bRet)
    {
        strTemp.Format("Get Packet Rate failed\n");
    }  
    else
    {
        strTemp.Format("Lost Packet Rate  \t (%d/%d)\n", ulLostPktNum, ulRecvPktNum);
    }
    strOut += strTemp;

    MessageBox(strOut, "Camera Info");
}

void CNetDemoDlg::NETSDK_SetActiveWndDZ(CRect oRect,BOOL bAction)
{
    LPVOID lpHandle = GetActivePlayHandle();
    if(NULL == lpHandle)
    {
        return ;
    }

    NETDEV_RECT_S stRect;
    memset(&stRect, 0, sizeof(NETDEV_RECT_S));

    if (NULL != oRect)
    {
        stRect.dwLeft = oRect.left;
        stRect.dwRight = oRect.right;
        stRect.dwTop = oRect.top;
        stRect.dwBottom = oRect.bottom;
    }
    BOOL bRet = FALSE;
    if (TRUE == bAction)
    {
        bRet = NETDEV_SetDigitalZoom(lpHandle, m_hWnd, &stRect);
    }
    else
    {
        bRet = NETDEV_SetDigitalZoom(lpHandle, m_hWnd, NULL);
    }
    if (TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Set digital zoom");
        return;
    }

    NETDEMO_LOG_SUCC(NULL, "Set digital zoom");

    return;
}

void CNetDemoDlg::NETSDK_SetActive3DPostion(CRect oRect)
{
    LPVOID lpDevHandle = GetDevHandle();
    int ChnID = GetChlID();
    if(NULL == lpDevHandle)
    {
        return ;
    }
    
    NETDEV_PTZ_OPERATEAREA_S stPtzAreaOperate;
    memset(&stPtzAreaOperate, 0, sizeof(NETDEV_PTZ_OPERATEAREA_S));

    /* Take the upper left corner of the window for playing as a start point, and the parameter value range from 0 to 10000. */
    stPtzAreaOperate.dwBeginPointX = oRect.left;
    stPtzAreaOperate.dwBeginPointY = oRect.top;
    stPtzAreaOperate.dwEndPointX = oRect.right;
    stPtzAreaOperate.dwEndPointY = oRect.bottom;

    BOOL bRet = NETDEV_PTZSelZoomIn_Other(lpDevHandle, ChnID, &stPtzAreaOperate);
    if (TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Operate area");
        return;
    }

    NETDEMO_LOG_SUCC(NULL, "Operate Area");

    return;
}

void CNetDemoDlg::SetCycleMonitor(BOOL bCycleMonitor)
{
    m_bCycleMonitor = bCycleMonitor;
    return;
}

BOOL CNetDemoDlg::GetCycleMonitor()
{
    return m_bCycleMonitor;
}
