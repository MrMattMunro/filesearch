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

	ClearPathList();
	
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
				int nIDLen = 0;
				char* pID = m_pMySqlDB->GetField("id",&nIDLen);
				if(pID != NULL && nIDLen >= 1)
				{	
					PathIndex path;
					memset(&path, NULL, sizeof(PathIndex));
					path.nID = atoi(pID);
					strcpy(path.szPath, pPath);

					m_PathList.push_back(path);
				}
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

	ClearRecList();	

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

			//先查找是否有该项
			SearchRectord sr;
			memset(&sr, NULL, sizeof(SearchRectord));
			if (nFileTypeLen)
				memcpy(sr.szFileType, pFileType, nFileTypeLen);
			if (nFileNameLen)
				memcpy(sr.szFileName, pFileName, nFileNameLen);
			if (nFilePathLen)
				memcpy(sr.szFilePath, pFilePath, nFilePathLen);

			if (nDespLen)
				sr.DespList.push_back(pDesp);

			if (nContentLen)
				memcpy(sr.szContent, pContent, nContentLen);

			//m_RecList.push_back(sr);
			AddList(sr);

		}
	}
	
	return 0;	
}

void sloFastSearchAgent::AddList(SearchRectord sr)
{
	int nCount = m_RecList.size();
	for (int i = 0; i < nCount; i++)
	{
		if (strcmp(sr.szFileName, m_RecList[i].szFileName) == 0)
		{
			break ;
		}
	}	

	if (i >= nCount)
	{
		m_RecList.push_back(sr);
	}else
		m_RecList[i].DespList.push_back(sr.DespList[0]);
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

void sloFastSearchAgent::ClearPathList()
{
	m_PathList.clear();
}


void sloFastSearchAgent::ClearRecList()
{
	m_RecList.clear();
}

int sloFastSearchAgent::GetPathIndex(char* szPath)
{
	if (strcmp(szPath, "全部") == 0)
	{
		return 0;
	}

	int nCount = m_PathList.size();
	for (int i = 0; i < nCount; i++)
	{
		PathIndex index = m_PathList[i];
		if (strcmp(szPath, index.szPath) == 0)
		{
			return index.nID;
		}
	}

	return -1;
}