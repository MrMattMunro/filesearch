#if !defined(AFX_FASTSEARCHDLG_H__013AEC8A_1717_41AC_9958_05F58B0A892D__INCLUDED_)
#define AFX_FASTSEARCHDLG_H__013AEC8A_1717_41AC_9958_05F58B0A892D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FastSearchDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFastSearchDlg dialog
#include "sloFastSearchAgent.h"
#include <map>

class CFastSearchDlg : public CDialog
{
// Construction
public:
	CFastSearchDlg(CWnd* pParent = NULL);   // standard constructor

	void ResetToolboxItems();
	BOOL CreateTaskPanel();
	CXTPTaskPanelGroup* CreateToolboxGroup(UINT nID);

	void AddLinkItem(UINT nFolderID, UINT nItemID, int nIconIndex, LPCTSTR lpszCaption);
	void AddToolboxGroup(UINT nID, LPCTSTR lpszCaption);

	CXTPTaskPanel m_wndTaskPanel;
	sloFastSearchAgent m_agent;
	std::map<int, CXTPTaskPanelGroup*> m_listMap;
// Dialog Data
	//{{AFX_DATA(CFastSearchDlg)
	enum { IDD = IDD_DIALOG_FAST_SEARCH };
	CComboBox	m_BoxList;
	CString	m_strKey;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFastSearchDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFastSearchDlg)
	afx_msg void OnEditchangeComboPath();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEditSearchKey();
	afx_msg void OnSelchangeComboPath();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FASTSEARCHDLG_H__013AEC8A_1717_41AC_9958_05F58B0A892D__INCLUDED_)
