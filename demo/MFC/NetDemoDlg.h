// NetDemoDlg.h : 

#pragma once
#include "afxcmn.h"
#include "DlgAddDevice.h"
#include "ScreenPannel.h"
#include "PannelPTZ.h"
#include "MenuCfg.h"
#include "MenuPlayBack.h"
#include "DlgCycleMonitor.h"
#include "DlgLocalSetting.h"
#include "MenuAlarm.h"
#include "MenuMaintain.h"
#include "DlgDiscovery.h"
#include "MenuVca.h"
#include "DlgCloudDev.h"
#include "afxwin.h"
#include "DlgLocalDevInfo.h"
#include "DlgCloudDevInfo.h"
#include <list>
#include "PannelPlayControl.h"
#include "DlgStreamCallback.h"
#include "MenuUserCfg.h"

#define  COL_INDEX_LOG_LIST_TIME                0
#define  COL_INDEX_LOG_LIST_DEV_INFO            1
#define  COL_INDEX_LOG_LIST_OPERATION           2
#define  COL_INDEX_LOG_LIST_STATUS              3
#define  COL_INDEX_LOG_LIST_ERRCODE             4


class CNetDemoDlg : public CDialog
{

public:
    CNetDemoDlg(CWnd* pParent = NULL);
    virtual ~CNetDemoDlg();

    enum { IDD = IDD_MAIN_NETDEMO };

    protected:
    virtual void DoDataExchange(CDataExchange* pDX);

protected:
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnNMRClickTreeDeviceList(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnTcnSelchangeTabMainMenu(NMHDR *pNMHDR, LRESULT *pResult);
    static DWORD WINAPI CycleMonitorThread(LPVOID lpArg);
    static DWORD WINAPI DevLoginThread(LPVOID lpArg);
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    DECLARE_MESSAGE_MAP()

protected:
    HANDLE  m_hCycleThread;
    HANDLE  m_hLoginThread;

    BOOL m_bStopCycFlag;
    BOOL m_bCycleMonitor;

    BOOL m_bStopLoginFlag;
    BOOL m_bLoginThread;
    
    BOOL m_bClientLogListEnlarge;
    std::list<NETDEMO_DEVICE_INFO> m_oListDevInfoBuffer;
    CRITICAL_SECTION m_stCycCs;

public://common 
    void InitGlobalSysInfo(void);
    void InitMainMenuUI(void);
    void InitClientLogList(void);
    void UpdatePannelPosition(void);
    void UpdateMainMenu(void);
    void InitCfgUI(void);
    void InitPlaybackUI(void);
    void InitWarningUI(void);
    void InitMainTainUI(void);
    void InitVCAUI(void);
    void InitUserCfgUI(void);
    void SetCurWindId(int nCuWinID);
    int  GetCurWinID(void);
    int  GetCurDeviceIndex(void);
    int  GetCurChlIndex(void);
    LPVOID GetDevHandle(void);
    LPVOID GetActivePlayHandle(void);
    int GetChlID();
    BOOL GetPlayWndDevIndex(LPVOID pPlayHandle, INT32& dwDevIndex);
    BOOL IsTalking();
    void AddDevice(NETDEMO_DEVICE_INFO stNetDevInfo);
    void DeviceoperLogin(NETDEMO_DEVICE_INFO stNetDevInfo);
    BOOL IsExistInThreadBuffer(NETDEMO_DEVICE_INFO stNetDevInfo);
    BOOL IsExistInDevBuffer(NETDEMO_DEVICE_INFO stNetDevInfo);
    CString GetDevIPByDevHandle(LPVOID lpDevHandle);
    void NETSDK_SetActiveWndDZ(CRect oRect,BOOL bAction);
    void NETSDK_SetActive3DPostion(CRect oRect);

public: //about SDK Interface
    INT32 Login(NETDEMO_DEVICE_INFO& stNetDevInfo);
    BOOL  Logout(NETDEMO_DEVICE_INFO& stNetDevInfo);
    INT32 GetNetSDKMicVolume(void);
    bool  SetNetSDKMicVolume(INT32 dwVolume);
    INT32 GetNetSDKSoundVolume(void);
    bool  SetNetSDKSoundVolume(INT32 dwVolume);
    BOOL  StartTwoWayAudio(void);
    BOOL  StopTalk(void);
    void  MakeKeyFrame(INT32 dwDevIndex, INT32 dwChnIndex);
    void  SetNetPlayMode(NETDEV_PICTURE_FLUENCY_E type); // NETDEV_PICTURE_FLUENCY_E
    void  CloseAll(void);
    void  StopVideoByIndex(INT32 dwIndex);
    void  StartCycleMonitor();
    void  StopCycMonitor();
    void  CycMonitorControl(INT32 dwWinID);

    void  GetCameraInfo();

public:  //about dev tree
    void CreateTree(void);
    void LoadTreeImage(void);
    void DrawTree(NETDEMO_DEVICE_INFO& stNetDevInfo);
    void UpdateSelectDevState();
    void UpdateDevState(NETDEMO_DEVICE_INFO stDevInfo);
    HTREEITEM GetAfterItem(HTREEITEM hRoot);
    LRESULT OnAddDevice(WPARAM wParam, LPARAM lParam);
    LRESULT OnClickPlayWindow(WPARAM wParam, LPARAM lParam);
    LRESULT OnSetDevAudioPara(WPARAM wParam, LPARAM lParam);

public: //about Play Control
    void CycleMonitor();
    void RealPlaySelectedDevice();
    void StopPlaySelectedDevice();
    void SnapShotSelectedDevice();
    void StartLocalRecod();
    void SetMultiScreen(INT32 dwSplit);
    void SetSliderSoundVolume(INT32 dwValue);
    void SetSliderMicVolume(INT32 dwValue);
    BOOL ControlMicVolume();
    BOOL ControlSoundVolume();
    void EnlargeList(BOOL bEnargeList);
    void UpdateDevState(HTREEITEM& hSelect, NETDEMO_DEVICE_INFO& stDevInfo);
    void SetCycleMonitor(BOOL bCycleMonitor);
    BOOL GetCycleMonitor();

public: //about window start
    int  GetSplit(void);
    void SetSplit(int nSplit);

public://about control start
    CImageList  m_oTreeImage;
    CTreeCtrl   m_oDeviceTreeList;
    CTabCtrl    m_oTabManu;
    CListCtrl   m_oClientLogList;

private: // Common
    INT32 m_dwMainMenuType;
    INT32 m_dwActiveScreen;
    INT32 m_dwCurDevIndex;
    INT32 m_dwCurChlIndex;
    INT32 m_dwSplitNum;
    HTREEITEM m_hCurDeviceItem;
    HTREEITEM m_hCurChanItem;
    HTREEITEM m_hDevtree;
    LPVOID m_lpTalkID;
    INT32 m_dwCurSelectType;

public:
    NETDEMO_CYCLE_INFO  m_stCycleInfo;
    CDlgLocalSetting    m_oDlgLocalSetting;
    CMenuVca            m_oDlgVCA;
    CMenuPlayBack       m_oDlgPlayback;
    CScreenPannel       m_oScreenPannel;
    CDlgStreamCallback  m_oStreamCallback;

private:// about dlg 
    CPannelPTZ      m_oPtzPannel;
    CMenuMaintain   m_oDlgMaintain;
    CDlgDiscovery   m_oDlgDiscovery;
    CMenuAlarm      m_oDlgAlarm;
    CMenuCfg        m_oDlgCfg;
    CMenuUserCfg    m_oDlgUserCfg;
    
    CDlgCycleMonitor    m_oDlgCycleMonitor;
    CPannelPlayControl  m_oPannelPlayControl;

private:
    CRect   m_oClientRect;
    CRect   m_oScreenRect;
    CRect   m_oPlayControlRect;
    CRect   m_oDeviceTreeRect;
    CRect   m_oClientAllLogRect;
    CRect   m_oPrimaryLabelRect;
    CRect   m_oPTZRect;
    HICON   m_hIcon;

public:
    afx_msg void OnBnClickedButtonLocalSetting();
    afx_msg void OnTvnSelchangedTreeDeviceList(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnDeviceoperLogin();
    afx_msg void OnBnClickedButtonDiscovery();
    afx_msg void OnLoginByCloud();
    afx_msg void OnLoginByLocal();
    afx_msg void OnDeleteDevice();
    afx_msg void OnClose();
    afx_msg void OnDeviceoperLogout();
    afx_msg void OnDeviceAttribute();
    afx_msg void OnNMDblclkTreeDeviceList(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnBnClickedCleanClintlog();
    afx_msg void OnBnClickedSaveClinetlog();
    afx_msg void OnLvnColumnclickListAllLog(NMHDR *pNMHDR, LRESULT *pResult);
};
