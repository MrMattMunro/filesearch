// SLabelAddin.h : Declaration of the CSLabelAddin

#ifndef __SLABELADDIN_H_
#define __SLABELADDIN_H_

#include "resource.h"       // main symbols
#include "BitmapHelper.h"
#include "fsAddinDlgAgent.h"

extern _ATL_FUNC_INFO OnClickButtonInfo;

/////////////////////////////////////////////////////////////////////////////
// CSLabelAddin
class ATL_NO_VTABLE CSLabelAddin : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSLabelAddin, &CLSID_SLabelAddin>,
	public IDispatchImpl<ISLabelAddin, &IID_ISLabelAddin, &LIBID_SLABELWORDADDINLib>,
	public IDispatchImpl<_IDTExtensibility2, &IID__IDTExtensibility2, &LIBID_AddInDesignerObjects>,
	public IDispEventSimpleImpl<1, CSLabelAddin, &__uuidof(Word::ApplicationEvents4)>,
	public IDispEventSimpleImpl<2, CSLabelAddin, &__uuidof(Office::_CommandBarButtonEvents)>
{
public:
	typedef IDispEventSimpleImpl<1, CSLabelAddin, &__uuidof(Word::ApplicationEvents4)> AppEvents;
	typedef IDispEventSimpleImpl<2, CSLabelAddin, &__uuidof(Office::_CommandBarButtonEvents)> CommandButtonEvents_Set;

	CSLabelAddin()
	{

	}

	~CSLabelAddin()
	{

	}

	//////////////////////////////////////////////////////////////////////////
	void __stdcall OnClickButtonSet(IDispatch *Ctrl,
		VARIANT_BOOL *CancelDefault);

	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////

DECLARE_REGISTRY_RESOURCEID(IDR_SLABELADDIN)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSLabelAddin)
	COM_INTERFACE_ENTRY(ISLabelAddin)
//DEL 	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY2(IDispatch, ISLabelAddin)
	COM_INTERFACE_ENTRY(_IDTExtensibility2)
END_COM_MAP()

BEGIN_SINK_MAP(CSLabelAddin)
	SINK_ENTRY_INFO(2, __uuidof(Office::_CommandBarButtonEvents), 0x01, OnClickButtonSet, &OnClickButtonInfo)
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

public:
	STDMETHOD(OpenFile)();
	STDMETHOD(SaveFile)();
public:
	CComQIPtr<_CommandBarButton> AddCmdButton(CComPtr<CommandBarControls> spBarControls, UINT uBitmapID, BSTR strCaption, BSTR strTag);

private:
	CComQIPtr<Word::_Application> m_Application;

	CComQIPtr<_CommandBarButton> m_spCmdButtonSet;
	CBitmapHelper m_BitmapHelper; 

	fsAddinDlgAgent m_addinAgent;
};

#endif //__SLABELADDIN_H_
