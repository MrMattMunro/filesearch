////////////////////////////////////////////////////////////////////////////////
//      
//      File for kws 3.5 
//      
//      File      : menuwnd.h
//      Version   : 1.0
//      Comment   : 网盾弹出对话框 
//                  画出Menu菜单
//      
//      Create at : 2010-05-06
//		Create by : chenguicheng  
//      
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include <vector>
#include <atlstr.h>
#include <atlwin.h>
#include <atlframe.h>
#include <atlmisc.h>
#include "resource.h"

typedef std::vector<HBITMAP>																HBITMAPVEC;
typedef std::vector<ATL::CString>															TEXTVEC;

#define POPUP_LIST_ITEM_HEGIHT		30
#define POPUP_LIST_PADDING_LEFT		5
#define POPUP_LIST_PADDING_TOP		5

enum{
	MENU_SET_ID	= 0,
	MENU_WEB_ID,
	MENU_BBS_ID,
	MENU_REPORT_ID,
	MENU_HELP_ID,
	MENU_ABOUT_ID,
};

class KMenuWnd : public CWindowImpl< KMenuWnd >,
				public CDoubleBufferImpl<KMenuWnd>
{
public:
	KMenuWnd()
	{
		m_nCurIndex		= 0;
		m_nPreIndex		= 0;
		m_hMsgWnd		= NULL;
		m_nItemHeight	= 0;
		m_nItemWidth	= 0;
	}

	~KMenuWnd()
	{

	}

	BEGIN_MSG_MAP(KMenuWnd)
		
		MESSAGE_HANDLER( WM_CREATE,			OnCreate )
		MESSAGE_HANDLER( WM_DESTROY,		OnDestroy )
		MESSAGE_HANDLER( WM_LBUTTONDOWN,	OnLButtonDown )
		MESSAGE_HANDLER( WM_MOUSEMOVE,		OnMouseMove)
		MESSAGE_HANDLER( WM_ACTIVATEAPP,	OnActivateApp )
		MESSAGE_HANDLER( WM_KILLFOCUS,		OnKillFocus)
		CHAIN_MSG_MAP(CDoubleBufferImpl< KMenuWnd >)

	END_MSG_MAP()

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
		m_bmpSel.LoadBitmap( IDB_MENU_SEL ); 
		return TRUE;
	}

	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
       for ( int i = 0; i < m_vecBmp.size(); i++ )
		{
			HBITMAP hBmp = m_vecBmp[i];
			if (!hBmp)
				continue;

			::DeleteObject( (HGDIOBJ)hBmp );
		}
		return TRUE;
	}

	BOOL PopUp( int xPos, int yPos )
	{
		SetWindowPos( HWND_TOP, xPos, yPos, m_nItemWidth, m_nItemHeight * m_vecText.size() + 2, SWP_SHOWWINDOW );
		ShowWindow( SW_SHOWNORMAL );

		return TRUE;
	}


	void DoPaint(CDCHandle dc)
	{
		int xPos = POPUP_LIST_PADDING_LEFT;
		int yPos = POPUP_LIST_PADDING_TOP;

		//draw bg
		DrawBkGnd( dc, m_clrSel );
		//draw bmp
		DrawBmpIcon( dc );
		//draw text
		DrawItemText( dc );

		DrawBorderNormal( dc );

		return;
	}

	BOOL HideWnd()
	{
		ATLASSERT(m_hWnd);
		ShowWindow(SW_HIDE);
		return TRUE;
	}

	BOOL CreatePopUpList( HWND hMsgWnd, HWND hParentWnd, HBITMAPVEC& vecBmp, TEXTVEC& vecText, COLORREF crMask )
	{
		HWND hWnd = NULL;
		DWORD dwStyle = WS_POPUP;
		DWORD dwStyleEx = WS_EX_TOOLWINDOW | WS_EX_TOPMOST ;
		m_vecBmp = vecBmp;
		m_vecText = vecText;
		hWnd			= Create( hParentWnd, NULL, NULL, dwStyle, dwStyleEx );
		m_hMsgWnd		= hParentWnd;
		m_clrMask		= crMask;
		m_hMsgWnd		= hMsgWnd;

		ATLASSERT( hWnd );
		ShowWindow(SW_HIDE);
		return TRUE;
	}

	void DrawBkGnd( CDCHandle& dc, COLORREF clrSel )
	{
		CRect rect;
		GetClientRect( &rect );
		dc.FillSolidRect( rect, RGB(0xFF, 0xFF, 0xFF));

		//int nWidth = rect.Width();
		//rect.right = rect.left + 29;
		//dc.FillSolidRect( rect, RGB(0xE8, 0xF7, 0xD8));

		CRect rectSel;
		if ( m_nCurIndex != -1 )
		{
			rectSel.top = m_nCurIndex * m_nItemHeight;
			rectSel.left = 0;
			rectSel.bottom = rectSel.top + m_nItemHeight;
			rectSel.right = rectSel.left;
			_draw_bmp( dc, rectSel, m_bmpSel );
		}
	}

	void DrawBmpIcon( CDCHandle& dc )
	{
		if ( m_vecBmp.size() == 0 )
			return;

		int xPos = 4;
		int yPos = 4;

        for ( int i = 0; i < m_vecBmp.size(); i++ )
		{
			CBitmapHandle hBmp = m_vecBmp[i];
			if ( hBmp.IsNull() )
				continue;

			BITMAP bmp;
			hBmp.GetBitmap( &bmp );

			CRect rect( xPos, yPos, xPos + bmp.bmWidth, yPos + bmp.bmHeight );
			_draw_bmp_mask( dc, rect, hBmp, m_clrMask );

			yPos += m_nItemHeight;
		}
	}


	LRESULT OnActivateApp(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
		if( wParam == FALSE )
			ShowWindow( SW_HIDE );

		return TRUE;
	}

	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
		int xPos = GET_X_LPARAM(lParam);
		int yPos = GET_Y_LPARAM(lParam);

		ResetInfo();
		HideWnd();

		m_nCurIndex= HitTest( xPos, yPos);

		return TRUE;
	}

	BOOL ResetInfo()
	{
		m_nCurIndex = -1;
		m_nPreIndex = -1;

		return TRUE;
	}

	LRESULT OnKillFocus(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		ShowWindow( SW_HIDE );
		return TRUE;
	}

	LRESULT OnMouseMove(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
		int xPos = GET_X_LPARAM(lParam);
		int yPos = GET_Y_LPARAM(lParam);
		m_nCurIndex = HitTest( xPos, yPos);

		if ( m_nCurIndex != m_nPreIndex )
		{
			m_nPreIndex = m_nCurIndex;
			Invalidate(TRUE);
		}

		return TRUE;
	}

	void DrawBorderNormal( CDCHandle &dc )
	{
		CRect rect;
		GetClientRect( &rect );
		// 外围边框的颜色
		CBrush brush( ::CreateSolidBrush(RGB(128, 128, 128)));
		dc.FrameRect( &rect, brush );
		rect.InflateRect( -1, -1 );
		dc.FrameRect( rect, (HBRUSH)::GetStockObject(WHITE_BRUSH) );
	}

	void DrawItemText( CDCHandle &dc )
	{
		CFont font( GetNormalFont() );
		HFONT hOldFont = dc.SelectFont( font );

		int xPos = 32;
		int yPos = 5;

		dc.SetBkMode( TRANSPARENT );
		COLORREF clrSel;
		for ( int i = 0; i < m_vecText.size(); i ++ )
		{
			if( m_nCurIndex == i )
				clrSel = dc.SetTextColor( RGB(192, 192, 192) );
			else
				clrSel = dc.SetTextColor( RGB(0x00, 0x00, 0x00) );
			dc.TextOut( xPos, yPos, m_vecText[i], m_vecText[i].GetLength() );
			yPos += m_nItemHeight;

			dc.SetTextColor( clrSel );
		}

		if ( hOldFont )
		{
			dc.SelectFont( hOldFont );
		}
	}


	int HitTest(int xPos, int yPos )
	{
		int nIndex = -1;

		yPos -= POPUP_LIST_PADDING_TOP;
		nIndex = yPos / m_nItemHeight;

		if ( nIndex >= m_vecText.size() || nIndex < 0 )
		{
			nIndex = -1;
		}

		return nIndex;
	}


	void _draw_bmp( HDC hdc, CRect rect, HBITMAP hbmp )
	{
		CBitmapHandle hBmp( hbmp );
		CDC ComDC;
		HBITMAP hOldBmp = NULL;
		ComDC.CreateCompatibleDC( hdc );
		BITMAP bmp;
		hBmp.GetBitmap( &bmp );

		hOldBmp = ComDC.SelectBitmap( hBmp );

		::StretchBlt(   hdc,
			rect.left,
			rect.top,
			rect.right - rect.left,
			rect.bottom - rect.top,
			ComDC,
			0,
			0,
			bmp.bmWidth,
			bmp.bmHeight,
			SRCCOPY );

		ComDC.SelectBitmap( hOldBmp );
	}

	void _draw_bmp_mask( HDC hdc, CRect rect, HBITMAP hbmp, COLORREF clr_mask )
	{
		CBitmapHandle hBmp( hbmp );
		CDC ComDC;
		HBITMAP hOldBmp = NULL;
		ComDC.CreateCompatibleDC( hdc );
		BITMAP bmp;
		hBmp.GetBitmap( &bmp );

		hOldBmp = ComDC.SelectBitmap( hBmp );

		::TransparentBlt(   hdc,
			rect.left,
			rect.top,
			rect.right - rect.left,
			rect.bottom - rect.top,
			ComDC,
			0,
			0,
			bmp.bmWidth,
			bmp.bmHeight,
			clr_mask );

		ComDC.SelectBitmap( hOldBmp );
	}

	HFONT GetNormalFont()
	{
		CFontHandle hFont;
		LOGFONT lf;
		RtlZeroMemory(&lf, sizeof(LOGFONT));
		memset(&lf, 0, sizeof(LOGFONT));
		lf.lfHeight = 12 ;
		lf.lfWeight = 400;
		_tcscpy(lf.lfFaceName, TEXT("宋体") );
		hFont.CreateFontIndirect(&lf);

		return hFont;
	}

	void SetItemHeight( int nHeight )
	{
		m_nItemHeight = nHeight;
	}

	void SetItemWidth( int nWidth )
	{
		m_nItemWidth = nWidth;
	}

protected:

	CBitmap			m_bmpSel;
	TEXTVEC			m_vecText;
	HBITMAPVEC		m_vecBmp;
	COLORREF		m_clrMask;
	COLORREF		m_clrSel;

	int				m_nCurIndex;
	int				m_nPreIndex;
	HWND			m_hMsgWnd;
	int				m_nItemHeight;
	int				m_nItemWidth;

};