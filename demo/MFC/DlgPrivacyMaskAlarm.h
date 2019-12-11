#pragma once


// CDlgPrivacyMaskAlarm 对话框

class CDlgPrivacyMaskAlarm : public CDialog
{
	DECLARE_DYNAMIC(CDlgPrivacyMaskAlarm)

public:
	CDlgPrivacyMaskAlarm(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgPrivacyMaskAlarm();

// 对话框数据
	enum { IDD = IDD_DLG_CHILD_WARNING_PRIVACY_MASK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
    virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
};
