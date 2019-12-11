
#include "stdafx.h"
#include "NetDemo.h"
#include "DlgPTZExtend.h"


IMPLEMENT_DYNAMIC(CDlgPTZExtend, CDialog)

CDlgPTZExtend::CDlgPTZExtend(CWnd* pParent /*=NULL*/)
    : CDialog(CDlgPTZExtend::IDD, pParent)
{
    m_dwPtzSpeed = 1;
}

CDlgPTZExtend::~CDlgPTZExtend()
{
}

void CDlgPTZExtend::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_CRUISE, m_oCruiseList);
    DDX_Control(pDX, IDC_COMBO_CRUISE, m_oCBoxPresetPatrols);
    DDX_Control(pDX, IDC_COMBO_EXTEND_PRESET, m_oCBoxExtendPreset);
}


BEGIN_MESSAGE_MAP(CDlgPTZExtend, CDialog)
    ON_BN_CLICKED(IDC_BTN_PTZ_WIPER_ON, &CDlgPTZExtend::OnBnClickedBtnPtzWiperOn)
    ON_BN_CLICKED(IDC_BTN_PTZ_WIPER_OFF, &CDlgPTZExtend::OnBnClickedBtnPtzWiperOff)
    ON_BN_CLICKED(IDC_BTN_PTZ_LIGHT_ON, &CDlgPTZExtend::OnBnClickedBtnPtzLightOn)
    ON_BN_CLICKED(IDC_BTN_PTZ_LIGHT_OFF, &CDlgPTZExtend::OnBnClickedBtnPtzLightOff)
    ON_BN_CLICKED(IDC_BTN_PTZ_HEATER_ON, &CDlgPTZExtend::OnBnClickedBtnPtzHeaterOn)
    ON_BN_CLICKED(IDC_BTN_PTZ_HEATER_OFF, &CDlgPTZExtend::OnBnClickedBtnPtzHeaterOff)
    ON_BN_CLICKED(IDC_BTN_PTZ_SNOWREMOVAL_ON, &CDlgPTZExtend::OnBnClickedBtnPtzSnowremovalOn)
    ON_BN_CLICKED(IDC_BTN_PTZ_SNOWREMOVAL_OFF, &CDlgPTZExtend::OnBnClickedBtnPtzSnowremovalOff)
    ON_BN_CLICKED(IDC_BTN_GET_ROUTE, &CDlgPTZExtend::OnBnClickedBtnGetRoute)
    ON_BN_CLICKED(IDC_BTN_START_RECORD_ROUTE, &CDlgPTZExtend::OnBnClickedBtnStartRecordRoute)
    ON_BN_CLICKED(IDC_BTN_STOP_RECORD_ROUTE, &CDlgPTZExtend::OnBnClickedBtnStopRecordRoute)
    ON_BN_CLICKED(IDC_BTN_START_ROUTE_PATROL, &CDlgPTZExtend::OnBnClickedBtnStartRoutePatrol)
    ON_BN_CLICKED(IDC_BTN_STOP_RECORD_PATROL, &CDlgPTZExtend::OnBnClickedBtnStopRecordPatrol)
    ON_BN_CLICKED(IDC_BTN_GET_PATROL, &CDlgPTZExtend::OnBnClickedBtnGetPatrol)
    ON_CBN_SELCHANGE(IDC_COMBO_CRUISE, &CDlgPTZExtend::OnCbnSelchangeComboCruise)
    ON_BN_CLICKED(IDC_BTN_POINT_ADD, &CDlgPTZExtend::OnBnClickedBtnAddPoint)
    ON_BN_CLICKED(IDC_BTN_EDIT_POINT, &CDlgPTZExtend::OnBnClickedBtnEditPoint)
    ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_CRUISE, &CDlgPTZExtend::OnLvnItemchangedListCruise)
    ON_BN_CLICKED(IDC_BTN_POINT_DEL, &CDlgPTZExtend::OnBnClickedBtnPointDel)
    ON_BN_CLICKED(IDC_BTN_SAVE_PATROL, &CDlgPTZExtend::OnBnClickedBtnSavePatrol)
    ON_BN_CLICKED(IDC_BTN_DELETE_PATROL, &CDlgPTZExtend::OnBnClickedBtnDeletePatrol)
    ON_BN_CLICKED(IDC_BTN_START_PATROL, &CDlgPTZExtend::OnBnClickedBtnStartPatrol)
    ON_BN_CLICKED(IDC_BTN_STOP_PATROL, &CDlgPTZExtend::OnBnClickedBtnStopPatrol)
    ON_CBN_SELCHANGE(IDC_COMBO_EXTEND_PRESET, &CDlgPTZExtend::OnCbnSelchangeComboExtendPreset)
END_MESSAGE_MAP()

BOOL CDlgPTZExtend::OnInitDialog()
{
    CDialog::OnInitDialog();
    CenterWindow();
    InitCruiseList();
    InitPresetPatrolsCombo();
    return TRUE;
}

void CDlgPTZExtend::SetPtzSpeed(INT32 Speed)
{
    m_dwPtzSpeed = Speed;
}

void CDlgPTZExtend::OnBnClickedBtnPtzWiperOn()
{
    LPVOID lpHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChID = ga_pMainDlg->GetChlID();
    BOOL bRet = NETDEV_PTZControl_Other(lpHandle, dwChID, NETDEV_PTZ_BRUSHON, m_dwPtzSpeed);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Wiper On");
    }
    else
    {
        NETDEMO_LOG_SUCC(NULL, "Wiper On");
    }

    return;
}


void CDlgPTZExtend::OnBnClickedBtnPtzWiperOff()
{
    LPVOID lpHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChID = ga_pMainDlg->GetChlID();
    BOOL bRet = NETDEV_PTZControl_Other(lpHandle, dwChID, NETDEV_PTZ_BRUSHOFF, m_dwPtzSpeed);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Wiper Off");
    }
    else
    {
        NETDEMO_LOG_SUCC(NULL, "Wiper Off");
    }

    return;
}

void CDlgPTZExtend::OnBnClickedBtnPtzLightOn()
{
    LPVOID lpHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChID = ga_pMainDlg->GetChlID();
    BOOL bRet = NETDEV_PTZControl_Other(lpHandle, dwChID, NETDEV_PTZ_LIGHTON, m_dwPtzSpeed);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Light On");
    }
    else
    {
        NETDEMO_LOG_SUCC(NULL, "Light On");
    }

    return;
}

void CDlgPTZExtend::OnBnClickedBtnPtzLightOff()
{
    LPVOID lpHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChID = ga_pMainDlg->GetChlID();
    BOOL bRet = NETDEV_PTZControl_Other(lpHandle, dwChID, NETDEV_PTZ_LIGHTOFF, m_dwPtzSpeed);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Light Off");
    }
    else
    {
        NETDEMO_LOG_SUCC(NULL, "Light Off");
    }

    return;
}

void CDlgPTZExtend::OnBnClickedBtnPtzHeaterOn()
{
    LPVOID lpHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChID = ga_pMainDlg->GetChlID();

    BOOL bRet = NETDEV_PTZControl_Other(lpHandle, dwChID, NETDEV_PTZ_HEATON, m_dwPtzSpeed);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Heater On");
    }
    else
    {
        NETDEMO_LOG_SUCC(NULL, "Heater On");
    }

    return;
}

void CDlgPTZExtend::OnBnClickedBtnPtzHeaterOff()
{
    LPVOID lpHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChID = ga_pMainDlg->GetChlID();

    BOOL bRet = NETDEV_PTZControl_Other(lpHandle, dwChID, NETDEV_PTZ_HEATOFF, m_dwPtzSpeed);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Heater Off");
    }
    else
    {
        NETDEMO_LOG_SUCC(NULL, "Heater Off");
    }

    return;
}

void CDlgPTZExtend::OnBnClickedBtnPtzSnowremovalOn()
{
    LPVOID lpHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChID = ga_pMainDlg->GetChlID();

    BOOL bRet = NETDEV_PTZControl_Other(lpHandle, dwChID, NETDEV_PTZ_SNOWREMOINGON, m_dwPtzSpeed);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Snow removal On");
    }
    else
    {
        NETDEMO_LOG_SUCC(NULL, "Snow removal On");
    }

    return;
}

void CDlgPTZExtend::OnBnClickedBtnPtzSnowremovalOff()
{
    LPVOID lpHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChID = ga_pMainDlg->GetChlID();

    BOOL bRet = NETDEV_PTZControl_Other(lpHandle, dwChID, NETDEV_PTZ_SNOWREMOINGOFF, m_dwPtzSpeed);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Snow removal Off");
    }
    else
    {
        NETDEMO_LOG_SUCC(NULL, "Snow removal Off");
    }

    return;
}

void CDlgPTZExtend::OnBnClickedBtnGetRoute()
{
    LPVOID lpHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChID = ga_pMainDlg->GetChlID();

    NETDEV_PTZ_TRACK_INFO_S stTrackCruiseInfo;
    memset(&stTrackCruiseInfo, 0, sizeof(NETDEV_PTZ_TRACK_INFO_S));

    BOOL bRet = NETDEV_PTZGetTrackCruise(lpHandle, dwChID, &stTrackCruiseInfo);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Get Route");
    }
    else
    {
        NETDEMO_LOG_SUCC(NULL, "Get Route");
    }

    CHAR szTmp[NETDEV_LEN_64] = {0};
    UTF8ToMB(stTrackCruiseInfo.aszTrackName[0], szTmp, sizeof(szTmp) - 1);
    GetDlgItem(IDC_EDIT_ROUTE)->SetWindowText(szTmp);
    return;
}

void CDlgPTZExtend::OnBnClickedBtnStartRecordRoute()
{
    LPVOID lpHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChID = ga_pMainDlg->GetChlID();
    CPlayWnd *pPlayWnd = (CPlayWnd*)ga_pMainDlg->GetActiveWindow();

    NETDEV_PTZ_TRACK_INFO_S stTrackCruiseInfo;
    memset(&stTrackCruiseInfo, 0, sizeof(NETDEV_PTZ_TRACK_INFO_S));
    BOOL bRet = NETDEV_PTZGetTrackCruise(lpHandle, dwChID, &stTrackCruiseInfo);
    if(TRUE != bRet)
    {
        /* Get error codes */
        NETDEMO_LOG_ERROR(NULL, "Get Route");
        return;
    }

    if (0 == stTrackCruiseInfo.dwTrackNum)
    {
        /* Use PTZ to record route */
        bRet = NETDEV_PTZTrackCruise(lpHandle, dwChID, NETDEV_PTZ_TRACKCRUISEADD, stTrackCruiseInfo.aszTrackName[0]);
        if(TRUE != bRet)
        {
            NETDEMO_LOG_ERROR(NULL, "Creat Route");
            return;
        }

        stTrackCruiseInfo.dwTrackNum++;
    }

    bRet = NETDEV_PTZTrackCruise(lpHandle, dwChID, NETDEV_PTZ_TRACKCRUISEREC, stTrackCruiseInfo.aszTrackName[0]);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Start Recording Route");
        return;
    }

    NETDEMO_LOG_SUCC(NULL, "Start Recording Route");

    return;
}

void CDlgPTZExtend::OnBnClickedBtnStopRecordRoute()
{
    LPVOID lpHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChID = ga_pMainDlg->GetChlID();
    CPlayWnd *pPlayWnd = (CPlayWnd*)ga_pMainDlg->GetActiveWindow();

    NETDEV_PTZ_TRACK_INFO_S stTrackCruiseInfo;
    memset(&stTrackCruiseInfo, 0, sizeof(NETDEV_PTZ_TRACK_INFO_S));

    BOOL bRet = NETDEV_PTZGetTrackCruise(lpHandle, dwChID, &stTrackCruiseInfo);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Get Route");
        return;
    }

    bRet = NETDEV_PTZTrackCruise(lpHandle, dwChID, NETDEV_PTZ_TRACKCRUISERECSTOP, stTrackCruiseInfo.aszTrackName[0]);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Stop Recording Route");
        return;
    }

    NETDEMO_LOG_SUCC(NULL, "Stop Recording Route");

    return;
}

void CDlgPTZExtend::OnBnClickedBtnStartRoutePatrol()
{
    LPVOID lpHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChID = ga_pMainDlg->GetChlID();
    CPlayWnd *pPlayWnd = (CPlayWnd*)ga_pMainDlg->GetActiveWindow();

    NETDEV_PTZ_TRACK_INFO_S stTrackCruiseInfo;
    memset(&stTrackCruiseInfo, 0, sizeof(NETDEV_PTZ_TRACK_INFO_S));

    BOOL bRet = NETDEV_PTZGetTrackCruise(lpHandle, dwChID, &stTrackCruiseInfo);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Get Route");
        return;
    }

    bRet = NETDEV_PTZTrackCruise(lpHandle, dwChID, NETDEV_PTZ_TRACKCRUISE, stTrackCruiseInfo.aszTrackName[0]);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Start Route patrol");
    }
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Start Route patrol");
        return;
    }
    else
    {
        pPlayWnd->SetTrackingState(TRUE);
        NETDEMO_LOG_SUCC(NULL, "Start Route patrol");
    }

    return;
}

void CDlgPTZExtend::OnBnClickedBtnStopRecordPatrol()
{
    LPVOID lpHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChID = ga_pMainDlg->GetChlID();
    CPlayWnd *pPlayWnd = (CPlayWnd*)ga_pMainDlg->GetActiveWindow();

    if (!pPlayWnd->GetTrackingState())
    {
        NETDEMO_LOG_ERROR(NULL, "Tracking");
        return;
    }

    NETDEV_PTZ_TRACK_INFO_S stTrackCruiseInfo;
    memset(&stTrackCruiseInfo, 0, sizeof(NETDEV_PTZ_TRACK_INFO_S));

    BOOL bRet = NETDEV_PTZGetTrackCruise(lpHandle, dwChID, &stTrackCruiseInfo);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Get Route");
        return;
    }

    bRet = NETDEV_PTZTrackCruise(lpHandle, dwChID, NETDEV_PTZ_TRACKCRUISESTOP, stTrackCruiseInfo.aszTrackName[0]);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Stop Route patrol");
        return;
    }
    else
    {
        pPlayWnd->SetTrackingState(FALSE);
        NETDEMO_LOG_SUCC(NULL, "Stop Route patrol");
    }

    return;
}

void CDlgPTZExtend::InitCruiseList()
{
    m_oCruiseList.InsertColumn(0, "", LVCFMT_LEFT, 0, -1); 

    CString str = "Cruise Point";
    m_oCruiseList.InsertColumn(1, str, LVCFMT_LEFT, 70);

    str = "Stay Time";
    m_oCruiseList.InsertColumn(2, str, LVCFMT_LEFT, 70);

    str = "Speed";
    m_oCruiseList.InsertColumn(3, str, LVCFMT_LEFT, 70);

    m_oCruiseList.SetExtendedStyle(m_oCruiseList.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES);

    return;
}


void CDlgPTZExtend::InitPresetPatrolsCombo()
{
    m_oCBoxPresetPatrols.ResetContent();

    char temp[NETDEV_LEN_16] = {0};
    for (INT32 i = 1; i <= NETDEV_MAX_CRUISEROUTE_NUM; i++)
    {
        memset(temp,0,sizeof(NETDEV_LEN_16));
        itoa(i,temp,10);
        m_oCBoxPresetPatrols.AddString(temp);
    }

    return;
}

void CDlgPTZExtend::OnBnClickedBtnGetPatrol()
{
    LPVOID lpHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChID = ga_pMainDlg->GetChlID();
    INT32 dwCurDevIndex = ga_pMainDlg->GetCurDeviceIndex();
    CPlayWnd *pPlayWnd = (CPlayWnd*)ga_pMainDlg->GetActiveWindow();

    NETDEV_CRUISE_LIST_S stCuriseList;
    memset(&stCuriseList, 0, sizeof(NETDEV_CRUISE_LIST_S));

    BOOL bRet = NETDEV_PTZGetCruise(lpHandle, dwChID, &stCuriseList);
    if(TRUE != bRet)
    {
        m_oCruiseList.DeleteAllItems();
        NETDEMO_LOG_ERROR(NULL, "Get cruise");
    }  
    else
    {
        gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwChID-1].stCruiseList = stCuriseList;
    }

    m_oCBoxPresetPatrols.SetCurSel(0);
    OnCbnSelchangeComboCruise();
    GetPresetID();
}

void CDlgPTZExtend::GetPresetID()
{
    LPVOID lpHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChID = ga_pMainDlg->GetChlID();

    m_oCBoxExtendPreset.ResetContent();
    NETDEV_PTZ_ALLPRESETS_S stPtzPresets;
    memset(&stPtzPresets, 0, sizeof(stPtzPresets));

    INT32 dwBytesReturned = 0;
    BOOL bRet = NETDEV_GetDevConfig(lpHandle, dwChID, NETDEV_GET_PTZPRESETS, (LPVOID)&stPtzPresets, sizeof(NETDEV_PTZ_ALLPRESETS_S), &dwBytesReturned);
    if(TRUE != bRet)
    {
        if (NETDEV_E_NO_RESULT == NETDEV_GetLastError())
        {
            NETDEMO_LOG_ERROR(NULL, "Preset list is emtpy.");
            GetDlgItem(IDC_EDIT_PTZ_PRESET_NAME)->SetWindowText("");
            return;
        }

        NETDEMO_LOG_ERROR(NULL, "Get presets");
    }
    else
    {

        CString strCuriseID;
        for(INT32 i = 0; i < stPtzPresets.dwSize; i++)
        {
            strCuriseID.Format("%d",stPtzPresets.astPreset[i].dwPresetID);
            m_oCBoxExtendPreset.AddString(strCuriseID);
        }

        m_oCBoxExtendPreset.SetCurSel(0);
        CHAR szTmp[NETDEV_LEN_32] = {0};
        UTF8ToMB(stPtzPresets.astPreset[0].szPresetName, szTmp, sizeof(szTmp) - 1);
        GetDlgItem(IDC_EDIT_EXTEND_PRESET_NAME)->SetWindowText(szTmp);
    }

    return;
}

void CDlgPTZExtend::OnCbnSelchangeComboCruise()
{
    INT32 dwCurDevIndex = ga_pMainDlg->GetCurDeviceIndex();
    int nSplit = m_oCBoxPresetPatrols.GetCurSel();
    INT32 dwChID = ga_pMainDlg->GetChlID();

    if (( dwChID <= 0 )|| (dwCurDevIndex < 0 ))
    {
        NETDEMO_LOG_ERROR(NULL, "Please select device");
        return;
    }
    m_oCruiseList.DeleteAllItems();

    NETDEMO_CHANNEL_INFO strDevInfo = gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwChID-1];

    for (INT32 i = 0; i < strDevInfo.stCruiseList.dwSize; i++)
    {
        if (strDevInfo.stCruiseList.astCruiseInfo[i].dwCuriseID == nSplit+1)
        {
            NETDEV_CRUISE_INFO_S strCruiseInfo = strDevInfo.stCruiseList.astCruiseInfo[i];

            CHAR szTmp[NETDEV_LEN_32] = {0};
            UTF8ToMB(strCruiseInfo.szCuriseName, szTmp, sizeof(szTmp) - 1);
            GetDlgItem(IDC_EDIT_CRUISE)->SetWindowText(szTmp);

            for (INT32 j=0;j<strCruiseInfo.dwSize;j++)
            {
                INT32 dwCount = m_oCruiseList.GetItemCount();
                INT32 dwRow = m_oCruiseList.InsertItem(dwCount, "");
                char szPresetID[NETDEV_LEN_32] = {0};
                char szStayTime[NETDEV_LEN_32] = {0};
                char szSpeed[NETDEV_LEN_32] = {0};
                sprintf(szPresetID, "%d", strCruiseInfo.astCruisePoint[j].dwPresetID);
                sprintf(szStayTime, "%d", strCruiseInfo.astCruisePoint[j].dwStayTime/1000);
                sprintf(szSpeed, "%d", strCruiseInfo.astCruisePoint[j].dwSpeed);

                m_oCruiseList.SetItemText(dwRow, 1, szPresetID);
                m_oCruiseList.SetItemText(dwRow, 2, szStayTime);
                m_oCruiseList.SetItemText(dwRow, 3, szSpeed);
            }
            break;
        }
        else
        {
            GetDlgItem(IDC_EDIT_CRUISE)->SetWindowText("");
        }
    }

    return;
}

void CDlgPTZExtend::OnBnClickedBtnAddPoint()
{
    INT32 dwCurDevIndex = ga_pMainDlg->GetCurDeviceIndex();
    int nSplit = m_oCBoxPresetPatrols.GetCurSel();
    INT32 dwChID = ga_pMainDlg->GetChlID();
    if (( dwChID <= 0 )|| (dwCurDevIndex < 0 ))
    {
        NETDEMO_LOG_ERROR(NULL, "Please select device");
        return;
    }
    
    CString strPreSetID;
    CString strStayTime;
    CString strSpeed;
    m_oCBoxExtendPreset.GetWindowText(strPreSetID);
    GetDlgItem(IDC_EDIT_POINT_STAYTIME)->GetWindowText(strStayTime);
    GetDlgItem(IDC_EDIT_POINT_SPEED)->GetWindowText(strSpeed);

    INT32 dwSpeed = atoi(strSpeed.GetBuffer(0));
    if ("" == strStayTime || "" == strSpeed || dwSpeed>40)
    {
        NETDEMO_LOG_ERROR(NULL, "Invalid staytime or speed");
        return;
    }

    INT32 dwCount = m_oCruiseList.GetItemCount();
    INT32 dwRow = m_oCruiseList.InsertItem(dwCount, "");
    
    if ((NETDEV_MAX_CRUISEPOINT_NUM <= dwCount))
    {
        NETDEMO_LOG_ERROR(NULL, "No more cruise point available");
        return;
    }

    LPNETDEMO_CHANNEL_INFO pstrDevInfo = &gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwChID-1];
    LPNETDEV_CRUISE_INFO_S strCruiseInfo = &pstrDevInfo->stCruiseList.astCruiseInfo[nSplit];

    m_oCruiseList.SetItemText(dwRow, 1, strPreSetID);
    m_oCruiseList.SetItemText(dwRow, 2, strStayTime);
    m_oCruiseList.SetItemText(dwRow, 3, strSpeed);

    return;
}

void CDlgPTZExtend::OnBnClickedBtnEditPoint()
{
    CString strPreSetID;
    CString strStayTime;
    CString strSpeed;

    m_oCBoxExtendPreset.GetWindowText(strPreSetID);
    GetDlgItem(IDC_EDIT_POINT_STAYTIME)->GetWindowText(strStayTime);
    GetDlgItem(IDC_EDIT_POINT_SPEED)->GetWindowText(strSpeed);

    if ("" == strStayTime || "" == strSpeed)
    {
        NETDEMO_LOG_ERROR(NULL, "Invalid stay time or speed");
        return;
    }

    POSITION pos=m_oCruiseList.GetFirstSelectedItemPosition();
    if(pos==NULL)
    {
        return;
    }

    INT32 dwSelect=(int)m_oCruiseList.GetNextSelectedItem(pos);
    if (dwSelect < 0)
    {
        return;
    }

    m_oCruiseList.SetItemText(dwSelect, 1, strPreSetID);
    m_oCruiseList.SetItemText(dwSelect, 2, strStayTime);
    m_oCruiseList.SetItemText(dwSelect, 3, strSpeed);

    return;
}

void CDlgPTZExtend::OnLvnItemchangedListCruise(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
    POSITION pos=m_oCruiseList.GetFirstSelectedItemPosition();
    if(pos==NULL)
    {
        return;
    }

    INT32 dwSelect=(int)m_oCruiseList.GetNextSelectedItem(pos);
    if (dwSelect < 0)
    {
        return;
    }

    CString strPreSetID;
    CString strStayTime;
    CString strSpeed;

    strPreSetID = m_oCruiseList.GetItemText(dwSelect,1);
    strStayTime = m_oCruiseList.GetItemText(dwSelect,2);
    strSpeed = m_oCruiseList.GetItemText(dwSelect,3);
    m_oCBoxExtendPreset.SetWindowText(strPreSetID);
    GetDlgItem(IDC_EDIT_POINT_STAYTIME)->SetWindowText(strStayTime);
    GetDlgItem(IDC_EDIT_POINT_SPEED)->SetWindowText(strSpeed);

    for (int i = 0; i < m_oCBoxExtendPreset.GetCount(); i++)
    {
        CString strTempPreSetID;
        m_oCBoxExtendPreset.GetLBText(i, strTempPreSetID);
        if (strTempPreSetID == strPreSetID)
        {
            m_oCBoxExtendPreset.SetCurSel(i);
            break;
        }
    }

    OnCbnSelchangeComboExtendPreset();
    *pResult = 0;
}

void CDlgPTZExtend::OnBnClickedBtnPointDel()
{
    POSITION pos=m_oCruiseList.GetFirstSelectedItemPosition();
    if(NULL == pos)
    {
        return;
    }

    INT32 dwSelect=(int)m_oCruiseList.GetNextSelectedItem(pos);
    if (dwSelect < 0)
    {
        return;
    }

    m_oCruiseList.DeleteItem(dwSelect);

    return;
}

void CDlgPTZExtend::OnBnClickedBtnSavePatrol()
{
    CString StrCruiseName;
    GetDlgItem(IDC_EDIT_CRUISE)->GetWindowText(StrCruiseName);
    if ("" == StrCruiseName)
    {
        NETDEMO_LOG_ERROR(NULL, "Please entry cruise name");
        return;
    }

    INT32 dwCurDevIndex = ga_pMainDlg->GetCurDeviceIndex();
    int nSplit = m_oCBoxPresetPatrols.GetCurSel();
    INT32 dwChID = ga_pMainDlg->GetChlID();
    LPVOID lpHandle = ga_pMainDlg->GetDevHandle();

    if (( dwChID <= 0 )|| (dwCurDevIndex < 0 ))
    {
        NETDEMO_LOG_ERROR(NULL, "Please select Device");
        return;
    }

    LPNETDEMO_CHANNEL_INFO pstrDevInfo = &gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwChID-1];
    LPNETDEV_CRUISE_INFO_S strCruiseInfo = &pstrDevInfo->stCruiseList.astCruiseInfo[nSplit];

    CString strPreSetID;
    CString strStayTime;
    CString strSpeed;
    strCruiseInfo->dwCuriseID = nSplit + 1;

    MBToUTF8(StrCruiseName.GetBuffer(0), strCruiseInfo->szCuriseName, sizeof(strCruiseInfo->szCuriseName) - 1);

    INT32 dwSize = strCruiseInfo->dwSize;
    strCruiseInfo->dwSize = m_oCruiseList.GetItemCount();

    if (strCruiseInfo->dwSize <= 0)
    {
        NETDEMO_LOG_ERROR(NULL, "Please add one item");
        return;
    }

    for (INT32 i = 0;i < strCruiseInfo->dwSize;i++)
    {
        strPreSetID = m_oCruiseList.GetItemText(i,1);
        strStayTime = m_oCruiseList.GetItemText(i,2);
        strSpeed = m_oCruiseList.GetItemText(i,3);

        strCruiseInfo->astCruisePoint[i].dwPresetID = atoi(strPreSetID.GetBuffer(0));
        strCruiseInfo->astCruisePoint[i].dwStayTime = atoi(strStayTime.GetBuffer(0))*1000;
        strCruiseInfo->astCruisePoint[i].dwSpeed = atoi(strSpeed.GetBuffer(0));
    }

    if (dwSize > 0)
    {
        BOOL bRet = NETDEV_PTZCruise_Other(lpHandle, dwChID, NETDEV_PTZ_MODIFY_CRUISE,strCruiseInfo);
        if(TRUE != bRet)
        {
            NETDEMO_LOG_ERROR(NULL, "Modify cruise");
        }
        else
        {
            NETDEMO_LOG_SUCC(NULL, "Modify cruise");
        }
    }
    else
    {
        BOOL bRet = NETDEV_PTZCruise_Other(lpHandle, dwChID, NETDEV_PTZ_ADD_CRUISE,strCruiseInfo);
        if(TRUE != bRet)
        {
            NETDEMO_LOG_ERROR(NULL, "Add cruise");
        }
        else
        {
            NETDEMO_LOG_SUCC(NULL, "Add cruise");
        }
    }

    OnBnClickedBtnGetPatrol();

    return;
}


void CDlgPTZExtend::OnBnClickedBtnDeletePatrol()
{
    BOOL bRet = handleCruise(NETDEV_PTZ_DEL_CRUISE);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Delete cruise");
        return;
    }
    else
    {
        NETDEMO_LOG_SUCC(NULL, "Delete cruise");
    }

    INT32 dwCurDevIndex = ga_pMainDlg->GetCurDeviceIndex();
    INT32 dwSplit = m_oCBoxPresetPatrols.GetCurSel();
    INT32 dwChID = ga_pMainDlg->GetChlID();

    if (( dwChID <= 0 )|| (dwCurDevIndex < 0 ))
    {
        NETDEMO_LOG_ERROR(NULL, "Please select a device");
        return;
    }

    LPNETDEMO_CHANNEL_INFO pstrDevInfo = &gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwChID-1];
    LPNETDEV_CRUISE_INFO_S strCruiseInfo = &pstrDevInfo->stCruiseList.astCruiseInfo[dwSplit];

    memset(strCruiseInfo->astCruisePoint,0,sizeof(strCruiseInfo->astCruisePoint));
    strCruiseInfo->dwCuriseID = 0;
    strCruiseInfo->dwSize = 0;
    memset(strCruiseInfo->szCuriseName,0,sizeof(strCruiseInfo->szCuriseName));
    
    m_oCBoxPresetPatrols.SetCurSel(0);
    OnCbnSelchangeComboCruise();

    return;
}
BOOL CDlgPTZExtend::handleCruise(NETDEV_PTZ_CRUISECMD_E eCruisecmd)
{
    INT32 dwCurDevIndex = ga_pMainDlg->GetCurDeviceIndex();
    int nSplit = m_oCBoxPresetPatrols.GetCurSel();
    INT32 dwChID = ga_pMainDlg->GetChlID();
    LPVOID lpHandle = ga_pMainDlg->GetDevHandle();

    if (( dwChID <= 0 )|| (dwCurDevIndex < 0 ) || (NULL == lpHandle))
    {
        NETDEMO_LOG_ERROR(NULL, "Please select device");
        return FALSE;
    }

    LPNETDEMO_CHANNEL_INFO pstrDevInfo = &gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwChID-1];
    LPNETDEV_CRUISE_INFO_S strCruiseInfo = &pstrDevInfo->stCruiseList.astCruiseInfo[nSplit];

    return NETDEV_PTZCruise_Other(lpHandle, dwChID, eCruisecmd,strCruiseInfo);
}

void CDlgPTZExtend::OnBnClickedBtnStartPatrol()
{
    BOOL bRet = handleCruise(NETDEV_PTZ_RUN_CRUISE);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Start cruise");
    }
    else
    {
        NETDEMO_LOG_SUCC(NULL, "Start cruise");
    }

    return;
}

void CDlgPTZExtend::OnBnClickedBtnStopPatrol()
{
    BOOL bRet = handleCruise(NETDEV_PTZ_STOP_CRUISE);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Stop cruise");
    }
    else
    {
        NETDEMO_LOG_SUCC(NULL, "Stop cruise");
    }

    return;
}

void CDlgPTZExtend::OnCbnSelchangeComboExtendPreset()
{
    LPVOID lpHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChID = ga_pMainDlg->GetChlID();

    NETDEV_PTZ_ALLPRESETS_S stPtzPresets;
    memset(&stPtzPresets, 0, sizeof(stPtzPresets));

    INT32 dwBytesReturned = 0;
    BOOL bRet = NETDEV_GetDevConfig(lpHandle, dwChID, NETDEV_GET_PTZPRESETS, (LPVOID)&stPtzPresets, sizeof(NETDEV_PTZ_ALLPRESETS_S), &dwBytesReturned);
    if(TRUE != bRet)
    {
        if (NETDEV_E_NO_RESULT == NETDEV_GetLastError())
        {
            NETDEMO_LOG_ERROR(NULL, "Presets list is emtpy.");
            GetDlgItem(IDC_EDIT_PTZ_PRESET_NAME)->SetWindowText("");
            return;
        }

        NETDEMO_LOG_ERROR(NULL, "Get presets");
    }
    else
    {
        int nSplit = m_oCBoxExtendPreset.GetCurSel();
        CString strPreSetID;
        m_oCBoxExtendPreset.GetLBText(nSplit, strPreSetID);
        for(INT32 i = 0; i < stPtzPresets.dwSize; i++)
        {
            if(stPtzPresets.astPreset[i].dwPresetID == atoi(strPreSetID.GetBuffer(0)))
            {
                UTF8ToMB(stPtzPresets.astPreset[i].szPresetName, stPtzPresets.astPreset[i].szPresetName, sizeof(stPtzPresets.astPreset[i].szPresetName) - 1);
                GetDlgItem(IDC_EDIT_EXTEND_PRESET_NAME)->SetWindowText(stPtzPresets.astPreset[i].szPresetName);
                return;
            }
        }
    }

    return;
}
