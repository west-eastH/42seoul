#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <deque>

template<typename T>
typename T::iterator easyfind(T& container, int value)
{
	typename T::iterator it;
	it = std::find(container.begin(), container.end(), value);
	if (it == container.end())
		throw std::out_of_range("Out of range!!");
	return it;
}
