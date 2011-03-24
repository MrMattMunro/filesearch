#include "StdAfx.h"
#include "slDirMonitor.h"
#include "DirectoryChanges.h"
#include "DirectoryChangeHandler_Dispatch.h"
#include "slLogSendThread.h"
#include "slXmlAgent.h"

//default filters
#define INCLUDE_FILTERS_STRING ""
#define EXCLUDE_FILTERS_STRING ""

CDirectoryChangeWatcher			m_DirWatcher;
slLogSendThread* g_lpLogSendAgent = NULL;
slXmlAgent g_xmlFilterAgent;

CString	m_strExcludeFilter1;
CString	m_strIncludeFilter1;

BOOL g_iniInit = FALSE;

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	BOOL    bret = FALSE;
	HRESULT hr = E_FAIL;

    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH: 
			{
				char szLogPath[MAX_PATH] = {0};
				char szProcName[MAX_PATH] = {0};
				GetSystemDirectory(szProcName, MAX_PATH);
				sprintf(szLogPath,"%s\\slfile.log", szProcName);
						
				log.SetFile(szLogPath);
				log.SetLevel(100);
				log.SetMode(Log::ToFile );	

			}
			break;
		case DLL_PROCESS_DETACH:
			{				

			}
			break;
		case DLL_THREAD_ATTACH:

			break;
		case DLL_THREAD_DETACH:

			break;
    }
    return TRUE;
}

DWORD __stdcall Monitor_Start_AllDisk(BOOL bRemovableDisk)
{
	DWORD dwRet = 0;
	//枚举当前所有的盘符，监视其中的可写盘符。
	TCHAR szDiskStr[MAX_PATH] = {0};
	GetLogicalDriveStrings(MAX_PATH, szDiskStr);

	TCHAR *ptmp  = szDiskStr;
	while (ptmp[0])
	{
		//如果是软盘 跳过
		if(('a' == (*ptmp)) || ('A' == (*ptmp)))
		{
			ptmp += 4;
			continue;
		}
		
		if(((DRIVE_REMOVABLE == GetDriveType(ptmp)) && bRemovableDisk) || 
			(DRIVE_FIXED == GetDriveType(ptmp)) || 
			(DRIVE_REMOTE == GetDriveType(ptmp)))
		{
			CString sDiskStr(ptmp);
			dwRet = Monitor_Start_Dir(ptmp, 4);
		}
		
		ptmp += 4;
	}

	return dwRet;
}

DWORD __stdcall Monitor_Start_Dir(char* pszDirPath, DWORD dwLen)
{
	log.Print(LL_DEBUG_INFO,"Begin To Monitor %s\r\n",pszDirPath);
	DWORD dwRet = 0;
	DWORD dwWatch = 0;
	CString	m_strDirectoryToMonitor(pszDirPath);

	g_xmlFilterAgent.LoadXML();

	DWORD dwChangeFilter = FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_LAST_WRITE;;
	BOOL bWatchSubDir = TRUE;
	
	if( m_DirWatcher.IsWatchingDirectory( m_strDirectoryToMonitor) )
		m_DirWatcher.UnwatchDirectory( m_strDirectoryToMonitor );
	if (!g_lpLogSendAgent)
	{
		g_lpLogSendAgent = new slLogSendThread();
		if (!g_lpLogSendAgent)
		{
			return -1;
		}
		g_lpLogSendAgent->startup();

	}
	CDirectoryChangeHandler_Dispatch * pHandler = new CDirectoryChangeHandler_Dispatch(g_lpLogSendAgent);
		
	if( ERROR_SUCCESS != (dwWatch = m_DirWatcher.WatchDirectory(m_strDirectoryToMonitor, 
		dwChangeFilter,
		pHandler,
		bWatchSubDir,
		m_strIncludeFilter1,
		m_strExcludeFilter1)) )
	{
		dwRet = 1;
	}

	if( pHandler )
		pHandler->Release();

	return dwRet;
}

DWORD __stdcall Monitor_Stop()
{
	m_DirWatcher.UnwatchAllDirectories();
	return 0;
}
