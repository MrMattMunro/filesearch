// DirMonitorTestDlg.h : header file
//

#if !defined(AFX_DIRMONITORTESTDLG_H__31197EE2_6577_44D4_A785_B5B154553B7B__INCLUDED_)
#define AFX_DIRMONITORTESTDLG_H__31197EE2_6577_44D4_A785_B5B154553B7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDirMonitorTestDlg dialog

class CDirMonitorTestDlg : public CDialog
{
// Construction
public:
	CDirMonitorTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDirMonitorTestDlg)
	enum { IDD = IDD_DIRMONITORTEST_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDirMonitorTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDirMonitorTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnClose();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIRMONITORTESTDLG_H__31197EE2_6577_44D4_A785_B5B154553B7B__INCLUDED_)
