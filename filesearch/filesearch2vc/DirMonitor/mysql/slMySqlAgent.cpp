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
	m_pMySqlDB = NULL;
}

slMySqlAgent::~slMySqlAgent()
{
	
}

bool slMySqlAgent::LogRecord(File_Action_Log FileLog)
{
	bool bRet = true;
	do 
	{
		std::string strDbName = g_xmlFilterAgent.GetDbNameFromPath(FileLog.szSrcName);
		memcpy(FileLog.szDbName, strDbName.c_str(), strDbName.size());
		
		//
		m_pMySqlDB = new CMySQLDB();
		
		//connect db
		bool bRet = m_pMySqlDB->Connect("127.0.0.1", 3306, "root","changsong",strDbName.c_str());
		if (bRet == false)
		{
			log.Print(LL_DEBUG_INFO,"Connect Sql Failed!IP=127.0.0.1, Port=3306,DbName=%s\r\n", strDbName.c_str());
			break;
		}
		//add db
		AddRec(FileLog);

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

bool slMySqlAgent::AddRec(File_Action_Log FileLog)
{
	bool bRet = true;
	do 
	{
		//修改的记录首先检查最近有没有此记录
		//
		if (FileLog.FileActon == FILE_MODIFYED)
		{
			std::string strQuerySQL = "select max(lastmodify) as maxtime from t_changeinfo where path='%s' and operflg=1 or operflg=2";
			HRESULT hr = doSqlExe(TRUE, strQuerySQL.c_str(), ConverSqlPath(FileLog.szSrcName).c_str());
			if (FAILED(hr))
			{
				log.Print(LL_DEBUG_INFO,"Error in slMySqlAgent::AddRec,doSqlExe Failed!Sql=%s\r\n",strQuerySQL.c_str());
				bRet = false;
				break;
			}
			int nCount = m_pMySqlDB->GetRowCount();
			if(nCount >= 1)
			{	
				bRet = m_pMySqlDB->GetRow();
				if(bRet==false)
				{
					log.Print(LL_DEBUG_INFO,"Error in slMySqlAgent::AddRec,GetRow Failed!Sql=%s\r\n",strQuerySQL.c_str());
					break;
				}
				
				int nTimeLen = 0;
				char* pTime = m_pMySqlDB->GetField("maxtime",&nTimeLen);
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
		HRESULT hr = doSqlExe(TRUE, strInsertSQL.c_str(),ConverSqlPath(FileLog.szSrcName).c_str(), GetOperFlag(FileLog).c_str(),FileLog.szLogTime);
		if (FAILED(hr))
		{
			log.Print(LL_DEBUG_INFO,"Error in slMySqlAgent::AddRec,doSqlExe Failed!Sql=%s\r\n",strInsertSQL.c_str());
			bRet = false;
			break;
		}

	} while (0);

	return bRet;
}


BOOL slMySqlAgent::doSqlExe(BOOL bCombin,const char* szSQL,...)
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
		log.Print(LL_DEBUG_INFO,"Exception in slMySqlAgent::doSqlExe!\r\n");	
		bSucc = FALSE;
	}
	
	return bSucc;
	
}

