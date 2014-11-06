/*******************************************************************************
**		Fliename:ConfigMgr.h
**      Description:配置文件的管理，全局配置项
**															Copyright by QTYL	
**															Coding by Haiwera Zhan
**															Last Modify:2014/6/23 
********************************************************************************/

#if !defined(AFX_CONFIGMGR_H__453C7958_EE97_4191_A6B6_4F4B7D9795C7__INCLUDED_)
#define AFX_CONFIGMGR_H__453C7958_EE97_4191_A6B6_4F4B7D9795C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CConfigMgr  
{
public:
	void SaveConfig();
	void SetConfigItem(CString item,CString value);
	CString GetConfigItem(CString name);
	CConfigMgr(CString strFileName = "WisdomWellServer.conf");
	virtual ~CConfigMgr();

private:
	CStringArray m_arrConfigs;
	FILE* m_fpConfFile;
};

#endif // !defined(AFX_CONFIGMGR_H__453C7958_EE97_4191_A6B6_4F4B7D9795C7__INCLUDED_)
