// sloModifyIndexAgent.cpp: implementation of the sloModifyIndexAgent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "FsUiTest.h"
#include "sloModifyIndexAgent.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

sloModifyIndexAgent::sloModifyIndexAgent()
{
	m_nIndexID = 0;
	memset(m_szSearchPath, NULL, MAX_PATH);
	memset(m_szSearchType, NULL, MAX_PATH*4);
	m_pMySqlDB = NULL;
}

sloModifyIndexAgent::~sloModifyIndexAgent()
{
	if (m_pMySqlDB)
	{
		delete m_pMySqlDB;
		m_pMySqlDB = NULL;
	}
}

void sloModifyIndexAgent::SetIndexID(int nID)
{
	m_nIndexID = nID;
}

int sloModifyIndexAgent::GetSearchInfo()
{
	//从数据库中获取最大的索引id
	if (!m_pMySqlDB && !ConnectDB())
	{
		return -1;
	}
	
	std::string strQuerySQL = "select * from t_searcher where id=%d";
	HRESULT hr = doSqlExe(TRUE, strQuerySQL.c_str(), m_nIndexID);
	if (FAILED(hr))
		return -1;
	
	int nCount = m_pMySqlDB->GetRowCount();
	int nFieldCount = m_pMySqlDB->GetFieldCount();
	if(nCount >= 1 && nFieldCount >= 1)
	{	
		bool bSucc = m_pMySqlDB->GetRow();
		if(bSucc==false)
			return -1;
		
		int nPathLen = 0;
		char* pPath = m_pMySqlDB->GetField("path",&nPathLen);
		if(pPath != NULL && nPathLen >= 1)
		{	
			strcpy(m_szSearchPath, pPath);
		}

		int nTypeLen = 0;
		char* pType = m_pMySqlDB->GetField("filetype",&nTypeLen);
		if(pType != NULL && nTypeLen >= 1)
		{	
			strcpy(m_szSearchType, pType);
		}
	}
	
	return 0;
}

//////////////////////////////////////////////////////////////////////////
bool sloModifyIndexAgent::ConnectDB()
{
	//
	m_pMySqlDB = new CMySQLDB();
	
	//connect db
	return m_pMySqlDB->Connect("127.0.0.1", 3306, "root","changsong","COMMONINFO");
}


BOOL sloModifyIndexAgent::doSqlExe(BOOL bCombin,const char* szSQL,...)
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