#include "ScalarConverter.hpp"

int main (int argc, char *argv[])
{
	if (argc != 2)
		return 1;
	try
	{
		ScalarConverter::convert(static_cast<std::string>(argv[1]));
	}
	catch(const int e)
	{
		std::cout << "char : impossible" << std::endl;
		std::cout << "int : impossible" << std::endl;
		std::cout << "float : impossible" << std::endl;
		std::cout << "double : impossible" << std::endl;
	}
	
	return 0;
}
