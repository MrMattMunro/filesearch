// LocalAgenter.h : main header file for the LOCALAGENTER application
//

#if !defined(AFX_LOCALAGENTER_H__BC93EF83_2410_417A_9040_7C99C4449665__INCLUDED_)
#define AFX_LOCALAGENTER_H__BC93EF83_2410_417A_9040_7C99C4449665__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CLocalAgenterApp:
// See LocalAgenter.cpp for the implementation of this class
//

class CLocalAgenterApp : public CWinApp
{
public:
	CLocalAgenterApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLocalAgenterApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CLocalAgenterApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOCALAGENTER_H__BC93EF83_2410_417A_9040_7C99C4449665__INCLUDED_)
