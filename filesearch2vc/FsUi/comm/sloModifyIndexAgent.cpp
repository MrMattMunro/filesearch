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
 
}

sloModifyIndexAgent::~sloModifyIndexAgent()
{

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


//update t_searcher set filetype='%s',hasupdate='0',lastmodify='%s' where id=%d
BOOL sloModifyIndexAgent::EventModifyIndex(char* pszFileTypes)
{
	BOOL bRet = TRUE;
	std::string strQuerySQL = "update t_searcher set modifyfiletype='%s',hasupdate='0',lastmodify='%s' where id=%d";
	HRESULT hr = doSqlExe(TRUE, strQuerySQL.c_str(),pszFileTypes, sloCommAgent::GetCurTime(),m_nIndexID);
	if (FAILED(hr))
		bRet = FALSE;
	
	return bRet;	
}

//update t_searcher set hasdel='1',lastmodify='%s' where id=%d
BOOL sloModifyIndexAgent::EventDelIndex()
{
	BOOL bRet = TRUE;
	std::string strQuerySQL = "update t_searcher set hasdel='1',lastmodify='%s' where id=%d";
	HRESULT hr = doSqlExe(TRUE, strQuerySQL.c_str(), sloCommAgent::GetCurTime(),m_nIndexID);
	if (FAILED(hr))
		bRet = FALSE;
	
	return bRet;	
}
