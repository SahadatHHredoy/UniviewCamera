#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CDlgPTZExtend 

class CDlgPTZExtend : public CDialog
{
    DECLARE_DYNAMIC(CDlgPTZExtend)

public:
    CDlgPTZExtend(CWnd* pParent = NULL);
    virtual ~CDlgPTZExtend();

    enum { IDD = IDD_DLG_PTZ_EXTEND };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()

    void InitPresetPatrolsCombo();
    void SetPtzSpeed(INT32 Speed);
    void InitCruiseList();
    void GetPresetID();

private:
    BOOL handleCruise(NETDEV_PTZ_CRUISECMD_E eCruisecmd);

private:
    INT32 m_dwPtzSpeed;
    CComboBox m_oCBoxPresetPatrols;
    CComboBox m_oCBoxExtendPreset;
    CListCtrl m_oCruiseList;
    INT32 m_dwBeginPointX;
    INT32 m_dwBeginPointY;
    INT32 m_dwEndPointX;
    INT32 m_dwEndPointY;

public:
    afx_msg void OnBnClickedBtnPtzWiperOn();
    afx_msg void OnBnClickedBtnPtzWiperOff();
    afx_msg void OnBnClickedBtnPtzLightOn();
    afx_msg void OnBnClickedBtnPtzLightOff();
    afx_msg void OnBnClickedBtnPtzHeaterOn();
    afx_msg void OnBnClickedBtnPtzHeaterOff();
    afx_msg void OnBnClickedBtnPtzSnowremovalOn();
    afx_msg void OnBnClickedBtnPtzSnowremovalOff();
    afx_msg void OnBnClickedBtnGetRoute();
    afx_msg void OnBnClickedBtnStartRecordRoute();
    afx_msg void OnBnClickedBtnStopRecordRoute();
    afx_msg void OnBnClickedBtnStartRoutePatrol();
    afx_msg void OnBnClickedBtnStopRecordPatrol();
    afx_msg void OnBnClickedBtnGetPatrol();
    afx_msg void OnCbnSelchangeComboCruise();
    afx_msg void OnBnClickedBtnAddPoint();
    afx_msg void OnBnClickedBtnEditPoint();
    afx_msg void OnLvnItemchangedListCruise(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnBnClickedBtnPointDel();
    afx_msg void OnBnClickedBtnSavePatrol();
    afx_msg void OnBnClickedBtnDeletePatrol();
    afx_msg void OnBnClickedBtnStartPatrol();
    afx_msg void OnBnClickedBtnStopPatrol();
    afx_msg void OnCbnSelchangeComboExtendPreset();
};
