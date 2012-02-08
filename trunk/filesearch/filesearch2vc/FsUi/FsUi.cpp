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

#include "FloatWnd.h"

#include "AddinSavefileDlg.h"

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

	char szSystemPath[MAX_PATH] = {0};
	GetSystemDirectory(szSystemPath, MAX_PATH);
	char szLogPath[MAX_PATH] = {0};
	sprintf(szLogPath, "%s\\fsui.log", szSystemPath);
	flog.SetFile(szLogPath,true);
	flog.SetLevel(100);
	flog.SetMode(Log::ToFile );	

	return CWinApp::InitInstance();
}


//////////////////////////////////////////////////////////////////////////
/*
  功能：创建索引
*/
DWORD __stdcall FsCreateIndex()
{
	flog.Print(LL_DEBUG_INFO,"[info]Enter FsCreateIndex!\r\n");

	if (sltCreateIndexDlgThread::getInstance() == NULL)
		sltCreateIndexDlgThread::newInstance();	

	sltCreateIndexDlgThread::getInstance()->startup();
	
	flog.Print(LL_DEBUG_INFO,"[info]Leave FsCreateIndex!\r\n");
	return 0;
}


/*
  功能：修改索引
*/
DWORD __stdcall FsModifyIndex(int nID)
{
	flog.Print(LL_DEBUG_INFO,"[info]Enter FsModifyIndex!\r\n");

	if (sltModifyIndexDlgThread::getInstance() == NULL)
		sltModifyIndexDlgThread::newInstance();	
	
	sltModifyIndexDlgThread::getInstance()->startup(nID);

	flog.Print(LL_DEBUG_INFO,"[info]Leave FsModifyIndex!\r\n");
	return 0;
}


/*
  功能：快速查找页面
*/
DWORD __stdcall FsFastSearch()
{
	flog.Print(LL_DEBUG_INFO,"[info]Enter FsFastSearch!\r\n");

	if (sltFastSearchDlgThread::getInstance() == NULL)
		sltFastSearchDlgThread::newInstance();	
	
	sltFastSearchDlgThread::getInstance()->startup(0);
	
	flog.Print(LL_DEBUG_INFO,"[info]Leave FsFastSearch!\r\n");
	return 0;
}

DWORD __stdcall FsFastSearchEx()
{
	flog.Print(LL_DEBUG_INFO,"[info]Enter FsFastSearch!\r\n");
	
	if (sltFastSearchDlgThread::getInstance() == NULL)
		sltFastSearchDlgThread::newInstance();	
	
	sltFastSearchDlgThread::getInstance()->startup(1);
	
	flog.Print(LL_DEBUG_INFO,"[info]Leave FsFastSearch!\r\n");
	return 0;
}

/*
  功能：系统设置界面
*/
DWORD __stdcall FsSetSheet()
{
	flog.Print(LL_DEBUG_INFO,"[info]Enter FsSetSheet!\r\n");

	if (sltSetSheetDlgThread::getInstance() == NULL)
		sltSetSheetDlgThread::newInstance();	
	
	sltSetSheetDlgThread::getInstance()->startup();

	flog.Print(LL_DEBUG_INFO,"[info]Leave FsSetSheet!\r\n");	
	return 0;
}


/*
  功能：加载皮肤
*/
DWORD __stdcall FsLoadSkin()
{
	OutputDebugString("===========Enter in FsLoadSkin!");
	
	g_skin.InitSkin();
	
	return 0;
}


CFloatWnd* g_pFloatWnd = NULL;
/*
  功能：加载FloatWnd
  nshow:
       1 : show
	   0 : hide
*/
DWORD __stdcall FsLoadFloatWnd(int nShow)
{
	flog.Print(LL_DEBUG_INFO,"[info]Enter FsLoadFloatWnd!nShow=%d\r\n",nShow);	
	if(g_pFloatWnd == NULL)
	{		
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		g_pFloatWnd = new CFloatWnd;
		if (g_pFloatWnd == NULL)
		{
			flog.Print(LL_DEBUG_INFO,"[error]create CFloatWnd object failed!GetLastError=0x%x\r\n",GetLastError());
			return -1;
		}
		g_pFloatWnd->Create(IDD_FLOATWND,NULL);
	}


	if (nShow == 1)
	{
		g_pFloatWnd->ShowWindow(SW_SHOW);
	}else
		g_pFloatWnd->ShowWindow(SW_HIDE);

	g_pFloatWnd->OnUpdateTransparent(255);
	flog.Print(LL_DEBUG_INFO,"[info]Leave FsLoadFloatWnd!nShow=%d\r\n",nShow);	
	return 0;
}

/*
  功能：自定义词汇
*/
DWORD __stdcall FsShowSavefileDlg(char* pszFileName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CAddinSavefileDlg addindlg;
	addindlg.SetDcoumentPath(pszFileName);
	if(IDOK == addindlg.DoModal())
	{
		return 0;
	}
	
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
