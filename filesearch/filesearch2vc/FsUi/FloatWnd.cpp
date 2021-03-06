// FloatWnd.cpp : implementation file
//

#include "stdafx.h"
#include "FsUi.h"
#include "FloatWnd.h"
#include "FsUi.h"
#include "sltHotkeyChangeThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFloatWnd dialog


CFloatWnd::CFloatWnd(CWnd* pParent /*=NULL*/)
	: CDialog(CFloatWnd::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFloatWnd)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CFloatWnd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFloatWnd)
	DDX_Control(pDX, IDC_LOGO, m_Logo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFloatWnd, CDialog)
	//{{AFX_MSG_MAP(CFloatWnd)
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_HIDE, OnHide)
	ON_COMMAND(ID_MENU_NEW_INDEX, OnMenuNewIndex)
	ON_COMMAND(ID_MENU_SYS_SET, OnMenuSysSet)
	ON_COMMAND(ID_MENU_WEB_QUERY, OnMenuWebQuery)
	ON_WM_NCHITTEST()
	ON_COMMAND(ID_MENU_TRANS_100, OnMenuTrans100)
	ON_COMMAND(ID_MENU_TRANS_20, OnMenuTrans20)
	ON_COMMAND(ID_MENU_TRANS_40, OnMenuTrans40)
	ON_COMMAND(ID_MENU_TRANS_60, OnMenuTrans60)
	ON_COMMAND(ID_MENU_TRANS_80, OnMenuTrans80)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_LOGO, OnLogo)
	ON_WM_LBUTTONDBLCLK()
	ON_MESSAGE(WM_HOTKEY,OnHotKey)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_MESSAGE(MSG_HOTCHANGE,OnHotKeyChange)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFloatWnd message handlers

BOOL CFloatWnd::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	flog.Print(LL_DEBUG_INFO,"[info]CFloatWnd::OnInitDialog!\r\n");


	nTickCount = GetTickCount();
#if 1
	CBitmap m_Bitmap;
	HBITMAP hBitmap = m_Logo.GetBitmap();
	ASSERT(hBitmap);
	
	m_Bitmap.Attach(hBitmap);
	BITMAP bmp;
	m_Bitmap.GetBitmap(&bmp);
	
	int nX = bmp.bmWidth;
	int nY = bmp.bmHeight;
	
	CRect rcDlgs;
	GetWindowRect(rcDlgs);   //得到对话框的Rect 对话框的大小
	ScreenToClient(rcDlgs);             //把屏幕的值转成相应的实际的值 
#endif
	int   cx   =   GetSystemMetrics(   SM_CXSCREEN   );  //获得屏幕的分辨率
	int   cy   =   GetSystemMetrics(   SM_CYSCREEN   );   
	
	int x = cx*0.9;
	int y = cy*0.1;

//  	int nX = 32;
// 	int nY = 32;
	MoveWindow(x,y,nX,nY);	
	m_Logo.MoveWindow(0,0,nX,nY);
	//CenterWindow();
	::SetWindowPos(m_hWnd,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE);

	m_Bitmap.Detach();
	
	//加入WS_EX_LAYERED扩展属性
	SetWindowLong(m_hWnd,GWL_EXSTYLE,GetWindowLong(this->GetSafeHwnd(),GWL_EXSTYLE)^0x80000);
	ModifyStyleEx(WS_EX_APPWINDOW,WS_EX_TOOLWINDOW, SWP_DRAWFRAME);

	RegHotKey();

	OnUpdateTransparent(255);

	sltHotkeyChangeThread::newInstance();
	sltHotkeyChangeThread::getInstance()->startup(this);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFloatWnd::RegHotKey()
{
	//获取系统热键值，并注册
	//从配置文件中获取hotkey，显示到界面
	WORD vk1= 0, sk1 = 0;
	WORD vk2= 0, sk2 = 0;
	m_hotkey.GetHotkey("fasts", vk1, sk1);
	m_hotkey.GetHotkey("webs", vk2, sk2);	
	
	UINT fs1 = 0;
	if (sk1 & HOTKEYF_ALT)	    fs1|= MOD_ALT;
	if (sk1 & HOTKEYF_CONTROL)   fs1|= MOD_CONTROL;
	if (sk1 & HOTKEYF_SHIFT) 	fs1|= MOD_SHIFT; 
	HWND hwnd = this->GetSafeHwnd();
	BOOL bRet = UnregisterHotKey(this->GetSafeHwnd(), 1);
	if(!RegisterHotKey(this->GetSafeHwnd(), 1, fs1, vk1))
	{
		MessageBox("快速查询的快捷键冲突，请重新设置快捷键!");
		DWORD dwError = GetLastError();
	}
	UINT fs2 = 0;
	if (sk2 & HOTKEYF_ALT)	    fs2|= MOD_ALT;
	if (sk2 & HOTKEYF_CONTROL)   fs2|= MOD_CONTROL;
	if (sk2 & HOTKEYF_SHIFT) 	fs2|= MOD_SHIFT; 
	
	bRet = UnregisterHotKey(this->GetSafeHwnd(), 2);	
	if(!RegisterHotKey(this->GetSafeHwnd(), 2, fs2, vk2))
	{
		MessageBox("web查询的快捷键冲突，请重新设置快捷键!");	
	}	
	
}

void CFloatWnd::OnUpdateTransparent(int iTransparent)
{
	HINSTANCE hInst = LoadLibrary("User32.DLL");
	if(hInst)
	{
		typedef BOOL (WINAPI *SLWA)(HWND,COLORREF,BYTE,DWORD);
		SLWA pFun = NULL;
		//取得SetLayeredWindowAttributes函数指针 
		pFun = (SLWA)GetProcAddress(hInst,"SetLayeredWindowAttributes");
		if(pFun)
		{
			pFun(m_hWnd,0,iTransparent,2);
		}
		FreeLibrary(hInst); 
	}
}

void CFloatWnd::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CMenu m_Right;
	m_Right.LoadMenu(IDR_MENU_FLOATWND);
	
	CMenu *pSub = m_Right.GetSubMenu(0);
	pSub->ModifyMenu(ID_MENU_NEW_INDEX,MF_BYCOMMAND,ID_MENU_NEW_INDEX, g_lag.LoadString("menu.newindex"));
	pSub->ModifyMenu(ID_MENU_SYS_SET,MF_BYCOMMAND,ID_MENU_SYS_SET, g_lag.LoadString("menu.sysseting"));
	pSub->ModifyMenu(ID_MENU_WEB_QUERY,MF_BYCOMMAND,ID_MENU_WEB_QUERY, g_lag.LoadString("menu.webs"));
	pSub->ModifyMenu(ID_HIDE,MF_BYCOMMAND,ID_HIDE, g_lag.LoadString("menu.hide"));

	ClientToScreen(&point);
	pSub->TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this,NULL);
	
	CDialog::OnRButtonUp(nFlags, point);
}

void CFloatWnd::OnHide() 
{
	// TODO: Add your command handler code here
	ShowWindow(SW_HIDE);
}

void CFloatWnd::OnMenuNewIndex() 
{
	// TODO: Add your command handler code here
	FsCreateIndex();
}

void CFloatWnd::OnMenuSysSet() 
{
	// TODO: Add your command handler code here
	FsSetSheet();
}

void CFloatWnd::OnMenuWebQuery() 
{
	// TODO: Add your command handler code here
	//处理菜单【更多...】消息 http://localhost:6666/slfile/load
	ShellExecute(NULL, "open", "http://localhost:6666/slfile/load", NULL, NULL,SW_SHOWNORMAL); 	
}

UINT CFloatWnd::OnNcHitTest(CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	UINT nHitTest = CDialog::OnNcHitTest(point);
	
	short keystate = ::GetAsyncKeyState(MK_LBUTTON);
	if (nHitTest == HTCLIENT &&
		::GetAsyncKeyState(MK_LBUTTON) < 0) // 如果鼠标左键按下，GetAsyncKeyState函数的返回值小于	
	{
		int nNextTickCount = GetTickCount();
		if (nNextTickCount - nTickCount <= 250)
		{
			//左键双击
			//MessageBox("dbclick");
			FsFastSearchEx();
		}else
		{
			nHitTest = HTCAPTION;
		}
		nTickCount = nNextTickCount;
	}
	
	return nHitTest;

//	return CDialog::OnNcHitTest(point);
}

#define MAX_TRANS_PARENT	255
void CFloatWnd::OnMenuTrans100() 
{
	// TODO: Add your command handler code here
	int nTransParent = MAX_TRANS_PARENT*1;
	OnUpdateTransparent(nTransParent);
}



void CFloatWnd::OnMenuTrans20() 
{
	// TODO: Add your command handler code here
	int nTransParent = MAX_TRANS_PARENT*0.2;
	OnUpdateTransparent(nTransParent);
}

void CFloatWnd::OnMenuTrans40() 
{
	// TODO: Add your command handler code here
	int nTransParent = MAX_TRANS_PARENT*0.4;
	OnUpdateTransparent(nTransParent);	
}

void CFloatWnd::OnMenuTrans60() 
{
	// TODO: Add your command handler code here
	int nTransParent = MAX_TRANS_PARENT*0.6;
	OnUpdateTransparent(nTransParent);		
}

void CFloatWnd::OnMenuTrans80() 
{
	// TODO: Add your command handler code here
	int nTransParent = MAX_TRANS_PARENT*0.8;
	OnUpdateTransparent(nTransParent);		
}

void CFloatWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
//	FsFastSearch();
	CDialog::OnLButtonDown(nFlags, point);
}

void CFloatWnd::OnLogo() 
{
	// TODO: Add your control notification handler code here
//	FsFastSearch();
}


void CFloatWnd::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
//	MessageBox("test");
//	FsFastSearch();

	CDialog::OnLButtonDblClk(nFlags, point);
}

LRESULT CFloatWnd::OnHotKey(WPARAM wp,LPARAM lp)   //热键处理函数
{
	switch(wp)
	{
	case 1:
		FsFastSearchEx();
		break;
		
	case 2:	 
		//处理菜单【更多...】消息 http://localhost:6666/slfile/load
		ShellExecute(NULL, "open", "http://localhost:6666/slfile/load", NULL, NULL,SW_SHOWNORMAL); 
		break;
	}
	
	return 0;
}

void CFloatWnd::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	UnregisterHotKey(m_hWnd, 1);
	UnregisterHotKey(m_hWnd, 2);
}

LRESULT CFloatWnd::OnHotKeyChange(WPARAM wp,LPARAM lp)
{
	RegHotKey();

	return 0;
}