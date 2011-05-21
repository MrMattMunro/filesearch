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
	: CXTPPropertyPage(CSetAttributeDlg::IDD)/*CDialog(CSetAttributeDlg::IDD, pParent)*/
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
	DDX_Control(pDX, IDC_BUTTON_BROWSER_IE, m_btnFolderIE);
	DDX_Control(pDX, IDC_BUTTON_BROWSER_WORD, m_btnFolderWord);
	DDX_Control(pDX, IDC_BUTTON_BROWSER_EXCEL, m_btnFolderExcel);
	DDX_Control(pDX, IDC_BUTTON_BROWSER_PPT, m_btnFolderPPT);
	DDX_Control(pDX, IDC_BUTTON_BROWSER_PDF, m_btnFolderPdf);
	DDX_Control(pDX, IDC_BUTTON_BROWSER_TXT, m_btnFolderTxt);
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
	ON_WM_CTLCOLOR()
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

	m_btnFolderIE.SetBitmap(0, IDB_BITMAP_FOLDER2);
	m_btnFolderIE.SetFlatStyle(TRUE);	
	
	m_btnFolderWord.SetBitmap(0, IDB_BITMAP_FOLDER2);
	m_btnFolderWord.SetFlatStyle(TRUE);	

	m_btnFolderExcel.SetBitmap(0, IDB_BITMAP_FOLDER2);
	m_btnFolderExcel.SetFlatStyle(TRUE);	

	m_btnFolderPPT.SetBitmap(0, IDB_BITMAP_FOLDER2);
	m_btnFolderPPT.SetFlatStyle(TRUE);	

	m_btnFolderPdf.SetBitmap(0, IDB_BITMAP_FOLDER2);
	m_btnFolderPdf.SetFlatStyle(TRUE);	

	m_btnFolderTxt.SetBitmap(0, IDB_BITMAP_FOLDER2);
	m_btnFolderTxt.SetFlatStyle(TRUE);	
	// TODO: Add extra initialization here

	SetDlgItemText(IDC_STATIC_SOFT_SET, g_lag.LoadString("label.set"));
	SetDlgItemText(IDC_STATIC_SET_1, g_lag.LoadString("label.setnote"));

	SetDlgItemText(IDOK, g_lag.LoadString("button.confirm"));
	SetDlgItemText(IDCANCEL, g_lag.LoadString("button.cancel"));
	//////////////////////////////////////////////////////////////////////////

	char szPath[MAX_PATH] = {0};
	
	if(m_setAgent.GetSoftPath(IE_NAME,szPath) == 0 )
		m_strIE = szPath;

	memset(szPath, NULL, MAX_PATH);
	if(m_setAgent.GetSoftPath(WORD_NAME,szPath) == 0 )
		m_strWord = szPath;

	memset(szPath, NULL, MAX_PATH);
	if(m_setAgent.GetSoftPath(EXCEL_NAME,szPath) == 0 )
		m_strExcel = szPath;

	memset(szPath, NULL, MAX_PATH);
	if(m_setAgent.GetSoftPath(PPT_NAME,szPath) == 0 )
		m_strPPT = szPath;

	memset(szPath, NULL, MAX_PATH);
	if(m_setAgent.GetSoftPath(PDF_NAME,szPath) == 0 )
		m_strPdf = szPath;

	memset(szPath, NULL, MAX_PATH);
	if(m_setAgent.GetSoftPath(TXT_NAME,szPath) == 0 )
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
	if( sloCommAgent::DoFileDialog(szPath, FILTER_EXE, m_strIE.GetBuffer(0)) )
	{
		m_strIE = szPath;
		UpdateData(FALSE);

		SetModified();
	}
}

void CSetAttributeDlg::OnButtonBrowserWord() 
{
	// TODO: Add your control notification handler code here
	char szPath[MAX_PATH] = {0};
	if( sloCommAgent::DoFileDialog(szPath, FILTER_EXE, m_strWord.GetBuffer(0)) )
	{
		m_strWord = szPath;
		UpdateData(FALSE);
		SetModified();
	}	
}

void CSetAttributeDlg::OnButtonBrowserExcel() 
{
	// TODO: Add your control notification handler code here
	char szPath[MAX_PATH] = {0};
	if( sloCommAgent::DoFileDialog(szPath, FILTER_EXE, m_strExcel.GetBuffer(0)) )
	{
		m_strExcel = szPath;
		UpdateData(FALSE);
		SetModified();
	}	
}

void CSetAttributeDlg::OnButtonBrowserPpt() 
{
	// TODO: Add your control notification handler code here
	char szPath[MAX_PATH] = {0};
	if( sloCommAgent::DoFileDialog(szPath, FILTER_EXE, m_strPPT.GetBuffer(0)) )
	{
		m_strPPT = szPath;
		UpdateData(FALSE);
		SetModified();
	}	
}

void CSetAttributeDlg::OnButtonBrowserPdf() 
{
	// TODO: Add your control notification handler code here
	char szPath[MAX_PATH] = {0};
	if( sloCommAgent::DoFileDialog(szPath, FILTER_EXE, m_strPdf.GetBuffer(0)) )
	{
		m_strPdf = szPath;
		UpdateData(FALSE);
		SetModified();
	}	
}

void CSetAttributeDlg::OnButtonBrowserTxt() 
{
	// TODO: Add your control notification handler code here
	char szPath[MAX_PATH] = {0};
	if( sloCommAgent::DoFileDialog(szPath, FILTER_EXE,m_strTxt.GetBuffer(0)) )
	{
		m_strTxt = szPath;
		UpdateData(FALSE);
		SetModified();
	}	
}
extern DWORD g_dwApplyID;
BOOL CSetAttributeDlg::OnApply()
{
//	ASSERT_VALID(this);	
	if (g_dwApplyID == 1)
	{
		MessageBox("CSetAttributeDlg OnApply");
		
		UpdateData(TRUE);
		m_setAgent.GetProFilePath();
		
		sloCommAgent::WritePropertyfileString(IE_NAME,m_strIE.GetBuffer(0), m_setAgent.m_szpropertiesPath);
		sloCommAgent::WritePropertyfileString(WORD_NAME,m_strWord.GetBuffer(0), m_setAgent.m_szpropertiesPath);
		
		sloCommAgent::WritePropertyfileString(EXCEL_NAME,m_strExcel.GetBuffer(0), m_setAgent.m_szpropertiesPath);
		sloCommAgent::WritePropertyfileString(PPT_NAME,m_strPPT.GetBuffer(0), m_setAgent.m_szpropertiesPath);
		sloCommAgent::WritePropertyfileString(PDF_NAME,m_strPdf.GetBuffer(0), m_setAgent.m_szpropertiesPath);
		sloCommAgent::WritePropertyfileString(TXT_NAME,m_strTxt.GetBuffer(0), m_setAgent.m_szpropertiesPath);
		
		return TRUE;
	}

	return TRUE;
}

BOOL CSetAttributeDlg::OnSetActive()
{
	g_dwApplyID = 1;

	return CXTPPropertyPage::OnSetActive();
}

BOOL CSetAttributeDlg::OnKillActive()
{
	return CXTPPropertyPage::OnKillActive();
}

void CSetAttributeDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	m_setAgent.GetProFilePath();

	sloCommAgent::WritePropertyfileString(IE_NAME,m_strIE.GetBuffer(0), m_setAgent.m_szpropertiesPath);
	sloCommAgent::WritePropertyfileString(WORD_NAME,m_strWord.GetBuffer(0), m_setAgent.m_szpropertiesPath);

	sloCommAgent::WritePropertyfileString(EXCEL_NAME,m_strExcel.GetBuffer(0), m_setAgent.m_szpropertiesPath);
	sloCommAgent::WritePropertyfileString(PPT_NAME,m_strPPT.GetBuffer(0), m_setAgent.m_szpropertiesPath);
	sloCommAgent::WritePropertyfileString(PDF_NAME,m_strPdf.GetBuffer(0), m_setAgent.m_szpropertiesPath);
	sloCommAgent::WritePropertyfileString(TXT_NAME,m_strTxt.GetBuffer(0), m_setAgent.m_szpropertiesPath);

	CDialog::OnOK();
}

void CSetAttributeDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

HBRUSH CSetAttributeDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
// 	COLORREF backColor = RGB(216, 231, 252); //office 2003背景色
// 	pDC->SetBkMode(TRANSPARENT);             //设置控件背景透明
// 	
// 	// 判断下是不是你要改的控件ID 
// 	if( pWnd->GetDlgCtrlID() == IDCANCEL || pWnd->GetDlgCtrlID() == IDOK )
// 	{
// 		pDC->SetBkColor(RGB(153, 255, 204));
// 	}
// 	
// 	return CreateSolidBrush(backColor);      //创建背景刷子	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
