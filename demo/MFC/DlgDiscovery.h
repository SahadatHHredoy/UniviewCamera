#pragma once
#include "afxcmn.h"


// CDlgDiscovery 

class CDlgDiscovery : public CDialog
{
    DECLARE_DYNAMIC(CDlgDiscovery)

public:
    CDlgDiscovery(CWnd* pParent = NULL);
    virtual ~CDlgDiscovery();

    enum { IDD = IDD_DLG_DISCOVERY };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()

private:
    void InitListCtrl();

    BOOL isExistDevinfo(const LPNETDEV_DISCOVERY_DEVINFO_S pstDiscoveryDevinfo);

public:
    void handleDiscovery(LPNETDEV_DISCOVERY_DEVINFO_S pstDevInfo);

public:
    CListCtrl m_oDeviceInfoList;
    afx_msg void OnBnClickedSegmentDiscovery();
    afx_msg void OnBnClickedAutoDiscovery();
    afx_msg void OnBnClickedAddDevice();
    afx_msg void OnClose();

private:
    CString m_strUserName;
    CString m_strPassword;

    CString m_strBeginIP;
    CString m_strEndIP;
    INT32 m_dwDeviceNum;
    std::vector<NETDEV_DISCOVERY_DEVINFO_S> m_oDevInfoMap;
};
