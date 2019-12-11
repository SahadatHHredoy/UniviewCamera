#pragma once
#include "afxwin.h"
#include "afxcmn.h"


class CPannelPlayControl : public CDialog
{
    DECLARE_DYNAMIC(CPannelPlayControl)

public:
    CPannelPlayControl(CWnd* pParent = NULL);  
    virtual ~CPannelPlayControl();

    enum { IDD = IDD_PANNEL_PLAY_CTRL };

protected:
    virtual void DoDataExchange(CDataExchange* pDX); 
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedRealplay();
    afx_msg void OnBnClickedRealplayStop();
    afx_msg void OnBnClickedSnapshot();
    afx_msg void OnBnClickedLocalRecoder();
    afx_msg void OnBnClickedCyclePlay();
    afx_msg void OnCbnSelchangeComboMultiScreen();
    CComboBox m_oCtrlSplitsel;
    CSliderCtrl m_oSliMicVolume;
    CSliderCtrl m_oSliSoundVolume;
    afx_msg void OnNMReleasedcaptureSliderMicVolume(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnNMReleasedcaptureSliderSoundVolume(NMHDR *pNMHDR, LRESULT *pResult);

private:

    HICON m_hPlayEnableIcon;
    HICON m_hPlayDisableIcon;

    HICON m_hStopEnableIcon;
    HICON m_hStopDisableIcon;

    HICON m_hCaptureIcon;

    HICON   m_hSoundStartIcon;
    HICON   m_hSoundStopIcon;

    HBITMAP m_hMicStartBmp;
    HBITMAP m_hMicStopBmp;

public:
    void SetMicState(BOOL bState);
    void SetSoundState(BOOL bState);
    void InitSplit(INT32 curSplit);
    void UpdateRecordTxt(CString strInfo);
    void EnableWindowMicBtn(BOOL bState);
    void EnableWindowSoundBtn(BOOL bState);
    void EnableWindowMicSli(BOOL bState);
    void EnableWindowSoundSli(BOOL bState);
    void SetSoundVolume(INT32 dwVolume);
    void SetMicVolume(INT32 dwVolume);
    void SetSplitNum(INT32 nSplit);
    int GetSplitNum();
    afx_msg void OnBnClickedButtonPlayMic();
    afx_msg void OnBnClickedButtonPlaySound();
    afx_msg void OnBnClickedButtonStreamCallback();
};
