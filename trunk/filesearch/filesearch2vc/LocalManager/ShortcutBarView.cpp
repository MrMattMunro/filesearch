// ShortcutBarView.cpp : implementation of the CShortcutBarView class
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
#include "ShortcutBar.h"

#include "ShortcutBarDoc.h"
#include "ShortcutBarView.h"
#include "GroupDlg.h"
#include "sloCommAgent.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShortcutBarView

IMPLEMENT_DYNCREATE(CShortcutBarView, CXTListView)

BEGIN_MESSAGE_MAP(CShortcutBarView, CXTListView)
	//{{AFX_MSG_MAP(CShortcutBarView)
	ON_WM_CREATE()
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CXTListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CXTListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CXTListView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShortcutBarView construction/destruction

CShortcutBarView::CShortcutBarView()
{
	// TODO: add construction code here

}

CShortcutBarView::~CShortcutBarView()
{
}

BOOL CShortcutBarView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style |= LVS_REPORT;
	return CXTListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CShortcutBarView drawing

void CShortcutBarView::OnDraw(CDC* pDC)
{
	CShortcutBarDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (XTPPaintManager()->GetCurrentTheme() == xtpThemeOffice2003)
		pDC->Draw3dRect(CXTPClientRect(this), GetXtremeColor(XPCOLOR_FRAME), GetXtremeColor(XPCOLOR_FRAME));
	else
		pDC->Draw3dRect(CXTPClientRect(this), GetXtremeColor(COLOR_3DSHADOW), GetXtremeColor(COLOR_3DHIGHLIGHT));
}

/////////////////////////////////////////////////////////////////////////////
// CShortcutBarView printing

BOOL CShortcutBarView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CShortcutBarView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CShortcutBarView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CShortcutBarView diagnostics

#ifdef _DEBUG
void CShortcutBarView::AssertValid() const
{
	CXTListView::AssertValid();
}

void CShortcutBarView::Dump(CDumpContext& dc) const
{
	CXTListView::Dump(dc);
}

CShortcutBarDoc* CShortcutBarView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CShortcutBarDoc)));
	return (CShortcutBarDoc*)m_pDocument;
}
#endif //_DEBUG



/////////////////////////////////////////////////////////////////////////////
// CShortcutBarView message handlers
static int arHeaderBmps[] = {
	IDB_HEADER_1,
	IDB_HEADER_3
};

static int arColWidths[] = {
	24,
		21,
		60,
		180
};

static CString arColLabels[] = {
	_T(" "),
		_T(" "),
		_T("词汇名称"),
		_T("创建日期")
};

int CShortcutBarView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CXTListView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// Create the image list.
	if (!m_imageList.Create(IDB_ENV, 14, 1, RGB(0xFF,0x00,0xFF)))
		return -1;
	
	InitializeHeaderControl();
	InitializeListControl();
	m_flatHeader.SetTheme(0);
	
	SetExtendedStyle (LVS_EX_FULLROWSELECT);
	
//	SetMinimumColSize(5/*15*/);
	
	return 0;
}

bool CShortcutBarView::SortList(int /*nCol*/, bool /*bAscending*/)
{
	CXTSortClass csc (&GetListCtrl(), m_nSortedCol);
	csc.Sort (m_bAscending, xtSortString);
	return true;
}

void CShortcutBarView::InitializeHeaderControl()
{
	// Insert the columns.
	BuildColumns(_countof(arColWidths), arColWidths, arColLabels);
	
	// Subclass the flat header control.
	SubclassHeader(false);
	
	// add images to the header columns.
	int nCol;
	for (nCol = 0; nCol < _countof(arHeaderBmps); ++nCol) {
//		m_flatHeader.SetBitmap(nCol, arHeaderBmps[nCol]/*, HDF_STRING*/);
	}
	
	// use sort arrows.
	m_flatHeader.ShowSortArrow(TRUE);
}

void CShortcutBarView::InitializeListControl()
{
	// build a date string to insert into the list control.
	CTime tm = CTime::GetCurrentTime();
	CString strDay[] = { _T("Sun"),_T("Mon"),_T("Tue"),_T("Wed"),_T("Thr"),_T("Fri"),_T("Sat") };
	CString strTime;
	
	strTime.Format(_T("%s %d/%d/%d"), strDay[tm.GetDayOfWeek()-1],
		tm.GetMonth(), tm.GetDay(), tm.GetYear());
	
	// set the image list for the list control.
	CListCtrl& rList = GetListCtrl();
	rList.SetImageList(&m_imageList, LVSIL_SMALL);
	

	sloMysqlAgent::GetInstance()->GetKeyWordsFromDB(1, 0);
	int nCount = sloMysqlAgent::GetInstance()->m_KeywordsList.size();
	for(int i = 0; i < nCount; i++)
	{
		rList.InsertItem(i, NULL, 0);
		rList.SetItemText(i, 2, sloMysqlAgent::GetInstance()->m_KeywordsList[i].szKeyName);
		rList.SetItemText(0, 3, sloMysqlAgent::GetInstance()->m_KeywordsList[i].szDate);	
	}

	// insert the first item.
// 	rList.InsertItem(0, NULL, 0);
// 	rList.SetItemText(0, 2, _T("Codejock Software"));
// 	rList.SetItemText(0, 3, _T("Xtreme Toolkit has arrived!"));
// //	rList.SetItemText(0, 4, strTime);
// 	
// 	// inset the second item.
// 	rList.InsertItem(1, NULL, 0);
// 	rList.SetItemText(1, 2, _T("Joe Programmer"));
// 	rList.SetItemText(1, 3, _T("How can I create an Outlook style application?"));
// //	rList.SetItemText(1, 4, strTime);
	
	EnableUserSortColor(true);
	
	// enable autosizing for columns.
	m_flatHeader.EnableAutoSize();
	
	// lock the first two colums from sizing operations.
	m_flatHeader.FreezeColumn(0);
	m_flatHeader.FreezeColumn(1);
}


void CShortcutBarView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here
	CMenu menu;
	VERIFY(menu.LoadMenu(IDR_MENU_POPUP_LIST));
	
	UINT uFlags;
	ScreenToClient(&point);
	CListCtrl& rList = GetListCtrl();

	int nRet = m_flatHeader.HitTest(point);
	if (nRet != -1)
	{
		//选中list的标题栏
		return ;
	}

	nRet = rList.HitTest(point);
	if (nRet == -1)
	{
		//未选中
		ClientToScreen(&point);

		menu.GetSubMenu(0)->RemoveMenu(1, MF_BYPOSITION);
		menu.GetSubMenu(0)->RemoveMenu(1, MF_BYPOSITION);
		int nReturn = CXTPCommandBars::TrackPopupMenu(menu.GetSubMenu(0), TPM_LEFTALIGN|TPM_RETURNCMD|TPM_NONOTIFY,  point.x, point.y, this);
		
		switch (nReturn)
		{
		case ID_EDIT_ADD:
			{
				CGroupDlg groupdlg;
				int nRet = groupdlg.DoModal();
				if (nRet == 1)
				{
					int nCount = rList.GetItemCount();
					rList.InsertItem(nCount, NULL, 0);
					rList.SetItemText(nCount, 2, groupdlg.m_szGroupName);
					rList.SetItemText(nCount, 3, sloCommAgent::GetCurTime());
					//并更新数据库表
					CMainFrame* pFrameWnd = (CMainFrame*)GetParentFrame();
					ASSERT_KINDOF (CMainFrame, pFrameWnd);

					if( strlen(pFrameWnd->m_paneFolders.m_szTypeName) != 0 )
					{
						//选中子节点
						sloMysqlAgent::GetInstance()->AddKeyword(pFrameWnd->m_paneFolders.m_szTypeName, groupdlg.m_szGroupName);
					}
				}
			}
			break;		
		}
		return ;
	}

	//选中
	ClientToScreen(&point);
	
	int nReturn = CXTPCommandBars::TrackPopupMenu(menu.GetSubMenu(0), TPM_LEFTALIGN|TPM_RETURNCMD|TPM_NONOTIFY,  point.x, point.y, this);
	
	switch (nReturn)
	{
	case ID_EDIT_ADD:
		{
			CGroupDlg groupdlg;
			int nRet = groupdlg.DoModal();
			if (nRet == 1)
			{
				int nCount = rList.GetItemCount();
				rList.InsertItem(nCount, NULL, 0);
				rList.SetItemText(nCount, 2, groupdlg.m_szGroupName);
				rList.SetItemText(nCount, 3, sloCommAgent::GetCurTime());
				//并更新数据库表
				CMainFrame* pFrameWnd = (CMainFrame*)GetParentFrame();
				ASSERT_KINDOF (CMainFrame, pFrameWnd);
				
				if( strlen(pFrameWnd->m_paneFolders.m_szTypeName) != 0 )
				{
					//选中子节点
					sloMysqlAgent::GetInstance()->AddKeyword(pFrameWnd->m_paneFolders.m_szTypeName, groupdlg.m_szGroupName);
				}
			}
		}
		break;		
	case ID_EDIT_DEL:
		{
			if (6 == MessageBox("您确定删除该条记录？","词汇管理",MB_YESNO | MB_ICONWARNING))
			{
				//确定删除
				CListCtrl& rList = GetListCtrl();	
				int nItem = rList.GetSelectionMark();
				CString strDelKeyword = rList.GetItemText(nItem, 2);
				rList.DeleteItem(nItem);

				//删除数据库
				sloMysqlAgent::GetInstance()->DelKeyword(strDelKeyword.GetBuffer(0));

			}
		}
		break;		
	case ID_EDIT_MODIFY:		
		{
			CGroupDlg groupdlg;
			int nItem = rList.GetSelectionMark();
			CString strOldKeyword = rList.GetItemText(nItem, 2);
			groupdlg.SetDefaultValue(strOldKeyword.GetBuffer(0));	
			int nRet = groupdlg.DoModal();
			if (nRet == 1)
			{
				char* pTime = sloCommAgent::GetCurTime();
				rList.SetItemText(nItem, 2, groupdlg.m_szGroupName);
				rList.SetItemText(nItem, 3, pTime);
				//并更新数据库表
				sloMysqlAgent::GetInstance()->UpdateKeyword(strOldKeyword.GetBuffer(0), groupdlg.m_szGroupName, pTime);
			}
		}
		break;
	}
}

void CShortcutBarView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
// 	CListCtrl& rList = GetListCtrl();
// 	int nSelectIndex = rList.GetSelectionMark();
// 	CString strNum;
// 	CString strID;
// 	strNum = rList.GetItemText(nSelectIndex, 0);
// 	strID = rList.GetItemText(nSelectIndex, 1);	
	CXTListView::OnRButtonDown(nFlags, point);
}


//ntype 
// 1 显示组下所有类型的keywords
// 2 显示某种类型的keywords
void CShortcutBarView::ShowListContent(int nType, char* szGroupName)
{
	if (nType == 1)
	{
		sloMysqlAgent::GetInstance()->GetKeyWordsFromGroupName(szGroupName);
	}else if (nType == 2)
	{
		sloMysqlAgent::GetInstance()->GetKeyWordsFromTypeName(szGroupName);
	}

	CListCtrl& rList = GetListCtrl();

	//清空列表
	rList.DeleteAllItems();
	int nCount = sloMysqlAgent::GetInstance()->m_KeywordsList.size();
	for(int i = 0; i < nCount; i++)
	{
		rList.InsertItem(i, NULL, 0);
		rList.SetItemText(i, 2, sloMysqlAgent::GetInstance()->m_KeywordsList[i].szKeyName);
		rList.SetItemText(i, 3, sloMysqlAgent::GetInstance()->m_KeywordsList[i].szDate);	
	}
}