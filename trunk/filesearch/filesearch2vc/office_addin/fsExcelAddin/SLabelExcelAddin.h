/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Jan 26 10:53:40 2012
 */
/* Compiler settings for F:\rw\slsearch\workdir\filesearch\filesearch2vc\office_addin\fsExcelAddin\SLabelExcelAddin.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __SLabelExcelAddin_h__
#define __SLabelExcelAddin_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ISLabelAddin_FWD_DEFINED__
#define __ISLabelAddin_FWD_DEFINED__
typedef interface ISLabelAddin ISLabelAddin;
#endif 	/* __ISLabelAddin_FWD_DEFINED__ */


#ifndef __SLabelAddin_FWD_DEFINED__
#define __SLabelAddin_FWD_DEFINED__

#ifdef __cplusplus
typedef class SLabelAddin SLabelAddin;
#else
typedef struct SLabelAddin SLabelAddin;
#endif /* __cplusplus */

#endif 	/* __SLabelAddin_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ISLabelAddin_INTERFACE_DEFINED__
#define __ISLabelAddin_INTERFACE_DEFINED__

/* interface ISLabelAddin */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ISLabelAddin;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DCA92446-D03F-4B54-B9EB-23CAA178009E")
    ISLabelAddin : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnOpen( 
            IDispatch __RPC_FAR *Ctrl,
            VARIANT __RPC_FAR *CancelDefault) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnCut( 
            IDispatch __RPC_FAR *Ctrl,
            VARIANT __RPC_FAR *CancelDefault) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnCopy( 
            IDispatch __RPC_FAR *Ctrl,
            VARIANT __RPC_FAR *CancelDefault) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnPaste( 
            IDispatch __RPC_FAR *Ctrl,
            VARIANT __RPC_FAR *CancelDefault) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISLabelAddinVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISLabelAddin __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISLabelAddin __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISLabelAddin __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ISLabelAddin __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ISLabelAddin __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ISLabelAddin __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ISLabelAddin __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnOpen )( 
            ISLabelAddin __RPC_FAR * This,
            IDispatch __RPC_FAR *Ctrl,
            VARIANT __RPC_FAR *CancelDefault);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnCut )( 
            ISLabelAddin __RPC_FAR * This,
            IDispatch __RPC_FAR *Ctrl,
            VARIANT __RPC_FAR *CancelDefault);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnCopy )( 
            ISLabelAddin __RPC_FAR * This,
            IDispatch __RPC_FAR *Ctrl,
            VARIANT __RPC_FAR *CancelDefault);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnPaste )( 
            ISLabelAddin __RPC_FAR * This,
            IDispatch __RPC_FAR *Ctrl,
            VARIANT __RPC_FAR *CancelDefault);
        
        END_INTERFACE
    } ISLabelAddinVtbl;

    interface ISLabelAddin
    {
        CONST_VTBL struct ISLabelAddinVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISLabelAddin_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISLabelAddin_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISLabelAddin_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISLabelAddin_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ISLabelAddin_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ISLabelAddin_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ISLabelAddin_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ISLabelAddin_OnOpen(This,Ctrl,CancelDefault)	\
    (This)->lpVtbl -> OnOpen(This,Ctrl,CancelDefault)

#define ISLabelAddin_OnCut(This,Ctrl,CancelDefault)	\
    (This)->lpVtbl -> OnCut(This,Ctrl,CancelDefault)

#define ISLabelAddin_OnCopy(This,Ctrl,CancelDefault)	\
    (This)->lpVtbl -> OnCopy(This,Ctrl,CancelDefault)

#define ISLabelAddin_OnPaste(This,Ctrl,CancelDefault)	\
    (This)->lpVtbl -> OnPaste(This,Ctrl,CancelDefault)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISLabelAddin_OnOpen_Proxy( 
    ISLabelAddin __RPC_FAR * This,
    IDispatch __RPC_FAR *Ctrl,
    VARIANT __RPC_FAR *CancelDefault);


void __RPC_STUB ISLabelAddin_OnOpen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISLabelAddin_OnCut_Proxy( 
    ISLabelAddin __RPC_FAR * This,
    IDispatch __RPC_FAR *Ctrl,
    VARIANT __RPC_FAR *CancelDefault);


void __RPC_STUB ISLabelAddin_OnCut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISLabelAddin_OnCopy_Proxy( 
    ISLabelAddin __RPC_FAR * This,
    IDispatch __RPC_FAR *Ctrl,
    VARIANT __RPC_FAR *CancelDefault);


void __RPC_STUB ISLabelAddin_OnCopy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISLabelAddin_OnPaste_Proxy( 
    ISLabelAddin __RPC_FAR * This,
    IDispatch __RPC_FAR *Ctrl,
    VARIANT __RPC_FAR *CancelDefault);


void __RPC_STUB ISLabelAddin_OnPaste_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISLabelAddin_INTERFACE_DEFINED__ */



#ifndef __SLABELEXCELADDINLib_LIBRARY_DEFINED__
#define __SLABELEXCELADDINLib_LIBRARY_DEFINED__

/* library SLABELEXCELADDINLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_SLABELEXCELADDINLib;

EXTERN_C const CLSID CLSID_SLabelAddin;

#ifdef __cplusplus

class DECLSPEC_UUID("60235315-A517-419C-9EE3-D104139BF8FB")
SLabelAddin;
#endif
#endif /* __SLABELEXCELADDINLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long __RPC_FAR *, unsigned long            , VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long __RPC_FAR *, VARIANT __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
