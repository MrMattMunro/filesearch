#if !defined(AFX_LICENSEDLG_H__06C2F9F0_8180_405E_9D42_C9BF8306CC32__INCLUDED_)
#define AFX_LICENSEDLG_H__06C2F9F0_8180_405E_9D42_C9BF8306CC32__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LicenseDlg.h : header file
//
#include "sloLicenseAgent.h"


/////////////////////////////////////////////////////////////////////////////
// CLicenseDlg dialog
class CLicenseDlg :public  CXTPPropertyPage/*CDialog*/
{
// Construction
public:
	CLicenseDlg(CWnd* pParent = NULL);   // standard constructor
	
	BOOL UpdateDialog();
	sloLicenseAgent m_licAgent;
// Dialog Data
	//{{AFX_DATA(CLicenseDlg)
	enum { IDD = IDD_DIALOG_LICENSE };
	CXTPButton	m_btnBack;
	CXTPButton	m_btnRestore;
	CXTPButton	m_btnFolderRestore;
	CXTPButton	m_btnFolderBack;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLicenseDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CXTPButton m_btnReg;
	// Generated message map functions
	//{{AFX_MSG(CLicenseDlg)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonReg();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnButtonLicenseBack();
	afx_msg void OnButtonBrowseBackPath();
	afx_msg void OnButtonBrowseRestorePath();
	afx_msg void OnButtonLicenseRestore();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LICENSEDLG_H__06C2F9F0_8180_405E_9D42_C9BF8306CC32__INCLUDED_)
