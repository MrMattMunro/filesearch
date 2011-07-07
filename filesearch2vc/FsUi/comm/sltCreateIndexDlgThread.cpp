// sltCreateIndexDlgThread.cpp: implementation of the sltCreateIndexDlgThread class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FsUi.h"
#include "sltCreateIndexDlgThread.h"
#include "CreateIndexDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

sltCreateIndexDlgThread::sltCreateIndexDlgThread()
{
	m_bDlgExist = FALSE;
}

sltCreateIndexDlgThread::~sltCreateIndexDlgThread()
{
	join();
}

HRESULT sltCreateIndexDlgThread::startup()
{
	do 
	{
		if (m_bDlgExist)
			break ;
		
		start();
	} while (0);
	
	return S_OK;
}

int sltCreateIndexDlgThread::run()
{	
	do 
	{
		m_bDlgExist = TRUE;
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		CCreateIndexDlg createindexdlg;
		if(IDOK == createindexdlg.DoModal())
		{	
			break;
		}
	} while (0);
	
	m_bDlgExist = FALSE;

	return 0;
}