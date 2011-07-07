// sltFastSearchThread.cpp: implementation of the sltFastSearchThread class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FsUi.h"
#include "sltFastSearchThread.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

sltFastSearchThread::sltFastSearchThread():m_bShutdown(TRUE)
{
	s_bInit = FALSE;
	m_pSearchThread = NULL;
}

sltFastSearchThread::~sltFastSearchThread()
{
	join();
}

HRESULT sltFastSearchThread::startup()
{
	m_bShutdown = FALSE;
	start();
	
	return S_OK;
}

void sltFastSearchThread::shutdownflag()
{
	if (m_bShutdown == TRUE)
	{
		return ;
	}
	m_bShutdown = TRUE;
	if (NULL != m_pSearchThread)
	{
		m_pSearchThread->PostThreadMessage(WM_QUIT, 0, 0);
		Sleep(100);
	}

}

HRESULT sltFastSearchThread::Init(HWND hParentWnd)
{
	
	OutputDebugString("AfxBeginThread ");
	m_pSearchThread = (CSearchThread*)AfxBeginThread(RUNTIME_CLASS(CSearchThread), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED , 0);		
	m_pSearchThread->m_hParentWnd = hParentWnd;
	m_pSearchThread->ResumeThread();
	
	return S_OK;
}

int sltFastSearchThread::run()
{

	for(;;)
	{
		if(m_bShutdown)
			break;
		
		int nCount = m_postQueue.size();
		BOOL bExist = m_agent.IsKeyFileExist();

		if(nCount < 1 || bExist)
		{
			Sleep(100);
			continue;
		}
		
		FastItem postlog = m_postQueue.getNext();
		
		BOOL bsucc = DoLog(postlog);		
		if(!bsucc)
		{
			
		}
		
		Sleep(100);
	}
	
	return 0;
}

BOOL sltFastSearchThread::DoLog(FastItem fast)
{
	//不存在的场合将用户输入的关键字写入
	//keyWord.properties文件,格式如下:
	//keyword=
	//id=
	//写入keyword和id字段
	sloCommAgent::WritePropertyfileString("keyword", fast.szKey, m_agent.m_szKeyPath);
	sloCommAgent::WritePropertyfileString("id", fast.szID, m_agent.m_szKeyPath);
	
	int nPostCount = 0;
	while(nPostCount < 10)
	{
		OutputDebugString("post WM_SEARCH_MSG ");
		if( m_pSearchThread->PostThreadMessage(WM_SEARCH_MSG, 0, 0) )
		{
			OutputDebugString("PostThreadMessage succ");
			break ;
		}else
		{	
			OutputDebugString("PostThreadMessage failed");
			nPostCount++;
		}
	}
	return TRUE;
}

void sltFastSearchThread::PostMsg(FastItem postlog)
{
	m_postQueue.add(postlog);	
}