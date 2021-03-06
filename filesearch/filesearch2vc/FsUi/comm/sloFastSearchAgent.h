// sloFastSearchAgent.h: interface for the sloFastSearchAgent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLOFASTSEARCHAGENT_H__13990F01_AA07_4061_B201_65500F812FBC__INCLUDED_)
#define AFX_SLOFASTSEARCHAGENT_H__13990F01_AA07_4061_B201_65500F812FBC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "sloFilterAgent.h"

class sloFastSearchAgent  :public mysqlcomm
{
public:
	sloFastSearchAgent();
	virtual ~sloFastSearchAgent();

	DWORD GetAllPath();
	BOOL IsKeyFileExist();

	DWORD GetSearchRecords();
	DWORD GetSearchRecords_Recent(int nDays);

	int GetPathIndex(char* szPath);

	std::string GetFilePathFromName(char* szName);
private:
	DWORD SearchRecords(std::string strQuerySQL, BOOL bRecent = FALSE);

	BOOL GetKeyFilePath();
	void AddList(SearchRectord sr);

	void ClearPathList();
	void ClearRecList();
public:
	std::vector<PathIndex> m_PathList;
	std::vector<SearchRectord> m_RecList; 

	char m_szKeyPath[MAX_PATH];

	sloFilterAgent m_filterAgent;
};

#endif // !defined(AFX_SLOFASTSEARCHAGENT_H__13990F01_AA07_4061_B201_65500F812FBC__INCLUDED_)
