// sloHotkeyAgent.cpp: implementation of the sloHotkeyAgent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FsUi.h"
#include "sloHotkeyAgent.h"
#include "sloRegAgent.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

sloHotkeyAgent::sloHotkeyAgent()
{
	memset(m_szpropertiesPath, NULL, MAX_PATH);
}

sloHotkeyAgent::~sloHotkeyAgent()
{

}

#define  HOTKEY_NAME "tomcat\\webapps\\slfile\\WEB-INF\\classes\\com\\web\\searchlocal\\properties\\hotkey.properties"
BOOL sloHotkeyAgent::GetProFilePath()
{
	if (strlen(m_szpropertiesPath) > 0)
	{
		return TRUE;
	}

	char szFileExePath[MAX_PATH] = {0};
	sloRegAgent reg;
	if(reg.ReadInstallPath(szFileExePath))
	{  
		char drive[_MAX_DRIVE];
		char dir[_MAX_DIR];
		char fname[_MAX_FNAME];
		char ext[_MAX_EXT];
		
		_splitpath( szFileExePath, drive, dir, fname, ext );
		sprintf(m_szpropertiesPath,"%s%s%s",drive, dir,HOTKEY_NAME);
		return TRUE;
	}
	
	return FALSE;
}

BOOL sloHotkeyAgent::SaveHotkey(char* pKeyName, WORD vk1, WORD sk1)
{
	//取出原有的vk1 和sk1 与当前设置的比较，是否有更新，如果有更新，则设置，并做事件通知
	WORD old_vk1 = 0, old_sk1 = 0;
	GetHotkey(pKeyName, old_vk1, old_sk1);

	//比较是否有更新
	if (old_vk1 == vk1 && old_sk1 == sk1)
	{
		//未变化，不做更新
		return TRUE;
	}

	//热键改变,保存
	BOOL bRet = SetHotkey(pKeyName, vk1, sk1);

	//通知热键监控进程更新热键变更

	

	return bRet;
}


BOOL sloHotkeyAgent::SetHotkey(char* pKeyName, WORD vk1, WORD sk1)
{
	if (!GetProFilePath())
	{
		return FALSE;
	}
	
	char szName1[MAX_PATH] = {0};
	char szName2[MAX_PATH] = {0};
	sprintf(szName1, "%s_vk1", pKeyName);
	sprintf(szName2, "%s_sk1", pKeyName);
	char szVK1[5] = {0};
	char szSK1[5] = {0};
	sprintf(szVK1, "%02d",vk1);
	sprintf(szSK1, "%02d",sk1);
	BOOL bSucc = sloCommAgent::WritePropertyfileString(szName1, szVK1, m_szpropertiesPath);
	bSucc = sloCommAgent::WritePropertyfileString(szName2, szSK1, m_szpropertiesPath);
	
	return bSucc;
}

BOOL sloHotkeyAgent::GetHotkey(char* pKeyName, WORD& vk1, WORD& sk1)
{
	if (!GetProFilePath())
	{
		return FALSE;
	}
	
	char szName1[MAX_PATH] = {0};
	char szName2[MAX_PATH] = {0};
	sprintf(szName1, "%s_vk1", pKeyName);
	sprintf(szName2, "%s_sk1", pKeyName);
	char szVK1[5] = {0};
	char szSK1[5] = {0};

	BOOL bSucc = sloCommAgent::GetPropertyfileString(szName1, "", szVK1, 5, m_szpropertiesPath);
	bSucc = sloCommAgent::GetPropertyfileString(szName2, "", szSK1, 5, m_szpropertiesPath);

	vk1 = atoi(szVK1);
	sk1 = atoi(szSK1);
	
	return bSucc;
}

