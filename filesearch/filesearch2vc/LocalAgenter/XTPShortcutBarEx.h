// XTPShortcutBarEx.h: interface for the CXTPShortcutBarEx class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XTPSHORTCUTBAREX_H__3FF1C900_CE9C_4B5A_9C62_F7856FB2BC89__INCLUDED_)
#define AFX_XTPSHORTCUTBAREX_H__3FF1C900_CE9C_4B5A_9C62_F7856FB2BC89__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CXTPShortcutBarEx  : public CXTPShortcutBar
{
public:
	CXTPShortcutBarEx();
	virtual ~CXTPShortcutBarEx();
	void SetParentWnd(LPVOID pParentWnd);
	
	LPVOID m_pParentWnd;
protected:
	//{{AFX_MSG(CTabTreeFile)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_XTPSHORTCUTBAREX_H__3FF1C900_CE9C_4B5A_9C62_F7856FB2BC89__INCLUDED_)
