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
	//}}AFX_DATA_INIT
}


void CCustomCiHuiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustomCiHuiDlg)
	DDX_Text(pDX, IDC_EDIT_CIHUI_PATH, m_strBrowsePath);
	DDX_Check(pDX, IDC_CHECK_OVERCIHUI, m_bIsOverCiHui);
	DDX_Control(pDX, IDC_BUTTON_BROWSE_CIHUI, m_btnFolder);
	DDX_Control(pDX, IDC_BUTTON_CHECK_EXISTCIHUI, m_btnShowAllCihui);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCustomCiHuiDlg, CDialog)
	//{{AFX_MSG_MAP(CCustomCiHuiDlg)
	ON_BN_CLICKED(IDC_BUTTON_CHECK_EXISTCIHUI, OnButtonCheckExistcihui)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE_CIHUI, OnButtonBrowseCihui)
	ON_BN_CLICKED(IDC_CHECK_OVERCIHUI, OnCheckOvercihui)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
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
			MessageBox(g_lag.LoadString("message.selectwordsfile"),g_lag.LoadString("title.adddic"),MB_OK | MB_ICONWARNING);
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

	if( sloCommAgent::DoFileDialog(TRUE, szPath, FITER_TXT_XLS) )
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

	m_btnFolder.SetBitmap(0, IDB_BITMAP_FOLDER);
	m_btnFolder.SetFlatStyle(TRUE);
	
	m_btnShowAllCihui.SetBitmap(0, IDB_BITMAP_CHECK_CIHUI);

	// TODO: Add extra initialization here
	SetDlgItemText(IDC_STATIC_CUSTOM_CIHUI, g_lag.LoadString("label.customwords"));
	SetDlgItemText(IDC_STATIC_CIHUI_1, g_lag.LoadString("label.customwordsnote"));
	SetDlgItemText(IDC_STATIC_CIHUI_2, g_lag.LoadString("label.selectwordsfile"));
	SetDlgItemText(IDC_STATIC_CIHUI_3, g_lag.LoadString("label.existwordsnote"));
	SetDlgItemText(IDC_STATIC_IMPORT_CIHUI, g_lag.LoadString("label.importwords"));
	SetDlgItemText(IDC_CHECK_OVERCIHUI, g_lag.LoadString("label.overwords"));
	SetDlgItemText(IDC_BUTTON_CHECK_EXISTCIHUI, g_lag.LoadString("button.viewdic"));

	SetDlgItemText(IDOK, g_lag.LoadString("button.confirm"));
	SetDlgItemText(IDCANCEL, g_lag.LoadString("button.cancel"));

	//////////////////////////////////////////////////////////////////////////
	//设置静态文本框的字体
	f.CreatePointFont(FONT_SIZE,"黑体");//这种更简单
	((CStatic *)this->GetDlgItem(IDC_STATIC_CUSTOM_CIHUI))->SetFont(&f,true);
	((CStatic *)this->GetDlgItem(IDC_STATIC_IMPORT_CIHUI))->SetFont(&f,true);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CCustomCiHuiDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(pWnd-> GetDlgCtrlID() == IDC_STATIC_CUSTOM_CIHUI ||
		pWnd-> GetDlgCtrlID() == IDC_STATIC_IMPORT_CIHUI) 
	{ 
//		static   HBRUSH   hbrEdit   =   ::CreateSolidBrush(RGB(255,   255,   255)); 
//		pDC-> SetBkColor(RGB(255,   255,   255)); 
		pDC-> SetTextColor(RGB(0, 0, 255)); 
	} 
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CCustomCiHuiDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	COLORREF crColor = RGB(0, 0, 255);
	CPen NewPen,*pOldPen;
	switch(PEN_STYLE_DOT)
	{
	case PEN_STYLE_SOLID:
		NewPen.CreatePen(PS_SOLID,1,crColor);
		break;
	case PEN_STYLE_DASH:
		NewPen.CreatePen(PS_DASH,1,crColor);
		break;
	case PEN_STYLE_DOT:
		NewPen.CreatePen(PS_DOT,1,crColor);
		break;
	}
	pOldPen=dc.SelectObject(&NewPen);
	dc.MoveTo(120, 30);
	dc.LineTo(420, 30);
	
	dc.MoveTo(120, 102);
	dc.LineTo(420, 102);

	dc.SelectObject(pOldPen);
	// Do not call CDialog::OnPaint() for painting messages
}
