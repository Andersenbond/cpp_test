module;

#include <initializer_list>
#include <iterator>
#include <iostream>
#include <ranges>
#include <stdexcept>
#include <vector>

export module smallVector;
export template <typename T, int N> class SmallVector;

/**
 * @brief A small fixed-size vector class template.
 *
 * This class template provides a container for storing a fixed number of
 * elements of type T. It supports various operations like insertion, access,
 * sorting, and more.
 *
 * @tparam T The type of elements to store in the SmallVector.
 * @tparam N The maximum number of elements the SmallVector can hold.
 */
template <typename T, int N> class SmallVector
{
public:
	/**
	 * @brief Define iterator type aliases.
	 */
	using iterator = T*;
	using const_iterator = const T*;

	/*** @Brief: Define value_type alias, required by std::ranges. */
	using value_type = T;

	/*** @Brief: Class constructor */
	SmallVector() : m_size{ 0 }
	{
		m_begin = m_data;
		m_end = m_data;
	}

	/*** @Brief: Class constructor 
	* @param initial size. This allow us to overwrite the values 
	* using the [] operator.
	* */
  	SmallVector(size_t size) : m_size{ size }
	{
		m_begin = m_data;
		m_end = m_begin + m_size;
	}

	/*** @Brief: Copy constructor 
	 * @param: reference to the copy object.
	 * @return: none */
	SmallVector(const SmallVector& other)
	{
		m_begin = m_data;
		m_end = m_begin + m_size;

		std::ranges::copy(other, std::back_inserter(*this));
		m_size = other.size();
	}

	/*** @Brief: Initializer List constructor
	* @param: initializer list of T elements.
	* @return: none */
	SmallVector(std::initializer_list<T> list) : m_begin {m_data}, m_end{ m_data }
	{
		if (list.size() > N) { return; }

 		// Initialize the vector using the elements from the initializer list
		int i = 0;
		for (const auto& element : list) 
		{
			m_data[i++] = element;
		}
		m_end += list.size();
		m_size = list.size(); 
	}

	/*** @Brief: Array begin iterator get function.
	 * @param:none.
	 * @return: returs array begin iterator. */
	[[ nodiscard ]] iterator begin() const noexcept { return m_begin; }


	/*** @Brief: Array end iterator get function.
	 * @param:none.
	 * @return: returs array end iterator. */
	[[ nodiscard ]] iterator end() const noexcept { return m_end; }

	/*** @Brief: Array end iterator get function.
	 * @param:none.
	 * @return: returs const reference to array begin iterator. */
	[[ nodiscard ]] const_iterator cbegin() const noexcept { return m_begin; }
	
	/*** @Brief: Array end iterator get function.
	 * @param:none.
	 * @return: returs const reference to array end iterator. */
	[[ nodiscard ]] const_iterator cend() const noexcept { return m_begin; }
	
	/*** @Brief: Implements array [] operator.
	 * @param:index of the element.
	 * @return: returs the element at index, if index is out of range 
	 * the function throw a std::out_of_range exception. */
	[[ nodiscard ]] T& operator[](size_t index) 
	{
		if (index >= m_size)
		{
			throw std::out_of_range("Index out of range");
		}
		return m_data[index];
	}

	/*** @Brief: Implements array [] operator.
 * @param:index of the element.
 * @return: returs the element at index, if index is out of range
 * the function throw a std::out_of_range exception. */
	[[ nodiscard ]] const T& operator[](size_t index) const
	{
		if (index >= m_size)
		{
			throw std::out_of_range("Index out of range");
		}
		return m_data[index];
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
			m_data[m_size] = val;
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
	 

	void merge_sort(int left = 0, int right = -1) noexcept 
	{
		right = right == -1 ? m_size - 1 : right;

		if (left < right) 
		{
			int middle = (left + right) / 2;
			merge_sort(left, middle);
			merge_sort(middle + 1, right);
			merge(left, right);
		}
	}


	void heap_sort() noexcept
	{	
		SmallVector<T, N> arr;
		// first convert our array to a binary tree where the node value is 
		// always higher than its childs
		for (int i = 0; i < N; i++)
		{
			heap_insert(arr, m_data[i]);
		}

		// Sort the max heap
		int unsorted_elements = static_cast<int>(arr.size() - 1);

		while (unsorted_elements > 0) 
		{
			heapify_max_representation(arr, unsorted_elements);
		}

		// now we sort our array by sending the root (highest element) to the
		//  end and heapifying the array afterwards
		// heapify_max_representation(arr, arr.size() - 1);

		// TODO: find a workaroung to not have to do this copy.
		// 
		// Copy the sorted elements back to the original array
		for(int i = 0; i < arr.size(); i++)
		{
			m_data[i] = arr[i];
		}	
	}


	void heap_insert(SmallVector<T, N>& arr, T value) 
	{
		// Get the parent of the node to be inserted

		std::size_t value_index = arr.size();
		std::size_t parent_index = (value_index - 1) / 2;
		// insert the node
		arr.push_back(value);

		// make sure none of the parents are 
		// bigger than the inserted node
		while (value_index > 0 && arr[value_index] > arr[parent_index]) 
		{
			std::swap(arr[value_index], arr[parent_index]);
			value_index = parent_index;
			parent_index = (value_index - 1) / 2;
		}
	}

	void heapify_max_representation(SmallVector<T, N>& arr, int& unsorted_elements)
	{
		if (unsorted_elements > 0) 
		{
			// First we swap the root with the last element in the array 
			std::swap(arr[0], arr[unsorted_elements]);

			// since the the root is the highest element in the array this swap sorts it
			// with that we need to decrement the unsorted_elements by 1.
			unsorted_elements--;

			// now we need to update the array in case our previous swap changes the 
			// array to be in the max representation
			int node_index = 0, child_l_index = 1, child_r_index = 2;

			while (node_index < unsorted_elements) 
			{
				int largest = node_index;
				if (child_l_index <= unsorted_elements && arr[child_l_index] > arr[largest]) 
				{
					largest = child_l_index;
				}
				if (child_r_index <= unsorted_elements && arr[child_r_index] > arr[largest]) {
					largest = child_r_index;
				}

				if (largest != node_index) 
				{
					std::swap(arr[node_index], arr[largest]);
					node_index = largest;
					child_l_index = 2 * node_index + 1;
					child_r_index = 2 * node_index + 2;
				}
				else 
				{
					// if no swap needed the array is already in the max representation.
					break;
				}
			}
		}
	}

	void heap_insert2(SmallVector<T, N>& arr, T value)
	{
		int len = arr.size();

		if (len == 0)
		{
			arr.push_back(value);
			return;
		}
		// go down the tree and insert the element so that 
		// each node is greater than or equal to the values 
		// of its children.
		int node_index = 0; 

		while (node_index < len) 
		{
			if (arr[node_index] > value) 
			{
				node_index++;
			}
			else 
			{
				std::swap(arr[node_index], value);
				heap_insert(arr, value);
				return;
			}
		}
		arr.push_back(value);
	}

	void stdout_dump(char delimiter = ' ') 
	{
		for(const auto & value : *this)
		{
			std::cout << value << delimiter;
		}
		std::cout << std::endl;
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

	/*** @Brief:Merge sort merge function. This function is used internally
	* to sort the vector using merge sort.
	* @param:left index.
	* @param:right index.
	* @return:returns the pivot index, the pivot value is taken as data[right],
	* the return value is the final position after the sort.
	* */
	void merge(int left, int right)
	{
		auto dataAsT = asTArray();
		// Split the array in two
		// Calculate the lenght of the two arrays
		int len1 = (right - left + 1) / 2; // Size of left subarray
		int len2 = right - left + 1 - len1; // Size of right subarray
		int mid = left + len1; // Midpoint index

		SmallVector <T, N / 2 + 1> leftSubArray(len1);
		SmallVector <T, N / 2 + 1> rightSubArray(len2);

		// Copy the data to the subArrays;
		for (int i = 0; i < len1; ++i)
		{
			leftSubArray[i] = dataAsT[left + i];
		}

		for (int i = 0; i < len2; ++i)
		{
			rightSubArray[i] = dataAsT[mid + i];
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
	T m_data[N]{ };
};

 