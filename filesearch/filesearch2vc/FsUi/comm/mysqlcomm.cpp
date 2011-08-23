// mysqlcomm.cpp: implementation of the mysqlcomm class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "FsUi.h"
#include "mysqlcomm.h"
#include "sloRegAgent.h"
#include "sloCommAgent.h"

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
	memset(m_szDataSourcePath, NULL, MAX_PATH);
	memset(m_szServerIP, NULL, MAX_PATH);	
	memset(m_szUserName, NULL, MAX_PATH);
	memset(m_szPwd, NULL, MAX_PATH);
	m_nPort = 3333;
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
			//log.Print(LL_DEBUG_INFO, "[Info]CreateDB Failed!\r\n");
			return false;
		}
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////
bool mysqlcomm::ConnectDB(std::string strDBName/* = "COMMONINFO"*/)
{
	//
	if (!CreateDB())
	{
		return false;
	}

	//从配置文件中dataSource.properties获取ip和port
	GetDataSource();
	
	//connect db
	bool bRet = m_pMySqlDB->Connect(m_szServerIP, m_nPort, m_szUserName, m_szPwd, strDBName.c_str());
// 	if (bRet)
// 	{
// 		log.Print(LL_DEBUG_INFO, "[Info]Connect Db(COMMONINFO) Succ!\r\n");
// 	}else
// 		log.Print(LL_DEBUG_INFO, "[Error]Connect Db(COMMONINFO) Failed!\r\n");

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


#define  DATASOURCE_PRO_NAME "tomcat\\webapps\\slfile\\WEB-INF\\classes\\com\\web\\searchlocal\\properties\\dataSource.properties"
BOOL mysqlcomm::GetProFilePath()
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
		sprintf(m_szDataSourcePath,"%s%s%s",drive, dir,DATASOURCE_PRO_NAME);
		
		return TRUE;
	}
	
	return FALSE;
}

#define MYSQL_IP		"127.0.0.1"
#define MYSQL_PORT2		3333
#define MYSQL_USERNAME	"root"
#define MYSQL_PWD		"changsong"

#define KEY_IP			"ip"
#define KEY_PORT		"port"
#define KEY_USERNAME	"username"
#define KEY_PWD			"password"

BOOL mysqlcomm::GetDataSource()
{
	if (strlen(m_szServerIP) != 0)
	{
		//已经获取过，不在获取
		return TRUE;
	}

	//获取配置文件路径
	if(GetProFilePath() == FALSE)
	{
		//采用默认值
		strcpy(m_szServerIP, MYSQL_IP);
		m_nPort = MYSQL_PORT2;
		strcpy(m_szUserName, MYSQL_USERNAME);
		strcpy(m_szPwd, MYSQL_PWD);
		return TRUE;
	}

	//获取配置文件中的key值
	char szPort[MAX_PATH] = {0};
	sloCommAgent::GetPropertyfileString(KEY_IP, MYSQL_IP, m_szServerIP, MAX_PATH, m_szDataSourcePath);
	sloCommAgent::GetPropertyfileString(KEY_PORT, "", szPort, MAX_PATH, m_szDataSourcePath);
	sloCommAgent::GetPropertyfileString(KEY_USERNAME, MYSQL_USERNAME, m_szUserName, MAX_PATH, m_szDataSourcePath);
	sloCommAgent::GetPropertyfileString(KEY_PWD, MYSQL_PWD, m_szPwd, MAX_PATH, m_szDataSourcePath);

	if (strlen(szPort) == 0)
	{
		m_nPort = MYSQL_PORT2;
	}else
		m_nPort = atoi(szPort);

	return TRUE;
}