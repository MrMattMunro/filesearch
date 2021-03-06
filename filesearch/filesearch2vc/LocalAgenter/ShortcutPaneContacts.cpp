// ShortcutPaneContacts.cpp: implementation of the CShortcutPaneContacts class.
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

#include "stdafx.h"
//#include "shortcutbar.h"
#include "ShortcutPaneContacts.h"
#include "LocalAgenterDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CShortcutPaneContacts::CShortcutPaneContacts()
{
	m_ilTreeIcons.Create(16, 16, ILC_MASK|ILC_COLOR32, 1, 1);

	HICON hIcon = AfxGetApp()->LoadIcon(IDI_CONTACTS);
	ASSERT(hIcon);

	m_ilTreeIcons.Add (hIcon);

}

CShortcutPaneContacts::~CShortcutPaneContacts()
{

}

BEGIN_MESSAGE_MAP(CShortcutPaneContacts, CXTPShortcutBarPane)
//{{AFX_MSG_MAP(CShortcutPaneCalendar)
	ON_NOTIFY(TVN_SELCHANGED, 0, OnSelchanged)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CShortcutPaneContacts::Create(LPCTSTR lpszCaption, CXTPShortcutBar* pParent)
{
	if (!CXTPShortcutBarPane::Create(lpszCaption, pParent))
		return FALSE;

	VERIFY(m_wndTreeContacts.Create(WS_VISIBLE|TVS_HASBUTTONS|TVS_LINESATROOT, CXTPEmptyRect(), this, 0));

	m_wndTreeContacts.SetImageList(&m_ilTreeIcons, TVSIL_NORMAL);

	m_wndTreeContacts.InsertItem (_T("�첶����"), 0, 0);

	CXTPShortcutBarPaneItem* pitem = AddItem(_T(""), &m_wndTreeContacts, 115);
    pitem->ShowCaption(FALSE);

	return TRUE;
}


void CShortcutPaneContacts::SetParentWnd(LPVOID pParentWnd)
{
	m_pParentWnd = pParentWnd;
}


void CShortcutPaneContacts::OnSelchanged(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
	CLocalAgenterDlg* pDlg = (CLocalAgenterDlg*)m_pParentWnd;
	// Get the selected tree item and its icon.
	//	int nImage;
	HTREEITEM htItem = m_wndTreeContacts.GetSelectedItem();
	if (htItem != NULL)
	{
		pDlg->m_btnDelete.EnableWindow(FALSE);

		CString strItemText = m_wndTreeContacts.GetItemText(htItem);
		m_wndTreeContacts.SelectItem(htItem);	
		
		pDlg->ShowListContent_Cyber();
	}
	
	*pResult = 0;
	
}