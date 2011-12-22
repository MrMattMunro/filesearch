#pragma once

#include "bkres/bkres.h"
#include "atlapp.h"
#include "resource.h"
#include "menuwnd.h"

class CMainDlg : public CBkDialogImpl<CMainDlg>
{

public:
	BK_NOTIFY_MAP(IDC_RICHVIEW_WIN)
		BK_NOTIFY_ID_COMMAND(IDC_BTN_CLOSE, OnClose)	
		BK_NOTIFY_ID_COMMAND(IDC_BTN_MAX, OnMaxWindow)
		BK_NOTIFY_ID_COMMAND(IDC_BTN_MIN, OnMinWindow)
		//BK_NOTIFY_ID_COMMAND(IDC_MENU_FILE, OnBnClickedPopupMenu)

		//BK_NOTIFY_ID_COMMAND(IDC_MENU_FILE, BN_CLICKED, OnBnClickedPopupMenu)
		// 标准控件的事件处理: ComboBox选中的内容改变时通知
		BK_NOTIFY_ID_COMMAND(IDC_MENU_FILE, OnBnClickedPopupMenu)
	    BK_NOTIFY_ID_COMMAND(IDC_MENU_VIEW, OnViewMenu)
		BK_NOTIFY_ID_COMMAND(IDC_MENU_TOOL, OnToolMenu)
		BK_NOTIFY_ID_COMMAND(IDC_MENU_HELP, OnHelpMenu)
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

    void	OnViewMenu();
    void	OnToolMenu();
	void	OnHelpMenu();
    LRESULT OnMyClick();
	LRESULT OnClose();
	LRESULT OnMaxWindow();
	LRESULT OnMinWindow();
	void	OnSysCommand(UINT nID, CPoint point);
	void    OnBnClickedPopupMenu();

	// 文件菜单 文字内容从资源文件中读取
	void initFileMenu()
	{
		if( !m_file_wndMenu.IsWindow() )
		{
			HBITMAPVEC vecBmp;

			CBitmapHandle bmpSet,bmpAbout;
			bmpSet.LoadBitmap( IDB_MENU_SET );
			vecBmp.push_back( bmpSet );
			bmpAbout.LoadBitmap( IDB_MENU_ABOUT );
			vecBmp.push_back( bmpAbout );

			TEXTVEC vecText;
			vecText.push_back( BkString::Get(IDS_FILEMENU_IMPORT));
			vecText.push_back( BkString::Get(IDS_FILEMENU_EXPORT));
			vecText.push_back( BkString::Get(IDS_FILEMENU_SASEAS));
			vecText.push_back( BkString::Get(IDS_FILEMENU_SASETOMOBILE));
			vecText.push_back( BkString::Get(IDS_FILEMENU_EXIT));
			m_file_wndMenu.SetItemHeight(28);
			m_file_wndMenu.SetItemWidth(195);
			m_file_wndMenu.CreatePopUpList( m_hWnd, m_hWnd, vecBmp, vecText,  RGB(0xFF,0x00, 0xFF) );
		}
	}

	void initViewMenu()
	{
		if( !m_view_wndMenu.IsWindow() )
		{
			HBITMAPVEC vecBmp;

			CBitmapHandle bmpSet;
			bmpSet.LoadBitmap( IDB_MENU_SET );
			vecBmp.push_back( bmpSet );

			TEXTVEC vecText;
			vecText.push_back( BkString::Get(IDS_VIEWMENU_FULLSCREEN));
			vecText.push_back( BkString::Get(IDS_VIEWMENU_SHOWCLASSTREE));
			vecText.push_back( BkString::Get(IDS_VIEWMENU_SKIN));
			vecText.push_back( BkString::Get(IDS_VIEWMENU_CUSTOMTOOLS));
			m_view_wndMenu.SetItemHeight(28);
			m_view_wndMenu.SetItemWidth(195);
			m_view_wndMenu.CreatePopUpList( m_hWnd, m_hWnd, vecBmp, vecText, RGB(0xFF,0x00, 0xFF) );
		}
	}

	void initToolMenu()
	{
		if( !m_tool_wndMenu.IsWindow() )
		{
			HBITMAPVEC vecBmp;

			CBitmapHandle bmpSet;
			bmpSet.LoadBitmap( IDB_MENU_SET );
			vecBmp.push_back( bmpSet );

			TEXTVEC vecText;
			vecText.push_back( BkString::Get(IDS_TOOLMENU_OPTION));
			vecText.push_back( BkString::Get(IDS_TOOLMENU_VIEWLOG));
			vecText.push_back( BkString::Get(IDS_TOOLMENU_PLUGIN));
			m_tool_wndMenu.SetItemHeight(28);
			m_tool_wndMenu.SetItemWidth(195);
			m_tool_wndMenu.CreatePopUpList( m_hWnd, m_hWnd, vecBmp, vecText, RGB(0xFF,0x00, 0xFF) );
		}
	}

	void initHelpMenu()
	{
		if( !m_help_wndMenu.IsWindow() )
		{
			HBITMAPVEC vecBmp;

			CBitmapHandle bmpSet;
			bmpSet.LoadBitmap( IDB_MENU_SET );
			vecBmp.push_back( bmpSet );

			TEXTVEC vecText;
			vecText.push_back( BkString::Get(IDS_HELPMENU_HELPDOC));
			vecText.push_back( BkString::Get(IDS_HELPMENU_HOMEPAGE));
			vecText.push_back( BkString::Get(IDS_HELPMENU_INVITE));
			vecText.push_back( BkString::Get(IDS_HELPMENU_CHECKVERSION));
			vecText.push_back( BkString::Get(IDS_HELPMENU_INVITE));
			vecText.push_back( BkString::Get(IDS_HELPMENU_BBS));
			vecText.push_back( BkString::Get(IDS_HELPMENU_ABOUT));
			m_help_wndMenu.SetItemHeight(28);
			m_help_wndMenu.SetItemWidth(195);
			m_help_wndMenu.CreatePopUpList( m_hWnd, m_hWnd, vecBmp, vecText, RGB(0xFF,0x00, 0xFF) );
		}
	}

protected:
	KMenuWnd m_file_wndMenu, m_view_wndMenu, m_tool_wndMenu, m_help_wndMenu;

};

extern CAppModule _Module;
