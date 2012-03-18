// SLabelAddin.cpp : Implementation of CSLabelAddin
#include "stdafx.h"
#include "SLabelPPTAddin.h"
#include "SLabelAddin.h"

_ATL_FUNC_INFO OnClickButtonInfo = { CC_STDCALL, VT_EMPTY, 2, { VT_DISPATCH, VT_BYREF|VT_BOOL } };

CComQIPtr<_Application> g_Application;
/////////////////////////////////////////////////////////////////////////////
// CSLabelAddin

HRESULT CSLabelAddin::OnConnection(IDispatch *Application, ext_ConnectMode ConnectMode,
								   IDispatch *AddInInst, SAFEARRAY **custom)
{
	UNREFERENCED_PARAMETER(ConnectMode);
	UNREFERENCED_PARAMETER(AddInInst);
	UNREFERENCED_PARAMETER(custom);
	
	m_Application = Application;
	g_Application = Application;
	ATLASSERT(m_Application);
	AppEvents4::DispEventAdvise((IDispatch *)m_Application);

	CComPtr<_CommandBars> spCmdBars;
	m_Application->get_CommandBars(&spCmdBars);
	ATLASSERT(spCmdBars);

	// 添加一个工具条
	CComVariant vName("信息检索");
	CComPtr<CommandBar> spNewCmdBar;
	CComVariant vPos(1);
	CComVariant vTemp(VARIANT_TRUE);
	CComVariant vEmpty(DISP_E_PARAMNOTFOUND, VT_ERROR);
	spNewCmdBar = spCmdBars->Add(vName, vPos, vEmpty, vTemp);

	// 获取所添加工具条的CommandBarControls
	CComPtr<CommandBarControls> spBarControls;
	spNewCmdBar->get_Controls(&spBarControls);
	ATLASSERT(spBarControls);

	// 添加按钮
	m_spCmdButtonSet = AddCmdButton(spBarControls, IDB_SET, L"", L"添加文件到检索");

	// 显示工具条
	spNewCmdBar->PutVisible(VARIANT_TRUE);

	if (m_spCmdButtonSet)
	{
		CommandButtonEvents_Set::DispEventAdvise((IDispatch *)m_spCmdButtonSet);
	}

	return S_OK;
}

HRESULT CSLabelAddin::OnDisconnection(ext_DisconnectMode RemoveMode, SAFEARRAY **custom)
{
	UNREFERENCED_PARAMETER(custom);

	if (m_Application)
	{
		AppEvents4::DispEventUnadvise((IDispatch *)m_Application);
	}

	if (m_spCmdButtonSet)
	{
		CommandButtonEvents_Set::DispEventUnadvise((IDispatch *)m_spCmdButtonSet);
	}

	return S_OK;
}

HRESULT CSLabelAddin::raw_GetCustomUI(BSTR RibbonID, BSTR * RibbonXml)
{
	OutputDebugStringW(L"[addin] raw_GetCustomUI\r\n");
	
	wchar_t szRibbon[MAX_PATH*10] = { 0 };
	LoadString(_Module.GetModuleInstance(), IDS_RIBBON_XML,
		szRibbon, sizeof(szRibbon)/sizeof(wchar_t));
	if (RibbonXml == NULL)
	{
		return E_POINTER;
	}
	
	OutputDebugStringW(szRibbon);
	*RibbonXml = CComBSTR(szRibbon);
	return S_OK;
}

void __stdcall CSLabelAddin::OnClickButtonSet(IDispatch *Ctrl,
											  VARIANT_BOOL *CancelDefault)
{
	OutputDebugStringW(L"[addin] OnClickButtonSet\r\n");
	CComPtr<_Presentation> pPresent = NULL;
	m_Application->get_ActivePresentation(&pPresent);
	if (pPresent == NULL)
	{
		return;
	}

	//获取文件名
	CComBSTR filename;
	pPresent->get_FullName(&filename);

	char szFilePath[MAX_PATH] = {0};
	WideCharToMultiByte(CP_ACP, 0, filename, -1, szFilePath, MAX_PATH, NULL, NULL);
	m_addinAgent.FsShowSavefileDlg(szFilePath); 
	
	//将该文件地址写入dat文件，并向T_DOCUMENT加入一条记录

}

STDMETHODIMP CSLabelAddin::OnCut(IDispatch *Ctrl, VARIANT *CancelDefault)
{

	return S_OK;
}


STDMETHODIMP CSLabelAddin::OnCopy(IDispatch *Ctrl, VARIANT *CancelDefault)
{
	OutputDebugStringW(L"[addin] OnClickButtonCut\r\n");


	return S_OK;
}

STDMETHODIMP CSLabelAddin::OnPaste(IDispatch *Ctrl, VARIANT *CancelDefault)
{
	(*CancelDefault).boolVal = VARIANT_FALSE;

	
	return S_OK;
}

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
