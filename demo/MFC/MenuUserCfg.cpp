// MenuUserCfg.cpp : 实现文件
//

#include "stdafx.h"
#include "NetDemo.h"
#include "MenuUserCfg.h"


// CMenuUserCfg 对话框

IMPLEMENT_DYNAMIC(CMenuUserCfg, CDialog)

#define COL_USER_INDEX              1
#define COL_USER_USERNAME          2
#define COL_USER_USERTYPE          3

CMenuUserCfg::CMenuUserCfg(CWnd* pParent /*=NULL*/)
    : CDialog(CMenuUserCfg::IDD, pParent)
    , m_strUserNewPasswaord(_T(""))
{
    pUserList = new NETDEV_USER_DETAIL_LIST_S();
    m_lUserType = 1;
    m_lUserTypeModify = 1;
}

CMenuUserCfg::~CMenuUserCfg()
{
    if(NULL != pUserList)
    {
        delete pUserList;
    }
}

void CMenuUserCfg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_USER_LIST, m_oUserList);
    DDX_Control(pDX, IDC_COMBO_USERTYPELIST, m_oUserType);
    // DDX_Control(pDX, IDC_EDIT_USERNAME, m_oUserName);
    // DDX_Control(pDX, IDC_EDIT_USERPASSWORD, m_oUserPassword);

    DDX_Text(pDX, IDC_EDIT_USERNAME, m_strUserName);
    DDX_Text(pDX, IDC_EDIT_USERPASSWORD, m_strUserPassword);


    DDX_Control(pDX, IDC_COMBO_USERTYPELIST2, m_oUserType2);
    DDX_Text(pDX, IDC_EDIT_USERNAME2, m_strUserNameModify);
    DDX_Text(pDX, IDC_EDIT_USERPASSWORD2, m_strUserOldPassword);
    DDX_Text(pDX, IDC_EDIT_USERPASSWORD3, m_strUserNewPasswaord);
}


BEGIN_MESSAGE_MAP(CMenuUserCfg, CDialog)
    ON_BN_CLICKED(IDC_BUTTON_GET_USER_LIST, &CMenuUserCfg::OnBnClickedButtonGetUserList)
    ON_BN_CLICKED(IDC_BUTTON_MODIFY_USER, &CMenuUserCfg::OnBnClickedButtonModifyUser)
    ON_BN_CLICKED(IDC_BUTTON_DELETE_USER, &CMenuUserCfg::OnBnClickedButtonDeleteUser)
    ON_WM_INITMENU()
    ON_BN_CLICKED(IDC_BUTTON_ADD_USER, &CMenuUserCfg::OnBnClickedButtonAddUser)
    ON_CBN_SELCHANGE(IDC_COMBO_USERTYPELIST, &CMenuUserCfg::OnCbnSelchangeComboUsertypelist)
   ON_CBN_SELCHANGE(IDC_COMBO_USERTYPELIST2, &CMenuUserCfg::OnCbnSelchangeComboUsertypelist2)
END_MESSAGE_MAP()

// CMenuUserCfg 消息处理程序


void CMenuUserCfg::initUserList()
{
    m_oUserList.InsertColumn(0, "", LVCFMT_CENTER, 0, -1);

    CString str ="No";
    m_oUserList.InsertColumn(1,str,LVCFMT_CENTER,120);

    str = "User Name";
    m_oUserList.InsertColumn(2, str, LVCFMT_CENTER, 210);

    str = "UserType";
    m_oUserList.InsertColumn(3, str, LVCFMT_CENTER, 190);

    m_oUserList.SetExtendedStyle(m_oUserList.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES);

    return;
}
BOOL CMenuUserCfg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO: 在此处添加消息处理程序代码
    initUserList();
    InitCombo();

    return TRUE;
}

void CMenuUserCfg::InitCombo()
{
    m_oUserType.AddString("Operator");
    m_oUserType.AddString("User");

    m_oUserType.SetCurSel(0);

    m_oUserType2.AddString("Operator");
    m_oUserType2.AddString("User");

    m_oUserType2.SetCurSel(0);

    return;
}

void CMenuUserCfg::OnCbnSelchangeComboUsertypelist()
{
    // TODO: 在此添加控件通知处理程序代码
    INT32 index = m_oUserType.GetCurSel();
    switch(index)
    {
    case 0:
        {
            m_lUserType = NETDEV_USER_LEVEL_OPERATOR;
        }
        break;
    case 1:
        {
            m_lUserType = NETDEV_USER_LEVEL_USER;
        }
        break;
    default:
        break;
    }

    return;
}

void CMenuUserCfg::OnCbnSelchangeComboUsertypelist2()
{
    // TODO: 在此添加控件通知处理程序代码
    INT32 index = m_oUserType2.GetCurSel();
    switch(index)
    {
    case 0:
        {
            m_lUserTypeModify = NETDEV_USER_LEVEL_OPERATOR;
        }
        break;
    case 1:
        {
            m_lUserTypeModify = NETDEV_USER_LEVEL_USER;
        }
        break;
    default:
        break;
    }

    return;
}

void CMenuUserCfg::updateListCtrl()
{
    LPVOID lpDevHandle = ga_pMainDlg->GetDevHandle();
    BOOL bRet = NETDEV_GetUserDetailList(lpDevHandle, pUserList);
    if (TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Getuserlist");
        return;
    }
    m_oUserList.DeleteAllItems();

    for (INT32 i = 0; i < pUserList->udwNum; i++)
    {
        INT32 dwRow = m_oUserList.InsertItem(i, "");

        CHAR szBuf[64];
        _snprintf(szBuf, sizeof(szBuf), "%d", i+1);
        m_oUserList.SetItemText(i, COL_USER_INDEX, szBuf);

        m_oUserList.SetItemText(i, COL_USER_USERNAME, pUserList->astUserInfo[i].szUserName);

        CString strUserType;;
        switch(pUserList->astUserInfo[i].udwLevel)
        {
        case NETDEV_USER_LEVEL_ADMINISTRATOR:
            strUserType = "Administrator";
            break;

        case NETDEV_USER_LEVEL_OPERATOR:
            strUserType = "Operater";
            break;

        case NETDEV_USER_LEVEL_USER:
            strUserType = "User";
            break;

        case NETDEV_USER_LEVEL_Default:
            strUserType = "Default";
            break;
        default:
            strUserType = "";
        }
        m_oUserList.SetItemText(i, COL_USER_USERTYPE, strUserType);
        UpdateData(FALSE);
    }

    return;
}

void CMenuUserCfg::OnBnClickedButtonAddUser()
{
    LPVOID lpDevHandle = ga_pMainDlg->GetDevHandle();
    // TODO: 在此添加控件通知处理程序代码
    if (m_oUserList.GetItemCount() >= NETDEV_LEN_64)
    {
        NETDEMO_LOG_ERROR(NULL, "No more mask area is allowed");
        return;
    }

    INT32 dwIndex = 0;
    INT32 dwInsertIndex = 0;
    for (INT32 i = 0; i < NETDEV_LEN_64; i++)
    {
        dwInsertIndex = i + 1;
        if (i < m_oUserList.GetItemCount())
        {
            CString str = m_oUserList.GetItemText(i, COL_USER_INDEX);
            sscanf(str, "%d", &dwIndex);

            if (dwInsertIndex >= dwIndex)
            {
                continue;
            }
        }
        break;
    }

    UpdateData(TRUE);

    NETDEV_USER_DETAIL_INFO_S stUserInfo = {0};
    strncpy(stUserInfo.szUserName, m_strUserName.GetBuffer(0), sizeof(stUserInfo.szUserName) - 1);
    strncpy(stUserInfo.szPassword, m_strUserPassword.GetBuffer(0), sizeof(stUserInfo.szPassword) - 1);

    stUserInfo.udwLevel = m_lUserType;

    if(0 != dwInsertIndex)
    {
        BOOL bRet = NETDEV_CreateUser(lpDevHandle, &stUserInfo );
        if (TRUE != bRet)
        {
            NETDEMO_LOG_ERROR(NULL, "Getuserlist");
            return;
        }
    }

    updateListCtrl();
}

void CMenuUserCfg::OnBnClickedButtonGetUserList()
{
    // TODO: 在此添加控件通知处理程序代码
    updateListCtrl();
}

/* 默认是管理员用户登录的设备，如果以其他用户登录可能会失败 */
void CMenuUserCfg::OnBnClickedButtonModifyUser()
{
    // TODO: 在此添加控件通知处理程序代码
    LPVOID lpDevHandle = ga_pMainDlg->GetDevHandle();

    UpdateData(TRUE);

    NETDEV_USER_MODIFY_DETAIL_INFO_S stUserInfo = {0};
    strncpy(stUserInfo.stUserInfo.szUserName, m_strUserNameModify.GetBuffer(0), sizeof(stUserInfo.stUserInfo.szUserName) - 1);
    strncpy(stUserInfo.szCurrentPassword, m_strUserOldPassword.GetBuffer(0), sizeof(stUserInfo.szCurrentPassword) - 1);
    strncpy(stUserInfo.szNewPassword, m_strUserNewPasswaord.GetBuffer(0), sizeof(stUserInfo.szNewPassword) - 1);

    stUserInfo.stUserInfo.udwLevel = m_lUserTypeModify;

    /* 管理员修改自己的信息 */
    if(0 == strncpy(stUserInfo.stUserInfo.szUserName, "Admin", sizeof("Admin") && strlen(stUserInfo.stUserInfo.szUserName) == strlen("Admin")) )
    {
          stUserInfo.bIsModifyOther = FALSE;
    }
    else
    {
          stUserInfo.bIsModifyOther = TRUE;
    }

    /* 如果旧密码和新密码一样 */
    if(0 == strcpy(stUserInfo.szCurrentPassword, stUserInfo.szNewPassword))
    {
       stUserInfo.bIsModifyPassword = FALSE;
    }
    else
    {
       stUserInfo.bIsModifyPassword = TRUE;
    }

    BOOL bRet = NETDEV_ModifyUser(lpDevHandle, &stUserInfo );
    if (TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "ModifyUser");
        return;
    }

    updateListCtrl();
}

void CMenuUserCfg::OnBnClickedButtonDeleteUser()
{
    // TODO: 在此添加控件通知处理程序代码
    INT32 dwCurDevIndex = ga_pMainDlg ->GetCurDeviceIndex();
    POSITION pos = m_oUserList.GetFirstSelectedItemPosition();
    if (NULL == pos)
    {
        NETDEMO_LOG_ERROR(NULL, "Please select one item");
        return;
    }
    else
    {
        LPVOID lpDevHandle = ga_pMainDlg->GetDevHandle();
        INT32 dwItem = 0;
        while(-1 != (dwItem = m_oUserList.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED)))
        {
            std::string strIndex = m_oUserList.GetItemText(dwItem, COL_USER_USERNAME);
            //INT32 dwIndex = 0;
            //sscanf(strIndex, "%d", &dwIndex);
            BOOL bRet = NETDEV_DeleteUser(lpDevHandle, (CHAR *)strIndex.c_str() );
            if(TRUE != bRet)
            {
                NETDEMO_LOG_ERROR(NULL, "Delete privacy mask cfg");
                return;
            }

            m_oUserList.DeleteItem(dwItem);
            UpdateData(TRUE);

            updateListCtrl();
            UpdateData(FALSE);

            NETDEMO_LOG_SUCC(NULL, "Delete privacy mask cfg");
        }
    }
}


