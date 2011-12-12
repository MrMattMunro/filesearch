#if !defined(AFX_CYBERDLG_H__8B84C28E_1173_40C6_B48E_093286E3F108__INCLUDED_)
#define AFX_CYBERDLG_H__8B84C28E_1173_40C6_B48E_093286E3F108__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CyberDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCyberDlg dialog
#include "XTPReportControlEx.h"
#include "SelectTreeCtrl.h"
#include "StateTreeCtrl.h"

class CCyberDlg : public CDialog
{
// Construction
public:
	CCyberDlg(CWnd* pParent = NULL);   // standard constructor
	void SetTreeFocus(CXTTreeCtrl* pTreeFocus);

	void SetKeywords(CString strKeywords);
	void SetWebsite(CString strWebsite);

	CXTTreeCtrl* m_pTreeFocus;

	CString m_strKeywords;
	CString m_strWebsite;

// Dialog Data
	//{{AFX_DATA(CCyberDlg)
	enum { IDD = IDD_DIALOG_CYBER };
	CStateTreeCtrl	m_treeWebsite;
	CStateTreeCtrl	m_treeKeywords;
	CEdit	m_editLayer;
	CEdit	m_editFrequency;
	CSpinButtonCtrl	m_pinLayer;
	CSpinButtonCtrl	m_pinFrenquency;
	CString	m_cyberName;
	CString	m_strLayerName;
	CString	m_strFrequencyName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCyberDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCyberDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CYBERDLG_H__8B84C28E_1173_40C6_B48E_093286E3F108__INCLUDED_)
