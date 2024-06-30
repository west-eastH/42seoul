#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <list>
#include <deque>
#include <algorithm>
#include <sys/time.h>

#define FIRST   0
#define SECOND  1

typedef std::pair<int, int> p;

class PmergeMe
{
private:
    std::list<int> _before_list;
    std::deque<int> _before_deque;
    std::list<int> _jacobsthal_list;
    std::deque<int> _jacobsthal_deque;

    std::list<p> _pairList;
    std::deque<p> _pairDeque;
    std::list<int> _mainChain_list;
    std::deque<int> _mainChain_deque;
    std::list<int> _pendingChain_list;
    std::deque<int> _pendingChain_deque;
    int _isOdd;

    PmergeMe();
    PmergeMe(const PmergeMe& origin);
    PmergeMe& operator=(const PmergeMe& origin);

public:
    PmergeMe(int argc, char *argv[]);
    ~PmergeMe();
    bool isValidArg(int argc, char *argv[]);
    void start();
    void printBefore();
    void printAfter();

    int getListValue(std::list<p>& list, int idx, bool flag);
    int getListValue(std::list<int>& list, int idx);
    std::pair<int, int>& getListPair(std::list<p>& list, int idx);
    void setJacobsthal_list();
    void makePair_list();
    void mergeSort_list(std::list<p>& list, int low, int high);
    void sortPair_list(std::list<p>& list, int low, int high);
    void setMainChain_list();
    void insertionSort_list();
    void changeListPair(std::list<p>& origin, std::list<p> ref, int begin, int end);
    
	void setJacobsthal_deque();
    void makePair_deque();
    void mergeSort_deque(std::deque<p>& deque, int low, int high);
    void sortPair_deque(std::deque<p>& deque, int low, int high);
    void setMainChain_deque();
    void insertionSort_deque();
};

#endif
