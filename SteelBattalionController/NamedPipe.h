#pragma once
#include "Internal.h"
#include <string>
#include <mutex>

class NamedPipe
{
private:
	HANDLE pipeHandle;
	std::mutex pipeMutex;
	std::string pipeName;
	bool connected = false;
public:
	NamedPipe(std::string name);
	BOOL Connect();
	bool IsConnected();
	ULONG Write(const void *buffer, ULONG bufferSize);
	ULONG Read(void *buffer, ULONG bufferSize);
	BOOL Peek(UCHAR &byte, DWORD &bytesRead, DWORD &totalBytes, DWORD &bytesLeft);
	~NamedPipe();
};

