// SkinDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FsUi.h"
#include "SkinDlg.h"
#include "sloSkinAgent.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkinDlg dialog


CSkinDlg::CSkinDlg(CWnd* pParent /*=NULL*/)
	: CXTPPropertyPage(CSkinDlg::IDD)/*: CDialog(CSkinDlg::IDD, pParent)*/
{
	//{{AFX_DATA_INIT(CSkinDlg)
		// NOTE: the ClassWizard will add member initialization here
	memset(m_szSkinTheme, NULL, MAX_PATH);
	//}}AFX_DATA_INIT
}


void CSkinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSkinDlg)
	DDX_Control(pDX, IDC_LIST_SKIN, m_skinbox);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSkinDlg, CDialog)
	//{{AFX_MSG_MAP(CSkinDlg)
	ON_LBN_SELCHANGE(IDC_LIST_SKIN, OnSelchangeListSkin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkinDlg message handlers

BOOL CSkinDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetDlgItemText(IDC_STATIC_SKIN_SET, g_lag.LoadString("label.skinset"));
	SetDlgItemText(IDC_STATIC_SKIN_SELECT, g_lag.LoadString("label.selectskin"));
	SetDlgItemText(IDC_STATIC_SKIN_PREVIEW, g_lag.LoadString("label.skinpreview"));
	SetDlgItemText(IDC_STATIC_AUTHOR, g_lag.LoadString("label.skinauthor"));

	SetDlgItemText(IDC_STATIC_AUTHOR_NAME, g_lag.LoadString("label.skinauthorname"));
	SetDlgItemText(IDC_STATIC_HOMEPAGE, g_lag.LoadString("label.skinhomepage"));
	SetDlgItemText(IDC_STATIC_HOMEPAGE_NAME, g_lag.LoadString("label.skinhomepagename"));
	SetDlgItemText(IDC_STATIC_SKIN_EAMIL, g_lag.LoadString("label.skinemail"));
	SetDlgItemText(IDC_STATIC_SKIN_EAMIL_NAME, g_lag.LoadString("label.skinemailname"));

	m_skinbox.AddString("<默认皮肤>");
	m_skinbox.AddString("Office2007");
	m_skinbox.AddString("Vista");
	m_skinbox.AddString("WinXP.Royale");
	m_skinbox.AddString("WinXP.Luna");
	m_skinbox.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
extern DWORD g_dwApplyID;
extern sloSkinAgent	g_skin;
BOOL CSkinDlg::OnApply()
{
	//	ASSERT_VALID(this);	
	if (g_dwApplyID == 3)
	{
		MessageBox("CSkinDlg OnApply");
		//将主题写入文件，并更新主题
		if (strlen(m_szSkinTheme))
		{
			g_skin.UpdateSkin(m_szSkinTheme);
		}
		
		return TRUE;
	}
	
	return TRUE;
}

BOOL CSkinDlg::OnSetActive()
{
	g_dwApplyID = 3;
	
	return CXTPPropertyPage::OnSetActive();
}

BOOL CSkinDlg::OnKillActive()
{
	return CXTPPropertyPage::OnKillActive();
}

void CSkinDlg::OnSelchangeListSkin() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_skinbox.GetCurSel();
	CString strText;
	m_skinbox.GetText(nIndex, strText);
	memset(&m_szSkinTheme, NULL, MAX_PATH);
	memcpy(&m_szSkinTheme, strText.GetBuffer(0), strText.GetLength());

	SetModified();
	//变换预览图形
//	MessageBox(strText);


}
