// LicenseDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FsUi.h"
#include "LicenseDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLicenseDlg dialog


CLicenseDlg::CLicenseDlg(CWnd* pParent /*=NULL*/)
	: CXTPPropertyPage(CLicenseDlg::IDD)/*CDialog(CLicenseDlg::IDD, pParent)*/
{
	//{{AFX_DATA_INIT(CLicenseDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CLicenseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLicenseDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLicenseDlg, CDialog)
	//{{AFX_MSG_MAP(CLicenseDlg)
	ON_BN_CLICKED(IDC_BUTTON_REG, OnButtonReg)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLicenseDlg message handlers

void CLicenseDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CLicenseDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL CLicenseDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetDlgItemText(IDC_STATIC_LICENSE_INFO, g_lag.LoadString("label.license"));
	SetDlgItemText(IDC_STATIC_LICENSE_1,  g_lag.LoadString("label.licensenote"));
	SetDlgItemText(IDC_STATIC_NUM,  g_lag.LoadString("label.num"));
	SetDlgItemText(IDC_STATIC_EMAIL,  g_lag.LoadString("label.email"));
	SetDlgItemText(IDC_STATIC_BEGINTIME,  g_lag.LoadString("label.regtime"));
	SetDlgItemText(IDC_STATIC_ENDTIME,  g_lag.LoadString("label.endtime"));

	SetDlgItemText(IDC_BUTTON_REG,  g_lag.LoadString("button.register"));

	//////////////////////////////////////////////////////////////////////////

	m_licAgent.Init();
	UpdateDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
#define ERROR_INFO_SUCCEED				"注册信息已经提交，一日之内确认后，软件将被注册！\r\n"
#define ERROR_INFO_ORDERNO				"请填写订单号！\r\n"
#define ERROR_INFO_EMAIL				"请填写正确的电子邮箱！\r\n错误信息："
#define ERROR_INFO_REGISTER_FAILED		"License注册失败！\r\n"

BOOL CLicenseDlg::UpdateDialog() 
{

	if (m_licAgent.m_bDown)
	{
		//已注册，则显示注册信息到界面上
		GetDlgItem(IDC_BUTTON_REG)->ShowWindow(SW_HIDE);
		(CStatic*)GetDlgItem(IDC_STATIC_ERROR_INFO)->ShowWindow(SW_HIDE);

		SetDlgItemText(IDC_EDIT_NUM,m_licAgent.m_LicInfo.szOrderNo);
		SetDlgItemText(IDC_EDIT_EMAIL,m_licAgent.m_LicInfo.szEmail);
		((CEdit*)GetDlgItem(IDC_EDIT_NUM))->SetReadOnly(TRUE); 
		((CEdit*)GetDlgItem(IDC_EDIT_EMAIL))->SetReadOnly(TRUE); 

		(CStatic*)GetDlgItem(IDC_STATIC_BEGINTIME_CONTENT)->ShowWindow(SW_SHOW);
		(CStatic*)GetDlgItem(IDC_STATIC_ENTTIME_CONTENT)->ShowWindow(SW_SHOW);
		(CStatic*)GetDlgItem(IDC_STATIC_BEGINTIME)->ShowWindow(SW_SHOW);
		(CStatic*)GetDlgItem(IDC_STATIC_ENDTIME)->ShowWindow(SW_SHOW);


		((CStatic*)GetDlgItem(IDC_STATIC_BEGINTIME_CONTENT))->SetWindowText(m_licAgent.m_LicInfo.szStartDate);
		((CStatic*)GetDlgItem(IDC_STATIC_ENTTIME_CONTENT))->SetWindowText(m_licAgent.m_LicInfo.szEndDate);
		
	}else if (m_licAgent.m_bReg)
	{
		//信息已提交
		SetDlgItemText(IDC_EDIT_NUM,m_licAgent.m_LicInfo.szOrderNo);
		SetDlgItemText(IDC_EDIT_EMAIL,m_licAgent.m_LicInfo.szEmail);

		(CStatic*)GetDlgItem(IDC_STATIC_BEGINTIME_CONTENT)->ShowWindow(SW_HIDE);
		(CStatic*)GetDlgItem(IDC_STATIC_ENTTIME_CONTENT)->ShowWindow(SW_HIDE);
		(CStatic*)GetDlgItem(IDC_STATIC_BEGINTIME)->ShowWindow(SW_HIDE);
		(CStatic*)GetDlgItem(IDC_STATIC_ENDTIME)->ShowWindow(SW_HIDE);
		(CStatic*)GetDlgItem(IDC_STATIC_ERROR_INFO)->ShowWindow(SW_HIDE);
	
		CString strErrorInfo = "提示：";
		strErrorInfo += ERROR_INFO_SUCCEED;

		(CStatic*)GetDlgItem(IDC_STATIC_ERROR_INFO)->ShowWindow(SW_SHOW);
		((CStatic*)GetDlgItem(IDC_STATIC_ERROR_INFO))->SetWindowText(strErrorInfo.GetBuffer(0));
	}else
	{
		//未注册
		(CStatic*)GetDlgItem(IDC_STATIC_BEGINTIME_CONTENT)->ShowWindow(SW_HIDE);
		(CStatic*)GetDlgItem(IDC_STATIC_ENTTIME_CONTENT)->ShowWindow(SW_HIDE);
		(CStatic*)GetDlgItem(IDC_STATIC_BEGINTIME)->ShowWindow(SW_HIDE);
		(CStatic*)GetDlgItem(IDC_STATIC_ENDTIME)->ShowWindow(SW_HIDE);
		(CStatic*)GetDlgItem(IDC_STATIC_ERROR_INFO)->ShowWindow(SW_HIDE);	
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
}

void CLicenseDlg::OnButtonReg() 
{
	// TODO: Add your control notification handler code here
	CString strNum, strEMail;
	CString strErrorInfo = "提示：";
	
	BOOL bRet = TRUE;
	do 
	{
		GetDlgItemText(IDC_EDIT_NUM,strNum);
		GetDlgItemText(IDC_EDIT_EMAIL,strEMail);
		if (strNum.GetLength() == 0)
		{
			strErrorInfo += ERROR_INFO_ORDERNO;
			bRet = FALSE ;
			break ;
		}

		//检查email是否合法
		char szErrInfo[1024] = {0};
		if( m_licAgent.IsEmailAddr(strEMail.GetBuffer(0),szErrInfo) == false)
		{
			strErrorInfo += ERROR_INFO_EMAIL;
			strErrorInfo += szErrInfo;
			bRet = FALSE ;
			break ;		
		}
		
		if (m_licAgent.EventLicense(strNum.GetBuffer(0), strEMail.GetBuffer(0)) == FALSE)
		{
			strErrorInfo += ERROR_INFO_REGISTER_FAILED;
			bRet = FALSE ;
			break ;	
		}

		strErrorInfo += ERROR_INFO_SUCCEED;
	} while (0);
	
	(CStatic*)GetDlgItem(IDC_STATIC_ERROR_INFO)->ShowWindow(SW_SHOW);
	((CStatic*)GetDlgItem(IDC_STATIC_ERROR_INFO))->SetWindowText(strErrorInfo.GetBuffer(0));
	
}

HBRUSH CLicenseDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(pWnd->GetDlgCtrlID()==IDC_STATIC_ERROR_INFO) 
		pDC->SetTextColor(RGB(255,0,0)); //设置字体颜色为蓝色
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
