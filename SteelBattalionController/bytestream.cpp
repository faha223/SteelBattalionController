#include "bytestream.h"
using namespace std;

Bytestream::Bytestream() { }

Bytestream::~Bytestream() 
{
	clear();
}

void Bytestream::clear() 
{
	lock_guard<std::mutex>(this->mutex);
	buffer.clear();
}

UCHAR * Bytestream::toArray(size_t &bufsize)
{
	lock_guard<std::mutex>(this->mutex);
	bufsize = buffer.size();
	if (buffer.size() == 0)
		return nullptr;
	auto out = new UCHAR[buffer.size()];
	memcpy(out, buffer.data(), buffer.size() * sizeof(UCHAR));
	return out;
}