#include "Brain.hpp"

Brain::Brain()
{
	this->idea = new std::string[100];
	std::cout << "Brain constructor called" << std::endl;
}

Brain::~Brain()
{
	delete[] this->idea;
	std::cout << "Brain Destructor called" << std::endl;
}

Brain::Brain(const Brain &origin)
{
	this->idea = new std::string[100];
	this->idea = origin.getIdea();
	std::cout << "Brain Copy constructor called" << std::endl;
}

Brain& Brain::operator=(const Brain &origin)
{
	if (this != &origin)
	{
		this->idea = origin.getIdea();
		std::cout << "Brain Copy assignment operator called" << std::endl;
	}
	return *this;
}

std::string *Brain::getIdea() const
{
	return (this->idea);
}
