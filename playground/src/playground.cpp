#include <iostream>
import smallVector;
import mv_search_algorithm;

int main()
{	
	int index = 0;
	SmallVector<int, 10> arr = {11, 30, 1, 20, 15, 5, 19, 88, 99, 12};

	std::cout << "Initial array: ";
	arr.stdout_dump(',');


	// Sort the array
	arr.heap_sort();
	std::cout << "Sorted array: ";
	arr.stdout_dump(',');

	// Find the element with value 20;
	std::cout << "Element 20 index: " << binary_search(arr, 20) << std::endl;
	std::cout << "Element 5 index: " << binary_search(arr, 5) << std::endl;
	std::cout << "Element 99 index: " << binary_search(arr, 99) << std::endl;


	return 0;
}


