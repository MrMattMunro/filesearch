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
	if (m_hevent)
	{
		CloseHandle(m_hevent);
	}

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
			OutputDebugStringA("WAIT_OBJECT_0 ");

			//ÖØÆô¼à¿ØÄ£¿é
			m_dirmon.StopMonitor();

			Sleep(500);

			m_dirmon.StartMonitor();

			ResetEvent(m_hevent);
			
			break;
		default:
			break;
		}		

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
			OutputDebugStringA("CreateEventW failed");

	}

	return 1;
}
