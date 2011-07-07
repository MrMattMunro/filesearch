// sloLanguageAgent.h: interface for the sloLanguageAgent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLOLANGUAGEAGENT_H__992CFA04_CBD1_4433_891B_6955185C70AD__INCLUDED_)
#define AFX_SLOLANGUAGEAGENT_H__992CFA04_CBD1_4433_891B_6955185C70AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class sloLanguageAgent  
{
public:
	sloLanguageAgent();
	virtual ~sloLanguageAgent();

	LANGUAGE GetLanguage();
	CString LoadString(char* pID);
protected:
	BOOL GetProFilePath();
public:
	char m_szpropertiesPath[MAX_PATH];
	char m_szPathHead[MAX_PATH];
	char m_szLagFilePath[MAX_PATH];
	LANGUAGE m_lag;

};

#endif // !defined(AFX_SLOLANGUAGEAGENT_H__992CFA04_CBD1_4433_891B_6955185C70AD__INCLUDED_)
