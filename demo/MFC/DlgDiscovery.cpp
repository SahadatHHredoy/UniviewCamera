// DlgDiscovery.cpp : 

#include "stdafx.h"
#include "NetDemo.h"
#include "DlgDiscovery.h"

#define COL_INDEX_DEV_TYPE              1
#define COL_INDEX_DEV_IP                2
#define COL_INDEX_DEV_PORT              3
#define COL_INDEX_DEV_MAC               4
#define COL_INDEX_DEV_SERAILNUM         5
#define COL_INDEX_DEV_MANUFACTURER      6

void STDCALL NETDEV_DISCOVERY_CB(IN LPNETDEV_DISCOVERY_DEVINFO_S pstDevInfo, void* lParam)
{
    CDlgDiscovery *pDlgDiscovery = (CDlgDiscovery*)lParam;
    pDlgDiscovery->handleDiscovery(pstDevInfo);
    return;
}

IMPLEMENT_DYNAMIC(CDlgDiscovery, CDialog)

CDlgDiscovery::CDlgDiscovery(CWnd* pParent /*=NULL*/)
    : CDialog(CDlgDiscovery::IDD, pParent)
    , m_dwDeviceNum(0)
{
}

CDlgDiscovery::~CDlgDiscovery()
{
}

void CDlgDiscovery::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_DEVICE_LIST, m_oDeviceInfoList);
    DDX_Text(pDX, IDC_EDIT_USER_NAME, m_strUserName);
    DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
    DDX_Text(pDX, IDC_IPADD_BEGIN_IP, m_strBeginIP);
    DDX_Text(pDX, IDC_IPADD_END_IP, m_strEndIP);
    DDX_Text(pDX, IDC_LAB_DEVICE_NUM, m_dwDeviceNum);

}


BOOL CDlgDiscovery::OnInitDialog()
{
    CDialog::OnInitDialog();
    CenterWindow();

    InitListCtrl();

    CFont oFont;
    oFont.CreateFont(60,30,0,0,120, FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_SWISS,"Arial");
    CEdit *pEdit=(CEdit *)GetDlgItem(IDC_LAB_DEVICE_NUM);
    pEdit->SetFont(&oFont,FALSE);
    GetDlgItem(IDC_LAB_DEVICE_NUM)->SetFont(&oFont);

    return TRUE;
}


BEGIN_MESSAGE_MAP(CDlgDiscovery, CDialog)
    ON_BN_CLICKED(IDC_BUTTON_DISCOVERY, &CDlgDiscovery::OnBnClickedSegmentDiscovery)
    ON_BN_CLICKED(IDC_BUTTON_AUTO_DISCOVERY, &CDlgDiscovery::OnBnClickedAutoDiscovery)
    ON_BN_CLICKED(IDC_BUTTON_ADD_DEVICE, &CDlgDiscovery::OnBnClickedAddDevice)
    ON_WM_CLOSE()
END_MESSAGE_MAP()


void CDlgDiscovery::InitListCtrl()
{
    m_oDeviceInfoList.InsertColumn(0, "", LVCFMT_LEFT, 0, -1); 

    CString str="Type";
    m_oDeviceInfoList.InsertColumn(COL_INDEX_DEV_TYPE,str,LVCFMT_LEFT,100);

    str = "IP";
    m_oDeviceInfoList.InsertColumn(COL_INDEX_DEV_IP, str, LVCFMT_LEFT, 120);

    str = "Port";
    m_oDeviceInfoList.InsertColumn(COL_INDEX_DEV_PORT, str, LVCFMT_LEFT, 50);

    str = "MAC";
    m_oDeviceInfoList.InsertColumn(COL_INDEX_DEV_MAC, str, LVCFMT_LEFT, 120);

    str = "Serial Num";
    m_oDeviceInfoList.InsertColumn(COL_INDEX_DEV_SERAILNUM, str, LVCFMT_LEFT, 120);

    str = "Manufacturer";
    m_oDeviceInfoList.InsertColumn(COL_INDEX_DEV_MANUFACTURER, str, LVCFMT_LEFT, 80);

    m_oDeviceInfoList.SetExtendedStyle(m_oDeviceInfoList.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES);
}

void CDlgDiscovery::OnBnClickedSegmentDiscovery()
{
    m_oDevInfoMap.clear();
    m_dwDeviceNum = m_oDevInfoMap.size();
    GetDlgItem(IDC_LAB_DEVICE_NUM)->SetWindowText("0");

    m_oDeviceInfoList.DeleteAllItems();
    m_oDeviceInfoList.SetRedraw(FALSE);

    UpdateData(TRUE);

    BOOL bRet = NETDEV_SetDiscoveryCallBack(NETDEV_DISCOVERY_CB, this);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Set discovery callback");
    }
    else
    {
        NETDEMO_LOG_SUCC(NULL, "Set discovery callback");
    }

    bRet = NETDEV_Discovery(m_strBeginIP.GetBuffer(0), m_strEndIP.GetBuffer(0));
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Discovery");
    }
    else
    {
        NETDEMO_LOG_SUCC(NULL, "Discovery");
    }

    m_oDeviceInfoList.SetRedraw(TRUE);
    m_oDeviceInfoList.Invalidate();
    m_oDeviceInfoList.UpdateWindow();

}

void CDlgDiscovery::OnBnClickedAutoDiscovery()
{
    m_oDevInfoMap.clear();
    m_dwDeviceNum = m_oDevInfoMap.size();

    m_oDeviceInfoList.DeleteAllItems(); 
    m_oDeviceInfoList.SetRedraw(FALSE);

    UpdateData(FALSE);

    BOOL bRet = NETDEV_SetDiscoveryCallBack(NETDEV_DISCOVERY_CB, this);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Set discovery callback");
    }
    else
    {
        NETDEMO_LOG_SUCC(NULL, "Set discovery callback");
    }

    bRet = NETDEV_Discovery("0.0.0.0", "0.0.0.0");
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Auto discovery");
    }
    else
    {
        NETDEMO_LOG_SUCC(NULL, "Auto discovery");
    }

    m_oDeviceInfoList.SetRedraw(TRUE);
    m_oDeviceInfoList.Invalidate();
    m_oDeviceInfoList.UpdateWindow();
}

void CDlgDiscovery::OnBnClickedAddDevice()
{
    UpdateData(TRUE);

    if (NETDEV_LEN_64 <= m_strUserName.GetLength() || NETDEV_LEN_64 <= m_strPassword.GetLength())
    {
        NETDEMO_LOG_ERROR(NULL, "Add device, invalid username or password");
    }

    POSITION pos = m_oDeviceInfoList.GetFirstSelectedItemPosition();
    if (pos > 0)
    {
        INT32 dwIndex = (int)pos - 1;
        CString strName = m_oDeviceInfoList.GetItemText(dwIndex, COL_INDEX_DEV_TYPE);
        CString strIP = m_oDeviceInfoList.GetItemText(dwIndex, COL_INDEX_DEV_IP);
        CString strPort = m_oDeviceInfoList.GetItemText(dwIndex, COL_INDEX_DEV_PORT);

        NETDEMO_DEVICE_INFO stLocalDeviceInfo;
        strncpy(stLocalDeviceInfo.szIPAddr, strIP.GetBuffer(0), sizeof(stLocalDeviceInfo.szIPAddr) - 1);
        stLocalDeviceInfo.dwDevPort = atoi(strPort.GetBuffer(0));
        strncpy(stLocalDeviceInfo.szDevUserName,m_strUserName.GetBuffer(0),m_strUserName.GetLength());
        strncpy(stLocalDeviceInfo.szPassword,m_strPassword.GetBuffer(0),m_strPassword.GetLength());
        stLocalDeviceInfo.dwLoginType = NETDEMO_LOGTYPE_LOCAL;

        GetParent()->SendMessage(WM_ADD_DEVICE,WPARAM(NETDEMO_LOGTYPE_LOCAL),(LPARAM)&stLocalDeviceInfo);
        for(UINT32 nIndex = 1; nIndex < m_oDeviceInfoList.GetSelectedCount() && pos > 0;nIndex++)
        {
            m_oDeviceInfoList.GetNextSelectedItem(pos);
            dwIndex = (int)pos - 1;
            CString strName = m_oDeviceInfoList.GetItemText(dwIndex, COL_INDEX_DEV_TYPE);
            CString strIP = m_oDeviceInfoList.GetItemText(dwIndex, COL_INDEX_DEV_IP);
            CString strPort = m_oDeviceInfoList.GetItemText(dwIndex, COL_INDEX_DEV_PORT);

            strncpy(stLocalDeviceInfo.szIPAddr, strIP.GetBuffer(0), sizeof(stLocalDeviceInfo.szIPAddr) - 1);
            stLocalDeviceInfo.dwDevPort = atoi(strPort.GetBuffer(0));
            strncpy(stLocalDeviceInfo.szDevUserName, m_strUserName.GetBuffer(0), sizeof(stLocalDeviceInfo.szDevUserName) - 1);
            strncpy(stLocalDeviceInfo.szPassword, m_strPassword.GetBuffer(0), sizeof(stLocalDeviceInfo.szPassword) - 1);
            stLocalDeviceInfo.dwLoginType = NETDEMO_LOGTYPE_LOCAL;
            GetParent()->SendMessage(WM_ADD_DEVICE,WPARAM(NETDEMO_LOGTYPE_LOCAL),(LPARAM)&stLocalDeviceInfo);
        }
    }
    else
    {
        NETDEMO_LOG_ERROR(NULL, "Add device, please select devices");
    }
}

void CDlgDiscovery::OnClose()
{
    m_oDevInfoMap.clear();
    m_dwDeviceNum = m_oDevInfoMap.size();
    m_oDeviceInfoList.DeleteAllItems();

    UpdateData(FALSE);

    CDialog::OnClose();
}

void CDlgDiscovery::handleDiscovery(LPNETDEV_DISCOVERY_DEVINFO_S pstDevInfo)
{
    if (TRUE == isExistDevinfo(pstDevInfo))
    {
        return;
    }

    CString str;
    int nRow = m_oDeviceInfoList.InsertItem(0, "");
    switch(pstDevInfo->enDevType)
    {
    case NETDEV_DTYPE_UNKNOWN:
        str = "UNKNOWN";
        break;
    case NETDEV_DTYPE_IPC:
        str = "IPC";
        break;
    case NETDEV_DTYPE_IPC_FISHEYE:
        str = "IPC_DISECONOMIC_FISHEYE";
        break;
    case NETDEV_DTYPE_IPC_ECONOMIC_FISHEYE:
        str = "IPC_ECONOMIC_FISHEYE";
        break;
    case NETDEV_DTYPE_NVR:
        str = "NVR";
        break;
    case NETDEV_DTYPE_NVR_BACKUP:
        str = "NVR_BACKUP";
        break;
    case NETDEV_DTYPE_DC:
        str = "DC";
        break;
    case NETDEV_DTYPE_EC:
        str = "EC";
        break;
    case NETDEV_DTYPE_VMS:
        str = "VMS";
        break;
    default:
        str = "INVALID";
        break;
    }

    m_oDeviceInfoList.SetItemText(nRow, COL_INDEX_DEV_TYPE, str.GetBuffer(0));

    m_oDeviceInfoList.SetItemText(nRow, COL_INDEX_DEV_IP, pstDevInfo->szDevAddr);

    CHAR szDevPort[10] = {0};
    itoa(pstDevInfo->dwDevPort, szDevPort, 10);
    m_oDeviceInfoList.SetItemText(nRow, COL_INDEX_DEV_PORT, szDevPort);

    m_oDeviceInfoList.SetItemText(nRow, COL_INDEX_DEV_MAC, pstDevInfo->szDevMac);

    m_oDeviceInfoList.SetItemText(nRow, COL_INDEX_DEV_SERAILNUM, pstDevInfo->szDevSerailNum);

    m_oDeviceInfoList.SetItemText(nRow, COL_INDEX_DEV_MANUFACTURER, pstDevInfo->szManuFacturer);

    m_oDevInfoMap.push_back(*pstDevInfo);

    m_dwDeviceNum = m_oDevInfoMap.size();

    UpdateData(FALSE);
    return;
}

BOOL CDlgDiscovery::isExistDevinfo(const LPNETDEV_DISCOVERY_DEVINFO_S pstDiscoveryDevinfo)
{
    for (int nDevinfoIndex = 0; nDevinfoIndex < m_oDevInfoMap.size(); nDevinfoIndex++)
    {
        if ((0 == strcmp(pstDiscoveryDevinfo->szDevAddr, m_oDevInfoMap[nDevinfoIndex].szDevAddr)) &&
            (0 == strcmp(pstDiscoveryDevinfo->szDevSerailNum, m_oDevInfoMap[nDevinfoIndex].szDevSerailNum)))
        {
            return TRUE;
        }
    }

    return FALSE;
}