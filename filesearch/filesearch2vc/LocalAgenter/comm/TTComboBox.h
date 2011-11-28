/*
 * TTComboBox.h
 * 
 * To use:
 *
 * The class CTTComboBox derive from MFC class - CCombobox,
 * there is only extended tool-tip functionality for the list-box 
 * in the combobox. you can immediately use the class CTTComboBox 
 * as well as make new class derive from it.
 *
 * Description:
 *
 * Install hooks for window subclassing, all messages go to new WindowProc
 * (window procedure) before going to the combobox, Usually, all windows 
 * with the same class share one window procedure.
 * There is using the new WindowProc to hold up the List-box's messages and 
 * to do too-tip things.
 *
 * Revision:
 *
 * 8th June, 2005
 * Thanks d3m0n to found out some issues about the control
 * I have fixed these issues at once as follows:
 *  1)
	Hover over the combobox, and the tooltip appears.
	Then while the tooltip is visible, click the arrow to expand the combobox.
	The dropdown list appears and then disappears immediately.

	2)
	While the tooltip is visible, nothing can receive focus.
	e.g. try clicking the Cancel button while a tooltip is visible.

	3)
	The size of the tooltip is sometimes too big.
	e.g. Hover over the listbox. Wait for the tooltip to appear and disappear.
	Now move the mouse out of the listbox. Now move it into the editbox.
	The size of the tooltip is much too big.
 *
 * Note:
 * you are allowed to use it for free and further modify it, 
 * but above the specification must be untouched at all times.
 *  
*/
#ifndef __TT_COMBOBOX__
#define __TT_COMBOBOX__

#include <afxwin.h>
#include <afxtempl.h>

/////////////////////////////////////////////////////////////////////////////
// CTTComboBox window

class CTTComboBox : public CComboBox
{
// Construction
public:
	CTTComboBox();

// Attributes
public:

private:
	// The original option selected when mouse cursor moves 
	// on in the list-box in the Combobox 
	static int		m_OriginalSel;

	// Pointer to the tool-tip window for the list-box
	static CWnd		m_tipWnd;

	// The font for tool-tip window
	static CFont	m_font;

	// Indicate delayed time for show the tool-tip window
	// Note: All combobox with the same class will use the same delayed time.
	static UINT		m_nDelayTime;

	// Indicate whether or not the mouse cursor entered in which
	// window will own the tool-tip.
	static BOOL		m_isEnter;
	
	// A list-box/edit-box window is corresponding to a redefined window proc.
	static CMap<HWND, HWND, WNDPROC, WNDPROC&> m_mapWndProc;

	// The coordinates of the button that contains drop-down arrow
	CRect	m_rcButton;

	// Indicate whether or not the too-tip window can be shown
	BOOL	m_isEnableTool;

	// The combobox information
	COMBOBOXINFO m_cbi;

public:
	// Set up the delayed time for show the tool-tip window
	static void SetTooltipDelay(UINT nDelay);

	// Get the delayed time for show the tool-tip window
	static UINT GetTooltipDelay();

// Operations
public:
	// Set the combobox own the tool-tip window
	void SetToolTip(BOOL bEnable=TRUE);

protected:
	// Create the tool-tip window
	void CreateTooltipWnd();

	// Destroy the tool-tip window
	// Note: it doesn't destroy the window object
	void DestroyTooltipWnd();

	// Install a hook to process messages send to the list-box and edit-box
	void InstallHookForListboxAndEditbox();

	// The callback function that hooks up and processes messages
	// send to the list-box within the combobox
	static LRESULT CALLBACK HookListboxWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// The callback function that hooks up and processes messages
	// send to the edit-box within the combobox
	static LRESULT CALLBACK HookEditboxWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// The callback function that hooks up and processes messages
	// send to the tool-tip window.
	static LRESULT CALLBACK HookTipWndProc(HWND hWnd, UINT message, WPARAM wp, LPARAM lp);

	// Handler for the mouse cursor moves on the list-box
	// that makes tool-tip for portion invisible option.
	static void HandleListboxMouseMove(CListBox* pList, UINT uFlag, CPoint point);	
	
	// Handler for the mouse cursor over the edit-box
	// that makes tool-tip for portion invisible text.
	// PARAMETER:
	// pWnd The window as edit box
	static void HandleEditboxMouseOver(CWnd* pWnd);

	// Handler for repaint the tool-tip window
	static void HandleOnPaint();

	// Handler for each interval specified when we used SetTimer to install a timer
	// for the tool-tip window.
	static void HandleOnTimer(UINT nIDEvent);

private:
	// Tracking mouse event on specified window
	// PARAMETER:
	// hWnd Handle to specified window
	// dwFlags Which events will be tracked
	static BOOL OnTrackMouseEvent(HWND hWnd, DWORD dwFlags);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTTComboBox)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTTComboBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTTComboBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	afx_msg void OnMouseOver(WPARAM wp, LPARAM lp);
	afx_msg void OnMouseLeave(WPARAM wp, LPARAM lp);

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif // __TT_COMBOBOX__
