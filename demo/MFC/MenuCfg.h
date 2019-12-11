#pragma once
#include "afxcmn.h"

#include "CfgDeviceBasic.h"
#include "CfgNetWork.h"
#include "CfgStreamInfo.h"
#include "CfgAlarmIO.h"
#include "CfgImage.h"
#include "CfgOSD.h"
#include "CfgPrivacyMask.h"
#include "CfgMotion.h"
#include "CfgTamper.h"
#include "GeneralDef.h"

class CMenuCfg : public CDialog
{
    DECLARE_DYNAMIC(CMenuCfg)

public:
    CMenuCfg(CWnd* pParent = NULL);
    virtual ~CMenuCfg();

    enum { IDD = IDD_MENU_CFG };
    static   INT32 sta_lastTimeID;
protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()
public:
    void refreshCfgTab();

private:
    CCfgDeviceBasic     m_oDlgDeviceBasic;
    CCfgNetWork         m_oDlgNetwork;
    CCfgStreamInfo      m_oDlgVideoStream;
    CCfgImage           m_oDlgImage;
    CCfgOSD             m_oDlgOSD;
    CCfgAlarmIO         m_oDlgAlarmIO;
    CCfgPrivacyMask     m_oDlgPrivacyMask;
    CCfgMotion          m_oDlgMotion;
    CCfgTamper          m_oDlgTamper;

    INT32               m_dwCfgType;
    CTabCtrl            m_oTabConfigure;

public:
    afx_msg void OnTcnSelchangeTabPrimarymenu(NMHDR *pNMHDR, LRESULT *pResult);
};
