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
	SetTheme(xtpTaskPanelThemeShortcutBarOffice2007);


	CXTPPaintManager::SetTheme( xtpThemeRibbon);
	SetSelectItemOnFocus(TRUE);
	
	SetIconSize(CSize(18, 18));
//	SetGroupIconSize(CSize(55, 55));

	SetFont(pFont);
	
	//添加基本设置group
	CXTPTaskPanelGroup* pGroup = AddGroup(0,IDI_ICON_SET_TOOLS);
	pGroup->SetCaption(g_lag.LoadString("title.basicset"));

	//添加常规item
	int i = 0;
	CXTPTaskPanelGroupItem* pItem = pGroup->AddLinkItem(0, IDI_ICON_SYS_SET);
	pItem->SetCaption(g_lag.LoadString("title.general"));

	CXTPPropertyPage* pPage = m_pSheet->GetPage(0);
	pItem->SetItemData((DWORD_PTR)pPage);
	pPage->m_dwData = (DWORD_PTR)pItem;

	//添加词汇item
	i = 1;
	pItem = pGroup->AddLinkItem(1, IDI_ICON_CIHUI2);
	pItem->SetCaption(g_lag.LoadString("title.words"));
	
	pPage = m_pSheet->GetPage(1);
	pItem->SetItemData((DWORD_PTR)pPage);
	pPage->m_dwData = (DWORD_PTR)pItem;

	//添加皮肤item
	i = 2;
	pItem = pGroup->AddLinkItem(2, IDI_ICON_CIHUI2);
	pItem->SetCaption(g_lag.LoadString("title.skin"));
	
	pPage = m_pSheet->GetPage(2);
	pItem->SetItemData((DWORD_PTR)pPage);
	pPage->m_dwData = (DWORD_PTR)pItem;

	//添加注册管理group
	pGroup = AddGroup(1,IDI_ICON_REG_INFO);
	pGroup->SetCaption(g_lag.LoadString("title.licensemanager"));

	//添加注册信息item
	i = 2;
	pItem = pGroup->AddLinkItem(0, IDI_ICON_REG_MANAGER);
	pItem->SetCaption(g_lag.LoadString("title.licenseinfo"));
	
	pPage = m_pSheet->GetPage(3);
	pItem->SetItemData((DWORD_PTR)pPage);
	pPage->m_dwData = (DWORD_PTR)pItem;

//	pGroup = AddGroup(2);
//	pGroup->SetCaption(_T("状态和提醒"));

	int nMargin = 2;
	GetPaintManager()->m_rcItemOuterMargins.SetRect(nMargin, nMargin, nMargin, nMargin);

	Reposition();

	GetImageManager()->SetIcon(IDI_ICON_SYS_SET, IDI_ICON_SYS_SET);
	GetImageManager()->SetIcon(IDI_ICON_SET_NORMAL, IDI_ICON_SET_NORMAL);
	GetImageManager()->SetIcon(IDI_ICON_SET_TOOLS, IDI_ICON_SET_TOOLS);
	GetImageManager()->SetIcon(IDI_ICON_CIHUI, IDI_ICON_CIHUI);
	GetImageManager()->SetIcon(IDI_ICON_CIHUI1, IDI_ICON_CIHUI1);
	GetImageManager()->SetIcon(IDI_ICON_CIHUI2, IDI_ICON_CIHUI2);
	GetImageManager()->SetIcon(IDI_ICON_REG_INFO, IDI_ICON_REG_INFO);
	GetImageManager()->SetIcon(IDI_ICON_REG_MANAGER, IDI_ICON_REG_MANAGER);	
	GetImageManager()->SetIcon(IDI_ICON_REG_MANAGE2, IDI_ICON_REG_MANAGE2);

//	SetGroupIconSize( CSize(16, 24));
	SetGroupIconSize( CSize(24, 48));

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