#if !defined(AFX_FLOATWND_H__DD886034_436D_4422_968E_72FE2E373234__INCLUDED_)
#define AFX_FLOATWND_H__DD886034_436D_4422_968E_72FE2E373234__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FloatWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFloatWnd dialog
#include "sloHotkeyAgent.h"

class CFloatWnd : public CDialog
{
// Construction
public:
	CFloatWnd(CWnd* pParent = NULL);   // standard constructor
	void OnUpdateTransparent(int iTransparent);
	void RegHotKey();
	int nTickCount;
	sloHotkeyAgent m_hotkey;
// Dialog Data
	//{{AFX_DATA(CFloatWnd)
	enum { IDD = IDD_FLOATWND };
	CStatic	m_Logo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFloatWnd)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFloatWnd)
	virtual BOOL OnInitDialog();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnHide();
	afx_msg void OnMenuNewIndex();
	afx_msg void OnMenuSysSet();
	afx_msg void OnMenuWebQuery();
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg void OnMenuTrans100();
	afx_msg void OnMenuTrans20();
	afx_msg void OnMenuTrans40();
	afx_msg void OnMenuTrans60();
	afx_msg void OnMenuTrans80();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLogo();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg LRESULT OnHotKey(WPARAM wp,LPARAM lp);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLOATWND_H__DD886034_436D_4422_968E_72FE2E373234__INCLUDED_)
