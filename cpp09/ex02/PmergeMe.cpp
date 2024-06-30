#include "PmergeMe.hpp"

PmergeMe::PmergeMe(int argc, char *argv[])
{
    if (!isValidArg(argc, argv))
        throw std::invalid_argument("invalid input.");

    for (int i = 1; i < argc; ++i)
    {
        int value = std::atoi(argv[i]);
        _before_list.push_back(value);
        _before_deque.push_back(value);
    }
    printBefore();
}

PmergeMe::~PmergeMe() {}

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
    }
    return true;
}

void PmergeMe::printBefore()
{
    std::cout << "Before: ";
    for (std::list<int>::iterator it = _before_list.begin(); it != _before_list.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

void PmergeMe::printAfter()
{
    std::cout << "After:  ";
    for (std::deque<int>::iterator it = _mainChain_deque.begin(); it != _mainChain_deque.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

double getTimeUS()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000 + tv.tv_usec;
}

void PmergeMe::start()
{
    double start_list, end_list;
    double start_deque, end_deque;

    if (_before_list.empty() || _before_deque.empty())
        return;

    start_list = getTimeUS();
    setJacobsthal_list();
    makePair_list();
    if (!_pairList.empty())
    {
        mergeSort_list(_pairList, 0, _pairList.size() - 1);
        setMainChain_list();
        insertionSort_list();
    }
    else
		_mainChain_list.push_back(_isOdd);
    end_list = getTimeUS();
    double duration_list = end_list - start_list;

    start_deque = getTimeUS();
    setJacobsthal_deque();
    makePair_deque();
    if (!_pairDeque.empty())
    {
        mergeSort_deque(_pairDeque, 0, _pairDeque.size() - 1);
        setMainChain_deque();
        insertionSort_deque();
    }
    else
		_mainChain_deque.push_back(_isOdd);
    end_deque = getTimeUS();
    double duration_deque = end_deque - start_deque;

    printAfter();

    std::cout << "Time to process a range of " << _before_list.size() << " elements with std::list: " << duration_list << " us" << std::endl;
    std::cout << "Time to process a range of " << _before_deque.size() << " elements with std::deque: " << duration_deque << " us" << std::endl;
}

void PmergeMe::setMainChain_list()
{
    for (std::list<p>::iterator it = _pairList.begin(); it != _pairList.end(); ++it)
    {
        _mainChain_list.push_back(it->first);
        _pendingChain_list.push_back(it->second);
    }
}

void PmergeMe::insertionSort_list()
{
    if (_pendingChain_list.empty())
        return;

    _mainChain_list.push_front(_pendingChain_list.front());

    std::list<int>::iterator jacob_it = _jacobsthal_list.begin();
    ++jacob_it;
    ++jacob_it;

    for (; jacob_it != _jacobsthal_list.end(); ++jacob_it)
    {
        size_t index = *jacob_it;
        if (index >= _pendingChain_list.size())
            break;

        int value = getListValue(_pendingChain_list, index);

        std::list<int>::iterator insert_it = _mainChain_list.begin();
        while (insert_it != _mainChain_list.end() && *insert_it < value)
            ++insert_it;
        _mainChain_list.insert(insert_it, value);
    }

    for (size_t i = 1; i < _pendingChain_list.size(); i++)
    {
        if (std::find(_jacobsthal_list.begin(), _jacobsthal_list.end(), i) == _jacobsthal_list.end())
        {
            int value = getListValue(_pendingChain_list, i);

            std::list<int>::iterator insert_it = _mainChain_list.begin();
            while (insert_it != _mainChain_list.end() && *insert_it < value)
                ++insert_it;
            _mainChain_list.insert(insert_it, value);
        }
    }

    if (_isOdd != -1)
    {
        std::list<int>::iterator insert_it = _mainChain_list.begin();
        while (insert_it != _mainChain_list.end() && *insert_it < _isOdd)
            ++insert_it;
        _mainChain_list.insert(insert_it, _isOdd);
    }
}

void PmergeMe::makePair_list()
{
    _isOdd = -1;
    if (_before_list.size() % 2 == 1)
    {
        _isOdd = _before_list.back();
        _before_list.pop_back();
    }

    std::list<int>::iterator it = _before_list.begin();
    while (it != _before_list.end())
    {
        int first = *it;
        ++it;
        if (it == _before_list.end())
            break;
        int second = *it;
        ++it;

        if (first >= second)
            _pairList.push_back(std::make_pair(first, second));
        else
            _pairList.push_back(std::make_pair(second, first));
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

void PmergeMe::mergeSort_list(std::list<p> &list, int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        mergeSort_list(list, low, mid);
        mergeSort_list(list, mid + 1, high);
        sortPair_list(list, low, high);
    }
}

void PmergeMe::sortPair_list(std::list<p> &list, int low, int high)
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

void PmergeMe::setJacobsthal_list()
{
    int n1 = 0;
    int n2 = 1;
    _jacobsthal_list.push_back(n1);
    _jacobsthal_list.push_back(n2);

    while (_jacobsthal_list.size() < 33)
    {
        int temp = n2 + 2 * n1;
        _jacobsthal_list.push_back(temp);
        n1 = n2;
        n2 = temp;
    }

    _jacobsthal_list.push_back(2147483647);
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
                break;
            }
            j++;
        }
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

void PmergeMe::insertionSort_deque()
{
    if (_pendingChain_deque.empty())
        return;

    _mainChain_deque.push_front(_pendingChain_deque.front());

    std::deque<int>::iterator jacob_it = _jacobsthal_deque.begin();
    ++jacob_it;
    ++jacob_it;

    for (; jacob_it != _jacobsthal_deque.end(); ++jacob_it)
    {
        size_t index = *jacob_it;
        if (index >= _pendingChain_deque.size())
            break;

        int value = _pendingChain_deque[index];

        std::deque<int>::iterator insert_it = _mainChain_deque.begin();
        while (insert_it != _mainChain_deque.end() && *insert_it < value)
        {
            ++insert_it;
        }
        _mainChain_deque.insert(insert_it, value);
    }

    for (size_t i = 0; i < _pendingChain_deque.size(); ++i)
    {
        if (std::find(_jacobsthal_deque.begin(), _jacobsthal_deque.end(), i) == _jacobsthal_deque.end())
        {
            int value = _pendingChain_deque[i];

            std::deque<int>::iterator insert_it = _mainChain_deque.begin();
            while (insert_it != _mainChain_deque.end() && *insert_it < value)
            {
                ++insert_it;
            }
            _mainChain_deque.insert(insert_it, value);
        }
    }

    if (_isOdd != -1)
    {
        std::deque<int>::iterator insert_it = _mainChain_deque.begin();
        while (insert_it != _mainChain_deque.end() && *insert_it < _isOdd)
        {
            ++insert_it;
        }
        _mainChain_deque.insert(insert_it, _isOdd);
    }
}

void PmergeMe::makePair_deque()
{
    _isOdd = -1;
    if (_before_deque.size() % 2 == 1)
    {
        _isOdd = _before_deque.back();
        _before_deque.pop_back();
    }

    for (size_t i = 0; i < _before_deque.size(); i += 2)
    {
        if (i + 1 < _before_deque.size()) {
            int first = _before_deque[i];
            int second = _before_deque[i + 1];

            if (first >= second)
                _pairDeque.push_back(std::make_pair(first, second));
            else
                _pairDeque.push_back(std::make_pair(second, first));
        }
    }
}

void PmergeMe::mergeSort_deque(std::deque<p>& deque, int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        mergeSort_deque(deque, low, mid);
        mergeSort_deque(deque, mid + 1, high);
        sortPair_deque(deque, low, high);
    }
}

void PmergeMe::sortPair_deque(std::deque<p>& deque, int low, int high)
{
    std::deque<p> sorted;
    int mid = (low + high) / 2;
    int i = low;
    int j = mid + 1;
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
    {
        deque[low + k] = sorted[k];
    }
}

void PmergeMe::setJacobsthal_deque()
{
    int n1 = 0;
    int n2 = 1;
    _jacobsthal_deque.push_back(n1);
    _jacobsthal_deque.push_back(n2);

    while (_jacobsthal_deque.size() < 33)
    {
        int temp = n2 + 2 * n1;
        _jacobsthal_deque.push_back(temp);
        n1 = n2;
        n2 = temp;
    }

    _jacobsthal_deque.push_back(2147483647);
}
