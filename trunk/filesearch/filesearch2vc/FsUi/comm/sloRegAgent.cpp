// sloRegAgent.cpp: implementation of the sloRegAgent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "FsUi.h"
#include "sloRegAgent.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

sloRegAgent::sloRegAgent()
{

}

sloRegAgent::~sloRegAgent()
{

}


//
BOOL sloRegAgent::ReadInstallPath(TCHAR *szInstallPath)
{
	struct HKEY__*RootKey;		//注册表主键名称
	TCHAR *Key;				//欲打开注册表项的地址
	TCHAR *newversionName = NULL;
	
	RootKey=HKEY_LOCAL_MACHINE;     //注册表主键名称
	Key="SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\slfile.exe";  //欲打开注册表值的地址
	
	int ret = 0;
	DWORD dwLen = 0;
	ret = ShowContent_S(RootKey, Key, newversionName, NULL,dwLen);

	ret = ShowContent_S(RootKey, Key, newversionName, (LPBYTE)szInstallPath,dwLen);
	
	return TRUE;
}


//////////////////////////////////////////////////////////////////////////
int sloRegAgent::SetValue_B (struct HKEY__*ReRootKey,TCHAR *ReSubKey,TCHAR *ReValueName,BYTE ReSetContent_B[1024])
{
	int iRet=0;	//操作结果：0==succeed
	HKEY hKey;

	if(RegOpenKeyEx(ReRootKey,ReSubKey,0,KEY_WRITE,&hKey)==ERROR_SUCCESS)
	{
		if(RegSetValueEx(hKey,ReValueName,NULL,REG_BINARY,(const unsigned char *)ReSetContent_B,168)!=ERROR_SUCCESS)
		{
			iRet = GetLastError();
		}
		RegCloseKey(hKey);
	}
	else
	{
		iRet = GetLastError();
	}
	return iRet;
}


int sloRegAgent::SetValue_D (struct HKEY__*ReRootKey,TCHAR *ReSubKey,TCHAR *ReValueName,DWORD ReSetContent_D)
{
	int iRet=0;	//操作结果：0==succeed
	HKEY hKey;
	if(RegOpenKeyEx(ReRootKey,ReSubKey,0,KEY_WRITE,&hKey)==ERROR_SUCCESS)
	{
		if(RegSetValueEx(hKey,ReValueName,NULL,REG_DWORD,(const unsigned char *)&ReSetContent_D,4)!=ERROR_SUCCESS)
		{
			iRet = GetLastError();			
		}
		RegCloseKey(hKey);
	}
	else
	{
			iRet = GetLastError();
	}
	return iRet;
}


//设置字符串值函数
int sloRegAgent::SetValue_S (struct HKEY__*ReRootKey,TCHAR *ReSubKey,TCHAR *ReValueName,LPBYTE ReSetContent_S)
{
	int iRet = 0;	//操作结果：0==succeed
	HKEY hKey;

	if(RegOpenKeyEx(ReRootKey,ReSubKey,0,KEY_WRITE,&hKey)==ERROR_SUCCESS)
	{
		if(RegSetValueEx(hKey,ReValueName,NULL,REG_SZ,ReSetContent_S,strlen((const char *)ReSetContent_S))!=ERROR_SUCCESS)
		{
			iRet = GetLastError();
		}
		RegCloseKey(hKey);
	}
	else
	{
		iRet = GetLastError();
	}

	return iRet;
}

//设置字符串值函数
int sloRegAgent::SetValue_ExpandS (struct HKEY__*ReRootKey,TCHAR *ReSubKey,TCHAR *ReValueName,LPBYTE ReSetContent_S)
{
	int iRet = 0;	//操作结果：0==succeed
	HKEY hKey;

	if(RegOpenKeyEx(ReRootKey,ReSubKey,0,KEY_WRITE,&hKey)==ERROR_SUCCESS)
	{
		if(RegSetValueEx(hKey,ReValueName,NULL,REG_EXPAND_SZ,ReSetContent_S,strlen((const char *)ReSetContent_S))!=ERROR_SUCCESS)
		{
			iRet = GetLastError();
		}
		RegCloseKey(hKey);
	}
	else
	{
		iRet = GetLastError();
	}

	return iRet;
}

//设置字符串值函数
int sloRegAgent::SetValue_MUTIS (struct HKEY__*ReRootKey,TCHAR *ReSubKey,TCHAR *ReValueName,LPBYTE ReSetContent_S,DWORD dwLen)
{
	int iRet = 0;	//操作结果：0==succeed
	HKEY hKey;

	if(RegOpenKeyEx(ReRootKey,ReSubKey,0,KEY_WRITE,&hKey)==ERROR_SUCCESS)
	{
		if(RegSetValueEx(hKey,ReValueName,NULL,REG_MULTI_SZ,ReSetContent_S,dwLen)!=ERROR_SUCCESS)
		{
			iRet = GetLastError();
		}
		RegCloseKey(hKey);
	}
	else
	{
		iRet = GetLastError();
	}

	return iRet;
}

//读取字符串值函数
int sloRegAgent::ShowContent_S(struct HKEY__*ReRootKey,TCHAR *ReSubKey,TCHAR *ReValueName,LPBYTE ReShowContent_S, DWORD &dwLen)
{
	int iRet = 0;	//操作结果：0==succeed
	HKEY hKey;
	DWORD dwType = 0;

	if(RegOpenKeyEx(ReRootKey,ReSubKey,0,KEY_READ,&hKey)==ERROR_SUCCESS)
	{
		if(RegQueryValueEx(hKey,ReValueName,NULL,&dwType,(unsigned char *)ReShowContent_S,&dwLen)!=ERROR_SUCCESS)
		{
			iRet = GetLastError();
		}
		RegCloseKey(hKey);
	}
	else
	{
		iRet = GetLastError();
	}
	
	return iRet;
}