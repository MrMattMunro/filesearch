// fsAddinDlgAgent.cpp: implementation of the fsAddinDlgAgent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "fsAddinDlgAgent.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

fsAddinDlgAgent::fsAddinDlgAgent()
{
	m_hinstance = NULL;
	m_bInit = FALSE;
	m_fnFsShowSavefileDlg = NULL;
}

fsAddinDlgAgent::~fsAddinDlgAgent()
{

}

#define DLL_NAME	"officeaddin.dll"
BOOL fsAddinDlgAgent::Init()
{
	if (m_bInit)
	{
		return TRUE;
	}

	m_hinstance = LoadLibraryA(DLL_NAME);
	if (!m_hinstance)
	{
		return FALSE;
	}

	m_fnFsShowSavefileDlg = (fnFsShowSavefileDlg)GetProcAddress(m_hinstance, "FsShowSavefileDlg");
	if (m_fnFsShowSavefileDlg == NULL)
	{
		return FALSE;
	}

	m_bInit = TRUE;

	return TRUE;
}

BOOL fsAddinDlgAgent::Uninit()
{
	if (m_bInit)
	{
		FreeLibrary(m_hinstance);
	}

	return TRUE;
}


BOOL fsAddinDlgAgent::FsShowSavefileDlg(char* szFilePath)
{
	if (!m_bInit)
	{
		if (!Init())
		{
			return FALSE;
		}
	}

	return m_fnFsShowSavefileDlg(szFilePath);
}