// sloCreateIndexAgent.h: interface for the sloCreateIndexAgent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLOCREATEINDEXAGENT_H__15940A96_1924_4B1D_9BE0_4C4496E39144__INCLUDED_)
#define AFX_SLOCREATEINDEXAGENT_H__15940A96_1924_4B1D_9BE0_4C4496E39144__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
 
class sloCreateIndexAgent  : public mysqlcomm
{
public:
	sloCreateIndexAgent();
	virtual ~sloCreateIndexAgent();
public:

	BOOL EventCreateIndex(char* pszSearchPath, char* pszFileTypes);

private:
	void BuildSearchName();
	void BuildIndexPath();

	int GetMaxIndexID();
	string ConverSqlPath(string strPath);
 
	//disk
	void GetDrvSpaceInfo(char* pDisk);
	void FindAllDrivers();

	BOOL IsSearchPathExist(char* pszSearchPath);
	
public:
	char m_cMaxDriver;
	ULARGE_INTEGER m_uMaxFreeSpace;
	char m_szSearchName[MAX_PATH];	
	char m_szIndexPath[MAX_PATH];
 
};

#endif // !defined(AFX_SLOCREATEINDEXAGENT_H__15940A96_1924_4B1D_9BE0_4C4496E39144__INCLUDED_)
