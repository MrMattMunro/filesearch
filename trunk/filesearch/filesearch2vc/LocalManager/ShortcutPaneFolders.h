// ShortcutPaneFolders.h: interface for the CShortcutPaneFolders class.
//
// This file is a part of the XTREME TOOLKIT PRO MFC class library.
// (c)1998-2009 Codejock Software, All Rights Reserved.
//
// THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO BE
// RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED WRITTEN
// CONSENT OF CODEJOCK SOFTWARE.
//
// THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS OUTLINED
// IN THE XTREME TOOLKIT PRO LICENSE AGREEMENT. CODEJOCK SOFTWARE GRANTS TO
// YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE THIS SOFTWARE ON A
// SINGLE COMPUTER.
//
// CONTACT INFORMATION:
// support@codejock.com
// http://www.codejock.com
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHORTCUTPANEFOLDERS_H__79AA106F_6B97_42A1_9CB7_0956F111422B__INCLUDED_)
#define AFX_SHORTCUTPANEFOLDERS_H__79AA106F_6B97_42A1_9CB7_0956F111422B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CShortcutPaneFolders : public CXTPShortcutBarPane
{
public:
	CShortcutPaneFolders();
	virtual ~CShortcutPaneFolders();

	BOOL Create(LPCTSTR lpszCaption, CXTPShortcutBar* pParent);

	CXTTreeCtrl m_wndTreeFolders;

	CImageList m_ilTreeIcons;

	BOOL m_bSelect;
	char m_szTypeName[MAX_PATH];
	//{{AFX_MSG(CShortcutPaneCalendar)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	friend class CMainFrame;
};

#endif // !defined(AFX_SHORTCUTPANEFOLDERS_H__79AA106F_6B97_42A1_9CB7_0956F111422B__INCLUDED_)
