/*******************************************************************************
**		Fliename:Db.cpp
**      Description:数据库连接、向数据库发送请求
**
**															Copyright by QTYL	
**															Coding by Haiwera Zhan
**															Last Modify:2014/6/23 
********************************************************************************/

#include "stdafx.h"
#include "WisdomWellServer.h"
#include "Db.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern CConfigMgr theConfig;

CDb::CDb()
{
	CConfigMgr theConfig("WisdomWellServer.conf"); 
	mysql_init(&m_mySQL);
	int port = atoi(theConfig.GetConfigItem(CString("dbport")));
	MYSQL * isConnected=mysql_real_connect(&m_mySQL,theConfig.GetConfigItem(CString("dbhost")),
											theConfig.GetConfigItem(CString("dbusername")),
											theConfig.GetConfigItem(CString("dbpassword")),
											theConfig.GetConfigItem(CString("dbname")),
											port,0,CLIENT_MULTI_STATEMENTS);//连
	m_resResult = NULL;
	if (isConnected)
	{
		//AfxMessageBox(_T("success connected!"));
		//return;
	}
	else
	{
		int i = mysql_errno(&m_mySQL);//连接出错
		const char * s = mysql_error(&m_mySQL);
		AfxMessageBox(_T("failed to connect! Please check for your db service."));
		exit(0);
	}
}

CDb::~CDb()
{

}

MYSQL_RES* CDb::Query(LPCSTR sql)
{
	if(m_resResult != NULL)
	{
		mysql_free_result(m_resResult);
	}
	int res=mysql_query(&m_mySQL,sql);//执行sql命令
	if(!res)
	{
		m_resResult=mysql_store_result(&m_mySQL);//保存查询到的数据到result
		return m_resResult;
	}
	else
	{
		 return NULL;
	}
}

int CDb::Fetch(LPCSTR sql)
{
	if(m_resResult != NULL)
	{
		mysql_free_result(m_resResult);
	}
	int res=mysql_query(&m_mySQL,sql);//执行sql命令
	int rows = mysql_affected_rows(&m_mySQL);
	if(!res)
	{
		m_resResult=mysql_store_result(&m_mySQL);//保存查询到的数据到result
	}
	return rows;
}

LPCSTR CDb::GetError()
{
	return mysql_error(&m_mySQL);
}
