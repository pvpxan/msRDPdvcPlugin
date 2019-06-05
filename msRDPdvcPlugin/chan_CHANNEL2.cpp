// 

#include "stdafx.h"
#include "resource.h"
#include "compreg.h"
#include "Datafunc.h"

// IWTSListenerCallback::OnNewChannelConnection implementation.
HRESULT ListenerCallback_CHANNEL2::OnNewChannelConnection(__in IWTSVirtualChannel *pChannel,
	__in_opt BSTR data, __out BOOL *pbAccept, __out IWTSVirtualChannelCallback **ppCallback)
{
	HRESULT hr;
	CComObject<ChannelCallback_CHANNEL2> *pCallback;
	CComPtr<ChannelCallback_CHANNEL2> ptrCallback;

	// Prevent C4100 "unreferenced parameter" warnings.
	UNREFERENCED_PARAMETER(data);

	*pbAccept = FALSE; // always accept connection
	hr = CComObject<ChannelCallback_CHANNEL2>::CreateInstance(&pCallback);
	ptrCallback = pCallback;

	ptrCallback->SetChannel(pChannel);

	*ppCallback = ptrCallback; // provide the plgn object as the callback
	(*ppCallback)->AddRef();

	*pbAccept = TRUE;

	return hr;
}

HRESULT STDMETHODCALLTYPE ChannelCallback_CHANNEL2::OnDataReceived(ULONG cbSize, __in_bcount(cbSize) BYTE *pBuffer)
{
	//MessageBoxA(NULL, "Data received on channel 2.", "DVC Channel Message...", MB_OK); //debug
	
	ReadDataStream(cbSize, pBuffer, "C:\\TEMP\\");

	// Do work with data here.

	// Send a response back to server with the size of the payload received.
	BYTE* rBuffer = NULL;
	ConvertULONGtoBYTEbuffer(&rBuffer, cbSize);
	if (rBuffer != NULL)
	{
		ULONG rSize = BYTElen(rBuffer);
		m_ptrChannel->Write(rSize, rBuffer, NULL); // The rBuffer should only ever be 4 bytes.
	}

	return S_OK;
}
