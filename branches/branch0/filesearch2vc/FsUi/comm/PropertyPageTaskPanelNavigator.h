// PropertyPageTaskPanelNavigator.h: interface for the CPropertyPageTaskPanelNavigator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROPERTYPAGETASKPANELNAVIGATOR_H__0C8161F9_E648_4812_890A_1D8973A0FB4F__INCLUDED_)
#define AFX_PROPERTYPAGETASKPANELNAVIGATOR_H__0C8161F9_E648_4812_890A_1D8973A0FB4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPropertyPageTaskPanelNavigator   : public CXTPTaskPanel, public CXTPPropertyPageControlNavigator
{
public:
	CPropertyPageTaskPanelNavigator();
	virtual ~CPropertyPageTaskPanelNavigator();
	
public:
	virtual BOOL Create();
	virtual void OnPageSelected(CXTPPropertyPage* pPage);
	virtual HWND GetSafeHwnd() const { return m_hWnd; }
	
protected:
	virtual void SetFocusedItem(CXTPTaskPanelItem* pItem, BOOL bDrawFocusRect = FALSE, BOOL bSetFocus = TRUE);
};

#endif // !defined(AFX_PROPERTYPAGETASKPANELNAVIGATOR_H__0C8161F9_E648_4812_890A_1D8973A0FB4F__INCLUDED_)
