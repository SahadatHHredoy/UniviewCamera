// DlgPrivacyMaskAlarm.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NetDemo.h"
#include "DlgPrivacyMaskAlarm.h"


// CDlgPrivacyMaskAlarm �Ի���

IMPLEMENT_DYNAMIC(CDlgPrivacyMaskAlarm, CDialog)

CDlgPrivacyMaskAlarm::CDlgPrivacyMaskAlarm(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPrivacyMaskAlarm::IDD, pParent)
{

}

CDlgPrivacyMaskAlarm::~CDlgPrivacyMaskAlarm()
{
}

void CDlgPrivacyMaskAlarm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgPrivacyMaskAlarm, CDialog)
END_MESSAGE_MAP()

BOOL CDlgPrivacyMaskAlarm::OnInitDialog()
{
    //���ƽ��� start
    CDialog::OnInitDialog();
    CRect rc(0, 0, 0, 0);
    GetParent()->GetClientRect(&rc);
    ((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
    MoveWindow(&rc);
    //���ƽ��� end
    return TRUE;
}
// CDlgPrivacyMaskAlarm ��Ϣ�������
