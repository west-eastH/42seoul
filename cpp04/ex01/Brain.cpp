#include "Brain.hpp"

Brain::Brain()
{
	std::cout << "Brain constructor called" << std::endl;
	for (int i = 0; i < 100; i++)
		this->ideas[i] = "@@@@@I'm brain@@@@@";
}

Brain::~Brain()
{
	std::cout << "Brain destructor called" << std::endl;
}

Brain::Brain(const Brain &origin)
{
	for (int i = 0; i < 100; i++)
		this->ideas[i] = origin.getIdea(i);
	std::cout << "Brain Copy constructor called" << std::endl;
}

Brain& Brain::operator=(const Brain &origin)
{
	if (this != &origin)
	{
		for (int i = 0; i < 100; i++)
			this->ideas[i] = origin.getIdea(i);
		std::cout << "Brain Copy assignment operator called" << std::endl;
	}
	return *this;
}

const std::string Brain::getIdea(int idx) const
{
	if (idx < 0)
		return this->ideas[0];
	else if (idx > 99)
		return this->ideas[99];
	return this->ideas[idx];
}

void Brain::setIdea(std::string const str,int idx)
{
	if (idx < 0 || idx > 99)
		return ;
	this->ideas[idx] = str;
}