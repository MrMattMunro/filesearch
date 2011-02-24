// SetAttributeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FsUi.h"
#include "SetAttributeDlg.h"
#include "sloSetAttrAgent.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetAttributeDlg dialog


CSetAttributeDlg::CSetAttributeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetAttributeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetAttributeDlg)
	m_strExcel = _T("");
	m_strIE = _T("");
	m_strPdf = _T("");
	m_strPPT = _T("");
	m_strTxt = _T("");
	m_strWord = _T("");
	//}}AFX_DATA_INIT
}


void CSetAttributeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetAttributeDlg)
	DDX_Text(pDX, IDC_EDIT_EXCEL_PATH, m_strExcel);
	DDX_Text(pDX, IDC_EDIT_IE_PATH, m_strIE);
	DDX_Text(pDX, IDC_EDIT_PDF_PATH, m_strPdf);
	DDX_Text(pDX, IDC_EDIT_PPT_PATH, m_strPPT);
	DDX_Text(pDX, IDC_EDIT_TXT_PATH, m_strTxt);
	DDX_Text(pDX, IDC_EDIT_WORD_PATH, m_strWord);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetAttributeDlg, CDialog)
	//{{AFX_MSG_MAP(CSetAttributeDlg)
	ON_BN_CLICKED(IDC_BUTTON_BROWSER_IE, OnButtonBrowserIe)
	ON_BN_CLICKED(IDC_BUTTON_BROWSER_WORD, OnButtonBrowserWord)
	ON_BN_CLICKED(IDC_BUTTON_BROWSER_EXCEL, OnButtonBrowserExcel)
	ON_BN_CLICKED(IDC_BUTTON_BROWSER_PPT, OnButtonBrowserPpt)
	ON_BN_CLICKED(IDC_BUTTON_BROWSER_PDF, OnButtonBrowserPdf)
	ON_BN_CLICKED(IDC_BUTTON_BROWSER_TXT, OnButtonBrowserTxt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetAttributeDlg message handlers

#define IE_NAME		"html"
#define WORD_NAME	"word"
#define EXCEL_NAME	"excel"
#define PPT_NAME	"ppt"
#define PDF_NAME	"pdf"
#define TXT_NAME	"txt"
BOOL CSetAttributeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	sloSetAttrAgent set;
	char szPath[MAX_PATH] = {0};
	
	if(set.GetSoftPath(IE_NAME,szPath) == 0 )
		m_strIE = szPath;

	memset(szPath, NULL, MAX_PATH);
	if(set.GetSoftPath(WORD_NAME,szPath) == 0 )
		m_strWord = szPath;

	memset(szPath, NULL, MAX_PATH);
	if(set.GetSoftPath(EXCEL_NAME,szPath) == 0 )
		m_strExcel = szPath;

	memset(szPath, NULL, MAX_PATH);
	if(set.GetSoftPath(PPT_NAME,szPath) == 0 )
		m_strPPT = szPath;

	memset(szPath, NULL, MAX_PATH);
	if(set.GetSoftPath(PDF_NAME,szPath) == 0 )
		m_strPdf = szPath;

	memset(szPath, NULL, MAX_PATH);
	if(set.GetSoftPath(TXT_NAME,szPath) == 0 )
		m_strTxt = szPath;

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

#define FILTER_EXE TEXT("EXE Files (.exe)|*.exe|")
void CSetAttributeDlg::OnButtonBrowserIe() 
{
	// TODO: Add your control notification handler code here
	char szPath[MAX_PATH] = {0};
	if( sloCommAgent::DoFileDialog(szPath, FILTER_EXE) )
	{
		m_strIE = szPath;
		UpdateData(FALSE);
	}
}

void CSetAttributeDlg::OnButtonBrowserWord() 
{
	// TODO: Add your control notification handler code here
	char szPath[MAX_PATH] = {0};
	if( sloCommAgent::DoFileDialog(szPath, FILTER_EXE) )
	{
		m_strWord = szPath;
		UpdateData(FALSE);
	}	
}

void CSetAttributeDlg::OnButtonBrowserExcel() 
{
	// TODO: Add your control notification handler code here
	char szPath[MAX_PATH] = {0};
	if( sloCommAgent::DoFileDialog(szPath, FILTER_EXE) )
	{
		m_strExcel = szPath;
		UpdateData(FALSE);
	}	
}

void CSetAttributeDlg::OnButtonBrowserPpt() 
{
	// TODO: Add your control notification handler code here
	char szPath[MAX_PATH] = {0};
	if( sloCommAgent::DoFileDialog(szPath, FILTER_EXE) )
	{
		m_strPPT = szPath;
		UpdateData(FALSE);
	}	
}

void CSetAttributeDlg::OnButtonBrowserPdf() 
{
	// TODO: Add your control notification handler code here
	char szPath[MAX_PATH] = {0};
	if( sloCommAgent::DoFileDialog(szPath, FILTER_EXE) )
	{
		m_strPdf = szPath;
		UpdateData(FALSE);
	}	
}

void CSetAttributeDlg::OnButtonBrowserTxt() 
{
	// TODO: Add your control notification handler code here
	char szPath[MAX_PATH] = {0};
	if( sloCommAgent::DoFileDialog(szPath, FILTER_EXE) )
	{
		m_strTxt = szPath;
		UpdateData(FALSE);
	}	
}

void CSetAttributeDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CSetAttributeDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
