// FastSearchDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FsUi.h"
#include "FastSearchDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFastSearchDlg dialog


CFastSearchDlg::CFastSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFastSearchDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFastSearchDlg)
	m_strKey = _T("");
	m_pSearchThread = NULL;
	//}}AFX_DATA_INIT
}


void CFastSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFastSearchDlg)
	DDX_Control(pDX, IDC_COMBO_PATH, m_BoxList);
	DDX_Text(pDX, IDC_EDIT_SEARCH_KEY, m_strKey);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFastSearchDlg, CDialog)
	//{{AFX_MSG_MAP(CFastSearchDlg)
	ON_CBN_EDITCHANGE(IDC_COMBO_PATH, OnEditchangeComboPath)
	ON_EN_CHANGE(IDC_EDIT_SEARCH_KEY, OnChangeEditSearchKey)
	ON_CBN_SELCHANGE(IDC_COMBO_PATH, OnSelchangeComboPath)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_PROGRESS_MSG, OnProgressChange)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFastSearchDlg message handlers

void CFastSearchDlg::OnEditchangeComboPath() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_BoxList.GetCurSel();		//得到被选中内容索引
	CString m_strtemp;						//存放得到的编辑框内容
	m_BoxList.GetLBText(nIndex,m_strtemp);	//得到被选中内容的名字
}

void CFastSearchDlg::SetWinPos()
{
	CRect rcDlgs;
	GetWindowRect(rcDlgs);   //得到对话框的Rect 对话框的大小
	ScreenToClient(rcDlgs);             //把屏幕的值转成相应的实际的值 
	
	int   cx   =   GetSystemMetrics(   SM_CXSCREEN   );  //获得屏幕的分辨率
	int   cy   =   GetSystemMetrics(   SM_CYSCREEN   );   

	//cx cy,就是屏幕最右下角的x,y的值 
	MoveWindow(cx-rcDlgs.Width(),cy-rcDlgs.Height(),rcDlgs.Width(),rcDlgs.Height(),TRUE);   // 

	//MoveWindow的参数前两个是对话框的x,y位置  
	//三四个是对话框的大小 ，最后以个不用管！ 
	SetWindowPos(&wndTopMost,cx-rcDlgs.Width(),cy-rcDlgs.Height()-30,rcDlgs.Width(),rcDlgs.Height(),SWP_NOSIZE); 
}

BOOL CFastSearchDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetWinPos();

	if (m_agent.GetAllPath() == 0)
	{
		int nSize = m_agent.m_PathList.size();
		for (int i =0 ; i < nSize; i++)
		{
			m_BoxList.AddString(m_agent.m_PathList[i].c_str());
		}
	}
	m_BoxList.InsertString(0,"全部");
	m_BoxList.SelectString(0,"全部");

	CreateTaskPanel();

	//循环显示group
	AddToolboxGroup(1,"控制面板");
	AddToolboxGroup(2,"文档");
	AddToolboxGroup(3,"图片");

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFastSearchDlg::OnChangeEditSearchKey() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CString strKey;
	GetDlgItemText(IDC_EDIT_SEARCH_KEY, strKey);

	if (m_agent.IsKeyFileExist())
	{
		return ;
	}

	//不存在的场合将用户输入的关键字写入
	//keyWord.properties文件,格式如下:
	//keyword=
	//id=
	int nIndex = m_BoxList.GetCurSel();		//得到被选中内容索引
	CString strtemp;						//存放得到的编辑框内容
	m_BoxList.GetLBText(nIndex,strtemp);	//得到被选中内容的名字
	sloCommAgent::WritePropertyfileString("keyword", strKey.GetBuffer(0), m_agent.m_szKeyPath);
	sloCommAgent::WritePropertyfileString("path", strtemp.GetBuffer(0), m_agent.m_szKeyPath);
	if (NULL == m_pSearchThread)
	{
		OutputDebugString("AfxBeginThread ");
		m_pSearchThread = (CSearchThread*)AfxBeginThread(RUNTIME_CLASS(CSearchThread), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED , 0);		
		m_pSearchThread->m_hParentWnd = this->GetSafeHwnd();
		m_pSearchThread->ResumeThread();
	}	

	OutputDebugString("post WM_SEARCH_MSG ");
	if( m_pSearchThread->PostThreadMessage(WM_SEARCH_MSG, 0, 0) )
	{
		OutputDebugString("PostThreadMessage succ");
	}else
	{	
		OutputDebugString("PostThreadMessage failed");
		m_pSearchThread->PostThreadMessage(WM_SEARCH_MSG, 0, 0);
	}

}

void CFastSearchDlg::OnProgressChange(WPARAM wParam, LPARAM lParam)
{
	OutputDebugString("OnProgressChange");

	//清空LinkItem
	m_wndTaskPanel.GetGroups()->Clear(FALSE);

	//从T_Result中取出数据
	if( m_agent.GetSearchRecords() == 0)
	{
		//显示在界面上
		int nCount = m_agent.m_RecList.size();
		for (int i = 0; i < nCount; i++)
		{
			SearchRectord sr;
			memcpy(&sr, &m_agent.m_RecList[i],sizeof(SearchRectord));
						
			//////////////////////////////////////////////////////////////////////////
			//显示到树中
			AddLinkItem(1, 1,1,sr.szFileName);
		}
	}
}

void CFastSearchDlg::OnSelchangeComboPath() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_BoxList.GetCurSel();		//得到被选中内容索引
	CString m_strtemp;						//存放得到的编辑框内容
	m_BoxList.GetLBText(nIndex,m_strtemp);	//得到被选中内容的名字

}


BOOL CFastSearchDlg::CreateTaskPanel()
{
	
	if (!m_wndTaskPanel.Create(WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|WS_TABSTOP, CRect(5, 5, 358, 480), this, 1))
		return FALSE;
	
	m_wndTaskPanel.SetOwner(this);
	
	//	m_wndTaskPanel.GetImageManager()->SetIcons(IDB_TOOLBOXICONS, 0, 0, CSize(16, 16));
	m_wndTaskPanel.SetIconSize(CSize(25, 25));
	m_wndTaskPanel.SetBehaviour(xtpTaskPanelBehaviourExplorer/*xtpTaskPanelBehaviourToolbox*/);
	m_wndTaskPanel.SetTheme(xtpTaskPanelThemeOfficeXPPlain/*xtpTaskPanelThemeToolbox*/);
	m_wndTaskPanel.SetSelectItemOnFocus(TRUE);
	m_wndTaskPanel.AllowDrag(TRUE);
 
	return TRUE;
}

 
CXTPTaskPanelGroup* CFastSearchDlg::CreateToolboxGroup(UINT nID)
{
	CXTPTaskPanelGroup* pFolder = m_wndTaskPanel.AddGroup(nID);
	
	CXTPTaskPanelGroupItem* pPointer = pFolder->AddLinkItem(1, 0);
	pPointer->SetItemSelected(TRUE);
	pPointer->AllowDrag(FALSE);
	pPointer->AllowDrop(FALSE);
	pFolder->SetIconIndex(0);
	
	return pFolder;
}

void CFastSearchDlg::AddToolboxGroup(UINT nID, LPCTSTR lpszCaption)
{
	CXTPTaskPanelGroup* pFolder = m_wndTaskPanel.AddGroup(nID);	
	pFolder->SetCaption(lpszCaption);
	m_listMap[nID] = pFolder;
}

void CFastSearchDlg::AddLinkItem(UINT nFolderID, UINT nItemID, int nIconIndex, LPCTSTR lpszCaption)
{

	CXTPTaskPanelGroup* pFolder = m_listMap[nFolderID];
	if (!pFolder)
	{
		return ;
	}

	CXTPTaskPanelGroupItem* pPointer = pFolder->AddLinkItem(nItemID, 0);
	pPointer->SetCaption(lpszCaption);
	pPointer->SetItemSelected(TRUE);
	pPointer->AllowDrag(FALSE);
	pPointer->AllowDrop(FALSE);
	pFolder->SetIconIndex(nIconIndex);
}


CXTPTaskPanelGroup* pFolderData = NULL;
void CFastSearchDlg::ResetToolboxItems()
{
	m_wndTaskPanel.GetGroups()->Clear(FALSE);
	
	CXTPTaskPanelGroup* pFolderPropertyPanes = CreateToolboxGroup(0);
	
	/*	CXTPTaskPanelGroup**/ pFolderData = CreateToolboxGroup(1);
	pFolderData->AddLinkItem(1,-1);
	
	
	CXTPTaskPanelGroup* pFolderComponents = CreateToolboxGroup(2);
	//pFolderComponents->AddLinkItem(ID_TOOLBOXITEM_BUTTON,-1);
	
	//	CreateToolboxGroup(3);
	//	CreateToolboxGroup(4);
	
	pFolderPropertyPanes->SetExpanded(TRUE);
	
}

void CFastSearchDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	if (NULL != m_pSearchThread)
	{
		m_pSearchThread->PostThreadMessage(WM_QUIT, 0, 0);
		Sleep(100);
	}
}
