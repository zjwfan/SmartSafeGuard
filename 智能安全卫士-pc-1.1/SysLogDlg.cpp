/*******************************************************************************
**		Fliename:SyslogDlg.cpp
**      Description:
**
**															Copyright by QTYL	
**															Coding by Haiwera Zhan
**															Last Modify:2014/6/23 
********************************************************************************/
#include "stdafx.h"
#include "WisdomWellServer.h"
#include "SysLogDlg.h"
#include "UTime.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSysLogDlg dialog


CSysLogDlg::CSysLogDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSysLogDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSysLogDlg)
	m_bChkTime = FALSE;
	m_dpEnd = 0;
	m_dpStart = 0;
	m_strErrcode = _T("");
	m_strErrDeal = _T("");
	m_strErrReson = _T("");
	//}}AFX_DATA_INIT
}


void CSysLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSysLogDlg)
	DDX_Control(pDX, IDC_LSTSYSLOG, m_lstSysLog);
	DDX_Check(pDX, IDC_CHKTIME, m_bChkTime);
	DDX_DateTimeCtrl(pDX, IDC_DPEND, m_dpEnd);
	DDX_DateTimeCtrl(pDX, IDC_DPSTART, m_dpStart);
	DDX_Text(pDX, IDC_ERRCODE, m_strErrcode);
	DDX_Text(pDX, IDC_ERRDEAL, m_strErrDeal);
	DDX_Text(pDX, IDC_ERRRESON, m_strErrReson);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSysLogDlg, CDialog)
	//{{AFX_MSG_MAP(CSysLogDlg)
	ON_BN_CLICKED(IDC_BTNSEARCH, OnBtnsearch)
	ON_NOTIFY(NM_CLICK, IDC_LSTSYSLOG, OnClickLstsyslog)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LSTSYSLOG, OnItemchangedLstsyslog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSysLogDlg message handlers



BOOL CSysLogDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_mdlSysLog = new CModel("log");
	LONG style = GetWindowLong(m_lstSysLog.m_hWnd,GWL_STYLE);

	SetWindowLong(m_lstSysLog.m_hWnd,GWL_STYLE,style  | LVS_REPORT | LVS_SINGLESEL | LVS_SHOWSELALWAYS);
	m_lstSysLog.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	CUTime t;
	m_dpEnd = t.GetTime();
	t.m_day = 1;
	t.m_mon = 1;
	m_dpStart = t.GetTime();
	UpdateData(FALSE);

	list<CString> lst = m_mdlSysLog->GetFieldsName();
	list<CString>::iterator it = lst.begin();
	int i = 0;
	for(;it != lst.end();it ++,i ++)
	{
		m_lstSysLog.InsertColumn(i,*it);
		m_lstSysLog.SetColumnWidth(i,100);
	}

	MYSQL_RES * res = m_mdlSysLog->Select();
	MYSQL_ROW row;
	if(res != NULL)
	{
		while(row = mysql_fetch_row(res),row != NULL)
		{
			m_lstSysLog.InsertItem(0,"");

			for(int j = 0;j < m_mdlSysLog->GetFieldCount();j ++)
			{
				m_lstSysLog.SetItemText(0,j,row[j]);
			}
		}
	}
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CSysLogDlg::~CSysLogDlg()
{
	if(m_mdlSysLog != NULL)
	{
		delete m_mdlSysLog;
	}

}

void CSysLogDlg::OnBtnsearch() 
{
	// TODO: Add your control notification handler code here
	m_lstSysLog.DeleteAllItems();
	CUTime tStart(m_dpStart);
	CUTime tEnd(m_dpEnd);

	char where[50];
	sprintf(where,"LTime > %d and LTime < %d",tStart.GetUnixTime(),tEnd.GetUnixTime());

	MYSQL_RES * res = m_mdlSysLog->Where(where).Select();
	MYSQL_ROW row;
	int j;
	if(res != NULL)
	{
		while(row = mysql_fetch_row(res),row !=NULL)
		{
			m_lstSysLog.InsertItem(0,"");
			for(j = 0;j < m_mdlSysLog->GetFieldCount();j ++)
			{
				m_lstSysLog.SetItemText(0,j,row[j]);
			}
		}
	}
}

void CSysLogDlg::OnClickLstsyslog(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CSysLogDlg::OnItemchangedLstsyslog(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	int firstSel = m_lstSysLog.GetNextItem(-1,LVIS_SELECTED);
	if(firstSel != -1)
	{
		this->m_strErrcode = m_lstSysLog.GetItemText(firstSel,3);
		this->m_strErrDeal = m_lstSysLog.GetItemText(firstSel,2);
		this->m_strErrReson = m_lstSysLog.GetItemText(firstSel,1);
	}
	else
	{
		this->m_strErrcode = "";
		this->m_strErrReson = "";
		this->m_strErrDeal = "";
	}
	UpdateData(FALSE);
	*pResult = 0;
}
