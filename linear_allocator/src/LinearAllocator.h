#pragma once


class LinearAllocator
{
	void *start = nullptr;
	uint32_t size;
	uint32_t offset;
public:
	LinearAllocator(uint32_t num_bytes);

	~LinearAllocator();

	void* Allocate(uint32_t num_bytes);

	void Free();
};


