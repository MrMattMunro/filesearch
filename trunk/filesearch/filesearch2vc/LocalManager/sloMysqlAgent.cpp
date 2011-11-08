// sloMysqlAgent.cpp: implementation of the sloMysqlAgent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "shortcutbar.h"
#include "sloMysqlAgent.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

sloMysqlAgent* sloMysqlAgent::m_hinstance = NULL;

sloMysqlAgent::sloMysqlAgent()
{

}

sloMysqlAgent::~sloMysqlAgent()
{

}
	
sloMysqlAgent* sloMysqlAgent::GetInstance()
{
	if (m_hinstance == NULL)
	{
		m_hinstance = new sloMysqlAgent();
 
	}

	return m_hinstance;
}

BOOL sloMysqlAgent::GetGroupsFromDB()
{
	ClearGroupList();

	//从数据库中获取最大的索引id
	if (!m_pMySqlDB && !ConnectDB())
	{
		return FALSE;
	}
	
	int dwMaxID = 0;
	std::string strQuerySQL = "select * from t_keywords_group";
	HRESULT hr = doSqlExe(FALSE, strQuerySQL.c_str());
	if (FAILED(hr))
		return -1;
	
	int nCount = m_pMySqlDB->GetRowCount();
	int nFieldCount = m_pMySqlDB->GetFieldCount();
	if(nCount >= 1 && nFieldCount >= 1)
	{	
		for (int i = 0; i < nCount; i++)
		{
			bool bSucc = m_pMySqlDB->GetRow();
			if(bSucc==false)
				return FALSE;
			
			int nIDLen = 0;
			char* pID = m_pMySqlDB->GetField("Id",&nIDLen);
			if(pID == NULL && nIDLen <= 1)
				return FALSE;

			int nGroupNameLen = 0;
			char* pGroupName = m_pMySqlDB->GetField("group_name",&nGroupNameLen);
			if(pGroupName == NULL && nGroupNameLen <= 1)
				return FALSE;

			KeyWords_Group group;
			memset(&group, NULL, sizeof(KeyWords_Group));
			group.nID = atoi(pID);
			strcpy(group.szGroupName, pGroupName);
			m_GroupList.push_back(group);
		}
	}
	
	return TRUE;
}

BOOL sloMysqlAgent::GetTypesFromDB(int nGroupID)
{
	ClearTypeList();

	//从数据库中获取最大的索引id
	if (!m_pMySqlDB && !ConnectDB())
	{
		return FALSE;
	}
	
	int dwMaxID = 0;
	std::string strQuerySQL = "select * from t_keywords_type where group_id=%d";
	HRESULT hr = doSqlExe(TRUE, strQuerySQL.c_str(), nGroupID);
	if (FAILED(hr))
		return -1;
	
	int nCount = m_pMySqlDB->GetRowCount();
	int nFieldCount = m_pMySqlDB->GetFieldCount();
	if(nCount >= 1 && nFieldCount >= 1)
	{	
		for (int i = 0; i < nCount; i++)
		{
			bool bSucc = m_pMySqlDB->GetRow();
			if(bSucc==false)
				return FALSE;
			
			int nIDLen = 0;
			char* pID = m_pMySqlDB->GetField("Id",&nIDLen);
			if(pID == NULL && nIDLen <= 1)
				return FALSE;
			
			int nTypeNameLen = 0;
			char* pTypeName = m_pMySqlDB->GetField("type_name",&nTypeNameLen);
			if(pTypeName == NULL && nTypeNameLen <= 1)
				return FALSE;
			
			KeyWords_Type type;
			memset(&type, NULL, sizeof(KeyWords_Type));
			type.nID = atoi(pID);
			strcpy(type.szTypeName, pTypeName);
			m_TypeList.push_back(type);
		}
	}
	
	return TRUE;
}

BOOL sloMysqlAgent::GetKeyWordsFromGroupName(char* szGroupName)
{
	//从数据库中获取最大的索引id
	if (!m_pMySqlDB && !ConnectDB())
	{
		return FALSE;
	}
	
	int nGroupID = 0;
	std::string strQuerySQL = "select * from t_keywords_group where group_name='%s'";
	HRESULT hr = doSqlExe(TRUE, strQuerySQL.c_str(), szGroupName);
	if (FAILED(hr))
		return -1;
	
	int nCount = m_pMySqlDB->GetRowCount();
	int nFieldCount = m_pMySqlDB->GetFieldCount();
	if(nCount >= 1 && nFieldCount >= 1)
	{	
		
		bool bSucc = m_pMySqlDB->GetRow();
		if(bSucc==false)
			return FALSE;
		
		int nIDLen = 0;
		char* pID = m_pMySqlDB->GetField("Id",&nIDLen);
		if(pID == NULL && nIDLen <= 1)
			return FALSE;
		
		nGroupID = atoi(pID);
	}
	/*
	//m_grouplist中根据groupname获取groupid
	int nGroupID = 0;
	int nCount = m_GroupList.size();
	for (int i = 0 ; i < nCount; i++)
	{
		if (strcmp(szGroupName, m_GroupList[i].szGroupName) == 0)
		{
			nGroupID = m_GroupList[i].nID;
			break;
		}
	}	
*/
	return GetKeyWordsFromDB(nGroupID, 0);
}

BOOL sloMysqlAgent::GetKeyWordsFromTypeName(char* szTypeName)
{
	//从数据库中获取最大的索引id
	if (!m_pMySqlDB && !ConnectDB())
	{
		return FALSE;
	}
	
	int nTypeID = 0;
	std::string strQuerySQL = "select * from t_keywords_type where type_name='%s'";
	HRESULT hr = doSqlExe(TRUE, strQuerySQL.c_str(), szTypeName);
	if (FAILED(hr))
		return -1;
	
	int nCount = m_pMySqlDB->GetRowCount();
	int nFieldCount = m_pMySqlDB->GetFieldCount();
	if(nCount >= 1 && nFieldCount >= 1)
	{	

		bool bSucc = m_pMySqlDB->GetRow();
		if(bSucc==false)
			return FALSE;
		
		int nIDLen = 0;
		char* pID = m_pMySqlDB->GetField("Id",&nIDLen);
		if(pID == NULL && nIDLen <= 1)
			return FALSE;
		
		nTypeID = atoi(pID);
	}
	/*
	int nTypeID = 0;
	int nCount = m_TypeList.size();
	for (int i = 0 ; i < nCount; i++)
	{
		if (strcmp(szTypeName, m_TypeList[i].szTypeName) == 0)
		{
			nTypeID = m_TypeList[i].nID;
			break;
		}
	}	
*/	
	return GetKeyWordsFromDB(0, nTypeID);
}

//nGroupID==0 & nTypeID==0表示获取所有的
BOOL sloMysqlAgent::GetKeyWordsFromDB(int nGroupID, int nTypeID)
{
	ClearKeywordsList();
	
	//从数据库中获取最大的索引id
	if (!m_pMySqlDB && !ConnectDB())
	{
		return FALSE;
	}
	
	std::string strQuerySQL;
	if (nGroupID == 0 && nTypeID == 0)
	{
		strQuerySQL = "select * from t_keywords"; 
		HRESULT hr = doSqlExe(FALSE, strQuerySQL.c_str());
		if (FAILED(hr))
			return -1;
	}
	
	if (nGroupID == 0 && nTypeID != 0)
	{
		strQuerySQL = "select * from t_keywords where key_type=%d"; 
		HRESULT hr = doSqlExe(TRUE, strQuerySQL.c_str(), nTypeID);
		if (FAILED(hr))
			return -1;
	}

	if (nGroupID != 0 && nTypeID == 0)
	{
		strQuerySQL = "select * from t_keywords where key_group=%d"; 
		HRESULT hr = doSqlExe(TRUE, strQuerySQL.c_str(), nGroupID);
		if (FAILED(hr))
			return -1;
	}

	if (nGroupID != 0 && nTypeID != 0)
	{
		strQuerySQL = "select * from t_keywords where key_group=%d and key_type=%d"; 
		HRESULT hr = doSqlExe(TRUE, strQuerySQL.c_str(), nGroupID, nTypeID);
		if (FAILED(hr))
			return -1;
	}
	
	int nCount = m_pMySqlDB->GetRowCount();
	int nFieldCount = m_pMySqlDB->GetFieldCount();
	if(nCount >= 1 && nFieldCount >= 1)
	{	
		for (int i = 0; i < nCount; i++)
		{
			bool bSucc = m_pMySqlDB->GetRow();
			if(bSucc==false)
				return FALSE;
			
			int nIDLen = 0;
			char* pID = m_pMySqlDB->GetField("Id",&nIDLen);
			if(pID == NULL && nIDLen <= 1)
				return FALSE;

			int nTypeIDLen = 0;
			char* pTypeID = m_pMySqlDB->GetField("key_type",&nTypeIDLen);
			if(pTypeID == NULL && nTypeIDLen <= 1)
				return FALSE;
	
//			int nGroupIDLen = 0;
// 			char* pGroupID = m_pMySqlDB->GetField("key_group",&nGroupIDLen);
// 			if(pGroupID == NULL && nGroupIDLen <= 1)
// 				return FALSE;

			int nKeyNameLen = 0;
			char* pKeyName = m_pMySqlDB->GetField("key_name",&nKeyNameLen);
			if(pKeyName == NULL && nKeyNameLen <= 1)
				return FALSE;

			int nDateLen = 0;
			char* pDate = m_pMySqlDB->GetField("date",&nDateLen);
			if(pDate == NULL && nDateLen <= 1)
				return FALSE;
			
			KeyWords keyword;
			memset(&keyword, NULL, sizeof(KeyWords_Type));
			keyword.nID = atoi(pID);
			keyword.nTypeID = atoi(pTypeID);
			keyword.nGroupID = 0/*atoi(pGroupID)*/;
			strcpy(keyword.szKeyName, pKeyName);
			strcpy(keyword.szDate, pDate);
			m_KeywordsList.push_back(keyword);
		}
	}
	
	return TRUE;	
}

BOOL sloMysqlAgent::AddType(char* szGroupName, char* szTypeName)
{
	//m_grouplist中根据groupname获取groupid
	int nGroupID = 0;
	int nCount = m_GroupList.size();
	for (int i = 0 ; i < nCount; i++)
	{
		if (strcmp(szGroupName, m_GroupList[i].szGroupName) == 0)
		{
			nGroupID = m_GroupList[i].nID;
			break;
		}
	}
	
	//从数据库中获取最大的索引id
	if (!m_pMySqlDB && !ConnectDB())
	{
		return FALSE;
	}
	
	//从
	BOOL bRet = TRUE;
	std::string strQuerySQL = "insert into t_keywords_type(type_name,group_id) values('%s',%d)";
	HRESULT hr = doSqlExe(TRUE, strQuerySQL.c_str(), szTypeName, nGroupID);
	if (FAILED(hr))
		bRet = FALSE;
	
	return bRet;

}

BOOL sloMysqlAgent::DelType(char* szTypeName)
{
	//从数据库中获取最大的索引id
	if (!m_pMySqlDB && !ConnectDB())
	{
		return FALSE;
	}
	
	//delete from t_keywords_type where type_name='%s'
	BOOL bRet = TRUE;
	std::string strQuerySQL = "delete from t_keywords_type where type_name='%s'";
	HRESULT hr = doSqlExe(TRUE, strQuerySQL.c_str(), szTypeName);
	if (FAILED(hr))
		bRet = FALSE;
	
	return bRet;	
}

BOOL sloMysqlAgent::UpdateType(char* szOldTypeName, char* szNewTypeName)
{
	//从数据库中获取最大的索引id
	if (!m_pMySqlDB && !ConnectDB())
	{
		return FALSE;
	}
	
	//update t_keywords_type set type_name='%s' where type_name='%s'
	BOOL bRet = TRUE;
	std::string strQuerySQL = "update t_keywords_type set type_name='%s' where type_name='%s'";
	HRESULT hr = doSqlExe(TRUE, strQuerySQL.c_str(), szNewTypeName, szOldTypeName);
	if (FAILED(hr))
		bRet = FALSE;
	
	return bRet;		
}

void sloMysqlAgent::ClearGroupList()
{
	m_GroupList.clear();

}

void sloMysqlAgent::ClearTypeList()
{
	m_TypeList.clear();
}

void sloMysqlAgent::ClearKeywordsList()
{
	m_KeywordsList.clear();
}

BOOL sloMysqlAgent::AddKeyword(char* szTypeName, char* szKeyName)
{
	BOOL bRet = TRUE;
	//从数据库中获取最大的索引id
	if (!m_pMySqlDB && !ConnectDB())
	{
		return FALSE;
	}
	
	int nTypeID = 0;
	std::string strQuerySQL = "select * from t_keywords_type where type_name='%s'";
	HRESULT hr = doSqlExe(TRUE, strQuerySQL.c_str(), szTypeName);
	if (FAILED(hr))
		return FALSE;
	
	int nCount = m_pMySqlDB->GetRowCount();
	int nFieldCount = m_pMySqlDB->GetFieldCount();
	if(nCount >= 1 && nFieldCount >= 1)
	{	
		
		bool bSucc = m_pMySqlDB->GetRow();
		if(bSucc==false)
			return FALSE;
		
		int nIDLen = 0;
		char* pID = m_pMySqlDB->GetField("Id",&nIDLen);
		if(pID == NULL && nIDLen <= 1)
			return FALSE;
		
		nTypeID = atoi(pID);
	}

	//插入数据库
	strQuerySQL = "insert into t_keywords(key_name,key_type) values('%s',%d)";
	hr = doSqlExe(TRUE, strQuerySQL.c_str(), szKeyName, nTypeID);
	if (FAILED(hr))
		bRet = FALSE;	

	return bRet;
	
}

BOOL sloMysqlAgent::DelKeyword(char* szKeyName)
{
	//从数据库中获取最大的索引id
	if (!m_pMySqlDB && !ConnectDB())
	{
		return FALSE;
	}
	
	//delete from t_keywords_type where type_name='%s'
	BOOL bRet = TRUE;
	std::string strQuerySQL = "delete from t_keywords where key_name='%s'";
	HRESULT hr = doSqlExe(TRUE, strQuerySQL.c_str(), szKeyName);
	if (FAILED(hr))
		bRet = FALSE;
	
	return bRet;		
}


BOOL sloMysqlAgent::UpdateKeyword(char* szOldKeyName, char* szNewKeyName, char* pTime)
{
	//从数据库中获取最大的索引id
	if (!m_pMySqlDB && !ConnectDB())
	{
		return FALSE;
	}
	
	//update t_keywords_type set type_name='%s' where type_name='%s'
	BOOL bRet = TRUE;
	std::string strQuerySQL = "update t_keywords set key_name='%s',date='%s', is_index=0 where key_name='%s'";
	HRESULT hr = doSqlExe(TRUE, strQuerySQL.c_str(), szNewKeyName, pTime, szOldKeyName);
	if (FAILED(hr))
		bRet = FALSE;
	
	return bRet;			
}


//////////////////////////////////////////////////////////////////////////
void sloMysqlAgent::ClearGroupList_Website()
{
	m_GroupListWebsite.clear();	
}
void sloMysqlAgent::ClearWebsiteList()
{
	m_WebsiteList.clear();
}

BOOL sloMysqlAgent::AddGroup_Website(char* szGroupName)
{
	//从数据库中获取最大的索引id
	if (!m_pMySqlDB && !ConnectDB())
	{
		return FALSE;
	}
	
	//从
	BOOL bRet = TRUE;
	std::string strQuerySQL = "insert into t_website_type(website_type) values('%s')";
	HRESULT hr = doSqlExe(TRUE, strQuerySQL.c_str(), szGroupName);
	if (FAILED(hr))
		bRet = FALSE;
	
	return bRet;	
}

BOOL sloMysqlAgent::DelGroup_Website(char* szGroupName)
{
	//从数据库中获取最大的索引id
	if (!m_pMySqlDB && !ConnectDB())
	{
		return FALSE;
	}
	
	//delete from t_keywords_type where type_name='%s'
	BOOL bRet = TRUE;
	std::string strQuerySQL = "delete from t_website_type where website_type='%s'";
	HRESULT hr = doSqlExe(TRUE, strQuerySQL.c_str(), szGroupName);
	if (FAILED(hr))
		bRet = FALSE;
	
	return bRet;		
}

BOOL sloMysqlAgent::UpdateGroup_Website(char* szOldGroupName, char* szNewGroupName)
{
	//从数据库中获取最大的索引id
	if (!m_pMySqlDB && !ConnectDB())
	{
		return FALSE;
	}
	
	//update t_keywords_type set type_name='%s' where type_name='%s'
	BOOL bRet = TRUE;
	std::string strQuerySQL = "update t_website_type set website_type='%s' where website_type='%s'";
	HRESULT hr = doSqlExe(TRUE, strQuerySQL.c_str(), szNewGroupName, szOldGroupName);
	if (FAILED(hr))
		bRet = FALSE;
	
	return bRet;			
}

BOOL sloMysqlAgent::GetGroupsFromDB_Website()
{
	ClearGroupList();
	
	//从数据库中获取最大的索引id
	if (!m_pMySqlDB && !ConnectDB())
	{
		return FALSE;
	}
	
	int dwMaxID = 0;
	std::string strQuerySQL = "select * from t_website_type";
	HRESULT hr = doSqlExe(FALSE, strQuerySQL.c_str());
	if (FAILED(hr))
		return -1;
	
	int nCount = m_pMySqlDB->GetRowCount();
	int nFieldCount = m_pMySqlDB->GetFieldCount();
	if(nCount >= 1 && nFieldCount >= 1)
	{	
		for (int i = 0; i < nCount; i++)
		{
			bool bSucc = m_pMySqlDB->GetRow();
			if(bSucc==false)
				return FALSE;
			
			int nIDLen = 0;
			char* pID = m_pMySqlDB->GetField("Id",&nIDLen);
			if(pID == NULL && nIDLen <= 1)
				return FALSE;
			
			int nGroupNameLen = 0;
			char* pGroupName = m_pMySqlDB->GetField("website_type",&nGroupNameLen);
			if(pGroupName == NULL && nGroupNameLen <= 1)
				return FALSE;
			
			WebSite_Group group;
			memset(&group, NULL, sizeof(WebSite_Group));
			group.nID = atoi(pID);
			strcpy(group.szGroupName, pGroupName);
			m_GroupListWebsite.push_back(group);
		}
	}
	
	return TRUE;	
}
BOOL sloMysqlAgent::GetWebsiteFromDB(int nGroupID)
{
	ClearWebsiteList();
	
	//从数据库中获取最大的索引id
	if (!m_pMySqlDB && !ConnectDB())
	{
		return FALSE;
	}
	
	std::string strQuerySQL;
	if (nGroupID == 0)
	{
		strQuerySQL = "select * from t_website"; 
		HRESULT hr = doSqlExe(FALSE, strQuerySQL.c_str());
		if (FAILED(hr))
			return -1;
	}else
	{
		strQuerySQL = "select * from t_website where website_type_id=%d"; 
		HRESULT hr = doSqlExe(TRUE, strQuerySQL.c_str(), nGroupID);
		if (FAILED(hr))
			return -1;
	}
	
	int nCount = m_pMySqlDB->GetRowCount();
	int nFieldCount = m_pMySqlDB->GetFieldCount();
	if(nCount >= 1 && nFieldCount >= 1)
	{	
		for (int i = 0; i < nCount; i++)
		{
			bool bSucc = m_pMySqlDB->GetRow();
			if(bSucc==false)
				return FALSE;
			
			int nIDLen = 0;
			char* pID = m_pMySqlDB->GetField("Id",&nIDLen);
			if(pID == NULL && nIDLen <= 1)
				return FALSE;
			
			int nTypeIDLen = 0;
			char* pTypeID = m_pMySqlDB->GetField("website_type_id",&nTypeIDLen);
			if(pTypeID == NULL && nTypeIDLen <= 1)
				return FALSE;
			
			int nWebsiteNameLen = 0;
			char* pWebsiteName = m_pMySqlDB->GetField("website",&nWebsiteNameLen);
			if(pWebsiteName == NULL && nWebsiteNameLen <= 1)
				return FALSE;
			
			int nDateLen = 0;
			char* pDate = m_pMySqlDB->GetField("date",&nDateLen);
			if(pDate == NULL && nDateLen <= 1)
				return FALSE;
			
			WebSite website;
			memset(&website, NULL, sizeof(WebSite));
			website.nID = atoi(pID);
			website.nTypeID = atoi(pTypeID);
			strcpy(website.szSiteName, pWebsiteName);
			strcpy(website.szDate, pDate);
			m_WebsiteList.push_back(website);
		}
	}
	
	return TRUE;		
}

BOOL sloMysqlAgent::GetWebsiteFromGroupName(char* szGroupName)
{
	//从数据库中获取最大的索引id
	if (!m_pMySqlDB && !ConnectDB())
	{
		return FALSE;
	}
	
	int nTypeID = 0;
	std::string strQuerySQL = "select * from t_website_type where website_type='%s'";
	HRESULT hr = doSqlExe(TRUE, strQuerySQL.c_str(), szGroupName);
	if (FAILED(hr))
		return -1;
	
	int nCount = m_pMySqlDB->GetRowCount();
	int nFieldCount = m_pMySqlDB->GetFieldCount();
	if(nCount >= 1 && nFieldCount >= 1)
	{	

		bool bSucc = m_pMySqlDB->GetRow();
		if(bSucc==false)
			return FALSE;
		
		int nIDLen = 0;
		char* pID = m_pMySqlDB->GetField("Id",&nIDLen);
		if(pID == NULL && nIDLen <= 1)
			return FALSE;
		
		nTypeID = atoi(pID);
	}

	return GetWebsiteFromDB(nTypeID);	
}