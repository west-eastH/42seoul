#include "PmergeMe.hpp"

PmergeMe::PmergeMe(int argc, char *argv[])
{
	if (!isValidArg(argc, argv))
		throw std::invalid_argument("invalid input.");
	
	for (int i = 1; i < argc; i++)
	{
		int value = std::atoi(argv[i]);
		_before_list.push_back(value);
		_before_deque.push_back(value);
	}
	printBefore();
}

void PmergeMe::printBefore()
{
	std::cout <<"Before: ";
	for (std::deque<int>::iterator it = _before_deque.begin(); it != _before_deque.end(); ++it)
        std::cout << *it << " ";
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

void PmergeMe::printAfter(double duration_list, double duration_deque)
{
    std::cout << "After:  ";
    for (std::deque<int>::iterator it = _mainChain_deque.begin(); it != _mainChain_deque.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

	std::cout << "Time to process a range of " << _before_list.size() << " elements with std::list: " << duration_list << " us" << std::endl;
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
	double start_list, end_list, duration_list;
	double start_deque, end_deque, duration_deque;

	start_deque = getTimeUS();
	setJacobsthal_deque();
	makePair_deque();

	if (_pairDeque.empty())
		_mainChain_deque.push_back(_isOdd);
	else
	{
		mergeSort_deque(_pairDeque, 0, _pairDeque.size() - 1);
		setMainChain_deque();
		insertionSort_deque();
	}

	end_deque = getTimeUS();
	duration_deque = end_deque - start_deque;

	printAfter(duration_list, duration_deque);
}

void PmergeMe::setJacobsthal_list()
{
	int n1, n2;

	n1 = 0;
	n2 = 1;

	while(_jacobsthal_list.size() < 33)
	{
		int temp = n2 + 2 * n1;
		_jacobsthal_list.push_back(temp);
		n1 = n2;
		n2 = temp;
	}
	_jacobsthal_list.push_back(2147483647);
}

void PmergeMe::setJacobsthal_deque()
{
	int n1, n2;

	n1 = 0;
	n2 = 1;

	while(_jacobsthal_deque.size() < 33)
	{
		int temp = n2 + 2 * n1;
		_jacobsthal_deque.push_back(temp);
		n1 = n2;
		n2 = temp;
	}
	_jacobsthal_deque.push_back(2147483647);
}

void PmergeMe::makePair_list()
{
	int first;
	int second;

	_isOdd = -1;
	if (_before_list.size() % 2 == 1)
	{
		_isOdd = _before_list.back();
		_before_list.pop_back();
	}

	std::list<int>::iterator it = _before_list.begin();
	while(it != _before_list.end())
	{
		first = *it;
		++it;
		if (it == _before_list.end())
			break;
		second = *it;
		++it;

		if (first >= second)
			_pairList.push_back(std::make_pair(first, second));
		else
			_pairList.push_back(std::make_pair(second, first));
	}
}

void PmergeMe::makePair_deque()
{
	int first;
	int second;

	_isOdd = -1;
	if (_before_deque.size() % 2 == 1)
	{
		_isOdd = _before_deque.back();
		_before_deque.pop_back();
	}

	for (size_t i = 0; i < _before_deque.size(); i += 2)
	{
		if (i + 1 < _before_deque.size())
		{
			first = _before_deque[i];
			second = _before_deque[i + 1];

			if (first >= second)
				_pairDeque.push_back(std::make_pair(first, second));
			else
				_pairDeque.push_back(std::make_pair(second, first));
		}
	}
}

void PmergeMe::mergeSort_list(std::list<p> &list, int low, int high)
{
	int mid;

	if (low < high)
	{
		mid = (low + high) / 2;
		mergeSort_list(list, low, mid);
		mergeSort_list(list, mid + 1, high);
		sortPair_list(list, low, high);
	}
}

void PmergeMe::mergeSort_deque(std::deque<p> &deque, int low, int high)
{
	int mid;

	if (low < high)
	{
		mid = (low + high) / 2;
		mergeSort_deque(deque, low, mid);
		mergeSort_deque(deque, mid + 1, high);
		sortPair_deque(deque, low, high);
	}
}

void PmergeMe::sortPair_list(std::list<p> &list, int low, int high)
{
	int i, j, mid;
	std::list<p> sorted;

	mid = (low + high) / 2;
	i = low;
	j = mid + 1;

	// 5 2 1 9 2 6 2 3 5 8  // 3 --- 1
	// (5 2) (9 1) (6 2) (3 2) // (8 5) --- 2
	// (9 1 5 2) (6 2 3 2) // --- 3
	// (9 1 5 2 6 2 3 2) // ---4
	// (6 2 3 2) (9 1 5 2) // --- 3
	// (3 2) (5 2) (6 2) (8 5) (9 1)	// --- 2
	// 3 5 6 8 9						// --- 1
	while(i <= mid && j <= high)
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

void PmergeMe::sortPair_deque(std::deque<p>& deque, int low, int high)
{
    int i, j, mid;
	std::deque<p> sorted;

	mid = (low + high) / 2;
	i = low;
	j = mid + 1;

    while (i <= mid && j <= high)
    {
        if (deque[i].first < deque[j].first)
        {
            sorted.push_back(deque[i]);
            i++;
        }
        else
        {
            sorted.push_back(deque[j]);
            j++;
        }
    }
    for (; i <= mid; i++)
        sorted.push_back(deque[i]);
    for (; j <= high; j++)
        sorted.push_back(deque[j]);
    for (int k = 0; k <= (high - low); ++k)
        deque[low + k] = sorted[k];
}

int PmergeMe::getListValue(std::list<p>& list, int idx, bool flag)
{
	int i;

	i = 0;
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
	int i;

	i = 0;
	for (std::list<int>::iterator it = list.begin(); it != list.end(); ++it)
    {
        if (i == idx)
            return *it;
        i++;
    }
    return -1;
}

std::pair<int, int>& PmergeMe::getListPair(std::list<p>& list, int idx)
{
    int i;

	i = 0;
    for (std::list<p>::iterator it = list.begin(); it != list.end(); ++it)
    {
        if (i == idx)
            return *it;
        i++;
    }
    return *list.end();
}

void PmergeMe::changeListPair(std::list<p>& origin, std::list<p> ref, int begin, int end)
{
    int j;
    size_t cnt;
	
	j = 0;
	cnt = end - begin + 1;
    for (size_t i = 0; i < cnt; i++)
    {
        j = 0;
        for (std::list<p>::iterator it = origin.begin(); it != origin.end(); ++it)
        {
            if (j == begin)
            {
                *it = getListPair(ref, i);
                begin++;
                break;
            }
            j++;
        }
    }
}

void PmergeMe::setMainChain_list()
{
    for (std::list<p>::iterator it = _pairList.begin(); it != _pairList.end(); ++it)
    {
        _mainChain_list.push_back(it->first);
        _pendingChain_list.push_back(it->second);
    }
}

void PmergeMe::setMainChain_deque()
{
    for (size_t i = 0; i < _pairDeque.size(); i++)
    {
        _mainChain_deque.push_back(_pairDeque[i].first);
        _pendingChain_deque.push_back(_pairDeque[i].second);
    }
}

void PmergeMe::insertValue_list(int value)
{
	std::list<int>::iterator insert_it = _mainChain_list.begin();
	while(insert_it != _mainChain_list.end() && *insert_it < value)
		++insert_it;
	_mainChain_list.insert(insert_it, value);
}

void PmergeMe::insertRemainValue_list(int prev)
{
	for (int i = _pendingChain_list.size(); i > prev; i--)
	{
		int value = getListValue(_pendingChain_list, i - 1);
		insertValue_list(value);
	}
}

void PmergeMe::insertionSort_list()
{
	int prev;
	std::list<int>::iterator jacob_it = _jacobsthal_list.begin();

	prev = 0;
	for (; jacob_it != _jacobsthal_list.end(); ++jacob_it)
	{
		size_t index = *jacob_it;
		if (index > _pendingChain_list.size())
		{
			insertRemainValue_list(prev);
			break;
		}
		for (int i = index; i > prev; i--)
		{
			int value = getListValue(_pendingChain_list, i - 1);
			insertValue_list(value);
		}
		prev = *jacob_it;
	}
	
	if (_isOdd != -1)
		insertValue_list(_isOdd);
}

void PmergeMe::insertValue_deque(int value)
{
	std::deque<int>::iterator insert_it = _mainChain_deque.begin();
	while (insert_it != _mainChain_deque.end() && *insert_it < value)
		++insert_it;
	_mainChain_deque.insert(insert_it, value);
}

void PmergeMe::insertRemainValue_deque(int prev)
{
	for (int i = _pendingChain_deque.size(); i > prev; i--)
	{
		int value = _pendingChain_deque[i - 1];
		insertValue_deque(value);
	}
}

void PmergeMe::insertionSort_deque()
{
	int prev;
    std::deque<int>::iterator jacob_it = _jacobsthal_deque.begin();

	prev = 0;
    for (; jacob_it != _jacobsthal_deque.end(); ++jacob_it)
    {
        size_t index = *jacob_it;
        if (index > _pendingChain_deque.size())
		{
            insertRemainValue_deque(prev);
			break;
		}
		for (int i = index; i > prev; i--)
		{
			int value = _pendingChain_deque[index - 1];
			insertValue_deque(value);
		}
		prev = *jacob_it;
    }

    if (_isOdd != -1)
		insertValue_deque(_isOdd);
}
#include <iostream>
#include <vector>
#include <algorithm>

// 두 벡터를 병합하는 함수
std::vector<int> mergeTwoChunks(const std::vector<int>& left, const std::vector<int>& right) {
    std::vector<int> result;
    size_t i = 0, j = 0;

    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j]) {
            result.push_back(left[i]);
            ++i;
        } else {
            result.push_back(right[j]);
            ++j;
        }
    }

    while (i < left.size()) {
        result.push_back(left[i]);
        ++i;
    }

    while (j < right.size()) {
        result.push_back(right[j]);
        ++j;
    }

    return result;
}

// 덩어리로 나누는 함수
std::vector<std::vector<int> > createChunks(const std::vector<int>& arr, int chunkSize) {
    std::vector<std::vector<int> > chunks;
    for (size_t i = 0; i < arr.size(); i += chunkSize) {
        std::vector<int> chunk;
        for (size_t j = i; j < i + chunkSize && j < arr.size(); ++j) {
            chunk.push_back(arr[j]);
        }
        chunks.push_back(chunk);
    }
    return chunks;
}

// 덩어리 정렬 함수
void chunkSort(std::vector<int>& arr) {
    int chunkSize = 1;

    while (chunkSize < arr.size()) {
        std::vector<std::vector<int> > chunks = createChunks(arr, chunkSize);

        std::vector<std::vector<int> > mergedChunks;

        for (size_t i = 0; i < chunks.size(); i += 2) {
            if (i + 1 < chunks.size()) {
                std::vector<int> mergedChunk = mergeTwoChunks(chunks[i], chunks[i + 1]);
                mergedChunks.push_back(mergedChunk);
            } else {
                mergedChunks.push_back(chunks[i]);
            }
        }

        arr.clear();
        for (size_t i = 0; i < mergedChunks.size(); ++i) {
            arr.insert(arr.end(), mergedChunks[i].begin(), mergedChunks[i].end());
        }

        chunkSize *= 2;
    }

    // 마지막 정렬
    std::sort(arr.begin(), arr.end());
}

int main() {
    int arr[] = {5, 2, 1, 9, 2, 6, 2, 3, 5, 8};
    int n = sizeof(arr) / sizeof(arr[0]);

    std::vector<int> vec(arr, arr + n);

    std::cout << "Original array: ";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    chunkSort(vec);

    std::cout << "Sorted array: ";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}