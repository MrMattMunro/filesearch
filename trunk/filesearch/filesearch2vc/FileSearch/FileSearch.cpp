// FileSearch.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

#define   EventName  (L"Global\\FS_Index_Notify")
int __stdcall NotifyService()
{
	int nRet = 0;
	HANDLE hevent = OpenEventW(EVENT_ALL_ACCESS,false,EventName);
	
	if ((hevent == NULL) || (hevent == INVALID_HANDLE_VALUE) )
	{
		DWORD dwErr = GetLastError();

		hevent = CreateEventW(NULL,true,false,EventName);
	}
	
	BOOL bsucc = SetEvent(hevent);
	if (bsucc)
		OutputDebugStringA("SetEvent succ");
	else
	{
		OutputDebugStringA("SetEvent failed");
		nRet = -1;
	}

	CloseHandle(hevent);

	return nRet;
}
