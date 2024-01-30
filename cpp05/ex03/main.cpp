
#include "Intern.hpp"

int main ()
{
	AForm *sc = NULL;
	AForm *rr = NULL;
	AForm *pp = NULL;
	try
	{
		srand(time(NULL));
		Intern someRandomIntern;
		Bureaucrat b1("test1", 136);
		Bureaucrat b2("test2", 30);
		Bureaucrat b3("test3", 1);
		sc = someRandomIntern.makeForm("shrubbery creation", "Bender");
		rr = someRandomIntern.makeForm("robotomy request", "Bender");
		pp = someRandomIntern.makeForm("presidential pardon", "Bender");
		
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
		if (sc)
		{
			delete sc;
			sc = NULL;
		}
		if (rr)
		{
			delete rr;
			rr = NULL;
		}
		if (pp)
		{
			delete pp;
			pp = NULL;
		}
	}
	catch(const std::exception& e)
	{
		if (sc)
		{
			delete sc;
			sc = NULL;
		}
		if (rr)
		{
			delete rr;
			rr = NULL;
		}
		if (pp)
		{
			delete pp;
			pp = NULL;
		}
		std::cerr << RED << e.what() << RESET << std::endl;
	}
	return 0;
}
