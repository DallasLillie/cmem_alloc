#include <cstdint>
#include <iostream>
#include "PoolAllocator.h"

#define MAX_POOL_SIZE 0x11111111
#define MAX_POOL_ITEM_SIZE 0x04444444

#ifdef _WIN64
typedef uint64_t paddr;
#elif _WIN32
typedef uint32_t paddr;
#endif

PoolAllocator::PoolAllocator(uint32_t numPoolItems, uint32_t poolItemSize)
	: numPoolItems(numPoolItems), poolItemSize(poolItemSize), numCurrentlyAllocated(0)
{
	if (numPoolItems > MAX_POOL_SIZE || poolItemSize > MAX_POOL_ITEM_SIZE || numPoolItems <= 0 || poolItemSize <= 0)
	{
		pool = top = nullptr;
		this->numPoolItems = this->poolItemSize = this->numCurrentlyAllocated = 0;
		return;
	}

	pool = new char[numPoolItems * (poolItemSize + sizeof(void*))];
	top = pool;

	this->Init();
}


PoolAllocator::PoolAllocator(PoolAllocator&& other)
{
	*this = std::move(other);
}


PoolAllocator& PoolAllocator::operator=(PoolAllocator&& other)
{
	if (this != &other)
	{
		this->Clear();

		this->pool = other.pool;
		this->top = other.top;
		this->poolItemSize = other.poolItemSize;
		this->numPoolItems = other.numPoolItems;
		this->numCurrentlyAllocated = other.numCurrentlyAllocated;

		other.pool = nullptr;
		other.top = nullptr;
		other.poolItemSize = 0;
		other.numPoolItems = 0;
		other.numCurrentlyAllocated = 0;
	}

	return *this;
}


PoolAllocator::~PoolAllocator()
{
	Clear();
}


void PoolAllocator::Init()
{
	paddr*blockHeader = static_cast<paddr*>(pool);
	for (uint32_t i = 0; i < this->numPoolItems; ++i)
	{
		*blockHeader = (paddr)blockHeader + (poolItemSize + sizeof(void*));
		blockHeader = (paddr*)((paddr)blockHeader + (poolItemSize + sizeof(void*)));
		//todo: last node should be some kinda nullptr thing
	}
}


void* PoolAllocator::Allocate()
{
	if (numCurrentlyAllocated < numPoolItems)
	{
		numCurrentlyAllocated++;
	}
	else
	{
		//should i print some kind of error?
		return nullptr;
	}
	void *r = (void*)((paddr)top + sizeof(void*));
	top = (*(void **)top);
	return r;
}


bool PoolAllocator::Free(void *block)
{
	//todo: i assume that the block being freed is one that's been allocated but there's no guarantee that's the case
	//todo: all this type conversion should have static_cast stuff right?
	//todo: all this type conversion stuff feels like it could be macro'd or something

	//Block is actually within pool
	if ((paddr)block <= (paddr)pool)
	{
		return false;
	}
	else if ((paddr)block > (paddr)pool + numPoolItems * (poolItemSize + sizeof(void*)) - 1)
	{
		return false;
	}

	//Block pointer actually points to the start of a block
	if (((paddr)block - sizeof(void*)) % (poolItemSize + sizeof(void*)) != 0)
	{
		return false;
	}


	//Point the block at current top
	void **node = (void**)((paddr)block - sizeof(void*));
	*node = top;

	//Change top to point to the block
	top = node;
	numCurrentlyAllocated--;
	return true;
}


void PoolAllocator::Clear()
{
	delete[] pool;
}
