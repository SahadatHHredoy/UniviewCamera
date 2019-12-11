#pragma once

class CDlgPTZPreset : public CDialog
{
    DECLARE_DYNAMIC(CDlgPTZPreset)

public:
    CDlgPTZPreset(CWnd* pParent = NULL);
    virtual ~CDlgPTZPreset();

    enum { IDD = IDD_DLG_PTZ_PRESET };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()

public:
    INT32 m_dwPresetID;
    CString m_strPresetName;

public:
    afx_msg void OnEnChangeEditPresetID();
};
