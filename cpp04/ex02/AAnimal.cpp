#include "AAnimal.hpp"

Animal::Animal()
{
	this->type = "Default";
	std::cout << "Animal constructor called" << std::endl;
}

Animal::Animal(std::string type)
{
	this->type = type;
	std::cout << "Animal constructor called" << std::endl;
}

Animal::~Animal()
{
	std::cout << "Animal Destructor called" << std::endl;
}

Animal::Animal(const Animal &origin)
{
	this->type = origin.getType();
	std::cout << "Animal Copy constructor called" << std::endl;
}

Animal& Animal::operator=(const Animal &origin)
{
	if (this != &origin)
	{
		this->type = origin.getType();
		std::cout << "Animal Copy assignment operator called" << std::endl;
	}
	return *this;
}

const std::string Animal::getType() const
{
	return this->type;
}

void Animal::setType(std::string const type)
{
	this->type = type;
}

void Animal::makeSound() const
{	
}