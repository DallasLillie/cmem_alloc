#include <cstdint>
#include "LinearAllocator.h"

LinearAllocator::LinearAllocator(uint32_t num_bytes)
	: size(num_bytes), offset(0)
{
	start = new char[num_bytes];
}

LinearAllocator::~LinearAllocator()
{
	this->Free();
}

void* LinearAllocator::Allocate(uint32_t num_bytes)
{
	if (this->offset + num_bytes > this->size)
	{
		return nullptr;
	}
	else
	{
		void* r = (void*)(((uint32_t)this->start) + this->offset);
		this->offset += num_bytes;
		return r;
	}

}

void LinearAllocator::Free()
{
	delete[] start;
}

