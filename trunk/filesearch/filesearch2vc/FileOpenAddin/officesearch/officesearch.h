// officesearch.h : main header file for the OFFICESEARCH application
//

#if !defined(AFX_OFFICESEARCH_H__BB5E3DEE_B164_4848_B0F7_73E3F1ACDA82__INCLUDED_)
#define AFX_OFFICESEARCH_H__BB5E3DEE_B164_4848_B0F7_73E3F1ACDA82__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// COfficesearchApp:
// See officesearch.cpp for the implementation of this class
//

class COfficesearchApp : public CWinApp
{
public:
	COfficesearchApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COfficesearchApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(COfficesearchApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OFFICESEARCH_H__BB5E3DEE_B164_4848_B0F7_73E3F1ACDA82__INCLUDED_)
