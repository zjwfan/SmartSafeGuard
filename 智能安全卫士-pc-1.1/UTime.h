/*******************************************************************************
**		Fliename:UTime.h
**      Description:时间戳到时间的转换、时间到时间戳的转换
**
**															Copyright by QTYL	
**															Coding by Haiwera Zhan
**															Last Modify:2014/6/23 
********************************************************************************/

#if !defined(AFX_UTIME_H__80F61F1B_37B7_47B0_AA7A_91F3B0972DE8__INCLUDED_)
#define AFX_UTIME_H__80F61F1B_37B7_47B0_AA7A_91F3B0972DE8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUTime  
{
public:
	CUTime(CTime time);
	CTime GetTime();
	CString FormatTime();
	int m_unixTime;
	int m_mon;
	int m_year;
	int m_day;
	int m_h;
	int m_m;
	int m_s;
	CUTime();
	CUTime(int unixtime);
	CUTime(int year,int mon,int day,int h,int m,int s);
	int GetUnixTime();
	virtual ~CUTime();

};

#endif // !defined(AFX_UTIME_H__80F61F1B_37B7_47B0_AA7A_91F3B0972DE8__INCLUDED_)
