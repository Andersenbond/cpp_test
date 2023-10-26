export module smallVector;

export template <typename T, int N> class SmallVector;

#include <ranges>
#include <iterator>
#include <iostream>


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
		if (index >= m_size)
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

 