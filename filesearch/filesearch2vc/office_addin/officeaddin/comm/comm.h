#if !defined(AFX_COMM__INCLUDED_)
#define AFX_COMM__INCLUDED_

#define THREME_NAME_NORMAL					"<Ä¬ÈÏÆ¤·ô>"
#define THREME_NAME_2007_Blue				"Office2007_Blue"
#define THREME_NAME_2007_LightBlue			"Office2007_LightBlue"
#define THREME_NAME_2007_Aqua				"Office2007_Aqua"
#define THREME_NAME_2007_Sliver				"Office2007_Sliver"
#define THREME_NAME_2007_Black				"Office2007_Black"

#define THREME_NAME_VISTA_Black				"Vista_Black"
#define THREME_NAME_VISTA_Black2			"Vista_Black2"
#define THREME_NAME_VISTA_Blue				"Vista_Blue"
#define THREME_NAME_VISTA_Sliver			"Vista_Sliver"

#define THREME_NAME_XP_ROYALE				"WinXP.Royale"

#define THREME_NAME_XP_LUNA_Blue			"WinXP.Luna_Blue"
#define THREME_NAME_XP_LUNA_HomeStead		"WinXP.Luna_HomeStead"
#define THREME_NAME_XP_LUNA_Metallic		"WinXP.Luna_Metallic"

#pragma pack(push, 1)

typedef struct _DocumentItem{
	char szuuid[36];
	char szlocation[1024];
	char szname[MAX_PATH];
	char sztype[1024];
	char szauthor[MAX_PATH];
	char szowner[MAX_PATH];
	char szcreatedate[MAX_PATH];
	char szmodifieddate[MAX_PATH];
	char szaccesseddate[MAX_PATH];
	char syncflg;
	char protectflg;
	char operflg;
	int	 nreadcout;
}DocumentItem, _DocumentItem;

typedef struct _Skin_Prop
{
	char szSkinShowName[MAX_PATH];
	char szSkinStyleName[MAX_PATH];
	char szSkinIniName[MAX_PATH];
	_Skin_Prop()
	{
		memset(szSkinShowName, NULL, MAX_PATH);
		memset(szSkinStyleName, NULL, MAX_PATH);
		memset(szSkinIniName, NULL, MAX_PATH);
	}
}Skin_Prop, *LPSkin_Prop;

#pragma pack(pop)

#endif

