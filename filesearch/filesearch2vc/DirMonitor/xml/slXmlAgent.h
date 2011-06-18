// slXmlAgent.h: interface for the slXmlAgent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLXMLAGENT_H__EBFD94D2_A970_405E_8A9D_D78AC361DC9C__INCLUDED_)
#define AFX_SLXMLAGENT_H__EBFD94D2_A970_405E_8A9D_D78AC361DC9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct _XmlFilter
{
	int  nIndex;
	char szSearceName[MAX_PATH];
	char szSearchPath[MAX_PATH];
	char szSearchType[MAX_PATH*2];
}XmlFilter,*pXmlFilter;

#include "mysqlcomm.h"
class slXmlAgent  :public mysqlcomm
{
public:
	slXmlAgent();
	virtual ~slXmlAgent();

	void LoadXML();

	int LoadDB();

	std::string GetXmlPath();

	bool Filters(char* pszFullPath);

	string GetDbNameFromPath(char* szFileName);

public:
	void Clear();

	pXmlFilter m_pxmlfilter;
	int m_nCount;

	BOOL m_bInit;
};

#endif // !defined(AFX_SLXMLAGENT_H__EBFD94D2_A970_405E_8A9D_D78AC361DC9C__INCLUDED_)
