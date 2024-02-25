#include "BitcoinExchange.hpp"

int main (int argc, char *argv[])
{
	try
	{
		BitcoinExchange btc(argc, argv);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return 0;
}