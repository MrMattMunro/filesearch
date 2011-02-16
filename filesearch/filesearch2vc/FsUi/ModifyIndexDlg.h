#if !defined(AFX_MODIFYINDEXDLG_H__39AE23D7_E39C_4B44_9B32_8058EB2CB661__INCLUDED_)
#define AFX_MODIFYINDEXDLG_H__39AE23D7_E39C_4B44_9B32_8058EB2CB661__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ModifyIndexDlg.h : header file
//
#include "sloModifyIndexAgent.h"
/////////////////////////////////////////////////////////////////////////////
// CModifyIndexDlg dialog

class CModifyIndexDlg : public CDialog
{
// Construction
public:
	CModifyIndexDlg(CWnd* pParent = NULL);   // standard constructor

	void SetIndexID(int id);
	void SetType(char *szType);

	int m_nIndexID;
	sloModifyIndexAgent m_modifyAgent;

// Dialog Data
	//{{AFX_DATA(CModifyIndexDlg)
	enum { IDD = IDD_DIALOG_MODIFY_INDEX };
	BOOL	m_bWord;
	BOOL	m_bPpt;
	BOOL	m_bPdf;
	BOOL	m_bHtml;
	BOOL	m_bExcel;
	BOOL	m_bChm;
	BOOL	m_bTxt;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModifyIndexDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CModifyIndexDlg)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnButtonDelIndex();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODIFYINDEXDLG_H__39AE23D7_E39C_4B44_9B32_8058EB2CB661__INCLUDED_)
