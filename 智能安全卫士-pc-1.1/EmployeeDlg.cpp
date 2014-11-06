/*******************************************************************************
**		Fliename:CEmployeeDlg.cpp
**      Description:员工信息管理，员工打卡记录查询
**
**															Copyright by QTYL	
**															Coding by Haiwera Zhan
**															Last Modify:2014/6/23 
********************************************************************************/

#include "stdafx.h"
#include "WisdomWellServer.h"
#include "EmployeeDlg.h"
#include "UTime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CEmployeeDlg::CEmployeeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEmployeeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEmployeeDlg)
	m_strNum = _T("");
	m_strSex = _T("");
	m_strAge = 0;
	m_strName = _T("");
	m_strStatus = _T("");
	m_strSearchName = _T("");
	m_strSearchNum = _T("");
	m_dpStart = 0;
	m_dpEnd = 0;
	m_nEnd = 0;
	m_nStart = 0;
	//}}AFX_DATA_INIT
	m_ModelEmp = new CModel("employee");
	m_ModelRecord = new CModel("record");
}

CEmployeeDlg::~CEmployeeDlg()
{
	if(m_ModelEmp != NULL)
	{
		delete m_ModelEmp;
	}
}

void CEmployeeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEmployeeDlg)
	DDX_Control(pDX, IDC_LISTCARDRECORD, m_lstCardRecord);
	DDX_Control(pDX, IDC_LISTEMPLOYEEVIEW, m_lstEmployee);
	DDX_Text(pDX, IDC_EDITNUM, m_strNum);
	DDV_MaxChars(pDX, m_strNum, 20);
	DDX_Text(pDX, IDC_EDITSEX, m_strSex);
	DDV_MaxChars(pDX, m_strSex, 2);
	DDX_Text(pDX, IDC_EDITAGE, m_strAge);
	DDV_MinMaxInt(pDX, m_strAge, 0, 120);
	DDX_Text(pDX, IDC_EDITNAME, m_strName);
	DDV_MaxChars(pDX, m_strName, 20);
	DDX_Text(pDX, IDC_EDITSTATUS, m_strStatus);
	DDX_Text(pDX, IDC_EDITSEARCHBYNAME, m_strSearchName);
	DDX_Text(pDX, IDC_EDITSEARCHBYNUM, m_strSearchNum);
	DDX_DateTimeCtrl(pDX, IDC_DPEND, m_dpEnd);
	DDX_DateTimeCtrl(pDX, IDC_DPSTART, m_dpStart);
	DDX_Text(pDX, IDC_EDITEND, m_nEnd);
	DDX_Text(pDX, IDC_EDITSTART, m_nStart);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEmployeeDlg, CDialog)
	//{{AFX_MSG_MAP(CEmployeeDlg)
	ON_BN_CLICKED(IDC_BTNADD, OnBtnadd)
	ON_WM_CANCELMODE()
	ON_BN_CLICKED(IDC_BTNRECORD, OnBtnrecord)
	ON_NOTIFY(NM_SETFOCUS, IDC_LISTEMPLOYEEVIEW, OnSetfocusListemployeeview)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTEMPLOYEEVIEW, OnItemchangedListemployeeview)
	ON_BN_CLICKED(IDC_BTNDELETE, OnBtndelete)
	ON_BN_CLICKED(IDC_BTNMODIFY, OnBtnmodify)
	ON_BN_CLICKED(IDC_BTNSEARCH, OnBtnsearch)
	ON_BN_CLICKED(IDC_BTNSEARCHCARD, OnBtnsearchcard)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEmployeeDlg message handlers
/**  添加按扭被点击
*/
void CEmployeeDlg::OnBtnadd() 
{
	// TODO: Add your control notification handler code here
	CString str;
	//读取按钮的文本
	if(GetDlgItemText(IDC_BTNMODIFY,str),str == "确认修改")
	{
		SetDlgItemText(IDC_BTNMODIFY,"修改");
	}
	//如果按钮文件是添加
	if(GetDlgItemText(IDC_BTNADD,str),str == "添加")
	{
		m_strName = "";
		m_strNum = "";
		m_strSex = "";
		m_strAge = 0;
		UpdateData(FALSE);

/*		if(m_nIndexSelected != -1)
		{
			m_lstEmployee.SetItemState(m_nIndexSelected,LVIS_SELECTED | LVIS_FOCUSED ,LVIS_SELECTED);
		}
*/
		((CEdit *)GetDlgItem(IDC_EDITNAME))->SetReadOnly(FALSE);
		((CEdit *)GetDlgItem(IDC_EDITNUM))->SetReadOnly(FALSE);
		((CEdit *)GetDlgItem(IDC_EDITAGE))->SetReadOnly(FALSE);
		((CEdit *)GetDlgItem(IDC_EDITSEX))->SetReadOnly(FALSE);
//		((CEdit *)GetDlgItem(IDC_EDITSTATUS))->SetReadOnly(TRUE);
		SetDlgItemText(IDC_BTNADD,"确认添加");
	}
	else
	{
		UpdateData();
		if(m_strName == "" || m_strNum == "" || m_strSex == "")
		{
			MessageBox("请输入有效的值");
		}
		else
		{
			((CEdit *)GetDlgItem(IDC_EDITNAME))->SetReadOnly(TRUE);
			((CEdit *)GetDlgItem(IDC_EDITNUM))->SetReadOnly(TRUE);
			((CEdit *)GetDlgItem(IDC_EDITAGE))->SetReadOnly(TRUE);
			((CEdit *)GetDlgItem(IDC_EDITSEX))->SetReadOnly(TRUE);
			
			CString strWhere;
			strWhere.Format("EName='%s'",m_strName);
			if(m_ModelEmp->Where(strWhere).Count())
			{
				MessageBox("该员工已经存在");
				return ;
			}
			CString data;
			data.Format("%s,'%s','%s',%d",m_strNum,m_strName,m_strSex,m_strAge);
			if(m_ModelEmp->Insert(data))
			{
				MessageBox("添加成功");
				UpdateListEmployee();
				SetDlgItemText(IDC_BTNADD,"添加");
			}
			else
			{
				MessageBox("添加失败");
			}
		}
	}
}

BOOL CEmployeeDlg::OnInitDialog() 
{
	// TODO: Add extra initialization here
	CDialog::OnInitDialog();
	
	//获得员工列表窗口的风格
	LONG style = GetWindowLong(m_lstEmployee.m_hWnd,GWL_STYLE); 
	
	//改变员工列表窗口的风格
	SetWindowLong(m_lstEmployee.m_hWnd,GWL_STYLE,style | LVS_REPORT | LVS_SINGLESEL | LVS_SHOWSELALWAYS);
	
	//获得员工列表窗口的扩展风格
	m_lstEmployee.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	
	//获得打卡记录列表窗口的风格
	style = GetWindowLong(m_lstCardRecord.m_hWnd,GWL_STYLE);												
	
	//改变员工列表窗口的风格
	SetWindowLong(m_lstCardRecord.m_hWnd,GWL_STYLE,style | LVS_REPORT | LVS_SINGLESEL | LVS_SHOWSELALWAYS);
	
	//获得员工列表窗口的扩展风格
	m_lstCardRecord.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	

	((CEdit *)GetDlgItem(IDC_EDITNAME))->SetReadOnly(TRUE);
	((CEdit *)GetDlgItem(IDC_EDITNUM))->SetReadOnly(TRUE);
	((CEdit *)GetDlgItem(IDC_EDITAGE))->SetReadOnly(TRUE);
	((CEdit *)GetDlgItem(IDC_EDITSEX))->SetReadOnly(TRUE);
	((CEdit *)GetDlgItem(IDC_EDITSTATUS))->SetReadOnly(TRUE);

	//获得员工表所有列的信息
	list<CString> fieldsEmp = m_ModelEmp->GetFieldsName();
	list<CString>::iterator it;
	int i = 0;
	for(it = fieldsEmp.begin();it != fieldsEmp.end();it ++,i ++)
	{
		//给员工表设置列属性
		m_lstEmployee.InsertColumn(i,*it);
		m_lstEmployee.SetColumnWidth(i,110);
	}	
	
	//给打卡记录设置列属性
	m_lstCardRecord.InsertColumn(0,"位置");
	m_lstCardRecord.SetColumnWidth(0,70);
	m_lstCardRecord.InsertColumn(1,"打卡时间");
	m_lstCardRecord.SetColumnWidth(1,180);


	//第一次更新员工信息并将其输出到员工列表窗口
	UpdateListEmployee();

	//得到窗口完全显示时的显示区域
	GetWindowRect(&m_rectFull);
	CRect rect;

	//得到分隔组的区域，以分隔线为基准确定窗口缩小时的显示区域
	GetDlgItem(IDC_SEPERATOR)->GetWindowRect(&rect);
	m_rectSmall.top = m_rectFull.top;
	m_rectSmall.left = m_rectFull.left;
	m_rectSmall.bottom = m_rectFull.bottom;
	m_rectSmall.right = rect.right;
	
	//初始修改按钮和删除按钮不可用
	GetDlgItem(IDC_BTNMODIFY)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTNDELETE)->EnableWindow(FALSE);

	//窗口初始以缩小方式显示
	SetWindowPos(this,0,0,m_rectSmall.Width(),m_rectSmall.Height(),SWP_NOZORDER | SWP_NOMOVE);

	CUTime tNow;
	m_dpEnd = tNow.GetTime();
	tNow.m_day = 1;
	tNow.m_mon = 1;
	m_dpStart = tNow.GetTime();

	UpdateData(FALSE);
	//m_lstEmployee.FlashWindow(FALSE);
	return TRUE;  
	// return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CEmployeeDlg::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

/** 按条件更新员工信息列表窗口
	@param where:条件
*/
void CEmployeeDlg::UpdateListEmployee(LPCSTR where)
{
	//删除员工窗口列表的的有信息
	m_lstEmployee.DeleteAllItems();

	//按条件查找员工信息表
	MYSQL_RES * res = m_ModelEmp->Where(where).Select();
	if(res == NULL)return ;
	MYSQL_ROW row;
	int i = 0;

	//读取信息并显示在员工信息列表窗口上
	while(row = mysql_fetch_row(res))
	{
		m_lstEmployee.InsertItem(0,"");
		for(int j = 0;j < m_ModelEmp->GetFieldCount();j ++)
			m_lstEmployee.SetItemText(i,j,row[j]);
	}
}

void CEmployeeDlg::OnBtnrecord() 
{
	// TODO: Add your control notification handler code here
	CString str;
	if(GetDlgItemText(IDC_BTNRECORD,str),str == "打卡记录>>")
	{
		SetWindowPos(this,0,0,m_rectFull.Width(),m_rectFull.Height(),SWP_NOZORDER | SWP_NOMOVE);
		SetDlgItemText(IDC_BTNRECORD,"打卡记录<<");
	}
	else
	{
		SetWindowPos(this,0,0,m_rectSmall.Width(),m_rectSmall.Height(),SWP_NOZORDER | SWP_NOMOVE);
		SetDlgItemText(IDC_BTNRECORD,"打卡记录>>");
	}
}

void CEmployeeDlg::OnSetfocusListemployeeview(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	//m_lstEmployee.SetHotItem(0);
//	m_lstEmployee.SetItemState(0,LVIS_SELECTED | LVIS_FOCUSED ,LVIS_SELECTED);
	LeaveAdd();
	*pResult = 0;
}

void CEmployeeDlg::OnItemchangedListemployeeview(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	if(m_nIndexSelected = m_lstEmployee.GetNextItem(-1,LVIS_SELECTED),m_nIndexSelected != -1)
	{
		CString str;
		//str.Format("%d is Selected!",m_nIndexSelected);
		GetDlgItem(IDC_BTNMODIFY)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTNDELETE)->EnableWindow(TRUE);
		m_strNum = m_lstEmployee.GetItemText(m_nIndexSelected,0);
		m_strName = m_lstEmployee.GetItemText(m_nIndexSelected,1);	
		m_strSex = m_lstEmployee.GetItemText(m_nIndexSelected,2);
		str = m_lstEmployee.GetItemText(m_nIndexSelected,3);
		m_strAge = atoi(str);
		char where[50] = {0};
		int eid = atoi(m_strNum);

		sprintf(where,"EID=%d",eid);
		UpdateListRecord(where);
		UpdateData(FALSE);
	}
	else
	{
		GetDlgItem(IDC_BTNMODIFY)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTNDELETE)->EnableWindow(FALSE);
		m_nIndexSelected = -1;
	}
	*pResult = 0;
}
/** 
*/
void CEmployeeDlg::LeaveAdd()
{
	((CEdit *)GetDlgItem(IDC_EDITNAME))->SetReadOnly(TRUE);
	((CEdit *)GetDlgItem(IDC_EDITNUM))->SetReadOnly(TRUE);
	((CEdit *)GetDlgItem(IDC_EDITAGE))->SetReadOnly(TRUE);
	((CEdit *)GetDlgItem(IDC_EDITSEX))->SetReadOnly(TRUE);
	SetDlgItemText(IDC_BTNADD,"添加");
	SetDlgItemText(IDC_BTNMODIFY,"修改");
}

void CEmployeeDlg::OnBtndelete() 
{
	// TODO: Add your control notification handler code here
	CString msg;
	CString name;
	if(m_nIndexSelected != -1)
	{
		name = m_lstEmployee.GetItemText(m_nIndexSelected,1);
		msg.Format("您确定删除所有有关%s的数据吗?",name);
		if(IDYES == MessageBox(msg,NULL,MB_YESNO))
		{
			msg.Format("EID=%s",m_lstEmployee.GetItemText(m_nIndexSelected,0));
			if(m_ModelEmp->Where(msg).Delete())
			{
				MessageBox("删除成功!");
				UpdateListEmployee();
			}
			else
			{
				MessageBox("删除失败!");
			}
		}
	}
}

void CEmployeeDlg::OnBtnmodify() 
{
	// TODO: Add your control notification handler code here
	CString str;
	if(GetDlgItemText(IDC_BTNADD,str),str == "确认添加")
	{
		SetDlgItemText(IDC_BTNADD,"添加");
	}
	if(GetDlgItemText(IDC_BTNMODIFY,str),str == "修改")
	{
		m_strNum = m_lstEmployee.GetItemText(m_nIndexSelected,0);
		m_strName = m_lstEmployee.GetItemText(m_nIndexSelected,1);
		m_strSex = m_lstEmployee.GetItemText(m_nIndexSelected,2);
		m_strAge = atoi(m_lstEmployee.GetItemText(m_nIndexSelected,3));
		UpdateData(FALSE);
		
		((CEdit *)GetDlgItem(IDC_EDITNAME))->SetReadOnly(FALSE);
		//((CEdit *)GetDlgItem(IDC_EDITNUM))->SetReadOnly(FALSE);
		((CEdit *)GetDlgItem(IDC_EDITAGE))->SetReadOnly(FALSE);
		((CEdit *)GetDlgItem(IDC_EDITSEX))->SetReadOnly(FALSE);
//		((CEdit *)GetDlgItem(IDC_EDITSTATUS))->SetReadOnly(TRUE);
		SetDlgItemText(IDC_BTNMODIFY,"确认修改");
	}
	else
	{
		UpdateData();
		if(m_strName == "" || m_strNum == "" || m_strSex == "")
		{
			MessageBox("请输入有效的值");
		}
		else
		{
			((CEdit *)GetDlgItem(IDC_EDITNAME))->SetReadOnly(TRUE);
			((CEdit *)GetDlgItem(IDC_EDITNUM))->SetReadOnly(TRUE);
			((CEdit *)GetDlgItem(IDC_EDITAGE))->SetReadOnly(TRUE);
			((CEdit *)GetDlgItem(IDC_EDITSEX))->SetReadOnly(TRUE);
			
			CString data;
			data.Format("Ename='%s',Esex='%s',Eage=%d",m_strName,m_strSex,m_strAge);
			CString where;
			where.Format("EID=%s",m_strNum);
			if(m_ModelEmp->Where(where).Update(data))
			{
				UpdateListEmployee();
				SetDlgItemText(IDC_BTNMODIFY,"修改");
				UpdateData(FALSE);
			}
			else
			{
				MessageBox("修改失败");
			}
			//SetDlgItemText(IDC_BTNADD,"修改");
		}
		
	}
}

/**  查找员工按钮按下触发
*/
void CEmployeeDlg::OnBtnsearch() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CString where;

	//如果没有指定条件，条件为空字符串
	if(m_strSearchName == "" && m_strSearchNum == "")
	{
		where = "";
	}
	//如果指定了姓名并且指定了员工号
	else if(m_strSearchName != "" && m_strSearchNum != "")
	{
		where.Format("EName like '%%%s%%' And EID=%s",m_strSearchName,m_strSearchNum);
	}
	//如果只指定了员工姓名
	else if(m_strSearchName != "")
	{
		where.Format("Ename like '%%%s%%'",m_strSearchName);
	}
	//如果只指定了员工号
	else
	{
		where.Format("EID=%s",m_strSearchNum);
	}

	//按条件更新员工信息窗口
	UpdateListEmployee(where);

}
/**  更新打卡记录信息
	@param where: 条件
*/
void CEmployeeDlg::UpdateListRecord(LPCSTR where)
{
	//删除所有原记录项
	m_lstCardRecord.DeleteAllItems();

	//按条件读取数据库中打卡记录
	MYSQL_RES * res = m_ModelRecord->Field("RWhere,RTime").Where(where).Select();
	
	//如果记录集为空,直接返回
	if(res == NULL)return ;
	MYSQL_ROW row;
	int i = 0;
	int unixtime;

	//读取记录集信息，并显示在打卡记录的窗口上
	while(row = mysql_fetch_row(res))
	{
		m_lstCardRecord.InsertItem(0,"");
		m_lstCardRecord.SetItemText(0,0,CString(row[0]).Compare("1") ? "井上" : "井下");
		unixtime = atoi(row[1]);
		CUTime t(unixtime);
		m_lstCardRecord.SetItemText(0,1,t.FormatTime());
	}
}

void CEmployeeDlg::OnBtnsearchcard() 
{
	UpdateData();
	CUTime tNow;

	char where[50];

	sprintf(where,"RTime > %d and RTime < %d",CUTime(m_dpStart).GetUnixTime(),CUTime(m_dpEnd).GetUnixTime());
	// TODO: Add your control notification handler code here

		m_lstCardRecord.DeleteAllItems();

	//按条件读取数据库中打卡记录
	MYSQL_RES * res = m_ModelRecord->Field("RWhere,RTime").Where(where).Select();
	
	//如果记录集为空,直接返回
	if(res == NULL)return ;
	MYSQL_ROW row;
	int i = 0;
	int unixtime;

	//读取记录集信息，并显示在打卡记录的窗口上
	while(row = mysql_fetch_row(res))
	{
		m_lstCardRecord.InsertItem(0,"");
		m_lstCardRecord.SetItemText(0,0,CString(row[0]).Compare("1") ? "井上" : "井下");
		unixtime = atoi(row[1]);
		CUTime t(unixtime);
		m_lstCardRecord.SetItemText(0,1,t.FormatTime());
	}
	
}
