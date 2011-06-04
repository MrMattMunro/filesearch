// sltFastSearchDlgThread.cpp: implementation of the sltFastSearchDlgThread class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FsUi.h"
#include "sltFastSearchDlgThread.h"
#include "FastSearchDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

sltFastSearchDlgThread::sltFastSearchDlgThread()
{
	m_bDlgExist = FALSE;
}

sltFastSearchDlgThread::~sltFastSearchDlgThread()
{
	join();
}

HRESULT sltFastSearchDlgThread::startup()
{
	do 
	{
		if (m_bDlgExist)
			break ;
		
		start();
	} while (0);
	
	return S_OK;
}

int sltFastSearchDlgThread::run()
{	
	do 
	{
		m_bDlgExist = TRUE;
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		CFastSearchDlg  dlg;
		if(IDOK ==  dlg.DoModal())
		{	
			break;
		}
	} while (0);
	
	m_bDlgExist = FALSE;
	
	return 0;
}
