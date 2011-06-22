// slLogSendThread.cpp: implementation of the slLogSendThread class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DirMonitor.h"
#include "slLogSendThread.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

slLogSendThread::slLogSendThread()
{
	m_bInit = FALSE;
}

slLogSendThread::~slLogSendThread()
{
	shutdown();
}

void slLogSendThread::AddLog(File_Action_Log FileLog)
{
	m_postQueue.add(FileLog);	
}

void slLogSendThread::shutdown()
{
	m_bShutdown = TRUE;
}

HRESULT slLogSendThread::startup()
{
	m_bShutdown = FALSE;
	start();
	
	return S_OK;
}


int slLogSendThread::run()
{
	BOOL bsucc = FALSE;
	
	for(;;)
	{
		if(m_bShutdown)
			break;
		
		int nCount = m_postQueue.size();
		if(nCount < 1)
		{
			Sleep(500);
			continue;
		}
		
		File_Action_Log FileLog = m_postQueue.getNext();		
		if(!DoWithLog(FileLog))
		{
			//add failed code
//			AddLog(FileLog);
		}
		Sleep(200);
	}
	
	return 0;
}

BOOL slLogSendThread::DoWithLog(File_Action_Log FileLog)
{
	//调用数据库模块，写数据库
	return m_mysqlAgent.LogRecord(FileLog);
}