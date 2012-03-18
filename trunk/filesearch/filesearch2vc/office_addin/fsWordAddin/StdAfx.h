// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__CC64286A_0714_439F_8304_B5E6F925FFCE__INCLUDED_)
#define AFX_STDAFX_H__CC64286A_0714_439F_8304_B5E6F925FFCE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif
#define _ATL_APARTMENT_THREADED

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>

//#define dcdebug if (false) printf
#define dcassert(exp) 
#define dcdrun(exp)

#include <io.h>
#include <cassert>

#include <string>
using namespace std;

#import "C:\\Program Files\\Common Files\\DESIGNER\MSADDNDR.DLL" raw_interfaces_only, raw_native_types, no_namespace, named_guids

//#define  OASYS

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#import "C:\\Program Files\\Common Files\\Microsoft Shared\\OFFICE11\\mso.dll" rename_namespace("Office") named_guids,exclude("Pages")
using namespace Office;

#import "C:\\Program Files\\Common Files\\Microsoft Shared\\VBA\\VBA6\\VBE6EXT.olb" rename_namespace("VBE6")
using namespace VBE6;

#import "C:\\Program Files\\Microsoft Office\\OFFICE11\\MSWORD.OLB" rename("ExitWindows","ExitWindowsEx")
#import "C:\\Program Files\\Microsoft Office\\OFFICE11\\MSWORD.OLB" rename_namespace("Word"), raw_interfaces_only, named_guids ,exclude("Pages")
using namespace Word;
#endif // !defined(AFX_STDAFX_H__CC64286A_0714_439F_8304_B5E6F925FFCE__INCLUDED)
