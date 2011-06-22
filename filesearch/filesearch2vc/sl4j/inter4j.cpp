#pragma once
#include "StdAfx.h"
#include <TLHELP32.H>

void slTerminateProcess(char* pProcessName);

DWORD __stdcall MsgBox(char* pText, char* pCaption, unsigned int uType)
{
	return MessageBox(NULL, pText, pCaption, uType);
}

DWORD __stdcall DoExe(char* szPath)
{

	//查找java，cmd进程，并结束掉
	slTerminateProcess("java.exe");
	slTerminateProcess("update.exe");

	//然后在执行相应的进程
	ShellExecute(NULL, "open",szPath, NULL,NULL, SW_SHOWNORMAL); 

	return 0;
}

void slTerminateProcess(char* pProcessName)
{
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(pe32);//为让系统知道使用的结构是哪个，故要求大小
	HANDLE hexit;
	//HANDLE htask;
	BOOL btest;
	HANDLE hsnapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);//遍历系统进程
	BOOL bMore = ::Process32First(hsnapshot,&pe32);
	while(bMore)
	{
		if(strcmp(pe32.szExeFile, pProcessName)==0)
		{
			hexit = ::OpenProcess(PROCESS_ALL_ACCESS,FALSE,pe32.th32ProcessID);
			btest = ::TerminateProcess(hexit,0);//结束进程
			if(!btest)
			{
				continue;
			}
		}
		bMore = ::Process32Next(hsnapshot,&pe32);
	}
}
