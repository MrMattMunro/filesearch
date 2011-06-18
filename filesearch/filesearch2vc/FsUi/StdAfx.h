// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__315C0CB2_7D43_4B55_ACCE_38F9D729A6DE__INCLUDED_)
#define AFX_STDAFX_H__315C0CB2_7D43_4B55_ACCE_38F9D729A6DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC Automation classes
#endif // _AFX_NO_OLE_SUPPORT


#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>			// MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>			// MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT

#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
//#include <afxsock.h>		// MFC socket extensions

#include <WinSock2.h>
#pragma  warning(disable : 4284)
#pragma comment(lib, "ws2_32.lib")

#define dcdebug if (false) printf
#define dcassert(exp) 
#define dcdrun(exp)

#include <vector>
#include <string>
using namespace std;

#include "omnithread.h"
#include "tyu_common_interface.h"

#include "Singleton.h"
#include "log.h"

//////////////////////////////////////////////////////////////////////////
#include "comm.h"
#include "sloCommAgent.h"
#include "mysqlcomm.h"
#include <XTToolkitPro.h>   // Codejock Software Components
//////////////////////////////////////////////////////////////////////////

#include "sloSkinAgent.h"
#include "sloLanguageAgent.h"
extern sloLanguageAgent g_lag;

#define WM_PROGRESS_MSG   WM_USER + 100

#define WORD_NAME	"word"
#define EXCEL_NAME	"excel"
#define PPT_NAME	"ppt"
#define PDF_NAME	"pdf"
#define TXT_NAME	"txt"
#define HTML_NAME	"html"

#define THREME_NAME_NORMAL			"<Ä¬ÈÏÆ¤·ô>"
#define THREME_NAME_2007			"Office2007"
#define THREME_NAME_VISTA			"Vista"
#define THREME_NAME_XP_ROYALE		"WinXP.Royale"
#define THREME_NAME_XP_LUNA			"WinXP.Luna"

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__315C0CB2_7D43_4B55_ACCE_38F9D729A6DE__INCLUDED_)
