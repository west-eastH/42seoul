#include "Cure.hpp"

Cure::Cure() : AMateria("cure")
{
}

Cure::Cure(std::string const & type) : AMateria(type)
{
}

Cure::~Cure()
{
}

Cure::Cure(const Cure &origin)
{
	this->_type = origin.getType();
}

Cure& Cure::operator=(const Cure &origin)
{
	if (this != &origin)
		this->_type = origin.getType();
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
