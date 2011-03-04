// sloFastSearchAgent.h: interface for the sloFastSearchAgent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLOFASTSEARCHAGENT_H__13990F01_AA07_4061_B201_65500F812FBC__INCLUDED_)
#define AFX_SLOFASTSEARCHAGENT_H__13990F01_AA07_4061_B201_65500F812FBC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct _SearchRectord
{
	char szFileType[20];
	char szFileName[MAX_PATH];
	char szFilePath[MAX_PATH];
	char szDesp[1000];
	char szContent[1000];
}SearchRectord, *pSearchRectord;

class sloFastSearchAgent  :public mysqlcomm
{
public:
	sloFastSearchAgent();
	virtual ~sloFastSearchAgent();

	DWORD GetAllPath();
	BOOL IsKeyFileExist();

	DWORD GetSearchRecords();
private:
	BOOL GetKeyFilePath();

	void ClearList();

public:
	std::vector<string> m_PathList;
	std::vector<SearchRectord> m_RecList; 

	char m_szKeyPath[MAX_PATH];

};

#endif // !defined(AFX_SLOFASTSEARCHAGENT_H__13990F01_AA07_4061_B201_65500F812FBC__INCLUDED_)
