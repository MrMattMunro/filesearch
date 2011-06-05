// sloCustomCiHuiAgent.cpp: implementation of the sloCustomCiHuiAgent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FsUi.h"
#include "sloCustomCiHuiAgent.h"
#include "sloRegAgent.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

sloCustomCiHuiAgent::sloCustomCiHuiAgent()
{
	memset(m_szpropertiesPath, NULL, MAX_PATH);
	memset(m_szcustomtxtPath, NULL, MAX_PATH);
}

sloCustomCiHuiAgent::~sloCustomCiHuiAgent()
{

}

#define DICFILE_NAME	"dicfile"
#define OVERFLAG_NAME	"isoverwrite"

BOOL sloCustomCiHuiAgent::EventCustomCiHui(BOOL bOver, char* pszFilePath)
{
	BOOL bSucc = FALSE;
	CString strOver = "false";
	if (bOver)
	{
		strOver = "true";
	}

	GetProFilePath();
	
	bSucc = sloCommAgent::WritePropertyfileString(DICFILE_NAME, pszFilePath, m_szpropertiesPath);
	
	bSucc = sloCommAgent::WritePropertyfileString(OVERFLAG_NAME, strOver.GetBuffer(0), m_szpropertiesPath);

	return bSucc;
}

#define  CUS_PRO_NAME "tomcat\\webapps\\slfile\\WEB-INF\\classes\\com\\web\\searchlocal\\properties\\custumdic.properties"
#define  CUS_TXT_NAME "dic\\custom.dic"
BOOL sloCustomCiHuiAgent::GetProFilePath()
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
		sprintf(m_szpropertiesPath,"%s%s%s",drive, dir,CUS_PRO_NAME);
		sprintf(m_szcustomtxtPath,"%s%s%s",drive, dir,CUS_TXT_NAME);
		return TRUE;
	}
	
	return FALSE;
}
