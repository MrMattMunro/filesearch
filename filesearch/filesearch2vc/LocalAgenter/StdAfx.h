// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__285FC4D6_ED38_4F17_AA94_31D3B7CAC43A__INCLUDED_)
#define AFX_STDAFX_H__285FC4D6_ED38_4F17_AA94_31D3B7CAC43A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN        // Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>       // MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>         // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


#include <XTToolkitPro.h>    // Xtreme Toolkit Pro components
#include "resource.h"

#include <WinSock2.h>
#pragma  warning(disable : 4284)
#pragma comment(lib, "ws2_32.lib")

#include <vector>
#include <string>
using namespace std;

#include "mysqlcomm.h"
#include "sloMysqlAgent.h"
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__285FC4D6_ED38_4F17_AA94_31D3B7CAC43A__INCLUDED_)
