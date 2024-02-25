#include "Manager.hpp"

int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		std::cout << "input error" << std::endl;
		return (1);
	}
	Argument arg(argv);
	Manager manager(arg);
	manager.start();
	return (0);
}
