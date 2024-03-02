#include <iostream>
#include <list>
#include <deque>
#include <algorithm>

#define FIRST	0
#define SECOND	1

typedef std::pair<int, int> p;

class PmergeMe
{
private:
	std::deque<int> _before;
	std::deque<int> _jacobsthal;

	std::list<p> _pairList;
	std::list<int> _mainChain;
	std::list<int> _pendingChain;

	PmergeMe();
	PmergeMe(const PmergeMe& origin);
	PmergeMe& operator=(const PmergeMe& origin);
public:
	PmergeMe(int argc, char *argv[]);
	~PmergeMe();
	bool isValidArg(int argc, char *argv[]);
	void start();

	void setJacobsthal();
	void printList();
	int makePairList();
	int getListValue(std::list<p>& list, int idx, bool flag);
	int getListValue(std::list<int>& list, int idx);
	void changeListPair(std::list<p>& origin, std::list<p> ref, int begin, int end);
	std::pair<int, int>& getListPair(std::list<p>& list, int idx);
	void mergeSort(std::list<p>& list, int low, int high);
	void sortPair(std::list<p>& list, int low, int high);
	void setMainChain();
	void insertionSort();
};
