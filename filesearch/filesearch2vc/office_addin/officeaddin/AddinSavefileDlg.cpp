// AddinSavefileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "officeaddin.h"
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
	
	HICON hIcon = AfxGetApp()->LoadIcon(IDI_ICON_FOLDER);
	ASSERT(hIcon);
	m_ilTreeIcons.Add (hIcon);
	
	//VERIFY(m_treeGroup.Create(WS_VISIBLE|TVS_LINESATROOT|TVS_HASBUTTONS|TVS_EDITLABELS |TVS_SHOWSELALWAYS, CXTPEmptyRect(), this, 0));
	m_treeGroup.SetImageList(&m_ilTreeIcons, TVSIL_NORMAL);
	
	//枚举applicationData目录下的slfile(C:\Documents and Settings\All Users\Application Data\slfile)，获取树基本信息
	BrowseFile(0, "D:\\test");
// 	HTREEITEM hItem;
// 	//获取分组个数
// 	int nGroupSize = 3;
// 	for (int i = 0; i < nGroupSize; i++)
// 	{
// 		hItem = m_treeGroup.InsertItem ("folder", 0, 0);
// 		//sloMysqlAgent::GetInstance()->GetTypesFromDB(sloMysqlAgent::GetInstance()->m_GroupList[i].nID);
// 		m_treeGroup.SetItemState (hItem, TVIS_BOLD, TVIS_BOLD);
// 		//获取该分组下得类型个数
// 		int nTypeSize = 2;
// 		for (int j = 0; j < nTypeSize; j++)
// 		{
// 			m_treeGroup.InsertItem ("subfolder", 1, 1, hItem);
// 		}
// 		m_treeGroup.Expand(hItem, TVE_EXPAND);
// 	}
// 	
// 	hItem = m_treeGroup.GetRootItem();
// 	m_treeGroup.SetItemState(hItem, TVIS_SELECTED, TVIS_SELECTED);
// 	//m_treeGroup.EnableMultiSelect(FALSE);
	
	UpdateData(FALSE);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAddinSavefileDlg::SetDcoumentPath(char* szFilePath)
{
	m_strDocpath = szFilePath;
}


void CAddinSavefileDlg::BrowseFile(int CallNum, CString strFile)
{
	CallNum++;
	CFileFind ff;
	CString szDir = strFile;
	
	if(szDir.Right(1) != "\\")
		szDir += "\\";
	
	szDir += "*.*";
	
	BOOL res = ff.FindFile(szDir);
	while(res)
	{
		res = ff.FindNextFile();
		if(ff.IsDirectory() && !ff.IsDots())
		{
			//如果是一个子目录，用递归继续往深一层找
			CString strPath = ff.GetFilePath();
			CString strTitle = ff.GetFileTitle();
			int i =0;
			switch(CallNum)
			{
			case 1:
				strHTFir = m_treeGroup.InsertItem(strTitle,0,0,NULL);						
				break;
			case 2:
				strHTSec = m_treeGroup.InsertItem(strTitle,0,0,strHTFir);											
				break;
			case 3:
				strHtThi = m_treeGroup.InsertItem(strTitle,0,0,strHTSec);					
				break;
			case 4:
				strHtFor = m_treeGroup.InsertItem(strTitle,0,0,strHtThi);					
				break;
			default:
				strHtFif = m_treeGroup.InsertItem(strTitle,0,0,strHtFor);
				break;					
			}
			BrowseFile(CallNum,strPath);
		}
		else if(!ff.IsDirectory() && !ff.IsDots())
		{
			//显示当前访问的文件
// 			CString strPath;
// 			CString strTitle;
// 			strPath = ff.GetFilePath();
// 			strTitle = ff.GetFileTitle();
// 			switch(CallNum)
// 			{
// 			case 1:
// 				strRoot = m_treeGroup.InsertItem(strTitle,0,0,NULL);
// 				break;
// 			case 2:
// 				strHtEnd = m_treeGroup.InsertItem(strTitle,0,0,strHTFir);
// 				break;
// 			case 3:
// 				strHtEnd = m_treeGroup.InsertItem(strTitle,0,0,strHTSec);				
// 				break;
// 			case 4:
// 				strHtEnd = m_treeGroup.InsertItem(strTitle,0,0,strHtThi);
// 				break;
// 			case 5:
// 				strHtEnd = m_treeGroup.InsertItem(strTitle,0,0,strHtFor);
// 				break;
// 			default:
// 				strHtEnd = m_treeGroup.InsertItem(strTitle,0,0,strHtFif);
// 				break;
// 			}
		}
	}
	ff.Close();//关闭
}

void CAddinSavefileDlg::OnOK() 
{
	// TODO: Add extra validation here
	//首先判断是否选中树
	HTREEITEM hItem = m_treeGroup.GetSelectedItem();
	if (hItem == NULL)
	{
		//提示需要选择目标目录
		MessageBox("请选择目标目录!");
		return ;
	}
	CString strDir = m_treeGroup.GetItemText(hItem);

	//将该文件地址写入dat文件，并向T_DOCUMENT加入一条记录
#if 0
	DocumentItem docitem;
	memset(&docitem, NULL, sizeof(DocumentItem));
	sloMysqlAgent::GetInstance()->AddDoucmentRecord(docitem);

#endif

	CDialog::OnOK();
}
