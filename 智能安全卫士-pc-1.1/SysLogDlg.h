/*******************************************************************************
**		Fliename:SyslogDlg.h
**      Description:
**
**															Copyright by QTYL	
**															Coding by Haiwera Zhan
**															Last Modify:2014/6/23 
********************************************************************************/
#if !defined(AFX_SYSLOGDLG_H__D5587E86_F01A_40A5_87A8_23A2AAD33933__INCLUDED_)
#define AFX_SYSLOGDLG_H__D5587E86_F01A_40A5_87A8_23A2AAD33933__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SysLogDlg.h : header file
//
#include "Model.h"

/////////////////////////////////////////////////////////////////////////////
// CSysLogDlg dialog

class CSysLogDlg : public CDialog
{
// Construction
public:
	~CSysLogDlg();
	CModel* m_mdlSysLog;
	CSysLogDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSysLogDlg)
	enum { IDD = IDD_SYS_LOG };
	CListCtrl	m_lstSysLog;
	BOOL	m_bChkTime;
	CTime	m_dpEnd;
	CTime	m_dpStart;
	CString	m_strErrcode;
	CString	m_strErrDeal;
	CString	m_strErrReson;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSysLogDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSysLogDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnsearch();
	afx_msg void OnClickLstsyslog(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedLstsyslog(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYSLOGDLG_H__D5587E86_F01A_40A5_87A8_23A2AAD33933__INCLUDED_)
