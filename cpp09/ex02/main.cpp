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
            pm.start();
        }
        catch (const std::exception &e)
        {
            std::cout << e.what() << '\n';
        }
    }
    return 0;
}