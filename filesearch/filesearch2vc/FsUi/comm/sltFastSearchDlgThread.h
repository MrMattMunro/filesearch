// sltFastSearchDlgThread.h: interface for the sltFastSearchDlgThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLTFASTSEARCHDLGTHREAD_H__B36E5228_E548_4D3F_9B8F_A3874609299E__INCLUDED_)
#define AFX_SLTFASTSEARCHDLGTHREAD_H__B36E5228_E548_4D3F_9B8F_A3874609299E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Thread.h"
class sltFastSearchDlgThread   :public Singleton<sltFastSearchDlgThread>, public Thread
{
public:
	sltFastSearchDlgThread();
	virtual ~sltFastSearchDlgThread();
	
	HRESULT startup(int nPos);
	
private:
	virtual int run();
	
private:
	BOOL m_bDlgExist;
	int m_nPos;
};

#endif // !defined(AFX_SLTFASTSEARCHDLGTHREAD_H__B36E5228_E548_4D3F_9B8F_A3874609299E__INCLUDED_)
