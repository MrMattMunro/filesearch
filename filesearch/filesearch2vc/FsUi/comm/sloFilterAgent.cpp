// sloFilterAgent.cpp: implementation of the sloFilterAgent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "DirMonitor.h"
#include "sloFilterAgent.h"
#include "sloCommAgent.h"
#include "sloRegAgent.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

sloFilterAgent::sloFilterAgent()
{
	m_bInit = FALSE;
	memset(m_szpropertiesPath, NULL, MAX_PATH);	
	memset(m_szExcludes, NULL, 4096);	
}

sloFilterAgent::~sloFilterAgent()
{

}


void sloFilterAgent::Init()
{
	if (m_bInit)
		return ;

	//获取配置文件路径
	if(!GetProFilePath())
		return ;

	//读取配置文件内容
	GetExtsFromFile("exts_word", "word");
	GetExtsFromFile("exts_excel", "excel");
	GetExtsFromFile("exts_ppt", "ppt");
	GetExtsFromFile("exts_pdf", "pdf");
	GetExtsFromFile("exts_txt", "txt");
	GetExtsFromFile("exts_html", "html");

	//获取exclude内容
	GetExcludesFromFile("exclude");

	m_bInit = TRUE;
}

void sloFilterAgent::GetExtsFromFile(char* szKeyName, char* szType)
{
	char szText[MAX_PATH*5] = {0};
	sloCommAgent::GetPropertyfileString(szKeyName, "", szText, MAX_PATH, m_szpropertiesPath);

	Ext_Filters item;
	item.strType = szType;
	item.strExts = szText;
	m_exts.push_back(item);
}

void sloFilterAgent::GetExcludesFromFile(char* szKeyName)
{
	memset(m_szExcludes, NULL, 4096);
	sloCommAgent::GetPropertyfileString(szKeyName, "", m_szExcludes, 4096, m_szpropertiesPath);
}


#define  PRO_NAME	"tomcat\\webapps\\slfile\\WEB-INF\\classes\\com\\web\\searchlocal\\properties\\DirMonFilter.properties"
BOOL sloFilterAgent::GetProFilePath()
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
		sprintf(m_szpropertiesPath,"%s%s%s",drive, dir,PRO_NAME);
		return TRUE;
	}
	
	return FALSE;
}

std::string sloFilterAgent::GetExtsFromTypes(char* szTypes)
{
	std::string strExts;
	std::string strTypes = szTypes;
	int nSize = m_exts.size();
	for (int i=0; i< nSize; i++)
	{
		if (strTypes.find(m_exts[i].strType) != -1)
		{
			strExts += m_exts[i].strExts;
		}
	}

	return strExts;
}

std::string sloFilterAgent::GetAllExts()
{
	std::string strExts;
	for (int i=0; i< m_exts.size(); i++)
	{
		strExts += m_exts[i].strExts;
	}
	
	return strExts;
}

std::string sloFilterAgent::GetFileTypeFromExt(char* szExt)
{
	std::string strType;
	int nSize = m_exts.size();
	for (int i=0; i< nSize; i++)
	{
		std::string strExts = m_exts[i].strExts;
		if (strExts.find(szExt) != -1)
		{
			strType = m_exts[i].strType;
			break ;
		}
	}

	return strType;
}