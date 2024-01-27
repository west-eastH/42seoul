
#include "Intern.hpp"

int main ()
{
	try
	{
		srand(time(NULL));
		Intern someRandomIntern;
		Bureaucrat b1("test1", 136);
		Bureaucrat b2("test2", 30);
		Bureaucrat b3("test3", 1);
		AForm *sc = someRandomIntern.makeForm("shrubbery creation", "Bender");
		AForm *rr = someRandomIntern.makeForm("robotomy request", "Bender");
		AForm *pp = someRandomIntern.makeForm("presidential pardon", "Bender");
		
		std::cout << "=========================================" << std::endl << std::endl;
		b1.executeForm(*sc);
		b1.executeForm(*rr);
		b1.executeForm(*pp);
		std::cout << std::endl << "=========================================" << std::endl << std::endl;
		b2.executeForm(*sc);
		b2.executeForm(*rr);
		b2.executeForm(*pp);
		std::cout << std::endl << "=========================================" << std::endl << std::endl;
		b3.executeForm(*sc);
		b3.executeForm(*rr);
		b3.executeForm(*pp);
		std::cout << std::endl << "=========================================" << std::endl;
		delete sc;
		delete rr;
		delete pp;
	}
	catch(const std::exception& e)
	{
		std::cerr << RED << e.what() << RESET << std::endl;
	}
	return 0;
}
