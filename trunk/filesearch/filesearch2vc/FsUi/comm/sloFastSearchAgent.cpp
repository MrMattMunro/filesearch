// sloFastSearchAgent.cpp: implementation of the sloFastSearchAgent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FsUi.h"
#include "sloFastSearchAgent.h"
#include "sloRegAgent.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

sloFastSearchAgent::sloFastSearchAgent()
{
	memset(m_szKeyPath, NULL, MAX_PATH);
	GetKeyFilePath();
}

sloFastSearchAgent::~sloFastSearchAgent()
{

}

DWORD sloFastSearchAgent::GetAllPath()
{
	//从数据库中获取最大的索引id
	if (!m_pMySqlDB && !ConnectDB())
	{
		return -1;
	}

	ClearList();
	
	std::string strQuerySQL = "select * from t_searcher order by id asc";
	HRESULT hr = doSqlExe(FALSE, strQuerySQL.c_str() );
	if (FAILED(hr))
		return -1;
	
	int nCount = m_pMySqlDB->GetRowCount();
	int nFieldCount = m_pMySqlDB->GetFieldCount();
	if(nCount >= 1 && nFieldCount >= 1)
	{	
		for (int i = 0; i < nCount; i++)
		{
			bool bSucc = m_pMySqlDB->GetRow();
			if(bSucc==false)
				return -1;
			
			int nPathLen = 0;
			char* pPath = m_pMySqlDB->GetField("path",&nPathLen);
			if(pPath != NULL && nPathLen >= 1)
			{	
				m_PathList.push_back(pPath);
			}
		}
	}
	
	return 0;	
}

DWORD sloFastSearchAgent::GetSearchRecords()
{
	//从数据库中获取最大的索引id
	if (!m_pMySqlDB && !ConnectDB())
	{
		return -1;
	}
	
	std::string strQuerySQL = "select * from t_result";
	HRESULT hr = doSqlExe(FALSE, strQuerySQL.c_str() );
	if (FAILED(hr))
		return -2;
	
	int nCount = m_pMySqlDB->GetRowCount();
	int nFieldCount = m_pMySqlDB->GetFieldCount();
	if(nCount >= 1 && nFieldCount >= 1)
	{	
		for (int i = 0; i < nCount; i++)
		{
			bool bSucc = m_pMySqlDB->GetRow();
			if(bSucc==false)
				return -1;
			
			int nFileTypeLen = 0;
			char* pFileType = m_pMySqlDB->GetField("filetype",&nFileTypeLen);
			if (nFileTypeLen == 0)
				continue ;

			int nFileNameLen = 0;
			char* pFileName = m_pMySqlDB->GetField("filename",&nFileNameLen);

			int nFilePathLen = 0;
			char* pFilePath = m_pMySqlDB->GetField("filepath",&nFilePathLen);
			
			int nDespLen = 0;
			char* pDesp = m_pMySqlDB->GetField("desp",&nDespLen);

			int nContentLen = 0;
			char* pContent = m_pMySqlDB->GetField("content",&nContentLen);

			SearchRectord sr;
			memset(&sr, NULL, sizeof(SearchRectord));
			if (nFileTypeLen)
				memcpy(sr.szFileType, pFileType, nFileTypeLen);
			if (nFileNameLen)
				memcpy(sr.szFileName, pFileName, nFileNameLen);
			if (nFilePathLen)
				memcpy(sr.szFilePath, pFilePath, nFilePathLen);

			if (nDespLen)
				memcpy(sr.szDesp, pDesp, nDespLen);
			if (nContentLen)
				memcpy(sr.szContent, pContent, nContentLen);

			m_RecList.push_back(sr);

		}
	}
	
	return 0;	
}

BOOL sloFastSearchAgent::IsKeyFileExist()
{
	if(strlen(m_szKeyPath) == 0)
		return FALSE;

	return sloCommAgent::IsFileExists(m_szKeyPath);
}

#define  KEY_PRO_NAME "tomcat\\webapps\\slfile\\WEB-INF\\classes\\com\\searchlocal\\properties\\keyWord.properties"
BOOL sloFastSearchAgent::GetKeyFilePath()
{
	char szFileExePath[MAX_PATH] = {0};
	sloRegAgent reg;
	if(reg.ReadInstallPath(szFileExePath))
	{  
		char drive[_MAX_DRIVE];
		char dir[_MAX_DIR];
		char fname[_MAX_FNAME];
		char ext[_MAX_EXT];
		
		_splitpath( szFileExePath, drive, dir, fname, ext );
		sprintf(m_szKeyPath,"%s%s%s",drive, dir,KEY_PRO_NAME);
	}
	
	return FALSE;
}

void sloFastSearchAgent::ClearList()
{
	m_RecList.clear();
}