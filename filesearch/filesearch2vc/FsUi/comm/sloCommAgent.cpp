// sloCommAgent.cpp: implementation of the sloCommAgent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FsUi.h"
#include "sloCommAgent.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

sloCommAgent::sloCommAgent()
{

}

sloCommAgent::~sloCommAgent()
{

}

char* sloCommAgent::GetCurTime()
{
	char *pszTime = new char[30];
	memset(pszTime, NULL, 30);
	SYSTEMTIME stTime;
	GetLocalTime(&stTime);
	sprintf(pszTime,"%04d-%02d-%02d %02d:%02d:%02d",
		stTime.wYear, stTime.wMonth, stTime.wDay, stTime.wHour, stTime.wMinute, stTime.wSecond);
	return pszTime;
}

