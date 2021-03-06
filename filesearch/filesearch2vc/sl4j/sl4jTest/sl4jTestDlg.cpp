// sl4jTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "sl4jTest.h"
#include "sl4jTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSl4jTestDlg dialog

CSl4jTestDlg::CSl4jTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSl4jTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSl4jTestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSl4jTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSl4jTestDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSl4jTestDlg, CDialog)
	//{{AFX_MSG_MAP(CSl4jTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSl4jTestDlg message handlers

BOOL CSl4jTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSl4jTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSl4jTestDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSl4jTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

typedef DWORD (__stdcall *fnMsgBox)(char* pText, char* pCaption, unsigned int uType);
fnMsgBox g_fnMsgBox;
void CSl4jTestDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	HINSTANCE hr = LoadLibrary("sl4j.dll");
	if (!hr)
	{
		MessageBox("sl4j.dll not find");
		return ;
	}

	g_fnMsgBox = (fnMsgBox)GetProcAddress(hr, "MsgBox");
	if (!g_fnMsgBox)
	{
		MessageBox("sl4j.dll func MsgBox not find");
		return ;
	}

	g_fnMsgBox("\u5bf9\u8c61\u6587\u6863\u7c7b\u578b\uff1a", "caption", MB_OK | MB_ICONQUESTION);

	FreeLibrary(hr);
}
typedef DWORD (__stdcall *fnDoExe)(char* szPath);
fnDoExe g_fnDoExe;
void CSl4jTestDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	HINSTANCE hr = LoadLibrary("sl4j.dll");
	if (!hr)
	{
		MessageBox("sl4j.dll not find");
		return ;
	}
	
	g_fnDoExe = (fnDoExe)GetProcAddress(hr, "DoExe");
	if (!g_fnDoExe)
	{
		MessageBox("sl4j.dll func DoExe not find");
		return ;
	}
	
	g_fnDoExe("c:\\1.exe");
	
	FreeLibrary(hr);	
}

typedef DWORD (__stdcall *fncreateRecentIndexPath)();
fncreateRecentIndexPath g_fncreateRecentIndexPath;
void CSl4jTestDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	HINSTANCE hr = LoadLibrary("sl4j.dll");
	if (!hr)
	{
		MessageBox("sl4j.dll not find");
		return ;
	}
	
	g_fncreateRecentIndexPath = (fncreateRecentIndexPath)GetProcAddress(hr, "createRecentIndexPath");
	if (!g_fncreateRecentIndexPath)
	{
		MessageBox("sl4j.dll func fncreateRecentIndexPath not find");
		return ;
	}
	
	g_fncreateRecentIndexPath();
	
	FreeLibrary(hr);		
}
