#pragma once

template <typename T, int N>
class SmallVector
{
public:
	using iterator = T*;
	using const_iterator = const T*;
	using value_type = T; // Add this typedef

	SmallVector();
	SmallVector(const SmallVector&);
	iterator begin() const noexcept;
	iterator end() const noexcept;
	const_iterator cbegin() const noexcept;
	const_iterator cend() const noexcept;
	T& operator[](size_t index);
	size_t size() const noexcept;
	void push_back(const T&) noexcept;
	void pop_back() noexcept;
	template <typename... Args> void emplace_back(Args&&... args) noexcept;

private:
	T* m_end{ nullptr };
	T* m_begin{ nullptr };
	size_t m_size{ 0 };
	char m_data[N * sizeof T] { };
};




