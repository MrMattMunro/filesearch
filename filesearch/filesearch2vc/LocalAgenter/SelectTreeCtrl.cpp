// SelectTreeCtrl.cpp : implementation file
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
//#include "treectrl.h"
#include "SelectTreeCtrl.h"
#include "CyberDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static UINT treeIcons[] =
{
	IDI_INBOX           ,
	//	IDI_SEARCH          ,
	IDI_SENT_ITEMS      ,
	IDI_OUTBOX          ,
	//	IDI_OUTLOOK_TODAY   ,
	//	IDI_DELETED_ITEMS   ,
	IDI_DRAFTS          ,
	IDI_ARCHIVE         ,
	IDI_CALENDAR        ,
	IDI_CONTACTS
};

/////////////////////////////////////////////////////////////////////////////
// CSelectTreeCtrl

CSelectTreeCtrl::CSelectTreeCtrl()
: m_pParentDlg(NULL)
{

}

CSelectTreeCtrl::~CSelectTreeCtrl()
{
}

BEGIN_MESSAGE_MAP(CSelectTreeCtrl, CTreeCtrl)
	//{{AFX_MSG_MAP(CSelectTreeCtrl)
	ON_WM_NCPAINT()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelChanged)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectTreeCtrl message handlers

void CSelectTreeCtrl::OnNcPaint() 
{
	Default();

	if (m_pParentDlg && m_pParentDlg->m_pTreeFocus == this)
	{
		CWindowDC dc(this);
		CXTPWindowRect rc(this);
		rc.OffsetRect(-rc.TopLeft());
		
		dc.Draw3dRect(rc, RGB(0,0,255),RGB(0,0,255));
		rc.DeflateRect(1,1);
		dc.Draw3dRect(rc, RGB(0,0,255),RGB(0,0,255));
	}
	
	// Do not call CTreeCtrl::OnNcPaint() for painting messages
}

void CSelectTreeCtrl::OnSetFocus(CWnd* pOldWnd) 
{
	CTreeCtrl::OnSetFocus(pOldWnd);

	if (::IsWindow(m_pParentDlg->GetSafeHwnd()))
		m_pParentDlg->SetTreeFocus(this);
}

void CSelectTreeCtrl::OnKillFocus(CWnd* pNewWnd) 
{
	CTreeCtrl::OnKillFocus(pNewWnd);

	if (::IsWindow(m_pParentDlg->GetSafeHwnd()))
		m_pParentDlg->SetTreeFocus(this);
}

void CSelectTreeCtrl::PreSubclassWindow() 
{
	CTreeCtrl::PreSubclassWindow();

	m_pParentDlg = (CCyberDlg*)GetParent();
//	m_pParentDlg = DYNAMIC_DOWNCAST(CCyberDlg, GetParent());
	ASSERT_VALID(m_pParentDlg);


// 	m_imageList.Create(16, 16, ILC_MASK|ILC_COLOR32, 1, 1);
// 	
// 	for (int i  = 0; i < _countof(treeIcons); i++)
// 	{
// 		HICON hIcon = AfxGetApp()->LoadIcon(treeIcons[i]);
// 		ASSERT(hIcon);
// 		
// 		m_imageList.Add (hIcon);
// 	}
	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_SHORTCUTS_SMALL);

	m_imageList.Create(16, 16, ILC_COLOR24|ILC_MASK, 8, 1);
	m_imageList.Add(&bitmap, RGB(0,255,0));

	HICON hIcon = AfxGetApp()->LoadIcon(IDI_IE);	
	ASSERT(hIcon);	 		
	m_imageList.Add (hIcon);

	hIcon = AfxGetApp()->LoadIcon(IDI_ICON_WORD);	
	ASSERT(hIcon);	 		
	m_imageList.Add (hIcon);

	SetImageList(&m_imageList, TVSIL_NORMAL);
}

void CSelectTreeCtrl::OnSelChanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	
	UNREFERENCED_PARAMETER(pNMTreeView);
	
	// TODO: Add your control notification handler code here
	//m_pParentDlg->EnableProperties();
	
	*pResult = 0;
}
