#include <iostream>
#include <stack>
#include <list>

template<typename T>
class MutantStack : public std::stack<T>
{
	private:
		MutantStack(const MutantStack& origin);
		MutantStack& operator=(const MutantStack& origin);
	public:
		MutantStack();
		~MutantStack();
		
		typedef typename std::deque<T>::__base::iterator	iterator;
		iterator begin();
		iterator end();

};

template<typename T>
MutantStack<T>::MutantStack()
{
}

template<typename T>
MutantStack<T>::~MutantStack()
{
}

template<typename T>
typename MutantStack<T>::iterator MutantStack<T>::begin()
{
	return this->c.begin();
}

template<typename T>
typename MutantStack<T>::iterator MutantStack<T>::end()
{
	return this->c.end();
}