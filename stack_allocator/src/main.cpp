#include <iostream>
#include <stdlib.h>
#include "StackAllocator.h"

int main()
{
	StackAllocator stackAllocator(30);
	stackAllocator.pop();
	void *first = stackAllocator.push(10);
	void *second = stackAllocator.push(8);
	stackAllocator.pop();
	void *third = stackAllocator.push(4);
	stackAllocator.clear();
	first = stackAllocator.push(4);

	stackAllocator.pop();
	stackAllocator.pop();
	stackAllocator.pop();
	stackAllocator.pop();
	stackAllocator.pop();
	stackAllocator.pop();
	stackAllocator.pop();




	//stackAllocator.begin = 4;
	std::cout << "Press Enter to Continue..." << std::endl;
	std::cin.get();
}