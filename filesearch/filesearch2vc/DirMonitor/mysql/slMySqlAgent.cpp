// slMySqlAgent.cpp: implementation of the slMySqlAgent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "slMySqlAgent.h"
#include "slXmlAgent.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern slXmlAgent g_xmlFilterAgent;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

slMySqlAgent::slMySqlAgent()
{

}

slMySqlAgent::~slMySqlAgent()
{
	ReleassObjectsDB();	
}

bool slMySqlAgent::LogRecord(File_Action_Log FileLog)
{
	bool bRet = true;
	do 
	{
		std::string strDbName = g_xmlFilterAgent.GetDbNameFromPath(FileLog.szSrcName);
		memcpy(FileLog.szDbName, strDbName.c_str(), strDbName.size());
		
		if (strDbName == DEFAULT_DB_NAME)
		{
			//非索引目录下的文件记录，插入一条记录
			bRet = LogRecordDB(strDbName, FileLog);
		}else
		{
			//索引目录下的文件记录，插入两条记录
			bRet = LogRecordDB(strDbName, FileLog);
			bRet = LogRecordDB(DEFAULT_DB_NAME, FileLog);
		}

	} while (0);

	return bRet;
}


bool slMySqlAgent::LogRecordDB(std::string strDbName, File_Action_Log FileLog)
{
	bool bRet = true;
	do 
	{	
		//建立索引，每种连接对应一个DB数据库，保证数据库的连接数与索引数目一致	
		CMySQLDB* pMySqlDB = GetObjectDB(strDbName);
		if (pMySqlDB->m_strDB.size() ==0 )
		{
			//未连接，进行首次连接
			//connect db
			bool bRet = pMySqlDB->Connect("127.0.0.1", 3306, "root","changsong",strDbName.c_str());
			if (bRet == false)
			{
				log.Print(LL_DEBUG_INFO,"Connect Sql Failed!IP=127.0.0.1, Port=3306,DbName=%s\r\n", strDbName.c_str());
				break;
			}
		}
		
		//add db
		if (strDbName == DEFAULT_DB_NAME)
		{	
			bRet = AddRecentRec(pMySqlDB, FileLog, TRUE);
		}else
			bRet = AddRecentRec(pMySqlDB, FileLog, FALSE);	
	} while (0);
	
	return bRet;
}


CMySQLDB* slMySqlAgent::GetObjectDB(std::string strSearchName)
{
	CMySQLDB* pMySqlDB = NULL;
	int nSize = m_DbPools.size();
	for (int i = 0; i < nSize; i++)
	{
		DbPools dbItem = m_DbPools[i];
		if (strSearchName == dbItem.strDBName)
		{
			pMySqlDB = dbItem.pSqlDB;
			break;
		}
	}

	if (!pMySqlDB)
	{
		DbPools dbItem;
		dbItem.strDBName = strSearchName;
		dbItem.pSqlDB = new CMySQLDB();
		pMySqlDB = dbItem.pSqlDB;
		m_DbPools.push_back(dbItem);
	}

	return pMySqlDB;

}

void slMySqlAgent::ReleassObjectsDB()
{
	for (std::vector<DbPools>::iterator item = m_DbPools.begin(); item != m_DbPools.end();)
	{
		DbPools dbItem = *item;
		if (dbItem.pSqlDB)
		{
			delete dbItem.pSqlDB;
			dbItem.pSqlDB = NULL;
		}
		m_DbPools.erase(item);
	}
}

//向数据库中插入一条记录，同一文件修改记录可插入多次
bool slMySqlAgent::AddRec(CMySQLDB* pMySqlDB, File_Action_Log FileLog)
{
	bool bRet = true;
	do 
	{
		//修改的记录首先检查最近有没有此记录
		//
		if (FileLog.FileActon == FILE_MODIFYED)
		{
			std::string strQuerySQL = "select max(lastmodify) as maxtime from t_changeinfo where path='%s' and operflg=1 or operflg=2";
			HRESULT hr = pMySqlDB->Query(strQuerySQL.c_str(), ConverSqlPath(FileLog.szSrcName).c_str());
			if (FAILED(hr))
			{
				log.Print(LL_DEBUG_INFO,"Error in slMySqlAgent::AddRec,doSqlExe Failed!Sql=%s\r\n",strQuerySQL.c_str());
				bRet = false;
				break;
			}
			int nCount = pMySqlDB->GetRowCount();
			if(nCount >= 1)
			{	
				bRet = pMySqlDB->GetRow();
				if(bRet==false)
				{
					log.Print(LL_DEBUG_INFO,"Error in slMySqlAgent::AddRec,GetRow Failed!Sql=%s\r\n",strQuerySQL.c_str());
					break;
				}
				
				int nTimeLen = 0;
				char* pTime = pMySqlDB->GetField("maxtime",&nTimeLen);
				if(pTime!=NULL && nTimeLen > 1)
				{	
					std::string strTime(pTime,nTimeLen);
					if (strcmp(pTime, FileLog.szLogTime) == 0)
					{
						bRet = false;
						break;
					}
				}
			}
		}
		
		std::string strInsertSQL = "insert into t_changeinfo(path,operflg,hasoper,lastmodify) values('%s','%s','0','%s')";
		HRESULT hr = pMySqlDB->Query(strInsertSQL.c_str(),ConverSqlPath(FileLog.szSrcName).c_str(), GetOperFlag(FileLog).c_str(),FileLog.szLogTime);
		if (FAILED(hr))
		{
			log.Print(LL_DEBUG_INFO,"Error in slMySqlAgent::AddRec,doSqlExe Failed!Sql=%s\r\n",strInsertSQL.c_str());
			bRet = false;
			break;
		}

		log.Print(LL_DEBUG_INFO,"insert new record!path=%s, operflg=%s\r\n",FileLog.szSrcName,GetOperFlag(FileLog).c_str());

	} while (0);

	return bRet;
}


//根据文件名获取文件最后访问时间
std::string GetFileLastModifyTime(char* szFileName, std::string strDefaultValue)
{
	std::string strDateTime;
	do 
	{
		try
		{
			WIN32_FIND_DATA ffd ;
			HANDLE hFind = FindFirstFile(szFileName,&ffd);
			if (hFind == INVALID_HANDLE_VALUE)
			{
				strDateTime = strDefaultValue;
				break;
			}
			SYSTEMTIME stUTC, stLocal;
			FileTimeToSystemTime(&(ffd.ftLastWriteTime), &stUTC);
			SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal); //正在打开的文档报异常
				
			char szDateTime[MAX_PATH] = {0};
			sprintf(szDateTime,"%04d-%02d-%02d %02d:%02d:%02d",
				stLocal.wYear, stLocal.wMonth, stLocal.wDay, stLocal.wHour, stLocal.wMinute, stLocal.wSecond);
			strDateTime = szDateTime;
		}
		catch (...)
		{
			strDateTime = strDefaultValue;
		}
	} while (0);

	return strDateTime;
}

//向数据库中插入一条记录，同一文件修改记录只插入一条
bool slMySqlAgent::AddRecentRec(CMySQLDB* pMySqlDB, File_Action_Log FileLog, BOOL bRecentRec)
{
	bool bRet = true;
	do 
	{
		//修改的记录首先检查最近有没有此记录
		//
		if (FileLog.FileActon == FILE_MODIFYED)
		{
			//查找一天之内，该文件是否有修改记录
			//select * from t_changeinfo where path='%s' and operflg=1 or operflg=2 and lastmodify between current_date() And date_add(current_date(), interval 1 day) 
			std::string strQuerySQL ;
			if (bRecentRec)
			{
				strQuerySQL = "select * from t_recent_changeinfo where path='%s' and operflg=2 and systime between current_date() And date_add(current_date(), interval 1 day)";
			}else
				strQuerySQL = "select * from t_changeinfo where path='%s' and operflg=2 and lastmodify between current_date() And date_add(current_date(), interval 1 day)";

			HRESULT hr = pMySqlDB->Query(strQuerySQL.c_str(), ConverSqlPath(FileLog.szSrcName).c_str());
			if (FAILED(hr))
			{
				log.Print(LL_DEBUG_INFO,"Error in slMySqlAgent::AddRec,doSqlExe Failed!Sql=%s\r\n",strQuerySQL.c_str());
				bRet = false;
				break;
			}
			int nCount = pMySqlDB->GetRowCount();
			if(nCount >= 1)
			{	
				bRet = pMySqlDB->GetRow();
				if(bRet==false)
				{
					log.Print(LL_DEBUG_INFO,"Error in slMySqlAgent::AddRec,GetRow Failed!Sql=%s\r\n",strQuerySQL.c_str());
					break;
				}
				
				int nPathLen = 0;
				char* pPath = pMySqlDB->GetField("path",&nPathLen);
				if(pPath!=NULL && nPathLen > 1)
				{	
					//一天之内存在此记录，则不记录
					log.Print(LL_DEBUG_INFO,"[Info]Exist in the day!\r\n");
					break;
				}
			}else
				log.Print(LL_DEBUG_INFO,"[Info]Not Exist this record in the day!\r\n");
		}
		
		//根据文件名获取文件最后修改时间
		std::string strInsertSQL;
		HRESULT hr;
		if (bRecentRec)
		{
			strInsertSQL = "insert into t_recent_changeinfo(path,operflg,hasoper,systime,lastmodify) values('%s','%s','0','%s','%s')";
			hr = pMySqlDB->Query(strInsertSQL.c_str(),ConverSqlPath(FileLog.szSrcName).c_str(), GetOperFlag(FileLog).c_str(),FileLog.szLogTime, GetFileLastModifyTime(FileLog.szSrcName, FileLog.szLogTime).c_str());
		}else{
			strInsertSQL = "insert into t_changeinfo(path,operflg,hasoper,lastmodify) values('%s','%s','0','%s')";
			hr = pMySqlDB->Query(strInsertSQL.c_str(),ConverSqlPath(FileLog.szSrcName).c_str(), GetOperFlag(FileLog).c_str(), GetFileLastModifyTime(FileLog.szSrcName, FileLog.szLogTime).c_str());
		}	

		if (FAILED(hr))
		{
			log.Print(LL_DEBUG_INFO,"Error in slMySqlAgent::AddRec,doSqlExe Failed!Sql=%s\r\n",strInsertSQL.c_str());
			bRet = false;
			break;
		}
		
		log.Print(LL_DEBUG_INFO,"insert new record!path=%s, operflg=%s\r\n",FileLog.szSrcName,GetOperFlag(FileLog).c_str());
		
	} while (0);
	
	return bRet;
}

string slMySqlAgent::GetOperFlag(File_Action_Log FileLog)
{
	std::string strOperFlag = "0";
	switch(FileLog.FileActon)
	{
	case FILE_ADD:
		strOperFlag = "1";
		break;
	case FILE_MODIFYED:
		strOperFlag = "2";
		break;
	case FILE_REMOVED:
		strOperFlag = "3";
		break;
	case FILE_NAMECHANGE:
		strOperFlag = "4";
		break;		
	default:
		break;
	}
	
	return strOperFlag;
}

string slMySqlAgent::ConverSqlPath(string strPath)
{
	std::string strData = strPath;
	std::string strTmp = strData;
	
	int nPos1 = 0;
	int nPos2 = strTmp.find_first_of('\\');	
	while(nPos2 != -1)
	{
		strData.insert(nPos1 + nPos2,"\\");
		strTmp.erase(0,nPos2+1);
		nPos1 += nPos2+2;
		nPos2 = strTmp.find_first_of('\\');	
	}
	
	return strData;
}