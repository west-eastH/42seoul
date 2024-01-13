#include "Ice.hpp"

Ice::Ice() : AMateria("cure")
{
	std::cout << "Ice constructor called" << std::endl;
}

Ice::Ice(std::string const & type) : AMateria(type)
{
	std::cout << "Ice constructor called" << std::endl;
}

Ice::~Ice()
{
	std::cout << "Ice Destructor called" << std::endl;
}

Ice::Ice(const Ice &origin)
{
	this->_type = std::string(origin.getType());
	std::cout << "Ice Copy constructor called" << std::endl;
}

Ice& Ice::operator=(const Ice &origin)
{
	if (this != &origin)
		{
			this->_type = std::string(origin.getType());
			std::cout << "Ice Copy assignment operator called" << std::endl;
		}
		return *this;	
}

Ice* Ice::clone() const
{
	Ice *temp = new Ice(this->getType());
	return temp;
}

void Ice::use(ICharacter& target)
{
	std::cout << "* shoots an ice bolt at " << target.getName() << " *" << std::endl;
}
