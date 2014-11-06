/*******************************************************************************
**		Fliename:CEmployeeDlg.h
**      Description:员工信息管理，员工打卡记录查询
**
**															Copyright by QTYL	
**															Coding by Haiwera Zhan
**															Last Modify:2014/6/23 
********************************************************************************/
#if !defined(AFX_EMPLOYEEDLG_H__D96CD71B_C1F0_4117_9695_B1E72B4AB946__INCLUDED_)
#define AFX_EMPLOYEEDLG_H__D96CD71B_C1F0_4117_9695_B1E72B4AB946__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EmployeeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEmployeeDlg dialog
#include "Model.h"
class CEmployeeDlg : public CDialog
{
// Construction
public:
	void UpdateListRecord(LPCSTR where);
	int m_nIndexSelected;
	CEmployeeDlg(CWnd* pParent = NULL);   // standard constructor
	~CEmployeeDlg();
// Dialog Data
	//{{AFX_DATA(CEmployeeDlg)
	enum { IDD = IDD_EMPLOYEE };
	CListCtrl	m_lstCardRecord;
	CListCtrl	m_lstEmployee;
	CString	m_strNum;
	CString	m_strSex;
	int		m_strAge;
	CString	m_strName;
	CString	m_strStatus;
	CString	m_strSearchName;
	CString	m_strSearchNum;
	CTime	m_dpStart;
	CTime	m_dpEnd;
	int		m_nEnd;
	int		m_nStart;
	//}}AFX_DATA
	CModel* m_ModelEmp;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEmployeeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEmployeeDlg)
	afx_msg void OnBtnadd();
	virtual BOOL OnInitDialog();
	afx_msg void OnCancelMode();
	afx_msg void OnBtnrecord();
	afx_msg void OnSetfocusListemployeeview(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedListemployeeview(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtndelete();
	afx_msg void OnBtnmodify();
	afx_msg void OnBtnsearch();
	afx_msg void OnBtnsearchcard();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CModel *m_ModelRecord;
	void LeaveAdd();
	CRect m_rectSmall;
	CRect m_rectFull;
	void UpdateListEmployee(LPCSTR where="");
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EMPLOYEEDLG_H__D96CD71B_C1F0_4117_9695_B1E72B4AB946__INCLUDED_)
