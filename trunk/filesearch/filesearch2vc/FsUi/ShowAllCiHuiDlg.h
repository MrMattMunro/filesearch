#if !defined(AFX_SHOWALLCIHUIDLG_H__8392E4AC_E59F_4204_A43E_67808E71F005__INCLUDED_)
#define AFX_SHOWALLCIHUIDLG_H__8392E4AC_E59F_4204_A43E_67808E71F005__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ShowAllCiHuiDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CShowAllCiHuiDlg dialog

class CShowAllCiHuiDlg : public CDialog
{
// Construction
public:
	CShowAllCiHuiDlg(CWnd* pParent = NULL);   // standard constructor
	
	int ReadAllCiHui();
// Dialog Data
	//{{AFX_DATA(CShowAllCiHuiDlg)
	enum { IDD = IDD_DIALOG_ALL_CIHUI };
	CListBox	m_AllCiHuiListBox;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShowAllCiHuiDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CShowAllCiHuiDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWALLCIHUIDLG_H__8392E4AC_E59F_4204_A43E_67808E71F005__INCLUDED_)
