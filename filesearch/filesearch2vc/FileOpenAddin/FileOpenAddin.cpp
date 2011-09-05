// FileOpenAddin.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "FileOpenAddin.h"

#include "sloFileOpenAddin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CFileOpenAddinApp

BEGIN_MESSAGE_MAP(CFileOpenAddinApp, CWinApp)
	//{{AFX_MSG_MAP(CFileOpenAddinApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileOpenAddinApp construction

CFileOpenAddinApp::CFileOpenAddinApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance

}

/////////////////////////////////////////////////////////////////////////////
// The one and only CFileOpenAddinApp object

CFileOpenAddinApp theApp;

sloFileOpenAddin fileaddin;
DWORD __stdcall openWordFile(char* pFileName, int nPage, char* pKeyWords/* = NULL*/)
{
	return fileaddin.OpenFile_WORD(pFileName, nPage, pKeyWords);
}

DWORD __stdcall openExcelFile(char* pFileName, char* pSheet, int nRow, char* pKeyWords/* = NULL*/)
{
	return fileaddin.OpenFile_EXCEL(pFileName, pSheet, nRow, pKeyWords);
}

DWORD __stdcall openPPTFile(char* pFileName, int nPage, char* pKeyWords/* = NULL*/)
{
	return fileaddin.OpenFile_PPT(pFileName, nPage, pKeyWords);
}

DWORD __stdcall openPdfFile(char* pFileName, int nPage, char* pKeyWords/* = NULL*/)
{
	return fileaddin.OpenFile_PDF(pFileName, nPage, pKeyWords);
}

DWORD __stdcall openTxtFile(char* pFileName, int nRow, char* pKeyWords/* = NULL*/)
{
	return fileaddin.OpenFile_TXT(pFileName, nRow, pKeyWords);
}

BOOL CFileOpenAddinApp::InitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	char szSystemPath[MAX_PATH] = {0};
	GetSystemDirectory(szSystemPath, MAX_PATH);
	char szLogPath[MAX_PATH] = {0};
	sprintf(szLogPath, "%s\\fileopenaddin.log", szSystemPath);
	log.SetFile(szLogPath,true);
	log.SetLevel(100);
	log.SetMode(Log::ToFile );	

	return CWinApp::InitInstance();
}
