// sltModifyIndexDlgThread.cpp: implementation of the sltModifyIndexDlgThread class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FsUi.h"
#include "sltModifyIndexDlgThread.h"
#include "ModifyIndexDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

sltModifyIndexDlgThread::sltModifyIndexDlgThread()
{
	m_bDlgExist = FALSE;
	m_nID = 0;
}

sltModifyIndexDlgThread::~sltModifyIndexDlgThread()
{
	join();
}

HRESULT sltModifyIndexDlgThread::startup(int nID)
{
	do 
	{
		if (m_bDlgExist)
			break ;

		m_nID = nID;
		start();
	} while (0);
	
	return S_OK;
}

int sltModifyIndexDlgThread::run()
{	
	do 
	{
		m_bDlgExist = TRUE;
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		CModifyIndexDlg dlg;
		dlg.SetIndexID(m_nID);
		if(IDOK == dlg.DoModal())
		{	
			break;
		}
	} while (0);
	
	m_bDlgExist = FALSE;
	
	return 0;
}
