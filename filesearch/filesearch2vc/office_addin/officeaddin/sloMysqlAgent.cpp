// sloMysqlAgent.cpp: implementation of the sloMysqlAgent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "officeaddin.h"
#include "sloMysqlAgent.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

sloMysqlAgent* sloMysqlAgent::m_hinstance = NULL;
sloMysqlAgent::sloMysqlAgent()
{

}

sloMysqlAgent::~sloMysqlAgent()
{

}

sloMysqlAgent* sloMysqlAgent::GetInstance()
{
	if (m_hinstance == NULL)
	{
		m_hinstance = new sloMysqlAgent();
		
	}
	
	return m_hinstance;
}


BOOL sloMysqlAgent::AddDoucmentRecord(DocumentItem docitem)
{
	BOOL bRet = TRUE;
	//从数据库中获取最大的索引id
	if (!m_pMySqlDB && !ConnectDB())
	{
		return FALSE;
	}
	
	//插入数据库
	std::string strQuerySQL = "insert into t_doument(uuid,title, location, name, keywords,type,\
		url, author,owner, createdate, modifieddate,accesseddate,syncflg, protectflg,operflg, document_read_cout\
		) values('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s',%d)";
	HRESULT hr = doSqlExe(TRUE, strQuerySQL.c_str(), docitem.szuuid, "",docitem.szname, "", docitem.sztype, "", \
		docitem.szauthor, docitem.szowner, docitem.szcreatedate, docitem.szmodifieddate, docitem.szaccesseddate, \
		docitem.syncflg, docitem.protectflg, docitem.operflg, docitem.nreadcout);

	if (FAILED(hr))
		bRet = FALSE;	
	
	return bRet;
	
}