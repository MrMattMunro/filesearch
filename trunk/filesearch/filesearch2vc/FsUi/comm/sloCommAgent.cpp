// sloCommAgent.cpp: implementation of the sloCommAgent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "FsUi.h"
#include "sloCommAgent.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

sloCommAgent::sloCommAgent()
{

}

sloCommAgent::~sloCommAgent()
{

}

char* sloCommAgent::GetCurTime(int nAddYear)
{
	char *pszTime = new char[30];
	memset(pszTime, NULL, 30);
	SYSTEMTIME stTime;
	GetLocalTime(&stTime);
	sprintf(pszTime,"%04d%02d%02d",
		stTime.wYear + nAddYear, stTime.wMonth, stTime.wDay);
	return pszTime;
}


string sloCommAgent::ConverSqlPath(string strPath)
{
	std::string strData = strPath;
	std::string strTmp = strData;
	
	int nPos1 = 0;
	int nPos2 = strTmp.find_first_of('\\');	
	while(nPos2 != -1)
	{
		strData.insert(nPos1 + nPos2,"\\");
		strTmp.erase(0,nPos2+1);
		nPos1 += nPos2+2;
		nPos2 = strTmp.find_first_of('\\');	
	}
	
	return strData;
}

BOOL sloCommAgent::DoFileDialog(BOOL bOpenFileDialog, char *szPath, LPCTSTR lpszFilter,LPCTSTR lpszDefExt  )
{
	CFileDialog hFileDlg(bOpenFileDialog,NULL ,
		NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST,	
		//TEXT("Text Files (.txt)|*.txt|Excel Files (.xls)|*.xls"),
		lpszFilter,
		NULL);
	if (lpszDefExt)
		hFileDlg.m_ofn.lpstrInitialDir=lpszDefExt;

	if(hFileDlg.DoModal() == IDOK)
	{
		CString strPath;
		strPath = hFileDlg.GetPathName();
		strcpy(szPath, strPath.GetBuffer(0));
		return TRUE;
	}	

	return FALSE;
}

BOOL sloCommAgent::IsFileExists(LPCTSTR lpszFileName) 
{ 
	
	WIN32_FIND_DATA wfd; 	
	BOOL bRet; 	
	HANDLE hFind; 	
	hFind = FindFirstFile(lpszFileName, &wfd); 
	bRet = hFind != INVALID_HANDLE_VALUE; 	
	FindClose(hFind); 
	return bRet; 
	
}   

BOOL sloCommAgent::WritePropertyfileString(LPCTSTR lpKeyName, LPCTSTR lpString, LPCTSTR lpFileName)
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

BOOL sloCommAgent::GetPropertyfileString(LPCTSTR lpKeyName, LPCTSTR lpDefault, LPTSTR lpReturnedString, DWORD nSize, LPCTSTR lpFileName)
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


