// FilenameEdit.cpp : implementation file
//

#include "stdafx.h"
#include "FilenameEdit.h"

#if !defined (PathCompactPath)
#pragma message("Include shlwapi.h and insert shlwapi.lib into project!")
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define BUFFER_EXTRA    _MAX_PATH

CFilenameEdit::CFilenameEdit()
{
    m_pTooltipCtrl = NULL;
}

CFilenameEdit::~CFilenameEdit()
{
    delete m_pTooltipCtrl;
}


BEGIN_MESSAGE_MAP(CFilenameEdit, CEdit)
	//{{AFX_MSG_MAP(CFilenameEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFilenameEdit message handlers

void CFilenameEdit::PreSubclassWindow() 
{
    // Set the control to read only, in case this style has not been set in the resources
//    SetReadOnly();

	CEdit::PreSubclassWindow();
}

BOOL CFilenameEdit::PreTranslateMessage(MSG* pMsg) 
{
    // If we have a tooltip, we need to relay the message to it
    if (m_pTooltipCtrl)
        m_pTooltipCtrl->RelayEvent(pMsg);
	
	return CEdit::PreTranslateMessage(pMsg);
}

void CFilenameEdit::SetFilename(const CString & strFilename)
{
    // Keep track of the full filename
//    m_strFilename = strFilename;

    // Create the tooltip control if we haven't already
    CreateTooltipControl();

    // If we have the tooltip, update the text to the full filename
    if (m_pTooltipCtrl)
        m_pTooltipCtrl->UpdateTipText(strFilename, this);

    // Work out the name that we can display, and display it
    SetWindowText(GetDisplayName());
}

CString CFilenameEdit::GetDisplayName()
{
    // Get the DC for the control, and the rectangle into which we draw text
    CDC * pDC = GetDC();
    CRect rectClient;
    GetRect(&rectClient);

    // Select the correct font into the DC
    CFont * pFontOld = pDC->SelectObject(GetFont());

    // Get the display name, and truncate it to fit into the control
    // Note that we make the buffer larger than max path in case we have some bizarre
    // situation where a load of ellipsis are inserted and it overruns the buffer
    CString strDisplayName = m_strFilename;
    PathCompactPath(pDC->GetSafeHdc(), strDisplayName.GetBuffer(_MAX_PATH + 1 + BUFFER_EXTRA), rectClient.Width());
    strDisplayName.ReleaseBuffer();

    // Clean up!
    pDC->SelectObject(pFontOld);
    ReleaseDC(pDC);

    return strDisplayName;
}

bool CFilenameEdit::CreateTooltipControl()
{
    bool bCreated = false;

    // If we already have a control just return now
    if (m_pTooltipCtrl) return true;

    m_pTooltipCtrl = new CToolTipCtrl;

    // Create the tool tip control and add ourselves as a tool
    if (m_pTooltipCtrl->Create(this, TTS_ALWAYSTIP))
    {
        if (m_pTooltipCtrl->AddTool(this, ""))
        {
            m_pTooltipCtrl->Activate(TRUE);
            bCreated = true;
        }
    }

    if (!bCreated)
    {
        // Something went amiss - clean up
        delete m_pTooltipCtrl;
        m_pTooltipCtrl = NULL;
    }

    return bCreated;
}

void AFXAPI DDX_Filename(CDataExchange* pDX, int nIDC, CString& value)
{
    // Start by preparing the edit control
	HWND hWndCtrl = pDX->PrepareEditCtrl(nIDC);

    CFilenameEdit editTemp;
    CFilenameEdit * pEdit;

    // See if the control has been subclassed
    CWnd * pWndMapped = CWnd::FromHandlePermanent(hWndCtrl);

    if (pWndMapped)
    {
        // Control has been subclassed - use the window returned from the permanent map
        pEdit = (CFilenameEdit *)pWndMapped;
    }
    else
    {
        // Control has not been subclassed, so attach to a temporary CFilenameEdit
        editTemp.Attach(hWndCtrl);
        pEdit = &editTemp;
    }

	if (pDX->m_bSaveAndValidate)
	{
        // We are saving the text, so get the filename from the control
        value = pEdit->GetFilename();
	}
	else
	{
        // We are loading text, so place the filename into the control
        pEdit->SetFilename(value);
	}

    if (pWndMapped == NULL)
    {
        // We attached to the temporary object, so detach again
        editTemp.Detach();
    }
}
