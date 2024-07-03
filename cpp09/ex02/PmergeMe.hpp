#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <sys/time.h>

typedef std::vector< std::vector<int> > vv;

class PmergeMe
{
	private:
		std::vector<int> _before_vector;
		std::vector<int> _jacobsthal_vector;
		PmergeMe();
		PmergeMe(const PmergeMe& origin);
		PmergeMe& operator=(const PmergeMe& origin);

	public:
		PmergeMe(int argc, char *argv[]);
		~PmergeMe();
		bool isValidArg(int argc, char *argv[]);
		void start();
		void printBefore();
		void printAfter(double duration_list, double duration_deque);
		double getTimeUS();


		//vector
		void setJacobsthal_vector();
		void mergeSortStart_vector(std::vector<int> &vec);
		vv mergeSort_vector(vv& vec, size_t depth);
		std::vector<int> merge_vec(std::vector<int>& v1, std::vector<int>& v2, size_t depth, vv& mainChain, vv& pendingChain);

};
#endif

// before = 5 2 1 9 2 6 2 3 5 8 3 size = 11
// 5 2 1 9 2 6 2 3 5 8  // 나머지 : 3 --- 1레벨
// (5 2) (9 1) (6 2) (3 2) // 나머지 : (8 5) --- 2레벨
// (9 1 5 2) (6 2 3 2) // --- 3레벨
// (9 1 5 2 6 2 3 2) // --- 4레벨
// (6 2 3 2) (9 1 5 2) // --- 3레벨
// (3 2) (5 2) (6 2) (8 5) (9 1) // --- 2레벨
// 1 2 2 2 3 3 5 5 6 8 9		// --- 1레벨