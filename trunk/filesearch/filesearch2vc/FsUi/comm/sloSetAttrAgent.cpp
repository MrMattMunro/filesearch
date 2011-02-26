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

#define  FILEOPENER_PRO_NAME "tomcat\\webapps\\slfile\\WEB-INF\\classes\\com\\searchlocal\\properties\\fileopener.properties"
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
	}
	
	return FALSE;
}
