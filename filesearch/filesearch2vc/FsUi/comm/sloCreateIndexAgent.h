// sloCreateIndexAgent.h: interface for the sloCreateIndexAgent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLOCREATEINDEXAGENT_H__15940A96_1924_4B1D_9BE0_4C4496E39144__INCLUDED_)
#define AFX_SLOCREATEINDEXAGENT_H__15940A96_1924_4B1D_9BE0_4C4496E39144__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "MySQLDB.h"
class sloCreateIndexAgent  
{
public:
	sloCreateIndexAgent();
	virtual ~sloCreateIndexAgent();
public:

	BOOL EventCreateIndex(char* pszSearchPath, char* pszFileTypes);

private:
	void BuildSearchName();
	void BuildIndexPath();

	int GetMaxIndexID();
	string ConverSqlPath(string strPath);

	bool ConnectDB();
	BOOL doSqlExe(BOOL bCombin,const char* szSQL,...);

	//disk
	void GetDrvSpaceInfo(char* pDisk);
	void FindAllDrivers();
	
public:
	char m_cMaxDriver;
	ULARGE_INTEGER m_uMaxFreeSpace;
	char m_szSearchName[MAX_PATH];	
	char m_szIndexPath[MAX_PATH];

	CMySQLDB* m_pMySqlDB;

};

#endif // !defined(AFX_SLOCREATEINDEXAGENT_H__15940A96_1924_4B1D_9BE0_4C4496E39144__INCLUDED_)
