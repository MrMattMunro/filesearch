// MySQLDB.h: interface for the CMySQLDB class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSQLDB_H__9B453EFB_2CB7_4A88_96BB_9C9E0108BB84__INCLUDED_)
#define AFX_MYSQLDB_H__9B453EFB_2CB7_4A88_96BB_9C9E0108BB84__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



#define DEFAULT_SQL_CMD_SIZE	1024
#include <mysql.h>
#include <string>

#pragma comment(lib, "libmysql.lib")

class AbstractObjectManager;
class CMySQLDB  
{
public:
	CMySQLDB();
	virtual ~CMySQLDB();

	
public:
	CMySQLDB* Clone();
	void SetManager(AbstractObjectManager * manager);
	unsigned long GetInsertId();
	long  GetAffectedRows();
	bool  Query(const char *sql,int len=0);
	bool  Query(const char *format,...);
	bool  Connect(const char *host,int port,const char *name,const char *pwd,const char *db);
	void  Close();
	int   GetFieldCount();
	bool  GetField(int idx,char *field,int *type,char **value);
	bool  GetFieldContent(int nIdx , int *pnType , char **ppValue);
	int   GetFieldInfo(int nIdx, char *pszName);
	char *GetField(char *fname,int *len = NULL);
    int   GetRowCount();
    bool  GetRow();
	
	void  ShowError();

	bool CallProc(const char* sCallProc,int len1,const char* sParamSql,int len2);
protected:
	MYSQL		*m_handle;
	MYSQL_RES	*m_res;
	MYSQL_ROW	 m_row;
	MYSQL_FIELD *m_fields;
	int          m_fieldCnt;
	
	char		m_strCMD[DEFAULT_SQL_CMD_SIZE];
public:
	void GetLastError(char* pErrBuf,int nMaxSize=512); 
	BOOL Ping();
	std::string m_strHost;
	int m_nPort;
	std::string m_strUser;
	std::string m_strPwd;
	std::string m_strDB;
};

#endif // !defined(AFX_MYSQLDB_H__9B453EFB_2CB7_4A88_96BB_9C9E0108BB84__INCLUDED_)
