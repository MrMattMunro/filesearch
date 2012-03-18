// fsAddinDlgAgent.h: interface for the fsAddinDlgAgent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FSADDINDLGAGENT_H__C8541B8C_CCC7_404E_B7D8_B2547CC1D96D__INCLUDED_)
#define AFX_FSADDINDLGAGENT_H__C8541B8C_CCC7_404E_B7D8_B2547CC1D96D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
typedef DWORD (__stdcall *fnFsShowSavefileDlg)(char* pszFileName);
class fsAddinDlgAgent  
{
public:
	fsAddinDlgAgent();
	virtual ~fsAddinDlgAgent();

public:
	BOOL Init();
	BOOL Uninit();

	BOOL FsShowSavefileDlg(char* szFilePath);

public:
	BOOL m_bInit;
	HINSTANCE m_hinstance;
	fnFsShowSavefileDlg m_fnFsShowSavefileDlg;
};

#endif // !defined(AFX_FSADDINDLGAGENT_H__C8541B8C_CCC7_404E_B7D8_B2547CC1D96D__INCLUDED_)
