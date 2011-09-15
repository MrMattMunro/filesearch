// sloSetAttrAgent.cpp: implementation of the sloSetAttrAgent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FsUi.h"
#include "sloSetAttrAgent.h"
#include "sloRegAgent.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

sloSetAttrAgent::sloSetAttrAgent()
{

}

sloSetAttrAgent::~sloSetAttrAgent()
{

}

int sloSetAttrAgent::GetSoftPath(char* szFileType, char* szPath)
{
	BOOL bSucc = FALSE;
	//从数据库中获取最大的索引id
	if (!m_pMySqlDB && !ConnectDB())
	{
		return -1;
	}
	
	std::string strQuerySQL = "select * from t_fileopener where filetype='%s'";
	HRESULT hr = doSqlExe(TRUE, strQuerySQL.c_str(), szFileType);
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
		char* pPath = m_pMySqlDB->GetField("exepath",&nPathLen);
		if(pPath != NULL && nPathLen >= 1)
		{	
			strcpy(szPath, pPath);
		}
	}
	
	return 0;
}

BOOL sloSetAttrAgent::UpdateSoftPath(char* szFileType, char* szPath)
{
	BOOL bRet = FALSE;

	do 
	{
		//连接数据库
		if (!m_pMySqlDB && !ConnectDB())
			break ;
		
		//如果数据库中没有该条记录，则插入新记录
		std::string strQuerySQL = "select * from t_fileopener where filetype='%s'";	
		HRESULT hr = doSqlExe(TRUE, strQuerySQL.c_str(), szFileType);
		if (FAILED(hr))
		{
			bRet = FALSE;
			break;
		}
		
		int nCount = m_pMySqlDB->GetRowCount();
		int nFieldCount = m_pMySqlDB->GetFieldCount();
		if(nCount >= 1 && nFieldCount >= 1)
		{	
			//如果数据库中有该条记录，则更新此记录
			strQuerySQL = "update t_fileopener set exepath='%s',lastmodify='%s' where filetype='%s'";
			HRESULT hr = doSqlExe(TRUE, strQuerySQL.c_str(),sloCommAgent::ConverSqlPath(szPath).c_str(), sloCommAgent::GetCurTime(),szFileType);
			if (FAILED(hr))
			{
				bRet = FALSE;
				break;
			}		
		}else
		{
			//插入记录
			strQuerySQL = "insert into t_fileopener(filetype,exepath, lastmodify) values('%s', '%s', '%s')";
			HRESULT hr = doSqlExe(TRUE, strQuerySQL.c_str(),szFileType,sloCommAgent::ConverSqlPath(szPath).c_str(), sloCommAgent::GetCurTime());
			if (FAILED(hr))
			{
				bRet = FALSE;
				break;
			}	
		}

		bRet = TRUE;

	} while (0);

	return bRet;
}

#define  FILEOPENER_PRO_NAME "tomcat\\webapps\\slfile\\WEB-INF\\classes\\com\\web\\searchlocal\\properties\\fileopener.properties"
BOOL sloSetAttrAgent::GetProFilePath()
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
		sprintf(m_szpropertiesPath,"%s%s%s",drive, dir,FILEOPENER_PRO_NAME);
		return TRUE;
	}
	
	return FALSE;
}


BOOL sloSetAttrAgent::EventSetAttr()
{
	//update db
	return TRUE;
}