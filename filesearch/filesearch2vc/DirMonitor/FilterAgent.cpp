// FilterAgent.cpp: implementation of the CFilterAgent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DirMonitor.h"
#include "FilterAgent.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFilterAgent::CFilterAgent()
:m_szIncludeFilter(NULL)
,m_szExcludeFilter(NULL)
,m_nNumIncludeFilterSpecs(0)
 ,m_nNumExcludeFilterSpecs(0)
{
	
}

CFilterAgent::~CFilterAgent()
{

}

static inline bool IsEmptyString(LPCTSTR sz)
{
	return (bool)(sz==NULL || *sz == 0);
}

void CFilterAgent::SetFilters(LPCTSTR szIncludeFilter, LPCTSTR szExcludeFilter)
{
	InitializePatterns( szIncludeFilter, szExcludeFilter );
}

BOOL CFilterAgent::InitializePatterns(LPCTSTR szIncludeFilter, LPCTSTR szExcludeFilter)
{
	//
	//	Copy the include/exclude filters if specified...
	//
	//
	if( IsEmptyString(szIncludeFilter) 
		&&	IsEmptyString(szExcludeFilter) )
	{
		return TRUE;//both the include && exclude filters aren't specified
		//no need to initialize the pattern matching function....
		//if filters are never used, then
		//one less dll is loaded.
	}	
	//
	//	we're using the function wildcmp() instead of PathMatchSpec..
	//
	//	this means that multiple pattern specs aren't supported...
	// in order to support them, we'll tokenize the string into multiple
	// pattern specs and test the string multiple times(once per pattern spec) 
	// in order to support multiple patterns.
	//
	//
	//	m_szIncludeFilter & m_szExclude filter will be used like TCHAR**'s instead of TCHAR*'s
	//
	
	m_nNumIncludeFilterSpecs = 0;
	if( !IsEmptyString(szIncludeFilter) )
	{
		TCHAR * szTmpFilter = _tcsdup(szIncludeFilter);
		TCHAR * pTok = _tcstok( szTmpFilter, _T(";"));
		while( pTok )
		{
			m_nNumIncludeFilterSpecs++;
			pTok = _tcstok(NULL, _T(";"));
		}
		if( m_nNumIncludeFilterSpecs == 1 )
			m_szIncludeFilter = _tcsdup(szIncludeFilter);
		else
		{   //allocate room for pointers .. one for each token...
			m_szIncludeFilter = (TCHAR*)malloc( m_nNumIncludeFilterSpecs * sizeof(TCHAR*));
			
			free(szTmpFilter);
			szTmpFilter = _tcsdup(szIncludeFilter);
			pTok = _tcstok(szTmpFilter, _T(";"));
			TCHAR ** ppTmp = (TCHAR**)m_szIncludeFilter;
			while(pTok)
			{
				*ppTmp = _tcsdup(pTok);
				ppTmp++;
				pTok = _tcstok(NULL, _T(";"));
			}
		}
		
		free(szTmpFilter);
	}
	
	//
	//	Do the same for the Exclude filter...
	//
	m_nNumExcludeFilterSpecs = 0;
	if( !IsEmptyString(szExcludeFilter) )
	{
		TCHAR * szTmpFilter = _tcsdup(szExcludeFilter);
		TCHAR * pTok = _tcstok( szTmpFilter, _T(";"));
		while( pTok )
		{
			m_nNumExcludeFilterSpecs++;
			pTok = _tcstok(NULL, _T(";"));
		}
		if( m_nNumExcludeFilterSpecs == 1 )
			m_szExcludeFilter = _tcsdup(szExcludeFilter);
		else
		{   //allocate room for pointers .. one for each token...
			m_szExcludeFilter = (TCHAR*)malloc( m_nNumExcludeFilterSpecs * sizeof(TCHAR*));
			
			free(szTmpFilter);
			szTmpFilter = _tcsdup(szExcludeFilter);
			
			pTok = _tcstok(szTmpFilter, _T(";"));
			TCHAR ** ppTmp = (TCHAR**)m_szExcludeFilter;
			while(pTok)
			{
				*ppTmp = _tcsdup(pTok);
				ppTmp++;
				pTok = _tcstok(NULL, _T(";"));
			}
		}
		free(szTmpFilter);
	}
	
	return (m_szExcludeFilter!= NULL || (m_szIncludeFilter != NULL));
}


bool CFilterAgent::IncludeThisNotification(LPCTSTR szFileName)
//
//	The Include filter specifies which file names we should allow to notifications
//	for... otherwise these notifications are not dispatched to the client's code.
//
//	Tests the file name to see if it matches a filter specification
//
//	RETURN VALUES:
//		
//		true : notifications for this file are to be included...
//			   notifiy the client by calling the appropriate CDirectoryChangeHandler::On_Filexxx() function.
//		false: this file is not included.... do not notifiy the client...
//
{
	ASSERT( szFileName );
	
	if( m_szIncludeFilter == NULL ) // no filter specified, all files pass....
		return true;
	if( m_nNumIncludeFilterSpecs == 1 )
	{
		return _PathMatchSpec(szFileName, m_szIncludeFilter)? true : false;
	}
	else
	{
		TCHAR ** ppTmp = (TCHAR**)m_szIncludeFilter;
		for(int i(0); i < m_nNumIncludeFilterSpecs; ++i )
		{
			if( _PathMatchSpec(szFileName, *ppTmp++) )
				return true;
		}
		return false;
	}
	
	return false;
}


BOOL CFilterAgent::_PathMatchSpec(LPCTSTR string, LPCTSTR wild ) 
{
	const TCHAR *cp, *mp;
	cp = mp = NULL;
	
	while ((*string) && (*wild != _T('*'))) 
	{
		if ((_toupper(*wild) != _toupper(*string)) && (*wild != _T('?'))) 
		{
			return FALSE;
		}
		wild++;
		string++;
	}
	
	while (*string) 
	{
		if (*wild == _T('*')) 
		{
			if (!*++wild) 
			{
				return TRUE;
			}
			mp = wild;
			cp = string+1;
		} 
		else 
			if ((_toupper(*wild) == _toupper(*string)) || (*wild == _T('?'))) 
			{
				wild++;
				string++;
			} 
			else 
			{
				wild = mp;
				string = cp++;
			}
	}
	
	while (*wild == _T('*')) 
	{
		wild++;
	}
	return (!*wild)? TRUE : FALSE;
}
