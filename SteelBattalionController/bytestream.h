#pragma once
#include <vector>
#include <mutex>
#include <Windows.h>

class Bytestream
{
private:
	std::mutex mutex;
	std::vector<UCHAR> buffer;
public:
	Bytestream();
	~Bytestream();
	void clear();
	UCHAR* toArray(size_t &bufsize);
};