#if !defined(AFX_COMM__INCLUDED_)
#define AFX_COMM__INCLUDED_

typedef enum{
	lag_chinese = 0,
	lag_Japanese,
	lag_engish
}LANGUAGE;

#pragma pack(push, 1)

typedef struct _SearchRectord
{
	char szFileType[20];
	char szFileName[MAX_PATH];
	char szFilePath[MAX_PATH];
	char szContent[1000];
	std::vector<std::string> DespList;
//	char szDesp[1000];
}SearchRectord, *pSearchRectord;

typedef struct _PathIndex
{
	int nID;
	char szPath[MAX_PATH];
}PathIndex,*pPathIndex;

typedef struct _LicenseInfo 
{
	char szOrderNo[20];
	char szEmail[200];
	char szStartDate[32];
	char szEndDate[32];
}LicenseInfo,*LPLicenseInfo;

typedef struct _FastItem
{
	char szKey[MAX_PATH];
	char szID[MAX_PATH];
	char szType[MAX_PATH];	
}FastItem,*LPFastItem;

typedef struct _License_Back_Head 
{
	char szGUID[36];
	LicenseInfo licinfo;
}License_Back_Head,*LPLicense_Back_Head;


typedef struct _Ext_Filters
{
	std::string strType;
	std::string strExts;
}Ext_Filters, *LPExt_Filters;


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

