#if !defined(AFX_SETATTRIBUTEDLG_H__17731C02_DE58_4BCD_8087_203E703663A0__INCLUDED_)
#define AFX_SETATTRIBUTEDLG_H__17731C02_DE58_4BCD_8087_203E703663A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetAttributeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetAttributeDlg dialog
#include "sloSetAttrAgent.h"

class CSetAttributeDlg : public  CXTPPropertyPage/*CDialog*/
{
// Construction
public:
	CSetAttributeDlg(CWnd* pParent = NULL);   // standard constructor
	void OKEvent();

	sloSetAttrAgent m_setAgent;
// Dialog Data
	//{{AFX_DATA(CSetAttributeDlg)
	enum { IDD = IDD_DIALOG_SET_ATTR };
	CString	m_strExcel;
	CString	m_strIE;
	CString	m_strPdf;
	CString	m_strPPT;
	CString	m_strTxt;
	CString	m_strWord;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetAttributeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	virtual BOOL OnApply();
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();

// Implementation
protected:
	CXTPButton m_btnFolderIE;
	CXTPButton m_btnFolderWord;
	CXTPButton m_btnFolderExcel;
	CXTPButton m_btnFolderPPT;
	CXTPButton m_btnFolderPdf;
	CXTPButton m_btnFolderTxt;

	CString	m_strOldExcel;
	CString	m_strOldIE;
	CString	m_strOldPdf;
	CString	m_strOldPPT;
	CString	m_strOldTxt;
	CString	m_strOldWord;
	// Generated message map functions
	//{{AFX_MSG(CSetAttributeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonBrowserIe();
	afx_msg void OnButtonBrowserWord();
	afx_msg void OnButtonBrowserExcel();
	afx_msg void OnButtonBrowserPpt();
	afx_msg void OnButtonBrowserPdf();
	afx_msg void OnButtonBrowserTxt();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETATTRIBUTEDLG_H__17731C02_DE58_4BCD_8087_203E703663A0__INCLUDED_)
