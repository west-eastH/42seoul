#pragma once

#include <iostream>
#include <algorithm>

#include <vector>
#include <deque>

class Span
{
	private:
		unsigned int _max;
		std::vector<int> _vec;
		Span();
		Span& operator=(const Span& origin);
	public:
		Span(unsigned int N);
		Span(const Span& origin);
		~Span();
		void addNumber(int val);
		int shortestSpan();
		int longestSpan();
		template<typename T>
		void insertRange(const T& container);
};

template<typename T>
void Span::insertRange(const T& container)
{
	if (_vec.size() + container.size() > _max)
		throw std::out_of_range("N elements are already stored!");
	_vec.insert(_vec.end(), container.begin(), container.end());
}
