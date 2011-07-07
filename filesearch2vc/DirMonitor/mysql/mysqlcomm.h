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
	bool ConnectDB();
	BOOL doSqlExe(BOOL bCombin,const char* szSQL,...);
public:
	CMySQLDB* m_pMySqlDB;
};

#endif // !defined(AFX_MYSQLCOMM_H__21CAE79B_F59B_49D0_A0B5_53B487CA3DC0__INCLUDED_)
