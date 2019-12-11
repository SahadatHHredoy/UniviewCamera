#pragma once
#include "afxcmn.h"


// CDlgDownloadInfo 
class CDlgDownloadInfo : public CDialog
{
    DECLARE_DYNAMIC(CDlgDownloadInfo)

public:
    CDlgDownloadInfo(CWnd* pParent = NULL);
    virtual ~CDlgDownloadInfo();

    enum { IDD = IDD_DLG_DOWNLOAD_INFO };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()

public:
    int updateDownLoadInfo(const NETDEMO_UPDATE_TIME_INFO& stFindData);
    void updateDownLoadState(int nIndex, int nState);
    void clearDownLoadInfo();
    void stopDownLoad();
    CString GetTime(const INT64 tTime);
    void initDownLoadList();

private:
    CListCtrl m_oDownloadInfoList;

public:
    afx_msg void OnLvnItemchangedListPlaybackDownloadInfo(NMHDR *pNMHDR, LRESULT *pResult);
};
