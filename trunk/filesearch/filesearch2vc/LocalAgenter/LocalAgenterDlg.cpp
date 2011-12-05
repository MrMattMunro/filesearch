// LocalAgenterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LocalAgenter.h"
#include "LocalAgenterDlg.h"
#include "ReportRecord.h"
#include "sloCommAgent.h"
#include "sloMysqlAgent.h"
#include "CyberDlg.h"

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
	m_bCommboxAllSel = FALSE;
	m_pItemFolder= NULL;
	m_pItemCalendar = NULL;
	m_pColumn4 = NULL;
}

void CLocalAgenterDlg::DoDataExchange(CDataExchange* pDX)
{
	CXTResizeDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLocalAgenterDlg)
	DDX_Control(pDX, IDC_BUTTON_SEARCH, m_btnSearch);
	DDX_Control(pDX, IDC_COMBO_TIME, m_BoxListTime);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_BoxListType);
	DDX_Control(pDX, IDC_COMBO_GROUP, m_BoxListGroup);
	DDX_Control(pDX, IDC_BUTTON_SET, m_btnSet);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_btnDelete);
	DDX_Control(pDX, IDC_BUTTON_EXPORT, m_buttonExport);
	DDX_Control(pDX, IDC_REPORTCTRL, m_wndReportCtrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLocalAgenterDlg, CXTResizeDialog)
	//{{AFX_MSG_MAP(CLocalAgenterDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_EXPORT, OnButtonExport)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_SET, OnButtonSet)
	ON_CBN_EDITCHANGE(IDC_COMBO_GROUP, OnEditchangeComboGroup)
	ON_CBN_SELCHANGE(IDC_COMBO_GROUP, OnSelchangeComboGroup)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, OnButtonSearch)
	ON_WM_CONTEXTMENU()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_CONTROL_RANGE(CBN_DROPDOWN, IDC_BUTTON_EXPORT, IDC_BUTTON_EXPORT, OnButtonDropDown)
	ON_NOTIFY(XTP_NM_REPORT_ITEMBUTTONCLICK, IDC_REPORTCTRL, OnItemButtonClick)
	ON_NOTIFY(XTP_NM_REPORT_BEGINEDIT, IDC_REPORTCTRL, OnBeginEdit)
	ON_NOTIFY(XTP_NM_REPORT_VALUECHANGED, IDC_REPORTCTRL, OnValueChanged)
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
	COLUMN_BUTTON1,
	COLUMN_BLACK1,
	COLUMN_BUTTON2,
	COLUMN_BLACK2,
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
	InitButton();

	//////////////////////////////////////////////////////////////////////////
	//commbox
	InitComboBox();

	//////////////////////////////////////////////////////////////////////////
	InitShortcutBar();

	//////////////////////////////////////////////////////////////////////////
	//
	InitReportCtrl();


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

void CLocalAgenterDlg::InitButton()
{
	//button
	//	m_buttonExport.SetTheme(xtpButtonThemeOffice2007);
	//	m_buttonExport.SetIcon(CSize(8,8), AfxGetApp()->LoadIcon(IDI_OUTBOX));
	m_buttonExport.SetBitmap(CSize(24,24), IDB_BITMAP_EXPORT);
	m_buttonExport.SetFlatStyle(TRUE);
	//	m_buttonExport.SetUseVisualStyle(FALSE);
	//	m_buttonExport.SetTextImageRelation(xtpButtonImageBeforeText);
	m_buttonExport.SetPushButtonStyle(xtpButtonSplitDropDown);	
	
	m_btnDelete.SetBitmap(CSize(24,24), IDB_BITMAP_DELETE);
	m_btnDelete.SetFlatStyle(TRUE);
	
	m_btnSet.SetBitmap(CSize(24,24), IDB_BITMAP_SET);
	m_btnSet.SetFlatStyle(TRUE);
	
	m_btnSearch.SetBitmap(CSize(24,24), IDB_BITMAP_SEARCH);
	m_btnSearch.SetFlatStyle(TRUE);
}

void CLocalAgenterDlg::InitComboBox()
{
	m_BoxListGroup.ResetContent(); // Clean up all contents	
	m_BoxListGroup.InsertString(0, "全部");
	m_BoxListGroup.InsertString(1, "词汇列表");
	m_BoxListGroup.InsertString(2, "网址列表");
	m_BoxListGroup.SetCurSel(0);
	
	m_BoxListType.ResetContent(); // Clean up all contents	
	m_BoxListType.InsertString(0, "默认分组");
	m_BoxListType.InsertString(1, "自定义分组");
	m_BoxListType.InsertString(2, "财经网址");
	m_BoxListType.SetCurSel(0);
	
	m_BoxListTime.ResetContent(); // Clean up all contents	
	m_BoxListTime.InsertString(0, "最近一周");
	m_BoxListTime.InsertString(1, "最近三个月");
	m_BoxListTime.InsertString(2, "最近一年");
	m_BoxListTime.InsertString(3, "全部");
	m_BoxListTime.SetCurSel(0);
	
	SetComboxPos(TRUE);
	
}

#define LENGHT_BAR 450
void CLocalAgenterDlg::InitShortcutBar()
{
	m_wndShortcutBar.Create(WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, CRect(5, 50, 180, LENGHT_BAR),
		this,  100);
	
	m_wndShortcutBar.SetOwner(this);
	m_wndShortcutBar.GetToolTipContext()->SetStyle(xtpToolTipOffice);
	m_wndShortcutBar.SetParentWnd(this);
	
	BOOL bUseAlphaIcons = XTPImageManager()->IsAlphaIconsSupported();
	
	XTPImageManager()->SetIcons(bUseAlphaIcons ? IDB_SHORTCUTS_SMALL_ALPHA : IDB_SHORTCUTS_SMALL, 
		shortcuts, sizeof(shortcuts)/sizeof(UINT), CSize(16, 16));
	
	XTPImageManager()->SetIcons(bUseAlphaIcons ? IDB_SHORTCUTS_BIG_ALPHA : IDB_SHORTCUTS_BIG, 
		shortcuts, sizeof(shortcuts)/sizeof(UINT), CSize(24, 24));
	
	VERIFY(m_paneFolders.Create(_T("词汇分类"), &m_wndShortcutBar));
	VERIFY(m_paneCalendar.Create(_T("网址分类"), &m_wndShortcutBar));
	VERIFY(m_paneTasks.Create(_T("网络快捕"), &m_wndShortcutBar));

	m_paneFolders.SetParentWnd(this);
	m_paneCalendar.SetParentWnd(this);
	m_paneTasks.SetParentWnd(this);
	
	CXTPShortcutBarItem* pItemFolder = m_wndShortcutBar.AddItem(ID_SHORTCUT_FOLDERS, &m_paneFolders);
	pItemFolder->SetCaption("词汇管理");
	
	CXTPShortcutBarItem* pItemCalendar = m_wndShortcutBar.AddItem(ID_SHORTCUT_CALENDAR, &m_paneCalendar);
	pItemCalendar->SetCaption("网址管理");

	CXTPShortcutBarItem* pItemTasks = m_wndShortcutBar.AddItem(ID_SHORTCUT_TASKS, &m_paneTasks);
	pItemTasks->SetCaption("快捕管理");

	m_pItemFolder = pItemFolder;
	m_pItemCalendar = pItemCalendar;
	m_pItemTasks = pItemTasks;
	
	//m_wndShortcutBar.AllowMinimize(TRUE);
	
	m_wndShortcutBar.SelectItem(pItemFolder);
	m_wndShortcutBar.LoadState(_T("ShortcutBar"));
	
	m_wndShortcutBar.SetTheme(xtpShortcutThemeOffice2007);

}

void CLocalAgenterDlg::InitReportCtrl()
{
	m_wndReportCtrl.MoveWindow(CRect(190, 50, 770, LENGHT_BAR), TRUE);
	
	// create the image list used by the report control.
	if (!m_ilIcons.Create(16,16, ILC_COLOR24 | ILC_MASK, 0, 1))
		return ;
	
	// report control.
	//	CBitmap bitmap;
	//	VERIFY(bitmap.LoadBitmap(IDB_BITMAP_DELETE));
	//	m_ilIcons.Add(&bitmap, RGB(255, 0, 255));
	m_ilIcons.Add(AfxGetApp()->LoadIcon(IDI_ICON_DELETE));
	m_ilIcons.Add(AfxGetApp()->LoadIcon(IDI_ICON_MODIFY));
	m_wndReportCtrl.SetImageList(&m_ilIcons);
	
	//只允许【名称】列可编辑
	CXTPReportColumn* pColumn = new CXTPReportColumn(COLUMN_BUTTON1, _T(""), 18);
	pColumn->SetEditable(FALSE);
	pColumn->EnableResize(FALSE);
	pColumn->SetAutoSize(FALSE);
	m_wndReportCtrl.AddColumn(pColumn);
	
	pColumn = new CXTPReportColumn(COLUMN_BLACK1, _T(""), 5);
	pColumn->SetEditable(FALSE);
	pColumn->EnableResize(FALSE);
	pColumn->SetAutoSize(FALSE);
	m_wndReportCtrl.AddColumn(pColumn);
	
	pColumn = new CXTPReportColumn(COLUMN_BUTTON2, _T(""), 18);
	pColumn->SetEditable(FALSE);
	pColumn->EnableResize(FALSE);
	pColumn->SetAutoSize(FALSE);
	m_wndReportCtrl.AddColumn(pColumn);
	
	pColumn = new CXTPReportColumn(COLUMN_BLACK2, _T(""), 5);
	pColumn->SetEditable(FALSE);
	pColumn->EnableResize(FALSE);
	m_wndReportCtrl.AddColumn(pColumn);
	
	m_pColumn4 = new CXTPReportColumn(COLUMN_SUBJECT, _T("名称"), 280);
	m_pColumn4->SetEditable(TRUE);
	m_wndReportCtrl.AddColumn(m_pColumn4);
	
	pColumn = new CXTPReportColumn(COLUMN_DATE, _T("时间"), 180);
	pColumn->SetEditable(FALSE);
	m_wndReportCtrl.AddColumn(pColumn);
	
	m_wndReportCtrl.SetGridStyle(FALSE, xtpReportGridSmallDots);
	m_wndReportCtrl.SetGridColor(RGB(190,190,190));
	
	m_wndReportCtrl.AllowEdit(TRUE);
	m_wndReportCtrl.EditOnDelayClick(TRUE);
	
	m_wndReportCtrl.Populate();
	
	m_wndReportCtrl.EnableDragDrop(_T("ReportDialog"), xtpReportAllowDrag | xtpReportAllowDrop);
	
	m_wndReportCtrl.SetParentDlg(this);
	// Set control resizing.
	SetResize(IDC_REPORTCTRL, SZ_TOP_LEFT, SZ_BOTTOM_RIGHT);
	
	// Load window placement
	LoadPlacement(_T("CLocalAgenterDlg"));
}

void CLocalAgenterDlg::AddNewRecord(char* szContent)
{
	char* pTime = sloCommAgent::GetCurTime();
	//插入数据库
	if( m_wndShortcutBar.GetSelectedItem() == m_pItemFolder)
	{
		sloMysqlAgent::GetInstance()->AddKeyword(m_paneFolders.m_szTypeName, szContent);
	}else if (m_wndShortcutBar.GetSelectedItem() == m_pItemCalendar)
	{
		//选中的是网址pane
		sloMysqlAgent::GetInstance()->AddWebsite(m_paneCalendar.m_szTypeName, szContent);
	}else if (m_wndShortcutBar.GetSelectedItem() == m_pItemTasks)
	{
		//选中网络快捕
		//
		CCyberDlg cyber;
		if(cyber.DoModal() == 1)
		{	
			//插入列表中
			CXTPReportRecord* pRecord = m_wndReportCtrl.AddRecord(new CReportRecord(cyber.m_cyberName.GetBuffer(0), pTime));
			ShowListContent_Button(pRecord);
			
			m_wndReportCtrl.Populate();
			
			CXTPReportRows* pRows = m_wndReportCtrl.GetRows();
			int nRowCount = pRows->GetCount();
			CXTPReportRow* pNewRow = pRows->GetAt(nRowCount - 1);
			
			m_wndReportCtrl.SetFocusedRow(pNewRow);
			return;
		}else
		{
			//选择取消
			return ;
		}
	}

	//插入列表中
	CXTPReportRecord* pRecord = m_wndReportCtrl.AddRecord(new CReportRecord(szContent, pTime));
	ShowListContent_Button(pRecord);
	
	m_wndReportCtrl.Populate();
	
	CXTPReportRows* pRows = m_wndReportCtrl.GetRows();
	int nRowCount = pRows->GetCount();
	CXTPReportRow* pNewRow = pRows->GetAt(nRowCount - 1);

	m_wndReportCtrl.SetFocusedRow(pNewRow);
	//将这一列值为可编辑		
	CXTPReportColumn* pColumn = m_wndReportCtrl.GetColumns()->GetAt(4);
	m_wndReportCtrl.SetFocusedColumn(pColumn);

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
		CXTPReportRecord* pRecord = m_wndReportCtrl.AddRecord(new CReportRecord(sloMysqlAgent::GetInstance()->m_KeywordsList[i].szKeyName, sloMysqlAgent::GetInstance()->m_KeywordsList[i].szDate));
		ShowListContent_Button(pRecord);
	}

	m_pColumn4->SetEditable(TRUE);

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
		CXTPReportRecord* pRecord = m_wndReportCtrl.AddRecord(new CReportRecord(sloMysqlAgent::GetInstance()->m_WebsiteList[i].szSiteName, sloMysqlAgent::GetInstance()->m_WebsiteList[i].szDate));
		ShowListContent_Button(pRecord);
	}

	m_pColumn4->SetEditable(TRUE);
	m_wndReportCtrl.Populate();
}

void CLocalAgenterDlg::ShowListContent_Cyber()
{
	sloMysqlAgent::GetInstance()->GetCyberFromDB();
	
	//清空列表
	m_wndReportCtrl.ResetContent();
	int nCount = sloMysqlAgent::GetInstance()->m_CyberList.size();
	for(int i = 0; i < nCount; i++)
	{
		CXTPReportRecord* pRecord = m_wndReportCtrl.AddRecord(new CReportRecord(sloMysqlAgent::GetInstance()->m_CyberList[i].szCyberName, sloMysqlAgent::GetInstance()->m_CyberList[i].szDate));
		ShowListContent_Button(pRecord);
	}

	//不可编辑
	m_pColumn4->SetEditable(FALSE);
	
	m_wndReportCtrl.Populate();	
}

void CLocalAgenterDlg::ShowListContent_Button(CXTPReportRecord* pRecord)
{
	if (!pRecord)
		return;

	CXTPReportRecordItem* pItem = pRecord->GetItem(0);
	if(!pItem)
		return;
	CXTPReportRecordItemControl* pButton = pItem->GetItemControls()->AddControl(xtpItemControlTypeButton);
	if(!pButton)
		return;
	pButton->SetAlignment(xtpItemControlLeft);
	pButton->SetIconIndex(PBS_NORMAL, 0);
	//pButton->SetIconIndex(PBS_PRESSED, 1);
	pButton->SetSize(CSize(22, 0));

	CXTPReportRecordItem* pItem2 = pRecord->GetItem(2);
	if(!pItem2)
		return;
	CXTPReportRecordItemControl* pButton2 = pItem2->GetItemControls()->AddControl(xtpItemControlTypeButton);
	if(!pButton2)
		return;
	pButton2->SetAlignment(xtpItemControlLeft);
	pButton2->SetIconIndex(PBS_NORMAL, 1);
	pButton2->SetSize(CSize(22, 0));
		

}


void CLocalAgenterDlg::OnButtonDropDown(UINT nID)
{
	// loading a user resource.
	CMenu menu;
	menu.LoadMenu(IDR_MENU_DROPDOWN);
	
	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);
	
	CXTPButton* pButton = DYNAMIC_DOWNCAST(CXTPButton, GetDlgItem(nID));
	ASSERT(pButton);
	
	DWORD dwStyle = pButton->GetPushButtonStyle();
	ASSERT(pButton->IsDropDownStyle());
	
	CXTPWindowRect rect(pButton);
	
	int nCmd = TrackPopupMenu(pPopup->GetSafeHmenu(), TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_VERTICAL |TPM_RETURNCMD,
		dwStyle == xtpButtonDropDownRight ? rect.right : rect.left, dwStyle == xtpButtonDropDownRight ? rect.top : rect.bottom, 0, m_hWnd, 0);
	
	switch(nCmd)
	{
	case ID_DROPDOWNMENU_OPTIONITEM1:
		MessageBox("1");
		break;
	case ID_DROPDOWNMENU_OPTIONITEM2:
		MessageBox("2");
		break;
	default:
		break;
	}
	

}

void CLocalAgenterDlg::OnButtonExport() 
{
	// TODO: Add your control notification handler code here
	MessageBox("dcclick");
}

void CLocalAgenterDlg::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
	
}

void CLocalAgenterDlg::OnButtonSet() 
{
	// TODO: Add your control notification handler code here
	
}

void CLocalAgenterDlg::OnButtonSearch() 
{
	// TODO: Add your control notification handler code here
	
}


void CLocalAgenterDlg::SetComboxPos(BOOL bAll)
{
	
	RECT rcDlgs;
	m_BoxListGroup.GetWindowRect(&rcDlgs);   //得到对话框的Rect 对话框的大小
	ScreenToClient(&rcDlgs);             //把屏幕的值转成相应的实际的值 

	RECT rcType;
	m_BoxListType.GetWindowRect(&rcType);   //得到对话框的Rect 对话框的大小
	ScreenToClient(&rcType);             //把屏幕的值转成相应的实际的值 
	int nTypeLen = rcType.right - rcType.left;
	
	//cx cy,就是屏幕最右下角的x,y的值 
	if (m_bCommboxAllSel == TRUE)
	{
		//当前状态处于选中【全部】状态
		if (bAll)
		{
			//由【全部】-》【全部】
			return ;
		}else
		{
			//由【全部】-》【group】
			m_BoxListGroup.MoveWindow(rcDlgs.left,rcDlgs.top,(rcDlgs.right - rcDlgs.left - nTypeLen),(rcDlgs.bottom - rcDlgs.top),TRUE);   // 
			m_bCommboxAllSel = FALSE;
			//隐藏type commbox
			m_BoxListType.ShowWindow(SW_SHOWNORMAL);
		}
	}else{
		//当前状态处于选中【索引目录】状态
		if (bAll)
		{
			//由【group】-》【全部】
			m_BoxListGroup.MoveWindow(rcDlgs.left,rcDlgs.top,(rcDlgs.right - rcDlgs.left + nTypeLen),(rcDlgs.bottom - rcDlgs.top),TRUE);   // 
			m_bCommboxAllSel = TRUE;
			//显示type commbox
			m_BoxListType.ShowWindow(SW_HIDE);
		}else
		{
			//由【group】-》【group】
			return ;
		}
	}
}

#define ALL_NAME	"全部"
void CLocalAgenterDlg::OnEditchangeComboGroup() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_BoxListGroup.GetCurSel();		//得到被选中内容索引
	CString strtemp;						//存放得到的编辑框内容
	m_BoxListGroup.GetLBText(nIndex,strtemp);	//得到被选中内容的名字
	
	if (strcmp(strtemp.GetBuffer(0), ALL_NAME) == 0)
	{
		//选中全部
		SetComboxPos(TRUE);
	}else
		SetComboxPos(FALSE);
}

void CLocalAgenterDlg::OnSelchangeComboGroup() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_BoxListGroup.GetCurSel();		//得到被选中内容索引
	CString strtemp;						//存放得到的编辑框内容
	m_BoxListGroup.GetLBText(nIndex,strtemp);	//得到被选中内容的名字
	
	if (strcmp(strtemp.GetBuffer(0), ALL_NAME) == 0)
	{
		//选中全部
		SetComboxPos(TRUE);
	}else
		SetComboxPos(FALSE);	
}


void CLocalAgenterDlg::OnItemButtonClick(NMHDR * pNotifyStruct, LRESULT*pResult)
{
	XTP_NM_REPORTITEMCONTROL* pItemNotify = (XTP_NM_REPORTITEMCONTROL*) pNotifyStruct;
	if(!(pItemNotify->pRow && pItemNotify->pItem && pItemNotify->pItemControl))
		return;

	int nColumn = pItemNotify->pColumn->GetIndex();
	//pItemNotify->pItemControl->GetIndex()
	switch(nColumn)
	{
		// button "delete"
	case 0 :
		{
			//选中
			m_wndReportCtrl.SetFocusedRow(pItemNotify->pRow);

			CXTPReportRecord* pRecord = pItemNotify->pRow->GetRecord();
	
			CXTPReportRecordItemText* pItemText = (CXTPReportRecordItemText*)pRecord->GetItem(4);
			CString strContent = pItemText->GetValue();
			//删除数据库记录
			if(m_wndShortcutBar.GetSelectedItem() == m_pItemFolder)
			{
				if (6 == MessageBox("您确定删除该条记录？","词汇管理",MB_YESNO | MB_ICONWARNING))
				{			
					//删除数据库
					sloMysqlAgent::GetInstance()->DelKeyword(strContent.GetBuffer(0));		
				}else
					break;
			}else if (m_wndShortcutBar.GetSelectedItem() == m_pItemCalendar)
			{
				//选中的是网址pane
				if (6 == MessageBox("您确定删除该条记录？","网址管理",MB_YESNO | MB_ICONWARNING))
				{				
					//删除数据库
					sloMysqlAgent::GetInstance()->DelWebsite(strContent.GetBuffer(0));		
				}else
					break;
			}else if (m_wndShortcutBar.GetSelectedItem() == m_pItemTasks)
			{
				//删除快捕任务

			}

			//删除行
			m_wndReportCtrl.RemoveRowEx(pItemNotify->pRow);
			break;
		}
		// button "modify"
	case 2 :
		{		
			//选中		
			m_wndReportCtrl.SetFocusedRow(pItemNotify->pRow);			
			if (m_wndShortcutBar.GetSelectedItem() == m_pItemTasks)
			{
				CXTPReportRecord* pRecord = pItemNotify->pRow->GetRecord();	
				CXTPReportRecordItemText* pItemText = (CXTPReportRecordItemText*)pRecord->GetItem(4);
				CString strContent = pItemText->GetValue();
				//修改快捕任务，弹出对话框
				CCyberDlg cyber;
				cyber.m_cyberName = strContent;
				if (cyber.DoModal() == 1)
				{
					//点击确定

				}else
				{
					//点击取消

				}
			}else{
	
				//将这一列值为可编辑		
				CXTPReportColumn* pColumn = m_wndReportCtrl.GetColumns()->GetAt(4);
				m_wndReportCtrl.SetFocusedColumn(pColumn);
			}

			break;
		}
	}

	*pResult = (LRESULT)TRUE;
}


void CLocalAgenterDlg::OnBeginEdit(NMHDR * pNotifyStruct, LRESULT*pResult)
{
	XTP_NM_REPORTITEMCONTROL* pItemNotify = (XTP_NM_REPORTITEMCONTROL*) pNotifyStruct;
	if(!(pItemNotify->pRow && pItemNotify->pItem && pItemNotify->pItemControl))
		return;
	
	int nColumn = pItemNotify->pColumn->GetIndex();
	//pItemNotify->pItemControl->GetIndex()
	switch(nColumn)
	{
		// 更新第四列
	case 4 :
		{
			//选中
			CXTPReportRecord* pRecord = pItemNotify->pRow->GetRecord();
			
			CXTPReportRecordItemText* pItemText = (CXTPReportRecordItemText*)pRecord->GetItem(4);
			m_strOldContent = pItemText->GetValue();
			
			break;
		}
	default :
		{

				
			break;
		}
	}
	
	*pResult = (LRESULT)TRUE;
}



void CLocalAgenterDlg::OnValueChanged(NMHDR * pNotifyStruct, LRESULT*pResult)
{
	XTP_NM_REPORTITEMCONTROL* pItemNotify = (XTP_NM_REPORTITEMCONTROL*) pNotifyStruct;
	if(!(pItemNotify->pRow && pItemNotify->pItem && pItemNotify->pItemControl))
		return;
	
	int nColumn = pItemNotify->pColumn->GetIndex();
	//pItemNotify->pItemControl->GetIndex()
	switch(nColumn)
	{
		// 更新第四列
	case 4 :
		{
			//选中
			CXTPReportRecord* pRecord = pItemNotify->pRow->GetRecord();
			
			CXTPReportRecordItemText* pItemText = (CXTPReportRecordItemText*)pRecord->GetItem(4);
			CString strNewContent = pItemText->GetValue();
			char* pTime = sloCommAgent::GetCurTime();
			//更新数据库
			if( m_wndShortcutBar.GetSelectedItem() == m_pItemFolder)
			{
				//并更新数据库表
				sloMysqlAgent::GetInstance()->UpdateKeyword(m_strOldContent.GetBuffer(0), strNewContent.GetBuffer(0), pTime);
			}else
			{
				//并更新数据库表
				sloMysqlAgent::GetInstance()->UpdateWebsite(m_strOldContent.GetBuffer(0), strNewContent.GetBuffer(0), pTime);
			}			

			//更新第5列时间数据
			CXTPReportRecordItemText* pItemText5 = (CXTPReportRecordItemText*)pRecord->GetItem(5);
			pItemText5->SetValue(pTime);
			
			break;
		}
	default :
		{
			
			
			break;
		}
	}
	
	*pResult = (LRESULT)TRUE;
}

void CLocalAgenterDlg::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here

}

void CLocalAgenterDlg::OnSize(UINT nType, int cx, int cy) 
{
	CXTResizeDialog::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if (m_wndShortcutBar.m_hWnd)
	{
		//根据分辨率来判断
		CRect rc;
		m_wndReportCtrl.GetWindowRect(&rc);
		ScreenToClient(&rc);
		m_wndShortcutBar.MoveWindow(CRect(5, 50, 180, rc.bottom),TRUE);
	}

}

void CLocalAgenterDlg::OnDestroy() 
{
	CXTResizeDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	m_wndShortcutBar.SaveState(_T("ShortcutBar"));
}
