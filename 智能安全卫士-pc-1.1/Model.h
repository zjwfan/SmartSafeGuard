/*******************************************************************************
**		Fliename:Model.h
**      Description:模型类，数据库表的管理
**
**															Copyright by QTYL	
**															Coding by Haiwera Zhan
**															Last Modify:2014/6/23 
********************************************************************************/

#if !defined(AFX_MODEL_H__439DF9FD_4618_4E7C_AF53_C090234C164C__INCLUDED_)
#define AFX_MODEL_H__439DF9FD_4618_4E7C_AF53_C090234C164C__INCLUDED_

#include "Db.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CModel  
{
public:
	int Fetch(LPCSTR sql);
	BOOL Update(LPCSTR data);
	BOOL Delete();
	int Count();
	BOOL Insert(LPCSTR data);
	CModel& Order(LPCSTR order);
	CModel& Where(LPCSTR whr);
	CModel& Field(LPCSTR fileds);
	MYSQL_RES* Select();
	MYSQL_RES * Query(LPCSTR sql);
	int GetFieldCount();
	CModel(LPCSTR tableName);
	virtual ~CModel();
	std::list<CString> GetFieldsName();
private:
	CString m_strField;
	CString m_strOrder;
	CString m_strWhere;
	list<CString> m_lstField;
	int m_iFieldCount;
	static CDb m_db;
	CString m_strTableName;
};

#endif // !defined(AFX_MODEL_H__439DF9FD_4618_4E7C_AF53_C090234C164C__INCLUDED_)
