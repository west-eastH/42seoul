#include "Cat.hpp"

Cat::Cat() : Animal("Cat")
{
	std::cout << "Cat constructor called" << std::endl;
}

Cat::~Cat()
{
	std::cout << "Cat Destructor called" << std::endl;

}

Cat::Cat(const Cat &origin)
{
	this->type = origin.getType();
	std::cout << "Cat Copy constructor called" << std::endl;
}

Cat& Cat::operator=(const Cat &origin)
{
	if (this != &origin)
	{
		this->type = origin.getType();
		std::cout << "Cat Copy assignment operator called" << std::endl;
	}
	return *this;
}

void Cat::makeSound() const
{
	std::cout << "고양이 야옹야옹" << std::endl;
}