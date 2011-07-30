// slXmlAgent.h: interface for the slXmlAgent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLXMLAGENT_H__EBFD94D2_A970_405E_8A9D_D78AC361DC9C__INCLUDED_)
#define AFX_SLXMLAGENT_H__EBFD94D2_A970_405E_8A9D_D78AC361DC9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "mysqlcomm.h"
#include "sloFilterAgent.h"
#include "FilterAgent.h"

class slXmlAgent  :public mysqlcomm, public CFilterAgent
{
public:
	slXmlAgent();
	virtual ~slXmlAgent();

	void LoadXML();

	int LoadDB();

	std::string GetXmlPath();

	bool Filters(char* pszFullPath, BOOL bAdd = FALSE);

	string GetDbNameFromPath(char* szFileName);

public:
	void Clear();

	pXmlFilter m_pxmlfilter;
	std::vector<XmlFilter> m_searcherList;
	int m_nCount;

	BOOL m_bInit;

	sloFilterAgent m_filterAgent;
};

#endif // !defined(AFX_SLXMLAGENT_H__EBFD94D2_A970_405E_8A9D_D78AC361DC9C__INCLUDED_)
