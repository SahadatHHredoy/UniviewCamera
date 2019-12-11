
#include "StdAfx.h"
#include "NetDemo.h"
#include "ScreenPannel.h"
#include "NetDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScreenPannel class

CScreenPannel::CScreenPannel()
{
}

CScreenPannel::~CScreenPannel()
{
    // remove all pages
    while(!m_PageList.IsEmpty())
    {
        m_PageList.RemoveHead();
    }
}


BEGIN_MESSAGE_MAP(CScreenPannel, CWnd)
    //{{AFX_MSG_MAP(CScreenPannel)
    ON_WM_PAINT()
    ON_WM_ERASEBKGND()
    ON_WM_CREATE()
    ON_WM_DESTROY()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CScreenPannel member functions
void CScreenPannel::OnPaint() 
{
    CPaintDC dc(this); // device context for painting
    
    // TODO: Add your message handler code here
    UpdateWnd();
    // Do not call CWnd::OnPaint() for painting messages
}

BOOL CScreenPannel::OnEraseBkgnd(CDC* pDC) 
{
    // TODO: Add your message handler code here and/or call default
    CRect rt;
    GetClientRect(&rt);
    CBrush br;
    br.CreateSolidBrush(RGB(192,192,192));
    pDC->FillRect(&rt,&br);

    return TRUE;
    return CWnd::OnEraseBkgnd(pDC);
}

int CScreenPannel::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    if (CWnd::OnCreate(lpCreateStruct) == -1)
        return NETDEMO_E_FAILED;
    
    // TODO: Add your specialized creation code here
    for(int i = 0; i < NETDEMO_MAX_SCREENNUM; i++)
    {
        m_wndVideo[i].Create(
            NULL, 
            NULL, 
            WS_VISIBLE | WS_CHILD,
            CRect(0, 0, 0, 0),
            this,
            1979,
            NULL);

        m_wndVideo[i].SetWinID(i);
        
        AddPage(&m_wndVideo[i]);
    }

    SetActivePage(&m_wndVideo[0], TRUE);
    SetDrawActivePage(TRUE, RGB(248,5,182), RGB(248,5,182));

    return 0;
}

int CScreenPannel::SetShowPlayWin(int nMain, int nSub)
{
    if (nSub < 0 || nSub > NETDEMO_MAX_SCREENNUM)
    {
        nSub = 0;
    }

    int nNum = 16;
    int nBegin = 0;
    switch(nMain) 
    {
    case NETDEMO_SPLIT1:
        nNum = 1;
        nBegin = nSub;
        break;
    case NETDEMO_SPLIT4:
        nNum = 4;
        if (nSub >= 12)
        {
            nBegin = 12;
        }
        else if (nSub >= 8)
        {
            nBegin = 8;
        }
        else if (nSub >= 4)
        {
            nBegin = 4;
        }
        else
        {
            nBegin = 0;
        }

        break;
    case NETDEMO_SPLIT9:
        nNum = 9;
        if (nSub >= 10)
        {
            nBegin = 7;
        }
        else
        {
            nBegin = 0;
        }
        break;
    case NETDEMO_SPLIT16:
        nNum = 16;
        nBegin = 0;
        break;
    default:
        break;
    }

    CList<CWnd*, CWnd*> oTmpList;
    POSITION pos = m_PageList.GetHeadPosition();
    while(pos != NULL)
    {
        CWnd* pWnd = m_PageList.GetNext(pos);
        if (pWnd)
        {
            oTmpList.AddTail(pWnd);
        }
    }

    m_PageList.RemoveAll();

    for(int i=nBegin; i < (nBegin+nNum); i++)
    {
        AddPage(&m_wndVideo[i], TRUE);
    }

    SetActivePage(&m_wndVideo[nSub], TRUE);

    pos = oTmpList.GetHeadPosition();
    while(pos != NULL)
    {
        CWnd* pWnd = oTmpList.GetNext(pos);
        if (pWnd)
        {
            pWnd->ShowWindow(SW_HIDE);
        }
    }

    oTmpList.RemoveAll();

    return m_PageList.GetCount();
}

void CScreenPannel::OnDestroy() 
{
    CWnd::OnDestroy();

    for(int i=0; i < NETDEMO_MAX_SCREENNUM; i++)
    {
        m_wndVideo[0].DestroyWindow();
    }

    return;
}

CWnd * CScreenPannel::GetPage(int nIndex)
{
    if (nIndex >= 0 && nIndex < NETDEMO_MAX_SCREENNUM)
    {
        return &m_wndVideo[nIndex];
    }

    return NULL;
}
