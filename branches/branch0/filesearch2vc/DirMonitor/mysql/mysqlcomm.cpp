// mysqlcomm.cpp: implementation of the mysqlcomm class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "FsUi.h"
#include "mysqlcomm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

mysqlcomm::mysqlcomm()
{
	m_pMySqlDB = NULL;
}

mysqlcomm::~mysqlcomm()
{
	if (m_pMySqlDB)
	{
		delete m_pMySqlDB;
		m_pMySqlDB = NULL;
	}
}

bool mysqlcomm::CreateDB()
{
	//
	if (!m_pMySqlDB)
	{
		m_pMySqlDB = new CMySQLDB();
		if (!m_pMySqlDB)
		{
			log.Print(LL_DEBUG_INFO, "[Info]CreateDB Failed!\r\n");
			return false;
		}
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////
bool mysqlcomm::ConnectDB()
{
	//
	if (!CreateDB())
	{
		return false;
	}
	
	//connect db
	bool bRet = m_pMySqlDB->Connect("127.0.0.1", 3306, "root","changsong","COMMONINFO");
	if (bRet)
	{
		log.Print(LL_DEBUG_INFO, "[Info]Connect Db(COMMONINFO) Succ!\r\n");
	}else
		log.Print(LL_DEBUG_INFO, "[Error]Connect Db(COMMONINFO) Failed!\r\n");

	return bRet;
}


BOOL mysqlcomm::doSqlExe(BOOL bCombin,const char* szSQL,...)
{
	BOOL bSucc = FALSE; 	
	try
	{	
		if(bCombin)
		{
			int pos = 0;
			char buffer[DEFAULT_SQL_CMD_SIZE] = {0 };
			va_list args;
			va_start(args, szSQL);
			pos += _vsnprintf(buffer+pos,DEFAULT_SQL_CMD_SIZE,szSQL, args);
			va_end(args);
			bSucc = m_pMySqlDB->Query(buffer,pos);
		}else
		{
			bSucc = m_pMySqlDB->Query(szSQL,strlen(szSQL));	
		}
	}
	catch (...)
	{
		OutputDebugStringA("exception in doSqlExe");
	}
	
	return bSucc;
	
}
