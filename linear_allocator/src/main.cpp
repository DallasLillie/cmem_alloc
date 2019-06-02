#include <iostream>
#include "LinearAllocator.h"

int main()
{
	LinearAllocator linearAllocator(16);

	int* first = static_cast<int*>(linearAllocator.Allocate(sizeof(int)));
	char* second = static_cast<char*>(linearAllocator.Allocate(sizeof(char)));
	short* third = static_cast<short*>(linearAllocator.Allocate(sizeof(short)));
	float* fourth = static_cast<float*>(linearAllocator.Allocate(sizeof(float)));
	double* fifth = static_cast<double*>(linearAllocator.Allocate(sizeof(double)));

	if (first)
	{
		*first = 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2;
	}
	if (second)
	{
		*second = 'A';
	}
	if (third)
	{
		*third = 2234;
	}
	if (fourth)
	{
		*fourth = 85.43f;
	}
	if (fifth)
	{
		*fifth = 99.87;
	}

	std::cin.get();
}