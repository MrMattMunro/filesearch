// FilterAgent.h: interface for the CFilterAgent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILTERAGENT_H__C84F1EF0_0A7C_40C2_92C5_F3B47AE426C4__INCLUDED_)
#define AFX_FILTERAGENT_H__C84F1EF0_0A7C_40C2_92C5_F3B47AE426C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFilterAgent  
{
public:
	CFilterAgent();
	virtual ~CFilterAgent();
	
	BOOL InitializePatterns(LPCTSTR szIncludeFilter, LPCTSTR szExcludeFilter);
	bool IncludeThisNotification(LPCTSTR szFileName);	//	based on file name.
	BOOL _PathMatchSpec(LPCTSTR string, LPCTSTR wild ) ;
	void SetFilters(LPCTSTR szIncludeFilter, LPCTSTR szExcludeFilter);
public:
	int m_nNumIncludeFilterSpecs;
	int m_nNumExcludeFilterSpecs;

	TCHAR * m_szIncludeFilter;		//	Supports the include
	TCHAR * m_szExcludeFilter;		//	& exclude filters
};

#endif // !defined(AFX_FILTERAGENT_H__C84F1EF0_0A7C_40C2_92C5_F3B47AE426C4__INCLUDED_)
