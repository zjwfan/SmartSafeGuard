#if !defined(AFX_CARRECORDDLG_H__886D46CE_249A_40C4_AF29_00119CECBA38__INCLUDED_)
#define AFX_CARRECORDDLG_H__886D46CE_249A_40C4_AF29_00119CECBA38__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CarRecordDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCarRecordDlg dialog
#include "Model.h"
class CCarRecordDlg : public CDialog
{
// Construction
public:
	CModel* m_mdlCar;
	CCarRecordDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCarRecordDlg)
	enum { IDD = IDD_CAR_RECORDDLG };
	CListCtrl	m_lstCar;
	BOOL	m_bChkTme;
	CTime	m_dpEnd;
	CTime	m_dpStart;
	int	m_nEnd;
	int	m_nStart;
	CString	m_strAvgYWeight;
	CString	m_strAvgWeight;
	CString	m_strCarNum;
	CString	m_strTime;
	CString	m_strTotalWeight;
	CString	m_strWeight;
	CString	m_strYWeight;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCarRecordDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCarRecordDlg)
	afx_msg void OnBtnsearch();
	virtual BOOL OnInitDialog();
	afx_msg void OnItemchangedLstcar(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CARRECORDDLG_H__886D46CE_249A_40C4_AF29_00119CECBA38__INCLUDED_)
