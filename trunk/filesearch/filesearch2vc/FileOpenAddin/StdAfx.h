// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__C82F96F2_20F2_4AE5_B68F_965F8C6E28FE__INCLUDED_)
#define AFX_STDAFX_H__C82F96F2_20F2_4AE5_B68F_965F8C6E28FE__INCLUDED_

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


#import "C:\\Program Files\\Common Files\\Microsoft Shared\\OFFICE12\\mso.dll" rename_namespace("Office")
using namespace Office;

//#import "C:\\Program Files\\Common Files\\Microsoft Shared\\OFFICE11\\mso.dll" rename_namespace("Office") named_guids,exclude("Pages")
//using namespace Office;

#import "C:\\Program Files\\Common Files\\Microsoft Shared\\VBA\\VBA6\\VBE6EXT.olb" rename_namespace("VBE6")
using namespace VBE6;

#import "c:\\Program Files\\Microsoft Office\\OFFICE11\\MSWORD.OLB" rename("ExitWindows","ExitWindowsEx")
#import "c:\\Program Files\\Microsoft Office\\OFFICE11\\MSWORD.OLB" rename_namespace("Word"), raw_interfaces_only, named_guids ,exclude("Pages") 
using namespace Word;

// Excel导入库
#import "c:\\Program Files\\Microsoft Office\\Office12\\EXCEL.EXE" rename("RGB","_RGB"), rename("DialogBox","_DialogBox"), named_guids, rename_namespace("Excel"), exclude("IFont", "IPicture")
using namespace Excel;

// PowerPoint导入库
#import "c:\\Program Files\\Microsoft Office\\OFFICE11\\MSPPT.OLB" rename("ExitWindows", "pptExitWindows") ,  rename_namespace("PPT")
using namespace PPT;

#include <atlbase.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__C82F96F2_20F2_4AE5_B68F_965F8C6E28FE__INCLUDED_)
