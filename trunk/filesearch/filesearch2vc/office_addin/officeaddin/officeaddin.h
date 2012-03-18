// officeaddin.h : main header file for the OFFICEADDIN DLL
//

#if !defined(AFX_OFFICEADDIN_H__F9DCE117_AFC3_4AAE_BD16_F01BF675DD5A__INCLUDED_)
#define AFX_OFFICEADDIN_H__F9DCE117_AFC3_4AAE_BD16_F01BF675DD5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// COfficeaddinApp
// See officeaddin.cpp for the implementation of this class
//

class COfficeaddinApp : public CWinApp
{
public:
	COfficeaddinApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COfficeaddinApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(COfficeaddinApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OFFICEADDIN_H__F9DCE117_AFC3_4AAE_BD16_F01BF675DD5A__INCLUDED_)
