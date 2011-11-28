// ShortcutPaneBase.h: interface for the CShortcutPaneBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHORTCUTPANEBASE_H__81429252_C7FF_45D4_A849_4CBD2A5619C6__INCLUDED_)
#define AFX_SHORTCUTPANEBASE_H__81429252_C7FF_45D4_A849_4CBD2A5619C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CShortcutPaneBase  
{
public:
	CShortcutPaneBase();
	virtual ~CShortcutPaneBase();

	virtual BOOL RenameItem(CString strNewitem)	{	return TRUE;	}
	virtual void SetOlditemText(CString strOlditem)	{	return ;	}

	int m_nType;
};

#endif // !defined(AFX_SHORTCUTPANEBASE_H__81429252_C7FF_45D4_A849_4CBD2A5619C6__INCLUDED_)
