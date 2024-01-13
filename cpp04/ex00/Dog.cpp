#include "Dog.hpp"

Dog::Dog() : Animal("Dog")
{
	std::cout << "Dog constructor called" << std::endl;
}

Dog::~Dog()
{
	std::cout << "Dog Destructor called" << std::endl;

}

Dog::Dog(const Dog &origin)
{
	this->type = origin.getType();
	std::cout << "Dog Copy constructor called" << std::endl;
}

Dog& Dog::operator=(const Dog &origin)
{
	if (this != &origin)
	{
		this->type = origin.getType();
		std::cout << "Dog Copy assignment operator called" << std::endl;
	}
	return *this;
}

void Dog::makeSound() const
{
	std::cout << "강아지 멍멍" << std::endl;
}