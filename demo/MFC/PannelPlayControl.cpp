
#include "stdafx.h"
#include "NetDemo.h"
#include "PannelPlayControl.h"



IMPLEMENT_DYNAMIC(CPannelPlayControl, CDialog)

CPannelPlayControl::CPannelPlayControl(CWnd* pParent /*=NULL*/)
    : CDialog(CPannelPlayControl::IDD, pParent)
{
    CBitmap oBitmap;
    oBitmap.LoadBitmap(IDB_BMP_MIC_START);
    m_hMicStartBmp = (HBITMAP)oBitmap.Detach();
    oBitmap.LoadBitmap(IDB_BMP_MIC_STOP);
    m_hMicStopBmp = (HBITMAP)oBitmap.Detach();

    m_hSoundStartIcon = AfxGetApp()->LoadIcon(IDI_SOUND_ENABLE);
    m_hSoundStopIcon = AfxGetApp()->LoadIcon(IDI_SOUND_DISABLE);

    m_hPlayEnableIcon = AfxGetApp()->LoadIcon(IDI_PLAY_ENABLE);
    m_hPlayDisableIcon = AfxGetApp()->LoadIcon(IDI_PLAY_DISABLE);

    m_hStopEnableIcon = AfxGetApp()->LoadIcon(IDI_STOP_ENABLE);
    m_hStopDisableIcon = AfxGetApp()->LoadIcon(IDI_STOP_DISABLE);

    m_hCaptureIcon = AfxGetApp()->LoadIcon(IDI_SNAPSHOT);
}

CPannelPlayControl::~CPannelPlayControl()
{
}

void CPannelPlayControl::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_MULTI_SCREEN, m_oCtrlSplitsel);
    DDX_Control(pDX, IDC_SLD_MIC_VOLUME, m_oSliMicVolume);
    DDX_Control(pDX, IDC_SLD_SOUND_VOLUME, m_oSliSoundVolume);
}


BEGIN_MESSAGE_MAP(CPannelPlayControl, CDialog)
    ON_BN_CLICKED(IDC_REALPLAY, &CPannelPlayControl::OnBnClickedRealplay)
    ON_BN_CLICKED(IDC_STOP_REALPLAY, &CPannelPlayControl::OnBnClickedRealplayStop)
    ON_BN_CLICKED(IDC_SNAPSHOT, &CPannelPlayControl::OnBnClickedSnapshot)
    ON_BN_CLICKED(IDC_LOCAL_RECODE, &CPannelPlayControl::OnBnClickedLocalRecoder)
    ON_BN_CLICKED(IDC_CYCLEPLAY, &CPannelPlayControl::OnBnClickedCyclePlay)
    ON_CBN_SELCHANGE(IDC_COMBO_MULTI_SCREEN, &CPannelPlayControl::OnCbnSelchangeComboMultiScreen)
    ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLD_MIC_VOLUME, &CPannelPlayControl::OnNMReleasedcaptureSliderMicVolume)
    ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLD_SOUND_VOLUME, &CPannelPlayControl::OnNMReleasedcaptureSliderSoundVolume)
    ON_BN_CLICKED(IDC_PLAY_MIC, &CPannelPlayControl::OnBnClickedButtonPlayMic)
    ON_BN_CLICKED(IDC_PLAY_SOUND, &CPannelPlayControl::OnBnClickedButtonPlaySound)
    ON_BN_CLICKED(IDC_BUTTON_STREAM_CALLBACK, &CPannelPlayControl::OnBnClickedButtonStreamCallback)
END_MESSAGE_MAP()



void CPannelPlayControl::OnBnClickedRealplay()
{
    ga_pMainDlg->RealPlaySelectedDevice();

    return;
}

void CPannelPlayControl::OnBnClickedRealplayStop()
{
    ga_pMainDlg->StopPlaySelectedDevice();

    return;
}

void CPannelPlayControl::OnBnClickedSnapshot()
{
    ga_pMainDlg->SnapShotSelectedDevice();

    return;
}

void CPannelPlayControl::OnBnClickedLocalRecoder()
{
    ga_pMainDlg->StartLocalRecod();
    
    return;
}

void CPannelPlayControl::OnBnClickedCyclePlay()
{
    ga_pMainDlg->CycleMonitor();

    return;
}

void CPannelPlayControl::OnCbnSelchangeComboMultiScreen()
{
    INT32 dwSplit = m_oCtrlSplitsel.GetCurSel();
    ga_pMainDlg->SetMultiScreen(dwSplit);

    return;
}

void CPannelPlayControl::OnNMReleasedcaptureSliderMicVolume(NMHDR *pNMHDR, LRESULT *pResult)
{
    INT32 dwMicValue = m_oSliMicVolume.GetPos();
    ga_pMainDlg->SetSliderMicVolume(dwMicValue);

    return;
}

void CPannelPlayControl::OnNMReleasedcaptureSliderSoundVolume(NMHDR *pNMHDR, LRESULT *pResult)
{
    INT32 dwSoundValue = m_oSliSoundVolume.GetPos();
    ga_pMainDlg->SetSliderSoundVolume(dwSoundValue);

    return;
}

void CPannelPlayControl::SetMicState(BOOL bState)
{
    CButton *pButton = (CButton *)GetDlgItem(IDC_PLAY_MIC);
    pButton->SetBitmap(m_hMicStopBmp);
    if (TRUE == bState)
    {
        pButton->SetBitmap(m_hMicStartBmp);
    }
    else
    {
        pButton->SetBitmap(m_hMicStopBmp);
    }

    return;
}

void CPannelPlayControl::SetSoundState(BOOL bState)
{
    CButton *pButton = (CButton *)GetDlgItem(IDC_PLAY_SOUND);
    if (TRUE == bState)
    {
        pButton->SetIcon(m_hSoundStartIcon);
    }
    else
    {
        pButton->SetIcon(m_hSoundStopIcon);
    }

    return;
}


void CPannelPlayControl::SetSoundVolume(INT32 dwVolume)
{
    m_oSliSoundVolume.SetPos(dwVolume);

    return;
}

void CPannelPlayControl::SetMicVolume(INT32 dwVolume)
{
    m_oSliMicVolume.SetPos(dwVolume);

    return;
}

BOOL CPannelPlayControl::OnInitDialog()
{
    CDialog::OnInitDialog();

    CButton *pButton = (CButton *)GetDlgItem(IDC_PLAY_SOUND);
    pButton->SetIcon(m_hSoundStopIcon);
    pButton->EnableWindow(FALSE);

    pButton = (CButton *)GetDlgItem(IDC_PLAY_MIC);
    pButton->SetBitmap(m_hMicStopBmp);
    pButton->EnableWindow(FALSE);

    pButton = (CButton *)GetDlgItem(IDC_REALPLAY);
    pButton->SetIcon(m_hPlayEnableIcon);
    pButton->EnableWindow(TRUE);

    pButton = (CButton *)GetDlgItem(IDC_STOP_REALPLAY);
    pButton->SetIcon(m_hStopEnableIcon);
    pButton->EnableWindow(TRUE);

    pButton = (CButton *)GetDlgItem(IDC_SNAPSHOT);
    pButton->SetIcon(m_hCaptureIcon);
    pButton->EnableWindow(TRUE);

    m_oSliMicVolume.SetRange(NETDEV_AUDIO_SOUND_MIN_VALUE,NETDEV_AUDIO_SOUND_MAX_VALUE,TRUE);
    m_oSliSoundVolume.SetRange(NETDEV_MIC_SOUND_MIN_VALUE,NETDEV_MIC_SOUND_MAX_VALUE,TRUE);
    m_oSliMicVolume.EnableWindow(FALSE);
    m_oSliSoundVolume.EnableWindow(FALSE);
    InitSplit(NETDEMO_SPLIT16);

    return TRUE;
}

void CPannelPlayControl::InitSplit(INT32 curSplit)
{
    char *nStrSplit[NETDEMO_SPLIT_TOTAL] = {NETDEMO_DLG_SPLITTYPE_1,
        NETDEMO_DLG_SPLITTYPE_4,
        NETDEMO_DLG_SPLITTYPE_9,
        NETDEMO_DLG_SPLITTYPE_16};

    for(INT32 i = 0; i <= curSplit ; i++)
    {
        m_oCtrlSplitsel.InsertString(i, nStrSplit[i]);
    }

    ga_pMainDlg->SetSplit(NETDEMO_SPLIT16);
    m_oCtrlSplitsel.SetCurSel(NETDEMO_SPLIT16);

    return;
}


void CPannelPlayControl::UpdateRecordTxt(CString strInfo)
{
    GetDlgItem(IDC_LOCAL_RECODE)->SetWindowText(strInfo);

    return;
}

void CPannelPlayControl::EnableWindowMicBtn(BOOL bState)
{
    CButton *pButton = (CButton *)GetDlgItem(IDC_PLAY_MIC);
    pButton->EnableWindow(bState);

    return;
}

void CPannelPlayControl::EnableWindowSoundBtn(BOOL bState)
{
    CButton *pButton = (CButton *)GetDlgItem(IDC_PLAY_SOUND);
    pButton->EnableWindow(bState);

    return;
}

void CPannelPlayControl::OnBnClickedButtonPlayMic()
{
    ga_pMainDlg->ControlMicVolume();

    return;
}

void CPannelPlayControl::OnBnClickedButtonPlaySound()
{
    ga_pMainDlg->ControlSoundVolume();

    return;
}

void CPannelPlayControl::EnableWindowMicSli(BOOL bState)
{
    m_oSliMicVolume.EnableWindow(bState);

    return;
}

void CPannelPlayControl::EnableWindowSoundSli(BOOL bState)
{
    m_oSliSoundVolume.EnableWindow(bState);

    return;
}

void CPannelPlayControl::SetSplitNum(INT32 nSplit)
{
    m_oCtrlSplitsel.SetCurSel(nSplit);

    return;
}

int CPannelPlayControl::GetSplitNum()
{
    return m_oCtrlSplitsel.GetCurSel();
}

void CPannelPlayControl::OnBnClickedButtonStreamCallback()
{
    LPVOID lpHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChlID = ga_pMainDlg->GetChlID();
    if ((NULL == lpHandle) || (dwChlID < 0))
    {
        NETDEMO_LOG_ERROR(NULL, "Device Handle : %p, Chl ID : %d.", lpHandle, dwChlID);

        return;
    }

    CDlgStreamCallback oDlgStreamCalback;
    if (-1 != oDlgStreamCalback.DoModal())
    {
        oDlgStreamCalback.CloseAllCallback();
    }

    return;
}
