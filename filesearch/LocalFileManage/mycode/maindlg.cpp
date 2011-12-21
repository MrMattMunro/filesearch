#include "stdafx.h"
#include "maindlg.h"
#include "resource.h"


CMainDlg::CMainDlg():CBkDialogImpl<CMainDlg>(IDR_MAIN_DIALOG) // 在这里加载界面框架
{
	BkString::Load(IDR_STRING_DEF); // 加载字符串
	BkSkin::LoadSkins(IDR_SKIN_DEF); // 加载皮肤
	BkStyle::LoadStyles(IDR_STYLE_DEF); // 加载风格
}

CMainDlg::~CMainDlg()
{

}

// 关闭窗体
LRESULT CMainDlg::OnClose()
{
	EndDialog(0);
	return 0;
}

// 最大化窗体
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

// 最小化窗体
LRESULT CMainDlg::OnMinWindow()
{
	SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
	return 0;
}

// 文件菜单
void CMainDlg::OnBnClickedPopupMenu()
{
	
	initFileMenu();
	if( m_file_wndMenu.IsWindow() )
	{
		CRect	rc;
		GetClientRect(&rc);
		ClientToScreen(&rc);
		m_file_wndMenu.PopUp( rc.left, rc.top + 50);
	}
}

// 查看菜单
void CMainDlg::OnViewMenu()
{
	CPoint	pos;
	CRect	rc;
	GetClientRect(&rc);
	ClientToScreen(&rc);

	pos.x = rc.right - 950;
	pos.y = rc.top + 50;

	CMenu menuPopup;
	menuPopup.LoadMenu(IDR_VIEWMENU);

	CMenuHandle Menu = menuPopup.GetSubMenu(0);;
	
	//ATLVERIFY(GetCursorPos(&pos));
	Menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_TOPALIGN, pos.x, pos.y, m_hWnd);
}
// 工具菜单
void CMainDlg::OnToolMenu()
{
	CPoint	pos;
	CRect	rc;
	GetClientRect(&rc);
	ClientToScreen(&rc);

	pos.x = rc.right - 890;
	pos.y = rc.top + 50;

	CMenu menuPopup;
	menuPopup.LoadMenu(IDR_TOOLMENU);

	CMenuHandle Menu = menuPopup.GetSubMenu(0);;
	
	//ATLVERIFY(GetCursorPos(&pos));
	Menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_TOPALIGN, pos.x, pos.y, m_hWnd);
}

// 帮助菜单
void CMainDlg::OnHelpMenu()
{
	CPoint	pos;
	CRect	rc;
	GetClientRect(&rc);
	ClientToScreen(&rc);

	pos.x = rc.right - 830;
	pos.y = rc.top + 50;

	CMenu menuPopup;
	menuPopup.LoadMenu(IDR_HELPMENU);

	CMenuHandle Menu = menuPopup.GetSubMenu(0);;
	
	//ATLVERIFY(GetCursorPos(&pos));
	Menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_TOPALIGN, pos.x, pos.y, m_hWnd);
}



// 系统图标
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