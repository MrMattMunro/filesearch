#if !defined(AFX_SEARCHTHREAD_H__FD72B354_32FF_456E_8EDD_D97EC3773600__INCLUDED_)
#define AFX_SEARCHTHREAD_H__FD72B354_32FF_456E_8EDD_D97EC3773600__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SearchThread.h : header file
//

#define WM_SEARCH_MSG	WM_USER + 200
/////////////////////////////////////////////////////////////////////////////
// CSearchThread thread
#include "sloFastSearchAgent.h"
class CSearchThread : public CWinThread
{
	DECLARE_DYNCREATE(CSearchThread)
protected:
	CSearchThread();           // protected constructor used by dynamic creation

	sloFastSearchAgent m_agent;

// Attributes
public:
	HWND m_hParentWnd;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearchThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSearchThread();

	// Generated message map functions
	//{{AFX_MSG(CSearchThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	afx_msg void OnSearch(WPARAM wParam, LPARAM lParam);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCHTHREAD_H__FD72B354_32FF_456E_8EDD_D97EC3773600__INCLUDED_)
