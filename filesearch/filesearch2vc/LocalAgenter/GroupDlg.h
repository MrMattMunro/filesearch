#if !defined(AFX_GROUPDLG_H__E988F885_787D_4D50_AD15_3B5CFF419C34__INCLUDED_)
#define AFX_GROUPDLG_H__E988F885_787D_4D50_AD15_3B5CFF419C34__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GroupDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGroupDlg dialog

class CGroupDlg : public CDialog
{
// Construction
public:
	CGroupDlg(CWnd* pParent = NULL);   // standard constructor

	void SetDefaultValue(char* pszName);
	
	char m_szGroupName[MAX_PATH];
// Dialog Data
	//{{AFX_DATA(CGroupDlg)
	enum { IDD = IDD_DIALOG_GROUP };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGroupDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGroupDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GROUPDLG_H__E988F885_787D_4D50_AD15_3B5CFF419C34__INCLUDED_)
