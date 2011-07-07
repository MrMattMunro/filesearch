// sltCreateIndexDlgThread.h: interface for the sltCreateIndexDlgThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLTCREATEINDEXDLGTHREAD_H__78011F93_6BB5_45C6_90AD_55A99220DC6E__INCLUDED_)
#define AFX_SLTCREATEINDEXDLGTHREAD_H__78011F93_6BB5_45C6_90AD_55A99220DC6E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Thread.h"
class sltCreateIndexDlgThread    :public Singleton<sltCreateIndexDlgThread>, public Thread
{
public:
	sltCreateIndexDlgThread();
	virtual ~sltCreateIndexDlgThread();

	HRESULT startup();
		
private:
	virtual int run();
	
private:
	BOOL m_bDlgExist;
};

#endif // !defined(AFX_SLTCREATEINDEXDLGTHREAD_H__78011F93_6BB5_45C6_90AD_55A99220DC6E__INCLUDED_)
