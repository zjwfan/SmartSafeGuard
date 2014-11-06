/*******************************************************************************
**		Fliename:UTime.h
**      Description:时间戳到时间的转换、时间到时间戳的转换
**
**															Copyright by QTYL	
**															Coding by Haiwera Zhan
**															Last Modify:2014/6/23 
********************************************************************************/

#include "stdafx.h"
#include "WisdomWellServer.h"
#include "UTime.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUTime::CUTime(int unixtime)
{
	m_year = unixtime / 31556926 + 1970;
	m_mon = unixtime % 31556926 / 2629743 + 1;
	m_day = unixtime % 31556926 % 2629743 / 86400 + 1;
	m_h = unixtime % 31556926 % 2629743 % 86400 / 3600;
	m_m = unixtime % 31556926 % 2629743 % 86400 % 3600 / 60;
	m_s = unixtime % 31556926 % 2629743 % 86400 % 3600 % 60;

	m_unixTime = unixtime;
}
CUTime::CUTime()
{
	CTime t = CTime::GetCurrentTime();
	m_year = t.GetYear();
	m_mon = t.GetMonth();
	m_day = t.GetDay();
	m_h = t.GetHour();
	m_m = t.GetMinute();
	m_s = t.GetSecond();
	
	m_unixTime = (m_year - 1970) * 31556926 + (m_mon - 1) * 2629743 + (m_day - 1) * 86400 + m_h * 3600 + m_m * 60 + m_s;
	
}
CUTime::CUTime(int year,int mon,int day,int h,int m,int s)
{
	m_year = year;
	m_mon = mon;
	m_day = day;
	m_h = h;
	m_m = m;
	m_s = s;
	
	m_unixTime = (year - 1970) * 31556926 + (mon - 1) * 2629743 + (day - 1) * 86400 + h * 3600 + m * 60 + s;

}
int CUTime::GetUnixTime()
{
	return m_unixTime;
}
CUTime::~CUTime()
{

}


CString CUTime::FormatTime()
{
	char result[20];
	sprintf(result,"%4d/%2d/%2d %2d:%2d:%2d",m_year,m_mon,m_day,m_h,m_m,m_s);
	return  CString(result);
}

CTime CUTime::GetTime()
{
	return CTime(m_year,m_mon,m_day,m_h,m_m,m_s);
}

CUTime::CUTime(CTime time)
{
	m_year = time.GetYear();
	m_mon = time.GetMonth();
	m_day = time.GetDay();
	m_h = time.GetHour();
	m_m = time.GetMinute();
	m_s = time.GetSecond();
	
	m_unixTime = (m_year - 1970) * 31556926 + (m_mon - 1) * 2629743 + (m_day - 1) * 86400 + m_h * 3600 + m_m * 60 + m_s;
}
