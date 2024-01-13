#include "WrongCat.hpp"

WrongCat::WrongCat() : WrongAnimal("WrongCat")
{
	std::cout << "WrongCat constructor called" << std::endl;
}

WrongCat::~WrongCat()
{
	std::cout << "WrongCat Destructor called" << std::endl;

}

WrongCat::WrongCat(const WrongCat &origin)
{
	this->type = origin.getType();
	std::cout << "WrongCat Copy constructor called" << std::endl;
}

WrongCat& WrongCat::operator=(const WrongCat &origin)
{
	if (this != &origin)
	{
		this->type = origin.getType();
		std::cout << "WrongCat Copy assignment operator called" << std::endl;
	}
	return *this;
}

void WrongCat::makeSound() const
{
	std::cout << "고양이 야옹야옹" << std::endl;
}