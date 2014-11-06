// ModifyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WisdomWellServer.h"
#include "ModifyDlg.h"
#include "Model.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModifyDlg dialog


CModifyDlg::CModifyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CModifyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CModifyDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CModifyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModifyDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CModifyDlg, CDialog)
	//{{AFX_MSG_MAP(CModifyDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModifyDlg message handlers

void CModifyDlg::OnOK() 
{
	// TODO: Add extra validation here
	CModel user("user");

	CString username;
	CString password;
	CString surepassword;
	GetDlgItemText(IDC_NEWUSERNAME,username);
	GetDlgItemText(IDC_NEWPASSWORD,password);
	GetDlgItemText(IDC_SUREPASSWORD,surepassword);
	char sql[255];

	

	if(password.Compare(surepassword) == 0)
	{
		sprintf(sql,"UPDATE user SET username='%s',password='%s' WHERE 1=1",username,password);
		if(user.Fetch(sql) > 0)
		{
			MessageBox("修改成功");
			CDialog::OnOK();
		}
		else
		{
			MessageBox("修改失败");
		}
	}
	else
	{
		MessageBox("两次输入密码不一致");
	}
	
}
