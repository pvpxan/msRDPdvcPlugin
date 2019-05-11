// compreg.h : Declaration of the CCompReg
// This file also contains declaration of the DLL plugin.
// This is needed for proper registry DLL registration and to compile correctly using Microsoft ATL.
// Both Listener callback and Channel callback are defined here.
// Foundation for this code comes from the Windows 7 SDK

#pragma once
#include "stdafx.h"
#include "resource.h"       // main symbols
#include "msRDPdvcPlugin_i.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

// Virtual Channel definitions
#define CHANNEL1 "CHANNEL1"
#define CHANNEL2 "CHANNEL2"

// msRDPdvcPlugin definition
// This portion is used for COM registration
// Compreg GUID: 7e6e7425-ac71-4e62-9752-8235a3ef2ae9
// msRDPdvcPluginLib GUID: 1e300d6b-9787-4bf6-a5eb-57c443a5bf8c
class ATL_NO_VTABLE CompReg :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CompReg, &CLSID_CompReg>,
	public IDispatchImpl<IComponentRegistrar, &IID_IComponentRegistrar, &LIBID_msRDPdvcPluginLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	DECLARE_REGISTRY_RESOURCEID(IDR_COMPREG)

	BEGIN_COM_MAP(CompReg)
		COM_INTERFACE_ENTRY(IComponentRegistrar)
		COM_INTERFACE_ENTRY(IDispatch)
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}
};

//OBJECT_ENTRY_AUTO(__uuidof(CompReg), CompReg) // This was part of the initial ATL template but is to NOT be used.

// ----------------------------------------------------------------------------------------------------------------

// IWTSPlugin implementation
// Definition of the Initialize function is here.
class ATL_NO_VTABLE msRDPdvcPlugin :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<msRDPdvcPlugin, &CLSID_CompReg>,
	public IWTSPlugin
{
public:
	DECLARE_REGISTRY_RESOURCEID(IDR_MSRDPDVCPLUGIN)

	BEGIN_COM_MAP(msRDPdvcPlugin)
		COM_INTERFACE_ENTRY(IWTSPlugin)
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

	// implement IWTSPlugin
	//
	HRESULT STDMETHODCALLTYPE Initialize(__in IWTSVirtualChannelManager *pChannelMgr);

	HRESULT STDMETHODCALLTYPE Connected()
	{
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE Disconnected(DWORD dwDisconnectCode)
	{
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE Terminated()
	{
		return S_OK;
	}
};

OBJECT_ENTRY_AUTO(__uuidof(CompReg), msRDPdvcPlugin) // Entry Point

// ----------------------------------------------------------------------------------------------------------------

// Callback Definitions per channel below:

// ----------------------------------------------------------------------------------------------------------------

// Class ListenerCallback_CHANNEL1 implements IWTSListenerCallback interface
class ATL_NO_VTABLE ListenerCallback_CHANNEL1 :
	public CComObjectRootEx<CComMultiThreadModel>,
	public IWTSListenerCallback
{
public:

	BEGIN_COM_MAP(ListenerCallback_CHANNEL1)
		COM_INTERFACE_ENTRY(IWTSListenerCallback)
	END_COM_MAP()

	// IWTSListenerCallback
	//
	HRESULT STDMETHODCALLTYPE
		OnNewChannelConnection(
			__in IWTSVirtualChannel *pChannel,
			__in_opt BSTR data,
			__out BOOL *pbAccept,
			__out IWTSVirtualChannelCallback **ppCallback);
};

// Class ChannelCallback_CHANNEL1 implements IWTSVirtualChannelCallback interface
class ATL_NO_VTABLE ChannelCallback_CHANNEL1 :
	public CComObjectRootEx<CComMultiThreadModel>,
	public IWTSVirtualChannelCallback
{
	CComPtr<IWTSVirtualChannel> m_ptrChannel;

public:

	BEGIN_COM_MAP(ChannelCallback_CHANNEL1)
		COM_INTERFACE_ENTRY(IWTSVirtualChannelCallback)
	END_COM_MAP()

	VOID SetChannel(IWTSVirtualChannel *pChannel)
	{
		m_ptrChannel = pChannel;
	}

	// IWTSVirtualChannelCallback  Methods
	/*
	 *  Called whenever a full message from the server is received
	 *  The message is fully reassembled and has the exact size
	 *  as the Write() call on the server
	 */
	HRESULT STDMETHODCALLTYPE OnDataReceived(ULONG cbSize, __in_bcount(cbSize) BYTE *pBuffer);

	/*
	 *  The channel is disconnected, all Write() calls will fail
	 *  no more incomming data is expected.
	 */
	HRESULT STDMETHODCALLTYPE OnClose()
	{
		return m_ptrChannel->Close();
	}
};

// ----------------------------------------------------------------------------------------------------------------

// Class ListenerCallback_CHANNEL2 implements IWTSListenerCallback interface
class ATL_NO_VTABLE ListenerCallback_CHANNEL2 :
	public CComObjectRootEx<CComMultiThreadModel>,
	public IWTSListenerCallback
{
public:

	BEGIN_COM_MAP(ListenerCallback_CHANNEL2)
		COM_INTERFACE_ENTRY(IWTSListenerCallback)
	END_COM_MAP()

	// IWTSListenerCallback
	//
	HRESULT STDMETHODCALLTYPE
		OnNewChannelConnection(
			__in IWTSVirtualChannel *pChannel,
			__in_opt BSTR data,
			__out BOOL *pbAccept,
			__out IWTSVirtualChannelCallback **ppCallback);
};

// Class ChannelCallback_CHANNEL2 implements IWTSVirtualChannelCallback interface
class ATL_NO_VTABLE ChannelCallback_CHANNEL2 :
	public CComObjectRootEx<CComMultiThreadModel>,
	public IWTSVirtualChannelCallback
{
	CComPtr<IWTSVirtualChannel> m_ptrChannel;

public:

	BEGIN_COM_MAP(ChannelCallback_CHANNEL2)
		COM_INTERFACE_ENTRY(IWTSVirtualChannelCallback)
	END_COM_MAP()

	VOID SetChannel(IWTSVirtualChannel *pChannel)
	{
		m_ptrChannel = pChannel;
	}

	// IWTSVirtualChannelCallback  Methods
	/*
	 *  Called whenever a full message from the server is received
	 *  The message is fully reassembled and has the exact size
	 *  as the Write() call on the server
	 */
	HRESULT STDMETHODCALLTYPE OnDataReceived(ULONG cbSize, __in_bcount(cbSize) BYTE *pBuffer);

	/*
	 *  The channel is disconnected, all Write() calls will fail
	 *  no more incomming data is expected.
	 */
	HRESULT STDMETHODCALLTYPE OnClose()
	{
		return m_ptrChannel->Close();
	}
};

// ----------------------------------------------------------------------------------------------------------------
