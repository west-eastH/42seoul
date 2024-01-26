#include "Form.hpp"

int main ()
{
	try
	{
		Form f1("testF1", 120, 120);
		std::cout << f1 << std::endl;
		Bureaucrat b1("testB1", 100);
		std::cout << b1 << std::endl;
		f1.beSigned(b1);
		std::cout << f1 << std::endl;
		Form f2("testF2", 1, 1);
		f2.beSigned(b1);
		std::cout << f2 << std::endl;
		Form fail("testF1", 152, 120);
	}
	catch(const std::exception& e)
	{
		std::cerr << RED << e.what() << RESET << std::endl;
	}
	return 0;
}
