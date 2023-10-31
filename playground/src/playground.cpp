#include <iostream>
import smallVector;


int main()
{
	SmallVector<int, 10> sort = {11, 30, 1, 20, 15, 5, 19, 88, 99, 12};



	sort.heap_sort();

	for (auto value : sort) 
	{
		std::cout << " Value: " << value << std::endl;
	}
	return 0;
}


