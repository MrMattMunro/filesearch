// LocalAgenterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LocalAgenter.h"
#include "LocalAgenterDlg.h"
#include "ReportRecord.h"

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
// CLocalAgenterDlg dialog

CLocalAgenterDlg::CLocalAgenterDlg(CWnd* pParent /*=NULL*/)
	: CXTResizeDialog(CLocalAgenterDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLocalAgenterDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLocalAgenterDlg::DoDataExchange(CDataExchange* pDX)
{
	CXTResizeDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLocalAgenterDlg)
	DDX_Control(pDX, IDC_BUTTON_EXPORT, m_buttonExport);
	DDX_Control(pDX, IDC_REPORTCTRL, m_wndReportCtrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLocalAgenterDlg, CXTResizeDialog)
	//{{AFX_MSG_MAP(CLocalAgenterDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLocalAgenterDlg message handlers
// enum
// {
// 	COLUMN_IMPORTANCE,
// 	COLUMN_ICON,
// 	COLUMN_ATTACHMENT,
// 	COLUMN_FROM,
// 	COLUMN_SUBJECT,
// 	COLUMN_SENT,
// 	COLUMN_SIZE,
// 	COLUMN_CHECK,
// 	COLUMN_PRICE,
// 	COLUMN_CREATED,
// 	COLUMN_RECEIVED,
// 	COLUMN_CONVERSATION,
// 	COLUMN_CONTACTS,
// 	COLUMN_MESSAGE,
// 	COLUMN_CC,
// 	COLUMN_CATEGORIES,
// 	COLUMN_AUTOFORWARD,
// 	COLUMN_DO_NOT_AUTOARCH,
// 	COLUMN_DUE_BY,
// };

enum
{
	COLUMN_ICON,
	COLUMN_BUTTON,
	COLUMN_SUBJECT,
	COLUMN_DATE,
};

static UINT shortcuts[] =
{
	ID_SHORTCUT_MAIL,
	ID_SHORTCUT_CALENDAR,
	ID_SHORTCUT_CONTACTS,
	ID_SHORTCUT_TASKS,
	ID_SHORTCUT_NOTES,
	ID_SHORTCUT_FOLDERS,
	ID_SHORTCUT_SHORTCUTS,
	ID_SHORTCUT_JOURNAL
};

BOOL CLocalAgenterDlg::OnInitDialog()
{
	CXTResizeDialog::OnInitDialog();

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
	SetIcon(m_hIcon, TRUE);         // Set big icon
	SetIcon(m_hIcon, FALSE);        // Set small icon

	// TODO: Add extra initialization here
	//////////////////////////////////////////////////////////////////////////
	//button
//	m_buttonExport.SetTheme(xtpButtonThemeOffice2007);
	m_buttonExport.SetIcon(CSize(8,8), AfxGetApp()->LoadIcon(IDI_OUTBOX));
	m_buttonExport.SetFlatStyle(TRUE);
//	m_buttonExport.SetUseVisualStyle(FALSE);
//	m_buttonExport.SetTextImageRelation(xtpButtonImageBeforeText);
	m_buttonExport.SetPushButtonStyle(xtpButtonDropDown);	
	//////////////////////////////////////////////////////////////////////////
	m_wndShortcutBar.Create(WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, CRect(5, 50, 180, 430),
		this,  100);
	
	m_wndShortcutBar.SetOwner(this);
	m_wndShortcutBar.GetToolTipContext()->SetStyle(xtpToolTipOffice);

	BOOL bUseAlphaIcons = XTPImageManager()->IsAlphaIconsSupported();
	
	XTPImageManager()->SetIcons(bUseAlphaIcons ? IDB_SHORTCUTS_SMALL_ALPHA : IDB_SHORTCUTS_SMALL, 
		shortcuts, sizeof(shortcuts)/sizeof(UINT), CSize(16, 16));
	
	XTPImageManager()->SetIcons(bUseAlphaIcons ? IDB_SHORTCUTS_BIG_ALPHA : IDB_SHORTCUTS_BIG, 
		shortcuts, sizeof(shortcuts)/sizeof(UINT), CSize(24, 24));

	VERIFY(m_paneCalendar.Create(_T("网址分类"), &m_wndShortcutBar));
	VERIFY(m_paneFolders.Create(_T("词汇分类"), &m_wndShortcutBar));
	m_paneFolders.SetParentWnd(this);
	m_paneCalendar.SetParentWnd(this);

	CXTPShortcutBarItem* pItemFolder = m_wndShortcutBar.AddItem(ID_SHORTCUT_FOLDERS, &m_paneFolders);
	pItemFolder->SetCaption("词汇管理");
	
	CXTPShortcutBarItem* pItemCalendar = m_wndShortcutBar.AddItem(ID_SHORTCUT_CALENDAR, &m_paneCalendar);
	pItemCalendar->SetCaption("网址管理");
	
	m_wndShortcutBar.AllowMinimize(TRUE);
	
	m_wndShortcutBar.SelectItem(pItemFolder);
	m_wndShortcutBar.LoadState(_T("ShortcutBar"));

	m_wndShortcutBar.SetTheme(xtpShortcutThemeOffice2007);

	//////////////////////////////////////////////////////////////////////////
	//
	m_wndReportCtrl.MoveWindow(CRect(190, 50, 685, 430), TRUE);

	m_wndReportCtrl.AddColumn(new CXTPReportColumn(COLUMN_ICON, _T(""), 18));
	m_wndReportCtrl.AddColumn(new CXTPReportColumn(COLUMN_BUTTON, _T(""), 18));
	m_wndReportCtrl.AddColumn(new CXTPReportColumn(COLUMN_SUBJECT, _T("名称"), 280));
	m_wndReportCtrl.AddColumn(new CXTPReportColumn(COLUMN_DATE, _T("时间"), 180));


	//
	// define style attributes for the report control.
	//
	
	m_wndReportCtrl.GetColumns()->Find(COLUMN_SUBJECT)->SetTreeColumn(TRUE);
	
	//
	// after columns and data have been added call Populate to 
	// populate all of the date for the control.
	//
	
	m_wndReportCtrl.Populate();
	
	m_wndReportCtrl.EnableDragDrop(_T("ReportDialog"), xtpReportAllowDrag | xtpReportAllowDrop);
	
	
	// Set control resizing.
	SetResize(IDC_REPORTCTRL, SZ_TOP_LEFT, SZ_BOTTOM_RIGHT);
	
	// Load window placement
	LoadPlacement(_T("CReportDialogDlg"));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLocalAgenterDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CXTResizeDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLocalAgenterDlg::OnPaint()
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
		CXTResizeDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLocalAgenterDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


//ntype 
// 1 显示组下所有类型的keywords
// 2 显示某种类型的keywords
void CLocalAgenterDlg::ShowListContent_Keywords(int nType, char* szGroupName)
{
	if (nType == 1)
	{
		sloMysqlAgent::GetInstance()->GetKeyWordsFromGroupName(szGroupName);
	}else if (nType == 2)
	{
		sloMysqlAgent::GetInstance()->GetKeyWordsFromTypeName(szGroupName);
	}
	
	//清空列表
	m_wndReportCtrl.ResetContent();
	int nCount = sloMysqlAgent::GetInstance()->m_KeywordsList.size();
	for(int i = 0; i < nCount; i++)
	{
		m_wndReportCtrl.AddRecord(new CReportRecord(sloMysqlAgent::GetInstance()->m_KeywordsList[i].szKeyName, sloMysqlAgent::GetInstance()->m_KeywordsList[i].szDate));
	}

	m_wndReportCtrl.Populate();
}

//ntype 
// 1 显示组下所有类型的keywords
// 2 显示某种类型的keywords
void CLocalAgenterDlg::ShowListContent_Website(char* szGroupName)
{
	sloMysqlAgent::GetInstance()->GetWebsiteFromGroupName(szGroupName);
	
	//清空列表
	m_wndReportCtrl.ResetContent();
	int nCount = sloMysqlAgent::GetInstance()->m_WebsiteList.size();
	for(int i = 0; i < nCount; i++)
	{
		m_wndReportCtrl.AddRecord(new CReportRecord(sloMysqlAgent::GetInstance()->m_WebsiteList[i].szSiteName, sloMysqlAgent::GetInstance()->m_WebsiteList[i].szDate));
	}

	m_wndReportCtrl.Populate();
}
