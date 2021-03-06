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
		sprintf(m_szLagFilePath,"%s%s",m_szPathHead,LAG_FILE_NAME_EN );
	}
	
	return FALSE;
}

#define CHINESE		"chinese"
#define JAPANESE	"japanese"
#define ENGISH		"english"
LANGUAGE sloLanguageAgent::GetLanguage()
{
	GetProFilePath();
	LANGUAGE lag = lag_engish;
	char szLanguage[MAX_PATH] = {0};
	
	LANGID lcid =GetUserDefaultLCID();

	if(lcid == 0x409 || lcid == 0x809)
	{   
		//美国英语
		OutputDebugString("英语");
	}
	
	if(lcid == 0x0411)
	{   
		//日文
		lag = lag_Japanese;
		memset(m_szLagFilePath, NULL, MAX_PATH);
		sprintf(m_szLagFilePath,"%s%s",m_szPathHead,LAG_FILE_NAME_JP );	
	}
	
	if(lcid == 0x804)
	{   
		//中国简体
		lag = lag_chinese;
		memset(m_szLagFilePath, NULL, MAX_PATH);
		sprintf(m_szLagFilePath,"%s%s",m_szPathHead,LAG_FILE_NAME_CN );		 
	}   

	/*
	BOOL bRet = sloCommAgent::GetPropertyfileString("language", "chinese", szLanguage, MAX_PATH, m_szpropertiesPath );
	if (bRet)
	{
		if (strcmp(szLanguage, JAPANESE) == 0)
		{
			lag = lag_Japanese;
			memset(m_szLagFilePath, NULL, MAX_PATH);
			sprintf(m_szLagFilePath,"%s%s",m_szPathHead,LAG_FILE_NAME_JP );
		}else if(strcmp(szLanguage, ENGISH) == 0)
		{
			lag = lag_engish;
			memset(m_szLagFilePath, NULL, MAX_PATH);
			sprintf(m_szLagFilePath,"%s%s",m_szPathHead,LAG_FILE_NAME_EN );
		}
	}else
	{
		//文件被占用，采用此方式打开
		FILE *fp = fopen(m_szpropertiesPath,"r+");
		fseek(fp, 0 ,SEEK_END);
		int nLen = ftell(fp);
		fseek(fp, 0 ,SEEK_SET);

		char *pData = new char[nLen + 1];
		memset(pData, NULL, nLen+1);

		int nRead = fread(pData, sizeof(char), nLen, fp);
		std::string strData = pData;
		if(strData.find(JAPANESE) != -1)
		{
			lag = lag_Japanese;
			memset(m_szLagFilePath, NULL, MAX_PATH);
			sprintf(m_szLagFilePath,"%s%s",m_szPathHead,LAG_FILE_NAME_JP );
		}else if (strData.find(ENGISH) != -1)
		{
			lag = lag_engish;
			memset(m_szLagFilePath, NULL, MAX_PATH);
			sprintf(m_szLagFilePath,"%s%s",m_szPathHead,LAG_FILE_NAME_EN );		
		}

		fclose(fp);
	}
*/
	m_lag = lag;

	return lag;
}

CString sloLanguageAgent::LoadString(char* pID)
{
	char szText[MAX_PATH] = {0};
	sloCommAgent::GetPropertyfileString(pID, "", szText, MAX_PATH, m_szLagFilePath);
	
	CString strText = szText;	
	return strText;
}