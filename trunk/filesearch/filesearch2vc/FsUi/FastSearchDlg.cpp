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
	//}}AFX_MSG_MAP
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

BOOL CFastSearchDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

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

	//等待keyWord.properties文件不存在时,从T_Result中取出数据,显示在界面上
	Sleep(200);
	int icount = 0;
	while(1 && icount < 10)
	{
		if (!m_agent.IsKeyFileExist())
		{
			break;
		}
		Sleep(200);
		icount++;
	}

	//从T_Result中取出数据
	if( m_agent.GetSearchRecords())
	{
		//显示在界面上
		int nCount = m_agent.m_RecList.size();
		for (int i = 0; i < nCount; i++)
		{
			SearchRectord sr;
			memcpy(&sr, &m_agent.m_RecList[i],sizeof(SearchRectord));

			//////////////////////////////////////////////////////////////////////////
			//显示到树中
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
