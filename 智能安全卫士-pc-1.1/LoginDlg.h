#if !defined(AFX_LOGINDLG_H__C7613DD8_6D68_457C_AACB_581D2A196978__INCLUDED_)
#define AFX_LOGINDLG_H__C7613DD8_6D68_457C_AACB_581D2A196978__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LoginDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg dialog

class CLoginDlg : public CDialog
{
// Construction
public:
	CLoginDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLoginDlg)
	enum { IDD = IDD_LOGINDLG };
	CStatic	m_ctrlVerify;
	CString	m_strVerify;
	CString	m_strPassword;
	CString	m_strUserName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoginDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLoginDlg)
	afx_msg void OnVerify();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnBtnok();
	afx_msg void OnBtncancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void DrawVerify();
	int m_iLength;
	static char* m_szSelCode;
	char m_szCode[10];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGINDLG_H__C7613DD8_6D68_457C_AACB_581D2A196978__INCLUDED_)
