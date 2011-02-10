// CustomCiHuiDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FsUi.h"
#include "CustomCiHuiDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomCiHuiDlg dialog


CCustomCiHuiDlg::CCustomCiHuiDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCustomCiHuiDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCustomCiHuiDlg)
	m_strBrowsePath = _T("");
	m_bIsOverCiHui = FALSE;
	//}}AFX_DATA_INIT
}


void CCustomCiHuiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustomCiHuiDlg)
	DDX_Text(pDX, IDC_EDIT_CIHUI_PATH, m_strBrowsePath);
	DDX_Check(pDX, IDC_CHECK_OVERCIHUI, m_bIsOverCiHui);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCustomCiHuiDlg, CDialog)
	//{{AFX_MSG_MAP(CCustomCiHuiDlg)
	ON_BN_CLICKED(IDC_BUTTON_CHECK_EXISTCIHUI, OnButtonCheckExistcihui)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE_CIHUI, OnButtonBrowseCihui)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomCiHuiDlg message handlers

void CCustomCiHuiDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CCustomCiHuiDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CCustomCiHuiDlg::OnButtonCheckExistcihui() 
{
	// TODO: Add your control notification handler code here
	
}

void CCustomCiHuiDlg::OnButtonBrowseCihui() 
{
	// TODO: Add your control notification handler code here
	CFileDialog hFileDlg(true,NULL ,
		NULL,
		OFN_FILEMUSTEXIST | OFN_READONLY | OFN_PATHMUSTEXIST,	
		TEXT("Text Files (.txt)|*.txt|Excel Files (.xls)|*.xls"),
		NULL);
	if(hFileDlg.DoModal() == IDOK)
	{
		m_strBrowsePath = hFileDlg.GetPathName();
		UpdateData(FALSE);
	}	
}
