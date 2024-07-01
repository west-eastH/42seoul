#include "BitcoinExchange.hpp"

int main(int argc, char *argv[])
{
	try
	{
		BitcoinExchange be(argc);
		be.start(argv[1]);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	return 0;
}