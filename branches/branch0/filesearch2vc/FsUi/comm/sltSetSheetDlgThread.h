// sltSetSheetDlgThread.h: interface for the sltSetSheetDlgThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLTSETSHEETDLGTHREAD_H__DF66F5E5_B20D_43C8_8B42_9D6B7C481DC4__INCLUDED_)
#define AFX_SLTSETSHEETDLGTHREAD_H__DF66F5E5_B20D_43C8_8B42_9D6B7C481DC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Thread.h"
class sltSetSheetDlgThread  :public Singleton<sltSetSheetDlgThread>, public Thread  
{
public:
	sltSetSheetDlgThread();
	virtual ~sltSetSheetDlgThread();
	
	HRESULT startup();
	
private:
	virtual int run();
	
private:
	BOOL m_bDlgExist;
};

#endif // !defined(AFX_SLTSETSHEETDLGTHREAD_H__DF66F5E5_B20D_43C8_8B42_9D6B7C481DC4__INCLUDED_)
