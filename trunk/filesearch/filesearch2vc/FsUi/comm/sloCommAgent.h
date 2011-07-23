// sloCommAgent.h: interface for the sloCommAgent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLOCOMMAGENT_H__DC6A156B_963F_4AAB_9116_E934A742DE58__INCLUDED_)
#define AFX_SLOCOMMAGENT_H__DC6A156B_963F_4AAB_9116_E934A742DE58__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class sloCommAgent  
{
public:
	sloCommAgent();
	virtual ~sloCommAgent();
	
	static char* GetCurTime(int nAddYear = 0);
	static BOOL DoFileDialog(BOOL bOpenFileDialog, char *szPath, LPCTSTR lpszFilter,LPCTSTR lpszDefExt = NULL );
	
	static BOOL IsFileExists(LPCTSTR lpszFileName) ;
	static BOOL GetPropertyfileString(LPCTSTR lpKeyName, LPCTSTR lpDefault, LPTSTR lpReturnedString, DWORD nSize, LPCTSTR lpFileName);
	static BOOL WritePropertyfileString(LPCTSTR lpKeyName, LPCTSTR lpString, LPCTSTR lpFileName);
	static string ConverSqlPath(string strPath);
};

#endif // !defined(AFX_SLOCOMMAGENT_H__DC6A156B_963F_4AAB_9116_E934A742DE58__INCLUDED_)
