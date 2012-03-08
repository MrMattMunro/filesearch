#if !defined(AFX_FILENAMEEDIT_H__E5446CA6_256D_43A5_BF13_CC20D8052EBE__INCLUDED_)
#define AFX_FILENAMEEDIT_H__E5446CA6_256D_43A5_BF13_CC20D8052EBE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FilenameEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFilenameEdit window

class CFilenameEdit : public CEdit
{
// Construction
public:
	CFilenameEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFilenameEdit)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFilenameEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CFilenameEdit)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

public:
    void    SetFilename(const CString & strFilename);
    CString GetFilename() { return m_strFilename; };

private:
    CString GetDisplayName();
    bool CreateTooltipControl();

    CToolTipCtrl * m_pTooltipCtrl;
    CString m_strFilename;
};

void AFXAPI DDX_Filename(CDataExchange* pDX, int nIDC, CString& value);


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILENAMEEDIT_H__E5446CA6_256D_43A5_BF13_CC20D8052EBE__INCLUDED_)
