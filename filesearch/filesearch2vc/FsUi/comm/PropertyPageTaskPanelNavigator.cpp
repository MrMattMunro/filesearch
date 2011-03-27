// PropertyPageTaskPanelNavigator.cpp: implementation of the CPropertyPageTaskPanelNavigator class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FsUi.h"
#include "PropertyPageTaskPanelNavigator.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPropertyPageTaskPanelNavigator::CPropertyPageTaskPanelNavigator()
{

}

CPropertyPageTaskPanelNavigator::~CPropertyPageTaskPanelNavigator()
{

}

BOOL CPropertyPageTaskPanelNavigator::Create()
{
	CFont* pFont = m_pSheet->GetFont();
	
	if (!CXTPTaskPanel::Create(WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|WS_TABSTOP | WS_GROUP, CRect(0, 0, 0, 0), m_pSheet, 2))
		return FALSE;
	
	SetBehaviour(xtpTaskPanelBehaviourToolbox);
	SetTheme(xtpTaskPanelThemeShortcutBarOffice2003);
	SetSelectItemOnFocus(TRUE);
	
	SetIconSize(CSize(25, 25));
	SetGroupIconSize(CSize(55, 55));

	SetFont(pFont);
	
	CXTPTaskPanelGroup* pGroup = AddGroup(0);
	pGroup->SetCaption(_T("基本设置"));

	int i = 0;
	CXTPTaskPanelGroupItem* pItem = pGroup->AddLinkItem(0, i);
	pItem->SetCaption(_T("常规"));

	CXTPPropertyPage* pPage = m_pSheet->GetPage(0);
	pItem->SetItemData((DWORD_PTR)pPage);
	pPage->m_dwData = (DWORD_PTR)pItem;

	i = 1;
	pItem = pGroup->AddLinkItem(1, i);
	pItem->SetCaption(_T("词汇"));
	
	pPage = m_pSheet->GetPage(1);
	pItem->SetItemData((DWORD_PTR)pPage);
	pPage->m_dwData = (DWORD_PTR)pItem;

	pGroup = AddGroup(1);
	pGroup->SetCaption(_T("License管理"));

	i = 2;
	pItem = pGroup->AddLinkItem(0, i);
	pItem->SetCaption(_T("License信息"));
	
	pPage = m_pSheet->GetPage(2);
	pItem->SetItemData((DWORD_PTR)pPage);
	pPage->m_dwData = (DWORD_PTR)pItem;



	pGroup = AddGroup(2);
	pGroup->SetCaption(_T("状态和提醒"));


	int nMargin = 2;
	GetPaintManager()->m_rcItemOuterMargins.SetRect(nMargin, nMargin, nMargin, nMargin);

	Reposition();

//	m_pSheet->SetPageBorderStyle(xtpPageBorderFrame);
	
	return TRUE;
}

void CPropertyPageTaskPanelNavigator::OnPageSelected(CXTPPropertyPage* pPage)
{
	CXTPTaskPanelGroupItem* pItem = (CXTPTaskPanelGroupItem*)pPage->m_dwData;
	SetFocusedItem(pItem);
}

void CPropertyPageTaskPanelNavigator::SetFocusedItem(CXTPTaskPanelItem* pItem, BOOL bDrawFocusRect /*= FALSE*/, BOOL bSetFocus)
{
	if (m_pItemFocused != pItem && pItem && pItem->GetType() == xtpTaskItemTypeLink)
	{
		CXTPPropertyPage* pPage = (CXTPPropertyPage*)pItem->GetItemData();
		if (!m_pSheet->SetActivePage(pPage))
		{
			return;
		}
	}
	
	CXTPTaskPanel::SetFocusedItem(pItem, bDrawFocusRect, bSetFocus);
	
}