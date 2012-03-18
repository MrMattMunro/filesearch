// SLabelAddin.cpp : Implementation of CSLabelAddin
#include "stdafx.h"
#include "SLabelWordAddin.h"
#include "SLabelAddin.h"

#include <atlconv.h>

#pragma comment(lib, "shlwapi.lib")

#include "Mmsystem.h"
#pragma comment(lib, "Winmm.lib")

_ATL_FUNC_INFO OnClickButtonInfo = { CC_STDCALL, VT_EMPTY, 2, { VT_DISPATCH, VT_BYREF|VT_BOOL } };

CComQIPtr<Word::_Application> g_Application;
extern HINSTANCE g_hinstance;

CComQIPtr<_CommandBarButton> CSLabelAddin::AddCmdButton(CComPtr<CommandBarControls> spBarControls, UINT uBitmapID,BSTR strCaption, BSTR strTag)
{
	// 添加按钮
	CComVariant vToolBarType(1);
	CComVariant vShow(VARIANT_TRUE);
	CComVariant vEmpty(DISP_E_PARAMNOTFOUND, VT_ERROR);
	CComPtr<CommandBarControl> spNewBar;

	// 添加按钮
	spNewBar = spBarControls->Add(vToolBarType, vEmpty, vEmpty, vEmpty, vShow);
	ATLASSERT(spNewBar);

	CComQIPtr<_CommandBarButton> spCmdButton(spNewBar);
	ATLASSERT(spCmdButton);
	HBITMAP hBmp = (HBITMAP)::LoadImage(_Module.GetResourceInstance(),
		MAKEINTRESOURCE(uBitmapID), IMAGE_BITMAP, 0, 0, LR_LOADMAP3DCOLORS);

    // add zhw  
	// 为COMMANDBARBUTTON插入背景透明的图片
	m_BitmapHelper.ModifyTransBitmap(hBmp);
	m_BitmapHelper.PutPicture(spCmdButton, hBmp);
	::DeleteObject(hBmp);

	spCmdButton->PutStyle(Office::msoButtonIconAndCaption);
	spCmdButton->PutVisible(VARIANT_TRUE);
	spCmdButton->PutCaption(strCaption);
	spCmdButton->PutEnabled(VARIANT_TRUE);
	spCmdButton->PutTooltipText(strTag);
	return spCmdButton;
}


LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

BOOL InitApplication(HINSTANCE hinstance) 
{ 
    WNDCLASSEX wcx; 
	
    // Fill in the window class structure with parameters 
    // that describe the main window. 
	
    wcx.cbSize = sizeof(wcx);          // size of structure 
    wcx.style = CS_HREDRAW | 
        CS_VREDRAW;                    // redraw if size changes 
    wcx.lpfnWndProc = MainWndProc;     // points to window procedure 
    wcx.cbClsExtra = 0;                // no extra class memory 
    wcx.cbWndExtra = 0;                // no extra window memory 
    wcx.hInstance = hinstance;         // handle to instance 
    wcx.hIcon = 0;              // predefined app. icon 
    wcx.hCursor = 0;                    // predefined arrow 
    wcx.hbrBackground = 0;                  // white background brush 
    wcx.lpszMenuName =  0;    // name of menu resource 
    wcx.lpszClassName = L"wordaddin";  // name of window class 
    wcx.hIconSm = 0; 
	
    // Register the window class. 
	
    return RegisterClassEx(&wcx); 
} 

HWND InitInstance(HINSTANCE hinstance) 
{ 
    // Create the main window. 	
    return CreateWindow( 
        L"wordaddin",        // name of window class 
        L"Sample",            // title-bar string 
        WS_POPUP | WS_CHILD, // top-level window 
        2,       // default horizontal position 
        2,       // default vertical position 
        2,       // default width 
        2,       // default height 
        (HWND)::FindWindowW(L"OpusApp", NULL),         // no owner window 
        (HMENU) NULL,        // use class menu 
        hinstance,           // handle to application instance 
        (LPVOID) NULL);      // no window-creation data 
}

void ExitInstance(HWND hwnd) 
{ 
    // Create the main window.
	if (hwnd)
	{
		SendMessage(hwnd,WM_QUIT, NULL, NULL);	
	}
}


/////////////////////////////////////////////////////////////////////////////
// CSLabelAddin
HRESULT CSLabelAddin::OnConnection(IDispatch *Application, ext_ConnectMode ConnectMode,
								   IDispatch *AddInInst, SAFEARRAY **custom)
{

	CComPtr<_CommandBars> spCmdBars;
	CComQIPtr<_Application> spApp(Application);
	ATLASSERT(spApp);
	m_Application = Application;
	g_Application = Application;

	AppEvents::DispEventAdvise((IDispatch*)m_Application, &__uuidof(Word::ApplicationEvents4));	

	CComQIPtr<COMAddIn> comAddin(AddInInst);
	comAddin->Object = (IDispatch*)(ISLabelAddin*)const_cast<CSLabelAddin*>(this);

	HRESULT hr = spApp->get_CommandBars(&spCmdBars);
	if(FAILED(hr))
		return hr;
	ATLASSERT(spCmdBars);

	// 添加一个工具条
	CComVariant vName("信息检索");
	CComPtr<CommandBar> spNewCmdBar;
	CComVariant vPos(1);
	CComVariant vTemp(VARIANT_TRUE);
	CComVariant vEmpty(DISP_E_PARAMNOTFOUND, VT_ERROR);
	spNewCmdBar = spCmdBars->Add(vName, vPos, vEmpty, vTemp);

	//
	CComPtr<CommandBarControls> spBarControls;
	spBarControls = spNewCmdBar->GetControls();
	ATLASSERT(spBarControls);

	m_spCmdButtonSet = AddCmdButton(spBarControls, IDB_BITMAP6, L"", L"添加文件到检索");

	// 显示工具条
	spNewCmdBar->PutVisible(VARIANT_TRUE);

	if (m_spCmdButtonSet)
		CommandButtonEvents_Set::DispEventAdvise((IDispatch*)m_spCmdButtonSet);

	return S_OK;
}

HRESULT CSLabelAddin::OnDisconnection(ext_DisconnectMode RemoveMode, SAFEARRAY **custom)
{
	if (m_spCmdButtonSet)
		CommandButtonEvents_Set::DispEventUnadvise((IDispatch*)m_spCmdButtonSet);

	AppEvents::DispEventUnadvise((IDispatch *)m_Application);

	m_addinAgent.Uninit();

	return S_OK;
}


void __stdcall CSLabelAddin::OnClickButtonSet(IDispatch *Ctrl,
		VARIANT_BOOL *CancelDefault)
{
	CComPtr<_Document> document;
	m_Application->get_ActiveDocument(&document);
	ATLASSERT(document);
	
	//获取文件名
	CComBSTR filename;
	document->get_FullName(&filename);
	
	char szFilePath[MAX_PATH] = {0};
	WideCharToMultiByte(CP_ACP, 0, filename, -1, szFilePath, MAX_PATH, NULL, NULL);
	//如果文件没有存盘，则提示“该文件未保存，请保存后在进行此操作”
	if (strstr(szFilePath, ":\\") == NULL)
	{
		MessageBoxA(NULL,"该文件未保存，请保存后在进行此操作!", "提示",MB_OK | MB_ICONWARNING);
		return ;
	}

	m_addinAgent.FsShowSavefileDlg(szFilePath); //调用之后，关闭出错，可能与sp3补丁有关，需要安装sp3补丁验证

	//将该文件地址写入dat文件，并向T_DOCUMENT加入一条记录
	
}

 
STDMETHODIMP CSLabelAddin::SaveFile()
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CSLabelAddin::OpenFile()
{
	// TODO: Add your implementation code here

	return S_OK;
}