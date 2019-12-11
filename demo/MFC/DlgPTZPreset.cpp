#include "stdafx.h"
#include "NetDemo.h"
#include "DlgPTZPreset.h"

#define NETDEV_MIN_PRESET_NUM               1       /* Minimum number of presets (1 ~ 255)*/

IMPLEMENT_DYNAMIC(CDlgPTZPreset, CDialog)

CDlgPTZPreset::CDlgPTZPreset(CWnd* pParent /*=NULL*/)
    : CDialog(CDlgPTZPreset::IDD, pParent)
    , m_dwPresetID(1)
    , m_strPresetName(_T(""))
{

}

CDlgPTZPreset::~CDlgPTZPreset()
{

}

void CDlgPTZPreset::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_PRESET_ID, m_dwPresetID);
    DDX_Text(pDX, IDC_EDIT_PRESET_NAME, m_strPresetName);
}

BOOL CDlgPTZPreset::OnInitDialog()
{
    CDialog::OnInitDialog();

    UpdateData(FALSE);
    return TRUE;
}

void CDlgPTZPreset::OnEnChangeEditPresetID()
{
    UpdateData(TRUE);

    if (m_dwPresetID < NETDEV_MIN_PRESET_NUM)
    {
        m_dwPresetID = NETDEV_MIN_PRESET_NUM;
    }
    else if (m_dwPresetID > NETDEV_MAX_PRESET_NUM)
    {
        m_dwPresetID = NETDEV_MAX_PRESET_NUM;
    }

    UpdateData(FALSE);

    return;
};


BEGIN_MESSAGE_MAP(CDlgPTZPreset, CDialog)
    ON_EN_CHANGE(IDC_EDIT_PRESET_ID, &CDlgPTZPreset::OnEnChangeEditPresetID)
END_MESSAGE_MAP()

