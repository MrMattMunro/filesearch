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
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCreateIndexDlg message handlers

BOOL CCreateIndexDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
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

	sloCreateIndexAgent create;
	create.EventCreateIndex(szPath, strTypes.GetBuffer(0));
	CDialog::OnOK();
}

void CCreateIndexDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
