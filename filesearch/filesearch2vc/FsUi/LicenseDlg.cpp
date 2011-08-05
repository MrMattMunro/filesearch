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
	DDX_Control(pDX, IDC_BUTTON_LICENSE_BACK, m_btnBack);
	DDX_Control(pDX, IDC_BUTTON_LICENSE_RESTORE, m_btnRestore);
	DDX_Control(pDX, IDC_BUTTON_BROWSE_RESTORE_PATH, m_btnFolderRestore);
	DDX_Control(pDX, IDC_BUTTON_BROWSE_BACK_PATH, m_btnFolderBack);
	DDX_Control(pDX, IDC_BUTTON_REG, m_btnReg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLicenseDlg, CDialog)
	//{{AFX_MSG_MAP(CLicenseDlg)
	ON_BN_CLICKED(IDC_BUTTON_REG, OnButtonReg)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_LICENSE_BACK, OnButtonLicenseBack)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE_BACK_PATH, OnButtonBrowseBackPath)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE_RESTORE_PATH, OnButtonBrowseRestorePath)
	ON_BN_CLICKED(IDC_BUTTON_LICENSE_RESTORE, OnButtonLicenseRestore)
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

	m_btnReg.SetBitmap(0, IDB_BITMAP_REGISTER);
	m_btnBack.SetBitmap(0, IDB_BITMAP_BACK);
	m_btnRestore.SetBitmap(0, IDB_BITMAP_RESTORE);

	m_btnFolderRestore.SetBitmap(0, IDB_BITMAP_FOLDER);
	m_btnFolderRestore.SetFlatStyle(TRUE);

	m_btnFolderBack.SetBitmap(0, IDB_BITMAP_FOLDER2);
	m_btnFolderBack.SetFlatStyle(TRUE);

	// TODO: Add extra initialization here
	SetDlgItemText(IDC_STATIC_LICENSE_INFO, g_lag.LoadString("label.license"));
	SetDlgItemText(IDC_STATIC_LICENSE_1,  g_lag.LoadString("label.licensenote"));
	SetDlgItemText(IDC_STATIC_NUM,  g_lag.LoadString("label.num"));
	SetDlgItemText(IDC_STATIC_EMAIL,  g_lag.LoadString("label.email"));
	SetDlgItemText(IDC_STATIC_BEGINTIME,  g_lag.LoadString("label.regtime"));
	SetDlgItemText(IDC_STATIC_ENDTIME,  g_lag.LoadString("label.endtime"));

	SetDlgItemText(IDC_STATIC_LICENSE_RESTORE_INFO2,  g_lag.LoadString("label.licrestoreinfo"));
	SetDlgItemText(IDC_STATIC_LICENSE_RESTORE_TIP,  g_lag.LoadString("label.licrestorepath"));
	SetDlgItemText(IDC_STATIC_LICENSE_BACK_INFO2,  g_lag.LoadString("label.licrebackinfo"));
	SetDlgItemText(IDC_STATIC_LICENSE_BACK_TIP,  g_lag.LoadString("label.licbackpath"));

	SetDlgItemText(IDC_STATIC_LICENSE_BACKINFO,  g_lag.LoadString("title.licback"));
	SetDlgItemText(IDC_STATIC_LICENSE_RESTOREINFO,  g_lag.LoadString("title.licrestore"));

	SetDlgItemText(IDC_BUTTON_REG,  g_lag.LoadString("button.register"));

	SetDlgItemText(IDC_BUTTON_LICENSE_RESTORE,  g_lag.LoadString("button.restore"));
	SetDlgItemText(IDC_BUTTON_LICENSE_BACK,  g_lag.LoadString("button.back"));
	//////////////////////////////////////////////////////////////////////////

	m_licAgent.Init();
	UpdateDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

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

		//显示备份界面
		((CEdit*)GetDlgItem(IDC_EDIT_LICENSE_BACK_PATH))->ShowWindow(SW_SHOW); 

		(CStatic*)GetDlgItem(IDC_STATIC_HAND_LICENSE_BACK)->ShowWindow(SW_SHOW);
		(CStatic*)GetDlgItem(IDC_STATIC_LICENSE_BACKINFO)->ShowWindow(SW_SHOW);
		(CStatic*)GetDlgItem(IDC_STATIC_LICENSE_BACK_TIP)->ShowWindow(SW_SHOW);
		(CStatic*)GetDlgItem(IDC_STATIC_LICENSE_BACK_INFO2)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_BUTTON_BROWSE_BACK_PATH)->ShowWindow(SW_SHOW);	
		GetDlgItem(IDC_BUTTON_LICENSE_BACK)->ShowWindow(SW_SHOW);


		//隐藏恢复界面	
		((CEdit*)GetDlgItem(IDC_EDIT_LICENSE_RESTORE_PATH))->ShowWindow(SW_HIDE); 

		(CStatic*)GetDlgItem(IDC_STATIC_HAND_LICENSE_RESOTRE)->ShowWindow(SW_HIDE);
		(CStatic*)GetDlgItem(IDC_STATIC_LICENSE_RESTOREINFO)->ShowWindow(SW_HIDE);
		(CStatic*)GetDlgItem(IDC_STATIC_LICENSE_RESTORE_TIP)->ShowWindow(SW_HIDE);
		(CStatic*)GetDlgItem(IDC_STATIC_LICENSE_RESTORE_INFO2)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_BUTTON_BROWSE_RESTORE_PATH)->ShowWindow(SW_HIDE);	
		GetDlgItem(IDC_BUTTON_LICENSE_RESTORE)->ShowWindow(SW_HIDE);

		
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
	
		CString strErrorInfo = g_lag.LoadString("label.info");
		strErrorInfo += g_lag.LoadString("label.reginfo");

		(CStatic*)GetDlgItem(IDC_STATIC_ERROR_INFO)->ShowWindow(SW_SHOW);
		((CStatic*)GetDlgItem(IDC_STATIC_ERROR_INFO))->SetWindowText(strErrorInfo.GetBuffer(0));
		
		//隐藏备份界面
		((CEdit*)GetDlgItem(IDC_EDIT_LICENSE_BACK_PATH))->ShowWindow(SW_HIDE); 
		
		(CStatic*)GetDlgItem(IDC_STATIC_HAND_LICENSE_BACK)->ShowWindow(SW_HIDE);
		(CStatic*)GetDlgItem(IDC_STATIC_LICENSE_BACKINFO)->ShowWindow(SW_HIDE);
		(CStatic*)GetDlgItem(IDC_STATIC_LICENSE_BACK_TIP)->ShowWindow(SW_HIDE);
		(CStatic*)GetDlgItem(IDC_STATIC_LICENSE_BACK_INFO2)->ShowWindow(SW_HIDE);
		
		GetDlgItem(IDC_BUTTON_BROWSE_BACK_PATH)->ShowWindow(SW_HIDE);	
		GetDlgItem(IDC_BUTTON_LICENSE_BACK)->ShowWindow(SW_HIDE);
		
		//显示恢复界面	
		((CEdit*)GetDlgItem(IDC_EDIT_LICENSE_RESTORE_PATH))->ShowWindow(SW_SHOW); 
		
		(CStatic*)GetDlgItem(IDC_STATIC_HAND_LICENSE_RESOTRE)->ShowWindow(SW_SHOW);
		(CStatic*)GetDlgItem(IDC_STATIC_LICENSE_RESTOREINFO)->ShowWindow(SW_SHOW);
		(CStatic*)GetDlgItem(IDC_STATIC_LICENSE_RESTORE_TIP)->ShowWindow(SW_SHOW);
		(CStatic*)GetDlgItem(IDC_STATIC_LICENSE_RESTORE_INFO2)->ShowWindow(SW_SHOW);
		
		GetDlgItem(IDC_BUTTON_BROWSE_RESTORE_PATH)->ShowWindow(SW_SHOW);	
		GetDlgItem(IDC_BUTTON_LICENSE_RESTORE)->ShowWindow(SW_SHOW);

	}else
	{
		//未注册
		(CStatic*)GetDlgItem(IDC_STATIC_BEGINTIME_CONTENT)->ShowWindow(SW_HIDE);
		(CStatic*)GetDlgItem(IDC_STATIC_ENTTIME_CONTENT)->ShowWindow(SW_HIDE);
		(CStatic*)GetDlgItem(IDC_STATIC_BEGINTIME)->ShowWindow(SW_HIDE);
		(CStatic*)GetDlgItem(IDC_STATIC_ENDTIME)->ShowWindow(SW_HIDE);
		(CStatic*)GetDlgItem(IDC_STATIC_ERROR_INFO)->ShowWindow(SW_HIDE);
		
		//隐藏备份界面
		((CEdit*)GetDlgItem(IDC_EDIT_LICENSE_BACK_PATH))->ShowWindow(SW_HIDE); 
		
		(CStatic*)GetDlgItem(IDC_STATIC_HAND_LICENSE_BACK)->ShowWindow(SW_HIDE);
		(CStatic*)GetDlgItem(IDC_STATIC_LICENSE_BACKINFO)->ShowWindow(SW_HIDE);
		(CStatic*)GetDlgItem(IDC_STATIC_LICENSE_BACK_TIP)->ShowWindow(SW_HIDE);
		(CStatic*)GetDlgItem(IDC_STATIC_LICENSE_BACK_INFO2)->ShowWindow(SW_HIDE);
		
		GetDlgItem(IDC_BUTTON_BROWSE_BACK_PATH)->ShowWindow(SW_HIDE);	
		GetDlgItem(IDC_BUTTON_LICENSE_BACK)->ShowWindow(SW_HIDE);
			
		//显示恢复界面	
		((CEdit*)GetDlgItem(IDC_EDIT_LICENSE_RESTORE_PATH))->ShowWindow(SW_SHOW); 
		
		(CStatic*)GetDlgItem(IDC_STATIC_HAND_LICENSE_RESOTRE)->ShowWindow(SW_SHOW);
		(CStatic*)GetDlgItem(IDC_STATIC_LICENSE_RESTOREINFO)->ShowWindow(SW_SHOW);
		(CStatic*)GetDlgItem(IDC_STATIC_LICENSE_RESTORE_TIP)->ShowWindow(SW_SHOW);
		(CStatic*)GetDlgItem(IDC_STATIC_LICENSE_RESTORE_INFO2)->ShowWindow(SW_SHOW);
		
		GetDlgItem(IDC_BUTTON_BROWSE_RESTORE_PATH)->ShowWindow(SW_SHOW);	
		GetDlgItem(IDC_BUTTON_LICENSE_RESTORE)->ShowWindow(SW_SHOW);

	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
}

void CLicenseDlg::OnButtonReg() 
{
	// TODO: Add your control notification handler code here
	CString strNum, strEMail;
	CString strErrorInfo = g_lag.LoadString("label.info");
	
	BOOL bRet = TRUE;
	do 
	{
		GetDlgItemText(IDC_EDIT_NUM,strNum);
		GetDlgItemText(IDC_EDIT_EMAIL,strEMail);
		if (strNum.GetLength() == 0)
		{
			strErrorInfo += g_lag.LoadString("errors.nonum");
			bRet = FALSE ;
			break ;
		}

		//检查email是否合法
		char szErrInfo[1024] = {0};
		if( m_licAgent.IsEmailAddr(strEMail.GetBuffer(0),szErrInfo) == false)
		{
			strErrorInfo += g_lag.LoadString("errors.invalidemail");
			strErrorInfo += szErrInfo;
			bRet = FALSE ;
			break ;		
		}
		
		if (m_licAgent.EventLicense(strNum.GetBuffer(0), strEMail.GetBuffer(0)) == FALSE)
		{
			strErrorInfo += g_lag.LoadString("errors.regfailed");
			bRet = FALSE ;
			break ;	
		}
		
		strErrorInfo += g_lag.LoadString("label.reginfo");
	} while (0);
	
	(CStatic*)GetDlgItem(IDC_STATIC_ERROR_INFO)->ShowWindow(SW_SHOW);
	((CStatic*)GetDlgItem(IDC_STATIC_ERROR_INFO))->SetWindowText(strErrorInfo.GetBuffer(0));
	
}

HBRUSH CLicenseDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
// 	if(pWnd->GetDlgCtrlID()==IDC_STATIC_ERROR_INFO) 
// 		pDC->SetTextColor(RGB(255,0,0)); //设置字体颜色为蓝色
// 	
// 	return CreateSolidBrush(backColor);      //创建背景刷子	


	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CLicenseDlg::OnButtonLicenseBack() 
{
	// TODO: Add your control notification handler code here
	//检查是否输入了正确的路径
	CString strPath;
	GetDlgItemText(IDC_EDIT_LICENSE_BACK_PATH, strPath);
	if (strPath.GetLength() == 0)
	{
		MessageBox(g_lag.LoadString("message.selectlicpath"), g_lag.LoadString("title.licback"),MB_ICONWARNING);
		return ;
	}

	//检查备份文件是否存在
	if (PathFileExists(strPath.GetBuffer(0)))
	{
		int nRet = MessageBox(g_lag.LoadString("message.bestrowlicpath"), g_lag.LoadString("title.licback"), MB_YESNO| MB_ICONQUESTION);
		if (nRet == 7)
		{
			//选择否
			return ;
		}
	}

	char szMsg[MAX_PATH*4] = {0};
	int nRet = m_licAgent.BackLicense(strPath.GetBuffer(0));
	if (nRet == 0)
	{
		sprintf(szMsg, "%s%s",g_lag.LoadString("message.licbacksucc"), strPath.GetBuffer(0));
		MessageBox(szMsg, g_lag.LoadString("title.licback"), MB_ICONINFORMATION);
	}else
	{
		sprintf(szMsg, "%s%d",g_lag.LoadString("message.licbackfail"), nRet);
		MessageBox(szMsg, g_lag.LoadString("title.licback"), MB_ICONERROR);	
	}
}

#define FITER_LIC		TEXT("License Files (.lic)|*.lic|")
#define LICENSE_EXT		".lic"
void CLicenseDlg::OnButtonBrowseBackPath() 
{
	// TODO: Add your control notification handler code here
	char szPath[MAX_PATH] = {0};
	
	if( sloCommAgent::DoFileDialog(FALSE, szPath, FITER_LIC) )
	{
		strcat(szPath, LICENSE_EXT);
		SetDlgItemText(IDC_EDIT_LICENSE_BACK_PATH, szPath);
	}
}

void CLicenseDlg::OnButtonBrowseRestorePath() 
{
	// TODO: Add your control notification handler code here
	char szPath[MAX_PATH] = {0};
	
	if( sloCommAgent::DoFileDialog(TRUE, szPath, FITER_LIC) )
	{
		SetDlgItemText(IDC_EDIT_LICENSE_RESTORE_PATH, szPath);
	}
}

void CLicenseDlg::OnButtonLicenseRestore() 
{
	// TODO: Add your control notification handler code here
	//检查是否输入了正确的路径
	CString strPath;
	GetDlgItemText(IDC_EDIT_LICENSE_RESTORE_PATH, strPath);
	if (strPath.GetLength() == 0)
	{
		MessageBox(g_lag.LoadString("message.selectlicpath"), g_lag.LoadString("title.licrestore"), MB_ICONWARNING);
		return ;
	}
	
	char szMsg[MAX_PATH*4] = {0};
	int nRet = m_licAgent.RestoreLicense(strPath.GetBuffer(0));
	if (nRet == 0)
	{
		sprintf(szMsg, "%s\r\n", g_lag.LoadString("message.licrestoresucc"));
		MessageBox(szMsg, g_lag.LoadString("title.licrestore"), MB_ICONINFORMATION);
	}else
	{
		sprintf(szMsg, "%s%d",g_lag.LoadString("message.licrestorefail"), nRet);
		MessageBox(szMsg, g_lag.LoadString("title.licrestore"), MB_ICONERROR);	
	}	

}
