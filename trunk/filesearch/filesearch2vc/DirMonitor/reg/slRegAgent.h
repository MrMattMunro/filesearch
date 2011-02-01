// slRegAgent.h: interface for the slRegAgent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLREGAGENT_H__31D3B36F_2258_4DD4_8D91_C9B732279A69__INCLUDED_)
#define AFX_SLREGAGENT_H__31D3B36F_2258_4DD4_8D91_C9B732279A69__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class slRegAgent  
{
public:
	slRegAgent();
	virtual ~slRegAgent();

	BOOL ReadXmlPath(TCHAR *szXmlPath);
public:
	//Set value reg
	int SetValue_MUTIS (struct HKEY__*ReRootKey,TCHAR *ReSubKey,TCHAR *ReValueName,LPBYTE ReSetContent_S,DWORD dwLen);
	int SetValue_ExpandS (struct HKEY__*ReRootKey,TCHAR *ReSubKey,TCHAR *ReValueName,LPBYTE ReSetContent_S);
	int SetValue_B (struct HKEY__*ReRootKey,TCHAR *ReSubKey,TCHAR *ReValueName,BYTE ReSetContent_B[256]);
	int SetValue_D (struct HKEY__*ReRootKey,TCHAR *ReSubKey,TCHAR *ReValueName,DWORD ReSetContent_D);
	int SetValue_S (struct HKEY__*ReRootKey,TCHAR *ReSubKey,TCHAR *ReValueName,LPBYTE ReSetContent_S);
	int CreateSubKey(struct HKEY__*ReRootKey,TCHAR *ReSubKey);
	
	int ShowContent_S(struct HKEY__*ReRootKey,TCHAR *ReSubKey,TCHAR *ReValueName,LPBYTE ReShowContent_S);
	int ShowContent_D(struct HKEY__*ReRootKey,TCHAR *ReSubKey,TCHAR *ReValueName,DWORD &ReShowContent_D);
};

#endif // !defined(AFX_SLREGAGENT_H__31D3B36F_2258_4DD4_8D91_C9B732279A69__INCLUDED_)
