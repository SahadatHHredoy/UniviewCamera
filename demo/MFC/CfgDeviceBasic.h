#pragma once
#include "afxcmn.h"


// CCfgDeviceBasic 

class CCfgDeviceBasic : public CDialog
{
    DECLARE_DYNAMIC(CCfgDeviceBasic)

public:
    CCfgDeviceBasic(CWnd* pParent = NULL);
    virtual ~CCfgDeviceBasic();

    enum { IDD = IDD_CFG_DEVICE_BASIC };
    void ReadGlobeToBasic();

protected:
    virtual void DoDataExchange(CDataExchange* pDX); 
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()

    void initDiskInfoList();

    void initTimeZone();

    void getDevName();

    void getSystemTime();

    void getDiskInfo();

private:
    CString m_strDeviceName;
    CListCtrl m_oDiskInfoList;
    CDateTimeCtrl m_oDevSysDate;
    CDateTimeCtrl m_oDevSysTime;
    CComboBox m_oCBoxTimeZone;

public:
    afx_msg void OnLvnItemchangedListDisksInfo(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnBnClickedSaveDevName();
    afx_msg void OnBnClickedRefresh();
    afx_msg void OnBnClickedSaveSystemTime();
};
