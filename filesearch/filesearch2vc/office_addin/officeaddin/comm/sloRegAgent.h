// sloRegAgent.h: interface for the sloRegAgent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLOREGAGENT_H__ED21EA86_AAE4_48A2_B506_AB370AFDED4D__INCLUDED_)
#define AFX_SLOREGAGENT_H__ED21EA86_AAE4_48A2_B506_AB370AFDED4D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class sloRegAgent  
{
public:
	sloRegAgent();
	virtual ~sloRegAgent();

	BOOL ReadInstallPath(TCHAR *szInstallPath);
public:
	//Set value reg
	int SetValue_MUTIS (struct HKEY__*ReRootKey,TCHAR *ReSubKey,TCHAR *ReValueName,LPBYTE ReSetContent_S,DWORD dwLen);
	int SetValue_ExpandS (struct HKEY__*ReRootKey,TCHAR *ReSubKey,TCHAR *ReValueName,LPBYTE ReSetContent_S);
	int SetValue_B (struct HKEY__*ReRootKey,TCHAR *ReSubKey,TCHAR *ReValueName,BYTE ReSetContent_B[256]);
	int SetValue_D (struct HKEY__*ReRootKey,TCHAR *ReSubKey,TCHAR *ReValueName,DWORD ReSetContent_D);
	int SetValue_S (struct HKEY__*ReRootKey,TCHAR *ReSubKey,TCHAR *ReValueName,LPBYTE ReSetContent_S);
	
	int ShowContent_S(struct HKEY__*ReRootKey,TCHAR *ReSubKey,TCHAR *ReValueName,LPBYTE ReShowContent_S, DWORD &dwLen);
};

#endif // !defined(AFX_SLOREGAGENT_H__ED21EA86_AAE4_48A2_B506_AB370AFDED4D__INCLUDED_)
