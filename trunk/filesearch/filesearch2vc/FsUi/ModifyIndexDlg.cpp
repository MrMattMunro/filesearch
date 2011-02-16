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
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CModifyIndexDlg, CDialog)
	//{{AFX_MSG_MAP(CModifyIndexDlg)
	ON_BN_CLICKED(IDC_BUTTON_DEL_INDEX, OnButtonDelIndex)
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
		int nRet = MessageBox("您确定要修改此索引吗？","修改索引",MB_YESNO | MB_ICONWARNING);
		if (nRet == 6)
		{
			m_modifyAgent.EventModifyIndex((char*)szTypes.c_str());
			CDialog::OnOK();
		}
	}else
	{
		MessageBox("您未做任何修改！","修改索引",MB_OK | MB_ICONWARNING);
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
	int nRet = MessageBox("您确定要删除该索引吗？","删除索引",MB_YESNO | MB_ICONWARNING);
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
	
	// TODO: Add extra initialization here
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