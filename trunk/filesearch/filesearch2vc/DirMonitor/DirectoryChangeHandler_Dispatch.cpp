// DirectoryChangeHandler_Dispatch.cpp: implementation of the CDirectoryChangeHandler_Dispatch class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DirMonitor.h"
#include "DirectoryChangeHandler_Dispatch.h"

extern slLogSendThread		g_LogSendThread;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDirectoryChangeHandler_Dispatch::CDirectoryChangeHandler_Dispatch()
{
	m_lastmodify = _T("");
	m_dwAddCurTick = 0;
	m_dwModifyCurTick = 0;
	m_dwRenameCurTick = 0;
}

CDirectoryChangeHandler_Dispatch::~CDirectoryChangeHandler_Dispatch()
{
}



char* GetCurTime()
{
	char *pszTime = new char[30];
	memset(pszTime, NULL, 30);
	SYSTEMTIME stTime;
	GetLocalTime(&stTime);
	sprintf(pszTime,"%04d-%02d-%02d %02d:%02d:%02d",
		stTime.wYear, stTime.wMonth, stTime.wDay, stTime.wHour, stTime.wMinute, stTime.wSecond);
	return pszTime;
}

void AddFileLogTime(File_Action_Log &filelog)
{
	char *pszTime = GetCurTime();
	memcpy(filelog.szLogTime, pszTime, strlen(pszTime));
	if (pszTime)
	{
		delete pszTime;
		pszTime = NULL;
	}
}
//These functions are called when the directory to watch has had a change made to it
void CDirectoryChangeHandler_Dispatch::On_FileAdded(const CString & strFileName)
{	

	m_dwAddCurTick = GetTickCount();
	m_strFileAddName = strFileName;
	CString strTmpName = strFileName;

	File_Action_Log filelog;
	filelog.FileActon = FILE_ADD;
	memcpy(filelog.szSrcName, strTmpName.GetBuffer(0),strTmpName.GetLength());
	AddFileLogTime(filelog);

	g_LogSendThread.AddLog(filelog);

	log.Print(LL_DEBUG_INFO, "File Added!FileName=%s\r\n",m_strFileAddName.GetBuffer(0));
}

void CDirectoryChangeHandler_Dispatch::On_FileRemoved(const CString & strFileName)
{
	CString strTmpName = strFileName;
	File_Action_Log filelog;
	filelog.FileActon = FILE_REMOVED;
	memcpy(filelog.szSrcName, strTmpName.GetBuffer(0),strTmpName.GetLength());
	AddFileLogTime(filelog);
	g_LogSendThread.AddLog(filelog);

	log.Print(LL_DEBUG_INFO, "File Removed!FileName=%s\r\n",strTmpName.GetBuffer(0));
}

void CDirectoryChangeHandler_Dispatch::On_FileModified(const CString & strFileName)
{
 	CString strTmpName = strFileName;
// 	DWORD dwCurTick = GetTickCount();
// 
// 	if ((5000 < (dwCurTick - m_dwModifyCurTick)) || (0 != strFileName.CompareNoCase(m_lastmodify)))
// 	{ 
// 		//过滤掉刚刚新建时的编辑
// 
// 		if ((2000 > (dwCurTick - m_dwAddCurTick)) && (0 == m_strFileAddName.CompareNoCase(strFileName)))
// 		{
// 			m_dwModifyCurTick = dwCurTick;
// 			return;
// 		}
		File_Action_Log filelog;
		filelog.FileActon = FILE_MODIFYED;
		memcpy(filelog.szSrcName, strTmpName.GetBuffer(0),strTmpName.GetLength());
		AddFileLogTime(filelog);
		g_LogSendThread.AddLog(filelog);

// 		m_lastmodify.Empty();
// 		m_lastmodify.Format(strFileName); 
// 	}
// 	
//	m_dwModifyCurTick = dwCurTick;	

	log.Print(LL_DEBUG_INFO, "File Modified!FileName=%s\r\n",strTmpName.GetBuffer(0));
}

void CDirectoryChangeHandler_Dispatch::On_FileNameChanged(const CString & strOldFileName, const CString & strNewFileName)
{
	CString strTmpOldName = strOldFileName;
	CString strTmpNewName = strNewFileName;
	File_Action_Log filelog;
	filelog.FileActon = FILE_NAMECHANGE;
	memcpy(filelog.szSrcName, strTmpOldName.GetBuffer(0),strTmpOldName.GetLength());
	memcpy(filelog.szSrcName+strTmpOldName.GetLength(),"*",1);
	memcpy(filelog.szSrcName+strTmpOldName.GetLength()+1,strTmpNewName.GetBuffer(0),strTmpNewName.GetLength());
	AddFileLogTime(filelog);
	g_LogSendThread.AddLog(filelog);

	OutputDebugStringA("File name changed from");
	log.Print(LL_DEBUG_INFO, "File Name Changed!SrcName=%s, DesName=%s\r\n",strTmpOldName.GetBuffer(0),strTmpNewName.GetBuffer(0));
}

void CDirectoryChangeHandler_Dispatch::On_WatchStarted(DWORD dwError, const CString & strDirectoryName)
{
	if( dwError == 0 )
	{	
		OutputDebugStringA("Directory Watch Started:");
	}
	else
	{
		OutputDebugStringA("Directory watch failed:");
	}

// 	if( dwError == 0 )
// 		m_listBox.AddString( _T("Directory Watch Started: ") + strDirectoryName);
// 	else
// 		m_listBox.AddString( _T("Directory watch failed: ") + strDirectoryName);
}

void CDirectoryChangeHandler_Dispatch::On_WatchStopped(const CString & strDirectoryName)
{
	//
	//	NOTE:  Be careful ! On_WatchStopped can be called AFTER this list box has
	//	been destoroyed.  Be carefull whenever interacting w/ windows with this function
	//	because the window may not be valid when this function is executed for the last time.
	//
	//
	OutputDebugStringA("Directory Watch Stoped:");

// 	if( ::IsWindow( m_listBox.GetSafeHwnd() ) )
// 		m_listBox.AddString(_T("Stopped watching directory: ") + strDirectoryName);
// 	else
// 	{
// 		TRACE(_T("NOTE: m_listBox is not a valid window! This has probably been called as the result of program shutdown sometime after CDirWatcherDlg::OnBtnMonitor2() was used to watch a direcotry.\n"));
// 		TRACE(_T("NOTE: Be sure that you are careful in your implementation of this function to watch out for the same condition if you are dealing w/ windows.\n"));
// 		//			MessageBeep(static_cast<UINT>(-1));
// 		//			MessageBeep(static_cast<UINT>(-1));
// 		//			MessageBeep(static_cast<UINT>(-1));
// 		
// 		//
// 		//	See the comments in DirectoryChanges.h for the CDirectoryChangeHandler::On_WatchStopped() function.
// 		//
// 		//
// 	}
}
