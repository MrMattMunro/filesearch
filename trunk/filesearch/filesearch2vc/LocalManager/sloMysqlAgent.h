// sloMysqlAgent.h: interface for the sloMysqlAgent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLOMYSQLAGENT_H__3286BA47_C6E5_424A_8B4E_34DEECE39BD0__INCLUDED_)
#define AFX_SLOMYSQLAGENT_H__3286BA47_C6E5_424A_8B4E_34DEECE39BD0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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

	std::vector<KeyWords_Group> m_GroupList;
	std::vector<KeyWords_Type> m_TypeList;
	std::vector<KeyWords> m_KeywordsList;
};

#endif // !defined(AFX_SLOMYSQLAGENT_H__3286BA47_C6E5_424A_8B4E_34DEECE39BD0__INCLUDED_)
