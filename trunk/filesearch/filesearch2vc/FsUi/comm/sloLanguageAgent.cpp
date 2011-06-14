// sloLanguageAgent.cpp: implementation of the sloLanguageAgent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FsUi.h"
#include "sloLanguageAgent.h"
#include "sloRegAgent.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

sloLanguageAgent::sloLanguageAgent()
{
	memset(m_szpropertiesPath, NULL, MAX_PATH);
	memset(m_szPathHead, NULL, MAX_PATH);
	memset(m_szLagFilePath, NULL, MAX_PATH);
}

sloLanguageAgent::~sloLanguageAgent()
{

}


#define  LANGUAGE_PRO_NAME "tomcat\\webapps\\slfile\\WEB-INF\\classes\\com\\web\\searchlocal\\properties\\"
#define  LAG_FILE_NAME		"language.properties"
#define  LAG_FILE_NAME_CN	"ApplicationResources_cn_src.properties"
#define  LAG_FILE_NAME_JP	"ApplicationResources_jp_src.properties"
#define  LAG_FILE_NAME_EN	"ApplicationResources_en_src.properties"
BOOL sloLanguageAgent::GetProFilePath()
{
	char szFileExePath[MAX_PATH] = {0};
	
	sloRegAgent reg;
	if(reg.ReadInstallPath(szFileExePath))
	{  
		char drive[_MAX_DRIVE];
		char dir[_MAX_DIR];
		char fname[_MAX_FNAME];
		char ext[_MAX_EXT];
		
		_splitpath( szFileExePath, drive, dir, fname, ext );
		sprintf(m_szpropertiesPath,"%s%s%s%s",drive, dir,LANGUAGE_PRO_NAME, LAG_FILE_NAME);
		sprintf(m_szPathHead,"%s%s%s",drive, dir,LANGUAGE_PRO_NAME);
		sprintf(m_szLagFilePath,"%s%s",m_szPathHead,LAG_FILE_NAME_CN );
	}
	
	return FALSE;
}

#define CHINESE		"chinese"
#define JAPANESE	"japanese"
#define ENGISH		"english"
LANGUAGE sloLanguageAgent::GetLanguage()
{
	GetProFilePath();
	char szLanguage[MAX_PATH] = {0};
	sloCommAgent::GetPropertyfileString("language", "chinese", szLanguage, MAX_PATH, m_szpropertiesPath );
	LANGUAGE lag = lag_chinese;
	if (strcmp(szLanguage, JAPANESE) == 0)
	{
		lag = lag_Japanese;
		sprintf(m_szLagFilePath,"%s%s",m_szPathHead,LAG_FILE_NAME_JP );
	}else if(strcmp(szLanguage, ENGISH) == 0)
	{
		lag = lag_engish;
		sprintf(m_szLagFilePath,"%s%s",m_szPathHead,LAG_FILE_NAME_EN );
	}

	m_lag = lag;

	return lag;
}

CString sloLanguageAgent::LoadString(char* pID)
{
	char szText[MAX_PATH] = {0};
	sloCommAgent::GetPropertyfileString(pID, "null", szText, MAX_PATH, m_szLagFilePath);

	CString strText = szText;	
	return strText;
}