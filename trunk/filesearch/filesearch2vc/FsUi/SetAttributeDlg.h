#if !defined(AFX_SETATTRIBUTEDLG_H__17731C02_DE58_4BCD_8087_203E703663A0__INCLUDED_)
#define AFX_SETATTRIBUTEDLG_H__17731C02_DE58_4BCD_8087_203E703663A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetAttributeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetAttributeDlg dialog

class CSetAttributeDlg : public CDialog
{
// Construction
public:
	CSetAttributeDlg(CWnd* pParent = NULL);   // standard constructor

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

// Implementation
protected:

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
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETATTRIBUTEDLG_H__17731C02_DE58_4BCD_8087_203E703663A0__INCLUDED_)
