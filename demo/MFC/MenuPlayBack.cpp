// DlgMenuPlayBack.cpp : 

#include "stdafx.h"
#include "NetDemo.h"
#include "MenuPlayBack.h"


#define PLAYBACK_TIME_ID        101
#define DOWNLOAD_TIME_ID        102

#define PLAY_BACK_TITLE         "Playback"
#define CAPTURE_TITLE           "Capture picture"
#define DOWNLOAD_TITLE          "Download"

#define TIME_COUNT                          5

#define COL_INDEX_START_TIME                1
#define COL_INDEX_STOP_TIME                 2

IMPLEMENT_DYNAMIC(CMenuPlayBack, CDialog)

CMenuPlayBack::CMenuPlayBack(CWnd* pParent /*=NULL*/)
: CDialog(CMenuPlayBack::IDD, pParent)
, m_strRecodeDayNums(_T(""))
{
    m_hPlayEnableIcon = AfxGetApp()->LoadIcon(IDI_PLAY_ENABLE);
    m_hPlayDisableIcon = AfxGetApp()->LoadIcon(IDI_PLAY_DISABLE);
    m_hPauseEnableIcon = AfxGetApp()->LoadIcon(IDI_PAUSE_ENABLE);
    m_hPauseDisableIcon = AfxGetApp()->LoadIcon(IDI_PAUSE_DISABLE);
    m_hStopEnableIcon = AfxGetApp()->LoadIcon(IDI_STOP_ENABLE);
    m_hStopDisableIcon = AfxGetApp()->LoadIcon(IDI_STOP_DISABLE);
    m_hSoundStartIcon= AfxGetApp()->LoadIcon(IDI_SOUND_ENABLE);
    m_hSoundStopIcon= AfxGetApp()->LoadIcon(IDI_SOUND_DISABLE);
    m_hGotoHeadDisableIcon =    AfxGetApp()->LoadIcon(IDI_GOTOSTART_DISABLE);
    m_hFastDisableIcon = AfxGetApp()->LoadIcon(IDI_FASTFORWARD_DISABLE);
    m_hSlowDisableIcon= AfxGetApp()->LoadIcon(IDI_FASTBACKWARD_DISABLE);
    m_hGotoHeadEnableIcon = AfxGetApp()->LoadIcon(IDI_GOTOSTART_ENABLE);
    m_hFastEnableIcon = AfxGetApp()->LoadIcon(IDI_FASTFORWARD_ENABLE);
    m_hSlowEnableIcon = AfxGetApp()->LoadIcon(IDI_FASTBACKWARD_ENABLE);
    m_hStepEnableIcon= AfxGetApp()->LoadIcon(IDI_STEP_ENABLE);
    m_hStepDisableIcon = AfxGetApp()->LoadIcon(IDI_STEP_DISABLE);
    m_hCaptureIcon = AfxGetApp()->LoadIcon(IDI_SNAPSHOT);
    m_lEventType = 0;
    m_dwVolume = 0;
    m_dwCurScreen = 0;
    m_dwSpeed = 1;
    m_lRemainTime = 0;
    m_strRecodeDayNums = " ";
}

CMenuPlayBack::~CMenuPlayBack()
{
    KillTimer(PLAYBACK_TIME_ID);
    KillTimer(DOWNLOAD_TIME_ID);
}

void CMenuPlayBack::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_PLAYBACK_RECORD_LIST, m_oRecordList);
    DDX_Control(pDX, IDC_COMBO_EVENT_LIST, m_oCBoxEventList);
    DDX_Control(pDX, IDC_TIME_BEGIN, m_oBeginTime);
    DDX_Control(pDX, IDC_TIME_END, m_oEndTime);
    DDX_Control(pDX, IDC_DATE_BEGIN, m_oBeginDate);
    DDX_Control(pDX, IDC_DATE_END, m_oEndDate);
    DDX_Text(pDX, IDC_PLAYBACK_CURRENT_TIME, m_oCurPlayTime);
    DDX_Text(pDX, IDC_PLAYBACK_REMAIN_TIME, m_strRemainTime);
    DDX_Text(pDX, IDC_DEV_SYSTEM_TIME, m_strRecodeDayNums);
}

BOOL CMenuPlayBack::OnInitDialog()
{
    CDialog::OnInitDialog();
    SetPlayBackIconDisable();
    m_oPlayBackscreenPannel.Create(
        NULL,
        NULL,
        WS_CHILD|WS_VISIBLE, 
        CRect(0,0,0,0), 
        this, 
        1981);
    m_oDownloadInfo.Create(IDD_DLG_DOWNLOAD_INFO,this);
    m_oPlayBackscreenPannel.ShowWindow(SW_SHOW);
    m_oPlayBackscreenPannel.SetShowPlayWin(NETDEMO_SPLIT4, m_dwCurScreen);
    UpdatePannelPosition();
    InitPlayBackList();
    InitCombo();
    initSlider();
    InitToolTipCtrl();
    InitScreenPannel();
    initSearchTime();
    initRemainTime();
    initSpeed();

    m_oCurPlayTime = "0000/00/00 00:00:00";
    CheckRadioButton(IDC_RADIO_FORWARD, IDC_RADIO_REVERSE, IDC_RADIO_FORWARD);
    UpdateData(FALSE);
    SetTimer(PLAYBACK_TIME_ID, 500, NULL);
    SetTimer(DOWNLOAD_TIME_ID, 1000, NULL);

    return TRUE;
}

BEGIN_MESSAGE_MAP(CMenuPlayBack, CDialog)
    ON_BN_CLICKED(IDC_BUTTON_DOWNLOADINFO, &CMenuPlayBack::OnBnClickedButtonDownloadinfo)
    ON_BN_CLICKED(IDC_EVENT_QUERY_RECORD, &CMenuPlayBack::OnBnClickedEventQueryRecord)
    ON_CBN_SELCHANGE(IDC_COMBO_EVENT_LIST, &CMenuPlayBack::OnCbnSelchangeComboEventList)
    ON_BN_CLICKED(IDC_BUTTON_PLAYBACK_PLAY, &CMenuPlayBack::OnBnClickedButtonPlaybackPlay)
    ON_BN_CLICKED(IDC_BUTTON_PLAYBACK_PAUSE, &CMenuPlayBack::OnBnClickedButtonPlaybackPause)
    ON_BN_CLICKED(IDC_BUTTON_PLAYBACK_STOP, &CMenuPlayBack::OnBnClickedButtonPlaybackStop)
    ON_BN_CLICKED(IDC_BUTTON_PLAYBACK_SLOW, &CMenuPlayBack::OnBnClickedButtonPlaybackSlow)
    ON_BN_CLICKED(IDC_BUTTON_PLAYBACK_FAST, &CMenuPlayBack::OnBnClickedButton1PlaybackFast)
    ON_BN_CLICKED(IDC_BUTTON_PLAYBACK_CAP, &CMenuPlayBack::OnBnClickedButtonPlaybackCap)
    ON_BN_CLICKED(IDC_BUTTON_PLAYBACK_SETBEGINPOS, &CMenuPlayBack::OnBnClickedButtonPlaybackSetbeginpos)
    ON_BN_CLICKED(IDC_BUTTON_PLAYBACK_NEXTFRAME, &CMenuPlayBack::OnBnClickedButtonPlaybackNextframe)
    ON_WM_HSCROLL()
    ON_WM_TIMER()
    ON_BN_CLICKED(IDC_BUTTON_START_DEMNLOAD, &CMenuPlayBack::OnBnClickedButtonStartDemnload)
    ON_BN_CLICKED(IDC_BUTTON_STOP_DOWNLOAD, &CMenuPlayBack::OnBnClickedButtonStopDownload)
    ON_BN_CLICKED(IDC_BUTTON_PLAYBACK_VOL, &CMenuPlayBack::OnBnClickedButtonPlaybackVol)
    ON_MESSAGE(WM_CLICK_PLAYBACK_WND,&CMenuPlayBack::OnClickPlayBackWindow)
    ON_NOTIFY(NM_CLICK, IDC_PLAYBACK_RECORD_LIST, &CMenuPlayBack::OnNMClickPlaybackRecordList)
    ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_PLAY_PROGRESS, &CMenuPlayBack::OnNMReleasedcaptureSliderPlayProgress)
    ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_PLAY_PROGRESS, &CMenuPlayBack::OnNMCustomdrawSliderPlayProgress)
    ON_BN_CLICKED(IDC_BUTTON_GETRECORDDAYNUMS, &CMenuPlayBack::OnBnClickedButtonGetrecorddaynums)
END_MESSAGE_MAP()


void CMenuPlayBack::UpdatePannelPosition()
{
    GetClientRect(&m_oClientRect);

    GetDlgItem(IDC_SCREEN_WINDOW_PLAYBACK)->GetWindowRect(&m_oClientRect);

    m_oScreenRect.top = m_oClientRect.top-25/* + 5*/;
    m_oScreenRect.bottom = m_oClientRect.bottom-25/* - 20*/;
    m_oScreenRect.left = m_oClientRect.left-5/* + 10*/;
    m_oScreenRect.right = m_oClientRect.right;

    m_oPlayBackscreenPannel.MoveWindow(m_oScreenRect);

    return;
}

void CMenuPlayBack::InitPlayBackList()
{
    m_oRecordList.InsertColumn(0, "", LVCFMT_LEFT, 0, -1); 

    CString str = "Begin Time";
    m_oRecordList.InsertColumn(COL_INDEX_START_TIME, str, LVCFMT_LEFT, 120);
    str = "End time";
    m_oRecordList.InsertColumn(COL_INDEX_STOP_TIME, str, LVCFMT_LEFT, 120);

    m_oRecordList.SetExtendedStyle(m_oRecordList.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES);

    return;
}

void CMenuPlayBack::SetPlayBackIconDisable()
{
    CButton *pButton;
    pButton = (CButton *)GetDlgItem(IDC_BUTTON_PLAYBACK_PLAY);
    pButton->SetIcon(m_hPlayDisableIcon);
    pButton->EnableWindow(FALSE);

    pButton = (CButton *)GetDlgItem(IDC_BUTTON_PLAYBACK_PAUSE);
    pButton->SetIcon(m_hPauseDisableIcon);
    pButton->EnableWindow(FALSE);

    pButton = (CButton *)GetDlgItem(IDC_BUTTON_PLAYBACK_STOP);
    pButton->SetIcon(m_hStopDisableIcon);
    pButton->EnableWindow(FALSE);

    pButton = (CButton *)GetDlgItem(IDC_BUTTON_PLAYBACK_SLOW);
    pButton->SetIcon(m_hSlowDisableIcon);
    pButton->EnableWindow(FALSE);

    pButton = (CButton *)GetDlgItem(IDC_BUTTON_PLAYBACK_FAST);
    pButton->SetIcon(m_hFastDisableIcon);
    pButton->EnableWindow(FALSE);

    pButton = (CButton *)GetDlgItem(IDC_BUTTON_PLAYBACK_CAP);
    pButton->SetIcon(m_hCaptureIcon);
    pButton->EnableWindow(FALSE);

    pButton = (CButton *)GetDlgItem(IDC_BUTTON_PLAYBACK_SETBEGINPOS);
    pButton->SetIcon(m_hGotoHeadDisableIcon);
    pButton->EnableWindow(FALSE);

    pButton = (CButton *)GetDlgItem(IDC_BUTTON_PLAYBACK_NEXTFRAME);
    pButton->SetIcon(m_hStepDisableIcon);
    pButton->EnableWindow(FALSE);

    pButton = (CButton *)GetDlgItem(IDC_BUTTON_PLAYBACK_VOL);
    pButton->SetIcon(m_hSoundStopIcon);
    pButton->EnableWindow(FALSE);

    return;
}

void CMenuPlayBack::SetPlayBackIconEnable()
{
    CButton *pButton;
    pButton = (CButton *)GetDlgItem(IDC_BUTTON_PLAYBACK_PLAY);
    pButton->SetIcon(m_hPlayEnableIcon);
    pButton->EnableWindow(TRUE);

    pButton = (CButton *)GetDlgItem(IDC_BUTTON_PLAYBACK_PAUSE);
    pButton->SetIcon(m_hPauseEnableIcon);
    pButton->EnableWindow(TRUE);

    pButton = (CButton *)GetDlgItem(IDC_BUTTON_PLAYBACK_STOP);
    pButton->SetIcon(m_hStopEnableIcon);
    pButton->EnableWindow(TRUE);

    pButton = (CButton *)GetDlgItem(IDC_BUTTON_PLAYBACK_SLOW);
    pButton->SetIcon(m_hSlowEnableIcon);
    pButton->EnableWindow(TRUE);

    pButton = (CButton *)GetDlgItem(IDC_BUTTON_PLAYBACK_FAST);
    pButton->SetIcon(m_hFastEnableIcon);
    pButton->EnableWindow(TRUE);

    pButton = (CButton *)GetDlgItem(IDC_BUTTON_PLAYBACK_CAP);
    pButton->SetIcon(m_hCaptureIcon);
    pButton->EnableWindow(TRUE);

    pButton = (CButton *)GetDlgItem(IDC_BUTTON_PLAYBACK_SETBEGINPOS);
    pButton->SetIcon(m_hGotoHeadEnableIcon);
    pButton->EnableWindow(TRUE);

    pButton = (CButton *)GetDlgItem(IDC_BUTTON_PLAYBACK_NEXTFRAME);
    pButton->SetIcon(m_hStepEnableIcon);
    pButton->EnableWindow(TRUE);

    pButton = (CButton *)GetDlgItem(IDC_BUTTON_PLAYBACK_VOL);
    pButton->SetIcon(m_hSoundStartIcon);
    pButton->EnableWindow(TRUE);

    return;
}

void CMenuPlayBack::OnBnClickedButtonDownloadinfo()
{
    m_oDownloadInfo.ShowWindow(SW_SHOW);

    return;
}

int CMenuPlayBack::GetCurWinID(void)
{
    CPlayWnd* pWnd = (CPlayWnd*)m_oPlayBackscreenPannel.GetActivePage();
    if (pWnd && ::IsWindow(pWnd->GetSafeHwnd()))
    {
        return pWnd->GetWinID();
    }

    return -1;
}
void CMenuPlayBack::OnBnClickedEventQueryRecord()
{
    std::queue<NETDEV_FINDDATA_S>  FindData ;
    int nRow = -1;

    m_oRecordList.DeleteAllItems();
    m_oFindData.clear();

    QueryRecord(FindData);
    while(FALSE == FindData.empty())
    {
        NETDEV_FINDDATA_S RecordData = FindData.front();
        nRow = m_oRecordList.InsertItem(0, "");
        m_oRecordList.SetItemText(nRow, 1, GetTime(RecordData.tBeginTime));
        m_oRecordList.SetItemText(nRow, 2, GetTime(RecordData.tEndTime));
        m_oFindData.push_back(RecordData);
        if (m_oFindData.size() == 1)
        {
            RecordData.tBeginTime = RecordData.tBeginTime;
        }
        FindData.pop();
    }
    if (nRow >= 0)
    {
        SetPlayBackIconEnable();
    }
    return;
}

BOOL CMenuPlayBack::getTimeInfo(INT64& dwBeginTime, INT64& dwEndTime)
{
    CString strBeginTime;
    CString strEndTime;
    CString strTemp;
    GetDlgItem(IDC_DATE_BEGIN)->GetWindowText(strTemp);
    strBeginTime = strTemp;
    GetDlgItem(IDC_TIME_BEGIN)->GetWindowText(strTemp);
    strBeginTime += " ";
    strBeginTime += strTemp;
    GetDlgItem(IDC_DATE_END)->GetWindowText(strTemp);
    strEndTime = strTemp;
    GetDlgItem(IDC_TIME_END)->GetWindowText(strTemp);
    strEndTime += " ";
    strEndTime += strTemp;

    dwBeginTime = GetTick(strBeginTime);
    dwEndTime = GetTick(strEndTime);

    if (difftime(dwBeginTime, dwEndTime) >= 0)
    {
        CString strInfo;
        strInfo.Format("BeginTime:%s >= EndTime:%s", strBeginTime, strEndTime);
        MessageBox(strInfo, PLAY_BACK_TITLE);
        return FALSE;
    }

    return TRUE;
}

BOOL CMenuPlayBack::compareTime(const CString& strBeginTime, const CString& strEndTime)
{
    int nBeginYear, nBeginMonth, nBeginDate, nBeginHour, nBeginMin, nBeginSec;
    sscanf(strBeginTime, "%d/%d/%d %d:%d:%d", &nBeginYear, &nBeginMonth, &nBeginDate, &nBeginHour, &nBeginMin, &nBeginSec);

    int nEndYear, nEndMonth, nEndDate, nEndHour, nEndMin, nEndSec;
    sscanf(strEndTime, "%d/%d/%d %d:%d:%d", &nEndYear, &nEndMonth, &nEndDate, &nEndHour, &nEndMin, &nEndSec);
    if ((nEndYear >= nBeginYear) ||
        (nEndMonth > nBeginMonth) ||
        (nEndDate > nBeginDate) ||
        (nEndHour > nBeginHour) ||
        (nEndMin > nBeginMin) || 
        (nEndSec > nBeginSec))
    {
        return TRUE;
    }

    return FALSE;
}

void CMenuPlayBack::InitCombo()
{
    m_oCBoxEventList.AddString("Normal");
    m_oCBoxEventList.AddString("Motion Detection");
    m_oCBoxEventList.AddString("Digital Input");
    m_oCBoxEventList.AddString("Video Loss");
    m_oCBoxEventList.SetCurSel(0);

    return;
}

void CMenuPlayBack::InitToolTipCtrl()
{
    m_oToolTip.Create(this);
    m_oToolTip.SetDelayTime(100);
    m_oToolTip.SetTipTextColor( RGB(0,0,255) );
    m_oToolTip.SetTipBkColor( RGB(255,255,255));
    m_oToolTip.Activate(TRUE);

    return;
}

BOOL CMenuPlayBack::PreTranslateMessage(MSG* pMsg)
{
    if(pMsg->message==WM_MOUSEMOVE )
    {
        m_oToolTip.RelayEvent(pMsg);
    }
    if(pMsg->message == WM_LBUTTONDOWN)
    {
        if(pMsg->hwnd == GetDlgItem(IDC_SLIDER_PLAY_PROGRESS)->m_hWnd)
        {
            KillTimer(PLAYBACK_TIME_ID);
            KillTimer(DOWNLOAD_TIME_ID);
        }

    }
    
    return CDialog::PreTranslateMessage(pMsg);
}

void CMenuPlayBack::OnCbnSelchangeComboEventList()
{
    INT32 index = m_oCBoxEventList.GetCurSel();
    switch(index)
    {
    case 0:
        {
            m_lEventType = NETDEV_TYPE_STORE_TYPE_ALL;
        }
        break;
    case 1:
        {
            m_lEventType = NETDEV_EVENT_STORE_TYPE_MOTIONDETECTION;
        }
        break;
    case 2:
        {
            m_lEventType = NETDEV_EVENT_STORE_TYPE_DIGITALINPUT;
        }
        break;
    case 3:
        {
            m_lEventType = NETDEV_EVENT_STORE_TYPE_VIDEOLOSS;
        }
        break;
    default:
        break;
    }

    return;
}

long CMenuPlayBack::GetTick(const CString& strTime)
{
    int nYear, nMonth, nDate, nHour, nMin, nSec;
    int nPos= strTime.Find('/');
    if (nPos != std::string::npos)
    {
        sscanf(strTime, "%d/%d/%d %d:%d:%d", &nYear, &nMonth, &nDate, &nHour, &nMin, &nSec);
    }
    nPos= strTime.Find('-');
    if (nPos != std::string::npos)
    {
        sscanf(strTime, "%d-%d-%d %d:%d:%d", &nYear, &nMonth, &nDate, &nHour, &nMin, &nSec);
    }
    nPos= strTime.Find('.');
    if (nPos != std::string::npos)
    {
        sscanf(strTime, "%d.%d.%d %d:%d:%d", &nYear, &nMonth, &nDate, &nHour, &nMin, &nSec);
    }

    struct tm stm;
    memset(&stm,0,sizeof(stm));
    if (nYear > 1900)
    {
        stm.tm_year = nYear-1900;
    }
    else
    {
        stm.tm_year = 2000 + nYear - 1900;
    }
    stm.tm_mon = nMonth-1;
    stm.tm_mday = nDate;
    stm.tm_hour = nHour;
    stm.tm_min = nMin;
    stm.tm_sec = nSec;

    return mktime(&stm);
}

CString CMenuPlayBack::GetTime(const INT64 tTime)
{
    CString strTime;
    tm *pTime = localtime((time_t*)&tTime);
    strTime.Format("%d/%02d/%02d %02d:%02d:%02d",
        pTime->tm_year + 1900,
        pTime->tm_mon+1,
        pTime->tm_mday,
        pTime->tm_hour,
        pTime->tm_min,
        pTime->tm_sec);
    
    return strTime;
}

void CMenuPlayBack::QueryRecord(std::queue<NETDEV_FINDDATA_S>&  FindData)
{
    NETDEV_FILECOND_S stFileCond = {0};
    if (FALSE == getTimeInfo(stFileCond.tBeginTime, stFileCond.tEndTime))
    {
        return ;
    }

    stFileCond.dwChannelID = ga_pMainDlg->GetChlID();
    stFileCond.dwFileType = m_lEventType;
    LPVOID dwFileHandle = NULL;
    LPVOID lpDevHandle = ga_pMainDlg->GetDevHandle();
    if (NULL == lpDevHandle)
    {
        return ;
    }
    dwFileHandle = NETDEV_FindFile(lpDevHandle, &stFileCond);
    if(NULL == dwFileHandle)
    {
        return ;
    }
    else
    {
        NETDEMO_LOG_SUCC(NULL, "Find file");
        NETDEV_FINDDATA_S stVodFile = {0};
        while (NETDEV_FindNextFile(dwFileHandle, &stVodFile))
        {
            FindData.push(stVodFile);
        }

    }
    if (TRUE == NETDEV_FindClose(dwFileHandle))
    {
        NETDEMO_LOG_SUCC(NULL, "Find close");
    }
    else
    {
        NETDEMO_LOG_ERROR(NULL, "Find close");
    }
    return ;
}

void CMenuPlayBack::OnBnClickedButtonPlaybackPlay()
{
    CPlayWnd* oPlayWnd = (CPlayWnd*)m_oPlayBackscreenPannel.GetActivePage();
    LPVOID lpHandle = oPlayWnd->GetSplitHandle();
    if (NULL != lpHandle)
    {
        if(TRUE == oPlayWnd->getPauseState())
        {
            NETDEV_PlayBackControl(lpHandle, NETDEV_PLAY_CTRL_RESUME, NULL);
            oPlayWnd->setPauseState(FALSE);
            return;
        }

        m_oPlayBackscreenPannel.SetNextActivePage();
        oPlayWnd = (CPlayWnd*)m_oPlayBackscreenPannel.GetActivePage();
    }

    if (NULL != oPlayWnd->GetSplitHandle())
    {
        OnBnClickedButtonPlaybackStop();
    }

    NETDEV_PLAYBACKCOND_S stPlayBackByTimeInfo = {0};
    if (FALSE == getTimeInfo(stPlayBackByTimeInfo.tBeginTime, stPlayBackByTimeInfo.tEndTime))
    {
        return;
    }

    CSliderCtrl *pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_PLAY_PROGRESS);//YZ
    pSlidCtrl->SetRange(stPlayBackByTimeInfo.tBeginTime, stPlayBackByTimeInfo.tEndTime, TRUE);
    pSlidCtrl->EnableWindow(TRUE);

    stPlayBackByTimeInfo.dwChannelID = ga_pMainDlg->GetChlID();
    stPlayBackByTimeInfo.hPlayWnd = oPlayWnd->m_hWnd;
    stPlayBackByTimeInfo.dwLinkMode = NETDEV_TRANSPROTOCAL_RTPTCP;
    LPVOID lpDevHandle = ga_pMainDlg->GetDevHandle();
    if (NULL == lpDevHandle)
    {
        return;
    }

    lpHandle = NETDEV_PlayBackByTime(lpDevHandle, &stPlayBackByTimeInfo);
    if (lpHandle== NULL)
    {
        NETDEMO_LOG_ERROR(NULL, "Playback by time");
        return;
    }
    else
    {
        NETDEMO_LOG_SUCC(NULL, "Playback by time");
    }

    HTREEITEM  hItemPos =  ga_pMainDlg->m_oDeviceTreeList.GetSelectedItem();
    NETDEMO_SPLITINFO_NODE stDevinfo;
    stDevinfo.hDevTreePos = hItemPos;
    stDevinfo.iHandle = lpHandle;
    stDevinfo.dwDevIndex = ga_pMainDlg->GetCurDeviceIndex();
    stDevinfo.dwChnIndex = ga_pMainDlg->GetChlID();
    stDevinfo.emType = NETDEMO_SPLIT_TYPE_PLAY_BACK;
    oPlayWnd->SetSplitInfo(&stDevinfo);

    NETDEMO_UPDATE_TIME_INFO stUpdateInfo;
    stUpdateInfo.tBeginTime = stPlayBackByTimeInfo.tBeginTime;
    stUpdateInfo.tEndTime = stPlayBackByTimeInfo.tEndTime;
    stUpdateInfo.lpHandle = lpHandle;
    stUpdateInfo.dwCount = 0;
    stUpdateInfo.tCurTime = 0;
    oPlayWnd->setUpdateInfo(stUpdateInfo);
    oPlayWnd->SetRemainTime(stUpdateInfo.tEndTime - stUpdateInfo.tBeginTime);
    updateRemainTime(stUpdateInfo.tEndTime - stUpdateInfo.tBeginTime);

    SYSTEMTIME oTimeBegin;
    SYSTEMTIME oTimeEnd;
    SYSTEMTIME oDateBegin;
    SYSTEMTIME oDateEnd;
    m_oBeginTime.GetTime(&oTimeBegin);
    m_oEndTime.GetTime(&oTimeEnd);
    m_oBeginDate.GetTime(&oDateBegin);
    m_oEndDate.GetTime(&oDateEnd);
    oPlayWnd->setDateTime(oDateBegin, oTimeBegin, oDateEnd, oTimeEnd);

    BOOL bRet = NETDEV_GetSoundVolume(lpHandle, &m_dwVolume);
    if (FALSE == bRet)
    {
        NETDEMO_LOG_SUCC(NULL, "Get sound volume");
    }

    pSlidCtrl=(CSliderCtrl*)GetDlgItem(IDC_SLD_SOUND_VOLUME);
    pSlidCtrl->SetPos(m_dwVolume);
    oPlayWnd->SetSoundState(TRUE);
    pSlidCtrl->EnableWindow(TRUE);
    CButton *pButton =(CButton *)GetDlgItem(IDC_BUTTON_PLAYBACK_VOL);
    pButton->SetIcon(m_hSoundStartIcon);
    oPlayWnd->SetSoundState(TRUE);

    bRet = NETDEV_OpenSound(lpHandle);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Open sound");
    }

    return;
}
BOOL CMenuPlayBack::GetPlayWnd(CPlayWnd** pPlayWnd)
{
    int nCurWinID = GetCurWinID();
    if (nCurWinID < 0)
    {
        MessageBox("please select playwnd", PLAY_BACK_TITLE);
        return FALSE;
    }

    *pPlayWnd = (CPlayWnd *)m_oPlayBackscreenPannel.GetPage(nCurWinID);
    return TRUE;
}

BOOL CMenuPlayBack::GetPlayHandle(LPVOID* pPlayHandle)
{
    CPlayWnd* objPlayWnd = NULL;
    if (FALSE == GetPlayWnd(&objPlayWnd))
    {
        return FALSE;
    }

    *pPlayHandle = objPlayWnd->GetSplitHandle();
    if (NULL == *pPlayHandle)
    {
        return FALSE;
    }

    return TRUE;
}

void CMenuPlayBack::OnBnClickedButtonPlaybackPause()
{
    CPlayWnd* objPlayWnd = (CPlayWnd*)m_oPlayBackscreenPannel.GetActivePage();
    LPVOID pPlayHandle = objPlayWnd->GetSplitHandle();
    if(NULL == pPlayHandle)
    {
        return;
    }

    BOOL bRet = NETDEV_PlayBackControl(pPlayHandle, NETDEV_PLAY_CTRL_PAUSE, NULL);
    if (!bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Playback control pause");
        return;
    }
    else
    {
        objPlayWnd->setPauseState(TRUE);
        NETDEMO_LOG_SUCC(NULL, "Playback control pause");
    }

    return;
}

void CMenuPlayBack::OnBnClickedButtonPlaybackStop()
{
    CPlayWnd* oPlayWnd = (CPlayWnd*)m_oPlayBackscreenPannel.GetActivePage();
    LPVOID pPlayHandle = oPlayWnd->GetSplitHandle();
    if(NULL == pPlayHandle)
    {
        return;
    }

    if (NULL != pPlayHandle)
    {
        BOOL bRet = NETDEV_StopPlayBack(pPlayHandle);
        if (pPlayHandle== NULL)
        {
            NETDEMO_LOG_ERROR(NULL, "Stop play back");
            return;
        }
        else
        {
            NETDEMO_LOG_SUCC(NULL, "Stop play back");
        }

        oPlayWnd->SetSplitHandle(NULL);

        NETDEMO_UPDATE_TIME_INFO stUpdateInfo;
        oPlayWnd->getUpdateInfo(stUpdateInfo);
        stUpdateInfo.tBeginTime = 0;
        stUpdateInfo.tEndTime = 0;
        stUpdateInfo.lpHandle = NULL;
        stUpdateInfo.dwCount = 0;
        stUpdateInfo.tCurTime = 0;
        CSliderCtrl   *pSlidCtrl=(CSliderCtrl*)GetDlgItem(IDC_SLIDER_PLAY_PROGRESS);
        pSlidCtrl->SetPos(0);
        updateRemainTime(0);
    }
    else
    {
        MessageBox("Open playback first", PLAY_BACK_TITLE);
    }

    return;
}

void CMenuPlayBack::initSpeed()
{
    char str[5];
    m_dwSpeed = 1;
    sprintf(str,"%dx",m_dwSpeed);
    ((CWnd*)GetDlgItem(IDC_TEXT_PLAYBACK_SPEED))->SetWindowText( _T(str));
}

void CMenuPlayBack::updateSpeed(INT32 enSpeed)
{
    char str[5];
    if(IMCP_RM_SCALE_16_BACKWARD == enSpeed)
    {
        m_dwSpeed = -16;
    }
    else if(IMCP_RM_SCALE_8_BACKWARD == enSpeed)
    {
        m_dwSpeed = -8;
    }
    else if(IMCP_RM_SCALE_4_BACKWARD == enSpeed)
    {
        m_dwSpeed = -4;
    }
    else if(IMCP_RM_SCALE_2_BACKWARD == enSpeed)
    {
        m_dwSpeed = -2;
    }
    else if(IMCP_RM_SCALE_1_BACKWARD == enSpeed)
    {
        m_dwSpeed = -1;
    }
    else if(IMCP_RM_SCALE_HALF_BACKWARD == enSpeed)
    {
        m_dwSpeed = -(1/2);
    }
    else if(IMCP_RM_SCALE_QUARTER_BACKWARD == enSpeed)
    {
         m_dwSpeed = -(1/4);
    }
    else if(IMCP_RM_SCALE_QUARTER_FORWARD == enSpeed)
    {
         m_dwSpeed = 1/4;
    }
    else if(IMCP_RM_SCALE_HALF_FORWARD == enSpeed)
    {
        m_dwSpeed = 1/2;
    }
    else if(IMCP_RM_SCALE_1_FORWARD == enSpeed)
    {
         m_dwSpeed = 1;
    }
    else if(IMCP_RM_SCALE_2_FORWARD == enSpeed)
    {
        m_dwSpeed = 2;
    }
    else if(IMCP_RM_SCALE_4_FORWARD == enSpeed)
    {
        m_dwSpeed = 4;
    }  
    else if(IMCP_RM_SCALE_8_FORWARD == enSpeed)
    {
        m_dwSpeed = 8;
    }    
    else if(IMCP_RM_SCALE_16_FORWARD == enSpeed)
    {
        m_dwSpeed = 16;
    }           
    sprintf(str,"%dx",m_dwSpeed);
    ((CWnd*)GetDlgItem(IDC_TEXT_PLAYBACK_SPEED))->SetWindowText( _T(str));
};

void CMenuPlayBack::OnBnClickedButtonPlaybackSlow()
{
    CPlayWnd* oPlayWnd = (CPlayWnd*)m_oPlayBackscreenPannel.GetActivePage();
    LPVOID pPlayHandle = oPlayWnd->GetSplitHandle();
    if(NULL == pPlayHandle)
    {
        return;
    }

    INT32 enSpeed = 0;
    BOOL bRet = NETDEV_PlayBackControl(pPlayHandle, NETDEV_PLAY_CTRL_GETPLAYSPEED, &enSpeed);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Get play speed");
    }
    else
    {
        NETDEMO_LOG_SUCC(NULL, "Get play speed");
    }

    enSpeed = enSpeed - 1 >= NETDEV_PLAY_STATUS_16_BACKWARD ? (enSpeed - 1) : enSpeed;
    while((enSpeed <= NETDEV_PLAY_STATUS_HALF_FORWARD) && (enSpeed >= NETDEV_PLAY_STATUS_HALF_BACKWARD))
    {
        enSpeed--;
    }

    bRet = NETDEV_PlayBackControl(pPlayHandle, NETDEV_PLAY_CTRL_SETPLAYSPEED, &enSpeed);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Set play speed");
    }
    else
    {
        NETDEMO_LOG_SUCC(NULL, "Set play speed");
    }

    oPlayWnd->SetSpeed(enSpeed);
    updateSpeed(enSpeed);

    return;
}

void CMenuPlayBack::OnBnClickedButton1PlaybackFast()
{
    CPlayWnd* oPlayWnd = (CPlayWnd*)m_oPlayBackscreenPannel.GetActivePage();
    LPVOID lpPlayHandle = oPlayWnd->GetSplitHandle();
    if(NULL == lpPlayHandle)
    {
        return;
    }

    INT32 enSpeed = 0;
    BOOL bRet = NETDEV_PlayBackControl(lpPlayHandle, NETDEV_PLAY_CTRL_GETPLAYSPEED, &enSpeed);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Get play speed");
    }
    else
    {
        NETDEMO_LOG_SUCC(NULL, "Get play speed");
    }

    enSpeed = enSpeed + 1 <= NETDEV_PLAY_STATUS_16_FORWARD ? (enSpeed + 1) : enSpeed;
    while((enSpeed <= NETDEV_PLAY_STATUS_HALF_FORWARD) && (enSpeed >= NETDEV_PLAY_STATUS_HALF_BACKWARD))
    {
        enSpeed++;
    }

    bRet = NETDEV_PlayBackControl(lpPlayHandle, NETDEV_PLAY_CTRL_SETPLAYSPEED, &enSpeed);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Set play speed");
    }
    else
    {
        NETDEMO_LOG_SUCC(NULL, "Set play speed");
    }

    oPlayWnd->SetSpeed(enSpeed);
    updateSpeed(enSpeed);

    return;
}

void CMenuPlayBack::OnBnClickedButtonPlaybackCap()
{
    CPlayWnd* oPlayWnd = (CPlayWnd*)m_oPlayBackscreenPannel.GetActivePage();
    LPVOID pPlayHandle = oPlayWnd->GetSplitHandle();
    if(NULL == pPlayHandle)
    {
        return;
    }

    CString strPath = ga_pMainDlg->m_oDlgLocalSetting.m_strSnapshotPath;
    strPath += "\\";
    LPVOID lpDevHandle = ga_pMainDlg->GetDevHandle();
    if (NULL == lpDevHandle)
    {
        return;
    }

    CString strFileName;
    getFileName(lpDevHandle, strFileName);
    strPath += strFileName;

    CHAR szTmpPath[NETDEV_LEN_260] = {0};
    MBToUTF8(strPath.GetBuffer(0), szTmpPath, sizeof(szTmpPath) - 1);
    BOOL bRet = NETDEV_CapturePicture(pPlayHandle, szTmpPath, NETDEV_PICTURE_BMP);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Capture picture");
    }
    else
    {
        CString strOut;
        strOut = "Get capture succeed! Path: ";
        strOut += strPath;
        MessageBox(strOut, CAPTURE_TITLE);
        NETDEMO_LOG_SUCC(NULL, "Capture picture");
    }

    return;
}

void CMenuPlayBack::OnBnClickedButtonPlaybackSetbeginpos()
{
    CSliderCtrl   *pSlidCtrl=(CSliderCtrl*)GetDlgItem(IDC_SLIDER_PLAY_PROGRESS);
    pSlidCtrl->SetPos(0);
    OnBnClickedButtonPlaybackStop();
    OnBnClickedButtonPlaybackPlay();

    return;
}

void CMenuPlayBack::OnBnClickedButtonPlaybackNextframe()
{
    CPlayWnd* oPlayWnd = (CPlayWnd*)m_oPlayBackscreenPannel.GetActivePage();
    LPVOID pPlayHandle = oPlayWnd->GetSplitHandle();
    if(NULL == pPlayHandle)
    {
        return;
    }

    INT32 enSpeed = NETDEV_PLAY_STATUS_1_FRAME_FORWD;
    BOOL bRet = NETDEV_PlayBackControl(pPlayHandle, NETDEV_PLAY_CTRL_SINGLE_FRAME, &enSpeed);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Playback control single frame");
    }
    else
    {
        NETDEMO_LOG_SUCC(NULL, "Playback control single frame");
    }

    return;
}

void CMenuPlayBack::initSlider()
{
    CSliderCtrl   *pSlidCtrl=(CSliderCtrl*)GetDlgItem(IDC_SLD_SOUND_VOLUME);
    pSlidCtrl->SetRange(NETDEV_AUDIO_SOUND_MIN_VALUE, NETDEV_AUDIO_SOUND_MAX_VALUE, TRUE);
    pSlidCtrl->SetTicFreq(20);

    pSlidCtrl=(CSliderCtrl*)GetDlgItem(IDC_SLIDER_PLAY_PROGRESS);
    pSlidCtrl->SetTicFreq(1);
    pSlidCtrl->EnableWindow(FALSE);

    return;
}


void CMenuPlayBack::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    CSliderCtrl *pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLD_SOUND_VOLUME);
    INT32 dwVolume = pSlidCtrl->GetPos();

    if (dwVolume != m_dwVolume)
    {
        LPVOID pPlayHandle;
        if(FALSE == GetPlayHandle(&pPlayHandle))
        {
            return;
        }
        BOOL bRet = NETDEV_SoundVolumeControl(pPlayHandle, dwVolume);
        if(TRUE != bRet)
        {
            NETDEMO_LOG_ERROR(NULL, "Sound volume control");
        }
        m_dwVolume = dwVolume;
    }

    CDialog::OnHScroll(nSBCode, nPos, pScrollBar);

    return;
}

void CMenuPlayBack::OnTimer(UINT_PTR nIDEvent)
{
    if(PLAYBACK_TIME_ID == nIDEvent)
    {
        CPlayWnd* oPlayWnd = (CPlayWnd*)m_oPlayBackscreenPannel.GetActivePage();
        LPVOID pPlayHandle = oPlayWnd->GetSplitHandle();
        if(NULL == pPlayHandle)
        {
            CSliderCtrl   *pSlidCtrl=(CSliderCtrl*)GetDlgItem(IDC_SLIDER_PLAY_PROGRESS);
            pSlidCtrl->SetPos(0);
            return;
        }

        INT64 iPlayTime = 0;
        BOOL bRet = NETDEV_PlayBackControl(pPlayHandle,NETDEV_PLAY_CTRL_GETPLAYTIME, &iPlayTime);
        if(TRUE != bRet)
        {
            //NETDEMO_LOG_ERROR(NULL, "play back control get play time");
        }

        NETDEMO_UPDATE_TIME_INFO &stUpdateInfo = m_oastUpdateInfo[m_dwCurScreen];
        oPlayWnd->getUpdateInfo(stUpdateInfo);
        CSliderCtrl *pSlidCtrl=(CSliderCtrl*)GetDlgItem(IDC_SLIDER_PLAY_PROGRESS);
        pSlidCtrl->SetRange(stUpdateInfo.tBeginTime, stUpdateInfo.tEndTime, TRUE);

        if (TRUE == updateProgress(stUpdateInfo, iPlayTime, FALSE))
        {
            pSlidCtrl->SetPos(iPlayTime);
            oPlayWnd->SetRemainTime(stUpdateInfo.tEndTime - stUpdateInfo.tCurTime);
        }
        else
        {
            if (iPlayTime > 0)
            {
                OnBnClickedButtonPlaybackStop();
                updateSpeed(IMCP_RM_SCALE_1_FORWARD);
                initRemainTime();
            }
        }
    }
    else if(DOWNLOAD_TIME_ID == nIDEvent)
    {
        std::map<int, NETDEMO_UPDATE_TIME_INFO>::iterator it;
        for (it = m_oDownloadInfoMap.begin(); it!= m_oDownloadInfoMap.end(); )
        {
            INT64 iPlayTime = 0;
            BOOL bRet = NETDEV_PlayBackControl(it->second.lpHandle,NETDEV_PLAY_CTRL_GETPLAYTIME, &iPlayTime);
            if(TRUE != bRet)
            {
                //NETDEMO_LOG_ERROR(NULL, "play back control get play time");
            }

            if (0 == iPlayTime|| updateProgress(it->second, iPlayTime))
            {
                int downLoadState = (float)(iPlayTime - it->second.tBeginTime)/(it->second.tEndTime - it->second.tBeginTime) * 100;
                m_oDownloadInfo.updateDownLoadState(it->first, downLoadState);
                it++;
            }
            else
            {
                NETDEV_StopGetFile(it->second.lpHandle);
                m_oDownloadInfoMap[it->first].lpHandle = NULL;
                m_oDownloadInfoMap[it->first].tBeginTime = 0;
                m_oDownloadInfoMap[it->first].tEndTime = 0;
                m_oDownloadInfoMap[it->first].strFileName = "";
                m_oDownloadInfoMap[it->first].strFilePath = "";
                m_oDownloadInfoMap[it->first].dwCount = 0;
                m_oDownloadInfoMap[it->first].tCurTime = 0;
                m_oDownloadInfo.updateDownLoadState(it->first, 100);
                it = m_oDownloadInfoMap.erase(it);
            }
        }
    }

    CDialog::OnTimer(nIDEvent);

    return;
}

void CMenuPlayBack::OnBnClickedButtonStartDemnload()
{
    startDownloadRecord();
}

void CMenuPlayBack::OnBnClickedButtonStopDownload()
{
    stopDownloadRecord();
    m_oDownloadInfo.stopDownLoad();
}

void CMenuPlayBack::startDownloadRecord()
{
    NETDEV_PLAYBACKCOND_S stPlayBackInfo = {0};
    if (FALSE == getTimeInfo(stPlayBackInfo.tBeginTime, stPlayBackInfo.tEndTime))
    {
        return;
    }

    stPlayBackInfo.hPlayWnd = NULL;
    stPlayBackInfo.dwDownloadSpeed = NETDEV_DOWNLOAD_SPEED_EIGHT;
    stPlayBackInfo.dwChannelID = ga_pMainDlg->GetChlID();

    LPVOID lpDevHandle = ga_pMainDlg->GetDevHandle();
    if (NULL == lpDevHandle)
    {
        return;
    }

    CString strFilePath = ga_pMainDlg->m_oDlgLocalSetting.m_strLocalRecordPath;
    strFilePath += "\\";
    CString strFileName;
    getFileName(lpDevHandle, strFileName);
    //strFileName += ".ts";
    CString strPath = strFilePath + strFileName;
    CHAR szTmpPath[NETDEV_LEN_260] = {0};
    MBToUTF8(strPath.GetBuffer(0), szTmpPath, sizeof(szTmpPath) - 1);
    LPVOID pHandle = NETDEV_GetFileByTime(lpDevHandle, &stPlayBackInfo, szTmpPath, NETDEV_MEDIA_FILE_TS);
    if(NULL == pHandle)
    {
        NETDEMO_LOG_ERROR(NULL, "Get file by time");
    }
    else
    {
        CString strOut;
        strOut = "Download succeed, Path: ";
        strOut += strPath;
        NETDEMO_UPDATE_TIME_INFO stUpdateInfo;
        stUpdateInfo.lpHandle = pHandle;
        stUpdateInfo.tBeginTime = stPlayBackInfo.tBeginTime;
        stUpdateInfo.tEndTime = stPlayBackInfo.tEndTime;
        stUpdateInfo.strFileName = strFileName;
        stUpdateInfo.strFilePath    = strFilePath;
        stUpdateInfo.dwCount = 0;
        stUpdateInfo.tCurTime = 0;

        int nIndex = m_oDownloadInfo.updateDownLoadInfo(stUpdateInfo);
        m_oDownloadInfoMap[nIndex] = stUpdateInfo;
        MessageBox(strOut, DOWNLOAD_TITLE);

        NETDEMO_LOG_SUCC(NULL, "Download");
    }

    return;
}
void CMenuPlayBack::getFileName(LPVOID  dwUserID, 
                                CString& strFileName)
{
    for (int i=0; i< gaDeviceIndex; i++)
    {
        if (dwUserID == gastDeviceInfo[i].lpDevHandle)
        {
            if(gastDeviceInfo[i].dwLoginType == NETDEMO_LOGTYPE_CLOUD)
            {
                strFileName.Format("%s_%d_", gastDeviceInfo[i].stCloudDevinfo.szDevName, ga_pMainDlg->GetChlID());
            }
            else
            {
                strFileName.Format("%s_%d_", gastDeviceInfo[i].szIPAddr, ga_pMainDlg->GetChlID());

                if (('0' > strFileName[0]) || ('9' < strFileName[0]))
                {
                    /* if domain name use https protocol */
                    if ('s' == strFileName[4])
                    {
                        strFileName.Delete(0, 8);
                    }
                    else
                    {
                        strFileName.Delete(0, 7);
                    }
                }

                INT32 dwIndex = strFileName.Find('/');
                if (std::string::npos != dwIndex)
                {
                    strFileName.SetAt(dwIndex, '-');
                }
            }
        }
    }

    INT64 tCurrentTime = time(NULL);
    CString strTime;
    tm *pTime = localtime((time_t*)&tCurrentTime);
    strTime.Format("%d%02d%02d%02d%02d%02d",pTime->tm_year + 1900,pTime->tm_mon+1,pTime->tm_mday,pTime->tm_hour,pTime->tm_min,pTime->tm_sec);

    strFileName += strTime;

    return;
}

BOOL CMenuPlayBack::updateProgress(NETDEMO_UPDATE_TIME_INFO& stUpdateInfo, INT64 dwCurTime, BOOL bFlag)
{
    if (bFlag && stUpdateInfo.dwCount > TIME_COUNT || stUpdateInfo.tEndTime <= dwCurTime)
    {
        return FALSE;
    }

    if (stUpdateInfo.tCurTime != dwCurTime)
    {
        stUpdateInfo.tCurTime = dwCurTime;
        stUpdateInfo.dwCount = 0;
    }
    else
    {
        stUpdateInfo.dwCount++;
    }

    return TRUE;
}
void CMenuPlayBack::initRemainTime()
{
    UpdateData(TRUE);

    SYSTEMTIME oSysTime = {0};
    oSysTime.wHour = 0;
    oSysTime.wMinute = 0;
    oSysTime.wSecond = 0;

    m_strRemainTime.Format("%02d:%02d:%02d",oSysTime.wHour,oSysTime.wMinute,oSysTime.wSecond);

    UpdateData(FALSE);
    return;
}

void CMenuPlayBack::updateRemainTime(INT64 remainTime)
{
    SYSTEMTIME oSysTime = {0};
    oSysTime.wHour= (remainTime / 60 / 60);
    oSysTime.wMinute = (remainTime / 60) % 60;
    oSysTime.wSecond = remainTime % 60;

    m_strRemainTime.Format("%02d:%02d:%02d",oSysTime.wHour,oSysTime.wMinute,oSysTime.wSecond);

    UpdateData(FALSE);

    return;
}

BOOL CMenuPlayBack::updateTime(NETDEMO_UPDATE_TIME_INFO& stUpdateInfo, INT64 dwCurTime, BOOL bFlag)
{
    if (bFlag && stUpdateInfo.dwCount > TIME_COUNT || stUpdateInfo.tEndTime <= dwCurTime)
    {
        return FALSE;
    }

    if (stUpdateInfo.tCurTime != dwCurTime)
    {
        stUpdateInfo.tCurTime = dwCurTime;
        stUpdateInfo.dwCount = 0;
    }
    else
    {
        stUpdateInfo.dwCount++;
    }

    INT64 tRemainTime = (float)(stUpdateInfo.tEndTime - dwCurTime);
    if (tRemainTime < 0)
    {
        return FALSE;
    }
    
    updateRemainTime(tRemainTime);
    return TRUE;
}

void CMenuPlayBack::stopDownloadRecord()
{
    std::map<int, NETDEMO_UPDATE_TIME_INFO>::iterator it;
    for (it = m_oDownloadInfoMap.begin(); it!= m_oDownloadInfoMap.end(); it++)
    {
        BOOL bRet = NETDEV_StopGetFile(it->second.lpHandle);
        if(TRUE != bRet)
        {
            NETDEMO_LOG_ERROR(NULL, "Stop get file");
        }
        else
        {
            NETDEMO_LOG_SUCC(NULL, "Stop get file");
        }
    }

    m_oDownloadInfoMap.clear();

    return;
}

void CMenuPlayBack::OnBnClickedButtonPlaybackVol()
{
    CPlayWnd* oPlayWnd = (CPlayWnd*)m_oPlayBackscreenPannel.GetActivePage();
    LPVOID pPlayHandle = oPlayWnd->GetSplitHandle();
    if(NULL == pPlayHandle)
    {
        return;
    }

    if (TRUE == oPlayWnd->GetSoundState())
    {
        BOOL bRet = NETDEV_CloseSound(pPlayHandle);
        if(TRUE != bRet)
        {
            NETDEMO_LOG_ERROR(NULL, "Close sound");
            return;
        }
        else
        {
            NETDEMO_LOG_SUCC(NULL, "Close sound");
        }

        CButton *pButton =(CButton *)GetDlgItem(IDC_BUTTON_PLAYBACK_VOL);
        pButton->SetIcon(m_hSoundStopIcon);
        oPlayWnd->SetSoundState(FALSE);

        CSliderCtrl* pSlidCtrl=(CSliderCtrl*)GetDlgItem(IDC_SLD_SOUND_VOLUME);
        pSlidCtrl->EnableWindow(FALSE);
    }
    else
    {
        BOOL bRet = NETDEV_OpenSound(pPlayHandle);
        if(TRUE != bRet)
        {
            NETDEMO_LOG_ERROR(NULL, "Open sound");
            return;
        }
        else
        {
            NETDEMO_LOG_SUCC(NULL, "Open sound");
        }
        CButton *pButton =(CButton *)GetDlgItem(IDC_BUTTON_PLAYBACK_VOL);
        pButton->SetIcon(m_hSoundStartIcon);
        oPlayWnd->SetSoundState(TRUE);

        CSliderCtrl* pSlidCtrl=(CSliderCtrl*)GetDlgItem(IDC_SLD_SOUND_VOLUME);
        pSlidCtrl->EnableWindow(TRUE);
    }

    return;
}

BOOL CMenuPlayBack::GetPlayWndDevIndex(LPVOID pPlayHandle, INT32& dwDevIndex)
{
    for (INT32 screenNo = 0; screenNo < NETDEMO_MAX_SCREENNUM; screenNo++)
    {
        CPlayWnd* pPlayWnd = (CPlayWnd *)m_oPlayBackscreenPannel.GetPage(screenNo);
        LPVOID lpPlayHandle = pPlayWnd->GetSplitHandle();
        if (pPlayHandle == lpPlayHandle)
        {
            dwDevIndex = pPlayWnd->GetDevIndex();
            return TRUE;
        }
    }

    return FALSE;
}

void CMenuPlayBack::InitScreenPannel()
{
    for (int i=0; i<NETDEMO_MAX_SCREENNUM; i++)
    {
        CPlayWnd * objPlayWnd= (CPlayWnd *)m_oPlayBackscreenPannel.GetPage(i);
        objPlayWnd->SetSplitType(NETDEMO_SPLIT_TYPE_PLAY_BACK);
        objPlayWnd->SetSplitHandle(NULL);
    }

    return;
}

void CMenuPlayBack::initSearchTime()
{
    UpdateData(TRUE);

    SYSTEMTIME oSysTime;
    m_oEndTime.GetTime(&oSysTime);
    oSysTime.wHour = 0;
    oSysTime.wMinute = 0;
    oSysTime.wSecond = 0;
    m_oBeginTime.SetTime(oSysTime);

    oSysTime.wHour = 23;
    oSysTime.wMinute = 59;
    oSysTime.wSecond = 59;
    m_oEndTime.SetTime(oSysTime);
    UpdateData(FALSE);

    return;
}


LRESULT CMenuPlayBack::OnClickPlayBackWindow(WPARAM wParam, LPARAM lParam)
{
    CPlayWnd* pPlayWnd = (CPlayWnd *)m_oPlayBackscreenPannel.GetActivePage();
    LPVOID lpHandle = pPlayWnd->GetSplitHandle();

    if (NULL != lpHandle)
    {
        HTREEITEM HTreeItem = pPlayWnd->GetDevTreePos();
        ga_pMainDlg->m_oDeviceTreeList.Select(HTreeItem,TVGN_CARET);
        SYSTEMTIME oTimeBegin;
        SYSTEMTIME oTimeEnd;
        SYSTEMTIME oDateBegin;
        SYSTEMTIME oDateEnd;
        pPlayWnd->getDateTime(oDateBegin, oTimeBegin, oDateEnd, oTimeEnd);
        m_oBeginTime.SetTime(&oTimeBegin);
        m_oEndTime.SetTime(&oTimeEnd);
        m_oBeginDate.SetTime(&oDateBegin);
        m_oEndDate.SetTime(&oDateEnd);

        m_dwSpeed = pPlayWnd->GetSpeed();
        updateSpeed(m_dwSpeed);

        m_lRemainTime = pPlayWnd->GetRemainTime();
        updateRemainTime(m_lRemainTime);
    }
    else
    {
        updateSpeed(IMCP_RM_SCALE_1_FORWARD);
        initRemainTime();
    }

    return NULL;
}


void CMenuPlayBack::OnNMClickPlaybackRecordList(NMHDR *pNMHDR, LRESULT *pResult)
{
    POSITION pos = m_oRecordList.GetFirstSelectedItemPosition();
    if (pos <= 0)
    {
        MessageBox("Please select play info", PLAY_BACK_TITLE);
        return;
    }

    INT32 dwIndex = (int)pos - 1;
    CString strStartTime = m_oRecordList.GetItemText(dwIndex, COL_INDEX_START_TIME);
    CString strEndTime = m_oRecordList.GetItemText(dwIndex, COL_INDEX_STOP_TIME);

    SYSTEMTIME oSysTime;
    parseTime(strStartTime.GetBuffer(), oSysTime);
    m_oBeginTime.SetTime(oSysTime);
    m_oBeginDate.SetTime(oSysTime);

    parseTime(strEndTime.GetBuffer(), oSysTime);
    m_oEndTime.SetTime(oSysTime);
    m_oEndDate.SetTime(oSysTime);
    UpdateData(FALSE);
    *pResult = 0;
}

INT32 CMenuPlayBack::parseTime(IN CHAR * pszTime, OUT SYSTEMTIME &oSysTime)
{
    if (NULL == pszTime)
    {
        return NETDEV_E_FAILED;
    }

    oSysTime.wYear = atoi(pszTime);
    oSysTime.wMonth = atoi(pszTime + 5);
    oSysTime.wDay = atoi(pszTime + 8);
    oSysTime.wHour = atoi(pszTime + 11);
    oSysTime.wMinute = atoi(pszTime + 14);
    oSysTime.wSecond = atoi(pszTime + 17);

    return NETDEV_E_SUCCEED;
}

void CMenuPlayBack::OnNMReleasedcaptureSliderPlayProgress(NMHDR *pNMHDR, LRESULT *pResult)
{
    CSliderCtrl *pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_PLAY_PROGRESS);
    INT64 dwTimePoint = pSlidCtrl->GetPos();
    LPVOID pPlayHandle;
    if(FALSE == GetPlayHandle(&pPlayHandle))
    {
        return;
    }

    BOOL bRet = NETDEV_PlayBackControl(pPlayHandle, NETDEV_PLAY_CTRL_SETPLAYTIME, &dwTimePoint);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Set play time");
    }
    else
    {
        NETDEMO_LOG_SUCC(NULL, "Set play time");
    }

    SetTimer(PLAYBACK_TIME_ID, 500, NULL);
    SetTimer(DOWNLOAD_TIME_ID, 1000, NULL);

    *pResult = 0;

    return;
}
void CMenuPlayBack::OnNMCustomdrawSliderPlayProgress(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
    LPVOID pPlayHandle;

    if(FALSE == GetPlayHandle(&pPlayHandle))
    {
        m_oCurPlayTime = "0000/00/00 00:00:00";
        UpdateData(FALSE);
        return;
    }

    CSliderCtrl *pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_PLAY_PROGRESS);
    CString playTimePoint = GetTime(pSlidCtrl->GetPos()).Trim();
    m_oCurPlayTime = playTimePoint.Trim();

    INT64 iPlayTime = pSlidCtrl->GetPos();
    updateTime(m_oastUpdateInfo[m_dwCurScreen], iPlayTime, FALSE);

    UpdateData(FALSE);
    *pResult = 0;
}

void CMenuPlayBack::OnBnClickedButtonGetrecorddaynums()
{
    // TODO: ?¨²¡ä?¨¬¨ª?¨®???t¨ª¡§?a¡ä|¨¤¨ª3¨¬D¨°¡ä¨²??
    LPVOID lpHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChlID = ga_pMainDlg->GetChlID();

    UINT32 dwDayNums = 0;
    BOOL bRet = NETDEV_GetVideoDayNums(lpHandle, dwChlID , &dwDayNums);
    if (TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Getrecorddaynums");
        return;
    }
    CHAR szBuf[64];
    _snprintf(szBuf, sizeof(szBuf), "%d", dwDayNums);
     m_strRecodeDayNums = szBuf;

     UpdateData(FALSE);
    NETDEMO_LOG_SUCC(NULL, "Getrecorddaynums");
}
