// DirMonitorTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DirMonitorTest.h"
#include "DirMonitorTestDlg.h"

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
// CDirMonitorTestDlg dialog

CDirMonitorTestDlg::CDirMonitorTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDirMonitorTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDirMonitorTestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDirMonitorTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDirMonitorTestDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDirMonitorTestDlg, CDialog)
	//{{AFX_MSG_MAP(CDirMonitorTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDirMonitorTestDlg message handlers
typedef DWORD (__stdcall *fnMonitor_Start_Dir)(char* pszDirPath, DWORD dwLen);
typedef DWORD (__stdcall *fnMonitor_Start_AllDisk)(BOOL bRemovableDisk);
typedef DWORD (__stdcall *fnMonitor_Stop)();
typedef DWORD (__stdcall *fnMonitor_Start)();
fnMonitor_Start_AllDisk g_fnMonitor_Start_AllDisk;
fnMonitor_Stop g_fnMonitor_Stop;
fnMonitor_Start_Dir g_fnMonitor_Start_Dir;
fnMonitor_Start g_fnMonitor_Start;
HINSTANCE g_hinstance;
BOOL CDirMonitorTestDlg::OnInitDialog()
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
	g_hinstance = LoadLibraryA("FileMonitor.dll");
	DWORD dwerr = GetLastError();
	if (!g_hinstance)
	{
		OutputDebugString("DirMonitor.dll�ļ�δ�ҵ�!");
		return TRUE;
	}

	g_fnMonitor_Start_AllDisk = (fnMonitor_Start_AllDisk)GetProcAddress(g_hinstance, "Monitor_Start_AllDisk");
	g_fnMonitor_Stop = (fnMonitor_Stop)GetProcAddress(g_hinstance, "Monitor_Stop");
	g_fnMonitor_Start_Dir = (fnMonitor_Start_Dir)GetProcAddress(g_hinstance, "Monitor_Start_Dir");
	g_fnMonitor_Start = (fnMonitor_Start)GetProcAddress(g_hinstance, "Monitor_Start");
	if (!g_fnMonitor_Start_AllDisk || 
		!g_fnMonitor_Stop || 
		!g_fnMonitor_Start_Dir ||
		!g_fnMonitor_Start)
	{
		return TRUE;
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDirMonitorTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDirMonitorTestDlg::OnPaint() 
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
HCURSOR CDirMonitorTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CDirMonitorTestDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	if (!g_fnMonitor_Start_AllDisk)
	{
		return ;
	}
	g_fnMonitor_Start_AllDisk(FALSE);

}

void CDirMonitorTestDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	if (!g_fnMonitor_Stop)
	{
		return ;
	}
	g_fnMonitor_Stop();	
}

void CDirMonitorTestDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	if (!g_fnMonitor_Start_Dir)
	{
		return ;
	}
	g_fnMonitor_Start_Dir("D:\\test1", 8);
}

void CDirMonitorTestDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	g_fnMonitor_Stop();

	FreeLibrary(g_hinstance);

	CDialog::OnClose();
}


void CDirMonitorTestDlg::OnButton4() 
{
	// TODO: Add your control notification handler code here
	char string[] = "xyzabc";
	int  pos;
	
	pos = strcspn( string, "yaf" );
	std::string str1 = "xyzabc";
	pos = str1.find("abcf");

}

void CDirMonitorTestDlg::OnButton5() 
{
	// TODO: Add your control notification handler code here
	if (!g_fnMonitor_Start)
	{
		return ;
	}
	g_fnMonitor_Start();	
}

void CDirMonitorTestDlg::OnButton6() 
{
	// TODO: Add your control notification handler code here
	WIN32_FIND_DATA ffd ;
	HANDLE hFind = FindFirstFile("C:\\1.doc",&ffd);
	SYSTEMTIME stUTC, stLocal;
	FileTimeToSystemTime(&(ffd.ftLastWriteTime), &stUTC);
	SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);
	CString myTime;
	myTime.Format("%d. %d %d, %d:%d", stLocal.wDay,stLocal.wMonth,stLocal.wYear,stLocal.wHour,stLocal.wMinute);
	//--
	
}
