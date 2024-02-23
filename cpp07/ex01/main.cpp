#include "iter.hpp"

int main() {
	std::cout << "=====INT=====" << std::endl;
    int intArr[] = {1, 2, 3, 4, 5};
    iter(intArr, 5, ft_print);
	std::cout << "=====float=====" << std::endl;
	float floatArr[] = {1.1, 2.2, 3.3, 4.4, 5.5};
    iter(floatArr, 5, ft_print);
	std::cout << "=====string=====" << std::endl;
	std::string strArr[] = {"aaa", "bbb", "ccc", "ddd", "eee"};
    iter(strArr, 5, ft_print);
    return 0;
}
