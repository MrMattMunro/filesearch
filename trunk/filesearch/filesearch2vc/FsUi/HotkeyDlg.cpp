// HotkeyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FsUi.h"
#include "HotkeyDlg.h"
#include "sltHotkeyChangeThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHotkeyDlg dialog


CHotkeyDlg::CHotkeyDlg(CWnd* pParent /*=NULL*/)
		: CXTPPropertyPage(CHotkeyDlg::IDD)/*: CDialog(CHotkeyDlg::IDD, pParent)*/
{
	//{{AFX_DATA_INIT(CHotkeyDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CHotkeyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHotkeyDlg)
	DDX_Control(pDX, IDC_HOTKEY_WEB_SEARCH, m_hotkeyWebs);
	DDX_Control(pDX, IDC_HOTKEY_FAST_SEARCH, m_hotkeyFasts);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHotkeyDlg, CDialog)
	//{{AFX_MSG_MAP(CHotkeyDlg)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_NOTIFY(NM_OUTOFMEMORY, IDC_HOTKEY_FAST_SEARCH, OnOutofmemoryHotkeyFastSearch)
	ON_BN_CLICKED(IDC_BUTTON_SET_HOTKEY, OnButtonSetHotkey)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHotkeyDlg message handlers

BOOL CHotkeyDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//////////////////////////////////////////////////////////////////////////
	//设置静态文本框的字体
	f.CreatePointFont(FONT_SIZE,"黑体");//这种更简单
	((CStatic *)this->GetDlgItem(IDC_STATIC_HOTKEY))->SetFont(&f,true);	

	SetDlgItemText(IDC_STATIC_HOTKEY, g_lag.LoadString("label.hotkeyset"));
	SetDlgItemText(IDC_STATIC_HOTKEY_DESC, g_lag.LoadString("label.hotkeynote"));
	SetDlgItemText(IDC_STATIC_HOTKEY_FAST_SEARCH, g_lag.LoadString("label.hotkeyfasts"));
	SetDlgItemText(IDC_STATIC_HOTKEY_WEB_SEARCH, g_lag.LoadString("label.hotkeywebs"));

	SetDlgItemText(IDC_BUTTON_SET_HOTKEY, g_lag.LoadString("button.hotkeyset"));

	//从配置文件中获取hotkey，显示到界面
	WORD vk1= 0, sk1 = 0;
	WORD vk2= 0, sk2 = 0;
	m_hotkey.GetHotkey("fasts", vk1, sk1);
	m_hotkey.GetHotkey("webs", vk2, sk2);

	m_hotkeyFasts.SetHotKey(vk1, sk1);	
	m_hotkeyWebs.SetHotKey(vk2, sk2);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CHotkeyDlg::OnPaint() 
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
	dc.SelectObject(pOldPen);	
	// Do not call CDialog::OnPaint() for painting messages
}

HBRUSH CHotkeyDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(pWnd-> GetDlgCtrlID()   ==   IDC_STATIC_HOTKEY) 
	{ 
		//		static   HBRUSH   hbrEdit   =   ::CreateSolidBrush(RGB(255,   255,   255)); 
		//		pDC-> SetBkColor(RGB(255,   255,   255)); 
		pDC-> SetTextColor(RGB(0, 0, 255)); 
	} 
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

extern DWORD g_dwApplyID;
BOOL CHotkeyDlg::OnApply()
{
	//	ASSERT_VALID(this);	
	if (g_dwApplyID == 4)
	{
		//将hotkey值写入.ini文件

		return TRUE;
	}
	
	return TRUE;
}

BOOL CHotkeyDlg::OnSetActive()
{
	g_dwApplyID = 4;

	return CXTPPropertyPage::OnSetActive();
}

BOOL CHotkeyDlg::OnKillActive()
{
	return CXTPPropertyPage::OnKillActive();
}

void CHotkeyDlg::OnOutofmemoryHotkeyFastSearch(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void CHotkeyDlg::OnButtonSetHotkey() 
{
	// TODO: Add your control notification handler code here
	//将hotkey值写入.ini文件
	UpdateData();

	WORD vk1, sk1,  vk2,sk2;
	m_hotkeyFasts.GetHotKey(vk1, sk1);
	m_hotkeyWebs.GetHotKey(vk2,sk2);
	
	m_hotkey.SaveHotkey("fasts", vk1, sk1);
	m_hotkey.SaveHotkey("webs", vk2, sk2);	
	
	//事件通知
	sltHotkeyChangeThread::getInstance()->addEvent();
}
