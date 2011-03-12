// sloCreateIndexAgent.cpp: implementation of the sloCreateIndexAgent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "FsUiTest.h"
#include "sloCreateIndexAgent.h"
#include "Shlwapi.h"

#pragma comment(lib, "Shlwapi.lib ")


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

sloCreateIndexAgent::sloCreateIndexAgent()
{
	m_cMaxDriver = 'C';
	memset(m_szSearchName, NULL, MAX_PATH);
	memset(m_szIndexPath, NULL, MAX_PATH);
	m_uMaxFreeSpace.QuadPart = 0;
}

sloCreateIndexAgent::~sloCreateIndexAgent()
{
 
}

void sloCreateIndexAgent::GetDrvSpaceInfo(char* pDisk) 
{
	
	//获得选择的驱动器
	CString Driver = pDisk;

	if (Driver == "C:\\")
	{
		return ;
	}
	
	//获得磁盘空间信息
	ULARGE_INTEGER FreeAv,TotalBytes,FreeBytes;
	if(GetDiskFreeSpaceEx(Driver,&FreeAv,&TotalBytes,&FreeBytes))
	{
		//格式化信息，并显示出来
		CString strTotalBytes,strFreeBytes;
		strTotalBytes.Format("%u字节",TotalBytes.QuadPart);
		strFreeBytes.Format("%u字节",FreeBytes.QuadPart);
		if (FreeBytes.QuadPart > m_uMaxFreeSpace.QuadPart)
		{
			m_uMaxFreeSpace = FreeBytes;
			m_cMaxDriver = pDisk[0];
		}
	}
	
}

void sloCreateIndexAgent::FindAllDrivers()
{
	//	CComboBox* Driver=(CComboBox*)GetDlgItem(IDC_DRIVER);
	DWORD dwNumBytesForDriveStrings;//实际存储驱动器号的字符串长度
	HANDLE hHeap;
	LPSTR lp;
	CString strLogdrive;
	
	//获得实际存储驱动器号的字符串长度
	dwNumBytesForDriveStrings=GetLogicalDriveStrings(0,NULL)*sizeof(TCHAR);
	
	//如果字符串不为空，则表示有正常的驱动器存在
	if (dwNumBytesForDriveStrings!=0) {
		//分配字符串空间
		hHeap=GetProcessHeap();
		lp=(LPSTR)HeapAlloc(hHeap,HEAP_ZERO_MEMORY,
			dwNumBytesForDriveStrings);
		
		//获得标明所有驱动器的字符串
		GetLogicalDriveStrings(HeapSize(hHeap,0,lp),lp);
		
		//将驱动器一个个放到下拉框中
		while (*lp!=0) {
			//Driver->AddString(lp);
			GetDrvSpaceInfo(lp);
			
			lp=_tcschr(lp,0)+1;
		}
	}
	
}

void sloCreateIndexAgent::BuildSearchName()
{
	//从数据库中获取已经存在的searchname的个数
	int nNameCount = GetMaxIndexID();
	memset(m_szSearchName, NULL,MAX_PATH);
	sprintf(m_szSearchName,"searcher%d",nNameCount+1);

}

void sloCreateIndexAgent::BuildIndexPath()
{
	//从数据库中获取已经存在的searchname的个数
	FindAllDrivers();

	int nNameCount = GetMaxIndexID();
	if (nNameCount == -1)
		return ;

	memset(m_szIndexPath, NULL, MAX_PATH);
	sprintf(m_szIndexPath,"%c:\\searcher_%d_index",m_cMaxDriver,nNameCount+1);	
	
	if (!PathFileExists(m_szIndexPath))
	{
		if (CreateDirectory(m_szIndexPath, NULL))
		{
			//设置文件夹属性
			SetFileAttributes(m_szIndexPath,FILE_ATTRIBUTE_HIDDEN);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//不能获取索引个数，因为索引被删除以后，在根据获取索引个数，会出现重复的索引名称
//-1 从数据库中读取失败
int sloCreateIndexAgent::GetMaxIndexID()
{
	//从数据库中获取最大的索引id
	if (!m_pMySqlDB && !ConnectDB())
	{
		return -1;
	}

	int dwMaxID = 0;
	std::string strQuerySQL = "select max(id) as maxid from t_searcher";
	HRESULT hr = doSqlExe(FALSE, strQuerySQL.c_str());
	if (FAILED(hr))
		return -1;
	
	int nCount = m_pMySqlDB->GetRowCount();
	int nFieldCount = m_pMySqlDB->GetFieldCount();
	if(nCount >= 1 && nFieldCount >= 1)
	{	
		bool bSucc = m_pMySqlDB->GetRow();
		if(bSucc==false)
			return -1;
		
		int nIDLen = 0;
		char* pId = m_pMySqlDB->GetField("maxid",&nIDLen);
		if(pId != NULL && nIDLen >= 1)
			return atoi(pId);
	}

	return dwMaxID;
}

string sloCreateIndexAgent::ConverSqlPath(string strPath)
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

BOOL sloCreateIndexAgent::IsSearchPathExist(char* pszSearchPath)
{
	//从数据库中获取最大的索引id
	if (!m_pMySqlDB && !ConnectDB())
	{
		return FALSE;
	}
	
	int dwMaxID = 0;
	std::string strQuerySQL = "select * from t_searcher where path='%s'";
	HRESULT hr = doSqlExe(TRUE, strQuerySQL.c_str(), ConverSqlPath(pszSearchPath).c_str());
	if (FAILED(hr))
		return -1;
	
	int nCount = m_pMySqlDB->GetRowCount();
	int nFieldCount = m_pMySqlDB->GetFieldCount();
	if(nCount >= 1 && nFieldCount >= 1)
	{	
		bool bSucc = m_pMySqlDB->GetRow();
		if(bSucc==false)
			return FALSE;
		
		int nPathLen = 0;
		char* pPath = m_pMySqlDB->GetField("path",&nPathLen);
		if(pPath != NULL && nPathLen >= 1)
			return TRUE;
	}
	
	return FALSE;

}

BOOL sloCreateIndexAgent::EventCreateIndex(char* pszSearchPath, char* pszFileTypes)
{
	//判断该目录是否已经建立过索引
	if (IsSearchPathExist(pszSearchPath))
		return FALSE;

	//构建索引目录
	BuildIndexPath();

	BOOL bRet = TRUE;
	std::string strQuerySQL = "insert into t_searcher(path,indexpath,filetype,hascreateindex,hasupdate,hasdel,lastmodify) values('%s','%s','%s','0','0','0','%s')";
	HRESULT hr = doSqlExe(TRUE, strQuerySQL.c_str(),ConverSqlPath(pszSearchPath).c_str(), ConverSqlPath(m_szIndexPath).c_str(), pszFileTypes, sloCommAgent::GetCurTime());
	if (FAILED(hr))
		bRet = FALSE;
	
	return bRet;
}
