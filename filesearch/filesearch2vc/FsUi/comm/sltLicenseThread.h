// sltLicenseThread.h: interface for the sltLicenseThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLTLICENSETHREAD_H__8D8E9452_A62A_43E0_854E_C2BAE2FBA085__INCLUDED_)
#define AFX_SLTLICENSETHREAD_H__8D8E9452_A62A_43E0_854E_C2BAE2FBA085__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Thread.h"
#include "LicenseDlg.h"

class sltLicenseThread  :public Singleton<sltLicenseThread>, public Thread  
{
public:
	sltLicenseThread();
	virtual ~sltLicenseThread();
	
	HRESULT startup(char* szNum, char* szMail, CLicenseDlg* licdlg);
	
private:
	virtual int run();

	sloLicenseAgent m_licAgent;
	
	char m_szNum[MAX_PATH];
	char m_szEmail[MAX_PATH];
	CLicenseDlg* m_licdlg;
};

#endif // !defined(AFX_SLTLICENSETHREAD_H__8D8E9452_A62A_43E0_854E_C2BAE2FBA085__INCLUDED_)
