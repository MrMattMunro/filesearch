// sl4j.h : main header file for the SL4J DLL
//

#if !defined(AFX_SL4J_H__D7D27E3A_E962_41CA_AD36_42BDD3FA4066__INCLUDED_)
#define AFX_SL4J_H__D7D27E3A_E962_41CA_AD36_42BDD3FA4066__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSl4jApp
// See sl4j.cpp for the implementation of this class
//

class CSl4jApp : public CWinApp
{
public:
	CSl4jApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSl4jApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CSl4jApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SL4J_H__D7D27E3A_E962_41CA_AD36_42BDD3FA4066__INCLUDED_)
