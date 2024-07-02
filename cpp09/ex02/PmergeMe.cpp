#include "PmergeMe.hpp"

PmergeMe::PmergeMe(int argc, char *argv[])
{
	if (!isValidArg(argc, argv))
		throw std::invalid_argument("invalid input.");
	
	for (int i = 1; i < argc; i++)
	{
		int value = std::atoi(argv[i]);
		_before_vector.push_back(value);
	}
	printBefore();
}

void PmergeMe::printBefore()
{
	std::cout <<"Before: ";
	for (size_t i = 0; i < _before_vector.size(); i++)
        std::cout << _before_vector[i] << " ";
	std::cout << std::endl;
}

PmergeMe::~PmergeMe(){}

bool PmergeMe::isValidArg(int argc, char *argv[])
{
	char *pEnd;
	
	for (int i = 1; i < argc; i++)
	{
		std::string temp = argv[i];
		for (size_t j = 0; j < temp.length(); j++)
		{
			if (!isdigit(temp[j]))
				return false;
		}
		double val = std::strtod(argv[i], &pEnd);
		if (val > 2147483647)
			return false;
	}
	return true;
}

void PmergeMe::start()
{
	setJacobsthal_vector();
	mergeSortStart_vector(_before_vector);
}

void PmergeMe::setJacobsthal_vector()
{
	int n1, n2;

	n1 = 0;
	n2 = 1;

	while(_jacobsthal_vector.size() < 31)
	{
		int temp = n2 + 2 * n1;
		_jacobsthal_vector.push_back(temp);
		n1 = n2;
		n2 = temp;
	}
	_jacobsthal_vector.push_back(2147483647);
}

void PmergeMe::mergeSortStart_vector(std::vector<int> &vec)
{
	vv start_vector;

	for (size_t i = 0; i < vec.size(); i++)
	{
		std::vector<int> temp;
		temp.push_back(vec[i]);
		start_vector.push_back(temp);
	}
	mergeSort_vector(start_vector, 1);
}

std::vector<int> PmergeMe::merge_vec(std::vector<int>& v1, std::vector<int>& v2, size_t depth)
{
	std::vector<int> result;

	if (v1.front() > v2.front())
	{
		for (size_t i = 0; i < depth; i++)
			result.push_back(v1[i]);
		for (size_t i = 0; i < depth; i++)
			result.push_back(v2[i]);
		// result.insert(result.end(), v1.begin(), v1.end());
		// result.insert(result.end(), v2.begin(), v2.end());
	}
	else
	{
		for (size_t i = 0; i < depth; i++)
			result.push_back(v2[i]);
		for (size_t i = 0; i < depth; i++)
			result.push_back(v1[i]);
		// result.insert(result.end(), v2.begin(), v2.end());
		// result.insert(result.end(), v1.begin(), v1.end());
	}
	return result;
}
// before = 5 2 1 9 2 6 2 3 5 8 3 size = 11
// 5 2 1 9 2 6 2 3 5 8  // 나머지 : 3 --- 1레벨
// (5 2) (9 1) (6 2) (3 2) // 나머지 : (8 5) --- 2레벨
// (9 1 5 2) (6 2 3 2) // --- 3레벨
// (9 1 5 2 6 2 3 2) // --- 4레벨
// (6 2 3 2) (9 1 5 2) // --- 3레벨
// (3 2) (5 2) (6 2) (8 5) (9 1) // --- 2레벨
// 1 2 2 2 3 3 5 5 6 8 9		// --- 1레벨

void PmergeMe::mergeSort_vector(vv& vec, size_t depth)
{
	vv isOdd;
	vv temp;
	vv sorted;
	size_t size = vec.size();

	if (vec.size() == 1)
	{
		for (size_t i = 0; i < vec[0].size(); i++)
		{
			std::cout << vec[0][i] << " ";
		}
		std::cout << std::endl;
		return ;
		
	}

	if (size % 2 != 0)
	{
		isOdd.push_back(vec.back());
		vec.pop_back();
	}
	for (size_t i = 0; i < size - 1; i+=2)
		temp.push_back(merge_vec(vec[i], vec[i + 1], depth));
	mergeSort_vector(temp, depth * 2);
	my_sort(temp);
}

void PmergeMe::my_sort(vv vec)
{
	for (size_t i = 0; i < count; i++)
	{
		/* code */
	}
	
}