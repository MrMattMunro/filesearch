// ShortcutBarView.h : interface of the CShortcutBarView class
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

#if !defined(AFX_SHORTCUTBARVIEW_H__4EDCFEEE_955B_424A_A169_A0051F97868C__INCLUDED_)
#define AFX_SHORTCUTBARVIEW_H__4EDCFEEE_955B_424A_A169_A0051F97868C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class CShortcutBarDoc;

class CShortcutBarView /*: public CView*/ : public CXTPOfficeBorder<CXTListView>
{
protected: // create from serialization only
	CShortcutBarView();
	DECLARE_DYNCREATE(CShortcutBarView)

// Attributes
public:
	CShortcutBarDoc* GetDocument();
	void ShowListContent(int nType, char* szGroupName);
	void ShowListContent_Website(char* szGroupName);


	//////////////////////////////////////////////////////////////////////////
	void OnMenuEvent_Add();
	void OnMenuEvent_Del();
	void OnMenuEvent_Update();
// Operations
public:
	CImageList  m_imageList;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShortcutBarView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

	virtual bool SortList(int nCol, bool bAscending);
	void InitializeHeaderControl();
	void InitializeListControl();
	void SetRedrawEx(BOOL bRedraw);
	


// Implementation
public:
	virtual ~CShortcutBarView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CShortcutBarView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

#ifndef _DEBUG  // debug version in ShortcutBarView.cpp
inline CShortcutBarDoc* CShortcutBarView::GetDocument()
	{ return (CShortcutBarDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHORTCUTBARVIEW_H__4EDCFEEE_955B_424A_A169_A0051F97868C__INCLUDED_)
