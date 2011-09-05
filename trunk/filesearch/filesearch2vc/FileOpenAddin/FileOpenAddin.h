// FileOpenAddin.h : main header file for the FILEOPENADDIN DLL
//

#if !defined(AFX_FILEOPENADDIN_H__4D00D4B3_59CF_42B5_87EB_1246244E4D8C__INCLUDED_)
#define AFX_FILEOPENADDIN_H__4D00D4B3_59CF_42B5_87EB_1246244E4D8C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFileOpenAddinApp
// See FileOpenAddin.cpp for the implementation of this class
//

class CFileOpenAddinApp : public CWinApp
{
public:
	CFileOpenAddinApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileOpenAddinApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CFileOpenAddinApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEOPENADDIN_H__4D00D4B3_59CF_42B5_87EB_1246244E4D8C__INCLUDED_)
