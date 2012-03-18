// AddinSavefileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FsUi.h"
#include "AddinSavefileDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddinSavefileDlg dialog


CAddinSavefileDlg::CAddinSavefileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddinSavefileDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddinSavefileDlg)
	m_strDocpath = _T("");
	//}}AFX_DATA_INIT
}


void CAddinSavefileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddinSavefileDlg)
	DDX_Control(pDX, IDC_TREE_GROUP, m_treeGroup);
	DDX_Text(pDX, IDC_EDIT_PATH, m_strDocpath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddinSavefileDlg, CDialog)
	//{{AFX_MSG_MAP(CAddinSavefileDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddinSavefileDlg message handlers

BOOL CAddinSavefileDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_ilTreeIcons.Create(16, 16, ILC_MASK|ILC_COLOR32, 1, 1);
	
	HICON hIcon = AfxGetApp()->LoadIcon(IDI_ICON_HAND);
	ASSERT(hIcon);
	
	m_ilTreeIcons.Add (hIcon);

	//VERIFY(m_treeGroup.Create(WS_VISIBLE|TVS_LINESATROOT|TVS_HASBUTTONS|TVS_EDITLABELS |TVS_SHOWSELALWAYS, CXTPEmptyRect(), this, 0));
	m_treeGroup.SetImageList(&m_ilTreeIcons, TVSIL_NORMAL);

	//读取数据库，获取树基本信息

	HTREEITEM hItem;
	//获取分组个数
	int nGroupSize = 3;
	for (int i = 0; i < nGroupSize; i++)
	{
		hItem = m_treeGroup.InsertItem ("folder", 0, 0);
		//sloMysqlAgent::GetInstance()->GetTypesFromDB(sloMysqlAgent::GetInstance()->m_GroupList[i].nID);
		m_treeGroup.SetItemState (hItem, TVIS_BOLD, TVIS_BOLD);
		//获取该分组下得类型个数
		int nTypeSize = 2;
		for (int j = 0; j < nTypeSize; j++)
		{
			m_treeGroup.InsertItem ("subfolder", 0, 0, hItem);
		}
		m_treeGroup.Expand(hItem, TVE_EXPAND);
	}

	hItem = m_treeGroup.GetRootItem();
	m_treeGroup.SetItemState(hItem, TVIS_SELECTED, TVIS_SELECTED);
	m_treeGroup.EnableMultiSelect(FALSE);

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAddinSavefileDlg::SetDcoumentPath(char* szFilePath)
{
	m_strDocpath = szFilePath;
}
