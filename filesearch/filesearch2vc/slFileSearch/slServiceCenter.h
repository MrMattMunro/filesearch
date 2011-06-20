// slServiceCenter.h: interface for the slServiceCenter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLSERVICECENTER_H__1C92D504_EDDB_44DB_A25C_4D5FA91D245D__INCLUDED_)
#define AFX_SLSERVICECENTER_H__1C92D504_EDDB_44DB_A25C_4D5FA91D245D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "sltIndexNotifyThread.h"

class slServiceCenter  
{
public:
	slServiceCenter();
	virtual ~slServiceCenter();
public:
	BOOL StopService();
	BOOL StartService();

private:
	slDirMonitorAgent _FileMonitor;
	sltIndexNotifyThread _IndexNotifyThread;

};

#endif // !defined(AFX_SLSERVICECENTER_H__1C92D504_EDDB_44DB_A25C_4D5FA91D245D__INCLUDED_)
