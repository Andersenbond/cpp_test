module;
#include <iostream>
#include <optional>

export module mv_search_algorithm;

// Import small vectors module used in the algorithm.
import smallVector;

/**
 * @brief Binary search for a sorted SmallVector.
 *
 * This function performs a binary search to find the index of the specified
 * value in a sorted SmallVector. If the value is found, the index is returned;
 * otherwise, std::nullopt is returned.
 *
 * @tparam T The type of elements in the SmallVector.
 * @tparam N The size of the SmallVector.
 * @param smallVector A reference to the sorted SmallVector.
 * @param searchValue The value to search for.
 * @return The index of the element equal to searchValue if found; otherwise, std::nullopt.
 *
 * @note For this function to work correctly, the SmallVector must be sorted
 * in ascending order.
 */
export template <typename T, std::size_t N>
 int binary_search(const SmallVector<T, N>& sv, T searchValue)
{
	int left = 0, right = sv.size() - 1;

	while (left <= right) 
	{
		int mid = left + (right - left) / 2;

		if (sv[mid] == searchValue)
		{
			return mid;
		}
		if (sv[mid] > searchValue)
		{
			right = mid - 1;
		}
		else 
		{
			left = mid + 1;
		}
	}
	// Element not found
	return std::nullopt; // or return -1
}





