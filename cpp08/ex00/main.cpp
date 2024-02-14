#include "easyfind.hpp"

int main()
{
	try
	{
		std::cout << "===================vector========================" << std::endl;
		std::vector<int> vec;
		vec.push_back(1);
		vec.push_back(2);
		vec.push_back(3);
		std::cout << *easyfind(vec, 1) << std::endl;
		std::cout << *easyfind(vec, 2) << std::endl;
		std::cout << *easyfind(vec, 3) << std::endl;

		std::cout << "===================list========================" << std::endl;

		std::list<int> list;
		list.push_back(1);
		list.push_back(2);
		list.push_back(3);
		std::cout << *easyfind(list, 1) << std::endl;
		std::cout << *easyfind(list, 2) << std::endl;
		std::cout << *easyfind(list, 3) << std::endl;

		std::cout << "===================deque========================" << std::endl;

		std::deque<int> dq;
		dq.push_back(1);
		dq.push_back(2);
		dq.push_back(3);
		std::cout << *easyfind(dq, 1) << std::endl;
		std::cout << *easyfind(dq, 2) << std::endl;
		std::cout << *easyfind(dq, 3) << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}	
	return 0;
}
