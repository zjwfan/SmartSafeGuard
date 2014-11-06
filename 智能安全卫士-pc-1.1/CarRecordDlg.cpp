// CarRecordDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WisdomWellServer.h"
#include "CarRecordDlg.h"
#include "UTime.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCarRecordDlg dialog


CCarRecordDlg::CCarRecordDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCarRecordDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCarRecordDlg)
	m_bChkTme = FALSE;
	m_dpEnd = 0;
	m_dpStart = 0;
	m_nEnd = 0;
	m_nStart = 0;
	m_strAvgYWeight = _T("");
	m_strAvgWeight = _T("");
	m_strCarNum = _T("");
	m_strTime = _T("");
	m_strTotalWeight = _T("");
	m_strWeight = _T("");
	m_strYWeight = _T("");
	//}}AFX_DATA_INIT
}


void CCarRecordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCarRecordDlg)
	DDX_Control(pDX, IDC_LSTCAR, m_lstCar);
	DDX_Check(pDX, IDC_CHKTIME, m_bChkTme);
	DDX_DateTimeCtrl(pDX, IDC_DPEND, m_dpEnd);
	DDX_DateTimeCtrl(pDX, IDC_DPSTART, m_dpStart);
	DDX_Text(pDX, IDC_EDITEND, m_nEnd);
	DDX_Text(pDX, IDC_EDITSTART, m_nStart);
	DDX_Text(pDX, IDC_STCAVEYWEIGHT, m_strAvgYWeight);
	DDX_Text(pDX, IDC_STCAVGWEIGHT, m_strAvgWeight);
	DDX_Text(pDX, IDC_STCCARNUM, m_strCarNum);
	DDX_Text(pDX, IDC_STCTIME, m_strTime);
	DDX_Text(pDX, IDC_STCTOTALWEIGHT, m_strTotalWeight);
	DDX_Text(pDX, IDC_STCWEIGHT, m_strWeight);
	DDX_Text(pDX, IDC_STCYWEIGHT, m_strYWeight);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCarRecordDlg, CDialog)
	//{{AFX_MSG_MAP(CCarRecordDlg)
	ON_BN_CLICKED(IDC_BTNSEARCH, OnBtnsearch)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LSTCAR, OnItemchangedLstcar)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCarRecordDlg message handlers

void CCarRecordDlg::OnBtnsearch() 
{
	// TODO: Add your control notification handler code here
	m_lstCar.DeleteAllItems();
	UpdateData();
	CUTime tStart(m_dpStart);
	tStart.m_h = m_nStart;
	CUTime tEnd(m_dpEnd);
	tEnd.m_h = m_nEnd;

	char where[50];

	sprintf(where,"CTime > %d and CTime < %d",tStart.GetUnixTime(),tEnd.GetUnixTime());

	if(m_bChkTme == 1)
	{
		MYSQL_RES *res;
		MYSQL_ROW row;

		res = m_mdlCar->Where(where).Select();
		if(res != NULL)
		{
			while(row = mysql_fetch_row(res),row != NULL)
			{
				m_lstCar.InsertColumn(0,"");

				m_lstCar.SetItemText(0,0,CUTime(atoi(row[0])).FormatTime());
				m_lstCar.SetItemText(0,1,row[1]);
				m_lstCar.SetItemText(0,2,row[2]);
			}
		}
	}
	else
	{
		MYSQL_RES *res;
		MYSQL_ROW row;
		res = m_mdlCar->Where("").Select();

		if(res != NULL)
		{
			while(row = mysql_fetch_row(res),row != NULL)
			{
				m_lstCar.InsertItem(0,"");

				m_lstCar.SetItemText(0,0,CUTime(atoi(row[0])).FormatTime());
				m_lstCar.SetItemText(0,1,row[1]);
				m_lstCar.SetItemText(0,2,row[2]);
			}
		}
	}
}

BOOL CCarRecordDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_mdlCar = new CModel("car");

	CUTime tNow;
	this->m_dpEnd = tNow.GetTime();
	tNow.m_day = 1;
	tNow.m_mon = 1;
	this->m_dpStart = tNow.GetTime();
	LONG style = GetWindowLong(m_lstCar.m_hWnd,GWL_STYLE);
	SetWindowLong(m_lstCar.m_hWnd,GWL_STYLE,style | LVS_REPORT | LVS_SINGLESEL | LVS_SHOWSELALWAYS);
	m_lstCar.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	// TODO: Add extra initialization here
	
	m_lstCar.InsertColumn(0,"时间");
	m_lstCar.InsertColumn(1,"");
	m_lstCar.InsertColumn(2,"");
//	m_lstCar.InsertColumn(3,"可燃性气体浓度");

	m_lstCar.SetColumnWidth(0,200);
	m_lstCar.SetColumnWidth(1,100);
	m_lstCar.SetColumnWidth(2,100);
//	m_lstCar.SetColumnWidth(3,100);

	MYSQL_RES * res = m_mdlCar->Select();

	int t;
	//char buffer[20];
	MYSQL_ROW row;
	if(res != NULL)
	{
		while(row = mysql_fetch_row(res),row != NULL)
		{
			m_lstCar.InsertItem(0,"");
		
			t = atoi(row[0]);
			CUTime tm(t);
			//m_lstCar.SetItemText(0,0,tm.FormatTime());
			//m_lstCar.SetItemText(0,1,row[1]);
			//m_lstCar.SetItemText(0,2,row[2]);
			
		}
	}
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCarRecordDlg::OnItemchangedLstcar(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	int nSelItem = m_lstCar.GetNextItem(-1,LVIS_SELECTED);
	if(nSelItem != -1)
	{
		m_strTime = m_lstCar.GetItemText(nSelItem,0);
		m_strYWeight = "";
		m_strWeight = "";
		//m_strYWeight = m_lstCar.GetItemText(nSelItem,1);
		//m_strWeight = m_lstCar.GetItemText(nSelItem,2);
	}
	else
	{
		m_strTime = "";
		m_strYWeight = "";
		m_strWeight = "";
	}
	UpdateData(FALSE);
	*pResult = 0;
}
