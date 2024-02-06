#pragma once

#include <iostream>

class Whatever
{
	private:
		Whatever();
		~Whatever();
		Whatever(const Whatever& origin);
		Whatever& operator=(const Whatever& origin);
	public:
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
};
