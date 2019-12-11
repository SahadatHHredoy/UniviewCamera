#pragma once

#include "ScreenPannel.h"
#include "afxcmn.h"
#include "DlgDownloadInfo.h"
#include <vector>
#include <map>
#include <queue>
#include "afxdtctl.h"

#define NETDEMO_PLAYBACK_SCREEN_NUM         4

class CMenuPlayBack : public CDialog
{
    DECLARE_DYNAMIC(CMenuPlayBack)

public:
    CMenuPlayBack(CWnd* pParent = NULL);
    virtual ~CMenuPlayBack();

    enum { IDD = IDD_MENU_PLAYBACK };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();
    virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
    HICON m_hSoundStartIcon;
    HICON m_hSoundStopIcon;

    HICON m_hPlayEnableIcon;
    HICON m_hPlayDisableIcon;

    HICON m_hPauseEnableIcon;
    HICON m_hPauseDisableIcon;

    HICON m_hStopEnableIcon;
    HICON m_hStopDisableIcon;

    HICON m_hGotoHeadDisableIcon;
    HICON m_hGotoHeadEnableIcon;

    HICON m_hFastDisableIcon;
    HICON m_hFastEnableIcon;

    HICON m_hSlowDisableIcon;
    HICON m_hSlowEnableIcon;

    HICON m_hStepEnableIcon;
    HICON m_hStepDisableIcon;

    HICON m_hCaptureIcon;
public:
    CScreenPannel   m_oPlayBackscreenPannel; 

    DECLARE_MESSAGE_MAP()
private:
    void InitScreenPannel();
    void UpdatePannelPosition();
    void InitPlayBackList();
    void SetPlayBackIconDisable();
    void SetPlayBackIconEnable();
    void InitCombo();
    void InitToolTipCtrl();
    long GetTick(const CString& strTime);
    CString GetTime(const INT64 tTime);
    BOOL getTimeInfo(INT64& dwBeginTime, INT64& dwEndTime);
    int     GetCurWinID(void);
    BOOL GetPlayWnd(CPlayWnd** pPlayWnd);
    BOOL GetPlayHandle(LPVOID* pPlayHandle);
    BOOL compareTime(const CString& strBeginTime, const CString& strEndTime);
    void initSlider();
    void startDownloadRecord();
    void stopDownloadRecord();
    void getFileName(LPVOID  dwUserID, CString& strFileName);
    void QueryRecord(std::queue<NETDEV_FINDDATA_S>&  FindData);
    BOOL updateProgress(NETDEMO_UPDATE_TIME_INFO& stUpdateInfo, INT64 dwCurTime, BOOL bFlag = TRUE);
    BOOL updateTime(NETDEMO_UPDATE_TIME_INFO& stUpdateInfo, INT64 dwCurTime, BOOL bFlag = TRUE);
    void initSearchTime();
    INT32 parseTime(IN CHAR * pszTime, OUT SYSTEMTIME &oSysTime);
    void initRemainTime();
    void updateRemainTime(INT64 remainTime);
    void initSpeed();
    void updateSpeed(INT32 enSpeed);

private:
    INT32       m_dwCurScreen;
    CRect       m_oClientRect;
    CRect       m_oScreenRect;
    CComboBox   m_oCBoxEventList;
    CString     m_oCurPlayTime;
    INT32       m_lEventType;
    INT32       m_dwVolume;
    INT32       m_dwSpeed;
    INT64       m_lRemainTime;
    std::vector<NETDEV_FINDDATA_S> m_oFindData;
    NETDEMO_UPDATE_TIME_INFO m_oastUpdateInfo[NETDEMO_PLAYBACK_SCREEN_NUM];
    std::map<int, NETDEMO_UPDATE_TIME_INFO> m_oDownloadInfoMap;
    CToolTipCtrl    m_oToolTip;
    CDateTimeCtrl m_oBeginTime;
    CDateTimeCtrl m_oEndTime;
    CDateTimeCtrl m_oBeginDate;
    CDateTimeCtrl m_oEndDate;
    CString m_strRemainTime;

public:
    CListCtrl m_oRecordList;
    CDlgDownloadInfo m_oDownloadInfo;
    afx_msg void OnBnClickedButtonDownloadinfo();
    afx_msg void OnBnClickedEventQueryRecord();
    afx_msg void OnCbnSelchangeComboEventList();
    afx_msg void OnBnClickedButtonPlaybackPlay();
    afx_msg void OnBnClickedButtonPlaybackPause();
    afx_msg void OnBnClickedButtonPlaybackStop();
    afx_msg void OnBnClickedButtonPlaybackSlow();
    afx_msg void OnBnClickedButton1PlaybackFast();
    afx_msg void OnBnClickedButtonPlaybackCap();
    afx_msg void OnBnClickedButtonPlaybackSetbeginpos();
    afx_msg void OnBnClickedButtonPlaybackNextframe();
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnBnClickedButtonStartDemnload();
    afx_msg void OnBnClickedButtonStopDownload();
    afx_msg void OnBnClickedButtonPlaybackVol();

    BOOL GetPlayWndDevIndex(LPVOID pPlayHandle, INT32& dwDevIndex);
    LRESULT OnClickPlayBackWindow(WPARAM wParam, LPARAM lParam);
    afx_msg void OnNMClickPlaybackRecordList(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnNMReleasedcaptureSliderPlayProgress(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnNMCustomdrawSliderPlayProgress(NMHDR *pNMHDR, LRESULT *pResult);

    CString m_strRecodeDayNums;
    afx_msg void OnBnClickedButtonGetrecorddaynums();
};
