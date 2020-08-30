#include <iostream>

int main()
{
	int num = 2;
	
	int* arr = new int[22];
	
	std::cout<<"Location of code  = "<<(void *)main<<std::endl;
	std::cout<<"Location of heap  = "<<arr<<std::endl;
	std::cout<<"Location of stack = "<<&num<<std::endl;
	
	delete []arr;
	
	return 0;
}
