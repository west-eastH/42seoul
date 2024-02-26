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
		typedef typename std::deque<T>::iterator iterator;
		iterator begin();
		iterator end();

    	typedef typename std::deque<T>::reverse_iterator reverse_iterator;
		reverse_iterator rbegin();
		reverse_iterator rend();
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

template<typename T>
typename MutantStack<T>::reverse_iterator MutantStack<T>::rbegin()
{
	return this->c.rbegin();
}

template<typename T>
typename MutantStack<T>::reverse_iterator MutantStack<T>::rend()
{
	return this->c.rend();
}
