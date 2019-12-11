#pragma once


// CCfgNetWork 

class CCfgNetWork : public CDialog
{
    DECLARE_DYNAMIC(CCfgNetWork)

public:
    CCfgNetWork(CWnd* pParent = NULL); 
    virtual ~CCfgNetWork();

    enum { IDD = IDD_CFG_NETWORK };
    void ReadGlobeToNetwork();

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()

    void getNetWorkCfg();

    void getProtoPort();

    void getNtpCfg();

private:

    BOOL m_bEnableDHCP;                     /* Enable DHCP */
    INT32 m_dwMtu;                          /* MTU */
    CString m_strIPv4Addr;                  /* IP address */
    CString m_strSubnetMask;                /* Sub netmask */
    CString m_strIPv4Gateway;               /* Gateway */
    CIPAddressCtrl m_oEditIPv4Addr;
    CIPAddressCtrl m_oEditSubnetMask;
    CIPAddressCtrl m_oEditGateway;

    INT32 m_dwHttpPort;                     /* http port */
    INT32 m_dwHttpsPort;                    /* https port */
    INT32 m_dwRtspPort;                     /* RTSP port  */
    CComboBox m_oCBoxHttpPortStatus;
    CComboBox m_oCBoxHttpsPortStatus;
    CComboBox m_oCBoxRtspPortStatus;

    
    //INT32 m_dwNtpIPType;                    /* Net IP type */
    //BOOL m_bEnableNtpDHCP;                  /* Support NTP DHCP */

    INT64  m_ulNtpSynInterval;              /* NTP SynchronizeInterval */
    INT64  m_ulNtpProt;                     /* NTP port */
    CString m_strNtpDomainName;             /* NTP DomainName */
    CString m_strNtpServerIP;               /* NTP server IP */
    INT64 m_ulNtpIPType;                    /* Net IP type */
    BOOL m_bEnableNtpServer;                /* Support NTP Server */
    INT64  m_ulNum;                         /* NTP Number*/

    CComboBox m_oCBoxIPType;
    CIPAddressCtrl m_oEditNtpServerIP;
    CIPAddressCtrl m_oEditNtpDomainName;
    CIPAddressCtrl m_oEditNtpPort;
    CIPAddressCtrl m_oEditNtpSynInterval;

public:
    afx_msg void OnBnClickedSaveNetworkCfg();
    afx_msg void OnBnClickedSaveProtoPort();
    afx_msg void OnBnClickedSaveNtpCfg();
    afx_msg void OnBnClickedRefresh();
    afx_msg void OnEnKillfocusEditMtu();
    afx_msg void OnBnClickedCheckEdnableDhcp();
    afx_msg void OnBnClickedCheckEdnableNtpDhcp();
};
