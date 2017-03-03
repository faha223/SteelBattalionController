#pragma once

#include "Internal.h"
#include <mutex>

class WinUsb
{
private: 
	WINUSB_INTERFACE_HANDLE handle;
	std::mutex interfaceMutex;
public:
	WinUsb(WINUSB_INTERFACE_HANDLE handle);
	BOOL WriteToBulkEndpoint(UCHAR* pID, UCHAR *szBuffer, ULONG cbSize, ULONG* pcbWritten);
	BOOL ReadFromBulkEndpoint(UCHAR *pID, UCHAR *szBuffer, ULONG cbSize, ULONG *pcbRead);
	~WinUsb();
};

