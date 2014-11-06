// DataCenter.cpp: implementation of the CDataCenter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WisdomWellServer.h"
#include "DataCenter.h"
#include "MSComm.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDataCenter::CDataCenter()
{
	OpenComm();
	SetTimer(NULL,1,100,OnTimerProc);
}

CDataCenter::~CDataCenter()
{

}

BOOL CDataCenter::OpenComm()
{
	DCB dcb;
	m_hComDev=CreateFile("COM2", GENERIC_READ | GENERIC_WRITE ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED ,NULL);
	//  打开串口，异步操作      
	if(m_hComDev == NULL)return FALSE;
	dcb.DCBlength = sizeof ( DCB );
	GetCommState( m_hComDev, &dcb );        // 获得端口默认设置   
	dcb.BaudRate=CBR_115200;
	dcb.ByteSize= 8;
	dcb.Parity= NOPARITY;
	dcb.StopBits=(BYTE)ONESTOPBIT;
}

int CDataCenter::ReadData(char * buffer,unsigned long dwBytesRead)
{
	BOOL  bReadStatus;
	bReadStatus = ReadFile( m_hComDev ,buffer,dwBytesRead, &dwBytesRead, &m_OverlappedRead );
	if(! bReadStatus )
    {     
		if( GetLastError () == ERROR_IO_PENDING )    
		{   
			WaitForSingleObject(m_OverlappedRead.hEvent,10);
			return(( int ) dwBytesRead );
		}    
		return(0);    
	}     
	return(( int ) dwBytesRead );  
}


void CALLBACK OnTimerProc(HWND hwnd,UINT msg,WPARAM wParam,unsigned long lParam)
{
	static char buffer[255];
	if(ReadData(buffer,255))
	{
		AfxMessageBox(buffer);
	}
}
