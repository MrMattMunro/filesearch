#if !defined(AFX_ADDINSAVEFILEDLG_H__646A2ED5_0E4F_42E4_9E1B_DD659FDD10DD__INCLUDED_)
#define AFX_ADDINSAVEFILEDLG_H__646A2ED5_0E4F_42E4_9E1B_DD659FDD10DD__INCLUDED_

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
	void BrowseFile(int CallNum,CString strFile);
	CImageList m_ilTreeIcons;
	HTREEITEM strRoot;
	HTREEITEM strHTFir;
	HTREEITEM strHTSec;
	HTREEITEM strHtThi;
	HTREEITEM strHtFor;
	HTREEITEM strHtFif;
	HTREEITEM strHtEnd;
// Dialog Data
	//{{AFX_DATA(CAddinSavefileDlg)
	enum { IDD = IDD_DIALOG_SAVE_FILE };
	CTreeCtrl	m_treeGroup;
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
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDINSAVEFILEDLG_H__646A2ED5_0E4F_42E4_9E1B_DD659FDD10DD__INCLUDED_)
