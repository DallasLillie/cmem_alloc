#include <cstdint>
#include "StackAllocator.h"

StackAllocator::StackAllocator(StackAllocator::Header stackSize_bytes)
	: size(stackSize_bytes)
{
	//todo: do i wanna use byte?
	start = new char[stackSize_bytes];
	top = start;
}


StackAllocator::~StackAllocator()
{
	delete[] start;
}


void* StackAllocator::push(StackAllocator::Header num_bytes)
{
	//Return block
	void *r = top;

	//Calculate the amount of memory we need to allocate
	StackAllocator::Header block_size = sizeof(StackAllocator::Header) + num_bytes;

	//Check that we have that amount of space
	if (((uint32_t)top - (uint32_t)start) + block_size > this->size)
	{
		return nullptr;
	}

	//Place a header
	void *header = (void*)((uint32_t)top + num_bytes);
	*(StackAllocator::Header*)header = num_bytes;


	//Update Top
	top = (void*)((uint32_t)top + block_size);

	return r;
}


bool StackAllocator::pop()
{
	if (top != start)
	{
		void *header = (void*)((uint32_t)top - sizeof(StackAllocator::Header));
		StackAllocator::Header block_size = *(StackAllocator::Header*)header;
		top = (void*)((uint32_t)header - block_size);
		return true;
	}
	else
	{
		return false;
	}
}


void StackAllocator::clear()
{
	while (pop())
	{
	}
}