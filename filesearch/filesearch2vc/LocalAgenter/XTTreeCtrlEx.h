// XTTreeCtrlEx.h: interface for the CXTTreeCtrlEx class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XTTREECTRLEX_H__7BC632EF_4053_4EA1_865E_9F2EEAC2A934__INCLUDED_)
#define AFX_XTTREECTRLEX_H__7BC632EF_4053_4EA1_865E_9F2EEAC2A934__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ShortcutPaneBase.h"
class CXTTreeCtrlEx  : public CXTTreeCtrl
{
public:
	CXTTreeCtrlEx();
	virtual ~CXTTreeCtrlEx();
	
	void SetParentPane(CShortcutPaneBase* pBase);
	CShortcutPaneBase* m_pBase;
	// Attributes
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabTreeFile)

	//}}AFX_VIRTUAL
	
	// Implementation
public:
	void UpdateTree();
	// Generated message map functions
protected:
	//{{AFX_MSG(CTabTreeFile)
	afx_msg void OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBeginlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_XTTREECTRLEX_H__7BC632EF_4053_4EA1_865E_9F2EEAC2A934__INCLUDED_)
