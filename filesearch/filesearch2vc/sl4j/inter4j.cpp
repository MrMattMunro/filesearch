#pragma once
#include "StdAfx.h"

DWORD __stdcall MsgBox(char* pText, char* pCaption, unsigned int uType)
{
	return MessageBox(NULL, pText, pCaption, uType);
}

DWORD __stdcall DoExe(char* szPath)
{
	ShellExecute(NULL, "open",szPath, NULL,NULL, SW_SHOWNORMAL); 

	return 0;
}
