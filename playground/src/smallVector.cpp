#include <ranges>
#include <iostream>
#include <iterator>

#include "SmallVector.h"


template <typename T, int N>
SmallVector<T, N>::SmallVector() : m_size{ 0 }
{
	m_begin = static_cast<T*>(static_cast<void*>(m_data));
	m_end = static_cast<T*>(static_cast<void*>(m_data));
}

template <typename T, int N>
SmallVector<T, N>::SmallVector(const SmallVector& other)
{
	m_begin = static_cast<T*>(static_cast<void*>(m_data));
	//m_end = static_cast<T*>(static_cast<void*>(m_data));

	std::ranges::copy(other, std::back_inserter(*this));
	m_size = other.size();
	m_end = m_begin + m_size;
	//m_end = &m_data[m_size];
}


template <typename T, int N>
T& SmallVector<T, N>::operator[](size_t index)
{
	if (index >= m_size)
	{
		throw std::out_of_range("Index out of range");
	}
	return *static_cast<T*>(static_cast<void*>(&m_data[index * sizeof T]));
}


template <typename T, int N>
void SmallVector<T, N>::push_back(const T& val) noexcept
{
	if (m_size < N)
	{
		//	m_data[m_size * sizeof T] = val;
		*m_end = val;
		m_end++;
		m_size++;
	}
}

template <typename T, int N>
void SmallVector<T, N>::pop_back() noexcept
{
	if (m_size)
	{
		--m_end; // Adjust the end pointer
		--m_size; // Update the size
	}
}

template <typename T, int N>
size_t SmallVector<T, N>::size() const noexcept
{
	return m_size;
}

template <typename T, int N>
SmallVector<T, N>::iterator SmallVector<T, N>::begin() const noexcept
{
	return m_begin;
}

template <typename T, int N>
SmallVector<T, N>::iterator SmallVector<T, N>::end() const noexcept
{
	return m_end;
}

template <typename T, int N>
SmallVector<T, N>::const_iterator SmallVector<T, N>::cbegin() const noexcept
{
	return m_begin;
}

template <typename T, int N>
SmallVector<T, N>::const_iterator SmallVector<T, N>::cend() const noexcept
{
	return m_end;
}

template <typename T, int N>
template <typename... Args>
void SmallVector<T, N>::emplace_back(Args&&... args) noexcept
{
	if (m_size < N)
	{
		*m_end = T(std::forward<Args>(args)...); // Construct in-place
		++m_size; // Increment the size
		++m_end;
	}
}



void SmallVector<T, N>::partition(int left, int right) noexcept
{
	auto pivot = m_data[right]; // set to last element
	int i = left - 1;

	for (int j = left; j < right - 1; j++)
	{
		if (m_data[j] < pivot)
		{
			i++;
			std::swap(m_data[i], m_data[j]);
		}
	}

	std::swap(m_data[i + 1], m_data[right]);
	return i + 1;
}

void SmallVector<T, N>::qs_partition(int left, int right) noexcept
{
	while (left < right)
	{
		//if
	}
}


// Sorting Algorithms

void SmallVector<T, N>::quick_sort(int pivot_index) noexcept 
{
	int i = 0, j = -1;



}


