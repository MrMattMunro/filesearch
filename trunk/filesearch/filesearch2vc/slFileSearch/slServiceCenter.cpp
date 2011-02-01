// slServiceCenter.cpp: implementation of the slServiceCenter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "slServiceCenter.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

slServiceCenter::slServiceCenter()
{

}

slServiceCenter::~slServiceCenter()
{

}

BOOL slServiceCenter::StartService()
{

	_FileMonitor.StartMonitor();
	_IndexNotifyThread.startup();
	
	return TRUE;
}

BOOL slServiceCenter::StopService()
{
	_FileMonitor.StopMonitor();

	_IndexNotifyThread.shutdown();
	
	return TRUE;
}
