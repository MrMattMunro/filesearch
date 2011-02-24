// sloCustomCiHuiAgent.cpp: implementation of the sloCustomCiHuiAgent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FsUi.h"
#include "sloCustomCiHuiAgent.h"
#include "sloRegAgent.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

sloCustomCiHuiAgent::sloCustomCiHuiAgent()
{
	memset(m_szpropertiesPath, NULL, MAX_PATH);
	memset(m_szcustomtxtPath, NULL, MAX_PATH);
}

sloCustomCiHuiAgent::~sloCustomCiHuiAgent()
{

}

#define DICFILE_NAME	"dicfile"
#define OVERFLAG_NAME	"isoverwrite"

BOOL sloCustomCiHuiAgent::EventCustomCiHui(BOOL bOver, char* pszFilePath)
{
	BOOL bSucc = FALSE;
	CString strOver = "false";
	if (bOver)
	{
		strOver = "true";
	}

	GetProFilePath();
	
	bSucc = WritePropertyfileString(DICFILE_NAME, pszFilePath, m_szpropertiesPath);
	
	bSucc = WritePropertyfileString(OVERFLAG_NAME, strOver.GetBuffer(0), m_szpropertiesPath);

	return bSucc;
}

BOOL sloCustomCiHuiAgent::IsFileExists(LPCTSTR lpszFileName) 
{ 
	
	WIN32_FIND_DATA wfd; 	
	BOOL bRet; 	
	HANDLE hFind; 	
	hFind = FindFirstFile(lpszFileName, &wfd); 
	bRet = hFind != INVALID_HANDLE_VALUE; 	
	FindClose(hFind); 
	return bRet; 
	
}   

BOOL sloCustomCiHuiAgent::WritePropertyfileString(LPCTSTR lpKeyName, LPCTSTR lpString, LPCTSTR lpFileName)
{
	CString strLocaleFile = lpFileName;
	CStdioFile file;
	CString line;
	BOOL bResult = FALSE;
	if(!strLocaleFile.IsEmpty())
	{
		if(IsFileExists(strLocaleFile.GetBuffer(0)) && file.Open(strLocaleFile, CFile::modeReadWrite | CFile::typeText))
		{
			int nline = 0;
			while(file.ReadString(line))
			{
				nline++;
			}
			CString *lineArray = new CString[nline];
			file.Seek(0, CFile::begin);
			BOOL isContains = FALSE;
			int iPosh = file.GetPosition();
			BOOL isRead = file.ReadString(line);
			int iPost = file.GetPosition();
			int iPosIndex = -1;
			for(int i=0;isRead;i++)
			{
				lineArray[i] = line;
				if(!line.IsEmpty() && line.Find(lpKeyName)>=0){
					int iPos = line.Find(_T("="));
					CString sfinder = line.Left(iPos);
					sfinder.TrimLeft();
					sfinder.TrimRight();
					if(!sfinder.IsEmpty() && lpKeyName == sfinder)
					{
						isContains = TRUE;
						iPosIndex = i;
					}
				}
				int preLineLength = line.GetLength();
				isRead = file.ReadString(line);
				if(!isRead && line.IsEmpty())
				{
					iPost = iPosh + preLineLength;
				}
				else
				{
					iPosh = iPost;
					iPost = file.GetPosition();
				}
			}
			if(!isContains)
			{
				file.Seek(iPost, CFile::begin);
				line = _T("");
				line = line + _T("\n") + lpKeyName + _T("=") + lpString + _T("\n");
				file.WriteString(line);
			}
			else if(iPosIndex>=0)
			{
				file.SetLength(0);
				file.Seek(0, CFile::begin);
				for(int j=0;j<nline;j++)
				{
					if(j==iPosIndex)
					{
						line = _T("");
						line = line + lpKeyName + _T("=") + lpString + _T("\n");
						file.WriteString(line);
					}
					else 
						file.WriteString(lineArray[j]+_T("\n"));
				}
			}
			file.Close();
			delete[] lineArray;
			bResult = TRUE;
		}
		else if(file.Open(strLocaleFile, CFile::modeCreate | CFile::modeReadWrite | CFile::typeText))
		{
			file.Seek(0, CFile::begin);
			line = _T("");
			line = line + lpKeyName + _T("=") + lpString + _T("\n");
			file.WriteString(line);
			file.Close();
			bResult = TRUE;
		}
	}
	return bResult;
}

BOOL sloCustomCiHuiAgent::GetPropertyfileString(LPCTSTR lpKeyName, LPCTSTR lpDefault, LPTSTR lpReturnedString, DWORD nSize, LPCTSTR lpFileName)
{
	CString strLocaleFile = lpFileName;
	CStdioFile file;
	CString line;
	BOOL bResult = FALSE;
	CString sfinder = _T("");
	if(!strLocaleFile.IsEmpty())
	{
		if(IsFileExists(strLocaleFile.GetBuffer(0)) && file.Open(strLocaleFile, CFile::modeReadWrite | CFile::typeText))
		{
			file.Seek(0, CFile::begin);
			BOOL isContains = FALSE;
			int iPosh = file.GetPosition();
			BOOL isRead = file.ReadString(line);
			int iPost = file.GetPosition();
			int iPosIndex = -1;
			for(int i=0;isRead;i++)
			{
				if(!line.IsEmpty() && line.Find(lpKeyName)>=0){
					int iPos = line.Find(_T("="));
					sfinder = line.Left(iPos);
					sfinder.TrimLeft();
					sfinder.TrimRight();
					if(!sfinder.IsEmpty() && lpKeyName == sfinder)
					{
						sfinder = line.Right(line.GetLength()-iPos-1);
						sfinder.TrimLeft();
						sfinder.TrimRight();
						bResult = TRUE;
						break;
					}
				}
				isRead = file.ReadString(line);
			}
		}
	}
	if(bResult)
		lstrcpyn(lpReturnedString, sfinder, nSize);
	else
		lstrcpyn(lpReturnedString, lpDefault, nSize);
	
	return bResult;
}

#define  CUS_PRO_NAME "dic\\custumdic.properties"
#define  CUS_TXT_NAME "dic\\custom.dic"
BOOL sloCustomCiHuiAgent::GetProFilePath()
{
	char szFileExePath[MAX_PATH] = {0};
	sloRegAgent reg;
	if(reg.ReadInstallPath(szFileExePath))
	{  
		char drive[_MAX_DRIVE];
		char dir[_MAX_DIR];
		char fname[_MAX_FNAME];
		char ext[_MAX_EXT];
		
		_splitpath( szFileExePath, drive, dir, fname, ext );
		sprintf(m_szpropertiesPath,"%s%s%s",drive, dir,CUS_PRO_NAME);
		sprintf(m_szcustomtxtPath,"%s%s%s",drive, dir,CUS_TXT_NAME);
	}
	
	return FALSE;
}
