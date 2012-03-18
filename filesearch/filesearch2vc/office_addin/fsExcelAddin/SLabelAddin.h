// SLabelAddin.h : Declaration of the CSLabelAddin

#ifndef __SLABELADDIN_H_
#define __SLABELADDIN_H_

#include "resource.h"       // main symbols
#include "StdAfx.h"
#include "BitmapHelper.h"

extern _ATL_FUNC_INFO OnClickButtonInfo;

/////////////////////////////////////////////////////////////////////////////
// CSLabelAddin
class ATL_NO_VTABLE CSLabelAddin : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSLabelAddin, &CLSID_SLabelAddin>,
	public IDispatchImpl<ISLabelAddin, &IID_ISLabelAddin, &LIBID_SLABELEXCELADDINLib>,
	public IDispatchImpl<_IDTExtensibility2, &IID__IDTExtensibility2, &LIBID_AddInDesignerObjects>,
	public IDispEventSimpleImpl<1, CSLabelAddin, &__uuidof(Office::_CommandBarButtonEvents)>,
	public IDispEventSimpleImpl<4, CSLabelAddin, &__uuidof(Excel::AppEvents)>
{
public:
	typedef IDispEventSimpleImpl<1, CSLabelAddin, &__uuidof(Office::_CommandBarButtonEvents)> CommandButtonEvents_Set;
	typedef IDispEventSimpleImpl<4, CSLabelAddin, &__uuidof(Excel::AppEvents)> AppEvents4;

	CSLabelAddin()
	{

	}

DECLARE_REGISTRY_RESOURCEID(IDR_SLABELADDIN)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSLabelAddin)
	COM_INTERFACE_ENTRY(ISLabelAddin)
//DEL 	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY2(IDispatch, ISLabelAddin)
	COM_INTERFACE_ENTRY(_IDTExtensibility2)
//	COM_INTERFACE_ENTRY(IRibbonExtensibility)
END_COM_MAP()

BEGIN_SINK_MAP(CSLabelAddin)
	SINK_ENTRY_INFO(1, __uuidof(Office::_CommandBarButtonEvents), 0x01, OnClickButtonSet, &OnClickButtonInfo)
END_SINK_MAP()

// ISLabelAddin
public:
// _IDTExtensibility2
	STDMETHOD(OnConnection)(IDispatch *Application, ext_ConnectMode ConnectMode, IDispatch *AddInInst, SAFEARRAY **custom);
	STDMETHOD(OnDisconnection)(ext_DisconnectMode RemoveMode, SAFEARRAY **custom);
	STDMETHOD(OnAddInsUpdate)(SAFEARRAY **custom)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(OnStartupComplete)(SAFEARRAY **custom)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(OnBeginShutdown)(SAFEARRAY **custom)
	{
		return E_NOTIMPL;
	}

//	CommandBar Button Event

	void __stdcall OnClickButtonSet(IDispatch *Ctrl,		VARIANT_BOOL *CancelDefault);

	CComQIPtr<_CommandBarButton> AddCmdButton(CComPtr<CommandBarControls> spBarControls, UINT uBitmapID,BSTR strCaption, BSTR strTag);
public:
	STDMETHOD(OnPaste)(IDispatch *Ctrl, VARIANT *CancelDefault);
	STDMETHOD(OnCopy)(IDispatch *Ctrl, VARIANT *CancelDefault);
	STDMETHOD(OnCut)(IDispatch *Ctrl, VARIANT *CancelDefault);
	STDMETHOD(OnOpen)(IDispatch *Ctrl, VARIANT *CancelDefault);
private:
	CComQIPtr<_CommandBarButton> m_spCmdButtonSet;
	CComQIPtr<_Application> m_Application;
	
	CBitmapHelper m_BitmapHelper;
};

#endif //__SLABELADDIN_H_
