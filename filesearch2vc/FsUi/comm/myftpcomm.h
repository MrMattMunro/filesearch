// myftpcomm.h: interface for the myftpcomm class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYFTPCOMM_H__50FE3A53_13FC_4A62_8D7E_8C4965326F3A__INCLUDED_)
#define AFX_MYFTPCOMM_H__50FE3A53_13FC_4A62_8D7E_8C4965326F3A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include < afxinet.h > 

class myftpcomm  
{
public:
	myftpcomm();
	virtual ~myftpcomm();

	int GetFtpConnection(LPCTSTR pstrServer,
						LPCTSTR pstrUserName = NULL, 
						LPCTSTR pstrPassword = NULL,
						INTERNET_PORT nPort = INTERNET_INVALID_PORT_NUMBER,
						BOOL bPassive = FALSE);
	void Disconnect();

	BOOL SetCurrentDirectory(LPCTSTR pstrDirName);
	BOOL GetCurrentDirectory(LPTSTR pstrDirName, LPDWORD lpdwLen) const;

	BOOL RemoveDirectory(LPCTSTR pstrDirName);
	BOOL CreateDirectory(LPCTSTR pstrDirName);
	BOOL Rename(LPCTSTR pstrExisting, LPCTSTR pstrNew);
	BOOL Remove(LPCTSTR pstrFileName);
	
	BOOL PutFile(LPCTSTR pstrLocalFile, LPCTSTR pstrRemoteFile,
		DWORD dwFlags = FTP_TRANSFER_TYPE_BINARY, DWORD dwContext = 1);
	
	BOOL GetFile(LPCTSTR pstrRemoteFile, LPCTSTR pstrLocalFile,
		BOOL bFailIfExists = TRUE,
		DWORD dwAttributes = FILE_ATTRIBUTE_NORMAL,
		DWORD dwFlags = FTP_TRANSFER_TYPE_BINARY, DWORD dwContext = 1);
private:
	CInternetSession  *m_pInetSession;
	CFtpConnection *m_pFtpConnection;
};

#endif // !defined(AFX_MYFTPCOMM_H__50FE3A53_13FC_4A62_8D7E_8C4965326F3A__INCLUDED_)
