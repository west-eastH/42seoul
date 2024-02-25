#include "Harl.hpp"

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cout << "Input error" << std::endl;
		return 1;
	}
	Harl harl(argv);
	harl.complain();
	return (0);
}
