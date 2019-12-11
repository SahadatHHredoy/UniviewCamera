
#if !defined(AFX_BSWNDCONTAINER_H__73CB8E46_8ED9_4C36_BA91_29D5F5BB05DE__INCLUDED_)
#define AFX_BSWNDCONTAINER_H__73CB8E46_8ED9_4C36_BA91_29D5F5BB05DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BSWndContainer.h : header file
//

#define WINDOW_SPACE  1

/////////////////////////////////////////////////////////////////////////////
// CBSWndContainer window
#include <afxtempl.h>

class CBSWndContainer : public CWnd
{
// Construction
public:
    CBSWndContainer();

// Attributes
public:

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CBSWndContainer)
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~CBSWndContainer();

    // Generated message map functions
protected:
    //{{AFX_MSG(CBSWndContainer)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////////////////////////
// public interface member
public:

    ///////////////////////////////////////////////////
    BOOL Create( LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);

    BOOL AddPage(CWnd *pWnd, BOOL bRepaint = TRUE);

    CWnd *DelPage(CWnd *pWnd);

    CWnd *DelPage();

    void SetActivePage(CWnd *pWnd, BOOL bRepaint = TRUE);

    void SetNextActivePage(BOOL bRepaint = TRUE);

    CWnd *GetActivePage();

    CWnd *GetNextPage(CWnd *pWnd);

    CWnd *GetPrevPage(CWnd *pWnd);

    CWnd *GetPage(int nIndex);

    int GetCount() const;

    CWnd *GetTailPage();

    virtual void UpdateWnd();

    void SetFullScreen(BOOL bFlag);
    BOOL GetFullScreen();

    void SetMultiScreen(BOOL bFlag);
    BOOL GetMultiScreen();

    void SetAutoAdjustPos(BOOL bFlag);
    BOOL GetAutoAdjustPos();

    void SetDrawActivePage(BOOL bFlag,COLORREF clrTopLeft=RGB(255, 0, 0), COLORREF clrBottomRight=RGB(255, 0, 0));
    BOOL GetDrawActivePage();

    void SetShowPortion(int nPortion=100);
    int  GetShowPortion();

    void SetTalkWinID(INT32 dwWinID);
    INT32 GetTalkWinID();

    void SetTalkState(BOOL state);
    BOOL GetTalkState();
//////////////////////////////////////////////////////////////////////////////////////////////////////
// protected member for derived class
protected:
    
    CList<CWnd *,CWnd *> m_PageList;
    CWnd *m_pActivePage;
    BOOL m_bFullScreen;
    BOOL m_bMultiScreen;
    BOOL m_bAutoAdjustPos;
    BOOL m_bDrawActive;
    INT32 m_dwShowPortion; 

    WINDOWPLACEMENT m_OldWndPlacement; 
    CRect m_oFullScreenRect;

    BOOL m_bTalkSate;
    INT32 m_dwTalkWinID;

// private member for inter user
private:

    int UpdateList();

    virtual void CalcPageRect(LPRECT lpRect,int nIndex,int nPageCount);

    void AdjustRect(LPRECT lpRect);

    void GetShowRect(LPRECT lpRect);

    void DrawActivePage(BOOL bFlag);

    COLORREF m_clrTopLeft;
    COLORREF m_clrBottomRight;

    WINDOWPLACEMENT _temppl;        //window's placement
    CWnd *            _tempparent;    //window's parent
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BSWNDCONTAINER_H__73CB8E46_8ED9_4C36_BA91_29D5F5BB05DE__INCLUDED_)
