// sltLicenseThread.cpp: implementation of the sltLicenseThread class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FsUi.h"
#include "sltLicenseThread.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

sltLicenseThread::sltLicenseThread()
{
	memset(m_szNum, NULL, MAX_PATH);
	memset(m_szEmail, NULL, MAX_PATH);
	m_licdlg = NULL;
}

sltLicenseThread::~sltLicenseThread()
{
	join();
}

HRESULT sltLicenseThread::startup(char* szNum, char* szMail, CLicenseDlg* licdlg)
{
	strcpy(m_szNum, szNum);
	strcpy(m_szEmail, szMail);
	m_licdlg = licdlg;
	start();

	return S_OK;
}

int sltLicenseThread::run()
{	
	Sleep(300);  //延迟的目的是防止g_lag.LoadString("label.info")文件被占用，取出的数据为空
	CString strErrorInfo = g_lag.LoadString("label.info");
	if (m_licAgent.EventLicense(m_szNum, m_szEmail) == FALSE)
	{
		//设置错误消息
		strErrorInfo += g_lag.LoadString("errors.regfailed");
	}else
		strErrorInfo += g_lag.LoadString("label.reginfo");

	OutputDebugString(strErrorInfo);
	((CStatic*)(m_licdlg->GetDlgItem(IDC_STATIC_ERROR_INFO)))->SetWindowText(strErrorInfo.GetBuffer(0));

	return 0;
}
