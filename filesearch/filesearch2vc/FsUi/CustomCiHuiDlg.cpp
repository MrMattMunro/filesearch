// CustomCiHuiDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FsUi.h"
#include "CustomCiHuiDlg.h"
#include "ShowAllCiHuiDlg.h"
#include "sloCustomCiHuiAgent.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomCiHuiDlg dialog


CCustomCiHuiDlg::CCustomCiHuiDlg(CWnd* pParent /*=NULL*/)
	: CXTPPropertyPage(CCustomCiHuiDlg::IDD)/*CDialog(CCustomCiHuiDlg::IDD, pParent)*/
{
	//{{AFX_DATA_INIT(CCustomCiHuiDlg)
	m_strBrowsePath = _T("");
	m_bIsOverCiHui = FALSE;
	m_dwApply = 0;
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
	ON_BN_CLICKED(IDC_CHECK_OVERCIHUI, OnCheckOvercihui)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomCiHuiDlg message handlers

extern DWORD g_dwApplyID;
BOOL CCustomCiHuiDlg::OnApply()
{
//	ASSERT_VALID(this);	

	if (g_dwApplyID == 2)
	{

		UpdateData(TRUE);
		
		if (!m_strBrowsePath.GetLength())
		{
			MessageBox("请选择词汇文件！","自定义词汇",MB_OK | MB_ICONWARNING);
			return TRUE;
		}
		
		sloCustomCiHuiAgent cihui;
		cihui.EventCustomCiHui(m_bIsOverCiHui, m_strBrowsePath.GetBuffer(0));
		
		return TRUE;
	}
	
	return TRUE;
}

BOOL CCustomCiHuiDlg::OnSetActive()
{
	g_dwApplyID = 2;
	return CXTPPropertyPage::OnSetActive();
}

BOOL CCustomCiHuiDlg::OnKillActive()
{
	return CXTPPropertyPage::OnKillActive();
}

void CCustomCiHuiDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	
	sloCustomCiHuiAgent cihui;
	cihui.EventCustomCiHui(m_bIsOverCiHui, m_strBrowsePath.GetBuffer(0));

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
	CShowAllCiHuiDlg AllCihui;
	AllCihui.DoModal();
}

#define FITER_TXT_XLS TEXT("Text Files (.txt)|*.txt|Excel Files (.xls)|*.xls")
void CCustomCiHuiDlg::OnButtonBrowseCihui() 
{
	// TODO: Add your control notification handler code here
	char szPath[MAX_PATH] = {0};

	if( sloCommAgent::DoFileDialog(szPath, FITER_TXT_XLS) )
	{
		m_strBrowsePath = szPath;
		UpdateData(FALSE);
			
		SetModified();
	}
}

void CCustomCiHuiDlg::OnCheckOvercihui() 
{
	// TODO: Add your control notification handler code here
	SetModified();
}

BOOL CCustomCiHuiDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CString strCustomCihui, strCihui1, strCihui2,strCihui3;
	CString strImportCihui,strOverCihui, strCheckAll,strOk, strCancel;
	
	strCustomCihui.LoadString(IDS_CUSTOM_CIHUI);
	strCihui1.LoadString(IDS_CIHUI_1);
	strCihui2.LoadString(IDS_CIHUI_2);
	strCihui3.LoadString(IDS_CIHUI_3);
	strImportCihui.LoadString(IDS_IMPORT_CIHUI);
	strOverCihui.LoadString(IDS_CHECK_OVERCIHUI);
	strCheckAll.LoadString(IDS_CHECK_EXISTCIHUI);

	strOk.LoadString(IDS_OK);
	strCancel.LoadString(IDS_CANCEL);
	
	SetDlgItemText(IDC_STATIC_CUSTOM_CIHUI, strCustomCihui);
	SetDlgItemText(IDC_STATIC_CIHUI_1, strCihui1);
	SetDlgItemText(IDC_STATIC_CIHUI_2, strCihui2);
	SetDlgItemText(IDC_STATIC_CIHUI_3, strCihui3);
	SetDlgItemText(IDC_STATIC_IMPORT_CIHUI, strImportCihui);
	SetDlgItemText(IDC_CHECK_OVERCIHUI, strOverCihui);
	SetDlgItemText(IDC_BUTTON_CHECK_EXISTCIHUI, strCheckAll);

	SetDlgItemText(IDOK, strOk);
	SetDlgItemText(IDCANCEL, strCancel);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
