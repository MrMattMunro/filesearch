// sloOpenFileAgent.h: interface for the sloOpenFileAgent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLOOPENFILEAGENT_H__4021CF12_4249_4D76_BC04_898E3D41B620__INCLUDED_)
#define AFX_SLOOPENFILEAGENT_H__4021CF12_4249_4D76_BC04_898E3D41B620__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
typedef DWORD (__stdcall *fnopenWordFile)(char* pFileName, int nPage, char* pKeyWords/* = NULL*/);
typedef DWORD (__stdcall *fnopenExcelFile)(char* pFileName, char* pSheet, int nRow, char* pKeyWords/* = NULL*/);
typedef DWORD (__stdcall *fnopenPPTFile)(char* pFileName, int nPage, char* pKeyWords/* = NULL*/);
typedef DWORD (__stdcall *fnopenTxtFile)(char* pFileName, int nRow, char* pKeyWords/* = NULL*/);
typedef DWORD (__stdcall *fnopenPdfFile)(char* pPdfSoftPath,char* pFileName, int nPage, char* pKeyWords/* = NULL*/);
class sloOpenFileAgent  
{
public:
	sloOpenFileAgent();
	virtual ~sloOpenFileAgent();

	BOOL Init();

public:
	BOOL m_bInit;
	HINSTANCE m_hinstance;
	fnopenWordFile m_fnopenWordFile;
	fnopenExcelFile m_fnopenExcelFile;
	fnopenPPTFile m_fnopenPPTFile;
	fnopenPdfFile m_fnopenPdfFile;
	fnopenTxtFile m_fnopenTxtFile;
};

#endif // !defined(AFX_SLOOPENFILEAGENT_H__4021CF12_4249_4D76_BC04_898E3D41B620__INCLUDED_)
