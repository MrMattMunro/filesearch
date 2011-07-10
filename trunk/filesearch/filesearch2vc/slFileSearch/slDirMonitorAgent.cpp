// slDirMonitorAgent.cpp: implementation of the slDirMonitorAgent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "slDirMonitorAgent.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

slDirMonitorAgent::slDirMonitorAgent()
{
	m_fnMonitor_Start_AllDisk = NULL;
	m_fnMonitor_Stop = NULL;
	m_fnMonitor_Start_Dir = NULL;
	m_hinstance = NULL;
	m_bInit = FALSE;
}

slDirMonitorAgent::~slDirMonitorAgent()
{
	FreeDll();
}

#define DIR_MONITOR_NAME "FileMonitor.dll"
BOOL slDirMonitorAgent::LoadDll()
{
	m_hinstance = LoadLibraryA(DIR_MONITOR_NAME);
	if (!m_hinstance)
	{
		log.Print(LL_DEBUG_INFO,"[Error]Not find FileMonitor.dll\r\n");
		return FALSE;
	}
	
	m_fnMonitor_Start_AllDisk = (fnMonitor_Start_AllDisk)GetProcAddress(m_hinstance, "Monitor_Start_AllDisk");
	m_fnMonitor_Stop = (fnMonitor_Stop)GetProcAddress(m_hinstance, "Monitor_Stop");
	m_fnMonitor_Start_Dir = (fnMonitor_Start_Dir)GetProcAddress(m_hinstance, "Monitor_Start_Dir");
	m_fnMonitor_Start = (fnMonitor_Start)GetProcAddress(m_hinstance, "Monitor_Start");
	m_fnMonitor_Reset = (fnMonitor_Reset)GetProcAddress(m_hinstance, "Monitor_Reset");
	if (!m_fnMonitor_Start_AllDisk || 
		!m_fnMonitor_Stop || 
		!m_fnMonitor_Start_Dir ||
		!m_fnMonitor_Start ||
		!m_fnMonitor_Reset)
	{
		log.Print(LL_DEBUG_INFO,"[Error]Not find FileMonitor.dll export fun!\r\n");
		return FALSE;
	}
	
	m_bInit = TRUE;
	
	return TRUE;
}

BOOL slDirMonitorAgent::FreeDll()
{
	if (!m_hinstance)
	{
		return TRUE;
	}
	
	FreeLibrary(m_hinstance);
	m_hinstance = NULL;
	
	return TRUE;
}

BOOL slDirMonitorAgent::StartMonitor()
{
	if (!m_bInit)
	{
		if (!LoadDll())
		{
			return FALSE;
		}
	}
	return m_fnMonitor_Start() == 0 ? TRUE : FALSE;
}

BOOL slDirMonitorAgent::StopMonitor()
{
	if (!m_bInit)
	{
		if (!LoadDll())
		{
			return FALSE;
		}
	}
	
	m_fnMonitor_Stop();

	return TRUE;
}


BOOL slDirMonitorAgent::ResetMonitor()
{
	if (!m_bInit)
	{
		if (!LoadDll())
		{
			return FALSE;
		}
	}
	
	return m_fnMonitor_Reset() == 0 ? TRUE : FALSE;

}