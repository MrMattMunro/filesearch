// sloSkinAgent.cpp: implementation of the sloSkinAgent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FsUi.h"
#include "sloSkinAgent.h"
#include "sloRegAgent.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

sloSkinAgent::sloSkinAgent()
{
	memset(&m_szSkinPath, NULL, MAX_PATH);	
	memset(&m_szSkinName, NULL, MAX_PATH);
	memset(&m_szSkinProPath, NULL, MAX_PATH);
}

sloSkinAgent::~sloSkinAgent()
{

}

#define  SKIN_PATH			"client\\Styles\\"
//#define  SKIN_NAME			"Office2007"
#define  SKIN_NAME_EXT		".cjstyles"

#define  SKIN_PRO_NAME "tomcat\\webapps\\slfile\\WEB-INF\\classes\\com\\web\\searchlocal\\properties\\skin.properties"

BOOL sloSkinAgent::GetSkinPath()
{
	char szFileExePath[MAX_PATH] = {0};
	sloRegAgent reg;
	if(!reg.ReadInstallPath(szFileExePath))
		return FALSE;
	
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];
	
	_splitpath( szFileExePath, drive, dir, fname, ext );
	sprintf(m_szSkinPath,"%s%s%s",drive, dir,SKIN_PATH);
//	sprintf(m_szSkinName,"%s%s%s",m_szSkinPath,SKIN_PATH, SKIN_NAME_EXT);

	sprintf(m_szSkinProPath,"%s%s%s",drive, dir,SKIN_PRO_NAME);	
	
	return TRUE;
}

#define SKINE_POR_KEY_NAME	"skintheme"
//Vista,WinXP.Luna,WinXP.Royale, Office2007
void sloSkinAgent::InitSkin()
{

	GetSkinPath();

	//从配置文件中读取skinname
	//如果没有就采用默认皮肤
	char szSkinName[MAX_PATH] = {0};
	sloCommAgent::GetPropertyfileString(SKINE_POR_KEY_NAME, THREME_NAME_VISTA, szSkinName, MAX_PATH, m_szSkinProPath );
	sprintf(m_szSkinName,"%s%s%s",m_szSkinPath,szSkinName, SKIN_NAME_EXT);

	//XTPSkinManager()->AddColorFilter(new CXTPSkinManagerColorFilterColorize(50, 100, 1));
	XTPSkinManager()->SetApplyOptions(XTPSkinManager()->GetApplyOptions() | xtpSkinApplyMetrics);
	XTPSkinManager()->LoadSkin(m_szSkinName, NULL/*_T("NormalBlue.ini")*/);
}


void sloSkinAgent::UpdateSkin(char* lpSkinName)
{
	memset(&m_szSkinName, NULL, MAX_PATH);
	sprintf(m_szSkinName,"%s%s%s",m_szSkinPath,lpSkinName, SKIN_NAME_EXT);
	XTPSkinManager()->LoadSkin(m_szSkinName);

	//写配置文件
	sloCommAgent::WritePropertyfileString(SKINE_POR_KEY_NAME, lpSkinName, m_szSkinProPath);
}
