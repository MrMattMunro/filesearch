// sltIndexNotifyThread.cpp: implementation of the sltIndexNotifyThread class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "sltIndexNotifyThread.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define   EventName  (L"Global\\FS_Index_Notify")
sltIndexNotifyThread::sltIndexNotifyThread():m_bShutdown(TRUE)
{

}

sltIndexNotifyThread::~sltIndexNotifyThread()
{
	join();
}

HRESULT sltIndexNotifyThread::startup()
{
	m_bShutdown = FALSE;
	start();
	
	return S_OK;
}

void sltIndexNotifyThread::shutdown()
{
	m_bShutdown = TRUE;
	SetEvent(m_hevent);
}

int sltIndexNotifyThread::run()
{
	UINT dwWaitResult = 0;
	CreateIndexEvent();
	for(;;)
	{
		if(m_bShutdown)
			break;

		dwWaitResult = WaitForSingleObject(m_hevent,INFINITE);
		switch (dwWaitResult)
		{
		case WAIT_OBJECT_0:
			log.Print(LL_DEBUG_INFO,"Receive Event Global\\FS_Index_Notify!\r\n");

			if (m_dirmon.ResetMonitor() != 0)
			{
				log.Print(LL_DEBUG_INFO,"Receive Event ResetMonitor Failed\r\n");
			}

			ResetEvent(m_hevent);
			
			break;
		default:
			break;
		}		

	}

	if (m_hevent)
	{
		CloseHandle(m_hevent);
	}

	
	return 0;
	
}

int sltIndexNotifyThread::CreateIndexEvent()
{
	UINT dwWaitResult = 0;

	m_hevent = OpenEventW(EVENT_ALL_ACCESS,false,EventName);	
	if ((m_hevent == NULL) || (m_hevent == INVALID_HANDLE_VALUE) )
	{
		// set SECURITY_DESCRIPTOR 
		SECURITY_DESCRIPTOR secutityDese; 
		::InitializeSecurityDescriptor(&secutityDese, SECURITY_DESCRIPTOR_REVISION); 
		::SetSecurityDescriptorDacl(&secutityDese,TRUE,NULL,FALSE); 
		
		SECURITY_ATTRIBUTES securityAttr; 
		
		// set SECURITY_ATTRIBUTES 
		securityAttr.nLength = sizeof SECURITY_ATTRIBUTES; 
		securityAttr.bInheritHandle = FALSE; 
		securityAttr.lpSecurityDescriptor = &secutityDese; 
		
		m_hevent = CreateEventW(&securityAttr,true,false,EventName);
		if (m_hevent != NULL && m_hevent != INVALID_HANDLE_VALUE)
		{
			OutputDebugStringA("CreateEventW succ");
		}else
			log.Print(LL_DEBUG_INFO,"[Error]CreateEventW Global\\FS_Index_Notify failed!\r\n");

	}

	return 1;
}
