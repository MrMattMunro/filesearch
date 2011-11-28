// TTComboBox.cpp : implementation file
//

#include "stdafx.h"
#include "TTComboBox.h"

CWnd	CTTComboBox::m_tipWnd;
int		CTTComboBox::m_OriginalSel = LB_ERR;
UINT	CTTComboBox::m_nDelayTime = 1000; // millisecond
BOOL	CTTComboBox::m_isEnter = FALSE;
CFont	CTTComboBox::m_font;
CMap<HWND, HWND, WNDPROC, WNDPROC&> CTTComboBox::m_mapWndProc;
/////////////////////////////////////////////////////////////////////////////
// CTTComboBox

CTTComboBox::CTTComboBox()
{
	// Using system tool-tip font for the tool-tip window
	NONCLIENTMETRICS ncm;
	ncm.cbSize = sizeof(NONCLIENTMETRICS);
	SystemParametersInfo(SPI_GETNONCLIENTMETRICS, 0, &ncm, 0);
	if (m_font.m_hObject == NULL)
		m_font.CreateFontIndirect(&ncm.lfStatusFont);

	m_rcButton = CRect(0,0,0,0);
	m_isEnableTool = TRUE; // The tool-tip is allowed

	// Create the tool-tip window
	this->CreateTooltipWnd();
}

CTTComboBox::~CTTComboBox()
{
	// Clean up the map 
	if (m_cbi.hwndList)
		m_mapWndProc.RemoveKey(m_cbi.hwndList);
	if (m_cbi.hwndItem)
		m_mapWndProc.RemoveKey(m_cbi.hwndItem);

	// Destroy the tool-tip window
	DestroyTooltipWnd();
}

void CTTComboBox::SetTooltipDelay(UINT nDelay)
{
	m_nDelayTime = nDelay;
}

UINT CTTComboBox::GetTooltipDelay()
{
	return m_nDelayTime;
}

void CTTComboBox::SetToolTip(BOOL bEnable/*=TRUE*/)
{
	m_isEnableTool = bEnable;
}


BEGIN_MESSAGE_MAP(CTTComboBox, CComboBox)
	//{{AFX_MSG_MAP(CTTComboBox)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MOUSEHOVER, OnMouseOver)
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTTComboBox message handlers

int CTTComboBox::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CComboBox::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// If the combo-box isn't dynamically subclassed that 
	// should get rid of the /* and */ commenting characters below
	/*
	if (m_isEnableTool == TRUE)
	{
		InstallHookForListboxAndEditbox();
	}
	*/

	return 0;
}

void CTTComboBox::CreateTooltipWnd()
{
	// However, the tool-tip window only once created and all combobox 
	// have share in the tool-tip window.
	if (!::IsWindow(m_tipWnd.m_hWnd))
	{
		m_tipWnd.CreateEx(WS_EX_TOOLWINDOW,
			AfxRegisterWndClass(0, AfxGetApp()->LoadStandardCursor(IDC_ARROW)),
		NULL, WS_POPUP, 0, 0, 0, 0, NULL, NULL);

		// Set up hooking with the tip window
		// Note: Refer to MSDN, In Windows NT/2000, You cannot change this attribute(GWL_WNDPROC) 
		// if the window(i.e, too-tip) does not belong to the same process as the calling thread.
		WNDPROC oldTipWndProc = (WNDPROC)::SetWindowLong(m_tipWnd.m_hWnd, 
			GWL_WNDPROC, (DWORD)HookTipWndProc);
		// Add the old hook(i.e, hook associated with window) to the map
		m_mapWndProc.SetAt(m_tipWnd.m_hWnd, oldTipWndProc);
	}
}

void CTTComboBox::DestroyTooltipWnd()
{
	int nSize = m_mapWndProc.GetCount();
	WNDPROC oldTipWndProc;
	HWND hWnd = m_tipWnd.m_hWnd;
	BOOL bRet = m_mapWndProc.Lookup(hWnd, oldTipWndProc);
	if (nSize == 1 && bRet == TRUE)
	{// Reset only one window procedure(i.e, the tool-tip window procedure)
	 // that means any combobox doesn't use the tool-tip window. 
		m_tipWnd.DestroyWindow();
		m_mapWndProc.RemoveKey(hWnd);
	}
}

void CTTComboBox::InstallHookForListboxAndEditbox()
{
	// Get the list-box/edit-box within the combobox and set up hooking with it.
	// Note: this only for Win98 or WinNT5.0 or later, 
	// However you must defined WINVER >= 0x0500 within the project
	ZeroMemory(&m_cbi, sizeof(COMBOBOXINFO));
	m_cbi.cbSize = sizeof(COMBOBOXINFO);
	::GetComboBoxInfo(m_hWnd, &m_cbi);
	m_rcButton = m_cbi.rcButton;

	if (m_cbi.hwndList)
	{
		// Set up hooking for the list-box within the combobox
		// Note: Refer to MSDN, In Windows NT/2000, You cannot change this attribute(GWL_WNDPROC) 
		// if the window(i.e, list-box) does not belong to the same process as the calling thread.
		WNDPROC oldListWndProc = (WNDPROC)::SetWindowLong(m_cbi.hwndList, GWL_WNDPROC, (DWORD)HookListboxWndProc);
		// Add the old hook(i.e, hook associated with window) to the map
		m_mapWndProc.SetAt(m_cbi.hwndList, oldListWndProc);
	}
	
	if (m_cbi.hwndItem)
	{
		// Set up hooking for the edit-box within the combobox
		// Note: Refer to MSDN, In Windows NT/2000, You cannot change this attribute(GWL_WNDPROC) 
		// if the window(i.e, edit-box) does not belong to the same process as the calling thread.
		WNDPROC oldEditWndProc = (WNDPROC)::SetWindowLong(m_cbi.hwndItem, GWL_WNDPROC, (DWORD)HookEditboxWndProc);
		// Add the old hook(i.e, hook associated with window) to the map
		m_mapWndProc.SetAt(m_cbi.hwndItem, oldEditWndProc);
	}
}

// The callback function that hooks up and processes messages
// send to the list-box within the combobox
LRESULT CALLBACK 
CTTComboBox::HookListboxWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CListBox* pList = (CListBox*)CWnd::FromHandle(hWnd);

	if (message == WM_MOUSEMOVE)
	{
		WORD xPos, yPos;
		xPos = LOWORD(lParam);
		yPos = HIWORD(lParam);
		CPoint point(xPos, yPos); 
		CRect rcClient;
		::GetClientRect(hWnd, &rcClient);
		if (rcClient.PtInRect(point))
		{// Handle mouse move event that may show a tool-tip window...
			CTTComboBox::HandleListboxMouseMove(pList, wParam, point);
		}
		else
		{// However, the list-box may be captured thus we must know when the mouse cursor
		 // out of the area of the list-box, and send 'WM_MOUSELEAVE' notification.
			::SendMessage(hWnd, WM_MOUSELEAVE, wParam, lParam);
		}

		if (!m_isEnter)
		{// Tracking the mouse event which are hovering and leaving.
			OnTrackMouseEvent(hWnd, TME_HOVER|TME_LEAVE);
			m_isEnter = TRUE;
		}
	}
	else if (message == WM_MOUSELEAVE)
	{
		// When the mouse cursor has been left current window, the original select of the list-box 
		// to reset LB_ERR.
		m_OriginalSel = LB_ERR;
		m_isEnter = FALSE;	
		// The tool-tip window is hidden
		m_tipWnd.ShowWindow(SW_HIDE);
	}
	else if (message == WM_CAPTURECHANGED)
	{	// Ignore the mouse capture changed...
		return 1;
	}

	// Get previous window procedure
	WNDPROC oldListWndProc;
	m_mapWndProc.Lookup(hWnd, oldListWndProc);
	// Call previous window procedure
	return ::CallWindowProc(oldListWndProc, hWnd, message, wParam, lParam);
}

LRESULT CALLBACK 
CTTComboBox::HookEditboxWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{	
	CWnd* pWnd = CWnd::FromHandle(hWnd);
	
	if (message == WM_MOUSEMOVE)
	{
		// However, the edit-box may be captured thus we must know when the mouse cursor
		// out of the area of the edit-box, and send 'WM_MOUSELEAVE' notification.
		CPoint point;
		point.x = LOWORD(lParam);
		point.y = HIWORD(lParam);
		CRect rcBounds;
		::GetClientRect(hWnd, &rcBounds);
		if (rcBounds.PtInRect(point) == FALSE)
		{
			::SendMessage(hWnd, WM_MOUSELEAVE, wParam, lParam);
		}

		if (!m_isEnter)
		{// Tracking the mouse event which are hovering and leaving.
			OnTrackMouseEvent(hWnd, TME_HOVER|TME_LEAVE);
			m_isEnter = TRUE;
		}
	}
	else if (message == WM_MOUSEHOVER)
	{
		HandleEditboxMouseOver(pWnd);
	}
	else if (message == WM_MOUSELEAVE)
	{
		// When the mouse cursor has been left current window, the original select of the list-box 
		// to reset LB_ERR.
		m_OriginalSel = LB_ERR;
		m_isEnter = FALSE;
		// The tool-tip window is hidden
		m_tipWnd.ShowWindow(SW_HIDE);
	}

	// Get previous window procedure
	WNDPROC oldEditWndProc;
	m_mapWndProc.Lookup(hWnd, oldEditWndProc);
	// Call previous window procedure
	return ::CallWindowProc(oldEditWndProc, hWnd, message, wParam, lParam);
}

// The callback function that hooks up and processes messages
// send to the tool-tip window.
LRESULT CALLBACK CTTComboBox::HookTipWndProc(HWND hWnd, UINT message, WPARAM wp, LPARAM lp)
{
	if (message == WM_PAINT)
	{
		CTTComboBox::HandleOnPaint();
	}
	else if (message == WM_TIMER)
	{
		CTTComboBox::HandleOnTimer(wp);
	}
	else if (message == WM_SHOWWINDOW &&
		wp == FALSE)
	{
		 // Release the mouse capture from a window 
		 // mean the mouse will reenter the(or other) window at next time
		ReleaseCapture();
	}

	// Get previous window procedure
	WNDPROC oldTipWndProc;
	m_mapWndProc.Lookup(hWnd, oldTipWndProc);

	// Call previous window procedure
	return ::CallWindowProc(oldTipWndProc, hWnd, message, wp, lp);
}

void CTTComboBox::HandleListboxMouseMove(CListBox* pList, UINT uFlag, CPoint point)
{	
	BOOL bOutside;
	int curSel = pList->ItemFromPoint(point, bOutside);
	if (bOutside)
		return; // the point is outside the client area of the item in the list-box

	if (m_OriginalSel == curSel || 
		curSel == LB_ERR)
	{// If The current option is original or a error selected that get outta here
		return; 
	}

	m_OriginalSel = curSel;

	CDC* pDC = m_tipWnd.GetDC();
	CFont* pOldFont = pDC->SelectObject(&m_font);
	CString strText;
	pList->GetText(curSel, strText);
	CRect rcBounds;
	pList->GetItemRect(curSel, &rcBounds);
	CRect rcDraw = rcBounds;
	pDC->DrawText(strText, &rcDraw, DT_CALCRECT|DT_SINGLELINE|DT_CENTER|DT_VCENTER);
	pDC->SelectObject(pOldFont);
	::ReleaseDC(m_tipWnd.GetSafeHwnd(), pDC->m_hDC);

	if (rcDraw.right <= rcBounds.right)
	{// However don't show the tool-tip window and get outta here, 
	 // unless the tool-tip window's width is greater than 
	 // the option's width in the list-box.
	//	m_tipWnd.ShowWindow(SW_HIDE);
		return;
	}

	rcDraw.InflateRect(2,2);
	pList->ClientToScreen(&rcDraw);
	m_tipWnd.SetWindowText(strText);

	m_tipWnd.ShowWindow(SW_HIDE); // Last showing window is hidden

	// Capture current window that prevent mouse cursor leave current window,
	// The cause is the mouse cursor will be over the tool-tip window(see below).
	if (GetCapture() != pList)
		::SetCapture(pList->m_hWnd);

	// Delayed to show the tool-tip window by given position
	m_tipWnd.SetWindowPos(&CWnd::wndTopMost, 
		rcDraw.left, rcDraw.top, rcDraw.Width(), rcDraw.Height(), SWP_NOACTIVATE | SWP_SHOWWINDOW);
	m_tipWnd.SetTimer(1, m_nDelayTime, NULL);
}

void CTTComboBox::HandleEditboxMouseOver(CWnd* pWnd)
{
	CRect rcBounds;
	pWnd->GetClientRect(&rcBounds);

	CString strText;
	pWnd->GetWindowText(strText);

	CDC* pDC = m_tipWnd.GetDC();
	CFont* pOldFont = pDC->SelectObject(&m_font);
	CRect rcDraw = rcBounds;
	pDC->DrawText(strText, &rcDraw, DT_CALCRECT|DT_SINGLELINE|DT_CENTER|DT_VCENTER);
	pDC->SelectObject(pOldFont);
	::ReleaseDC(m_tipWnd.GetSafeHwnd(), pDC->m_hDC);

	if (rcDraw.right <= rcBounds.right)
	{// However don't show the tool-tip window and get outta here, 
	 // unless the tool-tip window's width is greater than 
	 // the option's width in the list-box.
		m_tipWnd.ShowWindow(SW_HIDE);
	}
	else
	{
		rcDraw.bottom = rcBounds.bottom;
		rcDraw.InflateRect(2,2);
		pWnd->ClientToScreen(&rcDraw);
		m_tipWnd.SetWindowText(strText);
		m_tipWnd.ShowWindow(SW_HIDE); // Last showing window is hidden
		
		// Capture current window that prevent mouse cursor leave current window,
		// The cause is the mouse cursor will be over the tool-tip window(see below).
		::SetCapture(pWnd->m_hWnd);

		// Delayed to show the tool-tip window by given position
		m_tipWnd.SetWindowPos(&CWnd::wndTopMost, 
			rcDraw.left, rcDraw.top, rcDraw.Width(), rcDraw.Height(), SWP_NOACTIVATE | SWP_SHOWWINDOW);
		m_tipWnd.SetTimer(1, m_nDelayTime, NULL);
	}
}

// Handler for repaint tool-tip window
void CTTComboBox::HandleOnPaint()
{
	CPaintDC dc(&m_tipWnd);
	CRect rc;
	m_tipWnd.GetClientRect(&rc);
	CBrush brush(GetSysColor(COLOR_INFOBK));
	dc.FillRect(&rc, &brush);

	CBrush border(RGB(0,0,0));
	dc.FrameRect(&rc, &border);

	CString strText;
	m_tipWnd.GetWindowText(strText);
	dc.SetBkMode(TRANSPARENT);
	CFont* pOldFont = dc.SelectObject(&m_font);
	dc.DrawText(strText, &rc, DT_SINGLELINE|DT_CENTER|DT_VCENTER);

	dc.SelectObject(pOldFont);
}

// Handler for each interval specified when we used SetTimer to install a timer
// for tool-tip window.
void CTTComboBox::HandleOnTimer(UINT nIDEvent)
{
	m_tipWnd.KillTimer(nIDEvent);
	m_tipWnd.ShowWindow(SW_HIDE);
}

BOOL CTTComboBox::OnTrackMouseEvent(HWND hWnd, DWORD dwFlags)
{
	TRACKMOUSEEVENT tme;
	tme.cbSize = sizeof(TRACKMOUSEEVENT);
	tme.dwFlags = dwFlags;
	tme.dwHoverTime = HOVER_DEFAULT;
	tme.hwndTrack = hWnd;
	return ::_TrackMouseEvent(&tme);
}

void CTTComboBox::PreSubclassWindow() 
{
	CComboBox::PreSubclassWindow();
	
	// If the combo-box isn't dynamically subclassed that should get rid of 
	// the codes as follows and the codes should be placed in the OnCreate function.
	if (m_isEnableTool == TRUE)
	{
		InstallHookForListboxAndEditbox();
	}
}

void CTTComboBox::OnMouseMove(UINT nFlags, CPoint point) 
{
	// However, the combobox may be captured thus we must know when the mouse cursor
	// out of the area of the combobox, and send 'WM_MOUSELEAVE' notification.
	CRect rcBounds;
	GetClientRect(&rcBounds);
	if (rcBounds.PtInRect(point) == FALSE)
	{
		SendMessage(WM_MOUSELEAVE);
	}
	
	// Here is tracking mouse event such as 'HOVER', 'LEAVE'.
	if (m_isEnter == FALSE)
	{
		OnTrackMouseEvent(m_hWnd, TME_HOVER|TME_LEAVE);
		m_isEnter = TRUE;
	}

	CComboBox::OnMouseMove(nFlags, point);
}

void CTTComboBox::OnMouseOver(WPARAM wp, LPARAM lp) 
{
	if (m_isEnableTool == FALSE)
		return;

	if (::IsWindow(m_cbi.hwndItem))
		return; // If the edit-box has exist that gotta here

	CRect rcBounds;
	GetClientRect(&rcBounds);
	rcBounds.right -= m_rcButton.Width();

	CString strText;
	GetWindowText(strText);

	CDC* pDC = m_tipWnd.GetDC();
	CFont* pOldFont = pDC->SelectObject(&m_font);
	CRect rcDraw = rcBounds;
	pDC->DrawText(strText, &rcDraw, DT_CALCRECT|DT_SINGLELINE|DT_CENTER|DT_VCENTER);
	pDC->SelectObject(pOldFont);
	::ReleaseDC(m_tipWnd.GetSafeHwnd(), pDC->m_hDC);

	if (rcDraw.right <= rcBounds.right)
	{// However don't show the tool-tip window and get outta here, 
	 // unless the tool-tip window's width is greater than 
	 // the option's width in the list-box.
		m_tipWnd.ShowWindow(SW_HIDE);
		return;
	}

	rcDraw.bottom = rcBounds.bottom;
	rcDraw.InflateRect(2,2);
	ClientToScreen(&rcDraw);
	m_tipWnd.SetWindowText(strText);
	m_tipWnd.ShowWindow(SW_HIDE); // Last showing window is hidden

	// Capture current window that prevent mouse cursor leave current window,
	// The cause is the mouse cursor will be over the tool-tip window(see below).
	SetCapture();

	// Delayed to show the tool-tip window by given position
	m_tipWnd.SetWindowPos(&CWnd::wndTopMost, 
		rcDraw.left, rcDraw.top, rcDraw.Width(), rcDraw.Height(), SWP_NOACTIVATE | SWP_SHOWWINDOW);
	m_tipWnd.SetTimer(1, m_nDelayTime, NULL);
}

void CTTComboBox::OnMouseLeave(WPARAM wp, LPARAM lp)
{
	// The mouse cursor has leave current window
	m_isEnter = FALSE;
	// The tool-tip window is hidden
	m_tipWnd.ShowWindow(SW_HIDE);
}

void CTTComboBox::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if (m_tipWnd.IsWindowVisible())
		ReleaseCapture();
	
	CComboBox::OnLButtonDown(nFlags, point);
}
