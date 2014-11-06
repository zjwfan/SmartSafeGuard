/*******************************************************************************
**		Fliename:SettingDlg.h
**      Description:
**
**															Copyright by QTYL	
**															Coding by Haiwera Zhan
**															Last Modify:2014/6/23 
********************************************************************************/

#if !defined(AFX_SETTINGDLG_H__9B4CCD14_0E43_472D_952E_2E56C67224D8__INCLUDED_)
#define AFX_SETTINGDLG_H__9B4CCD14_0E43_472D_952E_2E56C67224D8__INCLUDED_

#include "ConfigMgr.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SettingDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSettingDlg dialog

class CSettingDlg : public CDialog
{
// Construction
public:
	~CSettingDlg();
	CSettingDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSettingDlg)
	enum { IDD = IDD_SETTINGDLG };
	CString	m_strMaxGas;
	CString	m_strMaxTemp;
	CString	m_strPassword;
	CString	m_strPhoneNum;
	int		m_nRealTimeHour;
	int		m_nRealTimeMin;
	int		m_nRealTimeSec;
	int		m_nSafeWeight;
	int		m_nTimeAftOffHour;
	int		m_nTimeAftOffMin;
	int		m_nTimeAftOnHour;
	int		m_nTimeAftOnMin;
	int		m_nTimeDiff;
	int		m_nTimeMorOffHour;
	int		m_nTimeMorOffMin;
	int		m_nTimeMorOnHour;
	int		m_nTimeMorOnMin;
	int		m_nVMechine;
	CTime	m_strCurrDate;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSettingDlg)
	afx_msg void OnBtnOk();
	afx_msg void OnBtnCancel();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnCloseupCurrdate(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDatetimechangeCurrdate(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeRealtimeHour();
	afx_msg void OnChangeRealtimeMin();
	afx_msg void OnChangeRealtimeSec();
	afx_msg void OnSetfocusRealtimeSec();
	afx_msg void OnKillfocusRealtimeSec();
	afx_msg void OnSetfocusRealtimeMin();
	afx_msg void OnKillfocusRealtimeMin();
	afx_msg void OnSetfocusRealtimeHour();
	afx_msg void OnKillfocusRealtimeHour();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SetRealTime();
	CString IntToString(int i);
	CConfigMgr m_confMgr;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTINGDLG_H__9B4CCD14_0E43_472D_952E_2E56C67224D8__INCLUDED_)
