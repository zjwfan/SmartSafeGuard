// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WisdomWellServer.h"
#include "LoginDlg.h"
#include "Model.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg dialog

char * CLoginDlg::m_szSelCode = "abcdefghijklmnopqrstuvwxyz123456ABCDEFGHIJKLMNOPQRSTUVWXYZ";
CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLoginDlg)
	m_strVerify = _T("");
	m_strPassword = _T("");
	m_strUserName = _T("");
	//}}AFX_DATA_INIT
}


void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoginDlg)
	DDX_Control(pDX, IDC_VERIFY, m_ctrlVerify);
	DDX_Text(pDX, IDC_EDITVERIFY, m_strVerify);
	DDX_Text(pDX, IDC_UPASSWORD, m_strPassword);
	DDX_Text(pDX, IDC_USERNAME, m_strUserName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
	//{{AFX_MSG_MAP(CLoginDlg)
	ON_BN_CLICKED(IDC_VERIFY, OnVerify)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTNOK, OnBtnok)
	ON_BN_CLICKED(IDC_BTNCANCEL, OnBtncancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg message handlers

void CLoginDlg::OnVerify() 
{
	// TODO: Add your control notification handler code here
	
	m_szCode[0] = m_szSelCode[rand() % m_iLength];
	m_szCode[1] = m_szSelCode[rand() % m_iLength];
	m_szCode[2] = m_szSelCode[rand() % m_iLength];
	m_szCode[3] = m_szSelCode[rand() % m_iLength];
	m_szCode[4] = 0;
	Invalidate();
}

BOOL CLoginDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_iLength = strlen(m_szSelCode);

	m_szCode[0] = m_szSelCode[rand() % m_iLength];
	m_szCode[1] = m_szSelCode[rand() % m_iLength];
	m_szCode[2] = m_szSelCode[rand() % m_iLength];
	m_szCode[3] = m_szSelCode[rand() % m_iLength];

	m_szCode[4] = 0;

	



	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLoginDlg::DrawVerify()
{
	CRect rect;
	this->GetDlgItem(IDC_VERIFY)->GetWindowRect(&rect);

	CClientDC dc(this);
	ScreenToClient(&rect);
	CBrush brh;
	brh.CreateSolidBrush(RGB(rand() % 255,rand() % 255,rand() % 255));
	dc.FillRect(&rect,&brh);
	//MessageBox(m_szCode);
	dc.SetBkMode(TRANSPARENT);
	dc.TextOut(rect.left + rand() % 10 + 5,rect.top + rand() % 10 + 5,&m_szCode[0],1);
	dc.TextOut(rect.left + rand() % 10 + 20,rect.top + rand() % 10 + 5,&m_szCode[1],1);
	dc.TextOut(rect.left + rand() % 10 + 35,rect.top + rand() % 10 + 5,&m_szCode[2],1);
	dc.TextOut(rect.left + rand() % 10 + 50,rect.top + rand() % 10 + 5,&m_szCode[3],1);

	int times = rand() % 100 + 100;
	for(int i = 0;i < times;i ++)
	{
		dc.SetPixel(rect.left + rand() % rect.Width(),rect.top + rand() % rect.Height(),RGB(rand() % 255,rand() % 255,rand() % 255)); 
	}
	
}


void CLoginDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	DrawVerify();
	// Do not call CDialog::OnPaint() for painting messages
}

void CLoginDlg::OnBtnok() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	
	m_strVerify.MakeUpper();
	
	//CDialog::OnOK();//weiyuan-chang 7.21--------参数设定！！！-------------
	if(m_strVerify.Compare(strupr(m_szCode)) == 0)
	{
		CModel user("user");

		MYSQL_RES * res;

		char where[50];

		sprintf(where,"username='%s' and password='%s'",m_strUserName,m_strPassword);

		res = user.Where(where).Select();
		if(res == NULL)
		{

			MessageBox("用户名不存在或密码错误");
			OnVerify();
		}
		else
		{

			MYSQL_ROW row;
			row = mysql_fetch_row(res);
			if(row == NULL)
			{
				MessageBox("用户名不存在或密码错误");
				OnVerify();
				return ;
			}
			//MessageBox(row[0]);
			CDialog::OnOK();
		}
	}
	else
	{
		MessageBox("验证码不正确");
		OnVerify();
	}
	//-chang 7.21--------参数设定！！！-------------
}

void CLoginDlg::OnBtncancel() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}
