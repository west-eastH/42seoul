#pragma once

#include <iostream>

template<typename T>
void ft_print(const T& data)
{
	std::cout << data << std::endl;
}

template<typename T>
void iter(T* address, unsigned int length, void(*func)(T& data))
{
	for (size_t i = 0; i < length; i++)
		func(address[i]);
}

template<typename T>
void iter(const T* address, unsigned int length, void(*func)(const T& data))
{
	for (size_t i = 0; i < length; i++)
		func(address[i]);
}
