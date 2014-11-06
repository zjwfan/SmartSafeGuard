/*******************************************************************************
**		Fliename:SimpleingDlg.h
**      Description:
**
**															Copyright by QTYL	
**															Coding by Haiwera Zhan
**															Last Modify:2014/6/23 
********************************************************************************/

#if !defined(AFX_SAMPLINGDLG_H__74F94E96_E606_42A4_AC50_357FDA0994F9__INCLUDED_)
#define AFX_SAMPLINGDLG_H__74F94E96_E606_42A4_AC50_357FDA0994F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SamplingDlg.h : header file
//
#include "Model.h"

/////////////////////////////////////////////////////////////////////////////
// CSamplingDlg dialog

class CSamplingDlg : public CDialog
{
// Construction
public:
	CModel* m_mdlSampling;
	CSamplingDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSamplingDlg)
	enum { IDD = IDD_SAMPLINGDLG };
	CListCtrl	m_lstSampling;
	BOOL	m_bChkTime;
	CTime	m_dpEnd;
	CTime	m_dpStart;
	int		m_nEnd;
	int		m_nStart;
	CString	m_strAvgWe;
	CString	m_strAvgGas;
	CString	m_strAvgTemp;
	CString	m_strGas;
	CString	m_strTemp;
	CString	m_strTime;
	CString	m_strWe;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSamplingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSamplingDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnsearch();
	afx_msg void OnItemchangedLstsampling(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAMPLINGDLG_H__74F94E96_E606_42A4_AC50_357FDA0994F9__INCLUDED_)
