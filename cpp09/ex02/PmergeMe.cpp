#include "PmergeMe.hpp"

void PmergeMe::printList()
{
	std::cout << "before : ";
	for (size_t i = 0; i < _before.size(); i++)
	{
		std::cout << _before[i] << " ";
	}
	std::cout << std::endl;
}

void PmergeMe::printMainChain()
{
	std::cout << "after : ";
	for (size_t i = 0; i < _mainChain.size(); i++)
		std::cout << getListValue(_mainChain, i) << " ";
	std::cout << std::endl;
}

PmergeMe::PmergeMe(int argc, char *argv[])
{
	if (!isValidArg(argc, argv))
		throw std::invalid_argument("invalid input.");
	printList();
}

PmergeMe::~PmergeMe()
{
}

bool PmergeMe::isValidArg(int argc, char *argv[])
{
	char *pEnd;
	for (size_t i = 1; i < static_cast<size_t>(argc); i++)
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
		_before.push_back(std::atoi(argv[i]));
	}
	return true;
}

void PmergeMe::start()
{
	setJacobsthal();
	makePairList();
	mergeSort(_pairList, 0, _pairList.size() - 1);
	setMainChain();
	insertionSort();
	printMainChain();

}

void PmergeMe::setMainChain()
{
	for (size_t i = 0; i < _pairList.size(); i++)
	{
		_mainChain.push_back(getListValue(_pairList, i, FIRST));
		_pendingChain.push_back(getListValue(_pairList, i, SECOND));
	}
}

void PmergeMe::insertionSort()
{
    _mainChain.push_front(getListValue(_pendingChain, 0));

    for (size_t i = 2; i < _jacobsthal.size(); i++)
    {
        size_t index = _jacobsthal[i];
        if (index >= _pendingChain.size())
            break;
        int value = getListValue(_pendingChain, index);

        std::list<int>::iterator it = _mainChain.begin();
        while (it != _mainChain.end() && *it < value)
        {
            ++it;
        }
        _mainChain.insert(it, value);
    }

    for (size_t i = 1; i < _pendingChain.size(); i++)
    {
        if (std::find(_jacobsthal.begin(), _jacobsthal.end(), i) == _jacobsthal.end())
        {
            int value = getListValue(_pendingChain, i);

            std::list<int>::iterator it = _mainChain.begin();
            while (it != _mainChain.end() && *it < value)
            {
                ++it;
            }
            _mainChain.insert(it, value);
        }
    }

    if (_isOdd != -1)
    {
        std::list<int>::iterator it = _mainChain.begin();
        while (it != _mainChain.end() && *it < _isOdd)
        {
            ++it;
        }
        _mainChain.insert(it, _isOdd);
    }
}


void PmergeMe::makePairList()
{
	_isOdd = -1;
	if (_before.size() % 2 == 1)
	{
		_isOdd = _before[_before.size() - 1];
		_before.pop_back();
	}
	for (size_t i = 0; i < _before.size(); i+=2)
	{
		if (_before[i] >= _before[i + 1])
			_pairList.push_back(std::make_pair(_before[i], _before[i + 1]));
		else
			_pairList.push_back(std::make_pair(_before[i + 1], _before[i]));
	}
}

int PmergeMe::getListValue(std::list<p>& list, int idx, bool flag)
{
	int i = 0;
	for (std::list<p>::iterator it = list.begin(); it != list.end(); ++it)
	{
		if (i == idx)
		{
			if (flag == FIRST)
				return it->first;
			else
				return it->second;
		}
		i++;
	}
	return -1;	
}

int PmergeMe::getListValue(std::list<int>& list, int idx)
{
	int i = 0;
	for (std::list<int>::iterator it = list.begin(); it != list.end(); ++it)
	{
		if (i == idx)
			return *it;
		i++;
	}
	return -1;
}

void PmergeMe::mergeSort(std::list<p> &list, int low, int high)
{
	if (low < high)
	{
		int mid = (low + high) / 2;
		mergeSort(list, low, mid);
		mergeSort(list, mid + 1, high);
		sortPair(list, low, high);
	}
}

void PmergeMe::sortPair(std::list<p> &list, int low, int high)
{
	std::list<p> sorted;
	int mid = (low + high) / 2;
	int i = low;
	int j = mid + 1;
	while (i <= mid && j <= high)
	{
		if (getListValue(list, i, FIRST) < getListValue(list, j, FIRST))
		{
			sorted.push_back(getListPair(list, i));
			i++;
		}
		else
		{
			sorted.push_back(getListPair(list, j));
			j++;
		}
	}
	for (; i <= mid; i++)
		sorted.push_back(getListPair(list, i));
	for (; j <= high; j++)
		sorted.push_back(getListPair(list, j));
	changeListPair(list, sorted, low, high);
}
std::pair<int, int>& PmergeMe::getListPair(std::list<p>& list, int idx)
{
	int i = 0;
	for (std::list<p>::iterator it = list.begin(); it != list.end(); ++it)
	{
		if (i == idx)
			return *it;
		i++;
	}
	return *list.end();
}

void PmergeMe::setJacobsthal()
{
    int n1 = 0;
    int n2 = 1;
    _jacobsthal.push_back(n1);
    _jacobsthal.push_back(n2);

    while (_jacobsthal.size() < 33)
    {
        int temp = n2 + 2 * n1;
        _jacobsthal.push_back(temp);
        n1 = n2;
        n2 = temp;
    }

    _jacobsthal.push_back(2147483647);
}
void PmergeMe::changeListPair(std::list<p>& origin, std::list<p> ref, int begin, int end)
{
	int j = 0;
	size_t cnt = end - begin + 1;
	for (size_t i = 0; i < cnt; i++)
	{
		j = 0;
		for (std::list<p>::iterator it = origin.begin(); it != origin.end(); ++it)
		{
			if (j == begin)
			{
				*it = getListPair(ref, i);
				begin++;
				break ;
			}
			j++;
		}
	}
}