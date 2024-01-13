#include "Cure.hpp"

Cure::Cure() : AMateria("cure")
{
	std::cout << "Cure constructor called" << std::endl;
}

Cure::Cure(std::string const & type) : AMateria(type)
{
	std::cout << "Cure constructor called" << std::endl;
}

Cure::~Cure()
{
	std::cout << "Cure Destructor called" << std::endl;
}

Cure::Cure(const Cure &origin)
{
	this->_type = std::string(origin.getType());
	std::cout << "Cure Copy constructor called" << std::endl;
}

Cure& Cure::operator=(const Cure &origin)
{
	if (this != &origin)
		{
			this->_type = std::string(origin.getType());
			std::cout << "Cure Copy assignment operator called" << std::endl;
		}
		return *this;	
}

Cure* Cure::clone() const
{
	Cure *temp = new Cure(this->getType());
	return temp;
}

void Cure::use(ICharacter& target)
{
	std::cout << "* heals " << target.getName() << "'s wounds *" << std::endl;
}
