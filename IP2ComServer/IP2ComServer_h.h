

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Wed Feb 18 18:41:00 2009
 */
/* Compiler settings for .\IP2ComServer.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __IP2ComServer_h_h__
#define __IP2ComServer_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IIP2ComServer_FWD_DEFINED__
#define __IIP2ComServer_FWD_DEFINED__
typedef interface IIP2ComServer IIP2ComServer;
#endif 	/* __IIP2ComServer_FWD_DEFINED__ */


#ifndef __CIP2ComServerDoc_FWD_DEFINED__
#define __CIP2ComServerDoc_FWD_DEFINED__

#ifdef __cplusplus
typedef class CIP2ComServerDoc CIP2ComServerDoc;
#else
typedef struct CIP2ComServerDoc CIP2ComServerDoc;
#endif /* __cplusplus */

#endif 	/* __CIP2ComServerDoc_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 


#ifndef __IP2ComServer_LIBRARY_DEFINED__
#define __IP2ComServer_LIBRARY_DEFINED__

/* library IP2ComServer */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_IP2ComServer;

#ifndef __IIP2ComServer_DISPINTERFACE_DEFINED__
#define __IIP2ComServer_DISPINTERFACE_DEFINED__

/* dispinterface IIP2ComServer */
/* [uuid] */ 


EXTERN_C const IID DIID_IIP2ComServer;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("07EC726C-7926-49C3-9D19-96280C1C69BD")
    IIP2ComServer : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IIP2ComServerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IIP2ComServer * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IIP2ComServer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IIP2ComServer * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IIP2ComServer * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IIP2ComServer * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IIP2ComServer * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IIP2ComServer * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IIP2ComServerVtbl;

    interface IIP2ComServer
    {
        CONST_VTBL struct IIP2ComServerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIP2ComServer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IIP2ComServer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IIP2ComServer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IIP2ComServer_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IIP2ComServer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IIP2ComServer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IIP2ComServer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IIP2ComServer_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CIP2ComServerDoc;

#ifdef __cplusplus

class DECLSPEC_UUID("608B7C2A-58D9-4ABD-A859-07F49674450D")
CIP2ComServerDoc;
#endif
#endif /* __IP2ComServer_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


