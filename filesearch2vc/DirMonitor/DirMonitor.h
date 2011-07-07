// DirMonitor.h : main header file for the DIRMONITOR DLL
//

#if !defined(AFX_DIRMONITOR_H__EAD27E89_B8B7_4E18_9D1A_B2575AB9AA12__INCLUDED_)
#define AFX_DIRMONITOR_H__EAD27E89_B8B7_4E18_9D1A_B2575AB9AA12__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDirMonitorApp
// See DirMonitor.cpp for the implementation of this class
//

class CDirMonitorApp : public CWinApp
{
public:
	CDirMonitorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDirMonitorApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CDirMonitorApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIRMONITOR_H__EAD27E89_B8B7_4E18_9D1A_B2575AB9AA12__INCLUDED_)
