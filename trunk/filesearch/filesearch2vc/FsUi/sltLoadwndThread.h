// sltLoadwndThread.h: interface for the sltLoadwndThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLTLOADWNDTHREAD_H__185BDDCE_EBA2_4351_B67D_FC888356E4A3__INCLUDED_)
#define AFX_SLTLOADWNDTHREAD_H__185BDDCE_EBA2_4351_B67D_FC888356E4A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Thread.h"
class sltLoadwndThread   :public Singleton<sltLoadwndThread>, public Thread
{
public:
	sltLoadwndThread();
	virtual ~sltLoadwndThread();
	
	HRESULT startup(int nPos);
	void ShowWnd(BOOL bShow);
private:
	virtual int run();
	
private:
	BOOL m_bDlgExist;
	int m_nPos;
};

#endif // !defined(AFX_SLTLOADWNDTHREAD_H__185BDDCE_EBA2_4351_B67D_FC888356E4A3__INCLUDED_)
