// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__315C0CB2_7D43_4B55_ACCE_38F9D729A6DE__INCLUDED_)
#define AFX_STDAFX_H__315C0CB2_7D43_4B55_ACCE_38F9D729A6DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#ifndef WINVER
#define WINVER 0x0500
#else
#undef	WINVER
#define WINVER 0x0500
#endif

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
#include <winuser.h>

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
#include "tyu_common_interface_nolog.h"

#include "Singleton.h"
#include "log.h"


#include "Shlwapi.h"
#pragma comment(lib, "Shlwapi.lib")

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

#define THREME_NAME_NORMAL					"<Ĭ��Ƥ��>"
#define THREME_NAME_2007_Blue				"Office2007_Blue"
#define THREME_NAME_2007_LightBlue			"Office2007_LightBlue"
#define THREME_NAME_2007_Aqua				"Office2007_Aqua"
#define THREME_NAME_2007_Sliver				"Office2007_Sliver"
#define THREME_NAME_2007_Black				"Office2007_Black"

#define THREME_NAME_VISTA_Black				"Vista_Black"
#define THREME_NAME_VISTA_Black2			"Vista_Black2"
#define THREME_NAME_VISTA_Blue				"Vista_Blue"
#define THREME_NAME_VISTA_Sliver			"Vista_Sliver"

#define THREME_NAME_XP_ROYALE				"WinXP.Royale"

#define THREME_NAME_XP_LUNA_Blue			"WinXP.Luna_Blue"
#define THREME_NAME_XP_LUNA_HomeStead		"WinXP.Luna_HomeStead"
#define THREME_NAME_XP_LUNA_Metallic		"WinXP.Luna_Metallic"

#define FONT_SIZE		119

enum{PEN_STYLE_SOLID,PEN_STYLE_DASH,PEN_STYLE_DOT};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__315C0CB2_7D43_4B55_ACCE_38F9D729A6DE__INCLUDED_)
