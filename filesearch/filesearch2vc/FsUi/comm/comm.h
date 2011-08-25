#if !defined(AFX_COMM__INCLUDED_)
#define AFX_COMM__INCLUDED_
#include <vector>
#include <string>
using namespace std;

typedef enum{
	lag_chinese = 0,
	lag_Japanese,
	lag_engish
}LANGUAGE;

enum File_Action{
	FILE_UNKNOW = 0,
	FILE_ADD,
	FILE_MODIFYED,
	FILE_REMOVED,
	FILE_NAMECHANGE
};

#define	DEFAULT_DB_NAME		"commoninfo"


#pragma pack(push, 1)


typedef struct _File_Action_Log
{
	File_Action FileActon;
	char szDbName[MAX_PATH];
	char szSrcName[MAX_PATH*2];
	char szDesName[MAX_PATH];
	char szLogTime[30];
	_File_Action_Log()
	{
		FileActon = FILE_UNKNOW;
		memset(szDbName, NULL, MAX_PATH);
		memset(szSrcName,NULL, MAX_PATH);
		memset(szDesName,NULL, MAX_PATH);
		memset(szLogTime, NULL, 30);
	}
	
}File_Action_Log,*pFile_Action_Log;

typedef struct _XmlFilter
{
	int  nIndex;
	char szSearceName[MAX_PATH];
	char szSearchPath[MAX_PATH];
	char szSearchType[MAX_PATH*2];
	char szExts[MAX_PATH*5];
}XmlFilter,*pXmlFilter;

typedef struct _DespInfo
{
	std::string strDesp;
	std::string strContent;
}DespInfo, *pDespInfo;

typedef struct _SearchRectord
{
	char szFileType[20];
	char szFileName[MAX_PATH];
	char szFilePath[MAX_PATH];
	std::vector<DespInfo> DespList;
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

