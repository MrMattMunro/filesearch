// CreateIndexDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FsUi.h"
#include "CreateIndexDlg.h"
#include "sloCreateIndexAgent.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCreateIndexDlg dialog


CCreateIndexDlg::CCreateIndexDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCreateIndexDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCreateIndexDlg)
	m_bExcel = FALSE;
	m_bHtml = FALSE;
	m_bPdf = FALSE;
	m_bTxt = FALSE;
	m_bPpt = FALSE;
	m_bWord = FALSE;
	//}}AFX_DATA_INIT
}


void CCreateIndexDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCreateIndexDlg)
	DDX_Check(pDX, IDC_CHECK_EXCEL, m_bExcel);
	DDX_Check(pDX, IDC_CHECK_HTML, m_bHtml);
	DDX_Check(pDX, IDC_CHECK_PDF, m_bPdf);
	DDX_Check(pDX, IDC_CHECK_TXT, m_bTxt);
	DDX_Check(pDX, IDC_CHECK_PPT, m_bPpt);
	DDX_Check(pDX, IDC_CHECK_WORD, m_bWord);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCreateIndexDlg, CDialog)
	//{{AFX_MSG_MAP(CCreateIndexDlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, OnButtonBrowse)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCreateIndexDlg message handlers

BOOL CCreateIndexDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	HICON m_hIcon;
	m_hIcon=AfxGetApp()->LoadIcon(IDI_ICON_NEW_INDEX);
	SetIcon(m_hIcon,TRUE); //设置为大图标

	//SetIcon(m_hIcon,FALSE);//设置为小图标
	// TODO: Add extra initialization here
	SetDlgItemText(IDC_STATIC_SEARCH_DIR, g_lag.LoadString("label.searchdir"));
	SetDlgItemText(IDC_STATIC_OBJECT_TYPE, g_lag.LoadString("label.doc"));
	SetDlgItemText(IDOK, g_lag.LoadString("button.confirm"));
	SetDlgItemText(IDCANCEL, g_lag.LoadString("button.cancel"));

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCreateIndexDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
}

void CCreateIndexDlg::OnButtonBrowse() 
{
	// TODO: Add your control notification handler code here
	BROWSEINFO   bi;       
	char   dispname[MAX_PATH],   path[MAX_PATH];       
	ITEMIDLIST   *pidl;       
    
	bi.hwndOwner   =   0;       
	bi.pidlRoot   =   0;       
	bi.pszDisplayName   =   dispname;       
	bi.lpszTitle   =   "Choose   Folder:";       
	bi.ulFlags   =   BIF_RETURNONLYFSDIRS;       
	bi.lpfn   =   0;       
	bi.lParam   =   0;       
	bi.iImage   =   0;       
    
	if   (pidl =  SHBrowseForFolder(&bi))   //弹出文件夹浏览窗口，并选取目录   
	{       
		SHGetPathFromIDList(pidl,   path);       
		GetDlgItem(IDC_EDIT_SEARCH_PATH)->SetWindowText(path);       
  }
}

char  *GetPath(HWND   hWnd,char   *pBuffer)  

{  
	
    BROWSEINFO   bf;  
	
    LPITEMIDLIST   lpitem;  
	
    memset(&bf,0,sizeof   BROWSEINFO);  
	
    bf.hwndOwner=hWnd;  
	
    bf.lpszTitle="选择路径";  
	
    bf.ulFlags=BIF_RETURNONLYFSDIRS;     //属性你可自己选择  
	
    lpitem=SHBrowseForFolder(&bf);  
	
    if(lpitem==NULL)     //如果没有选择路径则返回   0  
		
        return   "";  
	
    //如果选择了路径则复制路径,返回路径长度  	
	
    SHGetPathFromIDList(lpitem,pBuffer);  
	
    return   pBuffer;
	
}   

void CCreateIndexDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	char szPath[MAX_PATH];
	GetDlgItemText(IDC_EDIT_SEARCH_PATH,szPath, MAX_PATH );

	if (strlen(szPath) == 0)
	{
		MessageBox(g_lag.LoadString("message.selectsearchdir"),g_lag.LoadString("title.createnew"),MB_OK | MB_ICONWARNING);
		return ;
	}

	CString strTypes;
	if (m_bWord)
		strTypes += "word";
	if (m_bExcel)
		strTypes += ",excel";
	if (m_bPpt)
		strTypes += ",ppt";
	if (m_bPdf)
		strTypes += ",pdf";	
	if (m_bTxt)
		strTypes += ",txt";
	if (m_bHtml)
		strTypes += ",html";

	if (strTypes.GetLength() == 0)
	{
		MessageBox(g_lag.LoadString("title.createnew"),g_lag.LoadString("title.createnew"),MB_OK | MB_ICONWARNING);
		return ;
	}
	
	std::string szTypes = strTypes.GetBuffer(0);
	if (szTypes.substr(0,1) == ",")
	{
		szTypes.erase(0,1);
	}

	sloCreateIndexAgent create;
	if (!create.EventCreateIndex(szPath,(char*)szTypes.c_str()))
	{
		MessageBox(g_lag.LoadString("message.direxist"),g_lag.LoadString("title.createnew"),MB_OK | MB_ICONWARNING);
		SetDlgItemText(IDC_EDIT_SEARCH_PATH,"");
		return ;
	}

	CDialog::OnOK();
}

void CCreateIndexDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

HBRUSH CCreateIndexDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
//	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	COLORREF backColor = RGB(216, 231, 252); //office 2003背景色
	pDC->SetBkMode(TRANSPARENT);             //设置控件背景透明
	
	// 判断下是不是你要改的控件ID 
	if( pWnd->GetDlgCtrlID() == IDCANCEL || pWnd->GetDlgCtrlID() == IDOK )
	{
		pDC->SetBkColor(RGB(153, 255, 204));
	}
	
	return CreateSolidBrush(backColor);      //创建背景刷子
	// TODO: Return a different brush if the default is not desired
//	return hbr;
}
