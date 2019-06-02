#pragma once

class StackAllocator
{
public:
	typedef uint16_t Header;
	void *top;
	void *start;
	Header size;


	//todo: what is explicit keyword here for
	explicit StackAllocator(Header stackSize_bytes);

	void* push(Header size_bytes);

	bool pop();

	void clear();

	~StackAllocator();
};


