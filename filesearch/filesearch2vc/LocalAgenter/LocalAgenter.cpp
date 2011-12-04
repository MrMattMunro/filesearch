// LocalAgenter.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "LocalAgenter.h"
#include "LocalAgenterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLocalAgenterApp

BEGIN_MESSAGE_MAP(CLocalAgenterApp, CWinApp)
	//{{AFX_MSG_MAP(CLocalAgenterApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLocalAgenterApp construction

CLocalAgenterApp::CLocalAgenterApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CLocalAgenterApp object

CLocalAgenterApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CLocalAgenterApp initialization
//#define SKIN_PATH	"D:\\Program Files\\Codejock Software\\MFC\\Xtreme ToolkitPro v13.2.1\\Bin\\vc60\\Styles\\Office2007.cjstyles"
#define SKIN_PATH	"C:\\Program Files\\slfile\\client\\Styles\\Office2007.cjstyles"

#define SKIN_TYPE	"LightBlue.ini"
#define SKIN_TYPE2	"Aqua"
BOOL CLocalAgenterApp::InitInstance()
{
	AfxEnableControlContainer();
	
	XTPSkinManager()->SetApplyOptions(XTPSkinManager()->GetApplyOptions() | xtpSkinApplyMetrics);
	
	XTPSkinManager()->LoadSkin(SKIN_PATH, SKIN_TYPE);
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();         // Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();   // Call this when linking to MFC statically
#endif

	CLocalAgenterDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
