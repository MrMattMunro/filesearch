#pragma once

// Change these values to use different versions
#define WINVER		0x0500
#define _WIN32_WINNT	0x0501
#define _WIN32_IE	0x0501
#define _RICHEDIT_VER	0x0200

#undef _ATL_MIN_CRT

#include <atlbase.h>
#include <atlwin.h>
#include <atlstr.h>
#include <atltrace.h>

#define _WTL_NO_CSTRING

#include <atlapp.h>
#include <atlframe.h>
#include <atlctrls.h>
#include <atlctrlx.h>
#include <atldlgs.h>
#include <atlcrack.h>
#include <atlmisc.h>

#include <tinyxml.h>
#include <bkwin/bkdlgview.h>
#include <bkwin/bkwndnotify.h>
#include <bkwin/bkatldefine.h>
#include <wtlhelper/whwindow.h>
