#include "WinUsb_ThreadSafe.h"
using namespace std;

WinUsb::WinUsb(WINUSB_INTERFACE_HANDLE handle) : handle(handle)
{
}


WinUsb::~WinUsb()
{
}

BOOL WinUsb::WriteToBulkEndpoint(UCHAR* pID, UCHAR *szBuffer, ULONG cbSize, ULONG* pcbWritten)
{
	if (handle == INVALID_HANDLE_VALUE || !pID || !pcbWritten)
	{
		return FALSE;
	}

	BOOL bResult = true;

	ULONG cbSent = 0;

	{
		std::lock_guard<std::mutex> lk(interfaceMutex);
		bResult = WinUsb_WritePipe(handle, *pID, szBuffer, cbSize, &cbSent, 0);
		if (!bResult)
		{
			goto done;
		}
	}

	printf("Wrote to pipe %d: %s \nActual data transferred: %d.\n", *pID, szBuffer, cbSent);
	*pcbWritten = cbSent;


done:
	return bResult;

}

BOOL WinUsb::ReadFromBulkEndpoint(UCHAR *pID, UCHAR *szBuffer, ULONG cbSize, ULONG *pcbRead)
{
	if (handle == INVALID_HANDLE_VALUE || !pID || !pcbRead)
	{
		return FALSE;
	}

	BOOL bResult = true;

	ULONG cbRead = 0;

	{
		std::lock_guard<std::mutex> lk(interfaceMutex);
		bResult = WinUsb_ReadPipe(handle, *pID, szBuffer, cbSize, &cbRead, 0);
		if (!bResult)
		{
			goto done;
		}
	}

	printf("Read from pipe %d: %s \nActual data transferred: %d.\n", *pID, szBuffer, cbRead);
	*pcbRead = cbRead;


done:
	return bResult;
}