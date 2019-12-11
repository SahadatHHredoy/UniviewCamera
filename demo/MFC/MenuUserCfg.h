#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CMenuUserCfg 对话框

class CMenuUserCfg : public CDialog
{
    DECLARE_DYNAMIC(CMenuUserCfg)

public:
    CMenuUserCfg(CWnd* pParent = NULL);   // 标准构造函数
    virtual ~CMenuUserCfg();

// 对话框数据
    enum { IDD = IDD_MENU_USERCFG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()


    void updateListCtrl();
public:
    afx_msg void OnBnClickedButtonGetUserList();
    afx_msg void OnBnClickedButtonModifyUser();
    afx_msg void OnBnClickedButtonDeleteUser();
     void initUserList();
public:
    
    CListCtrl m_oUserList;
    INT32       m_lUserType;
    CComboBox m_oUserType;
    CString m_strUserName;
    CString m_strUserPassword;

    INT32       m_lUserTypeModify;
    CString m_strUserNameModify;
    CString m_strUserOldPassword;
    LPNETDEV_USER_DETAIL_LIST_S    pUserList;

    afx_msg void OnBnClickedButtonAddUser();
    afx_msg void OnCbnSelchangeComboUsertype();

private:
    void InitCombo();
    
public:
    CEdit m_oUserName;
    CEdit m_oUserPassword;
    afx_msg void OnCbnSelchangeComboUsertypelist();
//    afx_msg void OnCbnSelchangeComboUsertypelist2();
    afx_msg void OnCbnSelchangeComboUsertypelist2();
    CComboBox m_oUserType2;
    CString m_strUserNewPasswaord;
};
