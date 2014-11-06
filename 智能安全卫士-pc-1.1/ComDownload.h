// ComDownload.h : main header file for the COMDOWNLOAD application
//

#if !defined(AFX_COMDOWNLOAD_H__D3503F8E_DA95_4989_9547_7808D54F8366__INCLUDED_)
#define AFX_COMDOWNLOAD_H__D3503F8E_DA95_4989_9547_7808D54F8366__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CComDownloadApp:
// See ComDownload.cpp for the implementation of this class
//

class CComDownloadApp : public CWinApp
{
public:
	CComDownloadApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComDownloadApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CComDownloadApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMDOWNLOAD_H__D3503F8E_DA95_4989_9547_7808D54F8366__INCLUDED_)
