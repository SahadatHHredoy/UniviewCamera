#pragma once


// CDlgPrivacyMaskAlarm �Ի���

class CDlgPrivacyMaskAlarm : public CDialog
{
	DECLARE_DYNAMIC(CDlgPrivacyMaskAlarm)

public:
	CDlgPrivacyMaskAlarm(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgPrivacyMaskAlarm();

// �Ի�������
	enum { IDD = IDD_DLG_CHILD_WARNING_PRIVACY_MASK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
    virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
};
