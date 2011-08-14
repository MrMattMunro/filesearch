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
	memset(&m_szSkinName, NULL, MAX_PATH*2);
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

	sprintf(m_szSkinProPath,"%s%s%s",drive, dir,SKIN_PRO_NAME);	
	
	return TRUE;
}

#define THREME_NAME_NORMAL					"<默认皮肤>"
#define THREME_NAME_STYLES_2007				"Office2007.cjstyles"
#define THREME_NAME_STYLES_VISTA			"Vista.cjstyles"
#define THREME_NAME_STYLES_XP_ROYALE		"WinXP.Royale.cjstyles"
#define THREME_NAME_STYLES_XP_LUNA			"WinXP.Luna.cjstyles"

#define THREME_NAME_2007_Blue_INI				"NormalBlue.ini"
#define THREME_NAME_2007_LightBlue_INI			"LightBlue.ini"
#define THREME_NAME_2007_Aqua_INI				"NormalAqua.ini"
#define THREME_NAME_2007_Sliver_INI				"NormalSilver.ini"
#define THREME_NAME_2007_Black_INI				"NormalBlack.ini"

#define THREME_NAME_VISTA_Black_INI				"NormalBlack.ini"
#define THREME_NAME_VISTA_Black2_INI			"NormalBlack2.ini"
#define THREME_NAME_VISTA_Blue_INI				"NormalBlue.ini"
#define THREME_NAME_VISTA_Sliver_INI			"NormalSilver.ini"

#define THREME_NAME_XP_ROYALE_INI				"NormalRoyale.ini"

#define THREME_NAME_XP_LUNA_Blue_INI			"NormalBlue.ini"
#define THREME_NAME_XP_LUNA_HomeStead_INI		"NormalHomestead.ini"
#define THREME_NAME_XP_LUNA_Metallic_INI		"NormalMetallic.ini"

BOOL sloSkinAgent::InitSkinProp()
{
	Skin_Prop skinprop;

	//office2007
	strcpy(skinprop.szSkinStyleName, THREME_NAME_STYLES_2007);
	strcpy(skinprop.szSkinShowName, THREME_NAME_2007_Blue);
	strcpy(skinprop.szSkinIniName, THREME_NAME_2007_Blue_INI);
	m_skinPropList.push_back(skinprop);

	memset(&skinprop, NULL, sizeof(Skin_Prop));
	strcpy(skinprop.szSkinStyleName, THREME_NAME_STYLES_2007);
	strcpy(skinprop.szSkinShowName, THREME_NAME_2007_LightBlue);
	strcpy(skinprop.szSkinIniName, THREME_NAME_2007_LightBlue_INI);
	m_skinPropList.push_back(skinprop);

	memset(&skinprop, NULL, sizeof(Skin_Prop));
	strcpy(skinprop.szSkinStyleName, THREME_NAME_STYLES_2007);
	strcpy(skinprop.szSkinShowName, THREME_NAME_2007_Aqua);
	strcpy(skinprop.szSkinIniName, THREME_NAME_2007_Aqua_INI);
	m_skinPropList.push_back(skinprop);


	memset(&skinprop, NULL, sizeof(Skin_Prop));
	strcpy(skinprop.szSkinStyleName, THREME_NAME_STYLES_2007);
	strcpy(skinprop.szSkinShowName, THREME_NAME_2007_Sliver);
	strcpy(skinprop.szSkinIniName, THREME_NAME_2007_Sliver_INI);
	m_skinPropList.push_back(skinprop);

	memset(&skinprop, NULL, sizeof(Skin_Prop));
	strcpy(skinprop.szSkinStyleName, THREME_NAME_STYLES_2007);
	strcpy(skinprop.szSkinShowName, THREME_NAME_2007_Black);
	strcpy(skinprop.szSkinIniName, THREME_NAME_2007_Black_INI);
	m_skinPropList.push_back(skinprop);

	//vista
	memset(&skinprop, NULL, sizeof(Skin_Prop));
	strcpy(skinprop.szSkinStyleName, THREME_NAME_STYLES_VISTA);
	strcpy(skinprop.szSkinShowName, THREME_NAME_VISTA_Black);
	strcpy(skinprop.szSkinIniName, THREME_NAME_VISTA_Black_INI);
	m_skinPropList.push_back(skinprop);

	memset(&skinprop, NULL, sizeof(Skin_Prop));
	strcpy(skinprop.szSkinStyleName, THREME_NAME_STYLES_VISTA);
	strcpy(skinprop.szSkinShowName, THREME_NAME_VISTA_Black2);
	strcpy(skinprop.szSkinIniName, THREME_NAME_VISTA_Black2_INI);
	m_skinPropList.push_back(skinprop);

	memset(&skinprop, NULL, sizeof(Skin_Prop));
	strcpy(skinprop.szSkinStyleName, THREME_NAME_STYLES_VISTA);
	strcpy(skinprop.szSkinShowName, THREME_NAME_VISTA_Blue);
	strcpy(skinprop.szSkinIniName, THREME_NAME_VISTA_Blue_INI);
	m_skinPropList.push_back(skinprop);

	memset(&skinprop, NULL, sizeof(Skin_Prop));
	strcpy(skinprop.szSkinStyleName, THREME_NAME_STYLES_VISTA);
	strcpy(skinprop.szSkinShowName, THREME_NAME_VISTA_Sliver);
	strcpy(skinprop.szSkinIniName, THREME_NAME_VISTA_Sliver_INI);
	m_skinPropList.push_back(skinprop);

	//XP_ROYALE
	memset(&skinprop, NULL, sizeof(Skin_Prop));
	strcpy(skinprop.szSkinStyleName, THREME_NAME_STYLES_XP_ROYALE);
	strcpy(skinprop.szSkinShowName, THREME_NAME_XP_ROYALE);
	strcpy(skinprop.szSkinIniName, THREME_NAME_XP_ROYALE_INI);
	m_skinPropList.push_back(skinprop);

	//XP_LUNA
	memset(&skinprop, NULL, sizeof(Skin_Prop));
	strcpy(skinprop.szSkinStyleName, THREME_NAME_STYLES_XP_LUNA);
	strcpy(skinprop.szSkinShowName, THREME_NAME_XP_LUNA_Blue);
	strcpy(skinprop.szSkinIniName, THREME_NAME_XP_LUNA_Blue_INI);
	m_skinPropList.push_back(skinprop);

	memset(&skinprop, NULL, sizeof(Skin_Prop));
	strcpy(skinprop.szSkinStyleName, THREME_NAME_STYLES_XP_LUNA);
	strcpy(skinprop.szSkinShowName, THREME_NAME_XP_LUNA_HomeStead);
	strcpy(skinprop.szSkinIniName, THREME_NAME_XP_LUNA_HomeStead_INI);
	m_skinPropList.push_back(skinprop);

	memset(&skinprop, NULL, sizeof(Skin_Prop));
	strcpy(skinprop.szSkinStyleName, THREME_NAME_STYLES_XP_LUNA);
	strcpy(skinprop.szSkinShowName, THREME_NAME_XP_LUNA_Metallic);
	strcpy(skinprop.szSkinIniName, THREME_NAME_XP_LUNA_Metallic_INI);
	m_skinPropList.push_back(skinprop);

	return TRUE;
}


#define SKINE_POR_KEY_NAME	"skintheme"
//Vista,WinXP.Luna,WinXP.Royale, Office2007
void sloSkinAgent::InitSkin()
{
	InitSkinProp();

	GetSkinPath();

	//从配置文件中读取skinname
	//如果没有就采用默认皮肤
	char szSkinName[MAX_PATH] = {0};
	sloCommAgent::GetPropertyfileString(SKINE_POR_KEY_NAME, THREME_NAME_2007_LightBlue, szSkinName, MAX_PATH, m_szSkinProPath );
	int nSize = m_skinPropList.size();
	for (int i = 0; i < nSize; i++)
	{
		if( strcmp(m_skinPropList[i].szSkinShowName, szSkinName) == 0)
		{
			break;
		}
	}

	sprintf(m_szSkinName,"%s%s",m_szSkinPath, m_skinPropList[i].szSkinStyleName);

	XTPSkinManager()->SetApplyOptions(XTPSkinManager()->GetApplyOptions() | xtpSkinApplyMetrics);

	XTPSkinManager()->LoadSkin(m_szSkinName, m_skinPropList[i].szSkinIniName);

}


void sloSkinAgent::UpdateSkin(char* lpSkinName)
{
	int nSize = m_skinPropList.size();
	for (int i = 0; i < nSize; i++)
	{
		if( strcmp(m_skinPropList[i].szSkinShowName, lpSkinName) == 0 )
		{
			break;
		}
	}
	
	memset(&m_szSkinName, NULL, MAX_PATH*2);
	sprintf(m_szSkinName,"%s%s",m_szSkinPath, m_skinPropList[i].szSkinStyleName);

	XTPSkinManager()->LoadSkin(m_szSkinName, m_skinPropList[i].szSkinIniName);
	
	//写配置文件
	sloCommAgent::WritePropertyfileString(SKINE_POR_KEY_NAME, lpSkinName, m_szSkinProPath);
}
