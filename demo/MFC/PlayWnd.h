#if !defined(AFX_PLAYWND_H__E6AAF690_8D19_43AC_AE4E_E64F2412D706__INCLUDED_)
#define AFX_PLAYWND_H__E6AAF690_8D19_43AC_AE4E_E64F2412D706__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PlayWnd.h : header file
//

#include "GeneralDef.h"

/////////////////////////
//    POPUP MENU ID DEFINE
//    KeyColor

//#define        VIDEO_BACK_COLOR    RGB(111,104,160)
//#define        VIDEO_BACK_COLOR    RGB(100,100,160)
#define        VIDEO_BACK_COLOR    RGB(0,0,0)

typedef enum tagRMPlayScale
{
    IMCP_RM_SCALE_16_BACKWARD = 0,              /**< 16倍速后退播放 */
    IMCP_RM_SCALE_8_BACKWARD,                   /**< 8倍速后退播放 */
    IMCP_RM_SCALE_4_BACKWARD,                   /**< 4倍速后退播放 */
    IMCP_RM_SCALE_2_BACKWARD,                   /**< 2倍速后退播放 */
    IMCP_RM_SCALE_1_BACKWARD,                   /**< 正常速度后退播放 */
    IMCP_RM_SCALE_HALF_BACKWARD,                /**< 1/2倍速后退播放 */
    IMCP_RM_SCALE_QUARTER_BACKWARD,             /**< 1/4倍速后退播放 */
    IMCP_RM_SCALE_QUARTER_FORWARD,             /**< 1/4倍速后退播放 */
    IMCP_RM_SCALE_HALF_FORWARD,                 /**< 1/2倍速播放 */
    IMCP_RM_SCALE_1_FORWARD,                    /**< 正常速度前进播放 */
    IMCP_RM_SCALE_2_FORWARD,                    /**< 2倍速前进播放 */
    IMCP_RM_SCALE_4_FORWARD,                    /**< 4倍速前进播放 */
    IMCP_RM_SCALE_8_FORWARD,                    /**< 8倍速前进播放 */
    IMCP_RM_SCALE_16_FORWARD,                   /**< 16倍速前进播放 */

    IMCP_RM_SCALE_2_FORWARD_IFRAME,             /**< 2倍速前进播放(I帧) */
    IMCP_RM_SCALE_4_FORWARD_IFRAME,             /**< 4倍速前进播放(I帧) */
    IMCP_RM_SCALE_8_FORWARD_IFRAME,             /**< 8倍速前进播放(I帧) */
    IMCP_RM_SCALE_16_FORWARD_IFRAME,            /**< 16倍速前进播放(I帧) */

    IMCP_RM_SCALE_2_BACKWARD_IFRAME,            /**< 2倍速后退播放(I帧) */
    IMCP_RM_SCALE_4_BACKWARD_IFRAME,            /**< 4倍速后退播放(I帧) */
    IMCP_RM_SCALE_8_BACKWARD_IFRAME,            /**< 8倍速后退播放(I帧) */
    IMCP_RM_SCALE_16_BACKWARD_IFRAME,           /**< 16倍速后退播放(I帧) */

    IMCP_RM_SCALE_INTELLIGENT_FORWARD,          /**< 智能播放 */
    IMCP_RM_SCALE_1_FRAME_FORWARD,              /**< 单帧前进 */
    IMCP_RM_SCALE_I_FRAME_BACKWARD,             /**< 单帧(I帧)后退> */
    IMCP_RM_SCALE_BUT
}IMCP_RM_PLAY_SCALE_E;

/////////////////////////////////////////////////////////////////////////////
// CPlayWnd dialog
class CPlayWnd : public CWnd
{
// Construction
public:
    CPlayWnd();   // standard constructor


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CPlayWnd)
    public:
    virtual BOOL DestroyWindow();
    protected:
    virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
    //}}AFX_VIRTUAL
    afx_msg void OnVideoMenu(UINT nID);
    afx_msg LRESULT OnRepaintWnd(WPARAM wParam, LPARAM lParam);

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CPlayWnd)
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
    afx_msg void OnDestroy();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

public:
    void SetWinID(int ID) {m_nWndID = ID;}
    int  GetWinID(void){return m_nWndID;}

    //get split info 
    BOOL GetSplitInfo(NETDEMO_SPLITINFO_NODE* info);
    //set split info -- copy whole structure
    BOOL            SetSplitInfo(NETDEMO_SPLITINFO_NODE* info);
    //set split info -- channel handle
    void            SetSplitHandle(LPVOID dwHandle);
    void            SetSplitType(NETDEMO_SPLITTYPE type);

    LPVOID          GetSplitHandle();
    //set split info -- flages of call-back-data saving 
    void            SetSplitCBFlag_Real(int nFlag);
    
    void SetLocalRecordState(BOOL state);
    BOOL GetLocalRecordState();

    void SetMicState(BOOL state);
    BOOL GetMicState();

    void SetMicVolume(INT32 volume);
    INT32 GetMicVolume();

    void SetSoundState(BOOL state);
    BOOL GetSoundState();

    void SetSoundVolume(INT32 volume);
    INT32 GetSoundVolume();

    HTREEITEM GetDevTreePos();
    void SetDevTreePos(HTREEITEM ItemPos);

    BOOL GetTrackingState();
    void SetTrackingState(BOOL state);

    void SetDevIndex(INT32 dwDevIndex);
    INT32 GetDevIndex();

    void SetChnID(INT32 dwChnID);
    INT32 GetChnID();

    void setUpdateInfo(const NETDEMO_UPDATE_TIME_INFO& stUpdateInfo);
    void getUpdateInfo(NETDEMO_UPDATE_TIME_INFO& stUpdateInfo);

    void setPauseState(BOOL bPauseState);
    BOOL getPauseState();

    void setDateTime(const SYSTEMTIME& oDateBegin,
                        const SYSTEMTIME& oTimeBegin,
                        const SYSTEMTIME& oDateEnd,
                        const SYSTEMTIME& oTimeEnd);

    void getDateTime(SYSTEMTIME& oDateBegin,
                         SYSTEMTIME& oTimeBegin,
                         SYSTEMTIME& oDateEnd,
                         SYSTEMTIME& oTimeEnd);

    void Set3DPosition();
    
    void SetDigitalZoom(BOOL bAction);

    bool ConvertRectToNetSDK(CRect &dstRect);

    void SetSpeed(INT32 enSpeed);
    INT32 GetSpeed();
    void CPlayWnd::SetRemainTime(INT64 remainTime);
    INT64 GetRemainTime();

private:
    int m_nWndID;
    int m_nPreSplit;
    BOOL m_bFullScreen;
    

    CRITICAL_SECTION m_cs;
    NETDEMO_SPLITINFO_NODE m_stplitInfo;
    NETDEMO_UPDATE_TIME_INFO    m_stUpdateInfo;

    SYSTEMTIME m_oTimeBegin;
    SYSTEMTIME m_oTimeEnd;
    SYSTEMTIME m_oDateBegin;
    SYSTEMTIME m_oDateEnd;

    BOOL m_NetPlayRealMode;
    BOOL m_NetPlayFluenyMode;
    BOOL m_bShortDelay;
    BOOL m_bFluent;
    BOOL m_bOpenMic;
    BOOL m_bOpenSound;
    BOOL m_bRouteRecording;
    BOOL m_bTracking;  
    BOOL m_bSaveLocalRecord;
    BOOL m_bPauseState;

    INT32 m_dwMicVolume;
    INT32 m_dwSoundVolume;
    INT32 m_dwSpeed;
    INT64 m_lRemainTime;

    CPoint   m_nStartPos;
    CPoint   m_nOldPos;
    CPoint   m_nEndPos;
    BOOL    m_bDrawRect;

    /*Draw Rect*/
    CPen m_oPen;
    BOOL m_bOpen3D;
    BOOL m_bOpenDZ;
public:
    afx_msg void OnPlayRClickFullscreen();
    afx_msg void OnPlayRClickMulitscreen();
    afx_msg void OnPlayRClickAutoAdjust();
    afx_msg void OnPlayRClickClose(); 
    afx_msg void OnPlayRClickMakeKeyFrame();
    afx_msg void OnPlayRClickNetRealTime();
    afx_msg void OnPlayRClickNetFluey();
    afx_msg void OnPlayRClickTalk();
    afx_msg void OnUpdatePalyRightclickTalk(CCmdUI *pCmdUI);
    afx_msg void OnPlayRClickCloseAll();
    afx_msg void OnPlayRClickCameraInfo();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnPaint();
    afx_msg void OnPalyrightclickDz();
    afx_msg void OnPalyrightclick3dposition();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYWND_H__E6AAF690_8D19_43AC_AE4E_E64F2412D706__INCLUDED_)
