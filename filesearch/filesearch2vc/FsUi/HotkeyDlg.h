#if !defined(AFX_HOTKEYDLG_H__41BE0C33_E708_4020_BFD4_E654B89143CA__INCLUDED_)
#define AFX_HOTKEYDLG_H__41BE0C33_E708_4020_BFD4_E654B89143CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HotkeyDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHotkeyDlg dialog
#include "sloHotkeyAgent.h"
class CHotkeyDlg  : public  CXTPPropertyPage/*CDialog*/
{
// Construction
public:
	CHotkeyDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHotkeyDlg)
	enum { IDD = IDD_DIALOG_HOTKEY };
	CHotKeyCtrl	m_hotkeyWebs;
	CHotKeyCtrl	m_hotkeyFasts;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHotkeyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	virtual BOOL OnApply();
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHotkeyDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnOutofmemoryHotkeyFastSearch(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonSetHotkey();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CFont f;
	sloHotkeyAgent m_hotkey;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOTKEYDLG_H__41BE0C33_E708_4020_BFD4_E654B89143CA__INCLUDED_)
