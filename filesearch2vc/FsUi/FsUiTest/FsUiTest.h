// FsUiTest.h : main header file for the FSUITEST application
//

#if !defined(AFX_FSUITEST_H__0B532F06_B99A_406B_ABD9_39EE5DA97F94__INCLUDED_)
#define AFX_FSUITEST_H__0B532F06_B99A_406B_ABD9_39EE5DA97F94__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFsUiTestApp:
// See FsUiTest.cpp for the implementation of this class
//

class CFsUiTestApp : public CWinApp
{
public:
	CFsUiTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFsUiTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFsUiTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FSUITEST_H__0B532F06_B99A_406B_ABD9_39EE5DA97F94__INCLUDED_)
