// sloCustomCiHuiAgent.h: interface for the sloCustomCiHuiAgent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLOCUSTOMCIHUIAGENT_H__B04D28C7_7344_4E00_95B9_AFD6603A18CF__INCLUDED_)
#define AFX_SLOCUSTOMCIHUIAGENT_H__B04D28C7_7344_4E00_95B9_AFD6603A18CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class sloCustomCiHuiAgent  
{
public:
	sloCustomCiHuiAgent();
	virtual ~sloCustomCiHuiAgent();

	BOOL EventCustomCiHui(BOOL bOver, char* pszFilePath);

private:
	BOOL WritePropertyfileString(LPCTSTR lpKeyName, LPCTSTR lpString, LPCTSTR lpFileName);
	BOOL GetPropertyfileString(LPCTSTR lpKeyName, LPCTSTR lpDefault, LPTSTR lpReturnedString, DWORD nSize, LPCTSTR lpFileName);

	BOOL IsFileExists(LPCTSTR lpszFileName);

	BOOL GetProFilePath();

	char m_szProFilePath[MAX_PATH];
};

#endif // !defined(AFX_SLOCUSTOMCIHUIAGENT_H__B04D28C7_7344_4E00_95B9_AFD6603A18CF__INCLUDED_)
