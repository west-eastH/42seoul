#pragma once

#include <iostream>

template<typename T>
class Array
{
	private:
		T* _data;
		unsigned int _size;
	public:
		Array();
		Array(unsigned int n);
		~Array();
		Array(const Array& origin);
		Array& operator=(const Array& origin);
		unsigned int size() const;
		T& operator[](unsigned int n);
		const T& operator[](unsigned int n) const;
};

template<typename T>
Array<T>::Array()
{
	_size = 0;
	_data = new T();
}

template<typename T>
Array<T>::~Array()
{
	delete[] _data;
}

template<typename T>
Array<T>::Array(unsigned int n)
{
	_size = n;
	_data = new T[n];
}

template<typename T>
Array<T>::Array(const Array& origin)
{
	_size = origin.size();
	_data = new T[origin.size()];
	for (size_t i = 0; i < origin.size(); i++)
	{
		_data[i] = origin._data[i];
		_size++;
	}
}

template<typename T>
Array<T>& Array<T>::operator=(const Array& origin)
{
	delete _data;
	_size = origin.size();
	_data = new T[origin.size()];
	for (size_t i = 0; i < origin.size(); i++)
	{
		_data[i] = origin[i];
		_size++;
	}
	return *this;
}

template<typename T>
unsigned int Array<T>::size() const
{
	return _size;
}

template<typename T>
T& Array<T>::operator[](unsigned int n)
{
	if (n < 0 || n > _size)
		throw std::out_of_range("out of range!!");
	return _data[n];
}

template<typename T>
const T& Array<T>::operator[](unsigned int n) const
{
	if (n < 0 || n > _size)
		throw std::out_of_range("out of range!!");
	return _data[n];
}