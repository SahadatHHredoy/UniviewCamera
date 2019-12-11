
#include "stdafx.h"
#include "NetDemo.h"
#include "CfgPrivacyMask.h"


// CCfgPrivacyMask 

IMPLEMENT_DYNAMIC(CCfgPrivacyMask, CDialog)

//#define COL_PRIVACY_MASK_ENABLE             0
#define COL_PRIVACY_MASK_INDEX              0
#define COL_PRIVACY_MASK_LEFTTOP_X          1
#define COL_PRIVACY_MASK_LEFTTOP_Y          2
#define COL_PRIVACY_MASK_RIGHTBOTTOM_X      3
#define COL_PRIVACY_MASK_RIGHTBOTTOM_Y      4

CCfgPrivacyMask::CCfgPrivacyMask(CWnd* pParent /*=NULL*/)
    : CDialog(CCfgPrivacyMask::IDD, pParent)
{
}

CCfgPrivacyMask::~CCfgPrivacyMask()
{
}

void CCfgPrivacyMask::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_PRIVACY_MASK, m_oPrivacyMaskList);
    DDX_Control(pDX, IDC_EDIT_SUB_ITEM, m_oEditSubItem);
    DDX_Text(pDX, IDC_EDIT_SUB_ITEM, m_strItemValue);
}


BEGIN_MESSAGE_MAP(CCfgPrivacyMask, CDialog)
    ON_BN_CLICKED(IDC_REFRESH, &CCfgPrivacyMask::OnBnClickedRefresh)
    ON_BN_CLICKED(IDC_SAVE_PRIVACY_MASK, &CCfgPrivacyMask::OnBnClickedSavePrivacyMask)
    ON_BN_CLICKED(IDC_DELETE_PRIVACY_MASK, &CCfgPrivacyMask::OnBnClickedDeletePrivacyMask)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST_PRIVACY_MASK, &CCfgPrivacyMask::OnNMDblclkListPrivacyMask)
    ON_EN_KILLFOCUS(IDC_EDIT_SUB_ITEM, &CCfgPrivacyMask::OnEnKillfocusEditSubItem)
    ON_BN_CLICKED(IDC_ADD_PRIVACY_MASK, &CCfgPrivacyMask::OnBnClickedAddPrivacyMask)
END_MESSAGE_MAP()

BOOL CCfgPrivacyMask::OnInitDialog()
{
    CDialog::OnInitDialog();
    CRect rc(0, 0, 0, 0);
    GetParent()->GetClientRect(&rc);
    ((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
    MoveWindow(&rc);

    initPrivacyMaskList();

    return TRUE;
}


void CCfgPrivacyMask::initPrivacyMaskList()
{
    CString str="No.";
    m_oPrivacyMaskList.InsertColumn(COL_PRIVACY_MASK_INDEX, str, LVCFMT_LEFT, 40);

 //   str="Enable";
 //   m_oPrivacyMaskList.InsertColumn(COL_PRIVACY_MASK_ENABLE, str, LVCFMT_LEFT, 50); 

    str="Left Top (X)";
    m_oPrivacyMaskList.InsertColumn(COL_PRIVACY_MASK_LEFTTOP_X, str, LVCFMT_LEFT, 120); 

    str = "Left Top (Y)";
    m_oPrivacyMaskList.InsertColumn(COL_PRIVACY_MASK_LEFTTOP_Y, str, LVCFMT_LEFT, 120);

    str = "Right Bottom (X)";
    m_oPrivacyMaskList.InsertColumn(COL_PRIVACY_MASK_RIGHTBOTTOM_X, str, LVCFMT_LEFT, 120);

    str = "Right Bottom (Y)";
    m_oPrivacyMaskList.InsertColumn(COL_PRIVACY_MASK_RIGHTBOTTOM_Y, str, LVCFMT_LEFT, 120);

    m_oPrivacyMaskList.SetExtendedStyle(m_oPrivacyMaskList.GetExtendedStyle() | /*LVS_EX_CHECKBOXES | */LVS_EX_GRIDLINES |LVS_EX_FULLROWSELECT | LVS_EX_SUBITEMIMAGES | LVS_REPORT);

    return;
}

/* Get Privacy Mask */
void CCfgPrivacyMask::getPrivacyMaskCfg()
{
    LPVOID lpDevHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChannelID = ga_pMainDlg->GetChlID();
    INT32 dwCurDevIndex = ga_pMainDlg ->GetCurDeviceIndex();
    INT32 dwCurChlIndex = ga_pMainDlg->GetCurChlIndex();

    INT32 dwBytesReturned = 0;

    NETDEV_PRIVACY_MASK_CFG_S stPrivacyMaskInfo = {0};
    BOOL bRet = NETDEV_GetDevConfig(lpDevHandle, dwChannelID, NETDEV_GET_PRIVACYMASKCFG, &stPrivacyMaskInfo, sizeof(stPrivacyMaskInfo), &dwBytesReturned);
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Get privacy mask cfg");
        return;
    }

    m_oPrivacyMaskList.DeleteAllItems();
    for (INT32 i = 0; i < stPrivacyMaskInfo.dwSize; i++)
    {
        m_oPrivacyMaskList.InsertItem(i, _T(""));
        //m_oPrivacyMaskList.SetCheck(i, stPrivacyMaskInfo.astArea[i].bIsEanbled);

        CString strText = _T("");
        strText.Format(_T("%d"), stPrivacyMaskInfo.astArea[i].dwIndex);
        m_oPrivacyMaskList.SetItemText(i, COL_PRIVACY_MASK_INDEX, strText);

        strText.Format(_T("%d"), stPrivacyMaskInfo.astArea[i].dwTopLeftX);
        m_oPrivacyMaskList.SetItemText(i, COL_PRIVACY_MASK_LEFTTOP_X, strText);

        strText.Format(_T("%d"), stPrivacyMaskInfo.astArea[i].dwTopLeftY);
        m_oPrivacyMaskList.SetItemText(i, COL_PRIVACY_MASK_LEFTTOP_Y, strText);

        strText.Format(_T("%d"), stPrivacyMaskInfo.astArea[i].dwBottomRightX);
        m_oPrivacyMaskList.SetItemText(i, COL_PRIVACY_MASK_RIGHTBOTTOM_X, strText);

        strText.Format(_T("%d"), stPrivacyMaskInfo.astArea[i].dwBottomRightY);
        m_oPrivacyMaskList.SetItemText(i, COL_PRIVACY_MASK_RIGHTBOTTOM_Y, strText);
    }

    if(NULL != gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstPrivacyMaskInfo)
    {
        memcpy( gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstPrivacyMaskInfo,&stPrivacyMaskInfo,sizeof(NETDEV_PRIVACY_MASK_CFG_S));
    }

    NETDEMO_LOG_SUCC(NULL, "Get privacy mask cfg");

    return;
}

/* Save Privacy Mask */
void CCfgPrivacyMask::OnBnClickedSavePrivacyMask()
{
    LPVOID lpDevHandle = ga_pMainDlg->GetDevHandle();
    INT32 dwChannelID = ga_pMainDlg->GetChlID();
    INT32 dwCurDevIndex = ga_pMainDlg ->GetCurDeviceIndex();
    INT32 dwCurChlIndex = ga_pMainDlg->GetCurChlIndex();

    INT32 dwBytesReturned = 0;

    NETDEV_PRIVACY_MASK_CFG_S stPrivacyMaskInfo = {0};

    getListDate(&stPrivacyMaskInfo);

    BOOL bRet = NETDEV_SetDevConfig(lpDevHandle, dwChannelID, NETDEV_SET_PRIVACYMASKCFG, &stPrivacyMaskInfo, sizeof(stPrivacyMaskInfo));
    if(TRUE != bRet)
    {
        NETDEMO_LOG_ERROR(NULL, "Save privacy mask cfg");
        return;
    }
    if(NULL != gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstPrivacyMaskInfo)
    {
        memcpy( gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstPrivacyMaskInfo,&stPrivacyMaskInfo,sizeof(NETDEV_PRIVACY_MASK_CFG_S));
    }
    
    NETDEMO_LOG_SUCC(NULL, "Save privacy mask cfg");

    return;
}

void CCfgPrivacyMask::ReadGlobeToPrivacyMask()
{
    INT32 dwCurDevIndex = ga_pMainDlg ->GetCurDeviceIndex();
    INT32 dwCurChlIndex = ga_pMainDlg->GetCurChlIndex();
    
    NETDEV_PRIVACY_MASK_CFG_S  stPrivacyMaskInfo = {0};
    if(NULL != gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstPrivacyMaskInfo)
    {
        memcpy(&stPrivacyMaskInfo, gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstPrivacyMaskInfo, sizeof(NETDEV_PRIVACY_MASK_CFG_S));
    }
    m_oPrivacyMaskList.DeleteAllItems();
    for (INT32 i = 0; i < stPrivacyMaskInfo.dwSize; i++)
    {
        m_oPrivacyMaskList.InsertItem(i, _T(""));
       // m_oPrivacyMaskList.SetCheck(i, stPrivacyMaskInfo.astArea[i].bIsEanbled);

        CString strText = _T("");
        strText.Format(_T("%d"), stPrivacyMaskInfo.astArea[i].dwIndex);
        m_oPrivacyMaskList.SetItemText(i, COL_PRIVACY_MASK_INDEX, strText);

        strText.Format(_T("%d"), stPrivacyMaskInfo.astArea[i].dwTopLeftX);
        m_oPrivacyMaskList.SetItemText(i, COL_PRIVACY_MASK_LEFTTOP_X, strText);

        strText.Format(_T("%d"), stPrivacyMaskInfo.astArea[i].dwTopLeftY);
        m_oPrivacyMaskList.SetItemText(i, COL_PRIVACY_MASK_LEFTTOP_Y, strText);

        strText.Format(_T("%d"), stPrivacyMaskInfo.astArea[i].dwBottomRightX);
        m_oPrivacyMaskList.SetItemText(i, COL_PRIVACY_MASK_RIGHTBOTTOM_X, strText);

        strText.Format(_T("%d"), stPrivacyMaskInfo.astArea[i].dwBottomRightY);
        m_oPrivacyMaskList.SetItemText(i, COL_PRIVACY_MASK_RIGHTBOTTOM_Y, strText);
    }
    UpdateData(FALSE);
}

/* Refresh */
void CCfgPrivacyMask::OnBnClickedRefresh()
{
    INT32 dwCurDevIndex = ga_pMainDlg ->GetCurDeviceIndex();
    INT32 dwCurChlIndex = ga_pMainDlg->GetCurChlIndex();
    if(dwCurChlIndex <0 || dwCurDevIndex<0)
    {
        return;
    }
    if (NULL != gastDeviceInfo && NULL != gastDeviceInfo[dwCurDevIndex].pstChlInfo)
    {
        if(NULL == gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstPrivacyMaskInfo)
        {
            gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstPrivacyMaskInfo = new NETDEV_PRIVACY_MASK_CFG_S;
        }
        memset(gastDeviceInfo[dwCurDevIndex].pstChlInfo[dwCurChlIndex].pstPrivacyMaskInfo ,0,sizeof(NETDEV_PRIVACY_MASK_CFG_S));
        /* Get Privacy Mask */
        getPrivacyMaskCfg();
    }

    UpdateData(FALSE);
    return;
}

/* Delete privacy mask */
void CCfgPrivacyMask::OnBnClickedDeletePrivacyMask()
{
    INT32 dwCurDevIndex = ga_pMainDlg ->GetCurDeviceIndex();
    INT32 dwCurChlIndex = ga_pMainDlg->GetCurChlIndex();
    POSITION pos = m_oPrivacyMaskList.GetFirstSelectedItemPosition();
    if (NULL == pos)
    {
        NETDEMO_LOG_ERROR(NULL, "Please select one item");
        return;
    }
    else
    {
        LPVOID lpDevHandle = ga_pMainDlg->GetDevHandle();
        INT32 dwChannelID = ga_pMainDlg->GetChlID();
        INT32 dwItem = 0;
        while(-1 != (dwItem = m_oPrivacyMaskList.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED)))
        {
            CString strIndex = m_oPrivacyMaskList.GetItemText(dwItem, COL_PRIVACY_MASK_INDEX);
            INT32 dwIndex = 0;
            sscanf(strIndex, "%d", &dwIndex);

            BOOL bRet = NETDEV_SetDevConfig(lpDevHandle, dwChannelID, NETDEV_DELETE_PRIVACYMASKCFG, &dwIndex, sizeof(INT32));
            if(TRUE != bRet)
            {
                NETDEMO_LOG_ERROR(NULL, "Delete privacy mask cfg");
                return;
            }

            m_oPrivacyMaskList.DeleteItem(dwItem);
            OnBnClickedSavePrivacyMask();

            NETDEMO_LOG_SUCC(NULL, "Delete privacy mask cfg");
        }
    }

    UpdateData(FALSE);

    return;
}


void CCfgPrivacyMask::OnNMDblclkListPrivacyMask(NMHDR *pNMHDR, LRESULT *pResult)
{
    NM_LISTVIEW *pNMListCtrl = (NM_LISTVIEW *)pNMHDR;

    m_dwRow = pNMListCtrl->iItem;
    m_dwCol = pNMListCtrl->iSubItem;
    if((m_dwRow != -1) && (m_dwCol <= COL_PRIVACY_MASK_RIGHTBOTTOM_Y) && (m_dwCol >= COL_PRIVACY_MASK_LEFTTOP_X))
    {
        CRect oRect, oEditDlgRect;
        m_oPrivacyMaskList.GetSubItemRect(m_dwRow, m_dwCol, LVIR_BOUNDS, oRect);
        m_oPrivacyMaskList.GetWindowRect(&oEditDlgRect);

        ScreenToClient(&oEditDlgRect);
        int height = oRect.Height();
        int width = oRect.Width();
        oRect.top += (oEditDlgRect.top + 1);
        oRect.left += (oEditDlgRect.left + 1);
        oRect.bottom = oRect.top + height + 2;
        oRect.right = oRect.left + width + 2;

        m_oEditSubItem.MoveWindow(&oRect);
        m_oEditSubItem.ShowWindow(SW_SHOW);
        m_oEditSubItem.SetFocus();
    }

    *pResult = 0;
}


void CCfgPrivacyMask::SetListItemText()
{
    return;
}

void CCfgPrivacyMask::OnEnKillfocusEditSubItem()
{
    UpdateData(TRUE);

    if ("" == m_strItemValue)
    {
        m_oEditSubItem.ShowWindow(SW_HIDE);
        return;
    }

    INT32 dwValue = 0;
    sscanf(m_strItemValue, "%d", &dwValue);

    if (dwValue < 0)
    {
        m_strItemValue = "0";
    }
    else if (dwValue > 10000)
    {
        m_strItemValue = "10000";
    }

    m_oPrivacyMaskList.SetItemText(m_dwRow, m_dwCol, m_strItemValue);
    m_oEditSubItem.SetWindowText(_T(""));
    m_oEditSubItem.ShowWindow(SW_HIDE);

    m_oPrivacyMaskList.Invalidate();

    return;
}

void CCfgPrivacyMask::getListDate(OUT LPNETDEV_PRIVACY_MASK_CFG_S pstPrivacyMaskInfo)
{
    if (NULL == pstPrivacyMaskInfo)
    {
        return;
    }

    for (INT32 i = 0; i < m_oPrivacyMaskList.GetItemCount(); i++)
    {
        CString str = m_oPrivacyMaskList.GetItemText(i, COL_PRIVACY_MASK_INDEX);
        sscanf(str, "%d", &pstPrivacyMaskInfo->astArea[i].dwIndex);

        str = m_oPrivacyMaskList.GetItemText(i, COL_PRIVACY_MASK_LEFTTOP_X);
        sscanf(str, "%d", &pstPrivacyMaskInfo->astArea[i].dwTopLeftX);

        str = m_oPrivacyMaskList.GetItemText(i, COL_PRIVACY_MASK_LEFTTOP_Y);
        sscanf(str, "%d", &pstPrivacyMaskInfo->astArea[i].dwTopLeftY);

        str = m_oPrivacyMaskList.GetItemText(i, COL_PRIVACY_MASK_RIGHTBOTTOM_X);
        sscanf(str, "%d", &pstPrivacyMaskInfo->astArea[i].dwBottomRightX);

        str = m_oPrivacyMaskList.GetItemText(i, COL_PRIVACY_MASK_RIGHTBOTTOM_Y);
        sscanf(str, "%d", &pstPrivacyMaskInfo->astArea[i].dwBottomRightY);

        pstPrivacyMaskInfo->astArea[i].bIsEanbled = TRUE;//m_oPrivacyMaskList.GetCheck(i);


    }

    pstPrivacyMaskInfo->dwSize = m_oPrivacyMaskList.GetItemCount();

    return;
}

void CCfgPrivacyMask::OnBnClickedAddPrivacyMask()
{
    if (m_oPrivacyMaskList.GetItemCount() >= NETDEV_MAX_PRIVACY_MASK_AREA_NUM)
    {
        NETDEMO_LOG_ERROR(NULL, "No more mask area is allowed");
        return;
    }

    INT32 dwIndex = 0;
    INT32 dwInsertIndex = 0;
    for (INT32 i = 0; i < NETDEV_MAX_PRIVACY_MASK_AREA_NUM; i++)
    {
        dwInsertIndex = i + 1;
        if (i < m_oPrivacyMaskList.GetItemCount())
        {
            CString str = m_oPrivacyMaskList.GetItemText(i, COL_PRIVACY_MASK_INDEX);
            sscanf(str, "%d", &dwIndex);

            if (dwInsertIndex >= dwIndex)
            {
                continue;
            }
        }

        m_oPrivacyMaskList.InsertItem(i, _T(""));
       // m_oPrivacyMaskList.SetCheck(i, TRUE);

        CString strText = _T("");
        strText.Format(_T("%d"), dwInsertIndex);
        m_oPrivacyMaskList.SetItemText(i, COL_PRIVACY_MASK_INDEX, strText);

        m_oPrivacyMaskList.SetItemText(i, COL_PRIVACY_MASK_LEFTTOP_X, "0");
        m_oPrivacyMaskList.SetItemText(i, COL_PRIVACY_MASK_LEFTTOP_Y, "0");
        m_oPrivacyMaskList.SetItemText(i, COL_PRIVACY_MASK_RIGHTBOTTOM_X, "1000");
        m_oPrivacyMaskList.SetItemText(i, COL_PRIVACY_MASK_RIGHTBOTTOM_Y, "1000");

        break;
    }

    m_strItemValue = "";
    UpdateData(FALSE);

    OnBnClickedSavePrivacyMask();

    return;
}
