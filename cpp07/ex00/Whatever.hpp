#pragma once

#include <iostream>

template <typename T>
static void swap(T& a, T& b)
{
	T temp;
	temp = a;
	a = b;
	b = temp;
}
template <typename T>
static T max(T& a, T& b)
{
	return a > b ? a : b;
}
template <typename T>
static T min(T& a, T& b)
{
	return a < b ? a : b;
}
