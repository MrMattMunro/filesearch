#if !defined(AFX_TYDIRMONITOR__INCLUDED_)
#define AFX_TYDIRMONITOR__INCLUDED_

DWORD __stdcall Monitor_Start_Dir(char* pszDirPath, DWORD dwLen);

DWORD __stdcall Monitor_Start_AllDisk(BOOL bRemovableDisk);

DWORD __stdcall Monitor_StopMonitor();

#endif