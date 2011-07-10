// sl4jTestDlg.h : header file
//

#if !defined(AFX_SL4JTESTDLG_H__18F42C51_795C_460F_B9D4_6A627474D175__INCLUDED_)
#define AFX_SL4JTESTDLG_H__18F42C51_795C_460F_B9D4_6A627474D175__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSl4jTestDlg dialog

class CSl4jTestDlg : public CDialog
{
// Construction
public:
	CSl4jTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSl4jTestDlg)
	enum { IDD = IDD_SL4JTEST_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSl4jTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSl4jTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SL4JTESTDLG_H__18F42C51_795C_460F_B9D4_6A627474D175__INCLUDED_)
