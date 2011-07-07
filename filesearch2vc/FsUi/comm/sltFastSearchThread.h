// sltFastSearchThread.h: interface for the sltFastSearchThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLTFASTSEARCHTHREAD_H__0D74F75E_1663_42AA_B18E_BDBF22D3847D__INCLUDED_)
#define AFX_SLTFASTSEARCHTHREAD_H__0D74F75E_1663_42AA_B18E_BDBF22D3847D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Thread.h"
#include "sloFastSearchAgent.h"
#include "SearchThread.h"
class sltFastSearchThread   :public Singleton<sltFastSearchThread>, public Thread
{
public:
	sltFastSearchThread();
	virtual ~sltFastSearchThread();
	HRESULT startup();

	void PostMsg(FastItem postlog);

	BOOL DoLog(FastItem fast);

	HRESULT Init(HWND hParentWnd);
	void shutdownflag();
private:
	virtual int run();
	
private:
	BOOL m_bShutdown;
	tyoFifoQueue<FastItem> m_postQueue;
		
	sloFastSearchAgent m_agent;

	CSearchThread* m_pSearchThread;

	BOOL s_bInit;
};

#endif // !defined(AFX_SLTFASTSEARCHTHREAD_H__0D74F75E_1663_42AA_B18E_BDBF22D3847D__INCLUDED_)
