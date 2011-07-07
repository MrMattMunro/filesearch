// sltDirMonitorThread.h: interface for the sltDirMonitorThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLTDIRMONITORTHREAD_H__AE51550F_1CE2_4514_BB28_F1796FCD8DAB__INCLUDED_)
#define AFX_SLTDIRMONITORTHREAD_H__AE51550F_1CE2_4514_BB28_F1796FCD8DAB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Thread.h"
class sltDirMonitorThread  : public Thread
{
public:
	sltDirMonitorThread();
	virtual ~sltDirMonitorThread();

	HRESULT startup();
	void shutdown();
	
private:
	virtual int run();
	BOOL m_bShutdown;
	
	BOOL m_bInit;
};

#endif // !defined(AFX_SLTDIRMONITORTHREAD_H__AE51550F_1CE2_4514_BB28_F1796FCD8DAB__INCLUDED_)
