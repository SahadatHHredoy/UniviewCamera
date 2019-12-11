#pragma once
#include "afxcmn.h"
#include "VcaPeopleCounting.h"
#include "VcaPeopleCountingStatistics.h"

// CMenuVca 

class CMenuVca : public CDialog
{
    DECLARE_DYNAMIC(CMenuVca)

public:
    CMenuVca(CWnd* pParent = NULL);
    virtual ~CMenuVca();

    enum { IDD = IDD_MENU_VCA };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()

    void ConfigWithUpdate();
public:
    CTabCtrl m_oTabVCA;
    CVcaPeopleCounting m_oDlgPeopleCounting;
    CVcaPeopleCountingStatistics m_oDlgPeopleCountingStatistics;

    INT32               m_dwVCAType;

    afx_msg void OnTcnSelchangeTabVca(NMHDR *pNMHDR, LRESULT *pResult);
};
