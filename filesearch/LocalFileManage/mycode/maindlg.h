#pragma once

#include "bkres/bkres.h"
#include "atlapp.h"
#include "resource.h"

class CMainDlg 
	: public CBkDialogImpl<CMainDlg>
{

public:
	BK_NOTIFY_MAP(IDC_RICHVIEW_WIN)
		BK_NOTIFY_ID_COMMAND(IDC_BTN_CLOSE, OnClose)
		BK_NOTIFY_ID_COMMAND(IDC_BTN_MAX, OnMaxWindow)
		BK_NOTIFY_ID_COMMAND(IDC_BTN_MIN, OnMinWindow)
	    BK_NOTIFY_ID_COMMAND(IDC_CHK_TEST, OnMyClick)
	BK_NOTIFY_MAP_END()


	BEGIN_MSG_MAP_EX(CMainDlg)
		MSG_BK_NOTIFY(IDC_RICHVIEW_WIN)
		MSG_WM_SYSCOMMAND(OnSysCommand)
		CHAIN_MSG_MAP(CBkDialogImpl<CMainDlg>)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

public:
	CMainDlg();
	~CMainDlg();

    LRESULT OnMyClick();
	LRESULT OnClose();
	LRESULT OnMaxWindow();
	LRESULT OnMinWindow();
	void	OnSysCommand(UINT nID, CPoint point);

};

extern CAppModule _Module;
