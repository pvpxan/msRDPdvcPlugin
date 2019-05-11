// 

#include "stdafx.h"
#include "resource.h"
#include "compreg.h"
#include "Datafunc.h"

// IWTSListenerCallback::OnNewChannelConnection implementation.
HRESULT ListenerCallback_CHANNEL1::OnNewChannelConnection(__in IWTSVirtualChannel *pChannel,
	__in_opt BSTR data, __out BOOL *pbAccept, __out IWTSVirtualChannelCallback **ppCallback)
{
	HRESULT hr;
	CComObject<ChannelCallback_CHANNEL1> *pCallback;
	CComPtr<ChannelCallback_CHANNEL1> ptrCallback;

	// Prevent C4100 "unreferenced parameter" warnings.
	UNREFERENCED_PARAMETER(data);

	*pbAccept = FALSE; // always accept connection
	hr = CComObject<ChannelCallback_CHANNEL1>::CreateInstance(&pCallback);
	ptrCallback = pCallback;

	ptrCallback->SetChannel(pChannel);

	*ppCallback = ptrCallback; // provide the plgn object as the callback
	(*ppCallback)->AddRef();

	*pbAccept = TRUE;

	return hr;
}

HRESULT STDMETHODCALLTYPE ChannelCallback_CHANNEL1::OnDataReceived(ULONG cbSize, __in_bcount(cbSize) BYTE *pBuffer)
{
	HRESULT hr;
	hr = S_OK; // This needs to be changed at some point.

	// Send a response back to server with the size of the payload received.
	try
	{
		BYTE* rBuffer = NULL;
		ConvertULONGtoBYTEbuffer(&rBuffer, cbSize);

		if (rBuffer != NULL)
		{
			ULONG rSize = BYTElen(rBuffer);

			hr = m_ptrChannel->Write(rSize, rBuffer, NULL); // The rBuffer should only ever be 4 bytes.
		}
	}
	catch (...)
	{
		MessageBox(NULL, TEXT("An error occured while attempting to send a data received response back to server."), TEXT("Error..."), MB_OK | MB_ICONERROR);
	}

	//MessageBoxA(NULL, "Data received on channel 1.", "DVC Channel Message...", MB_OK);

	// Do work with data here.

	return hr;
}
