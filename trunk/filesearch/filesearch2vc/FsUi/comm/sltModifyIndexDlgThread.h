// sltModifyIndexDlgThread.h: interface for the sltModifyIndexDlgThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLTMODIFYINDEXDLGTHREAD_H__7421BF79_A608_4CD8_8599_5BE006E3FB63__INCLUDED_)
#define AFX_SLTMODIFYINDEXDLGTHREAD_H__7421BF79_A608_4CD8_8599_5BE006E3FB63__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Thread.h"
class sltModifyIndexDlgThread    :public Singleton<sltModifyIndexDlgThread>, public Thread 
{
public:
	sltModifyIndexDlgThread();
	virtual ~sltModifyIndexDlgThread();
	
	HRESULT startup(int nID);
	
private:
	virtual int run();
	
private:
	BOOL m_bDlgExist;
	int m_nID;
};

#endif // !defined(AFX_SLTMODIFYINDEXDLGTHREAD_H__7421BF79_A608_4CD8_8599_5BE006E3FB63__INCLUDED_)
