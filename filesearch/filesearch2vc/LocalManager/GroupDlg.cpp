// GroupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "shortcutbar.h"
#include "GroupDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGroupDlg dialog


CGroupDlg::CGroupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGroupDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGroupDlg)
		// NOTE: the ClassWizard will add member initialization here
	memset(m_szGroupName, NULL, MAX_PATH);
	//}}AFX_DATA_INIT
}


void CGroupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGroupDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGroupDlg, CDialog)
	//{{AFX_MSG_MAP(CGroupDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGroupDlg message handlers

void CGroupDlg::OnOK() 
{
	// TODO: Add extra validation here

	GetDlgItemText(IDC_EDIT_GROUP_NAME, m_szGroupName, MAX_PATH);

	if (strlen(m_szGroupName) == 0)
	{
		MessageBox("名称不能空！", "分组管理", MB_OK | MB_ICONWARNING);

		return ;
	}

	CDialog::OnOK();
}

BOOL CGroupDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetDlgItemText(IDC_EDIT_GROUP_NAME, m_szGroupName);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGroupDlg::SetDefaultValue(char* pszName)
{
	memset(m_szGroupName, NULL, MAX_PATH);
	strcpy(m_szGroupName, pszName);
}