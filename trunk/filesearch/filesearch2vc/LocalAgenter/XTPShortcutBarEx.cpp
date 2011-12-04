// XTPShortcutBarEx.cpp: implementation of the CXTPShortcutBarEx class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LocalAgenter.h"
#include "XTPShortcutBarEx.h"
#include "LocalAgenterDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXTPShortcutBarEx::CXTPShortcutBarEx()
{

}

CXTPShortcutBarEx::~CXTPShortcutBarEx()
{

}
BEGIN_MESSAGE_MAP(CXTPShortcutBarEx, CXTPShortcutBar)
//{{AFX_MSG_MAP(CTabTreeFile)
	ON_WM_LBUTTONDOWN()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CXTPShortcutBarEx::OnLButtonDown(UINT nFlags, CPoint point)
{
	CXTPShortcutBarItem* pSelectedItem = GetHotItem();
	CLocalAgenterDlg* dlg = (CLocalAgenterDlg*)m_pParentWnd;
	if(pSelectedItem == dlg->m_pItemFolder)
	{
		//选中词汇列表项
		dlg->ShowListContent_Keywords(1, "全部");
	}else if (pSelectedItem == dlg->m_pItemCalendar)
	{
		//选中网址列表
		dlg->ShowListContent_Website("全部");
	}else if (pSelectedItem == dlg->m_pItemTasks)
	{
		//快捕列表项

	}

	CXTPShortcutBar::OnLButtonDown(nFlags, point);
}


void CXTPShortcutBarEx::SetParentWnd(LPVOID pParentWnd)
{
	m_pParentWnd = pParentWnd;
}