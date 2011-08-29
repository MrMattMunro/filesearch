// officesearchDlg.cpp : implementation file
//

#include "stdafx.h"
#include "officesearch.h"
#include "officesearchDlg.h"

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
// COfficesearchDlg dialog

COfficesearchDlg::COfficesearchDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COfficesearchDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COfficesearchDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COfficesearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COfficesearchDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(COfficesearchDlg, CDialog)
	//{{AFX_MSG_MAP(COfficesearchDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COfficesearchDlg message handlers

BOOL COfficesearchDlg::OnInitDialog()
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

void COfficesearchDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void COfficesearchDlg::OnPaint() 
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
HCURSOR COfficesearchDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


/*

  Sub Macro1()
  '
  ' Macro1 Macro
  ' 宏在 2011-8-22 由 未定义 录制
  '
  Selection.GoTo What:=wdGoToPage, Which:=wdGoToNext, Name:="3"
  Selection.Find.ClearFormatting
  With Selection.Find
  .Text = "123"
  .Replacement.Text = ""
  .Forward = True
  .Wrap = wdFindContinue
  .Format = False
  .MatchCase = False
  .MatchWholeWord = False
  .MatchByte = True
  .MatchWildcards = False
  .MatchSoundsLike = False
  .MatchAllWordForms = False
  End With
  Selection.Find.Execute
  End Sub

*/
//打开word指定页
void COfficesearchDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	fileaddin.OpenFile_WORD("D:\\2.doc", 2, "1");
/*
	CoInitialize(NULL);
	
	HRESULT hr = S_OK;
	Word::_ApplicationPtr spWordApp = NULL;
	{
		hr = spWordApp.CreateInstance(L"Word.Application.11");
	}
	if (FAILED(hr))
	{
		CoUninitialize();
		return ;
	}
	spWordApp->put_Visible(VARIANT_TRUE);

	CComPtr<Word::_Document> document;
	CComPtr<Documents> spDocs = NULL;
	spWordApp->get_Documents(&spDocs);
	if (spDocs == NULL)
	{
		OutputDebugStringA("[EnumWord] 获取文档对象集合失败\n");
		return ;
	}
	
	document = spDocs->Open(&CComVariant("H:\\3.doc"), &vtMissing, &vtMissing, &CComVariant(VARIANT_TRUE));
	if (document == NULL)
	{
		OutputDebugStringA("[EnumWord] 打开文档失败\n");
		return ;
	}
	//光标执行第几页

	int nPage  =0;
	CComPtr<Word::Selection> sel;
	spWordApp->get_Selection(&sel);

	CComVariant vName("3");
	CComVariant count(1);
	CComVariant What(wdGoToPage);
	CComVariant Which(wdGoToNext);
	CComPtr<Word::Range> range;
	range = sel->GoTo(&What, &Which, &count, &vName);

	VARIANT pagecount;
	sel->get_Information(wdNumberOfPagesInDocument, &pagecount);
	int nPagecount = pagecount.lVal;

	CComPtr<Word::Find> find;
	sel->get_Find(&find);
	find->ClearFormatting();

	CComVariant vFindText("123"), vForward(VARIANT_TRUE);
	VARIANT_BOOL prop;
	find->Execute(&vFindText, 
		&vtMissing, 
		&vtMissing, 
		&vtMissing, 
		&vtMissing, 
		&vtMissing, 
		&vForward, 
		&vtMissing,
		&vtMissing,
		&vtMissing,
		&vtMissing,
		&vtMissing, 
		&vtMissing, 
		&vtMissing,
		&vtMissing);

	CoUninitialize();
*/
}

/*

  Sub Macro2()
  '
  ' Macro2 Macro
  ' 宏由 未定义 录制，时间: 2011-8-22
  '
	  	'
		Sheets("Sheet2").Select
		Application.Goto Reference:="Sheet2!R20C1"
		End Sub

  Sub Macro2()
  '
  ' Macro2 Macro
  ' 宏由 未定义 录制，时间: 2011-8-22
  '
  
	'
    Sheets("Sheet2").Select
    Range("A18").Select
    Cells.Find(What:="4", After:=ActiveCell, LookIn:=xlFormulas, LookAt:= _
	xlPart, SearchOrder:=xlByRows, SearchDirection:=xlNext, MatchCase:=False _
	, MatchByte:=False, SearchFormat:=False).Activate
	End Sub
*/
void COfficesearchDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	fileaddin.OpenFile_EXCEL("h:\\3.xls", "Sheet3", 20, "123");
/*
	CoInitialize(NULL);

	Excel::_ApplicationPtr spExcelApp;
	HRESULT hr = spExcelApp.CreateInstance(L"Excel.Application");
	if (FAILED(hr))
	{
		CoUninitialize();
		return;
	}
	
	spExcelApp->put_Visible(0, VARIANT_TRUE);

	CComPtr<Excel::Workbooks> spWorkbooks = NULL;
	spExcelApp->get_Workbooks(&spWorkbooks);
	if (spWorkbooks == NULL)
	{
		OutputDebugStringA("[EnumExcel] 获取工作薄对象集合失败\n");
		return ;
	}
	
	CComPtr<Excel::_Workbook> m_spWb;
	m_spWb = spWorkbooks->Open("h:\\3.xls");
	if (m_spWb == NULL)
	{
		OutputDebugStringA("[EnumExcel] 打开工作薄失败\n");
		return ;
	}
	
	//定位
	CComVariant vsheet("Sheet3!R20C1");
	spExcelApp->Goto(&vsheet, &vtMissing, 0);
	
	//查找
	CComVariant What("123"), LookIn(xlFormulas), LookAt(xlPart), SearchOrder(xlByRows);
	spExcelApp->GetCells()->Find(&What, &vtMissing, &LookIn,
		&LookAt, &SearchOrder, xlNext, 
		&vtMissing, &vtMissing,	&vtMissing)->Activate();
*/
}

/*
 ActiveWindow.Selection.SlideRange.Shapes("Rectangle 3").Select

ShapeRange.TextFrame.TextRange
*/
void COfficesearchDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here

	fileaddin.OpenFile_PPT("H:\\1.ppt", 2, "5");
/*	CoInitialize(NULL);
	PPT::_ApplicationPtr spPPTApp;
	HRESULT hr = spPPTApp.CreateInstance(L"PowerPoint.Application");
	if (FAILED(hr))
	{
		CoUninitialize();
		return ;
	}
	
	spPPTApp->put_Visible(msoTrue);

	spPPTApp->Activate();
	
	CComPtr<Presentations> spPresents = NULL;
	spPPTApp->get_Presentations(&spPresents);
	if (spPresents == NULL)
	{
		OutputDebugStringA("[EnumPPT] 获取存在对象集合失败\n");
		return ;
	}
		
	CComPtr<PPT::_Presentation> m_spPres;
	m_spPres = spPresents->Open("H:\\1.ppt", msoFalse, msoFalse, msoTrue);
	if (m_spPres == NULL)
	{
		OutputDebugStringA("[EnumPPT] 打开ppt文档失败\n");
		return ;
	}

	CComVariant item(2);
	m_spPres->GetSlides()->Item(&item)->Select();

	//查找内容
	CComPtr<PPT::DocumentWindow> docwin;
	spPPTApp->get_ActiveWindow(&docwin);
	
	CComPtr<PPT::Shapes> shapes;
	docwin->GetSelection()->GetSlideRange()->get_Shapes(&shapes);

	CComBSTR strText("5");
	int nCount = shapes->GetCount();
	for (int i = 0; i < nCount; i++)
	{
		CComVariant index = i+1;
		CComPtr<PPT::Shape> shape = shapes->Item(&index);
		CComPtr<PPT::TextRange> textrange;
		textrange = shape->GetTextFrame()->GetTextRange()->Find(strText.m_str, 1, msoFalse, msoFalse);
		int nCount = textrange->GetLength();
		int nstart = textrange->GetStart();

		if (nCount != 0 && nstart != 1)
		{
			textrange->Select();
			break;
		}
	}
*/	
}

void COfficesearchDlg::OnButton4() 
{
	// TODO: Add your control notification handler code here
	fileaddin.OpenFile_TXT("H:\\1.txt", 7, "3524");
/*
	CWnd* ptxtwnd = FindWindow("NotePad","689.txt - 记事本");
	HWND hwnd = FindWindowEx(ptxtwnd->m_hWnd, NULL, "Edit", "");

	CEdit edit;
	edit.Attach(hwnd);

	edit.SetFocus();

	int nLine = 2;
	int nIndex = -1;
	nIndex = edit.LineIndex(nLine);
	if (nIndex == -1)
	{
		return ;
	}
	edit.SetSel(nIndex,nIndex);

	edit.Detach();
*/	
}
