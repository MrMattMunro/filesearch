// FileSearch.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "log.h"

extern Log log;
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH: 
		{
			char szSystemPath[MAX_PATH] = {0};
			GetSystemDirectory(szSystemPath, MAX_PATH);
			char szLogPath[MAX_PATH] = {0};
			sprintf(szLogPath, "%s\\FileSearch.log", szSystemPath);
			log.SetFile(szLogPath, true);
			log.SetMode(Log::ToFile);
			log.SetLevel(LL_DEBUG_INFO);
		}
		break;
	case DLL_PROCESS_DETACH:
		{				
			
		}
		break;
	case DLL_THREAD_ATTACH:
		
		break;
	case DLL_THREAD_DETACH:
		
		break;
    }
    return TRUE;
}

#define   EventName  (L"Global\\FS_Index_Notify")
int __stdcall NotifyService()
{
	int nRet = 0;
	log.Print(LL_DEBUG_INFO,"Enter NotifyService\r\n");
	HANDLE hevent = OpenEventW(EVENT_ALL_ACCESS,false,EventName);
	
	if ((hevent == NULL) || (hevent == INVALID_HANDLE_VALUE) )
	{
		log.Print(LL_DEBUG_INFO,"OpenEventW Global\\FS_Index_Notify !GetLastError=%d\r\n",GetLastError());

		hevent = CreateEventW(NULL,true,false,EventName);
	}
	
	if (!SetEvent(hevent))
	{	
		log.Print(LL_DEBUG_INFO,"SetEvent Failed!GetLastError=%d \r\n",GetLastError());
		nRet = -1;
	}

	CloseHandle(hevent);
	log.Print(LL_DEBUG_INFO,"Leave NotifyService\r\n");
	return nRet;
}
