// sloOpenFileAgent.cpp: implementation of the sloOpenFileAgent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FsUi.h"
#include "sloOpenFileAgent.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

sloOpenFileAgent::sloOpenFileAgent()
{
	m_bInit = FALSE;
	m_hinstance = NULL;
}

sloOpenFileAgent::~sloOpenFileAgent()
{

}

#define DLL_NAME	"OpenFileAddin.dll"
BOOL sloOpenFileAgent::Init()
{
	m_hinstance = LoadLibrary(DLL_NAME);
	if (!m_hinstance)
	{
		return FALSE;
	}

	m_fnopenWordFile = (fnopenWordFile)GetProcAddress(m_hinstance, "openWordFile");
	m_fnopenExcelFile = (fnopenExcelFile)GetProcAddress(m_hinstance, "openExcelFile");
	m_fnopenPPTFile = (fnopenPPTFile)GetProcAddress(m_hinstance, "openPPTFile");
	m_fnopenPdfFile = (fnopenPdfFile)GetProcAddress(m_hinstance, "openPdfFile");
	m_fnopenTxtFile = (fnopenTxtFile)GetProcAddress(m_hinstance, "openTxtFile");
	if (m_fnopenWordFile == NULL || m_fnopenExcelFile == NULL ||
		m_fnopenPPTFile == NULL || m_fnopenPdfFile == NULL ||
		m_fnopenTxtFile == NULL)
	{
		return FALSE;
	}

	m_bInit = TRUE;
	
	return TRUE;
}
