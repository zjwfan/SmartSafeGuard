/*******************************************************************************
**		Fliename:Model.cpp
**      Description:模型类，数据库表的管理
**
**															Copyright by QTYL	
**															Coding by Haiwera Zhan
**															Last Modify:2014/6/23 
********************************************************************************/

#include "stdafx.h"
#include "WisdomWellServer.h"
#include "Model.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CModel::CModel(LPCSTR tableName)
{
	this->m_strTableName = CString(tableName);

	//list<CString> l;
	CString str = "";
	MYSQL_ROW sql_row;
	str.Format("desc %s",this->m_strTableName);
	MYSQL_RES* result = this->m_db.Query(str);
	if(!result)
	{
		CString msg;
		msg.Format("%s 表不存在!",this->m_strTableName);
		AfxMessageBox(msg);
		return ;
	}
	CString ss;
	this->m_strField = "";
	while(sql_row=mysql_fetch_row(result))//获取具体的数据
    {
		ss.Format("%s",sql_row[0]);
		m_lstField.push_back(ss);
		this->m_strField += ss + ',';
	}
	m_iFieldCount = m_lstField.size();
	//return l;
	this->m_strField.Delete(this->m_strField.GetLength() - 1);
	//AfxMessageBox(this->m_strField);
	this->m_strOrder = "";
	this->m_strWhere = "";
}
CDb CModel::m_db = CDb();
std::list<CString> CModel::GetFieldsName()
{
	return this->m_lstField;
}	

CModel::~CModel()
{

}



int CModel::GetFieldCount()
{
	return this->m_iFieldCount;
}

MYSQL_RES * CModel::Query(LPCSTR sql)
{
#ifdef __DEBUG__
	AfxMessageBox(sql);
#endif
	return this->m_db.Query(sql);
}

MYSQL_RES* CModel::Select()
{
	CString str;
	if(this->m_strWhere == "" && this->m_strOrder == "")
	{
		str.Format("SELECT %s FROM %s",this->m_strField,this->m_strTableName);
	}
	else if(this->m_strWhere == "")
	{
		str.Format("SELECT %s FROM %s ORDER BY %s",this->m_strField,this->m_strTableName,this->m_strOrder);
	}
	else if(this->m_strOrder == "")
	{
		str.Format("SELECT %s FROM %s WHERE %s",this->m_strField,this->m_strTableName,
				this->m_strWhere);
	}
	else
	{
		str.Format("SELECT %s FROM %s WHERE %s ORDER BY %s",this->m_strField,this->m_strTableName,
				this->m_strWhere,this->m_strOrder);
	}
	//AfxMessageBox(str);
	return CModel::m_db.Query(str);

}

CModel& CModel::Field(LPCSTR fileds)
{
	this->m_strField = fileds;
	return *this;
}

CModel& CModel::Where(LPCSTR whr)
{
	this->m_strWhere = whr;
	return *this;
}

CModel& CModel::Order(LPCSTR order)
{
	this->m_strOrder;
	return *this;
}

BOOL CModel::Insert(LPCSTR data)
{
	CString str;
	str.Format("INSERT INTO %s(%s) VALUES(%s)",this->m_strTableName,this->m_strField,data);
#ifdef __DEBUG__
//	AfxMessageBox(str);
#endif
	if(-1 == CModel::m_db.Fetch(str))
	{
		//AfxMessageBox(CModel::m_db.GetError());
		return FALSE;
	}
	return TRUE;
}

int CModel::Count()
{
	CString str;
	int count;
	if(m_strWhere != "")
	{
		str.Format("SELECT %s FROM %s WHERE %s",this->m_strField,this->m_strTableName,this->m_strWhere);
	}
	else
	{
		str.Format("SELECT %s FROM %s",this->m_strField,this->m_strTableName);
	}
	//AfxMessageBox(str);
	MYSQL_RES* res = CModel::m_db.Query(str);
	count = mysql_num_rows(res);
	//str.Format("it is %d",count);
	//AfxMessageBox(str);
	return count;
}

BOOL CModel::Delete()
{
	CString str;
	int count;
	if(m_strWhere != "")
	{
		str.Format("DELETE FROM %s WHERE %s",this->m_strTableName,this->m_strWhere);
	}
	else
	{
		str.Format("DELETE FROM %s",this->m_strTableName);
	}
	//AfxMessageBox(str);
	if(-1 == CModel::m_db.Fetch(str))
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

BOOL CModel::Update(LPCSTR data)
{
	CString str;
	int count;
	if(m_strWhere != "")
	{
		str.Format("UPDATE %s SET %s WHERE %s",this->m_strTableName,data,this->m_strWhere);
	}
	else
	{
		str.Format("UPDATE %s SET %s",this->m_strTableName,data);
	}
	//AfxMessageBox(str);
	if(-1 == CModel::m_db.Fetch(str))
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

int CModel::Fetch(LPCSTR sql)
{
#ifdef __DEBUG__
	AfxMessageBox(sql);
#endif
	return this->m_db.Fetch(sql);

}
