// sltLoadwndThread.cpp: implementation of the sltLoadwndThread class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FsUi.h"
#include "sltLoadwndThread.h"
#include "FloatWnd.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

sltLoadwndThread::sltLoadwndThread()
{
	m_bDlgExist = FALSE;
}

sltLoadwndThread::~sltLoadwndThread()
{
	join();
}

HRESULT sltLoadwndThread::startup(int nPos)
{
	do 
	{
		if (m_bDlgExist)
			break ;
		m_nPos = nPos;
		
		start();
	} while (0);
	
	return S_OK;
}

CFloatWnd  dlg;
void sltLoadwndThread::ShowWnd(BOOL bShow)
{
	if (m_bDlgExist)
	{
		if (bShow)
			dlg.ShowWindow(SW_SHOW);
		else
			dlg.ShowWindow(SW_HIDE);
	}

}

int sltLoadwndThread::run()
{	
	do 
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		m_bDlgExist = TRUE;
		if(IDOK ==  dlg.DoModal())
		{	
			break;
		}
	} while (0);
	
	m_bDlgExist = FALSE;
	
	return 0;
}

