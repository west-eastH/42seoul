#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <sys/time.h>

typedef std::vector< std::vector<int> > vv;
typedef std::deque< std::deque<int> > dd;

class PmergeMe
{
	private:
		std::vector<int> _before_vector;
		std::vector<int> _jacobsthal_vector;
		std::deque<int> _before_deque;
		std::deque<int> _jacobsthal_deque;
		PmergeMe();
		PmergeMe(const PmergeMe& origin);
		PmergeMe& operator=(const PmergeMe& origin);

	public:
		PmergeMe(int argc, char *argv[]);
		~PmergeMe();
		void printBefore();
		bool isValidArg(int argc, char *argv[]);
		void printAfter(double duration_list, double duration_deque, std::vector<int> vec);
		double getTimeUS();
		void start();


		//vector
		void setJacobsthal_vector();
		std::vector<int> mergeSortStart_vector(std::vector<int> &vec);
		int binaryInsertValue_vector(vv& mainChain, int left, int right, std::vector<int>& target);
		std::vector<int> merge_vector(std::vector<int>& v1, std::vector<int>& v2, size_t cnt, vv& mainChain, vv& pendingChain);
		vv mergeSort_vector(vv& vec, size_t cnt);
		void insertRemainValue_vector(int prev, vv& mainChain, vv& pendingChain);
		vv insertionSort_vector(vv& mainChain, vv& pendingChain);

		//deque
		void setJacobsthal_deque();
		std::deque<int> mergeSortStart_deque(std::deque<int> &vec);
		int binaryInsertValue_deque(dd& mainChain, int left, int right, std::deque<int>& target);
		std::deque<int> merge_deque(std::deque<int>& v1, std::deque<int>& v2, size_t cnt, dd& mainChain, dd& pendingChain);
		dd mergeSort_deque(dd& vec, size_t cnt);
		void insertRemainValue_deque(int prev, dd& mainChain, dd& pendingChain);
		dd insertionSort_deque(dd& mainChain, dd& pendingChain);
};
#endif
