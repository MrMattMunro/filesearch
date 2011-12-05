#include "stdafx.h"
#include "maindlg.h"

CMainDlg::CMainDlg():CBkDialogImpl<CMainDlg>(IDR_MAIN_DIALOG) // 在这里加载界面框架
{
	BkString::Load(IDR_STRING_DEF); // 加载字符串
	BkSkin::LoadSkins(IDR_SKIN_DEF); // 加载皮肤
	BkStyle::LoadStyles(IDR_STYLE_DEF); // 加载风格
}

CMainDlg::~CMainDlg()
{

}

LRESULT CMainDlg::OnClose()
{
	EndDialog(0);
	return 0;
}


LRESULT CMainDlg::OnMyClick()
{

	::MessageBox(0, L"请使用管理员账户运行本软件", 0, 0);
	return 0;
}

LRESULT CMainDlg::OnMaxWindow()
{
	if (WS_MAXIMIZE == (GetStyle() & WS_MAXIMIZE))
	{		
		SendMessage(WM_SYSCOMMAND, SC_RESTORE | HTCAPTION, 0);
	}
	else
	{		
		SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE | HTCAPTION, 0);
	}
	return 0;
}

LRESULT CMainDlg::OnMinWindow()
{
	SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
	return 0;
}

void CMainDlg::OnSysCommand(UINT nID, CPoint point)
{
	SetMsgHandled(FALSE);

	switch (nID & 0xFFF0)
	{
	case SC_CLOSE:
		SetMsgHandled(TRUE);
		OnClose();
		break;
	case SC_RESTORE:
		{
			DWORD dwStyle = GetStyle();
			if (WS_MINIMIZE == (dwStyle & WS_MINIMIZE))
				break;

			if (WS_MAXIMIZE == (dwStyle & WS_MAXIMIZE))
			{
				SetItemAttribute(IDC_BTN_MAX, "skin", "dlg_btn_max");
				break;
			}
		}
	case SC_MAXIMIZE:
		SetItemAttribute(IDC_BTN_MAX, "skin", "dlg_btn_normal");
		break;
	default:
		break;
	}
}