// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__14586B2D_996B_4EC6_89F6_D0E02282108D__INCLUDED_)
#define AFX_STDAFX_H__14586B2D_996B_4EC6_89F6_D0E02282108D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif
#define _ATL_APARTMENT_THREADED
//#pragma warning( disable : C4100)
#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>
#include <stdio.h>
#include <cassert>


#define dcassert(exp) 
#define dcdrun(exp)



#import "C:\\Program Files\\Common Files\\Microsoft Shared\\OFFICE11\\MSO.DLL" rename_namespace("Office")
using namespace Office;

#import "C:\\Program Files\\Common Files\\Microsoft Shared\\VBA\\VBA6\\VBE6EXT.olb" rename_namespace("VBE6")
using namespace VBE6;

#import "C:\\Program Files\\Microsoft Office\\Office11\\EXCEL.EXE" rename("RGB","_RGB"), rename("DialogBox","_DialogBox"), named_guids, rename_namespace("Excel"), exclude("IFont", "IPicture")
using namespace Excel;

#import "C:\\Program Files\\Common Files\\DESIGNER\\MSADDNDR.DLL" raw_interfaces_only, raw_native_types, no_namespace, named_guids 


#include <string>
using namespace std;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__14586B2D_996B_4EC6_89F6_D0E02282108D__INCLUDED)
