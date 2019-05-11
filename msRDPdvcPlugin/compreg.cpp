// compreg.cpp : Implementation of CCompReg

#include "stdafx.h"
#include "resource.h"
#include "compreg.h"


// CCompReg
using namespace ATL;

template<class T> inline
void CreateChannelEndpoint(HRESULT *hr, const char *channelName, __in IWTSVirtualChannelManager *pChannelMgr)
{
	// -------------
	CComObject<T> *pListenerCallback;
	CComPtr<T> ptrListenerCallback;
	CComPtr<IWTSListener> ptrListener;

	// Create an instance of the FrzHostedDVCPlugin object.
	HRESULT _hr = CComObject<T>::CreateInstance(&pListenerCallback);
	ptrListenerCallback = pListenerCallback;

	// Attach the callback to the endpoint.
	_hr = pChannelMgr->CreateListener(
		channelName,
		0,
		(T*)ptrListenerCallback,
		&ptrListener);

	if (_hr != S_OK) {
		hr = &_hr;
	}
}

// IWTSPlugin::Initialize implementation.
/*
 *  Called immediately after instantiating the COM class
 */
HRESULT msRDPdvcPlugin::Initialize(__in IWTSVirtualChannelManager *pChannelMgr)
{
	HRESULT hr = S_OK;

	CreateChannelEndpoint<ListenerCallback_CHANNEL1>(&hr, CHANNEL1, __in pChannelMgr);
	CreateChannelEndpoint<ListenerCallback_CHANNEL2>(&hr, CHANNEL2, __in pChannelMgr);

	// The last error is returned.
	if (hr != S_OK)
	{
		MessageBox(NULL, L"Error initializing dynamic virtual channel.", L"Error...", MB_OK | MB_ICONERROR);
	}

	return hr;
}
