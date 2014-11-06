// DataCenter.h: interface for the CDataCenter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATACENTER_H__3A84FB0E_CD50_44E1_B876_16D6FEFB9DED__INCLUDED_)
#define AFX_DATACENTER_H__3A84FB0E_CD50_44E1_B876_16D6FEFB9DED__INCLUDED_

#include "mscomm.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDataCenter  
{
public:
	BOOL OpenComm();
	CDataCenter();
	virtual ~CDataCenter();
	friend void CALLBACK OnTimerProc(HWND hwnd,UINT msg,WPARAM wParam,unsigned long lParam);
private:

	OVERLAPPED m_OverlappedRead;
	int ReadData(char * buffer,unsigned long dwBytesRead);
	HANDLE m_hComDev;
};

#endif // !defined(AFX_DATACENTER_H__3A84FB0E_CD50_44E1_B876_16D6FEFB9DED__INCLUDED_)
