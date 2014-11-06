/*******************************************************************************
**		Fliename:SimpleingDlg.cpp
**      Description:
**
**															Copyright by QTYL	
**															Coding by Haiwera Zhan
**															Last Modify:2014/6/23 
********************************************************************************/

#include "stdafx.h"
#include "WisdomWellServer.h"
#include "SamplingDlg.h"
#include "UTime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSamplingDlg dialog


CSamplingDlg::CSamplingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSamplingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSamplingDlg)
	m_bChkTime = FALSE;
	m_dpEnd = 0;
	m_dpStart = 0;
	m_nEnd = 0;
	m_nStart = 0;
	m_strAvgWe = _T("");
	m_strAvgGas = _T("");
	m_strAvgTemp = _T("");
	m_strGas = _T("");
	m_strTemp = _T("");
	m_strTime = _T("");
	m_strWe = _T("");
	//}}AFX_DATA_INIT
}


void CSamplingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSamplingDlg)
	DDX_Control(pDX, IDC_LSTSAMPLING, m_lstSampling);
	DDX_Check(pDX, IDC_CHKTIME, m_bChkTime);
	DDX_DateTimeCtrl(pDX, IDC_DPEND, m_dpEnd);
	DDX_DateTimeCtrl(pDX, IDC_DPSTART, m_dpStart);
	DDX_Text(pDX, IDC_EDITEND, m_nEnd);
	DDX_Text(pDX, IDC_EDITSTART, m_nStart);
	DDX_Text(pDX, IDC_STCAVEWE, m_strAvgWe);
	DDX_Text(pDX, IDC_STCAVGGAS, m_strAvgGas);
	DDX_Text(pDX, IDC_STCAVGTEMP, m_strAvgTemp);
	DDX_Text(pDX, IDC_STCGAS, m_strGas);
	DDX_Text(pDX, IDC_STCTEMP, m_strTemp);
	DDX_Text(pDX, IDC_STCTIME, m_strTime);
	DDX_Text(pDX, IDC_STCWE, m_strWe);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSamplingDlg, CDialog)
	//{{AFX_MSG_MAP(CSamplingDlg)
	ON_BN_CLICKED(IDC_BTNSEARCH, OnBtnsearch)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LSTSAMPLING, OnItemchangedLstsampling)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSamplingDlg message handlers

BOOL CSamplingDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_mdlSampling = new CModel("sampling");

	CUTime tNow;
	this->m_dpEnd = tNow.GetTime();
	tNow.m_day = 1;
	tNow.m_mon = 1;
	this->m_dpStart = tNow.GetTime();
	LONG style = GetWindowLong(m_lstSampling.m_hWnd,GWL_STYLE);
	SetWindowLong(m_lstSampling.m_hWnd,GWL_STYLE,style | LVS_REPORT | LVS_SINGLESEL | LVS_SHOWSELALWAYS);
	m_lstSampling.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	// TODO: Add extra initialization here
	
	m_lstSampling.InsertColumn(0,"采样时间");
	m_lstSampling.InsertColumn(1,"温度");
	m_lstSampling.InsertColumn(2,"湿度");
	m_lstSampling.InsertColumn(3,"可燃性气体浓度");

	m_lstSampling.SetColumnWidth(0,200);
	m_lstSampling.SetColumnWidth(1,100);
	m_lstSampling.SetColumnWidth(2,100);
	m_lstSampling.SetColumnWidth(3,100);

	MYSQL_RES * res = m_mdlSampling->Select();

	int t;
	char buffer[20];
	MYSQL_ROW row;
	if(res != NULL)
	{
		while(row = mysql_fetch_row(res),row != NULL)
		{
			m_lstSampling.InsertItem(0,"");
		
			t = atoi(row[1]);
			CUTime tm(t);
			m_lstSampling.SetItemText(0,0,tm.FormatTime());
			m_lstSampling.SetItemText(0,1,row[2]);
			m_lstSampling.SetItemText(0,2,row[3]);
			m_lstSampling.SetItemText(0,3,row[4]);
			
		}
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSamplingDlg::OnBtnsearch() 
{
	// TODO: Add your control notification handler code here

	m_lstSampling.DeleteAllItems();
	UpdateData();
	if(m_bChkTime == 1)
	{
		CUTime t;
		CUTime tEnd(m_dpEnd);
		tEnd.m_h = this->m_nEnd;
		CUTime tStart(m_dpStart);
		tStart.m_h = this->m_nStart;
	
		char where[50];
		char buffer[20];
		sprintf(where,"STime < %d and STime > %d",tEnd.GetUnixTime(),tStart.GetUnixTime());

		MYSQL_RES * res;
		MYSQL_ROW row;
		res = m_mdlSampling->Where(where).Select();

		if(res != NULL)
		{
			while(row  = mysql_fetch_row(res),row != NULL)
			{
				m_lstSampling.InsertItem(0,"");
				
				CUTime tm(atoi(row[1]));

				m_lstSampling.SetItemText(0,0,tm.FormatTime());
				m_lstSampling.SetItemText(0,1,row[2]);
				m_lstSampling.SetItemText(0,2,row[3]);
				m_lstSampling.SetItemText(0,3,row[4]);
			}
		}
	}
	else
	{
		MYSQL_RES * res = m_mdlSampling->Select();

		int t;
		char buffer[20];
		MYSQL_ROW row;
		if(res != NULL)
		{
			while(row = mysql_fetch_row(res),row != NULL)
			{
				m_lstSampling.InsertItem(0,"");
			
				t = atoi(row[1]);
				CUTime tm(t);
				m_lstSampling.SetItemText(0,0,tm.FormatTime());
				m_lstSampling.SetItemText(0,1,row[2]);
				m_lstSampling.SetItemText(0,2,row[3]);
				m_lstSampling.SetItemText(0,3,row[4]);
				
			}
		}
	}
}

void CSamplingDlg::OnItemchangedLstsampling(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	int sItem = m_lstSampling.GetNextItem(-1,LVIS_SELECTED);
	if(sItem != -1)
	{
		m_strTime = m_lstSampling.GetItemText(sItem,0);
		m_strTemp = m_lstSampling.GetItemText(sItem,1);
		m_strWe = m_lstSampling.GetItemText(sItem,2);
		m_strGas = m_lstSampling.GetItemText(sItem,3);
		
		
		if(strstr(m_strGas,"5")!=NULL)
			m_strGas = "超标";
		else
			m_strGas = "安全";

	}
	else
	{
		m_strTime = "";
		m_strTemp = "";
		m_strWe = "";
		m_strGas = "安全";
	}
	UpdateData(FALSE);

	*pResult = 0;
}
