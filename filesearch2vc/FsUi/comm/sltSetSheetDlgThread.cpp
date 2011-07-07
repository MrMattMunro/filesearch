// sltSetSheetDlgThread.cpp: implementation of the sltSetSheetDlgThread class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FsUi.h"
#include "sltSetSheetDlgThread.h"
#include "CustomCiHuiDlg.h"
#include "SetAttributeDlg.h"
#include "LicenseDlg.h"
#include "SkinDlg.h"
#include "PropertyPageTaskPanelNavigator.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

sltSetSheetDlgThread::sltSetSheetDlgThread()
{
	m_bDlgExist = FALSE;
}

sltSetSheetDlgThread::~sltSetSheetDlgThread()
{
	join();
}

HRESULT sltSetSheetDlgThread::startup()
{
	do 
	{
		if (m_bDlgExist)
			break ;
		
		start();
	} while (0);
	
	return S_OK;
}

int sltSetSheetDlgThread::run()
{	
	do 
	{
		m_bDlgExist = TRUE;
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		CXTPPropertySheet ps(g_lag.LoadString("title.set"));
		
		CPropertyPageTaskPanelNavigator* pList = new CPropertyPageTaskPanelNavigator();
		
		ps.SetNavigator(pList);
		ps.m_psh.dwFlags &= (~PSH_HASHELP);
		
		CCustomCiHuiDlg		cihuidlg;
		CSetAttributeDlg	attrdlg;
		CLicenseDlg			licdlg;
		CSkinDlg			skindlg;
		ps.AddPage(&attrdlg);
		ps.AddPage(&cihuidlg);
		ps.AddPage(&skindlg);
		ps.AddPage(&licdlg);
		
		ps.SetResizable();
		
		ps.DoModal();
	} while (0);
	
	m_bDlgExist = FALSE;
	
	return 0;
}
