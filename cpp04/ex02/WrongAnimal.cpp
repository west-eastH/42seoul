#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal()
{
	this->type = "Default";
	std::cout << "WrongAnimal constructor called" << std::endl;
}

WrongAnimal::WrongAnimal(std::string type)
{
	this->type = type;
	std::cout << "WrongAnimal constructor called" << std::endl;
}

WrongAnimal::~WrongAnimal()
{
	std::cout << "WrongAnimal Destructor called" << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal &origin)
{
	this->type = origin.getType();
	std::cout << "WrongAnimal Copy constructor called" << std::endl;
}

WrongAnimal& WrongAnimal::operator=(const WrongAnimal &origin)
{
	if (this != &origin)
	{
		this->type = origin.getType();
		std::cout << "WrongAnimal Copy assignment operator called" << std::endl;
	}
	return *this;
}

const std::string WrongAnimal::getType() const
{
	return this->type;
}

void WrongAnimal::setType(std::string const type)
{
	this->type = type;
}

void WrongAnimal::makeSound() const
{
	std::cout << "안녕하세요 동물입니다" << std::endl;
}