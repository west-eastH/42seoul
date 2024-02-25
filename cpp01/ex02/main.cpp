#include <iostream>
#include <string>

int main ()
{
	std::string STR;

	STR = "HI THIS IS BRAIN";
	std::string *PTR = &STR;
	std::string &REF = STR;

	std::cout << "STR address = " << &STR << std::endl;
	std::cout << "PTR address = " << PTR << std::endl;
	std::cout << "REF address = " << &REF << std::endl;

	std::cout << std::endl;

	std::cout << "STR data = " << STR << std::endl;
	std::cout << "PTR data = " << *PTR << std::endl;
	std::cout << "REF data = " << REF << std::endl;
	return (0);
}