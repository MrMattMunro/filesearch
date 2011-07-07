// slMySqlAgent.h: interface for the slMySqlAgent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLMYSQLAGENT_H__8D417962_5253_45F2_AF54_1E7323C9C54C__INCLUDED_)
#define AFX_SLMYSQLAGENT_H__8D417962_5253_45F2_AF54_1E7323C9C54C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct _DbPools
{
	std::string strDBName;
	CMySQLDB*	pSqlDB;
}DbPools,*LPDbPools;

class slMySqlAgent 
{
public:
	slMySqlAgent();
	virtual ~slMySqlAgent();

	bool LogRecord(File_Action_Log FileLog);

private:

	bool AddRec(CMySQLDB* pMySqlDB, File_Action_Log FileLog);
	string GetOperFlag(File_Action_Log FileLog);
	string ConverSqlPath(string strPath);

	CMySQLDB* GetObjectDB(std::string strSearchName);
	void ReleassObjectsDB();
private:
	std::vector<DbPools> m_DbPools;
};

#endif // !defined(AFX_SLMYSQLAGENT_H__8D417962_5253_45F2_AF54_1E7323C9C54C__INCLUDED_)
