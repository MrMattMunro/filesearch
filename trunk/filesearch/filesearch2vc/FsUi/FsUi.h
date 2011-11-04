// FsUi.h : main header file for the FSUI DLL
//

#if !defined(AFX_FSUI_H__68B8A356_0F30_44A4_9232_D92002537CA0__INCLUDED_)
#define AFX_FSUI_H__68B8A356_0F30_44A4_9232_D92002537CA0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFsUiApp
// See FsUi.cpp for the implementation of this class
//
DWORD __stdcall FsCreateIndex();
DWORD __stdcall FsModifyIndex(int nID);
DWORD __stdcall FsFastSearch();
DWORD __stdcall FsSetSheet();
DWORD __stdcall FsLoadSkin();

class CFsUiApp : public CWinApp
{
public:
	CFsUiApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFsUiApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CFsUiApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FSUI_H__68B8A356_0F30_44A4_9232_D92002537CA0__INCLUDED_)
