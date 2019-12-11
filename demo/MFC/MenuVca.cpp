#include "stdafx.h"
#include "NetDemo.h"
#include "MenuVca.h"

// CMenuVca 

IMPLEMENT_DYNAMIC(CMenuVca, CDialog)

CMenuVca::CMenuVca(CWnd* pParent /*=NULL*/)
    : CDialog(CMenuVca::IDD, pParent)
{

}

CMenuVca::~CMenuVca()
{
}

void CMenuVca::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TAB_VCA, m_oTabVCA);
}


BEGIN_MESSAGE_MAP(CMenuVca, CDialog)
    ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_VCA, &CMenuVca::OnTcnSelchangeTabVca)
END_MESSAGE_MAP()

/* Tab index */
typedef enum tabIndexConfig
{
    TAB_INDEX_PEOPLE_COUNTING  = 0,
    TAB_INDEX_PEOPLE_COUNTING_STATISTICS
};

BOOL CMenuVca::OnInitDialog()
{
    CDialog::OnInitDialog();

    CString str = "People Counting for Report";
    m_oTabVCA.InsertItem(TAB_INDEX_PEOPLE_COUNTING, str);
    m_oDlgPeopleCounting.Create(IDD_VCA_PEOPLE_COUNTING,&m_oTabVCA);
    m_oDlgPeopleCounting.ShowWindow(SW_SHOW);

    str = "People Counting for Statistics";
    m_oTabVCA.InsertItem(TAB_INDEX_PEOPLE_COUNTING_STATISTICS, str);
    m_oDlgPeopleCountingStatistics.Create(IDD_VCA_PEOPLE_COUNTING_STATISTICS, &m_oTabVCA);
    m_oDlgPeopleCountingStatistics.ShowWindow(SW_HIDE);

    UpdateData(FALSE);

    return TRUE;
}

void CMenuVca::ConfigWithUpdate()
{
    switch(m_dwVCAType)
    {
    case TAB_INDEX_PEOPLE_COUNTING:
        m_oDlgPeopleCounting.ShowWindow(SW_SHOW);
        m_oDlgPeopleCountingStatistics.ShowWindow(SW_HIDE);

        break;
    case TAB_INDEX_PEOPLE_COUNTING_STATISTICS:
        m_oDlgPeopleCounting.ShowWindow(SW_HIDE);
        m_oDlgPeopleCountingStatistics.ShowWindow(SW_SHOW);
        break;

    default:
        break;
    }
}

void CMenuVca::OnTcnSelchangeTabVca(NMHDR *pNMHDR, LRESULT *pResult)
{
    UpdateData(TRUE);
    m_dwVCAType =  m_oTabVCA.GetCurSel();
    ConfigWithUpdate();
    *pResult = 0;
}
