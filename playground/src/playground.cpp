#include <iostream>
import smallVector;


int main()
{
	SmallVector<int, 5> sort;
	sort.push_back(11);
	sort.push_back(30);
	sort.push_back(1);
	sort.push_back(20);
	sort.push_back(15);

	sort.quick_sort(0, sort.size() - 1);

	for (auto value : sort) 
	{
		std::cout << " Value: " << value << std::endl;
	}
	return 0;
}


