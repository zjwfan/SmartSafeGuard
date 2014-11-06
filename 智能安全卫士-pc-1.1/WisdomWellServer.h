/*******************************************************************************
**		Fliename:WisdomWellApp.h
**      Description:应用程序类，表示应用程序实例
**
**															Copyright by QTYL	
**															Coding by Haiwera Zhan
**															Last Modify:2014/6/23 
********************************************************************************/
#if !defined(AFX_WISDOMWELLSERVER_H__7C4AF5DE_2AF6_41E8_9E7D_309B5F5F0833__INCLUDED_)
#define AFX_WISDOMWELLSERVER_H__7C4AF5DE_2AF6_41E8_9E7D_309B5F5F0833__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWisdomWellServerApp:
// See WisdomWellServer.cpp for the implementation of this class
//

class CWisdomWellServerApp : public CWinApp
{
public:
	CWisdomWellServerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWisdomWellServerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWisdomWellServerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WISDOMWELLSERVER_H__7C4AF5DE_2AF6_41E8_9E7D_309B5F5F0833__INCLUDED_)
