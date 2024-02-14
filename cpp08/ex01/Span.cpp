#include "Span.hpp"

Span::Span() {}
Span &Span::operator=(const Span &origin)
{
	_max = origin._max;
	_vec = origin._vec;
	return *this;
}

Span::Span(unsigned int N) : _max(N) {}

Span::Span(const Span &origin)
{
	_max = origin._max;
	_vec = origin._vec;
}

Span::~Span() {}

void Span::addNumber(int val)
{
	if (_vec.size() == _max)
		throw std::out_of_range("N elements are already stored!");
	_vec.push_back(val);
}

int Span::shortestSpan()
{
	int min;

	if (_vec.size() < 2)
		throw std::out_of_range("Not enough numbers stored!");
	std::vector<int>copy = _vec;
	std::sort(copy.begin(), copy.end());
	min = copy[1] - copy[0];
	for (std::vector<int>::iterator it = copy.begin(); it != copy.end() - 1; ++it)
	{
		int tempMin = *(it + 1) - *it;
		if (min > tempMin)
			min = tempMin;
	}
	return min;
}

int Span::longestSpan()
{
	if (_vec.size() < 2)
		throw std::out_of_range("Not enough numbers stored!");
	std::vector<int>copy = _vec;
	std::sort(copy.begin(), copy.end());
	return copy.back() - copy.front();
}
