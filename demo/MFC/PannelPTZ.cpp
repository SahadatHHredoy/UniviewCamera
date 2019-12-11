// PTZPannel.cpp : 
//

#include "stdafx.h"
#include "NetDemo.h"
#include "PannelPTZ.h"


#define PTZ_MIN_SPEED   1
#define PTZ_MAX_SPEED   9
// CPannelPTZ 

IMPLEMENT_DYNAMIC(CPannelPTZ, CDialog)

CPannelPTZ::CPannelPTZ(CWnd* pParent /*=NULL*/)
: CDialog(CPannelPTZ::IDD, pParent)
{
    m_hLeftIcon = AfxGetApp()->LoadIcon(IDI_ICON_LEFT);
    m_hRightIcon = AfxGetApp()->LoadIcon(IDI_ICON_RIGHT);
    m_hUpIcon = AfxGetApp()->LoadIcon(IDI_ICON_UP);
    m_hDownIcon = AfxGetApp()->LoadIcon(IDI_ICON_DOWN);
    m_hLeftUpIcon = AfxGetApp()->LoadIcon(IDI_ICON_LEFTUP);
    m_hLeftDownIcon = AfxGetApp()->LoadIcon(IDI_ICON_LEFTDOWN);
    m_hRightUpIcon = AfxGetApp()->LoadIcon(IDI_ICON_RIGHTUP);
    m_hRighDowntIcon = AfxGetApp()->LoadIcon(IDI_ICON_RIGHTDOWN);
    m_hStopIcon = AfxGetApp()->LoadIcon(IDI_ICON_STOP);
}

CPannelPTZ::~CPannelPTZ()
{
}

void CPannelPTZ::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_SLIDER_SPEED, m_oSldPtzSpeed);
    DDX_Control(pDX, IDC_COMBO_PRESET, m_BoxPreset);
}


BEGIN_MESSAGE_MAP(CPannelPTZ, CDialog)
    ON_BN_CLICKED(IDC_BUTTON_PTZ_EXTEND, &CPannelPTZ::OnBnClickedButtonPtzExtend)
    ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_SPEED, &CPannelPTZ::OnNMCustomdrawSliderSpeed)
    ON_BN_CLICKED(IDC_BUTTON_PTZ_STOP, &CPannelPTZ::OnBnPTZStop)
    ON_BN_CLICKED(IDC_BTN_GET_PRESET, &CPannelPTZ::OnBnClickedBtnGetPreset)
    ON_BN_CLICKED(IDC_BTN_SET_PRESET, &CPannelPTZ::OnBnClickedBtnSetPreset)
    ON_BN_CLICKED(IDC_BTN_GOTO_PRESET, &CPannelPTZ::OnBnClickedBtnGotoPreset)
    ON_BN_CLICKED(IDC_BTN_DEL_PRESET, &CPannelPTZ::OnBnClickedBtnDelPreset)
    ON_CBN_SELCHANGE(IDC_COMBO_PRESET, &CPannelPTZ::OnCbnSelchangeComboPreset)
    ON_BN_CLICKED(IDC_BTN_FOCUS_STOP, &CPannelPTZ::OnBnPTZStopFocus)
END_MESSAGE_MAP()

BOOL CPannelPTZ::OnInitDialog()
{
    CDialog::OnInitDialog();
    m_oDlgPTZExtend.Create(IDD_DLG_PTZ_EXTEND,this);
    initButtonIco();
    InitToolTipCtrl();
    m_oSldPtzSpeed.SetRange(PTZ_MIN_SPEED,PTZ_MAX_SPEED, TRUE);
    m_oSldPtzSpeed.SetPos(5);   //default : 5

    return TRUE;
}

void CPannelPTZ::OnBnClickedButtonPtzExtend()
{
    m_oDlgPTZExtend.ShowWindow(SW_SHOW);

    return;
}

void CPannelPTZ::initButtonIco()
{
    CButton *pButton = (CButton *)GetDlgItem(IDC_BUTTON_LEFT);
    pButton->SetIcon(m_hLeftIcon);
    pButton->EnableWindow(TRUE);

    pButton = (CButton *)GetDlgItem(IDC_BUTTON_RIGHT);
    pButton->SetIcon(m_hRightIcon);
    pButton->EnableWindow(TRUE);

    pButton = (CButton *)GetDlgItem(IDC_BUTTON_UP);
    pButton->SetIcon(m_hUpIcon);
    pButton->EnableWindow(TRUE);

    pButton = (CButton *)GetDlgItem(IDC_BUTTON_DOWN);
    pButton->SetIcon(m_hDownIcon);
    pButton->EnableWindow(TRUE);

    pButton = (CButton *)GetDlgItem(IDC_BUTTON_RIGHTDOWN);
    pButton->SetIcon(m_hRighDowntIcon);
    pButton->EnableWindow(TRUE);

    pButton = (CButton *)GetDlgItem(IDC_BUTTON_RIGHTUP);
    pButton->SetIcon(m_hRightUpIcon);
    pButton->EnableWindow(TRUE);

    pButton = (CButton *)GetDlgItem(IDC_BUTTON_LEFTDOWN);
    pButton->SetIcon(m_hLeftDownIcon);
    pButton->EnableWindow(TRUE);

    pButton = (CButton *)GetDlgItem(IDC_BUTTON_LEFTUP);
    pButton->SetIcon(m_hLeftUpIcon);
    pButton->EnableWindow(TRUE);

    pButton = (CButton *)GetDlgItem(IDC_BUTTON_STOP);
    pButton->SetIcon(m_hStopIcon);
    pButton->EnableWindow(TRUE);

    return;
}

void CPannelPTZ::OnNMCustomdrawSliderSpeed(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

    m_dwPtzSpeed = m_oSldPtzSpeed.GetPos();
    char szPtzSpeed[4] = "";
    itoa(m_dwPtzSpeed, szPtzSpeed, 10);
    m_cToolTip.AddTool(&m_oSldPtzSpeed, szPtzSpeed); 
    *pResult = 0;
}

void CPannelPTZ::OnBnPTZUp()
{
    LPVOID lpHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChlID = ga_pMainDlg->GetChlID();
    if ((NULL == lpHandle) || (dwChlID < 0))
    {
        NETDEMO_LOG_ERROR(NULL, "Device Handle : %p, Chl ID : %d.", lpHandle, dwChlID);
        return;
    }

    BOOL bRet = NETDEV_PTZControl_Other(lpHandle, dwChlID, NETDEV_PTZ_TILTUP,m_dwPtzSpeed);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "PTZ up");
        return;
    }

    NETDEMO_LOG_SUCC(NULL, "PTZ up");

    return;
}

void CPannelPTZ::OnBnPTZDown()
{
    LPVOID lpHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChlID = ga_pMainDlg->GetChlID();
    if ((NULL == lpHandle) || (dwChlID < 0))
    {
        NETDEMO_LOG_ERROR(NULL, "Device Handle : %p, Chl ID : %d.", lpHandle, dwChlID);
        return;
    }

    BOOL bRet = NETDEV_PTZControl_Other(lpHandle, dwChlID, NETDEV_PTZ_TILTDOWN,m_dwPtzSpeed);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "PTZ down");
        return;
    }

    NETDEMO_LOG_SUCC(NULL, "PTZ down");
    return;
}

void CPannelPTZ::OnBnPTZLeft()
{
    LPVOID lpHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChlID = ga_pMainDlg->GetChlID();
    if ((NULL == lpHandle) || (dwChlID < 0))
    {
        NETDEMO_LOG_ERROR(NULL, "Device Handle : %p, Chl ID : %d.", lpHandle, dwChlID);
        return;
    }

    BOOL bRet = NETDEV_PTZControl_Other(lpHandle, dwChlID, NETDEV_PTZ_PANLEFT,m_dwPtzSpeed);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "PTZ left");
        return;
    }

    NETDEMO_LOG_SUCC(NULL, "PTZ left");
    return;
}

void CPannelPTZ::OnBnPTZRight()
{
    LPVOID lpHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChlID = ga_pMainDlg->GetChlID();
    if ((NULL == lpHandle) || (dwChlID < 0))
    {
        NETDEMO_LOG_ERROR(NULL, "Device Handle : %p, Chl ID : %d.", lpHandle, dwChlID);
        return;
    }

    BOOL bRet = NETDEV_PTZControl_Other(lpHandle, dwChlID, NETDEV_PTZ_PANRIGHT,m_dwPtzSpeed);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "PTZ right");
        return;
    }

    NETDEMO_LOG_SUCC(NULL, "PTZ right");
    return;
}

void CPannelPTZ::OnBnPTZLeftup()
{
    LPVOID lpHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChlID = ga_pMainDlg->GetChlID();
    if ((NULL == lpHandle) || (dwChlID < 0))
    {
        NETDEMO_LOG_ERROR(NULL, "Device Handle : %p, Chl ID : %d.", lpHandle, dwChlID);
        return;
    }

    BOOL bRet = NETDEV_PTZControl_Other(lpHandle, dwChlID, NETDEV_PTZ_LEFTUP,m_dwPtzSpeed);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "PTZ left-up");
        return;
    }

    NETDEMO_LOG_SUCC(NULL, "PTZ left-up");
    return;
}

void CPannelPTZ::OnBnPTZLeftdown()
{
    LPVOID lpHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChlID = ga_pMainDlg->GetChlID();
    if ((NULL == lpHandle) || (dwChlID < 0))
    {
        NETDEMO_LOG_ERROR(NULL, "Device Handle : %p, Chl ID : %d.", lpHandle, dwChlID);
        return;
    }

    BOOL bRet = NETDEV_PTZControl_Other(lpHandle, dwChlID, NETDEV_PTZ_LEFTDOWN,m_dwPtzSpeed);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "PTZ left-down");
        return;
    }

    NETDEMO_LOG_SUCC(NULL, "PTZ left-down");
    return;
}

void CPannelPTZ::OnBnPTZRightup()
{
    LPVOID lpHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChlID = ga_pMainDlg->GetChlID();
    if ((NULL == lpHandle) || (dwChlID < 0))
    {
        NETDEMO_LOG_ERROR(NULL, "Device Handle : %p, Chl ID : %d.", lpHandle, dwChlID);
        return;
    }

    BOOL bRet = NETDEV_PTZControl_Other(lpHandle, dwChlID, NETDEV_PTZ_RIGHTUP,m_dwPtzSpeed);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "PTZ right-up");
        return;
    }

    NETDEMO_LOG_SUCC(NULL, "PTZ right-up");
    return;
}

void CPannelPTZ::OnBnPTZRightdown()
{
    LPVOID lpHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChlID = ga_pMainDlg->GetChlID();
    if ((NULL == lpHandle) || (dwChlID < 0))
    {
        NETDEMO_LOG_ERROR(NULL, "Device Handle : %p, Chl ID : %d.", lpHandle, dwChlID);
        return;
    }

    BOOL bRet = NETDEV_PTZControl_Other(lpHandle, dwChlID, NETDEV_PTZ_RIGHTDOWN,m_dwPtzSpeed);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "PTZ right-down");
        return;
    }

    NETDEMO_LOG_SUCC(NULL, "PTZ right-down");
    return;
}

void CPannelPTZ::OnBnPTZStop()
{
    LPVOID lpHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChlID = ga_pMainDlg->GetChlID();
    if ((NULL == lpHandle) || (dwChlID < 0))
    {
        NETDEMO_LOG_ERROR(NULL, "Device Handle : %p, Chl ID : %d.", lpHandle, dwChlID);
        return;
    }

    BOOL bRet = NETDEV_PTZControl_Other(lpHandle, dwChlID, NETDEV_PTZ_ALLSTOP,m_dwPtzSpeed);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "PTZ stop");
        return;
    }

    NETDEMO_LOG_SUCC(NULL, "PTZ stop");
    return;
}

void CPannelPTZ::OnBnClickedBtnGetPreset()
{
    LPVOID lpHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChlID = ga_pMainDlg->GetChlID();
    if ((NULL == lpHandle) || (dwChlID < 0))
    {
        NETDEMO_LOG_ERROR(NULL, "Device Handle : %p, Chl ID : %d.", lpHandle, dwChlID);
        return;
    }

    m_BoxPreset.ResetContent();
    NETDEV_PTZ_ALLPRESETS_S stPtzPresets;
    memset(&stPtzPresets, 0, sizeof(stPtzPresets));

    INT32 dwBytesReturned = 0;
    BOOL bRet = NETDEV_GetDevConfig(lpHandle, dwChlID, NETDEV_GET_PTZPRESETS, (LPVOID)&stPtzPresets, sizeof(NETDEV_PTZ_ALLPRESETS_S), &dwBytesReturned);
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
        INT32 i = 0;
        for(; i < stPtzPresets.dwSize; i++)
        {
            CString strPresetID;
            strPresetID.Format("%d",stPtzPresets.astPreset[i].dwPresetID);
            m_BoxPreset.AddString(strPresetID);
        }

        if (i > 0)
        {
            m_BoxPreset.SetCurSel(0);
            CHAR szTmp[NETDEV_LEN_32] = {0};
            UTF8ToMB(stPtzPresets.astPreset[0].szPresetName, szTmp, sizeof(szTmp) - 1);
            GetDlgItem(IDC_EDIT_PTZ_PRESET_NAME)->SetWindowText(szTmp);
        }
        else
        {
            GetDlgItem(IDC_EDIT_PTZ_PRESET_NAME)->SetWindowText("");
        }
    }

    UpdateData(FALSE);

    return;
}

void CPannelPTZ::OnBnClickedBtnSetPreset()
{
    LPVOID lpHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChlID = ga_pMainDlg->GetChlID();
    if ((NULL == lpHandle) || (dwChlID < 0))
    {
        NETDEMO_LOG_ERROR(NULL, "Device Handle : %p, Chl ID : %d.", lpHandle, dwChlID);
        return;
    }

    CString strName;
    CDlgPTZPreset oDlgPtzPreset;

    if( IDOK == oDlgPtzPreset.DoModal())
    {
        INT32 lPresetID = oDlgPtzPreset.m_dwPresetID;
        strName = oDlgPtzPreset.m_strPresetName;

        if(0 >= lPresetID || lPresetID > NETDEV_MAX_PRESET_NUM)
        {
            NETDEMO_LOG_ERROR(NULL, "Preset ID invalid.");
            return;
        }

        CHAR szPresetName[NETDEV_LEN_32] = {0};
        MBToUTF8(strName.GetBuffer(0), szPresetName, sizeof(szPresetName) - 1);

        BOOL bRet = NETDEV_PTZPreset_Other(lpHandle, dwChlID, NETDEV_PTZ_SET_PRESET, szPresetName, lPresetID);
        if(TRUE != bRet)
        {
            NETDEMO_LOG_ERROR(NULL, "Set preset");
        }
        else
        {
            NETDEMO_LOG_SUCC(NULL, "Set preset");
            OnBnClickedBtnGetPreset();
        }
    }

    return;
}

void CPannelPTZ::OnBnClickedBtnGotoPreset()
{
    LPVOID lpHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChlID = ga_pMainDlg->GetChlID();
    if ((NULL == lpHandle) || (dwChlID < 0))
    {
        NETDEMO_LOG_ERROR(NULL, "Device Handle : %p, Chl ID : %d.", lpHandle, dwChlID);
        return;
    }

    CString strPresetID;
    m_BoxPreset.GetWindowText(strPresetID);
    LONG lPresetID = atoi(strPresetID.GetBuffer(0));

    CHAR szPresetName[64] = {0};
    BOOL bRet = NETDEV_PTZPreset_Other(lpHandle, dwChlID, NETDEV_PTZ_GOTO_PRESET, szPresetName, lPresetID);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Go to preset");
        return;
    }
    else
    {
        NETDEMO_LOG_SUCC(NULL, "Go to preset");
    }

    return;
}

void CPannelPTZ::OnBnClickedBtnDelPreset()
{
    LPVOID lpHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChlID = ga_pMainDlg->GetChlID();
    if ((NULL == lpHandle) || (dwChlID < 0))
    {
        NETDEMO_LOG_ERROR(NULL, "Device Handle : %p, Chl ID : %d.", lpHandle, dwChlID);
        return;
    }   

    CString strPresetID;
    m_BoxPreset.GetWindowText(strPresetID);
    INT32 dwPresetID = atoi(strPresetID.GetBuffer(0));

    CHAR szPresetName[NETDEV_NAME_MAX_LEN] = {0};

    BOOL bRet = NETDEV_PTZPreset_Other(lpHandle, dwChlID, NETDEV_PTZ_CLE_PRESET, szPresetName, dwPresetID);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Delete preset");
    }  
    else
    {
        NETDEMO_LOG_SUCC(NULL, "Delete preset");
        OnBnClickedBtnGetPreset();
    }

    return;
}

void CPannelPTZ::OnBnPTZZoomIn()
{
    LPVOID lpHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChlID = ga_pMainDlg->GetChlID();
    if ((NULL == lpHandle) || (dwChlID < 0))
    {
        NETDEMO_LOG_ERROR(NULL, "Device Handle : %p, Chl ID : %d.", lpHandle, dwChlID);
        return;
    } 

    BOOL bRet = NETDEV_PTZControl_Other(lpHandle, dwChlID, NETDEV_PTZ_ZOOMWIDE, m_dwPtzSpeed);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "PTZ Zoom In");
    }
    else
    {
        NETDEMO_LOG_SUCC(NULL, "PTZ Zoom In");
    }

    return;
}

void CPannelPTZ::OnBnPTZZoomOut()
{
    LPVOID lpHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChlID = ga_pMainDlg->GetChlID();
    if ((NULL == lpHandle) || (dwChlID < 0))
    {
        NETDEMO_LOG_ERROR(NULL, "Device Handle : %p, Chl ID : %d.", lpHandle, dwChlID);
        return;
    } 

    BOOL bRet = NETDEV_PTZControl_Other(lpHandle, dwChlID, NETDEV_PTZ_ZOOMTELE, m_dwPtzSpeed);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "PTZ Zoom Out");
    }
    else
    {
        NETDEMO_LOG_SUCC(NULL, "PTZ Zoom Out");
    }

    return;
}

void CPannelPTZ::OnBnPTZFocusNear()
{
    LPVOID lpHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChlID = ga_pMainDlg->GetChlID();
    if ((NULL == lpHandle) || (dwChlID < 0))
    {
        NETDEMO_LOG_ERROR(NULL, "Device Handle : %p, Chl ID : %d.", lpHandle, dwChlID);
        return;
    } 

    BOOL bRet = NETDEV_PTZControl_Other(lpHandle, dwChlID, NETDEV_PTZ_FOCUSNEAR, m_dwPtzSpeed);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "PTZ Focus Near");
    }
    else
    {
        NETDEMO_LOG_SUCC(NULL, "PTZ Focus Near");
    }

    return;
}

void CPannelPTZ::OnBnPTZFocusFar()
{
    LPVOID lpHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChlID = ga_pMainDlg->GetChlID();
    if ((NULL == lpHandle) || (dwChlID < 0))
    {
        NETDEMO_LOG_ERROR(NULL, "Device Handle : %p, Chl ID : %d.", lpHandle, dwChlID);
        return;
    }

    BOOL bRet = NETDEV_PTZControl_Other(lpHandle, dwChlID, NETDEV_PTZ_FOCUSFAR, m_dwPtzSpeed);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "PTZ Focus Far");
    }
    else
    {
        NETDEMO_LOG_SUCC(NULL, "PTZ Focus Far");
    }

    return;
}

void CPannelPTZ::InitToolTipCtrl()
{
    m_cToolTip.Create(this);
    m_cToolTip.SetDelayTime(20);
    m_cToolTip.SetTipTextColor( RGB(0,0,255) );
    m_cToolTip.SetTipBkColor( RGB(255,255,255));
    m_cToolTip.Activate(TRUE);

    return;
}

BOOL CPannelPTZ::PreTranslateMessage(MSG* pMsg)
{
    if(WM_MOUSEMOVE == pMsg->message)
    {
        m_cToolTip.RelayEvent(pMsg);
    }

    if(WM_LBUTTONDOWN == pMsg->message)
    {
        if(pMsg->hwnd == GetDlgItem(IDC_BUTTON_PTZ_UP)->m_hWnd)
        {
            OnBnPTZUp();
        }
        else if(pMsg->hwnd == GetDlgItem(IDC_BUTTON_LEFTUP)->m_hWnd)
        {
            OnBnPTZLeftup();
        }
        else if(pMsg->hwnd == GetDlgItem(IDC_BUTTON_LEFT)->m_hWnd)
        {
            OnBnPTZLeft();
        }
        else if(pMsg->hwnd == GetDlgItem(IDC_BUTTON_LEFTDOWN)->m_hWnd)
        {
            OnBnPTZLeftdown();
        }
        else if(pMsg->hwnd == GetDlgItem(IDC_BUTTON_DOWN)->m_hWnd)
        {
            OnBnPTZDown();
        }
        else if(pMsg->hwnd == GetDlgItem(IDC_BUTTON_RIGHTDOWN)->m_hWnd)
        {
            OnBnPTZRightdown();
        }
        else if(pMsg->hwnd == GetDlgItem(IDC_BUTTON_RIGHT)->m_hWnd)
        {
            OnBnPTZRight();
        }
        else if(pMsg->hwnd == GetDlgItem(IDC_BUTTON_RIGHTUP)->m_hWnd)
        {
            OnBnPTZRightup();
        }
        else if(pMsg->hwnd == GetDlgItem(IDC_BTN_FOCUS_NEAR)->m_hWnd)
        {
            OnBnPTZFocusNear();
        }
        else if(pMsg->hwnd == GetDlgItem(IDC_BTN_FOCUS_FAR)->m_hWnd)
        {
            OnBnPTZFocusFar();
        }
        else if (pMsg->hwnd == GetDlgItem(IDC_BTN_ZOOM_IN)->m_hWnd)
        {
            OnBnPTZZoomIn();
        }
        else if (pMsg->hwnd == GetDlgItem(IDC_BTN_ZOOM_OUT)->m_hWnd)
        {
            OnBnPTZZoomOut();
        }
    }

    if(WM_LBUTTONUP == pMsg->message)
    {
        if( (pMsg->hwnd == GetDlgItem(IDC_BUTTON_PTZ_UP)->m_hWnd) ||
            (pMsg->hwnd == GetDlgItem(IDC_BUTTON_LEFTUP)->m_hWnd) || 
            (pMsg->hwnd == GetDlgItem(IDC_BUTTON_LEFT)->m_hWnd) ||
            (pMsg->hwnd == GetDlgItem(IDC_BUTTON_LEFTDOWN)->m_hWnd) ||
            (pMsg->hwnd == GetDlgItem(IDC_BUTTON_DOWN)->m_hWnd) ||
            (pMsg->hwnd == GetDlgItem(IDC_BUTTON_RIGHTDOWN)->m_hWnd) ||
            (pMsg->hwnd == GetDlgItem(IDC_BUTTON_RIGHT)->m_hWnd) ||
            (pMsg->hwnd == GetDlgItem(IDC_BUTTON_RIGHTUP)->m_hWnd) )
        {
            OnBnPTZStop();
        }

        else if((pMsg->hwnd == GetDlgItem(IDC_BTN_FOCUS_NEAR)->m_hWnd) ||
                (pMsg->hwnd == GetDlgItem(IDC_BTN_FOCUS_FAR)->m_hWnd))
        {
            OnBnPTZStopFocus();
        }
        else if (pMsg->hwnd == GetDlgItem(IDC_BTN_ZOOM_IN)->m_hWnd)
        {
            OnBnPTZStopZoomIn();
        }
        else if (pMsg->hwnd == GetDlgItem(IDC_BTN_ZOOM_OUT)->m_hWnd)
        {
            OnBnPTZStopZoomOut();
        }
    }

    return CDialog::PreTranslateMessage(pMsg);
}

void CPannelPTZ::OnCbnSelchangeComboPreset()
{
    LPVOID lpHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChlID = ga_pMainDlg->GetChlID();
    if ((NULL == lpHandle) || (dwChlID < 0))
    {
        NETDEMO_LOG_ERROR(NULL, "Device Handle : %p, Chl ID : %d.", lpHandle, dwChlID);
        return;
    }

    NETDEV_PTZ_ALLPRESETS_S stPtzPresets = {0};
    INT32 dwBytesReturned = 0;
    BOOL bRet = NETDEV_GetDevConfig(lpHandle, dwChlID, NETDEV_GET_PTZPRESETS, (LPVOID)&stPtzPresets, sizeof(NETDEV_PTZ_ALLPRESETS_S), &dwBytesReturned);
    if(TRUE != bRet)
    {
        if (NETDEV_E_NO_RESULT == NETDEV_GetLastError())
        {
            NETDEMO_LOG_ERROR(NULL, "Presets list is emtpy.");
            GetDlgItem(IDC_EDIT_PTZ_PRESET_NAME)->SetWindowText("");
            return;
        }

        NETDEMO_LOG_ERROR(NULL, "Get presets failed.");
    }
    else
    {
        int nSplit = m_BoxPreset.GetCurSel();
        CString strPreSetID;
        m_BoxPreset.GetLBText(nSplit, strPreSetID);
        for(INT32 i = 0; i < stPtzPresets.dwSize; i++)
        {
            if(stPtzPresets.astPreset[i].dwPresetID == atoi(strPreSetID.GetBuffer(0)))
            {
                UTF8ToMB(stPtzPresets.astPreset[i].szPresetName, stPtzPresets.astPreset[i].szPresetName, sizeof(stPtzPresets.astPreset[i].szPresetName) - 1);
                GetDlgItem(IDC_EDIT_PTZ_PRESET_NAME)->SetWindowText(stPtzPresets.astPreset[i].szPresetName);
                return;
            }
        }
    }

    return;
}

void CPannelPTZ::OnBnPTZStopFocus()
{
    LPVOID lpHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChlID = ga_pMainDlg->GetChlID();
    if ((NULL == lpHandle) || (dwChlID < 0))
    {
        NETDEMO_LOG_ERROR(NULL, "DevHandle : %p,Chn id is %d.", lpHandle, dwChlID);
        return;
    }

    BOOL bRet = NETDEV_PTZControl_Other(lpHandle, dwChlID, NETDEV_PTZ_FOCUS_AND_IRIS_STOP, m_dwPtzSpeed);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "PTZ Focus Stop");
    }
    else
    {
        NETDEMO_LOG_SUCC(NULL, "PTZ Focus Stop");
    }

    return;
}


void CPannelPTZ::OnBnPTZStopZoomIn()
{
    LPVOID lpHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChlID = ga_pMainDlg->GetChlID();
    if ((NULL == lpHandle) || (dwChlID < 0))
    {
        NETDEMO_LOG_ERROR(NULL, "DevHandle : %p,Chn id is %d.", lpHandle, dwChlID);
        return;
    }

    BOOL bRet = NETDEV_PTZControl_Other(lpHandle, dwChlID, NETDEV_PTZ_ZOOMWIDE_STOP, m_dwPtzSpeed);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "PTZ Zoom In Stop");
    }
    else
    {
        NETDEMO_LOG_SUCC(NULL, "PTZ Zoom In Stop");
    }

    return;
}

void CPannelPTZ::OnBnPTZStopZoomOut()
{
    LPVOID lpHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChlID = ga_pMainDlg->GetChlID();
    if ((NULL == lpHandle) || (dwChlID < 0))
    {
        NETDEMO_LOG_ERROR(NULL, "DevHandle : %p,Chn id is %d.",lpHandle,dwChlID);
        return;
    }

    BOOL bRet = NETDEV_PTZControl_Other(lpHandle, dwChlID, NETDEV_PTZ_ZOOMTELE_STOP, m_dwPtzSpeed);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "PTZ Zoom Out Stop");
    }
    else
    {
        NETDEMO_LOG_SUCC(NULL, "PTZ Zoom Out Stop");
    }

    return;
}
