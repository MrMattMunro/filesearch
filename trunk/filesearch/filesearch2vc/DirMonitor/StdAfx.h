// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__F68E6482_34F3_4137_B263_561708076EFA__INCLUDED_)
#define AFX_STDAFX_H__F68E6482_34F3_4137_B263_561708076EFA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#define _WIN32_WINNT 0x400 //so that I can use ReadDirectoryChanges

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

//#include <winbase.h>

#include <WinSock2.h>
#pragma  warning(disable : 4284)
#pragma comment(lib, "ws2_32.lib")

#import "msxml.dll" //引入类型库
#import "msxml3.dll"
using namespace MSXML2;

#include "comm.h"
#include <vector>
#include <string>
using namespace std;

#define dcdebug if (false) printf
#define dcassert(exp) 
#define dcdrun(exp)

#include "omnithread.h"
#include "tyu_common_interface.h"

#include "slLogSendThread.h"
#include "slXmlAgent.h"


extern Log log;
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__F68E6482_34F3_4137_B263_561708076EFA__INCLUDED_)
