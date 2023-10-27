export module smallVector;

export template <typename T, int N> class SmallVector;

#include <ranges>
#include <iterator>
#include <iostream>
#include <vector>

template <typename T, int N>
class SmallVector
{
public:
	/*** @Brief: Define iterator type alias */
	using iterator = T*;
	using const_iterator = const T*;

	/*** @Brief: Define value_type alias, required by ranges. */
	using value_type = T;

	/*** @Brief: Class constructor */
	SmallVector() : m_size{ 0 }
	{
		m_begin = static_cast<T*>(static_cast<void*>(m_data));
		m_end = static_cast<T*>(static_cast<void*>(m_data));
	}

	/*** @Brief: Copy constructor 
	 * @param: reference to the copy object.
	 * @return: none */
	SmallVector(const SmallVector& other)
	{
		m_begin = static_cast<T*>(static_cast<void*>(m_data));
		m_end = static_cast<T*>(static_cast<void*>(m_data));

		std::ranges::copy(other, std::back_inserter(*this));
		m_size = other.size();
	}

	/*** @Brief: Array begin iterator get function.
	 * @param:none.
	 * @return: returs array begin iterator. */
	iterator begin() const noexcept { return m_begin; }


	/*** @Brief: Array end iterator get function.
	 * @param:none.
	 * @return: returs array end iterator. */
	iterator end() const noexcept { return m_end; }

	/*** @Brief: Array end iterator get function.
	 * @param:none.
	 * @return: returs const reference to array begin iterator. */
	const_iterator cbegin() const noexcept { return m_begin; }
	
	/*** @Brief: Array end iterator get function.
	 * @param:none.
	 * @return: returs const reference to array end iterator. */
	const_iterator cend() const noexcept { return m_begin; }
	
	/*** @Brief: Implements array [] operator.
	 * @param:index of the element.
	 * @return: returs the element at index, if index is out of range 
	 * the function throw a std::out_of_range exception. */
	T& operator[](size_t index)
	{
		if (index >= N)
		{
			throw std::out_of_range("Index out of range");
		}
		return *static_cast<T*>(static_cast<void*>(&m_data[index * sizeof T]));
	}

	/*** @Brief: Returns the number of elements in the array.
	* @param:none.
	* @return: returs the number of elements in the array. */
	size_t size() const noexcept { return m_size; }


	/*** @Brief: Insert a new elements at the end of the array.
	* @param:none.
	* @return: none. */
	void push_back(const T& val) noexcept
	{
		if (m_size < N)
		{
			*m_end = val;
			m_end++;
			m_size++;
		}
	}

	/*** @Brief: Remove the elements at the end of the array.
	* @param:none.
	* @return: none. */
	void pop_back() noexcept 
	{
		if (m_size)
		{
			--m_end; // Adjust the end pointer
			--m_size; // Update the size
		}
	}

	/*** @Brief:Create a new element and insert it at the end of the array.
	* @param:none.
	* @return: none. */
	template <typename... Args> void emplace_back(Args&&... args) noexcept
	{
		if (m_size < N)
		{
			*m_end = T(std::forward<Args>(args)...); // Construct in-place
			++m_size; // Increment the size
			++m_end;
		}
	}

 
	/*** @Brief: Sort the Array using the quick sort algorithm.
	* @param:none.
	* @return: none. */
	void quick_sort(int left, int right) noexcept
	{
		if (left >= right)
		{
			return;
		}

		// Get the pivot position. 
		auto pivot_index = partition(left, right);

		// Call the function for the left and right side of the pivot position.
		quick_sort(left, pivot_index - 1);
		quick_sort(pivot_index + 1, right);
	}
	 

	void merge_sort(int left, int right) noexcept 
	{
		if (left < right) 
		{
			int middle = (left + right) / 2;
			merge_sort(left, middle);
			merge_sort(middle + 1, right);
			merge(left, right);
		}
	}


	void merge(int left, int right) 
	{
		auto dataAsT = asTArray();
		// Split the array in two
		// Calculate the lenght of the two arrays
		//int len2 = right - len1 + 1;
		
		int len1 = (right - left + 1) / 2; // Size of left subarray
		int len2 = right - left + 1 - len1; // Size of right subarray
		int mid = left + len1; // Midpoint index

		SmallVector <T, N / 2 + 1> leftSubArray;
		SmallVector <T, N / 2 + 1> rightSubArray;
		// Copy the data to the subArrays;
		//std::copy(m_begin + left, m_begin + left + len1, leftSubArray.begin());
		//std::copy(m_begin + left + len1, m_begin + right + 1, rightSubArray.begin());
		/**/

		// Create arrays for left and right subarrays
		//T leftSubArray[len1];
		//T rightSubArray[len2];
		//std::vector<T> leftSubArray(len1);
		//std::vector<T> rightSubArray(len2); 
		// Copy data from the main array to the subarrays
		for (int i = 0; i < len1; ++i)
		{
			leftSubArray.push_back(dataAsT[left + i]);
		}

		for (int i = 0; i < len2; ++i) 
		{
			rightSubArray.push_back(dataAsT[mid +1*0 + i]);
		}
		
		// Sort the sub Arrays 
		int l = 0, r = 0, i = left;

		while (l < len1 && r < len2)
		{
			if (leftSubArray[l] < rightSubArray[r]) 
			{
				dataAsT[i++] = leftSubArray[l++];
			}
			else 
			{
				dataAsT[i++] = rightSubArray[r++];
			}
		}
		// copy the rest of the data, one one array will still have data to be 
		// copied when the other reaches the end. 
		while (l < len1) 
		{
			dataAsT[i++] = leftSubArray[l++];
		}
		while (r < len1)
		{
			dataAsT[i++] = rightSubArray[r++];
		}
	}

private:
	/*** @Brief:Quick sort partition function. This function is used internally 
	* to sort the vector using quick sort.
	* @param:left index.
	* @param:right index.
	* @param:returns the pivot index, the pivot value is taken as data[right].
	* @return: pivot index. */
	int partition(int left, int right) noexcept
	{
		auto dataAsT = asTArray();
		auto pivot = dataAsT[right]; // set to last element
		int i = left - 1;

		for (int j = left; j < right - 1; j++)
		{
			if (dataAsT[j] < pivot)
			{
				i++;
				std::swap(dataAsT[i], dataAsT[j]);
			}
		}

		std::swap(dataAsT[i + 1], dataAsT[right]);
		return i + 1;
	}

	// Helper function to interpret m_data as an array of T
	T* asTArray() noexcept 
	{
		return reinterpret_cast<T*>(m_data);
	}

	const T* asTArray() const noexcept 
	{
		return reinterpret_cast<const T*>(m_data);
	}

	T* m_end{ nullptr };
	T* m_begin{ nullptr };
	size_t m_size{ 0 };
	char m_data[N * sizeof T]{ };
};

 