#pragma once
#include "afxcmn.h"

// CVcaPeopleCounting 

class CVcaPeopleCounting : public CDialog
{
    DECLARE_DYNAMIC(CVcaPeopleCounting)

public:
    CVcaPeopleCounting(CWnd* pParent = NULL);   
    virtual ~CVcaPeopleCounting();

    enum { IDD = IDD_VCA_PEOPLE_COUNTING };

protected:
    virtual void DoDataExchange(CDataExchange* pDX); 
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()

    void InitListCtrl();

public:
    CListCtrl m_oPeopleCountingList;

public:
    afx_msg void OnBnClickedRegisterPassengerFlowSetCallback();
    afx_msg void OnBnClickedUnRegisterPassengerFlowSetCallback();
    afx_msg void OnBnClickedClearPassengerFlowList();
};
