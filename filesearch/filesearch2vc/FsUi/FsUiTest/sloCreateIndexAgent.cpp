// sloCreateIndexAgent.cpp: implementation of the sloCreateIndexAgent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FsUiTest.h"
#include "sloCreateIndexAgent.h"

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
		// 		CStatic* pTotalStatic = (CStatic*)GetDlgItem(IDC_TOTAL);
		// 		CStatic* pFreeStatic = (CStatic*)GetDlgItem(IDC_FREE);
		// 		pTotalStatic->SetWindowText(strTotalBytes);
		// 		pFreeStatic->SetWindowText(strFreeBytes);
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
	int nNameCount = 0;
	sprintf(m_szSearchName,"searcher%d",nNameCount);

}

void sloCreateIndexAgent::BuildIndexPath()
{
	//从数据库中获取已经存在的searchname的个数
	char szIndexPath[MAX_PATH] = {0};
	int nNameCount = 0;
	sprintf(szIndexPath,"%c:\\searcher_%d_index",m_cMaxDriver,nNameCount);	
	
	if (CreateDirectory(szIndexPath, NULL))
	{
		//设置文件夹属性
		SetFileAttributes(szIndexPath,FILE_ATTRIBUTE_HIDDEN);
	}

}
