// DirMonitorTest.h : main header file for the DIRMONITORTEST application
//

#if !defined(AFX_DIRMONITORTEST_H__644CCF76_C97E_4AA0_AFA3_737D2B27BC2E__INCLUDED_)
#define AFX_DIRMONITORTEST_H__644CCF76_C97E_4AA0_AFA3_737D2B27BC2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDirMonitorTestApp:
// See DirMonitorTest.cpp for the implementation of this class
//

class CDirMonitorTestApp : public CWinApp
{
public:
	CDirMonitorTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDirMonitorTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDirMonitorTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIRMONITORTEST_H__644CCF76_C97E_4AA0_AFA3_737D2B27BC2E__INCLUDED_)
