#if !defined(AFX_SKINDLG_H__0F6A32A1_3F4F_4ABA_99C6_E2AC386E895B__INCLUDED_)
#define AFX_SKINDLG_H__0F6A32A1_3F4F_4ABA_99C6_E2AC386E895B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SkinDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSkinDlg dialog

class CSkinDlg : public  CXTPPropertyPage/*CDialog*/
{
// Construction
public:
	CSkinDlg(CWnd* pParent = NULL);   // standard constructor

	char m_szSkinTheme[MAX_PATH];
// Dialog Data
	//{{AFX_DATA(CSkinDlg)
	enum { IDD = IDD_DIALOG_SKIN };
	CListBox	m_skinbox;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	virtual BOOL OnApply();
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSkinDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeListSkin();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKINDLG_H__0F6A32A1_3F4F_4ABA_99C6_E2AC386E895B__INCLUDED_)
