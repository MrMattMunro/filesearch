// sltDirMonitorThread.cpp: implementation of the sltDirMonitorThread class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DirMonitor.h"
#include "sltDirMonitorThread.h"
#include "slDirMonitor.h"

extern slXmlAgent		g_xmlFilterAgent;
extern slLogSendThread	g_LogSendThread;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

sltDirMonitorThread::sltDirMonitorThread()
{
	m_bInit = FALSE;
}

sltDirMonitorThread::~sltDirMonitorThread()
{
	shutdown();
}

void sltDirMonitorThread::shutdown()
{
	m_bShutdown = TRUE;
}

HRESULT sltDirMonitorThread::startup()
{
	m_bShutdown = FALSE;
	start();

	return S_OK;
}

int sltDirMonitorThread::run()
{
	BOOL bsucc = FALSE;

	g_LogSendThread.startup();	
	int nRetry = 0;
	
	for(;;)
	{
		if(m_bShutdown)
			break;

		//首次连接数据库
		//连接失败，继续连接

		if (!g_xmlFilterAgent.ConnectDB())
		{
			log.Print(LL_DEBUG_INFO, "[Warn]Try to Connect Db Failed!DBName=COMMONINFO\r\n");
			sleep(1000*30);
			continue;
		}

		log.Print(LL_DEBUG_INFO, "[Info]Connect Db succ!DBName=COMMONINFO\r\n");
		//连接成功，读取待监控的目录，并监视该目录
		if (g_xmlFilterAgent.LoadDB() != 0)
		{
			log.Print(LL_DEBUG_INFO, "[Warn]Try to LoadDB Failed!DBName=COMMONINFO\r\n");
			sleep(1000*10);
			if (nRetry++ > 5)
			{
				log.Print(LL_DEBUG_INFO, "[Error]Over Try Time LoadDB Failed!DBName=COMMONINFO\r\n");
				break;
			}

			continue;
		}

		//监控所有目录
		Monitor_Start_AllDisk(FALSE);

// 		int nDirCount = g_xmlFilterAgent.m_nCount;
// 		for (int i = 0; i < nDirCount; i++)
// 		{
// 			//获取监控目录开始监控
// 			Monitor_Start_Dir(g_xmlFilterAgent.m_pxmlfilter[i].szSearchPath, 0);
// 		}
		
		break;		
	}
	
	return 0;
}
