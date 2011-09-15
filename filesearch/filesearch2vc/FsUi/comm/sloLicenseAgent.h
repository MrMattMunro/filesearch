// sloLicenseAgent.h: interface for the sloLicenseAgent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLOLICENSEAGENT_H__F2E42359_A761_4578_98AD_9E59D39082D4__INCLUDED_)
#define AFX_SLOLICENSEAGENT_H__F2E42359_A761_4578_98AD_9E59D39082D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class sloLicenseAgent :public mysqlcomm
{
public:
	sloLicenseAgent();
	virtual ~sloLicenseAgent();

	int Init();
	
	BOOL EventLicense(char* szOrderNo, char* szEmail); 

	bool IsEmailAddr(char* str,char* error);

	int BackLicense(char* szBackPath);
	int RestoreLicense(char* szResotrePath);	

private:
	void SetLicenseInfo(char* szOrderNo, char* szEmail);
	int	 AddLicenseRec(char *szHasDownload);

	int  UpLoadLicFiles();
	int  BuildLicenseFile();
	BOOL GetLicensePath();

	void ClearPath();
public:
	LicenseInfo m_LicInfo;

	char m_szOldLicBatPath[MAX_PATH];
	char m_szLicBatPath[MAX_PATH];
	char m_szLicTxtPath[MAX_PATH];

	char m_szServerLicBatPath[MAX_PATH];
	char m_szServerLicTxtPath[MAX_PATH];

	char m_szUpdateProPath[MAX_PATH];


	BOOL m_bReg;
	BOOL m_bDown;
};

#endif // !defined(AFX_SLOLICENSEAGENT_H__F2E42359_A761_4578_98AD_9E59D39082D4__INCLUDED_)
