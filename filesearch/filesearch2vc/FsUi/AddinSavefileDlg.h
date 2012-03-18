#if !defined(AFX_ADDINSAVEFILEDLG_H__2F35E6A3_9529_4159_8A55_AB350A8365CB__INCLUDED_)
#define AFX_ADDINSAVEFILEDLG_H__2F35E6A3_9529_4159_8A55_AB350A8365CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddinSavefileDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddinSavefileDlg dialog

class CAddinSavefileDlg : public CDialog
{
// Construction
public:
	CAddinSavefileDlg(CWnd* pParent = NULL);   // standard constructor

	void SetDcoumentPath(char* szFilePath);
	CImageList m_ilTreeIcons;
// Dialog Data
	//{{AFX_DATA(CAddinSavefileDlg)
	enum { IDD = IDD_DIALOG_SAVE_FILE };
	CXTTreeCtrl	m_treeGroup;
	CString	m_strDocpath;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddinSavefileDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddinSavefileDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDINSAVEFILEDLG_H__2F35E6A3_9529_4159_8A55_AB350A8365CB__INCLUDED_)
