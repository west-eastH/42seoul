#include "Ice.hpp"

Ice::Ice() : AMateria("ice")
{
}

Ice::Ice(std::string const & type) : AMateria(type)
{
}

Ice::~Ice()
{
}

Ice::Ice(const Ice &origin)
{
	this->_type = origin.getType();
}

Ice& Ice::operator=(const Ice &origin)
{
	if (this != &origin)
		this->_type = origin.getType();
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
