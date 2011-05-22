// FsUi.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "FsUi.h"
#include "CreateIndexDlg.h"
#include "CustomCiHuiDlg.h"
#include "ModifyIndexDlg.h"
#include "SetAttributeDlg.h"
#include "FastSearchDlg.h"
#include "LicenseDlg.h"
#include "SkinDlg.h"
#include "PropertyPageTaskPanelNavigator.h"
#include "sloSkinAgent.h"

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

BOOL CFsUiApp::InitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
//	SetDialogBkColor(RGB(243,243,243),RGB(0,0,0));
//	SetDialogBkColor(RGB(230,235,235),RGB(0,0,0));

	g_lag.GetLanguage();
	g_skin.InitSkin();

// 	TCHAR szStylesPath[_MAX_PATH];
// 	
// 	VERIFY(::GetModuleFileName(
// 		AfxGetApp()->m_hInstance, szStylesPath, _MAX_PATH));		
// 	
// 	m_strStylesPath = szStylesPath;
// 	int nIndex  = m_strStylesPath.ReverseFind(_T('\\'));
// 	if (nIndex > 0) {
// 		m_strStylesPath = m_strStylesPath.Left(nIndex);
// 	}
// 	else {
// 		m_strStylesPath.Empty();
// 	}
// 	m_strStylesPath += _T("\\Styles\\");
// 	
// 	
// 	//XTPSkinManager()->AddColorFilter(new CXTPSkinManagerColorFilterColorize(50, 100, 1));
// 	
// 	XTPSkinManager()->SetApplyOptions(XTPSkinManager()->GetApplyOptions() | xtpSkinApplyMetrics);
// //	XTPSkinManager()->LoadSkin(m_strStylesPath + _T("WinXP.Luna.cjstyles"), _T("NormalBlue.ini"));	
// 	//Vista,WinXP.Luna,WinXP.Royale, Office2007
// 	XTPSkinManager()->LoadSkin(m_strStylesPath + _T("Office2007.cjstyles"), _T("NormalBlue.ini"));

	return CWinApp::InitInstance();
}


//////////////////////////////////////////////////////////////////////////
/*
  功能：创建索引
*/
DWORD __stdcall FsCreateIndex()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	OutputDebugString("===========Enter in FsCreateIndex!");
	CCreateIndexDlg createindexdlg;
	if(IDOK == createindexdlg.DoModal())
	{
		
		return 0;
	}
	
	return 0;
}


/*
  功能：修改索引
*/
DWORD __stdcall FsModifyIndex(int nID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CModifyIndexDlg modifyindexdlg;
	modifyindexdlg.SetIndexID(nID);
	if(IDOK == modifyindexdlg.DoModal())
	{	
		return 0;
	}
	
	return 0;
}

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


DWORD dwFastDlgExist = 0;
/*
  功能：快速查找页面
*/
DWORD __stdcall FsFastSearch()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (dwFastDlgExist == 0)
	{
		dwFastDlgExist = 1;
		CFastSearchDlg dlg;
		dlg.DoModal();

		dwFastDlgExist = 0;
	}

	return 0;
}


DWORD g_dwApplyID = 0;

/*
  功能：系统设置界面
*/
DWORD __stdcall FsSetSheet()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	OutputDebugString("===========Enter in FsSetSheet!");

	CXTPPropertySheet ps(g_lag.LoadString("title.set"));
	
	CPropertyPageTaskPanelNavigator* pList = new CPropertyPageTaskPanelNavigator();
	
	ps.SetNavigator(pList);
	ps.m_psh.dwFlags &= (~PSH_HASHELP);

	CCustomCiHuiDlg		cihuidlg;
	CSetAttributeDlg	attrdlg;
	CLicenseDlg			licdlg;
	CSkinDlg			skindlg;
	ps.AddPage(&attrdlg);
	ps.AddPage(&cihuidlg);
	ps.AddPage(&skindlg);
	ps.AddPage(&licdlg);

	ps.SetResizable();

	ps.DoModal();

	return 0;
}