// ModifyIndexDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FsUi.h"
#include "ModifyIndexDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModifyIndexDlg dialog


CModifyIndexDlg::CModifyIndexDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CModifyIndexDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CModifyIndexDlg)
	m_bWord = FALSE;
	m_bPpt = FALSE;
	m_bPdf = FALSE;
	m_bHtml = FALSE;
	m_bExcel = FALSE;
	m_bChm = FALSE;
	m_nIndexID = 0;
	m_bTxt = FALSE;
	m_nTheme = 6;
	//}}AFX_DATA_INIT
}


void CModifyIndexDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModifyIndexDlg)
	DDX_Check(pDX, IDC_CHECK_WORD, m_bWord);
	DDX_Check(pDX, IDC_CHECK_PPT, m_bPpt);
	DDX_Check(pDX, IDC_CHECK_PDF, m_bPdf);
	DDX_Check(pDX, IDC_CHECK_HTML, m_bHtml);
	DDX_Check(pDX, IDC_CHECK_EXCEL, m_bExcel);
	DDX_Check(pDX, IDC_CHECK_CHM, m_bChm);
	DDX_Check(pDX, IDC_CHECK_TXT_MODIFY, m_bTxt);
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_BUTTON_DEL_INDEX, m_btnDelete);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CModifyIndexDlg, CDialog)
	//{{AFX_MSG_MAP(CModifyIndexDlg)
	ON_BN_CLICKED(IDC_BUTTON_DEL_INDEX, OnButtonDelIndex)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModifyIndexDlg message handlers

void CModifyIndexDlg::OnOK() 
{
	// TODO: Add extra validation here
	//更新T_SEACHER表中filetype字段及 是否已更新=0(待更新)
	UpdateData(TRUE);
	
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

	std::string szTypes = strTypes.GetBuffer(0);
	if (szTypes.substr(0,1) == ",")
	{
		szTypes.erase(0,1);
	}
	
	if (szTypes.compare(m_modifyAgent.m_szSearchType))
	{
		//修改索引type
		int nRet = MessageBox(g_lag.LoadString("message.suremodifyindex"),g_lag.LoadString("title.modifysearch"),MB_YESNO | MB_ICONWARNING);
		if (nRet == 6)
		{
			m_modifyAgent.EventModifyIndex((char*)szTypes.c_str());
			CDialog::OnOK();
		}
	}else
	{
		MessageBox(g_lag.LoadString("message.nomodify"),g_lag.LoadString("title.modifysearch"),MB_OK | MB_ICONWARNING);
	}

//	CDialog::OnOK();
}

void CModifyIndexDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CModifyIndexDlg::OnButtonDelIndex() 
{
	// TODO: Add your control notification handler code here
	int nRet = MessageBox(g_lag.LoadString("message.suredelindex"),g_lag.LoadString("title.modifysearch"),MB_YESNO | MB_ICONWARNING);
	if (nRet == 6)
	{
		m_modifyAgent.EventDelIndex();
		CDialog::OnOK();
	}
}

void CModifyIndexDlg::SetIndexID(int id)
{
	m_nIndexID = id;
	m_modifyAgent.SetIndexID(m_nIndexID);
}

BOOL CModifyIndexDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	HICON m_hIcon;
	m_hIcon=AfxGetApp()->LoadIcon(IDI_ICON_MODIFY_INDEX);
	SetIcon(m_hIcon,TRUE); //设置为大图标

	SetWindowText(g_lag.LoadString("title.modifysearch"));

	m_btnOk.SetBitmap(0, IDB_BITMAP_OK);
	m_btnCancel.SetBitmap(0, IDB_BITMAP_CANCEL);
	m_btnDelete.SetBitmap(0, IDB_BITMAP_DELETE);
	// TODO: Add extra initialization here	
	SetDlgItemText(IDC_STATIC_SEARCH_DIR_MODIFY, g_lag.LoadString("label.searchdir"));
	SetDlgItemText(IDC_STATIC_OBJECT_TYPE_MODIFY, g_lag.LoadString("label.doc"));
	SetDlgItemText(IDOK, g_lag.LoadString("button.confirm"));
	SetDlgItemText(IDCANCEL, g_lag.LoadString("button.cancel"));
	SetDlgItemText(IDC_BUTTON_DEL_INDEX, g_lag.LoadString("button.delete"));
	//////////////////////////////////////////////////////////////////////////

	m_modifyAgent.GetSearchInfo();
	SetDlgItemText(IDC_STATIC_SEARCHPATH,m_modifyAgent.m_szSearchPath);

	std::string szTypes = m_modifyAgent.m_szSearchType;
	size_t nPos = szTypes.find_first_of(',');
	while(nPos != -1)
	{
		std::string strType = szTypes.substr(0, nPos);
		SetType((char*)strType.c_str());
		
		szTypes.erase(0, nPos+1);
		nPos = szTypes.find_first_of(',');
	}

	SetType((char*)szTypes.c_str());

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CModifyIndexDlg::SetType(char *szType)
{
	std::string strType = szType; 
	if (strType == "word")
	{
		m_bWord = TRUE;
	}
	if (strType == "excel")
	{
		m_bExcel = TRUE;
	}
	if (strType == "ppt")
	{
		m_bPpt = TRUE;
	}
	if (strType == "pdf")
	{
		m_bPdf = TRUE;
	}
	if (strType == "txt")
	{
		m_bTxt = TRUE;
	}	
	if (strType == "chm")
	{
		m_bChm = TRUE;
	}	
	if (strType == "html")
	{
		m_bHtml = TRUE;
	}	
}

HBRUSH CModifyIndexDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
// 	COLORREF backColor = RGB(216, 231, 252); //office 2003背景色
// 	pDC->SetBkMode(TRANSPARENT);             //设置控件背景透明
// 	
// 	// 判断下是不是你要改的控件ID 
// 	if( pWnd->GetDlgCtrlID() == IDCANCEL || pWnd->GetDlgCtrlID() == IDOK )
// 	{
// 		pDC->SetBkColor(RGB(153, 255, 204));
// 	}
// 	
// 	return CreateSolidBrush(backColor);      //创建背景刷子	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
