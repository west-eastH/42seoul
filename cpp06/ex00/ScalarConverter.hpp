#pragma once

#include <iostream>
class ScalarConverter
{
	private:
		ScalarConverter();
		ScalarConverter(const ScalarConverter &origin);
		ScalarConverter& operator=(const ScalarConverter &origin);
		~ScalarConverter();
	public:
		static void convert(std::string literal);
};
