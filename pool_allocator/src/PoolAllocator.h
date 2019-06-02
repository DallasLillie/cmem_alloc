#pragma once
//	//todo: some general ways to improve this(and all of these experimental allocators):
//	//look into making it threadsafe
//	//copy constructor/move constructor/assignement operator stuff
//	//aligned memory address stuff
//	//unit tests would actually be perfect for this guy
//	//api could use some renaming
//	//const correctness is not very present
//	//'new' can throw exceptions if memory has been exhausted, would be nice to have some code that makes sure we dont have to worry about that
//	//	this link: https://stackoverflow.com/questions/4172722/what-is-the-rule-of-three, talks about the exceptioned mention above
//	//todo: move assigment/move Constructor
//	//todo: cross-platform/cross-compiler

class PoolAllocator
{
private:
	//todo: not sure if these should be made public or not
	void Init();
	void Clear();

	void *pool;
	void *top;

	uint32_t numPoolItems;
	uint32_t poolItemSize;
	uint32_t numCurrentlyAllocated;

public:
	//Basic Class Functions
	//
	//Ctor
	PoolAllocator(uint32_t poolSize, uint32_t poolItemSize);

	//Copy Ctor
	PoolAllocator(const PoolAllocator& that) = delete;

	//Copy Assignment
	PoolAllocator& operator=(const PoolAllocator& that) = delete;

	//Move Ctor
	PoolAllocator(PoolAllocator&& other);

	//Move Assignment
	PoolAllocator& operator=(PoolAllocator&& other);

	//Destructor
	~PoolAllocator();

	//Accessors
	const void* Pool() const { return pool; }
	const void* Top() const { return top; }

	//Interface
	//
	void* Allocate();

	bool Free(void *block);
};
