// MySQLDB.cpp: implementation of the CMySQLDB class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MySQLDB.h"
#include <stdio.h>
// #include "log.h"
// extern Log log;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMySQLDB::CMySQLDB()
{
	m_handle = NULL;
	m_res = NULL;
}

CMySQLDB::~CMySQLDB()
{
	
	Close();
}

bool CMySQLDB::Connect(const char *host, int port,const char *name,const char *pwd,const char *db)
{
	Close();
	m_handle = mysql_init(NULL);
	if (m_handle==NULL) return false;
	if (port == 0) port = MYSQL_PORT;
	//add code by prevent the error [MySQL Server is gong awary]
	mysql_options(m_handle, MYSQL_OPT_RECONNECT, "1");

	if (mysql_real_connect(m_handle, host, name, pwd, NULL, port, NULL, 0) == NULL)
	{
		ShowError();
		return false;
	}
	if (mysql_select_db(m_handle, db) != 0) 
	{
		ShowError();
		return false;
	}
	if(mysql_set_character_set(m_handle,"gbk"))
	{
		ShowError();
		return false;
	}
	
	m_strHost = host;
	m_nPort = port;
	m_strUser = name;
	m_strPwd = pwd;
	m_strDB = db;

	return true;
}

void CMySQLDB::Close()
{
	if (m_handle)
	{
		mysql_close(m_handle);
		m_handle = NULL;
	}
	if (m_res)
	{
		mysql_free_result(m_res);
		m_res = NULL;
	}
}

bool CMySQLDB::CallProc(const char* sCallProc,int len1,const char* sParamSql,int len2)
{
	if (!m_handle) return false;
	if (len1 == 0) len1 = strlen(sCallProc);	
	if (len2 == 0) len2 = strlen(sParamSql);
	if (mysql_real_query(m_handle, sCallProc, len1) != 0) 
	{
		ShowError();
		return false;
	}		

	if(sParamSql!=NULL)
	{
		if(mysql_query(m_handle,sParamSql)!=0)
		{
			ShowError();
			return false;
		}
	}
 
	if (m_res != NULL) mysql_free_result(m_res);
	m_res = mysql_store_result(m_handle);
	if (m_res != NULL)
	{
		m_fieldCnt = mysql_num_fields(m_res);
		m_fields = mysql_fetch_fields(m_res);
	}
	return true;
}

bool CMySQLDB::Query(const char *sql,int len)
{
	if (!m_handle) return false;
	if (len == 0) len = strlen(sql);
	if (mysql_real_query(m_handle, sql, len) != 0) 
	{
		ShowError();
		return false;
	}

	if (m_res != NULL) mysql_free_result(m_res);
	m_res = mysql_store_result(m_handle);
	if (m_res != NULL)
	{
		m_fieldCnt = mysql_num_fields(m_res);
		m_fields = mysql_fetch_fields(m_res);
	}
	return true;
}
bool CMySQLDB::Query(const char *format,...)
{
	int pos = 0;
	va_list args;
	va_start(args, format);
	pos += _vsnprintf(m_strCMD+pos,DEFAULT_SQL_CMD_SIZE,format, args);
	va_end(args);
	return Query(m_strCMD, pos);
}


int CMySQLDB::GetFieldCount()
{
	return m_fieldCnt;
}

int CMySQLDB::GetRowCount()
{
	return (int)mysql_num_rows(m_res);
}

void CMySQLDB::ShowError()
{
	char errMsg[512];
	memset(errMsg,0,sizeof(errMsg));
	if(mysql_errno(m_handle))  //  
	{
		sprintf(errMsg,"SQL EER = [%s]", mysql_error(m_handle));
	}

	OutputDebugString(errMsg);
//	log.Print(LL_DBERR, "SQL EER = [%s]", mysql_error(m_handle));
}

bool CMySQLDB::GetRow()
{
	m_row = mysql_fetch_row(m_res);
	if (m_row == NULL) return false;
	return true;
}

char *CMySQLDB::GetField(char *fname, int *pnLen)
{
	int i;
	unsigned long *lengths;
	lengths = mysql_fetch_lengths(m_res);
	for(i = 0; i < m_fieldCnt; i++)
	{
		if (strcmp(fname,m_fields[i].name)==0)
		{
			if(pnLen) *pnLen = lengths[i];
			return m_row[i];
		}
	}
	return NULL;
}

//-------------------------------------
// Get Field Name , Data Type And Value
//-------------------------------------
bool CMySQLDB::GetField(int idx,char *field,int *type,char **value)
{
	if(idx<0 || idx>m_fieldCnt)
		return false;
	strcpy(field,m_fields[idx].name);
	*type = m_fields[idx].type;
	*value = m_row[idx];
	return true;
}

//------------------------
// Get Field Name And Type
//------------------------
int CMySQLDB::GetFieldInfo(int nIdx, char *pszName)
{
	if(nIdx<0 || nIdx>=m_fieldCnt)
    {
        return 0;
    }
	if(pszName)
    {
        strcpy(pszName, m_fields[nIdx].name);
    }
	return m_fields[nIdx].type;
}

//------------------------------
// Get Field Data Type And Value
//------------------------------
bool CMySQLDB::GetFieldContent(int nIdx , int *pnType , char **ppValue)
{
	if(nIdx<0 || nIdx>=m_fieldCnt)
    {
        return false;
    }
	*pnType  = m_fields[nIdx].type;
	*ppValue = m_row[nIdx];
    return true;
}

unsigned long CMySQLDB::GetInsertId()
{
	return (unsigned long)mysql_insert_id(m_handle);
}

long CMySQLDB::GetAffectedRows()
{
	return (unsigned long)mysql_affected_rows(m_handle);
}

void CMySQLDB::SetManager(AbstractObjectManager *manager)
{

}

CMySQLDB* CMySQLDB::Clone()
{
	CMySQLDB* pDB = new CMySQLDB();
	pDB->Connect(m_strHost.c_str(),m_nPort,m_strUser.c_str(),m_strPwd.c_str(),m_strDB.c_str());	

	return pDB;
}

BOOL CMySQLDB::Ping()
{
	if(m_handle==NULL)
		return FALSE;
	
	//Zero if the connection to the server is alive Non-Zero if an error occurred
	if(mysql_ping(m_handle) != 0)
	{
		return FALSE;
	}

	return TRUE;

}

void CMySQLDB::GetLastError(char *pErrBuf, int nSize)
{
	if(m_handle==NULL)
		return;

	if(mysql_errno(m_handle))  //  
	{
		sprintf(pErrBuf,"SQL EER = [%s]", mysql_error(m_handle));
	}

}

