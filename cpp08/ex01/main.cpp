#include "Span.hpp"

int main()
{
	try
	{
		Span sp = Span(5);
		sp.addNumber(6);
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);
		std::cout << sp.shortestSpan() << std::endl;
		std::cout << sp.longestSpan() << std::endl;

		Span test1(10000);
		std::vector<int> t_vec;
		for (size_t i = 0; i < 10000; i++)
			t_vec.push_back(i);
		test1.insertRange(t_vec);
		std::cout << test1.shortestSpan() << std::endl;
		std::cout << test1.longestSpan() << std::endl;
		
		Span test2(10000);
		std::deque<int> t_dq;
		for (size_t i = 0; i < 10000; i++)
			t_dq.push_back(i);
		test2.insertRange(t_dq);
		std::cout << test2.shortestSpan() << std::endl;
		std::cout << test2.longestSpan() << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
return 0;
}