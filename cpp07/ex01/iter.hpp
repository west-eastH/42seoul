#pragma once

#include <iostream>

template<typename T>
void ft_print(const T data)
{
	std::cout << data << std::endl;
}

template<typename T>
void ft_double(T& data)
{
	data += data;
}

template<typename T1, typename T2>
void iter(T1* address, unsigned int length, void(*func)(T2 data))
{
	for (size_t i = 0; i < length; i++)
		func(address[i]);
}
