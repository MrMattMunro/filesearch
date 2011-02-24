// sloModifyIndexAgent.h: interface for the sloModifyIndexAgent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLOMODIFYINDEXAGENT_H__2143ADB2_C230_4633_B5F6_D636F280E38B__INCLUDED_)
#define AFX_SLOMODIFYINDEXAGENT_H__2143ADB2_C230_4633_B5F6_D636F280E38B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "MySQLDB.h"

typedef enum Search_Type{
	TYPE_WORD = 0,
	TYPE_EXCEL,
	TYPE_PPT,
	TYPE_PDF,
	TYPE_HTML,
	TYPE_TXT,
	TYPE_CHM
};

class sloModifyIndexAgent  : public mysqlcomm
{
public:
	sloModifyIndexAgent();
	virtual ~sloModifyIndexAgent();

	void SetIndexID(int nID);
	int GetSearchInfo();

	BOOL EventModifyIndex(char* pszFileTypes);
	BOOL EventDelIndex();
 
public:
	int m_nIndexID;
	char m_szSearchPath[MAX_PATH];
	char m_szSearchType[MAX_PATH*4];
 
};

#endif // !defined(AFX_SLOMODIFYINDEXAGENT_H__2143ADB2_C230_4633_B5F6_D636F280E38B__INCLUDED_)
