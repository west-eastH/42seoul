#include "Bureaucrat.hpp"

int main ()
{
	try
	{
		Bureaucrat a("test1111", 111);
		std::cout << a << std::endl;
		Bureaucrat b("test2222", 23);
		std::cout << b << std::endl;
		Bureaucrat c("test3333", 2);
		std::cout << c << std::endl;
		c.increaseGrade();
		std::cout << c << std::endl;
		std::cout << "==========error=========" << std::endl;
		c.increaseGrade();
		std::cout << c << std::endl;
		Bureaucrat d("test4444", 150);
		std::cout << d << std::endl;
		d.decreaseGrade();
		std::cout << d << std::endl;
		Bureaucrat e("test5555", 151);
		std::cout << e << std::endl;
		Bureaucrat f("test6666", 0);
		std::cout << f << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}