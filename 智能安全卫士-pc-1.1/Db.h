/*******************************************************************************
**		Fliename:Db.h
**      Description:数据库连接、向数据库发送请求
**
**															Copyright by QTYL	
**															Coding by Haiwera Zhan
**															Last Modify:2014/6/23 
********************************************************************************/

#if !defined(AFX_DB_H__F44BC67C_92FC_4D97_9E33_526DC0B83759__INCLUDED_)
#define AFX_DB_H__F44BC67C_92FC_4D97_9E33_526DC0B83759__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <winsock2.h>
#include <mysql.h>
#pragma comment(lib,"libmysql.lib")
class CDb  
{
public:
	LPCSTR GetError();
	int Fetch(LPCSTR sql);
	MYSQL_RES* Query(LPCSTR sql);
	CDb();
	virtual ~CDb();

private:
	MYSQL_RES *m_resResult;
	MYSQL m_mySQL;
};

#endif // !defined(AFX_DB_H__F44BC67C_92FC_4D97_9E33_526DC0B83759__INCLUDED_)
