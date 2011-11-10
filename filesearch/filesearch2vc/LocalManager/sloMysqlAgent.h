// sloMysqlAgent.h: interface for the sloMysqlAgent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLOMYSQLAGENT_H__3286BA47_C6E5_424A_8B4E_34DEECE39BD0__INCLUDED_)
#define AFX_SLOMYSQLAGENT_H__3286BA47_C6E5_424A_8B4E_34DEECE39BD0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//////////////////////////////////////////////////////////////////////////
//keywords
typedef struct _KeyWords_Group
{	
	int nID;
	char szGroupName[100];
}KeyWords_Group, *LPKeyWords_Group;

typedef struct _KeyWords_Type
{	
	int nID;
	int nGroupID;
	char szTypeName[100];
}KeyWords_Type, *LPKeyWords_Type;

typedef struct _KeyWords
{	
	int nID;
	int nGroupID;
	int nTypeID;
	char szKeyName[100];
	char szDate[100];
}KeyWords, *LPKeyWords;


//////////////////////////////////////////////////////////////////////////
//web site
typedef struct _WebSite_Group
{	
	int nID;
	char szGroupName[100];
}WebSite_Group, *LPWebSite_Group;

typedef struct _WebSite
{	
	int nID;
	int nTypeID;
	char szSiteName[100];
	char szDate[100];
}WebSite, *LPWebSite;

class sloMysqlAgent  :public mysqlcomm
{
public:
	sloMysqlAgent();
	virtual ~sloMysqlAgent();

	static sloMysqlAgent* GetInstance();
	static sloMysqlAgent* m_hinstance;

public:
	BOOL GetGroupsFromDB();
	BOOL GetTypesFromDB(int nGroupID);	
	BOOL GetKeyWordsFromDB(int nGroupID, int nTypeID);
	BOOL GetKeyWordsFromGroupName(char* szGroupName);
	BOOL GetKeyWordsFromTypeName(char* szTypeName);
public:
	//type
	BOOL AddType(char* szGroupName, char* szTypeName);
	BOOL DelType(char* szTypeName);
	BOOL UpdateType(char* szOldTypeName, char* szNewTypeName);
public:
	//keywords
	BOOL AddKeyword(char* szTypeName, char* szKeyName);
	BOOL DelKeyword(char* szKeyName);
	BOOL UpdateKeyword(char* szOldKeyName, char* szNewKeyName, char* pTime);
public:	
	void ClearGroupList();
	void ClearTypeList();
	void ClearKeywordsList();

//////////////////////////////////////////////////////////////////////////
//website
public:
	void ClearGroupList_Website();
	void ClearWebsiteList();
public:
	//type
	BOOL AddGroup_Website(char* szGroupName);
	BOOL DelGroup_Website(char* szGroupName);
	BOOL UpdateGroup_Website(char* szOldGroupName, char* szNewGroupName);
public:
	BOOL GetGroupsFromDB_Website();
	BOOL GetWebsiteFromDB(int nGroupID);
	BOOL GetWebsiteFromGroupName(char* szGroupName);
public:
	//website
	BOOL AddWebsite(char* szTypeName, char* szKeyName);
	BOOL DelWebsite(char* szKeyName);
	BOOL UpdateWebsite(char* szOldKeyName, char* szNewKeyName, char* pTime);
public:
	std::vector<KeyWords_Group> m_GroupList;
	std::vector<KeyWords_Type> m_TypeList;
	std::vector<KeyWords> m_KeywordsList;


	std::vector<WebSite_Group> m_GroupListWebsite;
	std::vector<WebSite> m_WebsiteList;
};

#endif // !defined(AFX_SLOMYSQLAGENT_H__3286BA47_C6E5_424A_8B4E_34DEECE39BD0__INCLUDED_)
