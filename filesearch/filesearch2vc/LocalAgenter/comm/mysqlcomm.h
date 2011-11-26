// mysqlcomm.h: interface for the mysqlcomm class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSQLCOMM_H__21CAE79B_F59B_49D0_A0B5_53B487CA3DC0__INCLUDED_)
#define AFX_MYSQLCOMM_H__21CAE79B_F59B_49D0_A0B5_53B487CA3DC0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "MySQLDB.h"

class mysqlcomm  
{
public:
	mysqlcomm();
	virtual ~mysqlcomm();

	bool CreateDB();
	bool ConnectDB(std::string strDBName = "COMMONINFO");
	BOOL doSqlExe(BOOL bCombin,const char* szSQL,...);

private:
	BOOL GetProFilePath();
	BOOL GetDataSource();
public:
	CMySQLDB* m_pMySqlDB;

	char m_szDataSourcePath[MAX_PATH];
	char m_szServerIP[MAX_PATH];
	int  m_nPort;
	char m_szUserName[MAX_PATH];
	char m_szPwd[MAX_PATH];
};

#endif // !defined(AFX_MYSQLCOMM_H__21CAE79B_F59B_49D0_A0B5_53B487CA3DC0__INCLUDED_)
