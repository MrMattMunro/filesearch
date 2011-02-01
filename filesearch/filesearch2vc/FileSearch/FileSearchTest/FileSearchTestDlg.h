// FileSearchTestDlg.h : header file
//

#if !defined(AFX_FILESEARCHTESTDLG_H__2CA3F050_AC02_44F2_80DB_AB697E0CE779__INCLUDED_)
#define AFX_FILESEARCHTESTDLG_H__2CA3F050_AC02_44F2_80DB_AB697E0CE779__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFileSearchTestDlg dialog

class CFileSearchTestDlg : public CDialog
{
// Construction
public:
	CFileSearchTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CFileSearchTestDlg)
	enum { IDD = IDD_FILESEARCHTEST_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileSearchTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFileSearchTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILESEARCHTESTDLG_H__2CA3F050_AC02_44F2_80DB_AB697E0CE779__INCLUDED_)
