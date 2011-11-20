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
#include "sloSetAttrAgent.h"
#include <map>
#include "TTComboBox.h"
#include "IconEdit.h"
#include "FilenameEdit.h"
#include "sloOpenFileAgent.h"

typedef struct _GroupInfo
{
	CXTPTaskPanelGroup* pGroup;
	int nItemSize;
}GroupInfo, *LPGroupInfo;

class CFastSearchDlg : public CDialog
{
// Construction
public:
	CFastSearchDlg(CWnd* pParent = NULL);   // standard constructor

//	CSearchThread* m_pSearchThread;
// Dialog Data
	//{{AFX_DATA(CFastSearchDlg)
	enum { IDD = IDD_DIALOG_FAST_SEARCH };
	CStatic	m_picBack;
	CIconEdit	m_keyEdit;
	CStatic	m_static_find;
	CTTComboBox	m_BoxListRecent;
	CTTComboBox	m_BoxList;
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
	afx_msg void OnDestroy();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnSelchangeComboPathRecent();
	afx_msg void OnKillfocusEditSearchKey();
	afx_msg void OnSetfocusEditSearchKey();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	LRESULT OnTaskPanelNotify(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnProgressChange(WPARAM wParam, LPARAM lParam);

private:
    CFilenameEdit   m_FilenameEdit;
public:
	int GetFileID(char* szFileType);
	
	void SetWinPos();
	void SetComboxPos(BOOL bRecent);
	void SetStaticFindPos();
	
	void OnEventNotify();
	BOOL CreateTaskPanel();
	
	void AddLinkItem(UINT nFolderID, UINT nItemID, int nIconIndex, LPCTSTR lpszCaption, std::vector<DespInfo> DespList,LPCTSTR lpszTooltip = "", BOOL bShowTextItem = TRUE);
	void AddToolboxGroup(UINT nID, LPCTSTR lpszCaption, LPCTSTR lpszTooltip = "", int nIconIndex = 0);
	
	void AddLinkItemEx(UINT nFolderID, UINT nItemID, int nIconIndex, LPCTSTR lpszCaption, std::vector<DespInfo> DespList,LPCTSTR lpszTooltip = "", BOOL bShowTextItem = TRUE);
	
	void ClearGroupsItems(); 
	
	void UpdateGroupsCaption(); 
	
	void OnTaskPanelClickDownEvent(WPARAM wParam, LPARAM lParam);
	
	void OnProgressChangeRecent(FastItem item);
	
	CXTPTaskPanel m_wndTaskPanel;
	sloFastSearchAgent m_agent;
	sloSetAttrAgent m_setAgent;
	std::map<int, GroupInfo> m_listMap;
	sloOpenFileAgent m_fileopen;
	BOOL m_bDestory;
	BOOL m_bCommboxRecentStatus;
	BOOL m_bEditForce;
	CString m_strOldKey;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FASTSEARCHDLG_H__013AEC8A_1717_41AC_9958_05F58B0A892D__INCLUDED_)
