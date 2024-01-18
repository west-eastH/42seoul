#include "Cat.hpp"

Cat::Cat() : Animal("Cat")
{
	this->brain = new Brain();
	std::cout << "Cat constructor called" << std::endl;
}

Cat::~Cat()
{
	delete this->brain;
	std::cout << "Cat destructor called" << std::endl;
}

Cat::Cat(const Cat &origin)
{
	this->brain = new Brain();
	for (int i = 0; i < 100; i++)
		this->brain->setIdea(origin.brain->getIdea(i), i);
	this->type = origin.getType();
	std::cout << "Cat Copy constructor called" << std::endl;
}

Cat& Cat::operator=(const Cat &origin)
{
	if (this != &origin)
	{
		delete this->brain;
		this->brain = new Brain();
		for (int i = 0; i < 100; i++)
			this->brain->setIdea(origin.brain->getIdea(i), i);
		this->type = origin.getType();
		std::cout << "Cat Copy assignment operator called" << std::endl;
	}
	return *this;
}

void Cat::makeSound() const
{
	std::cout << "고양이 야옹야옹" << std::endl;
}

Brain *Cat::getBrain() const
{
	return this->brain;
}