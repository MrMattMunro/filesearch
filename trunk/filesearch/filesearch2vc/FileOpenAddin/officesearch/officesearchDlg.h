// officesearchDlg.h : header file
//

#if !defined(AFX_OFFICESEARCHDLG_H__1D28B6A4_3BB4_4D7F_AA9D_E6223C6C78EF__INCLUDED_)
#define AFX_OFFICESEARCHDLG_H__1D28B6A4_3BB4_4D7F_AA9D_E6223C6C78EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "sloFileOpenAddin.h"
/////////////////////////////////////////////////////////////////////////////
// COfficesearchDlg dialog

class COfficesearchDlg : public CDialog
{
// Construction
public:
	COfficesearchDlg(CWnd* pParent = NULL);	// standard constructor

	sloFileOpenAddin fileaddin;
// Dialog Data
	//{{AFX_DATA(COfficesearchDlg)
	enum { IDD = IDD_OFFICESEARCH_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COfficesearchDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(COfficesearchDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OFFICESEARCHDLG_H__1D28B6A4_3BB4_4D7F_AA9D_E6223C6C78EF__INCLUDED_)
