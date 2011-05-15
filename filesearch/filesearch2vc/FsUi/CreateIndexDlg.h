#if !defined(AFX_CREATEINDEXDLG_H__15633A26_DA34_48CC_988B_C8DB0D4241EA__INCLUDED_)
#define AFX_CREATEINDEXDLG_H__15633A26_DA34_48CC_988B_C8DB0D4241EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CreateIndexDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCreateIndexDlg dialog

class CCreateIndexDlg : public CDialog
{
// Construction
public:
	CCreateIndexDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCreateIndexDlg)
	enum { IDD = IDD_DIALOG_CREATE_INDEX };
	BOOL	m_bExcel;
	BOOL	m_bHtml;
	BOOL	m_bPdf;
	BOOL	m_bTxt;
	BOOL	m_bPpt;
	BOOL	m_bWord;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCreateIndexDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCreateIndexDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnButtonBrowse();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CREATEINDEXDLG_H__15633A26_DA34_48CC_988B_C8DB0D4241EA__INCLUDED_)
