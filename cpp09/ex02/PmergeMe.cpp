#include "PmergeMe.hpp"

PmergeMe::PmergeMe(int argc, char *argv[])
{
	if (!isValidArg(argc, argv))
		throw std::invalid_argument("invalid input.");
	
	for (int i = 1; i < argc; i++)
	{
		int value = std::atoi(argv[i]);
		_before_vector.push_back(value);
		_before_deque.push_back(value);
	}
	printBefore();
}

PmergeMe::~PmergeMe(){}

void PmergeMe::printBefore()
{
	std::cout <<"Before: ";
	for (size_t i = 0; i < _before_vector.size(); i++)
        std::cout << _before_vector[i] << " ";
	std::cout << std::endl;
}

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

void PmergeMe::printAfter(double duration_vector, double duration_deque, std::vector<int> vec)
{
    std::cout << "After:  ";
    for (size_t i = 0; i < vec.size(); i++)
        std::cout << vec[i] << " ";
    std::cout << std::endl;
	std::cout << "Time to process a range of " << _before_vector.size() << " elements with std::vector: " << duration_vector << " us" << std::endl;
    std::cout << "Time to process a range of " << _before_deque.size() << " elements with std::deque: " << duration_deque << " us" << std::endl;
}

double PmergeMe::getTimeUS()
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000 + tv.tv_usec;
}

void PmergeMe::start()
{
	double start_vector, end_vector, duration_vector;
	double start_deque, end_deque, duration_deque;
	std::vector<int> result_vector;
	std::deque<int> result_deque;

	setJacobsthal_vector();
	start_vector = getTimeUS();
	result_vector = mergeSortStart_vector(_before_vector);
	end_vector = getTimeUS();
	duration_vector = end_vector - start_vector;

	setJacobsthal_deque();
	start_deque = getTimeUS();
	result_deque = mergeSortStart_deque(_before_deque);
	end_deque = getTimeUS();
	duration_deque = end_deque - start_deque;

	printAfter(duration_vector, duration_deque, result_vector);
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

void PmergeMe::setJacobsthal_deque()
{
	int n1, n2;

	n1 = 0;
	n2 = 1;

	while(_jacobsthal_deque.size() < 31)
	{
		int temp = n2 + 2 * n1;
		_jacobsthal_deque.push_back(temp);
		n1 = n2;
		n2 = temp;
	}
	_jacobsthal_deque.push_back(2147483647);
}

std::vector<int> PmergeMe::mergeSortStart_vector(std::vector<int> &vec)
{
	vv start_vector;
	vv sorted;
	std::vector<int> result;

	for (size_t i = 0; i < vec.size(); i++)
	{
		std::vector<int> temp;
		temp.push_back(vec[i]);
		start_vector.push_back(temp);
	}
	sorted = mergeSort_vector(start_vector, 1);
	for (size_t i = 0; i < sorted.size(); i++)
		result.push_back(sorted[i][0]);
	return result;
}

std::deque<int> PmergeMe::mergeSortStart_deque(std::deque<int> &deq)
{
	dd start_deque;
	dd sorted;
	std::deque<int> result;

	for (size_t i = 0; i < deq.size(); i++)
	{
		std::deque<int> temp;
		temp.push_back(deq[i]);
		start_deque.push_back(temp);
	}
	sorted = mergeSort_deque(start_deque, 1);
	for (size_t i = 0; i < sorted.size(); i++)
		result.push_back(sorted[i][0]);
	return result;
}

int PmergeMe::binaryInsertValue_vector(vv& mainChain, int left, int right, std::vector<int>& target)
{
	while (left <= right)
	{
		int mid = (left + right) / 2;
		if (mainChain[mid].front() > target.front())
			right = mid - 1;
		else if (mainChain[mid].front() < target.front())
			left = mid + 1;
		else
			return mid;
	}
	return left;
}

int PmergeMe::binaryInsertValue_deque(dd& mainChain, int left, int right, std::deque<int>& target)
{
	while (left <= right)
	{
		int mid = (left + right) / 2;
		if (mainChain[mid].front() > target.front())
			right = mid - 1;
		else if (mainChain[mid].front() < target.front())
			left = mid + 1;
		else
			return mid;
	}
	return left;
}

std::vector<int> PmergeMe::merge_vector(std::vector<int>& v1, std::vector<int>& v2, size_t cnt)
{
	std::vector<int> result;
	if (v1.front() > v2.front())
	{
		for (size_t i = 0; i < cnt; i++)
			result.push_back(v1[i]);
		for (size_t i = 0; i < cnt; i++)
			result.push_back(v2[i]);
	}
	else
	{
		for (size_t i = 0; i < cnt; i++)
			result.push_back(v2[i]);
		for (size_t i = 0; i < cnt; i++)
			result.push_back(v1[i]);
	}
	return result;
}

std::deque<int> PmergeMe::merge_deque(std::deque<int>& d1, std::deque<int>& d2, size_t cnt)
{
	std::deque<int> result;

	if (d1.front() > d2.front())
	{
		for (size_t i = 0; i < cnt; i++)
			result.push_back(d1[i]);
		for (size_t i = 0; i < cnt; i++)
			result.push_back(d2[i]);
	}
	else
	{
		for (size_t i = 0; i < cnt; i++)
			result.push_back(d2[i]);
		for (size_t i = 0; i < cnt; i++)
			result.push_back(d1[i]);
	}
	return result;
}

void PmergeMe::makeSorted_vector(vv& sorted, vv& mainChain, vv& pendingChain, size_t cnt)
{
	std::vector<int> temp;
	for (size_t i = 0; i < sorted.size(); i++)
	{
		temp.clear();
		for (size_t j = 0; j < cnt; j++)
			temp.push_back(sorted[i][j]);
		mainChain.push_back(temp);

		temp.clear();
		for (size_t j = cnt; j < sorted[i].size(); j++)
			temp.push_back(sorted[i][j]);
		pendingChain.push_back(temp);
	}
}

void PmergeMe::makeSorted_deque(dd& sorted, dd& mainChain, dd& pendingChain, size_t cnt)
{
	std::deque<int> temp;
	for (size_t i = 0; i < sorted.size(); i++)
	{
		temp.clear();
		for (size_t j = 0; j < cnt; j++)
			temp.push_back(sorted[i][j]);
		mainChain.push_back(temp);

		temp.clear();
		for (size_t j = cnt; j < sorted[i].size(); j++)
			temp.push_back(sorted[i][j]);
		pendingChain.push_back(temp);
	}
}

// before = 5 2 1 9 2 6 2 3 5 8 3 size = 11
// 5 2 1 9 2 6 2 3 5 8  // 나머지 : 3 --- 1레벨
// (5 2) (9 1) (6 2) (3 2) // 나머지 : (8 5) --- 2레벨
// (9 1 5 2) (6 2 3 2) // --- 3레벨
// (9 1 5 2 6 2 3 2) // --- 4레벨
// (6 2 3 2) (9 1 5 2) // --- 3레벨
// (3 2) (5 2) (6 2) (8 5) (9 1) // --- 2레벨
// 1 2 2 2 3 3 5 5 6 8 9		// --- 1레벨

vv PmergeMe::mergeSort_vector(vv& vec, size_t cnt)
{
	vv isOdd;
	vv temp;
	vv mainChain;
	vv pendingChain;
	vv sorted;
	size_t size = vec.size();

	if (vec.size() == 1)
		return vec;

	if (size % 2 != 0)
	{
		isOdd.push_back(vec.back());
		vec.pop_back();
	}
	for (size_t i = 0; i < size - 1; i+=2)
		temp.push_back(merge_vector(vec[i], vec[i + 1], cnt));
	
	sorted = mergeSort_vector(temp, cnt * 2);
	makeSorted_vector(sorted, mainChain, pendingChain, cnt);
	
	if (!isOdd.empty())
		pendingChain.push_back(isOdd[0]);
	return insertionSort_vector(mainChain, pendingChain);
}

dd PmergeMe::mergeSort_deque(dd& deq, size_t cnt)
{
	dd isOdd;
	dd temp;
	dd mainChain;
	dd pendingChain;
	dd sorted;
	size_t size = deq.size();

	if (deq.size() == 1)
		return deq;

	if (size % 2 != 0)
	{
		isOdd.push_back(deq.back());
		deq.pop_back();
	}
	for (size_t i = 0; i < size - 1; i+=2)
		temp.push_back(merge_deque(deq[i], deq[i + 1], cnt));
	sorted = mergeSort_deque(temp, cnt * 2);
	makeSorted_deque(sorted, mainChain, pendingChain, cnt);
	
	if (!isOdd.empty())
		pendingChain.push_back(isOdd[0]);
	return insertionSort_deque(mainChain, pendingChain);
}

void PmergeMe::insertRemainValue_vector(int prev, vv& mainChain, vv& pendingChain)
{
	for (int i = pendingChain.size(); i > prev; i--)
	{
		std::vector<int> target = pendingChain[i - 1];
		int idx = binaryInsertValue_vector(mainChain, 0, mainChain.size() - 1, target);
		mainChain.insert(mainChain.begin() + idx, target);
	}
}

void PmergeMe::insertRemainValue_deque(int prev, dd& mainChain, dd& pendingChain)
{
	for (int i = pendingChain.size(); i > prev; i--)
	{
		std::deque<int> target = pendingChain[i - 1];
		int idx = binaryInsertValue_deque(mainChain, 0, mainChain.size() - 1, target);
		mainChain.insert(mainChain.begin() + idx, target);
	}
}

vv PmergeMe::insertionSort_vector(vv& mainChain, vv& pendingChain)
{
	int prev;
    std::vector<int>::iterator jacob_it = _jacobsthal_vector.begin();

	prev = 0;
    for (; jacob_it != _jacobsthal_vector.end(); ++jacob_it)
    {
        size_t index = *jacob_it;
        if (index > pendingChain.size())
		{
            insertRemainValue_vector(prev, mainChain, pendingChain);
			break;
		}
		for (int i = index; i > prev; i--)
		{
			std::vector<int> target = pendingChain[i - 1];
			int insertIdx = binaryInsertValue_vector(mainChain, 0, mainChain.size() - 1, target);
			mainChain.insert(mainChain.begin() + insertIdx, target);
		}
		prev = *jacob_it;
    }
	return mainChain;
}

dd PmergeMe::insertionSort_deque(dd& mainChain, dd& pendingChain)
{
	int prev;
    std::deque<int>::iterator jacob_it = _jacobsthal_deque.begin();

	prev = 0;
    for (; jacob_it != _jacobsthal_deque.end(); ++jacob_it)
    {
        size_t index = *jacob_it;
        if (index > pendingChain.size())
		{
            insertRemainValue_deque(prev, mainChain, pendingChain);
			break;
		}
		for (int i = index; i > prev; i--)
		{
			std::deque<int> target = pendingChain[i - 1];
			int insertIdx = binaryInsertValue_deque(mainChain, 0, mainChain.size() - 1, target);
			mainChain.insert(mainChain.begin() + insertIdx, target);
		}
		prev = *jacob_it;
    }
	return mainChain;
}
