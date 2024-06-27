#include "PmergeMe.hpp"
#include <ctime>
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        try
        {
            PmergeMe pm(argc, argv);
            clock_t start = clock();
            pm.start();
            clock_t end = clock();
            double list = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;

            std::cout << "Time to process a range of " << argc - 1 << " elements with std::list: " << list << " us" << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cout << e.what() << '\n';
        }
    }
    return 0;
}