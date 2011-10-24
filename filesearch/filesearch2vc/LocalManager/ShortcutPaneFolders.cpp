// ShortcutPaneFolders.cpp: implementation of the CShortcutPaneFolders class.
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
#include "shortcutbar.h"
#include "ShortcutPaneFolders.h"
#include "GroupDlg.h"
#include "MainFrm.h"
#include "ShortcutBarView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


static UINT treeIcons[] =
{
	IDI_INBOX           ,
	IDI_SEARCH          ,
	IDI_SENT_ITEMS      ,
	IDI_OUTBOX          ,
	IDI_OUTLOOK_TODAY   ,
	IDI_DELETED_ITEMS   ,
	IDI_DRAFTS          ,
	IDI_ARCHIVE         ,
	IDI_CALENDAR        ,
	IDI_CONTACTS
};
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CShortcutPaneFolders::CShortcutPaneFolders()
{
	m_ilTreeIcons.Create(16, 16, ILC_MASK|ILC_COLOR32, 1, 1);

	for (int i  = 0; i < _countof(treeIcons); i++)
	{
		HICON hIcon = AfxGetApp()->LoadIcon(treeIcons[i]);
		ASSERT(hIcon);

		m_ilTreeIcons.Add (hIcon);
	}

	m_bSelect = FALSE;
}

CShortcutPaneFolders::~CShortcutPaneFolders()
{

}


BOOL CShortcutPaneFolders::Create(LPCTSTR lpszCaption, CXTPShortcutBar* pParent)
{
	if (!CXTPShortcutBarPane::Create(lpszCaption, pParent))
		return FALSE;

	VERIFY(m_wndTreeFolders.Create(WS_VISIBLE|TVS_LINESATROOT|TVS_HASBUTTONS , CXTPEmptyRect(), this, 0));

	m_wndTreeFolders.SetImageList(&m_ilTreeIcons, TVSIL_NORMAL);


	//读取数据库，获取树基本信息
	sloMysqlAgent::GetInstance()->GetGroupsFromDB();
	HTREEITEM hItem;
	//获取分组个数
	int nGroupSize = sloMysqlAgent::GetInstance()->m_GroupList.size();
	for (int i = 0; i < nGroupSize; i++)
	{
		hItem = m_wndTreeFolders.InsertItem (sloMysqlAgent::GetInstance()->m_GroupList[i].szGroupName, 7, 7);
		sloMysqlAgent::GetInstance()->GetTypesFromDB(sloMysqlAgent::GetInstance()->m_GroupList[i].nID);
		//获取该分组下得类型个数
		int nTypeSize = sloMysqlAgent::GetInstance()->m_TypeList.size();
		for (int j = 0; j < nTypeSize; j++)
		{
			m_wndTreeFolders.InsertItem (sloMysqlAgent::GetInstance()->m_TypeList[j].szTypeName, 2, 2, hItem);
		}
		m_wndTreeFolders.Expand(hItem, TVE_EXPAND);
	}


// 	hItemDefault = m_wndTreeFolders.InsertItem (_T("默认分组"), 7, 7);
// 
// 	m_wndTreeFolders.InsertItem (_T("汽车"), 2, 2, hItemDefault);
// 	m_wndTreeFolders.InsertItem (_T("经济"), 2, 2, hItemDefault);
// 	m_wndTreeFolders.InsertItem (_T("交通"), 2, 2, hItemDefault);
// 	m_wndTreeFolders.InsertItem (_T("农业"), 2, 2, hItemDefault);
// 	m_wndTreeFolders.InsertItem (_T("娱乐"), 2, 2, hItemDefault);
// 	m_wndTreeFolders.InsertItem (_T("教育"), 2, 2, hItemDefault);
// 	m_wndTreeFolders.InsertItem (_T("法律"), 2, 2, hItemDefault);
// 	m_wndTreeFolders.InsertItem(_T("电影"), 2, 2, hItemDefault);

// 	HTREEITEM hItemSearch = m_wndTreeFolders.InsertItem (_T("自定义分组"), 1, 1, hItem);
// 	m_wndTreeFolders.InsertItem (_T("For Follow Up"), 1, 1, hItemSearch);
// 	m_wndTreeFolders.InsertItem (_T("Large Mail"), 1, 1, hItemSearch);
// 	m_wndTreeFolders.InsertItem (_T("Unread Mail"), 1, 1, hItemSearch);

//	m_wndTreeFolders.Expand(hItemDefault, TVE_EXPAND);

// 	hItemCustom = m_wndTreeFolders.InsertItem (_T("自定义分组"), 4, 4);
// 	m_wndTreeFolders.InsertItem (_T("食品"), 1, 1, hItemCustom);
// 	m_wndTreeFolders.InsertItem (_T("服装"), 1, 1, hItemCustom);

	hItem = m_wndTreeFolders.GetRootItem();
	m_wndTreeFolders.SetItemState(hItem, TVIS_SELECTED, TVIS_SELECTED);
	m_wndTreeFolders.EnableMultiSelect(FALSE);

	AddItem(_T("词汇列表"), &m_wndTreeFolders, 115);

	return TRUE;
}


BEGIN_MESSAGE_MAP(CShortcutPaneFolders, CXTPShortcutBarPane)
//{{AFX_MSG_MAP(CShortcutPaneFolders)
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_NOTIFY(TVN_SELCHANGED, 0, OnSelchanged)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CShortcutPaneFolders::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here
	CPoint pt;
	GetCursorPos(&pt);
	
 	UINT uFlags;
 	ScreenToClient(&pt);

	HTREEITEM hItemSelected = m_wndTreeFolders.GetSelectedItem();
	if (hItemSelected != NULL && m_bSelect)
	{
		m_bSelect = FALSE;
		CString strItemText = m_wndTreeFolders.GetItemText(hItemSelected);

		HTREEITEM hItemParent = m_wndTreeFolders.GetParentItem(hItemSelected);
		if (hItemParent == NULL)
		{
			//如果未选中父节点
			CMenu menu;
			VERIFY(menu.LoadMenu(IDR_MENU_POPUP_TREE_PARENT));
			ClientToScreen(&pt);
			int nReturn = CXTPCommandBars::TrackPopupMenu(menu.GetSubMenu(0), TPM_LEFTALIGN|TPM_RETURNCMD|TPM_NONOTIFY, pt.x, pt.y, this);
			
			switch (nReturn)
			{
			case ID_TREE_ADD_TYPE:
				//pItem->CopyToClipboard();
				//MessageBox("新增分组");
				CGroupDlg groupdlg;
				int nRet = groupdlg.DoModal();
				if (nRet == 1)
				{
					//点击确定
					m_wndTreeFolders.InsertItem(groupdlg.m_szGroupName, 2, 2, hItemSelected);				
					//并更新数据库表t_keywords_type
					sloMysqlAgent::GetInstance()->AddType(strItemText.GetBuffer(0), groupdlg.m_szGroupName);
				}
				break;		
			}
		}else
		{
			//如果选中父节点
			CMenu menu;
			VERIFY(menu.LoadMenu(IDR_MENU_POPUP_TREE_CHILD));
			ClientToScreen(&pt);
			int nReturn = CXTPCommandBars::TrackPopupMenu(menu.GetSubMenu(0), TPM_LEFTALIGN|TPM_RETURNCMD|TPM_NONOTIFY, pt.x, pt.y, this);
			
			switch (nReturn)
			{
			case ID_DEL_GROUP:
				//pItem->CopyToClipboard();
				{
					int nRet = MessageBox("您确认删除该分组？","删除分组", MB_YESNO | MB_ICONWARNING);
					if(6 == nRet)
					{
						m_wndTreeFolders.DeleteItem(hItemSelected);
						//并更新数据库表
						sloMysqlAgent::GetInstance()->DelType(strItemText.GetBuffer(0));
					}

				}
				break;	
			case ID_MODIFY_GROUP:
				//pItem->CopyToClipboard();
				{
					CGroupDlg groupdlg;
					groupdlg.SetDefaultValue(strItemText.GetBuffer(0));
 					int nRet = groupdlg.DoModal();
					if (nRet == 1)
					{
						m_wndTreeFolders.SetItemText(hItemSelected, groupdlg.m_szGroupName);
						//并写入数据库表
						sloMysqlAgent::GetInstance()->UpdateType(strItemText.GetBuffer(0), groupdlg.m_szGroupName);
					}
				}
				break;				
			}
		}
	}
	else
	{
		//选中空白位置，不显示菜单
		return;
	}
}

void CShortcutPaneFolders::OnSize(UINT nType, int cx, int cy)
{
	
	CXTPShortcutBarPane::OnSize(nType, cx, cy);
}


void CShortcutPaneFolders::OnSelchanged(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
	//clear report ctrl columns and content
	CMainFrame* pFrameWnd = (CMainFrame*)GetParentFrame();
	ASSERT_KINDOF (CMainFrame, pFrameWnd);

	// Get the selected tree item and its icon.
	//	int nImage;
	HTREEITEM htItem = m_wndTreeFolders.GetSelectedItem();
	if (htItem != NULL)
	{
		m_bSelect = TRUE;
		//		m_wndTreeCtrl.GetItemImage( htItem, nImage, nImage );
		
		// 		pFrameWnd->UpdateCaption(m_wndTreeCtrl.GetItemText( htItem ),
		// 			m_ilTreeIcons.ExtractIcon(nImage));
		CString strItemText = m_wndTreeFolders.GetItemText(htItem);
		m_wndTreeFolders.SelectItem(htItem);
		if(m_wndTreeFolders.ItemHasChildren(htItem))
		{
			//选中分组item
			pFrameWnd->m_pShortcutBarView->ShowListContent(1, strItemText.GetBuffer(0));
		}else
		{
			//选中类型item
			pFrameWnd->m_pShortcutBarView->ShowListContent(2, strItemText.GetBuffer(0));
		}

		//ShowRecords(wndReportCtrl, strItemText);
	}
	
	*pResult = 0;
	
}