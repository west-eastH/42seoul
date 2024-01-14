#include "Brain.hpp"

Brain::Brain()
{
	std::cout << "Brain constructor called" << std::endl;
}

Brain::~Brain()
{
	std::cout << "Brain Destructor called" << std::endl;
}

Brain::Brain(const Brain &origin)
{
	for (int i = 0; i < 100; i++)
		this->idea[i] = origin.getIdea(i);
	std::cout << "Brain Copy constructor called" << std::endl;
}

Brain& Brain::operator=(const Brain &origin)
{
	if (this != &origin)
	{
		for (int i = 0; i < 100; i++)
			this->idea[i] = origin.getIdea(i);
		std::cout << "Brain Copy assignment operator called" << std::endl;
	}
	return *this;
}

std::string Brain::getIdea(int idx) const
{
	return this->idea[idx];
}
