// XTPReportControlEx.h: interface for the CXTPReportControlEx class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XTPREPORTCONTROLEX_H__239D59CE_2B79_468E_A66B_E67030B3F4EA__INCLUDED_)
#define AFX_XTPREPORTCONTROLEX_H__239D59CE_2B79_468E_A66B_E67030B3F4EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CXTPReportControlEx  :public CXTPReportControl
{
public:
	CXTPReportControlEx();
	virtual ~CXTPReportControlEx();

	void SetParentDlg(LPVOID pDlg);

	LPVOID m_ParentDlg;
protected:
	//{{AFX_MSG(CTabTreeFile)
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint pos);
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_XTPREPORTCONTROLEX_H__239D59CE_2B79_468E_A66B_E67030B3F4EA__INCLUDED_)
