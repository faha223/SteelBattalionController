#include "NamedPipe.h"
using namespace std;

#define BUFSIZE 512

NamedPipe::NamedPipe(string pipeName) : pipeHandle(0), 
	connected(false),
	pipeName(pipeName)
{
	
}

BOOL NamedPipe::Connect()
{
	std::lock_guard<std::mutex> lk(pipeMutex);
	char lpszPipename[256];
	sprintf_s(lpszPipename, 255, "\\\\.\\pipe\\%s", pipeName.c_str());
	pipeHandle = CreateFile(
		lpszPipename,
		GENERIC_READ | GENERIC_WRITE, 
		0, 
		NULL, 
		OPEN_EXISTING, 
		0, 
		NULL);
	return (connected = (pipeHandle != INVALID_HANDLE_VALUE));
}

bool NamedPipe::IsConnected()
{
	std::lock_guard<std::mutex> lk(pipeMutex);
	return connected;
}

ULONG NamedPipe::Read(void *buffer, ULONG bufferSize)
{
	std::lock_guard<std::mutex> lk(pipeMutex);
	if (connected)
	{
		ULONG bytesRead = 0;
		if (!ReadFile(pipeHandle, buffer, bufferSize, &bytesRead, nullptr))
		{
			connected = false;
			DisconnectNamedPipe(pipeHandle);
			CloseHandle(pipeHandle);
			pipeHandle = 0;
			return 0;
		}
		return bytesRead;
	}
	return 0;
}

ULONG NamedPipe::Write(const void *buffer, ULONG bufferSize)
{
	std::lock_guard<std::mutex> lk(pipeMutex);
	if (connected)
	{
		ULONG bytesWritten = 0;
		if (!WriteFile(pipeHandle, buffer, bufferSize, &bytesWritten, nullptr))
		{
			connected = false;
			DisconnectNamedPipe(pipeHandle);
			CloseHandle(pipeHandle);
			pipeHandle = 0;
			return 0;
		}
		return bytesWritten;
	}
	return 0;
}

BOOL NamedPipe::Peek(UCHAR &byte, DWORD &bytesRead, DWORD &totalBytes, DWORD &bytesLeft)
{
	std::lock_guard<std::mutex> lk(pipeMutex);
	return PeekNamedPipe(pipeHandle, &byte, sizeof(UCHAR), &bytesRead, &totalBytes, &bytesLeft);
}

NamedPipe::~NamedPipe()
{
	if (pipeHandle != 0)
	{
		DisconnectNamedPipe(pipeHandle);
		CloseHandle(pipeHandle);
	}
	pipeHandle = 0;
}
