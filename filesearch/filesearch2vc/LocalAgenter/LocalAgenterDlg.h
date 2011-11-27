// LocalAgenterDlg.h : header file
//

#if !defined(AFX_LOCALAGENTERDLG_H__45299157_8E32_415B_8C67_CC3D17DBFC3F__INCLUDED_)
#define AFX_LOCALAGENTERDLG_H__45299157_8E32_415B_8C67_CC3D17DBFC3F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CLocalAgenterDlg dialog
#include "ShortcutPaneCalendar.h"
#include "ShortcutPaneFolders.h"
#include "TTComboBox.h"

class CLocalAgenterDlg : public CXTResizeDialog
{
// Construction
public:
	CLocalAgenterDlg(CWnd* pParent = NULL);    // standard constructor

	void ShowListContent_Keywords(int nType, char* szGroupName);
	void ShowListContent_Website(char* szGroupName);

	void SetComboxPos(BOOL bAll);

	CImageList m_ilIcons;
	BOOL m_bCommboxAllSel;
// Dialog Data
	//{{AFX_DATA(CLocalAgenterDlg)
	enum { IDD = IDD_LOCALAGENTER_DIALOG };
	CTTComboBox	m_BoxListTime;
	CTTComboBox	m_BoxListType;
	CTTComboBox	m_BoxListGroup;
	CXTPButton	m_btnSet;
	CXTPButton	m_btnDelete;
	CXTPButton	m_buttonExport;
	CXTPButton	m_btnSearch;
	CXTPReportControl m_wndReportCtrl;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLocalAgenterDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CLocalAgenterDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonExport();
	afx_msg void OnButtonDelete();
	afx_msg void OnButtonSet();
	afx_msg void OnEditchangeComboGroup();
	afx_msg void OnSelchangeComboGroup();
	afx_msg void OnButtonSearch();
	//}}AFX_MSG
	afx_msg void OnButtonDropDown(UINT nID);
	DECLARE_MESSAGE_MAP()
public:
	CXTPShortcutBar m_wndShortcutBar;

	CShortcutPaneCalendar m_paneCalendar;
	CShortcutPaneFolders m_paneFolders;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOCALAGENTERDLG_H__45299157_8E32_415B_8C67_CC3D17DBFC3F__INCLUDED_)
