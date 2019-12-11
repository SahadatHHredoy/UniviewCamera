#include "stdafx.h"
#include "NetDemo.h"
#include "DlgDownloadInfo.h"

#define COL_INDEX_DOWNLOAD_FILE_NAME        0
#define COL_INDEX_DOWNLOAD_BEGIN_TIME       1
#define COL_INDEX_DOWNLOAD_END_TIME         2
#define COL_INDEX_DOWNLOAD_PROGRESS         3
#define COL_INDEX_DOWNLOAD_FILE_PATH        4

IMPLEMENT_DYNAMIC(CDlgDownloadInfo, CDialog)

CDlgDownloadInfo::CDlgDownloadInfo(CWnd* pParent /*=NULL*/)
: CDialog(CDlgDownloadInfo::IDD, pParent)
{
    //InitDownLoadList();
}

CDlgDownloadInfo::~CDlgDownloadInfo()
{
}

void CDlgDownloadInfo::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_PLAYBACK_DOWNLOAD_INFO, m_oDownloadInfoList);
}


BEGIN_MESSAGE_MAP(CDlgDownloadInfo, CDialog)
    ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_PLAYBACK_DOWNLOAD_INFO, &CDlgDownloadInfo::OnLvnItemchangedListPlaybackDownloadInfo)
END_MESSAGE_MAP()

BOOL CDlgDownloadInfo::OnInitDialog()
{
    CenterWindow();

    initDownLoadList();

    return TRUE;
}


void CDlgDownloadInfo::initDownLoadList()
{
    CDialog::OnInitDialog();

    CString str="File Name";
    m_oDownloadInfoList.InsertColumn(COL_INDEX_DOWNLOAD_FILE_NAME, str, LVCFMT_LEFT, 200, 50); 

    str = "Begin Time";
    m_oDownloadInfoList.InsertColumn(COL_INDEX_DOWNLOAD_BEGIN_TIME, str, LVCFMT_LEFT, 150);

    str = "End Time";
    m_oDownloadInfoList.InsertColumn(COL_INDEX_DOWNLOAD_END_TIME, str, LVCFMT_LEFT, 150);

    str = "Progress (%)";
    m_oDownloadInfoList.InsertColumn(COL_INDEX_DOWNLOAD_PROGRESS, str, LVCFMT_LEFT, 100);

    str = "File Path";
    m_oDownloadInfoList.InsertColumn(COL_INDEX_DOWNLOAD_FILE_PATH, str, LVCFMT_LEFT, 250);

    m_oDownloadInfoList.SetExtendedStyle(m_oDownloadInfoList.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES);
}

void CDlgDownloadInfo::OnLvnItemchangedListPlaybackDownloadInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

    *pResult = 0;
}

int CDlgDownloadInfo::updateDownLoadInfo(const NETDEMO_UPDATE_TIME_INFO& stFindData)
{
    int nRow = m_oDownloadInfoList.GetItemCount();
    m_oDownloadInfoList.InsertItem(nRow, "");

    m_oDownloadInfoList.SetItemText(nRow, COL_INDEX_DOWNLOAD_FILE_NAME, stFindData.strFileName);
    m_oDownloadInfoList.SetItemText(nRow, COL_INDEX_DOWNLOAD_BEGIN_TIME, GetTime(stFindData.tBeginTime));
    m_oDownloadInfoList.SetItemText(nRow, COL_INDEX_DOWNLOAD_END_TIME, GetTime(stFindData.tEndTime));
    m_oDownloadInfoList.SetItemText(nRow, COL_INDEX_DOWNLOAD_FILE_PATH, stFindData.strFilePath);


    m_oDownloadInfoList.SetItemText(nRow, COL_INDEX_DOWNLOAD_PROGRESS, "0");
    return nRow;
}

void CDlgDownloadInfo::clearDownLoadInfo()
{
    m_oDownloadInfoList.DeleteAllItems();

    return;
}

CString CDlgDownloadInfo::GetTime(const INT64 tTime)
{
    CString strTime;
    tm *pTime = localtime((time_t*)&tTime);
    strTime.Format("%d/%02d/%02d %02d:%02d:%02d",pTime->tm_year + 1900,pTime->tm_mon+1,pTime->tm_mday,pTime->tm_hour,pTime->tm_min,pTime->tm_sec);

    return strTime;
}

void CDlgDownloadInfo::stopDownLoad()
{
    int nRow = m_oDownloadInfoList.GetItemCount();
    for(int i = 0; i< nRow; i++)
    {
        m_oDownloadInfoList.SetItemText(i, COL_INDEX_DOWNLOAD_PROGRESS, "100");
    }

    return;
}

void CDlgDownloadInfo::updateDownLoadState(int nIndex, int nState)
{
    CString strDownState;
    strDownState.Format("%d", nState);
    m_oDownloadInfoList.SetItemText(nIndex, COL_INDEX_DOWNLOAD_PROGRESS, strDownState);

    return;
}