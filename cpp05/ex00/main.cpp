#include "Bureaucrat.hpp"

int main ()
{
	try
	{
		Bureaucrat a("test1111", 111);
		std::cout << a << std::endl;
		Bureaucrat b("test2222", 23);
		std::cout << b << std::endl;
		Bureaucrat c("test2222", 0);
		std::cout << c << std::endl;
		Bureaucrat d("test2222", 151);
		std::cout << d << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}