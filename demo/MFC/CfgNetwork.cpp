
#include "stdafx.h"
#include "NetDemo.h"
#include "CfgNetWork.h"

// CCfgNetWork 

IMPLEMENT_DYNAMIC(CCfgNetWork, CDialog)

CCfgNetWork::CCfgNetWork(CWnd* pParent /*=NULL*/)
    : CDialog(CCfgNetWork::IDD, pParent)
    , m_dwMtu(0)
    , m_dwHttpPort(0)
    , m_dwHttpsPort(0)
    , m_dwRtspPort(0)
    , m_ulNtpProt(0)
    , m_ulNtpSynInterval(0)
{

}

CCfgNetWork::~CCfgNetWork()
{
}

void CCfgNetWork::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_IPADD_IPV4, m_strIPv4Addr);
    DDX_Text(pDX, IDC_IPADD_SUB_NETMASK, m_strSubnetMask);
    DDX_Text(pDX, IDC_IPADD_GATEWAY, m_strIPv4Gateway);
    DDX_Text(pDX, IDC_EDIT_MTU, m_dwMtu);
    DDX_Check(pDX, IDC_CHECK_EDNABLE_DHCP, m_bEnableDHCP);

    DDX_Control(pDX, IDC_IPADD_IPV4, m_oEditIPv4Addr);
    DDX_Control(pDX, IDC_IPADD_SUB_NETMASK, m_oEditSubnetMask);
    DDX_Control(pDX, IDC_IPADD_GATEWAY, m_oEditGateway);

    DDX_Text(pDX, IDC_EDIT_HTTP_PORT, m_dwHttpPort);
    DDX_Text(pDX, IDC_EDIT_HTTPS_PORT, m_dwHttpsPort);
    DDX_Text(pDX, IDC_EDIT_RTSP_PORT, m_dwRtspPort);
    DDX_Control(pDX, IDC_COMBO_HTTP_PORT_STATUS, m_oCBoxHttpPortStatus);
    DDX_Control(pDX, IDC_COMBO_HTTPS_PORT_STATUS, m_oCBoxHttpsPortStatus);
    DDX_Control(pDX, IDC_COMBO_RTSP_PORT_STATUS, m_oCBoxRtspPortStatus);

    DDX_Text(pDX,IDC_EDIT_SYNCHRONIZEINTERVAL,m_ulNtpSynInterval);
    DDX_Text(pDX,IDC_EDIT_NTP_PORT,m_ulNtpProt);
    DDX_Text(pDX,IDC_EDIT_NTP_DOMAINNAME,m_strNtpDomainName);
    DDX_Text(pDX, IDC_IPADD_NTP_SERVER_IP, m_strNtpServerIP);
    DDX_Control(pDX, IDC_IPADD_NTP_SERVER_IP, m_oEditNtpServerIP);
    DDX_Check(pDX, IDC_CHECK_EDNABLE_NTP_SERVER, m_bEnableNtpServer);
    DDX_Control(pDX, IDC_COMBO_IP_TYPE, m_oCBoxIPType);
    DDX_Control(pDX,IDC_EDIT_SYNCHRONIZEINTERVAL,m_oEditNtpSynInterval);
    DDX_Control(pDX,IDC_EDIT_NTP_PORT,m_oEditNtpPort);
    DDX_Control(pDX,IDC_EDIT_NTP_DOMAINNAME,m_oEditNtpDomainName);

}

BOOL CCfgNetWork::OnInitDialog()
{
    CDialog::OnInitDialog();
    CRect rc(0, 0, 0, 0);
    GetParent()->GetClientRect(&rc);
    ((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
    MoveWindow(&rc);

    m_oCBoxHttpPortStatus.InsertString(0, _T("Disable"));
    m_oCBoxHttpPortStatus.InsertString(1, _T("Enable"));
    m_oCBoxHttpPortStatus.SetCurSel(0);

    m_oCBoxHttpsPortStatus.InsertString(0, _T("Disable"));
    m_oCBoxHttpsPortStatus.InsertString(1, _T("Enable"));
    m_oCBoxHttpsPortStatus.SetCurSel(0);

    m_oCBoxRtspPortStatus.InsertString(0, _T("Disable"));
    m_oCBoxRtspPortStatus.InsertString(1, _T("Enable"));
    m_oCBoxRtspPortStatus.SetCurSel(0);

    m_oCBoxIPType.InsertString(NETDEV_NETWORK_HOSTTYPE_IPV4, _T("IPV4"));
    m_oCBoxIPType.InsertString(NETDEV_NETWORK_HOSTTYPE_IPV6, _T("IPV6"));
    m_oCBoxIPType.InsertString(NETDEV_NETWORK_HOSTTYPE_DNS, _T("DNS"));
    m_oCBoxIPType.SetCurSel(NETDEV_NETWORK_HOSTTYPE_IPV4);

    return TRUE;
}
BEGIN_MESSAGE_MAP(CCfgNetWork, CDialog)
    ON_BN_CLICKED(IDC_SAVE_NETWORK_CFG, &CCfgNetWork::OnBnClickedSaveNetworkCfg)
    ON_BN_CLICKED(IDC_SAVE_PROTO_PORT, &CCfgNetWork::OnBnClickedSaveProtoPort)
    ON_BN_CLICKED(IDC_SAVE_NTP_CFG, &CCfgNetWork::OnBnClickedSaveNtpCfg)
    ON_BN_CLICKED(IDC_REFRESH, &CCfgNetWork::OnBnClickedRefresh)
    ON_EN_KILLFOCUS(IDC_EDIT_MTU, &CCfgNetWork::OnEnKillfocusEditMtu)
    ON_BN_CLICKED(IDC_CHECK_EDNABLE_DHCP, &CCfgNetWork::OnBnClickedCheckEdnableDhcp)
    ON_BN_CLICKED(IDC_CHECK_EDNABLE_NTP_DHCP, &CCfgNetWork::OnBnClickedCheckEdnableNtpDhcp)
END_MESSAGE_MAP()



/* Get Network Config */
void CCfgNetWork::getNetWorkCfg()
{
    LPVOID lpDevHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChannelID = ga_pMainDlg->GetChlID();
    INT32 dwCurDevIndex = ga_pMainDlg ->GetCurDeviceIndex();
    INT32 dwCurChlIndex = ga_pMainDlg->GetCurChlIndex();
    NETDEV_NETWORKCFG_S stNetworkcfg = {0};

    INT32 dwBytesReturned = 0;
    BOOL bRet = NETDEV_GetDevConfig(lpDevHandle, dwChannelID, NETDEV_GET_NETWORKCFG, &stNetworkcfg, sizeof(NETDEV_NETWORKCFG_S), &dwBytesReturned);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Get network cfg");
        return;
    }
    
    m_strIPv4Addr = stNetworkcfg.szIpv4Address;
    m_strIPv4Gateway = stNetworkcfg.szIPv4GateWay;
    m_strSubnetMask = stNetworkcfg.szIPv4SubnetMask;
    m_dwMtu = stNetworkcfg.dwMTU;
    m_bEnableDHCP = stNetworkcfg.bIPv4DHCP;

    NETDEMO_LOG_SUCC(NULL, "Get network cfg");
    UpdateData(FALSE);
    gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstNetworkInfo->stNetWorkIP = stNetworkcfg;
    OnBnClickedCheckEdnableDhcp();
    return;
}

/*Set Network Config */
void CCfgNetWork::OnBnClickedSaveNetworkCfg()
{
    UpdateData(TRUE);
    LPVOID lpDevHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChannelID = ga_pMainDlg->GetChlID();
    INT32 dwCurDevIndex = ga_pMainDlg ->GetCurDeviceIndex();
    INT32 dwCurChlIndex = ga_pMainDlg->GetCurChlIndex();

    NETDEV_NETWORKCFG_S stNetworkSetcfg = {0};
    INT32 dwBytesReturned = 0;

    /* IP address */
    if("" != m_strIPv4Addr)
    {
        strncpy(stNetworkSetcfg.szIpv4Address, m_strIPv4Addr, sizeof(stNetworkSetcfg.szIpv4Address) -1);
    }

    /* Gate way */
    if("" != m_strIPv4Gateway)
    {
        strncpy(stNetworkSetcfg.szIPv4GateWay, m_strIPv4Gateway, sizeof(stNetworkSetcfg.szIPv4GateWay) -1);
    }

    /* sub netmask */
    if("" != m_strSubnetMask)
    {
        strncpy(stNetworkSetcfg.szIPv4SubnetMask, m_strSubnetMask, sizeof(stNetworkSetcfg.szIPv4SubnetMask) -1);
    }

    /* MTU */
    stNetworkSetcfg.dwMTU = m_dwMtu;

    /* DHCP */
    stNetworkSetcfg.bIPv4DHCP = m_bEnableDHCP;

    BOOL bRet = NETDEV_SetDevConfig(lpDevHandle, dwChannelID, NETDEV_SET_NETWORKCFG, &stNetworkSetcfg, sizeof(stNetworkSetcfg));
    if (TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Save network cfg");
        return;
    }
    gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstNetworkInfo->stNetWorkIP = stNetworkSetcfg;
    NETDEMO_LOG_SUCC(NULL, "Save network cfg");
    return;
}

/* Get protocal port */
void CCfgNetWork::getProtoPort()
{
    LPVOID lpDevHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChannelID = ga_pMainDlg->GetChlID();
    INT32 dwCurDevIndex = ga_pMainDlg ->GetCurDeviceIndex();
    INT32 dwCurChlIndex = ga_pMainDlg->GetCurChlIndex();
    NETDEV_UPNP_NAT_STATE_S stNatState = {0};

    BOOL bRet = NETDEV_GetUpnpNatState(lpDevHandle, &stNatState);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Get port cfg");
        return;
    }

    for (INT32 i = 0; i < stNatState.dwSize;i++)
    {
        switch(stNatState.astUpnpPort[i].eType)
        {
        case NETDEV_PROTOCOL_TYPE_HTTP:
            {
                m_dwHttpPort = stNatState.astUpnpPort[i].dwPort;
                INT32 index = stNatState.astUpnpPort[i].bEnbale ? 1 : 0;
                m_oCBoxHttpPortStatus.SetCurSel(index);
            }
            break;
        case NETDEV_PROTOCOL_TYPE_HTTPS:
            {
                m_dwHttpsPort = stNatState.astUpnpPort[i].dwPort;
                INT32 index = stNatState.astUpnpPort[i].bEnbale ? 1 : 0;
                m_oCBoxHttpsPortStatus.SetCurSel(index);
            }
            break;
        case NETDEV_PROTOCOL_TYPE_RTSP:
            {
                m_dwRtspPort = stNatState.astUpnpPort[i].dwPort;
                INT32 index = stNatState.astUpnpPort[i].bEnbale ? 1 : 0;
                m_oCBoxRtspPortStatus.SetCurSel(index);
            }
            break;
        default:
            break;
        }
    }
    gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstNetworkInfo->stNetWorkPort  = stNatState;
    NETDEMO_LOG_SUCC(NULL, "Get port cfg");
    UpdateData(FALSE);
    return;
}

/* Save protocal port */
void CCfgNetWork::OnBnClickedSaveProtoPort()
{
    UpdateData(TRUE);
    LPVOID lpDevHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChannelID = ga_pMainDlg->GetChlID();
    INT32 dwCurDevIndex = ga_pMainDlg ->GetCurDeviceIndex();
    INT32 dwCurChlIndex = ga_pMainDlg->GetCurChlIndex();
    NETDEV_UPNP_NAT_STATE_S stNatState = {0};

    stNatState.dwSize = 3;

    stNatState.astUpnpPort[0].dwPort = m_dwHttpPort;
    stNatState.astUpnpPort[0].eType = NETDEV_PROTOCOL_TYPE_HTTP;
    BOOL bEnable = (0 != m_oCBoxHttpPortStatus.GetCurSel()) ? TRUE : FALSE;
    stNatState.astUpnpPort[0].bEnbale = bEnable;


    stNatState.astUpnpPort[1].dwPort = m_dwHttpsPort;
    stNatState.astUpnpPort[1].eType = NETDEV_PROTOCOL_TYPE_HTTPS;
    bEnable = (0 != m_oCBoxHttpsPortStatus.GetCurSel()) ? TRUE : FALSE;
    stNatState.astUpnpPort[1].bEnbale = bEnable;


    stNatState.astUpnpPort[2].dwPort = m_dwRtspPort;
    stNatState.astUpnpPort[2].eType = NETDEV_PROTOCOL_TYPE_RTSP;
    bEnable = (0 != m_oCBoxRtspPortStatus.GetCurSel()) ? TRUE : FALSE;
    stNatState.astUpnpPort[2].bEnbale = bEnable;

    BOOL bRet = NETDEV_SetUpnpNatState(lpDevHandle, &stNatState);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Set port cfg");
        return;
    }
    gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstNetworkInfo->stNetWorkPort = stNatState;
    NETDEMO_LOG_SUCC(NULL, "Set port cfg");

    return;
}


void CCfgNetWork::ReadGlobeToNetwork()
{
    INT32 dwCurDevIndex = ga_pMainDlg ->GetCurDeviceIndex();
    INT32 dwCurChlIndex = ga_pMainDlg->GetCurChlIndex();
    
    /* IP  */
    NETDEV_NETWORKCFG_S stNetworkcfg = {0};
    stNetworkcfg = gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstNetworkInfo->stNetWorkIP;
    m_strIPv4Addr = stNetworkcfg.szIpv4Address;
    m_strIPv4Gateway = stNetworkcfg.szIPv4GateWay;
    m_strSubnetMask = stNetworkcfg.szIPv4SubnetMask;
    m_dwMtu = stNetworkcfg.dwMTU;
    m_bEnableDHCP = stNetworkcfg.bIPv4DHCP;

    /* Port  */
    NETDEV_UPNP_NAT_STATE_S stNatState = {0};
    stNatState = gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstNetworkInfo->stNetWorkPort;
    for (INT32 i = 0; i < stNatState.dwSize;i++)
    {
        switch(stNatState.astUpnpPort[i].eType)
        {
        case NETDEV_PROTOCOL_TYPE_HTTP:
            {
                m_dwHttpPort = stNatState.astUpnpPort[i].dwPort;
                INT32 index = stNatState.astUpnpPort[i].bEnbale ? 1 : 0;
                m_oCBoxHttpPortStatus.SetCurSel(index);
            }
            break;
        case NETDEV_PROTOCOL_TYPE_HTTPS:
            {
                m_dwHttpsPort = stNatState.astUpnpPort[i].dwPort;
                INT32 index = stNatState.astUpnpPort[i].bEnbale ? 1 : 0;
                m_oCBoxHttpsPortStatus.SetCurSel(index);
            }
            break;
        case NETDEV_PROTOCOL_TYPE_RTSP:
            {
                m_dwRtspPort = stNatState.astUpnpPort[i].dwPort;
                INT32 index = stNatState.astUpnpPort[i].bEnbale ? 1 : 0;
                m_oCBoxRtspPortStatus.SetCurSel(index);
            }
            break;
        default:
            break;
        }
        UpdateData(FALSE);
    }

    /* NTP  */
    
    NETDEV_SYSTEM_NTP_INFO_LIST_S stNTPInfo = {0};
    stNTPInfo = gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstNetworkInfo->stNetWorkNTP;
    for (INT32 i = 0; i < stNTPInfo.ulNum;i++)
    {
        /* Support NTP Server */
        m_bEnableNtpServer = stNTPInfo.astNTPServerInfoList[i].bEnabled;

        /* IP type */
        m_oCBoxIPType.SetCurSel(stNTPInfo.astNTPServerInfoList[i].ulAddressType);

        /* Ntp Server IP address */
        m_strNtpServerIP = stNTPInfo.astNTPServerInfoList[i].szIPAddress;

        /*Ntp DomainName*/
        m_strNtpDomainName = stNTPInfo.astNTPServerInfoList[i].szDomainName;

        /*Ntp IP Prot*/
        m_ulNtpProt = stNTPInfo.astNTPServerInfoList[i].ulPort;

        /*Ntp SynchronizeInterval*/
        m_ulNtpSynInterval = stNTPInfo.astNTPServerInfoList[i].ulSynchronizeInterval;
    }
    UpdateData(FALSE);
}

void CCfgNetWork::OnBnClickedRefresh()
{
    INT32 dwCurDevIndex = ga_pMainDlg ->GetCurDeviceIndex();
    INT32 dwCurChlIndex = ga_pMainDlg->GetCurChlIndex();
    if(dwCurChlIndex <0 )
    {
        return;
    }

    if (NULL != gastDeviceInfo && NULL != gastDeviceInfo[dwCurDevIndex].pstChlInfo)
    {
        if(NULL == gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstNetworkInfo)
        {
            gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstNetworkInfo = new NETDEMO_NETWORK_INFO_S;
        }
        memset(gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstNetworkInfo ,0,sizeof(NETDEMO_NETWORK_INFO_S));

        /* Get Network Config */
        getNetWorkCfg();

        /* Get protocal port */
        getProtoPort();

        /* Get NTP config */
        getNtpCfg();
    }
    
    UpdateData(FALSE);
    return;
}

void CCfgNetWork::OnEnKillfocusEditMtu()
{
    UpdateData(TRUE);
    if (m_dwMtu < 576)
    {
        m_dwMtu = 576;
    }
    else if (m_dwMtu > 1500)
    {
        m_dwMtu = 1500;
    }

    char szTmp[16] = {0};
    sprintf_s(szTmp, sizeof(szTmp), "%d", m_dwMtu);
    GetDlgItem(IDC_EDIT_MTU)->SetWindowText(szTmp);

    UpdateData(FALSE);
    return;
}

void CCfgNetWork::OnBnClickedCheckEdnableDhcp()
{
    UpdateData(TRUE);

    //set read only while check DHCP
    m_oEditIPv4Addr.EnableWindow(!m_bEnableDHCP);
    m_oEditGateway.EnableWindow(!m_bEnableDHCP);
    m_oEditSubnetMask.EnableWindow(!m_bEnableDHCP);

    UpdateData(FALSE);
    return;
}

void CCfgNetWork::OnBnClickedCheckEdnableNtpDhcp()
{
    UpdateData(TRUE);

    m_oEditNtpServerIP.EnableWindow(m_bEnableNtpServer);
    m_oCBoxIPType.EnableWindow(m_bEnableNtpServer);
    m_oEditNtpPort.EnableWindow(m_bEnableNtpServer);
    m_oEditNtpDomainName.EnableWindow(m_bEnableNtpServer);
    m_oEditNtpSynInterval.EnableWindow(m_bEnableNtpServer);

    UpdateData(FALSE);
    return;
}
/* Get NTP config */
void CCfgNetWork::getNtpCfg()
{
    LPVOID lpDevHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChannelID = ga_pMainDlg->GetChlID();
    INT32 dwCurDevIndex = ga_pMainDlg ->GetCurDeviceIndex();
    INT32 dwCurChlIndex = ga_pMainDlg->GetCurChlIndex();

    INT32 dwBytesReturned = 0;


    NETDEV_SYSTEM_NTP_INFO_LIST_S stNTPInfo = {0};

    /* Failed to return Get information when NTP is not enabled for the NVR. Please perform Set operation first. */
    BOOL bRet = NETDEV_GetDevConfig(lpDevHandle, dwChannelID, NETDEV_GET_NTPCFG_EX, &stNTPInfo, sizeof(stNTPInfo), &dwBytesReturned);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Get NTP cfg");
        return;
    }
    for (INT32 i = 0; i < stNTPInfo.ulNum;i++)
    {
        /* Support NTP Server */
        m_bEnableNtpServer = stNTPInfo.astNTPServerInfoList[i].bEnabled;

        /* IP type */
        m_oCBoxIPType.SetCurSel(stNTPInfo.astNTPServerInfoList[i].ulAddressType);

        /* Ntp Server IP address */
        m_strNtpServerIP = stNTPInfo.astNTPServerInfoList[i].szIPAddress;

        /*Ntp DomainName*/
        m_strNtpDomainName = stNTPInfo.astNTPServerInfoList[i].szDomainName;

        /*Ntp IP Prot*/
        m_ulNtpProt = stNTPInfo.astNTPServerInfoList[i].ulPort;

        /*Ntp SynchronizeInterval*/
        m_ulNtpSynInterval = stNTPInfo.astNTPServerInfoList[i].ulSynchronizeInterval;
    }
    gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstNetworkInfo->stNetWorkNTP = stNTPInfo;

    if(m_bEnableNtpServer == TRUE)
    {
        ((CButton *)GetDlgItem(IDC_CHECK_EDNABLE_NTP_SERVER))->SetCheck(TRUE);
    }
    else
    {
         ((CButton *)GetDlgItem(IDC_CHECK_EDNABLE_NTP_SERVER))->SetCheck(FALSE);
    }
    UpdateData(FALSE);


    NETDEMO_LOG_SUCC(NULL, "Get NTP cfg");
    return;
}

/* Save NTP config */
void CCfgNetWork::OnBnClickedSaveNtpCfg()
{
    UpdateData(TRUE);
    LPVOID lpDevHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChannelID = ga_pMainDlg->GetChlID();
    INT32 dwCurDevIndex = ga_pMainDlg ->GetCurDeviceIndex();
    INT32 dwCurChlIndex = ga_pMainDlg->GetCurChlIndex();
    if (0 == m_oCBoxIPType.GetCurSel())
    {
        if ("" == m_strNtpServerIP || "0.0.0.0" == m_strNtpServerIP)
        {
            NETDEMO_LOG_ERROR(NULL, "Set NTP cfg");
            return;
        }
    } 
    else if(2 == m_oCBoxIPType.GetCurSel())
    {
        if ("" == m_strNtpDomainName)
        {
            NETDEMO_LOG_ERROR(NULL, "Set NTP cfg");
            return;
        }
    }

    NETDEV_SYSTEM_NTP_INFO_LIST_S stNTPInfo = {0};

    stNTPInfo.ulNum = 1;
    stNTPInfo.astNTPServerInfoList->bEnabled = m_bEnableNtpServer;
    stNTPInfo.astNTPServerInfoList->ulAddressType = m_oCBoxIPType.GetCurSel();
    strncpy(stNTPInfo.astNTPServerInfoList->szIPAddress, m_strNtpServerIP.GetBuffer(0), sizeof(stNTPInfo.astNTPServerInfoList->szIPAddress) - 1);
    strncpy(stNTPInfo.astNTPServerInfoList->szDomainName, m_strNtpDomainName.GetBuffer(0), sizeof(stNTPInfo.astNTPServerInfoList->szDomainName) - 1);
    stNTPInfo.astNTPServerInfoList->ulPort = m_ulNtpProt;
    stNTPInfo.astNTPServerInfoList->ulSynchronizeInterval = m_ulNtpSynInterval;

    BOOL bRet = NETDEV_SetDevConfig(lpDevHandle, dwChannelID, NETDEV_SET_NTPCFG_EX, &stNTPInfo, sizeof(stNTPInfo));
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Set NTP cfg");
        return;
    }
    gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstNetworkInfo->stNetWorkNTP = stNTPInfo;
    NETDEMO_LOG_SUCC(NULL, "Set NTP cfg");
    return;
}