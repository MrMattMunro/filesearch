#if !defined(AFX_SKINDLG_H__0F6A32A1_3F4F_4ABA_99C6_E2AC386E895B__INCLUDED_)
#define AFX_SKINDLG_H__0F6A32A1_3F4F_4ABA_99C6_E2AC386E895B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SkinDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSkinDlg dialog
#include "EnBitmap.h"
class CSkinDlg : public  CXTPPropertyPage/*CDialog*/
{
// Construction
public:
	CSkinDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSkinDlg)
	enum { IDD = IDD_DIALOG_SKIN };
	CListBox	m_skinbox;

	BOOL	m_bGrayscale;
	BOOL	m_bRotate;
	BOOL	m_bShearDown;
	BOOL	m_bShearAcross;
	BOOL	m_bBlur;
	BOOL	m_bShrink;
	BOOL	m_bEnlarge;
	BOOL	m_bFlipHorz;
	BOOL	m_bFlipVert;
	BOOL	m_bNegate;
	BOOL	m_bReplaceBlack;
	BOOL	m_bWeighting;
	CString	m_sTimeTaken;
	BOOL	m_bUseProcessorArray;
	BOOL	m_bSharpen;
	int		m_nBlurFactor;
	int		m_nSharpenFactor;
	int		m_nShrinkFactor;
	int		m_nEnlargeFactor;
	int		m_nRotationAngle;
	int		m_nYShearAmount;
	int		m_nXShearAmount;
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
	CEnBitmap m_bitmap, m_bitmapOrg;
	CSize m_sizePrev;

	void OnChangeProcessing() ;
	char m_szSkinTheme[MAX_PATH];
	// Generated message map functions
	//{{AFX_MSG(CSkinDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeListSkin();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKINDLG_H__0F6A32A1_3F4F_4ABA_99C6_E2AC386E895B__INCLUDED_)
