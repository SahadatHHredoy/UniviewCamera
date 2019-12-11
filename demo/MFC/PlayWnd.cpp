
#include "StdAfx.h"
#include "netdemo.h"
#include "PlayWnd.h"
#include "NetDemoDlg.h"
#include "ScreenPannel.h"
#include "netdemo.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CPlayWnd::CPlayWnd()
    :m_nWndID(0)
{
    InitializeCriticalSection(&m_cs);
    memset(&m_stplitInfo, 0, sizeof(m_stplitInfo));
    m_nPreSplit = 0;

    m_bSaveLocalRecord = FALSE;

    m_bShortDelay = TRUE;
    m_bFluent = FALSE;

    m_bOpenMic = FALSE;
    m_bOpenSound = FALSE;
    m_dwMicVolume = 0;
    m_dwSoundVolume = 0;
    m_bRouteRecording = FALSE;
    m_dwSpeed = IMCP_RM_SCALE_1_FORWARD;
    m_lRemainTime = 0;

    m_bDrawRect = FALSE;
    
    m_bOpen3D = FALSE;
    m_bOpenDZ = FALSE;
    m_oPen.CreatePen(PS_SOLID,1,RGB(234,23,53));
}

BEGIN_MESSAGE_MAP(CPlayWnd, CWnd)
    //{{AFX_MSG_MAP(CPlayWnd)
    ON_WM_ERASEBKGND()
    ON_WM_CREATE()
    ON_WM_CONTEXTMENU()
    //}}AFX_MSG_MAP
    ON_COMMAND_RANGE(WM_VIDEO_MENU_BASE, WM_VIDEO_MENU_END, OnVideoMenu)
    ON_MESSAGE(WM_VIDEO_REPAINT, OnRepaintWnd)
    //}}AFX_MSG_MAP
    ON_COMMAND(ID_PALYRIGHTCLICK_FULLSCREEN, &CPlayWnd::OnPlayRClickFullscreen)
    ON_COMMAND(ID_PALYRIGHTCLICK_MULITSCREEN, &CPlayWnd::OnPlayRClickMulitscreen)
    ON_COMMAND(ID_PALYRIGHTCLICK_AUTOADJUST, &CPlayWnd::OnPlayRClickAutoAdjust)
    ON_COMMAND(ID_PALY_RIGHTCLICK_STOPVIDEO, &CPlayWnd::OnPlayRClickClose)
    ON_COMMAND(ID_PALY_RCLICK_KEYFRAME, &CPlayWnd::OnPlayRClickMakeKeyFrame)
    ON_COMMAND(ID_PALY_RIGHTCLICK_NETDELAY_REAL, &CPlayWnd::OnPlayRClickNetRealTime)
    ON_COMMAND(ID_PALY_RIGHTCLICK_NETDELAY_FLUENT, &CPlayWnd::OnPlayRClickNetFluey)
    ON_COMMAND(ID_PALY_RIGHTCLICK_TALK, &CPlayWnd::OnPlayRClickTalk)
    ON_UPDATE_COMMAND_UI(ID_PALY_RIGHTCLICK_TALK, &CPlayWnd::OnUpdatePalyRightclickTalk)
    ON_COMMAND(ID_PALYRIGHTCLICK_STOPALL, &CPlayWnd::OnPlayRClickCloseAll)
    ON_COMMAND(ID_PALYRIGHTCLICK_CAMERAINFO, &CPlayWnd::OnPlayRClickCameraInfo)
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
    ON_WM_PAINT()
    ON_COMMAND(ID_PALYRIGHTCLICK_DZ, &CPlayWnd::OnPalyrightclickDz)
    ON_COMMAND(ID_PALYRIGHTCLICK_3DPOSITION, &CPlayWnd::OnPalyrightclick3dposition)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlayWnd message handlers
BOOL CPlayWnd::OnEraseBkgnd(CDC* pDC) 
{
    // TODO: Add your message handler code here and/or call default
    CRect rt;
    GetClientRect(&rt);
    CBrush br;
    br.CreateSolidBrush(VIDEO_BACK_COLOR);
    pDC->FillRect(&rt,&br);

    return CWnd::OnEraseBkgnd(pDC);
}

LRESULT CPlayWnd::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
    // TODO: Add your specialized code here and/or call the base class
    CScreenPannel *pContainer = (CScreenPannel *)GetParent();
    if (NETDEMO_SPLIT_TYPE_PLAY_BACK == m_stplitInfo.emType)
    {
        switch(message)
        {
        case WM_LBUTTONDOWN:
        case WM_RBUTTONDOWN:
            pContainer->SetActivePage(this);
            {
                CNetDemoDlg * pMainWnd = (CNetDemoDlg *)(AfxGetMainWnd());
                if (pMainWnd)
                {
                    pMainWnd->SetCurWindId(m_nWndID);
                }
            }
            ga_pMainDlg->m_oDlgPlayback.SendMessage(WM_CLICK_PLAYBACK_WND,1,(LPARAM)this);
            break;
        case WM_LBUTTONDBLCLK:
            {
                CNetDemoDlg * pMainWnd = (CNetDemoDlg *)(AfxGetMainWnd());
                BOOL bMulti = pContainer->GetMultiScreen();
                //    int nCnt = pContainer->GetCount();
                pContainer->SetMultiScreen(!bMulti);

                if (TRUE == bMulti)
                {
                    m_nPreSplit = pMainWnd->GetSplit();
                    //            pMainWnd->SetSplit(SPLIT1);
                }
                else
                {
                    //            pMainWnd->SetSplit(m_nPreSplit);
                }
            }
            break;
        default:
            break;
        }
    }
    else
    {
        if(pContainer)
        {
            switch(message)
            {
            case WM_LBUTTONDOWN:
            case WM_RBUTTONDOWN:
                pContainer->SetActivePage(this);
                {
                    CNetDemoDlg * pMainWnd = (CNetDemoDlg *)(AfxGetMainWnd());
                    if (pMainWnd)
                    {
                        pMainWnd->SetCurWindId(m_nWndID);
                    }
                }
                ga_pMainDlg->SendMessage(WM_CLICK_REALPLAY_WND,1,(LPARAM)this);
                break;
            case WM_LBUTTONDBLCLK:
                {
                    CNetDemoDlg * pMainWnd = (CNetDemoDlg *)(AfxGetMainWnd());
                    BOOL bMulti = pContainer->GetMultiScreen();
                    //    int nCnt = pContainer->GetCount();
                    pContainer->SetMultiScreen(!bMulti);

                    if (TRUE == bMulti)
                    {
                        m_nPreSplit = pMainWnd->GetSplit();
                        ga_pMainDlg->SetSplit(NETDEMO_SPLIT1);
                    }
                    else
                    {
                        ga_pMainDlg->SetSplit(m_nPreSplit);
                    }
                }
                break;
            default:
                break;
            }
        }
    }

    return CWnd::DefWindowProc(message, wParam, lParam);
}

void CPlayWnd::OnContextMenu(CWnd* pWnd, CPoint point) 
{
    // TODO: Add your message handler code here
    CScreenPannel *pContainer = (CScreenPannel *)GetParent();
    pContainer->SetActivePage(this);

    CMenu menu;
    menu.LoadMenu(IDR_MENU_LIVE_VIEW_RIGHT_MENU);
    
    menu.CheckMenuItem(ID_PALYRIGHTCLICK_FULLSCREEN, MF_BYCOMMAND | (pContainer->GetFullScreen() ? MF_CHECKED : MF_UNCHECKED));
    menu.CheckMenuItem(ID_PALYRIGHTCLICK_MULITSCREEN, MF_BYCOMMAND | (pContainer->GetMultiScreen() ? MF_CHECKED : MF_UNCHECKED));
    menu.CheckMenuItem(ID_PALYRIGHTCLICK_AUTOADJUST, MF_BYCOMMAND | (pContainer->GetAutoAdjustPos() ? MF_CHECKED : MF_UNCHECKED));
    menu.CheckMenuItem(ID_PALY_RIGHTCLICK_NETDELAY_REAL, MF_BYCOMMAND | (m_bShortDelay ? MF_CHECKED : MF_UNCHECKED));
    menu.CheckMenuItem(ID_PALY_RIGHTCLICK_NETDELAY_FLUENT, MF_BYCOMMAND |  (m_bFluent? MF_CHECKED : MF_UNCHECKED));
    menu.CheckMenuItem(ID_PALY_RIGHTCLICK_TALK, MF_BYCOMMAND |  (pContainer->GetTalkState()? MF_CHECKED : MF_UNCHECKED));
    menu.CheckMenuItem(ID_PALYRIGHTCLICK_DZ, MF_BYCOMMAND |  (m_bOpenDZ? MF_CHECKED : MF_UNCHECKED));
    menu.CheckMenuItem(ID_PALYRIGHTCLICK_3DPOSITION, MF_BYCOMMAND |  (m_bOpen3D? MF_CHECKED : MF_UNCHECKED));
    if (pContainer->GetTalkState())
    {
         if (pContainer->GetTalkWinID() !=  GetWinID())
         {
             menu.EnableMenuItem(ID_PALY_RIGHTCLICK_TALK,TRUE);
         }
    }

    if (NETDEMO_SPLIT_TYPE_PLAY_BACK != m_stplitInfo.emType)
    {
        menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN,point.x ,point.y,this);
    }

    return;
}

void CPlayWnd::OnVideoMenu(UINT nID)
{
    CScreenPannel *pContainer = (CScreenPannel *)GetParent();
    switch(nID)
    {
    case WM_VIDEO_MENU_FULLSCREEN:
        pContainer->SetFullScreen(!pContainer->GetFullScreen());
        break;
    case WM_VIDEO_MENU_MULTISCREEN:
        {
//             CNetSDKDemoDlg * pMainWnd = (CNetSDKDemoDlg *)(AfxGetMainWnd());
//                 BOOL bMulti = pContainer->GetMultiScreen();
//                 //    int nCnt = pContainer->GetCount();
//                 pContainer->SetMultiScreen(!bMulti);
//                 
//                 if (TRUE == bMulti)
//                 {
//                     m_nPreSplit = pMainWnd->GetSplit();
//                     pMainWnd->SetSplit(SPLIT1);
//                 }
//                 else
//                 {
//                     pMainWnd->SetSplit(m_nPreSplit);
//                 }
//         //        pContainer->SetMultiScreen(!pContainer->GetMultiScreen());
            break;
        }
        
    case WM_VIDEO_MENU_AUTOADJUST:
        pContainer->SetAutoAdjustPos(!pContainer->GetAutoAdjustPos());
        break;
    case WM_VIDEO_MENU_PRINTSCREEN:
        break;
    case WM_VIDEO_MENU_RECORDVIDEO:
        break;
    case WM_VIDEO_MENU_EXITDECODE:
        //pContainer->SetFullScreen(FALSE);
        break;
    default:
        break;
    }
}

BOOL CPlayWnd::GetSplitInfo(NETDEMO_SPLITINFO_NODE* pstNodeInfo)
{
    if (NULL == pstNodeInfo)
    {
        return FALSE;
    }

    EnterCriticalSection(&m_cs);
    memcpy(pstNodeInfo, &m_stplitInfo, sizeof(NETDEMO_SPLITINFO_NODE));
    LeaveCriticalSection(&m_cs);

    return TRUE;
}

BOOL CPlayWnd::SetSplitInfo(NETDEMO_SPLITINFO_NODE* info)
{
    if (!info)
    {
        return FALSE;
    }

    EnterCriticalSection(&m_cs);
    memcpy(&m_stplitInfo, info, sizeof(NETDEMO_SPLITINFO_NODE));
    LeaveCriticalSection(&m_cs);

    return TRUE;
}

void CPlayWnd::SetSplitHandle(LPVOID dwHandle)
{
    EnterCriticalSection(&m_cs);
    m_stplitInfo.iHandle = dwHandle;
    LeaveCriticalSection(&m_cs);

    return;
}

void CPlayWnd::SetSplitType(NETDEMO_SPLITTYPE type)
{
    EnterCriticalSection(&m_cs);
    m_stplitInfo.emType = type;
    LeaveCriticalSection(&m_cs);

    return;
}

LPVOID CPlayWnd::GetSplitHandle()
{
    EnterCriticalSection(&m_cs);
    LPVOID pHandle = m_stplitInfo.iHandle;
    LeaveCriticalSection(&m_cs);

    return pHandle;
}


void CPlayWnd::SetSplitCBFlag_Real(int nFlag)
{
    EnterCriticalSection(&m_cs);
    m_stplitInfo.bSaveData = nFlag;
    LeaveCriticalSection(&m_cs);

    return;
}

LRESULT CPlayWnd::OnRepaintWnd(WPARAM wParam, LPARAM lParam)
{
    Invalidate();
    return 0;
}

BOOL CPlayWnd::DestroyWindow() 
{
    DeleteCriticalSection(&m_cs);
    return CWnd::DestroyWindow();
}


void CPlayWnd::OnPlayRClickFullscreen()
{
    CScreenPannel *pContainer = (CScreenPannel *)GetParent();
    pContainer->SetFullScreen(!pContainer->GetFullScreen());

    return;
}

void CPlayWnd::OnPlayRClickMulitscreen()
{
    CScreenPannel *pContainer = (CScreenPannel *)GetParent();
    CNetDemoDlg * pMainWnd = (CNetDemoDlg *)(AfxGetMainWnd());
    BOOL bMulti = pContainer->GetMultiScreen();
    pContainer->SetMultiScreen(!bMulti);

    if (TRUE == bMulti)
    {
        m_nPreSplit = pMainWnd->GetSplit();
        pMainWnd->SetMultiScreen(NETDEMO_SPLIT1);
        pMainWnd->SetSplit(NETDEMO_SPLIT1);
    }
    else
    {
        pMainWnd->SetSplit(m_nPreSplit);
    }

    return;
}

void CPlayWnd::OnPlayRClickAutoAdjust()
{
    CScreenPannel *pContainer = (CScreenPannel *)GetParent();
    pContainer->SetAutoAdjustPos(!pContainer->GetAutoAdjustPos());

    return;
}

void CPlayWnd::OnPlayRClickClose()
{
    ga_pMainDlg->StopPlaySelectedDevice();

    return;
}

void CPlayWnd::SetLocalRecordState(BOOL state)
{
    m_bSaveLocalRecord = state;

    return;
}

BOOL CPlayWnd::GetLocalRecordState()
{
    return m_bSaveLocalRecord;
}

void CPlayWnd::OnPlayRClickMakeKeyFrame()
{
    if (( 0> m_stplitInfo.dwDevIndex ) || (0>m_stplitInfo.dwChnIndex))
    {
        return;
    }

    ga_pMainDlg->MakeKeyFrame(m_stplitInfo.dwDevIndex, m_stplitInfo.dwChnIndex + 1);
    
    return;
}

void CPlayWnd::OnPlayRClickNetRealTime()
{
    ga_pMainDlg->SetNetPlayMode(NETDEV_PICTURE_REAL);

    m_bShortDelay = TRUE;
    m_bFluent = FALSE;

    return;
}

void CPlayWnd::OnPlayRClickNetFluey()
{
    ga_pMainDlg->SetNetPlayMode(NETDEV_PICTURE_FLUENCY);
    m_bShortDelay = FALSE;
    m_bFluent = TRUE;

    return;
}

void CPlayWnd::OnPlayRClickTalk()
{
    CScreenPannel *pContainer = (CScreenPannel *)GetParent();
    if (pContainer->GetTalkState())
    {
        if (ga_pMainDlg->StopTalk())
        {
            pContainer->SetTalkState(FALSE);
        }
        else
        {
            pContainer->SetTalkState(TRUE);
        } 
    }
    else
    {
        if (ga_pMainDlg->StartTwoWayAudio())
        {
            pContainer->SetTalkWinID(m_nWndID);
            pContainer->SetTalkState(TRUE);
        }
        else
        {
            pContainer->SetTalkWinID(-1);
            pContainer->SetTalkState(FALSE);
        }
    }

    return;
}

void CPlayWnd::OnUpdatePalyRightclickTalk(CCmdUI *pCmdUI)
{
    //pCmdUI->Enable(FALSE);
}

void CPlayWnd::SetMicState(BOOL state)
{
    m_bOpenMic = state;

    return;
}

BOOL CPlayWnd::GetMicState()
{
    return m_bOpenMic;
}

void CPlayWnd::SetMicVolume(INT32 volume)
{
    m_dwMicVolume = volume;

    return;
}

INT32 CPlayWnd::GetMicVolume()
{
    return m_dwMicVolume;
}

void CPlayWnd::SetSoundState(BOOL state)
{
    m_bOpenSound = state;

    return;
}

BOOL CPlayWnd::GetSoundState()
{
    return m_bOpenSound;
}

void CPlayWnd::SetSoundVolume(INT32 volume)
{
    m_dwSoundVolume = volume;

    return;
}

INT32 CPlayWnd::GetSoundVolume()
{
    return m_dwSoundVolume;
}

void CPlayWnd::SetSpeed(INT32 enSpeed)
{
    m_dwSpeed = enSpeed;
}

INT32 CPlayWnd::GetSpeed()
{
    return m_dwSpeed;
}

void CPlayWnd::SetRemainTime(INT64 remainTime)
{
    m_lRemainTime = remainTime;
}
INT64 CPlayWnd::GetRemainTime()
{
    return m_lRemainTime;
}

HTREEITEM CPlayWnd::GetDevTreePos()
{
    return m_stplitInfo.hDevTreePos;
}

void CPlayWnd::SetDevTreePos(HTREEITEM ItemPos)
{
    m_stplitInfo.hDevTreePos = ItemPos;

    return;
}


BOOL CPlayWnd::GetTrackingState()
{
    return m_bTracking;
}

void CPlayWnd::SetTrackingState(BOOL state)
{
    m_bTracking = state;

    return;
}

void CPlayWnd::SetDevIndex(INT32 dwDevIndex)
{
    m_stplitInfo.dwDevIndex = dwDevIndex;

    return;
}

INT32 CPlayWnd::GetDevIndex()
{
    return m_stplitInfo.dwDevIndex;
}

void CPlayWnd::SetChnID(INT32 dwChnID)
{
    m_stplitInfo.dwChnIndex = dwChnID;

    return;
}

INT32 CPlayWnd::GetChnID()
{
    return m_stplitInfo.dwChnIndex;
}

void CPlayWnd::OnPlayRClickCloseAll()
{
    ga_pMainDlg->CloseAll();

    return;
}

void CPlayWnd::setUpdateInfo(const NETDEMO_UPDATE_TIME_INFO& stUpdateInfo)
{
    m_stUpdateInfo = stUpdateInfo;
}

void CPlayWnd::getUpdateInfo(NETDEMO_UPDATE_TIME_INFO& stUpdateInfo)
{
    memcpy(&stUpdateInfo, &m_stUpdateInfo, sizeof(stUpdateInfo));
    return;
}

void CPlayWnd::setPauseState(BOOL bPauseState)
{
    m_bPauseState = bPauseState;
}

BOOL CPlayWnd::getPauseState()
{
    return m_bPauseState;
}

void CPlayWnd::setDateTime(const SYSTEMTIME& oDateBegin,
                     const SYSTEMTIME& oTimeBegin,
                     const SYSTEMTIME& oDateEnd,
                     const SYSTEMTIME& oTimeEnd)
{
    m_oDateBegin = oDateBegin;
    m_oTimeBegin = oTimeBegin;
    m_oDateEnd = oDateEnd;
    m_oTimeEnd = oTimeEnd;
}

void CPlayWnd::getDateTime(SYSTEMTIME& oDateBegin,
                     SYSTEMTIME& oTimeBegin,
                     SYSTEMTIME& oDateEnd,
                     SYSTEMTIME& oTimeEnd)
{
    oDateBegin = m_oDateBegin;
    oTimeBegin = m_oTimeBegin;
    oDateEnd = m_oDateEnd;
    oTimeEnd = m_oTimeEnd;

    return;
}

void CPlayWnd::OnPlayRClickCameraInfo()
{
    ga_pMainDlg->GetCameraInfo();

    return;
}

void CPlayWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
    m_nStartPos = point;
    m_bDrawRect = TRUE;

    CWnd::OnLButtonDown(nFlags, point);

    return;
}

void CPlayWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
    m_nEndPos = point;
    m_bDrawRect = FALSE;
    Invalidate();
    
    if (m_bOpen3D)
    {
        Set3DPosition();
    }
    if (m_bOpenDZ)
    {
        SetDigitalZoom(TRUE);
    }

    CWnd::OnLButtonUp(nFlags, point);

    return;
}

void CPlayWnd::OnMouseMove(UINT nFlags, CPoint point)
{
    m_nEndPos = point;

    if (m_bDrawRect)
    {
//      CRect oRect;
// 
//      oRect.top = m_nStartPos.y + 5;
//      oRect.left =m_nStartPos.x + 5;
//      oRect.bottom = m_nEndPos.y - 5;
//      oRect.right = m_nEndPos.x - 5;
// 
//      InvalidateRect(oRect);

        CClientDC dc(this);
        

        CPen *pOldPen=dc.SelectObject(&m_oPen);

        CBrush *pBrush=CBrush::FromHandle((HBRUSH)

        GetStockObject(NULL_BRUSH));

        CBrush *pOldBrush=dc.SelectObject(pBrush);

        dc.Rectangle(CRect(m_nStartPos,m_nEndPos));

        dc.SelectObject(pOldPen);

        dc.SelectObject(pOldBrush);

        m_nOldPos = m_nEndPos;
    }

    CWnd::OnMouseMove(nFlags, point);

    return;
}

void CPlayWnd::OnPaint()
{
    CPaintDC dc(this); // device context for painting

    return;
}

void CPlayWnd::OnPalyrightclickDz()
{
    if (NULL == m_stplitInfo.iHandle)
    {
        return;
    }

    if (TRUE == m_bOpenDZ)
    {
        m_bOpenDZ =  FALSE;
        ga_pMainDlg->NETSDK_SetActiveWndDZ(NULL,FALSE);
    }
    else
    {
        m_bOpenDZ = TRUE;
    }

    return;
}

void CPlayWnd::OnPalyrightclick3dposition()
{
    if (NULL == m_stplitInfo.iHandle)
    {
        return;
    }

    if (TRUE == m_bOpen3D)
    {
        m_bOpen3D =  FALSE;
    }
    else
    {
       m_bOpen3D = TRUE;
    }

    return;
}


void CPlayWnd::Set3DPosition()
{
    CRect oDstRt;
    if (TRUE == ConvertRectToNetSDK(oDstRt))
    {
       ga_pMainDlg->NETSDK_SetActive3DPostion(oDstRt);
    }

    return;
}

void CPlayWnd::SetDigitalZoom(BOOL bAction)
{
    CRect oDstRt;
    if ( TRUE == ConvertRectToNetSDK(oDstRt))
    {
        ga_pMainDlg->NETSDK_SetActiveWndDZ(oDstRt,bAction);
    }

    return;
}

bool CPlayWnd::ConvertRectToNetSDK(CRect &dstRect)
{
    CRect oSrcRt;
    GetClientRect(&oSrcRt);

    dstRect.left = m_nStartPos.x;
    dstRect.right = m_nEndPos.x;
    dstRect.top = m_nStartPos.y;
    dstRect.bottom = m_nEndPos.y;


    dstRect.left = (dstRect.left*10000)/oSrcRt.right;
    dstRect.right = (dstRect.right*10000)/oSrcRt.right;
    dstRect.top = (dstRect.top*10000)/oSrcRt.bottom;
    dstRect.bottom = (dstRect.bottom*10000)/oSrcRt.bottom;

    int nIntervalX = m_nStartPos.x < m_nEndPos.x?(m_nEndPos.x - m_nStartPos.x):(m_nStartPos.x - m_nEndPos.x);
    int nIntervalY = m_nStartPos.y < m_nEndPos.y?(m_nEndPos.y - m_nStartPos.y):(m_nStartPos.y - m_nEndPos.y);
    if ( nIntervalX < 20 || nIntervalY <20)
    {
        return FALSE;
    }

    return TRUE;
}

