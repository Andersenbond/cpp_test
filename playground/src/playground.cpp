#include <iostream>
import smallVector;


int main()
{
	SmallVector<int, 10> sort;
	sort.push_back(11);
	sort.push_back(30);
	sort.push_back(1);
	sort.push_back(20);
	sort.push_back(15);
	sort.push_back(5);
	sort.push_back(19);
	sort.push_back(88);
	sort.push_back(99);
	sort.push_back(12);



	sort.heap_sort();

	for (auto value : sort) 
	{
		std::cout << " Value: " << value << std::endl;
	}
	return 0;
}


