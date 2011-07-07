// slLogSendThread.h: interface for the slLogSendThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLLOGSENDTHREAD_H__10D34171_3494_4E93_9C70_EAFB071C90A9__INCLUDED_)
#define AFX_SLLOGSENDTHREAD_H__10D34171_3494_4E93_9C70_EAFB071C90A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Thread.h"
#include "slMySqlAgent.h"
class slLogSendThread   :public Thread
{
public:
	slLogSendThread();
	virtual ~slLogSendThread();

	HRESULT startup();
	void shutdown();

	void AddLog(File_Action_Log FileLog);
protected:
	BOOL DoWithLog(File_Action_Log FileLog);

private:
	virtual int run();
	BOOL m_bShutdown;
	tyoFifoQueue<File_Action_Log> m_postQueue;

	slMySqlAgent m_mysqlAgent;

	BOOL m_bInit;
};

#endif // !defined(AFX_SLLOGSENDTHREAD_H__10D34171_3494_4E93_9C70_EAFB071C90A9__INCLUDED_)
