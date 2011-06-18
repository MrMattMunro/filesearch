// DirectoryChangeHandler_Dispatch.h: interface for the CDirectoryChangeHandler_Dispatch class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIRECTORYCHANGEHANDLER_DISPATCH_H__B42A149F_41E9_4897_9BE8_8185D22CFF84__INCLUDED_)
#define AFX_DIRECTORYCHANGEHANDLER_DISPATCH_H__B42A149F_41E9_4897_9BE8_8185D22CFF84__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DirectoryChanges.h"

class CDirectoryChangeHandler_Dispatch : public CDirectoryChangeHandler 
{
public:
	CDirectoryChangeHandler_Dispatch();
	virtual ~CDirectoryChangeHandler_Dispatch();
	//These functions are called when the directory to watch has had a change made to it
	void On_FileAdded(const CString & strFileName);
	void On_FileRemoved(const CString & strFileName);
	void On_FileModified(const CString & strFileName);
	void On_FileNameChanged(const CString & strOldFileName, const CString & strNewFileName);
	
	void On_WatchStarted(DWORD dwError, const CString & strDirectoryName);
	void On_WatchStopped(const CString & strDirectoryName);

private:
	CString m_lastmodify;
	CString m_strFileAddName;

	DWORD    m_dwModifyCurTick;
	DWORD    m_dwAddCurTick;
	DWORD    m_dwRenameCurTick;
};

#endif // !defined(AFX_DIRECTORYCHANGEHANDLER_DISPATCH_H__B42A149F_41E9_4897_9BE8_8185D22CFF84__INCLUDED_)
