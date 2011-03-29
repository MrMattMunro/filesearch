// LicenseDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FsUi.h"
#include "LicenseDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLicenseDlg dialog


CLicenseDlg::CLicenseDlg(CWnd* pParent /*=NULL*/)
	: CXTPPropertyPage(CLicenseDlg::IDD)/*CDialog(CLicenseDlg::IDD, pParent)*/
{
	//{{AFX_DATA_INIT(CLicenseDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CLicenseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLicenseDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLicenseDlg, CDialog)
	//{{AFX_MSG_MAP(CLicenseDlg)
	ON_BN_CLICKED(IDC_BUTTON_REG, OnButtonReg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLicenseDlg message handlers

void CLicenseDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CLicenseDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL CLicenseDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLicenseDlg::OnButtonReg() 
{
	// TODO: Add your control notification handler code here
	
}
