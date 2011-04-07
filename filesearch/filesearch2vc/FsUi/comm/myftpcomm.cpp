// myftpcomm.cpp: implementation of the myftpcomm class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FsUi.h"
#include "myftpcomm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

myftpcomm::myftpcomm()
{
	m_pFtpConnection = NULL;
	m_pInetSession = NULL;
}

myftpcomm::~myftpcomm()
{

}

int myftpcomm::GetFtpConnection(LPCTSTR pstrServer,
					 LPCTSTR pstrUserName /*= NULL*/, 
					 LPCTSTR pstrPassword/* = NULL*/,
					 INTERNET_PORT nPort /*= INTERNET_INVALID_PORT_NUMBER*/,
					 BOOL bPassive /*= FALSE*/)
{
	int nRet = 0;
	do 
	{
		m_pInetSession = new CInternetSession(AfxGetAppName(),1,PRE_CONFIG_INTERNET_ACCESS);
		try
		{
			m_pFtpConnection = m_pInetSession->GetFtpConnection(pstrServer, pstrUserName, pstrPassword, nPort, bPassive);
			break;
		}
		catch(CInternetException *pEx)
		{
			pEx->Delete();
			m_pFtpConnection=NULL;
			nRet = GetLastError();
			break;
		}
	} while (0);

	return nRet;
}

void myftpcomm::Disconnect()
{
	if (m_pFtpConnection != NULL)
	{
		m_pFtpConnection->Close();
		delete m_pFtpConnection;
		m_pFtpConnection = NULL;
	}

	if (m_pInetSession != NULL)
	{
		m_pInetSession->Close();
		delete m_pInetSession;
		m_pInetSession = NULL;
	}
}

BOOL myftpcomm::SetCurrentDirectory(LPCTSTR pstrDirName)
{
	if (m_pFtpConnection && m_pFtpConnection->SetCurrentDirectory(pstrDirName)) 
		return TRUE;
	else
		return FALSE;
	
	return TRUE;
}

BOOL myftpcomm::GetCurrentDirectory(LPTSTR pstrDirName, LPDWORD lpdwLen) const
{
	if (m_pFtpConnection && m_pFtpConnection->GetCurrentDirectory(pstrDirName, lpdwLen)) 
		return TRUE;
	else
		return FALSE;
	
	return TRUE;
}

BOOL myftpcomm::RemoveDirectory(LPCTSTR pstrDirName)
{
	if (m_pFtpConnection && m_pFtpConnection->RemoveDirectory(pstrDirName)) 
		return TRUE;
	else
		return FALSE;
	
	return TRUE;
}

BOOL myftpcomm::CreateDirectory(LPCTSTR pstrDirName)
{
	if (m_pFtpConnection && m_pFtpConnection->CreateDirectory(pstrDirName)) 
		return TRUE;
	else
		return FALSE;
	
	return TRUE;
}

BOOL myftpcomm::Rename(LPCTSTR pstrExisting, LPCTSTR pstrNew)
{
	if (m_pFtpConnection && m_pFtpConnection->Rename(pstrExisting, pstrNew)) 
		return TRUE;
	else
		return FALSE;
	
	return TRUE;
}

BOOL myftpcomm::Remove(LPCTSTR Remove)
{
	if (m_pFtpConnection && m_pFtpConnection->Remove(Remove)) 
		return TRUE;
	else
		return FALSE;
	
	return TRUE;
}

BOOL myftpcomm::PutFile(LPCTSTR pstrLocalFile, LPCTSTR pstrRemoteFile,
			 DWORD dwFlags/* = FTP_TRANSFER_TYPE_BINARY*/, DWORD dwContext/* = 1*/)
{
	if (m_pFtpConnection && m_pFtpConnection->PutFile(pstrLocalFile, pstrRemoteFile,dwFlags, dwContext)) 
		return TRUE;
	else
		return FALSE;
	
	return TRUE;
}

BOOL myftpcomm::GetFile(LPCTSTR pstrRemoteFile, 
						LPCTSTR pstrLocalFile,
						BOOL bFailIfExists/* = TRUE*/,
						DWORD dwAttributes/* = FILE_ATTRIBUTE_NORMAL*/,
						DWORD dwFlags/* = FTP_TRANSFER_TYPE_BINARY*/, 
						DWORD dwContext/*  = 1*/)
{
	if (m_pFtpConnection && m_pFtpConnection->GetFile(pstrLocalFile, pstrRemoteFile,dwFlags, dwContext)) 
		return TRUE;
	else
		return FALSE;
	
	return TRUE;
}