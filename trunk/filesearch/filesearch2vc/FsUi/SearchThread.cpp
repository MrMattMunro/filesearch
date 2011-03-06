// SearchThread.cpp : implementation file
//

#include "stdafx.h"
#include "FsUi.h"
#include "SearchThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSearchThread

IMPLEMENT_DYNCREATE(CSearchThread, CWinThread)

CSearchThread::CSearchThread()
{
}

CSearchThread::~CSearchThread()
{
}

BOOL CSearchThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CSearchThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CSearchThread, CWinThread)
	//{{AFX_MSG_MAP(CSearchThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_THREAD_MESSAGE(WM_SEARCH_MSG, OnSearch)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSearchThread message handlers

void CSearchThread::OnSearch(WPARAM wParam, LPARAM lParam)
{
	//等待keyWord.properties文件不存在时,从T_Result中取出数据,显示在界面上
	Sleep(100);

	OutputDebugString("OnSearch begin");
	while(1)
	{
		if (!m_agent.IsKeyFileExist())
		{
			break;
		}
		Sleep(100);
	}

	OutputDebugString("OnSearch end");

	int nPostCount = 0;
	while(nPostCount < 10)
	{
		OutputDebugString("post WM_PROGRESS_MSG ");
		if(PostMessage(m_hParentWnd, WM_PROGRESS_MSG, 0, 0))
		{
			OutputDebugString("PostThreadMessage  WM_PROGRESS_MSG succ");
			break ;
		}else
		{	
			OutputDebugString("PostThreadMessage WM_PROGRESS_MSG failed");
			nPostCount++;
		}
	}
}
