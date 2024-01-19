#include "Form.hpp"

int main ()
{
	try
	{
		Form f1;
		Bureaucrat b1;
		f1.beSigned(b1);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return 0;
}