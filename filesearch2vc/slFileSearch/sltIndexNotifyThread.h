// sltIndexNotifyThread.h: interface for the sltIndexNotifyThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLTINDEXNOTIFYTHREAD_H__C4E32148_BE50_4BBB_A0D3_866867F00992__INCLUDED_)
#define AFX_SLTINDEXNOTIFYTHREAD_H__C4E32148_BE50_4BBB_A0D3_866867F00992__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Thread.h"
#include "slDirMonitorAgent.h"

class sltIndexNotifyThread  : public Thread
{
public:
	sltIndexNotifyThread();
	virtual ~sltIndexNotifyThread();

	HRESULT startup();
	void shutdown();

protected:
	virtual int run();
	int CreateIndexEvent();

private:
	BOOL m_bShutdown;
	HANDLE m_hevent;	
	slDirMonitorAgent m_dirmon;
};

#endif // !defined(AFX_SLTINDEXNOTIFYTHREAD_H__C4E32148_BE50_4BBB_A0D3_866867F00992__INCLUDED_)
