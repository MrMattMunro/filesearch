// sloDiskManager.cpp: implementation of the sloDiskManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "sl4j.h"
#include "sloDiskManager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

sloDiskManager::sloDiskManager()
{
	m_cMaxDriver = 'C';
	m_uMaxFreeSpace.QuadPart = 0;
}

sloDiskManager::~sloDiskManager()
{

}

void sloDiskManager::GetDrvSpaceInfo(char* pDisk) 
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

void sloDiskManager::FindAllDrivers()
{
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


char sloDiskManager::GetMaxFreeSpaceDisk()
{
	FindAllDrivers();

	return m_cMaxDriver;
}
