// FsUiTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FsUiTest.h"
#include "FsUiTestDlg.h"
#include "sloCreateIndexAgent.h"
#include "sloModifyIndexAgent.h"

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
// CFsUiTestDlg dialog

CFsUiTestDlg::CFsUiTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFsUiTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFsUiTestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFsUiTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFsUiTestDlg)
	DDX_Control(pDX, IDC_STATIC_GROUP, m_groupbox);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFsUiTestDlg, CDialog)
	//{{AFX_MSG_MAP(CFsUiTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	ON_BN_CLICKED(IDC_BUTTON9, OnButton9)
	ON_BN_CLICKED(IDC_BUTTON10, OnButton10)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFsUiTestDlg message handlers

BOOL CFsUiTestDlg::OnInitDialog()
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

void CFsUiTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFsUiTestDlg::OnPaint() 
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
HCURSOR CFsUiTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

typedef DWORD (__stdcall *fnFsCreateIndex)();
fnFsCreateIndex g_fnFsCreateIndex;

void CFsUiTestDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	HINSTANCE hins = LoadLibrary("FsUi.dll");
	if (!hins)
	{
		DWORD dwErr = GetLastError();
		MessageBox("Not Find FsUi.dll");
		return ;
	}

	g_fnFsCreateIndex = (fnFsCreateIndex)GetProcAddress(hins, "FsCreateIndex");
	if (!g_fnFsCreateIndex)
	{
		MessageBox("Not Find Func FsCreateIndex");
		return ;
	}

	g_fnFsCreateIndex();

//	FreeLibrary(hins);
}

typedef DWORD (__stdcall *fnFsModifyIndex)(int nID);
fnFsModifyIndex g_fnFsModifyIndex;
void CFsUiTestDlg::OnButton4() 
{
	// TODO: Add your control notification handler code here
	HINSTANCE hins = LoadLibrary("FsUi.dll");
	if (!hins)
	{
		DWORD dwErr = GetLastError();
		MessageBox("Not Find FsUi.dll");
		return ;
	}
	
	g_fnFsModifyIndex = (fnFsModifyIndex)GetProcAddress(hins, "FsModifyIndex");
	if (!g_fnFsModifyIndex)
	{
		MessageBox("Not Find Func FsCreateIndex");
		return ;
	}
	
	char szID[MAX_PATH] = {0};
	GetDlgItemText(IDC_EDIT_MODIFY_ID, szID, MAX_PATH);
	int nId = atoi(szID);
	g_fnFsModifyIndex(nId);

//	FreeLibrary(hins);	
}

typedef DWORD (__stdcall *fnFsImportCustomCiHui)();
fnFsImportCustomCiHui g_fnFsImportCustomCiHui;
void CFsUiTestDlg::OnButton6() 
{
	// TODO: Add your control notification handler code here
	HINSTANCE hins = LoadLibrary("FsUi.dll");
	if (!hins)
	{
		DWORD dwErr = GetLastError();
		MessageBox("Not Find FsUi.dll");
		return ;
	}
	
	g_fnFsImportCustomCiHui = (fnFsImportCustomCiHui)GetProcAddress(hins, "FsImportCustomCiHui");
	if (!g_fnFsImportCustomCiHui)
	{
		MessageBox("Not Find Func fnFsImportCustomCiHui");
		return ;
	}
	
	g_fnFsImportCustomCiHui();
	
//	FreeLibrary(hins);		
}

typedef DWORD (__stdcall *fnFsSetAttribute)();
fnFsSetAttribute g_fnFsSetAttribute;
void CFsUiTestDlg::OnButton7() 
{
	// TODO: Add your control notification handler code here
	HINSTANCE hins = LoadLibrary("FsUi.dll");
	if (!hins)
	{
		DWORD dwErr = GetLastError();
		MessageBox("Not Find FsUi.dll");
		return ;
	}
	
	g_fnFsSetAttribute = (fnFsSetAttribute)GetProcAddress(hins, "FsSetAttribute");
	if (!g_fnFsSetAttribute)
	{
		MessageBox("Not Find Func fnFsSetAttribute");
		return ;
	}
	
	g_fnFsSetAttribute();
	
//	FreeLibrary(hins);		
}

typedef DWORD (__stdcall *fnFsFastSearch)();
fnFsFastSearch g_fnFsFastSearch;
void CFsUiTestDlg::OnButton8() 
{
	// TODO: Add your control notification handler code here
	HINSTANCE hins = LoadLibrary("FsUi.dll");
	if (!hins)
	{
		DWORD dwErr = GetLastError();
		MessageBox("Not Find FsUi.dll");
		return ;
	}
	
	g_fnFsFastSearch = (fnFsFastSearch)GetProcAddress(hins, "FsFastSearch");
	if (!g_fnFsFastSearch)
	{
		MessageBox("Not Find Func fnFsFastSearch");
		return ;
	}
	
	g_fnFsFastSearch();
	
//	FreeLibrary(hins);		
}

typedef DWORD (__stdcall *fnFsSetSheet)();
fnFsSetSheet g_fnFsSetSheet;
void CFsUiTestDlg::OnButton9() 
{
	// TODO: Add your control notification handler code here
	HINSTANCE hins = LoadLibrary("FsUi.dll");
	if (!hins)
	{
		DWORD dwErr = GetLastError();
		MessageBox("Not Find FsUi.dll");
		return ;
	}
	
	g_fnFsSetSheet = (fnFsSetSheet)GetProcAddress(hins, "FsSetSheet");
	if (!g_fnFsSetSheet)
	{
		MessageBox("Not Find Func fnFsSetSheet");
		return ;
	}
	
	g_fnFsSetSheet();
	
//	FreeLibrary(hins);	
}

void GetDrvSpaceInfo(char* pDisk) 
{
	
	//获得选择的驱动器
	CString Driver = pDisk;
	
	//获得磁盘空间信息
	ULARGE_INTEGER FreeAv,TotalBytes,FreeBytes;
	if(GetDiskFreeSpaceEx(Driver,&FreeAv,&TotalBytes,&FreeBytes))
	{
		//格式化信息，并显示出来
		CString strTotalBytes,strFreeBytes;
		strTotalBytes.Format("%u字节",TotalBytes.QuadPart);
		strFreeBytes.Format("%u字节",FreeBytes.QuadPart);
		// 		CStatic* pTotalStatic = (CStatic*)GetDlgItem(IDC_TOTAL);
		// 		CStatic* pFreeStatic = (CStatic*)GetDlgItem(IDC_FREE);
		// 		pTotalStatic->SetWindowText(strTotalBytes);
		// 		pFreeStatic->SetWindowText(strFreeBytes);
	}
	
}

void FindAllDrivers()
{
//	CComboBox* Driver=(CComboBox*)GetDlgItem(IDC_DRIVER);
	DWORD dwNumBytesForDriveStrings;//实际存储驱动器号的字符串长度
	HANDLE hHeap;
	LPSTR lp;
	CString strLogdrive;
	
	//获得实际存储驱动器号的字符串长度
	dwNumBytesForDriveStrings=GetLogicalDriveStrings(0,NULL)*sizeof(TCHAR);
	
	//如果字符串不为空，则表示有正常的驱动器存在
	if (dwNumBytesForDriveStrings!=0) {
		//分配字符串空间
		hHeap=GetProcessHeap();
		lp=(LPSTR)HeapAlloc(hHeap,HEAP_ZERO_MEMORY,
			dwNumBytesForDriveStrings);
		
		//获得标明所有驱动器的字符串
		GetLogicalDriveStrings(HeapSize(hHeap,0,lp),lp);
		
		//将驱动器一个个放到下拉框中
		while (*lp!=0) {
			//Driver->AddString(lp);
			GetDrvSpaceInfo(lp);

			lp=_tcschr(lp,0)+1;
		}
	}

}


void CFsUiTestDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	//FindAllDrivers();
	sloCreateIndexAgent slinfo;
	slinfo.EventCreateIndex("c:\\1","*.txt,*.xls");
}

void CFsUiTestDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	CString strPath;
	CFileDialog hFileDlg(true,NULL ,
		NULL,
		OFN_FILEMUSTEXIST | OFN_READONLY | OFN_PATHMUSTEXIST,	
		TEXT("Text Files (.txt)|*.txt|Excel Files (.xls)|*.xls"),
		NULL);
	if(hFileDlg.DoModal() == IDOK)
	{
		strPath = hFileDlg.GetPathName();
		UpdateData(FALSE);
	}
	
	
}


void CFsUiTestDlg::OnButton5() 
{
	// TODO: Add your control notification handler code here
	sloModifyIndexAgent modifyAgent;
	modifyAgent.SetIndexID(3);
	modifyAgent.GetSearchInfo();
}



void CFsUiTestDlg::OnButton10() 
{
	// TODO: Add your control notification handler code here

	int i =800;
	for (i; i < 1500; i++)
	{
		char szOut[MAX_PATH] = {0};
		sprintf(szOut, "insert into t_recent_changeinfo(path, operflg,hasoper,systime,lastmodify) values('%d.doc', 2, 1, '2011-08-07 18:45:55', '2011-08-07 18:45:55');\r\n" ,i);
		OutputDebugString(szOut);
	}


	return ;

	CString strData;
	GetDlgItemText(IDC_EDIT_MODIFY_ID, strData);

	MessageBox(strData);
	int strLen = strData.GetLength();

	strData.TrimLeft(" ");
		MessageBox(strData);

	int strLen2 = strData.GetLength();
	return ;
	
	//ShellExecute(this->m_hWnd,"open","C:\\Program Files\\Microsoft Office\\OFFICE11\\WINWORD.EXE","\"D:\\slfile测试文件\\测试dir3\\1 2.doc\"","",SW_SHOW );	
	char szParam[_MAX_PATH+64]={0};
	strcpy(szParam,"/e,/select, ");
	strcat(szParam,"D:\\1.txt");
	ShellExecute(NULL,"open","explorer",szParam,NULL,SW_SHOW);

	
	//explorer.exe的 /select参数

}

HBRUSH CFsUiTestDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	


	// TODO: Change any attributes of the DC here
// 	if(pWnd->GetDlgCtrlID()==IDC_STATIC_GROUP) 
// 	{ 
// 		CRect rc; 
// 		m_groupbox.GetClientRect(&rc); 
// 		pDC->FillSolidRect(rc , RGB(0,255,255));//green 
// 		// Set the background mode for text to transparent  
// 		// so background will show thru. 
// 		pDC->SetBkMode(TRANSPARENT); 
// 	} 	

	// TODO: Return a different brush if the default is not desired
	return hbr;
}
