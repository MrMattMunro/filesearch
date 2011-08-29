// sloFileOpenAddin.h: interface for the sloFileOpenAddin class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLOFILEOPENADDIN_H__18A821C5_DEB3_410E_8E3E_8FC21712344E__INCLUDED_)
#define AFX_SLOFILEOPENADDIN_H__18A821C5_DEB3_410E_8E3E_8FC21712344E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class sloFileOpenAddin  
{
public:
	sloFileOpenAddin();
	virtual ~sloFileOpenAddin();

public:
	DWORD OpenFile_WORD(char* pFileName, int nPage, char* pKeyWords = NULL);
	DWORD OpenFile_EXCEL(char* pFileName, char* pSheet, int nRow, char* pKeyWords = NULL);
	DWORD OpenFile_PPT(char* pFileName, int nPage, char* pKeyWords = NULL);
	DWORD OpenFile_PDF(char* pFileName, int nPage, char* pKeyWords = NULL);
	DWORD OpenFile_TXT(char* pFileName, int nRow, char* pKeyWords = NULL);
};

#endif // !defined(AFX_SLOFILEOPENADDIN_H__18A821C5_DEB3_410E_8E3E_8FC21712344E__INCLUDED_)
