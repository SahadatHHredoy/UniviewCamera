// DlgPrivacyMaskAlarm.cpp : 实现文件
//

#include "stdafx.h"
#include "NetDemo.h"
#include "DlgPrivacyMaskAlarm.h"


// CDlgPrivacyMaskAlarm 对话框

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
    //绘制界面 start
    CDialog::OnInitDialog();
    CRect rc(0, 0, 0, 0);
    GetParent()->GetClientRect(&rc);
    ((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
    MoveWindow(&rc);
    //绘制界面 end
    return TRUE;
}
// CDlgPrivacyMaskAlarm 消息处理程序
