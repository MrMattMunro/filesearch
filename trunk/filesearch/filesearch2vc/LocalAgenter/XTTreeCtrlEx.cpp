// XTTreeCtrlEx.cpp: implementation of the CXTTreeCtrlEx class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LocalAgenter.h"
#include "XTTreeCtrlEx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXTTreeCtrlEx::CXTTreeCtrlEx()
{
	m_pBase = NULL;
}

CXTTreeCtrlEx::~CXTTreeCtrlEx()
{

}

BEGIN_MESSAGE_MAP(CXTTreeCtrlEx, CXTTreeCtrl)
//{{AFX_MSG_MAP(CTabTreeFile)
ON_NOTIFY_REFLECT(TVN_ENDLABELEDIT, OnEndlabeledit)
ON_NOTIFY_REFLECT(TVN_BEGINLABELEDIT, OnBeginlabeledit)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CXTTreeCtrlEx::OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;
	
	// TODO: Add your control notification handler code here
	if (pTVDispInfo->item.pszText && m_pBase)
	{
		if (m_pBase->m_nType == 1 && ItemHasChildren(pTVDispInfo->item.hItem))
		{
			*pResult = 0;
			return ;
		}

		CString strNewTxet(pTVDispInfo->item.pszText);
		strNewTxet.TrimLeft();
		strNewTxet.TrimRight();
		if (strNewTxet.GetLength() == 0)
		{
			//½ûÖ¹ÊäÈë¿Õ
			*pResult = 0;
			return ;
		}

		SetItemText(pTVDispInfo->item.hItem,
			pTVDispInfo->item.pszText);
		if (m_pBase != NULL)
		{
			m_pBase->RenameItem(pTVDispInfo->item.pszText);
		}
	}
	
	*pResult = 0;
}


void CXTTreeCtrlEx::OnBeginlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;
	
	// TODO: Add your control notification handler code here
	if (pTVDispInfo->item.pszText && m_pBase)
	{
		if (m_pBase->m_nType == 1 && ItemHasChildren(pTVDispInfo->item.hItem))
		{
			*pResult = 0;
			return ;
		}
		m_pBase->SetOlditemText(pTVDispInfo->item.pszText);
	}
	
	*pResult = 0;
}

void CXTTreeCtrlEx::SetParentPane(CShortcutPaneBase* pBase)
{
	m_pBase = pBase;
}