// FsUi.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "FsUi.h"
#include "CustomCiHuiDlg.h"
#include "SetAttributeDlg.h"

#include "sltCreateIndexDlgThread.h"
#include "sltModifyIndexDlgThread.h"
#include "sltSetSheetDlgThread.h"
#include "sltFastSearchDlgThread.h"

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
// CFsUiApp

BEGIN_MESSAGE_MAP(CFsUiApp, CWinApp)
	//{{AFX_MSG_MAP(CFsUiApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFsUiApp construction

CFsUiApp::CFsUiApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CFsUiApp object

CFsUiApp theApp;
sloLanguageAgent g_lag;
sloSkinAgent	g_skin;

DWORD g_dwApplyID = 0;

BOOL CFsUiApp::InitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class

	g_lag.GetLanguage();
	g_skin.InitSkin();

	return CWinApp::InitInstance();
}


//////////////////////////////////////////////////////////////////////////
/*
  功能：创建索引
*/
DWORD __stdcall FsCreateIndex()
{
	if (sltCreateIndexDlgThread::getInstance() == NULL)
		sltCreateIndexDlgThread::newInstance();	

	sltCreateIndexDlgThread::getInstance()->startup();
	
	return 0;
}


/*
  功能：修改索引
*/
DWORD __stdcall FsModifyIndex(int nID)
{
	if (sltModifyIndexDlgThread::getInstance() == NULL)
		sltModifyIndexDlgThread::newInstance();	
	
	sltModifyIndexDlgThread::getInstance()->startup(nID);

	return 0;
}


/*
  功能：快速查找页面
*/
DWORD __stdcall FsFastSearch()
{
	if (sltFastSearchDlgThread::getInstance() == NULL)
		sltFastSearchDlgThread::newInstance();	
	
	sltFastSearchDlgThread::getInstance()->startup();
	
	return 0;
}

/*
  功能：系统设置界面
*/
DWORD __stdcall FsSetSheet()
{
	if (sltSetSheetDlgThread::getInstance() == NULL)
		sltSetSheetDlgThread::newInstance();	
	
	sltSetSheetDlgThread::getInstance()->startup();
	
	return 0;
}

//////////////////////////////////////////////////////////////////////////
///////////////////////////////// 未用  //////////////////////////////////
/*
  功能：自定义词汇
*/
DWORD __stdcall FsImportCustomCiHui()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CCustomCiHuiDlg cihuidlg;
	if(IDOK == cihuidlg.DoModal())
	{
		
		return 0;
	}
	
	return 0;
}

/*
  功能：设置界面
*/
DWORD __stdcall FsSetAttribute()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	OutputDebugString("===========Enter in FsSetAttribute!");
	CSetAttributeDlg set;
	if(IDOK == set.DoModal())
	{	
		return 0;
	}
	
	return 0;
}
