// slDirMonitorAgent.h: interface for the slDirMonitorAgent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLDIRMONITORAGENT_H__7CB9EC23_3D22_4F95_94A3_241A3128280B__INCLUDED_)
#define AFX_SLDIRMONITORAGENT_H__7CB9EC23_3D22_4F95_94A3_241A3128280B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef DWORD (__stdcall *fnMonitor_Start_Dir)(char* pszDirPath, DWORD dwLen);
typedef DWORD (__stdcall *fnMonitor_Start_AllDisk)(BOOL bRemovableDisk);
typedef DWORD (__stdcall *fnMonitor_Stop)();
typedef DWORD (__stdcall *fnMonitor_Start)();
typedef DWORD (__stdcall *fnMonitor_Reset)();
class slDirMonitorAgent  
{
public:
	slDirMonitorAgent();
	virtual ~slDirMonitorAgent();
	
	BOOL StartMonitor();
	BOOL StopMonitor();
	BOOL ResetMonitor();
protected:
	BOOL LoadDll();
	BOOL FreeDll();
	
private:
	fnMonitor_Start_AllDisk m_fnMonitor_Start_AllDisk;
	fnMonitor_Stop m_fnMonitor_Stop;
	fnMonitor_Start_Dir m_fnMonitor_Start_Dir;
	fnMonitor_Start m_fnMonitor_Start;
	fnMonitor_Reset m_fnMonitor_Reset;
	HINSTANCE m_hinstance;
	BOOL m_bInit;
};

#endif // !defined(AFX_SLDIRMONITORAGENT_H__7CB9EC23_3D22_4F95_94A3_241A3128280B__INCLUDED_)
