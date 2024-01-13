
#include "AMateria.hpp"

	AMateria::AMateria()
	{
		this->_type = std::string("Default");
		std::cout << "AMateria constructor called" << std::endl;
	}
	
	AMateria::AMateria(std::string const & type)
	{	
		this->_type = std::string(type);
		std::cout << "AMateria constructor called" << std::endl;
	}
	
	AMateria::~AMateria()
	{
		std::cout << "AMateria Destructor called" << std::endl;
	}
	
	AMateria::AMateria(const AMateria &origin)
	{
		this->_type = std::string(origin.getType());
		std::cout << "AMateria Copy constructor called" << std::endl;
	}
	
	AMateria& AMateria::operator=(const AMateria &origin)
	{
		if (this != &origin)
		{
			this->_type = std::string(origin.getType());
			std::cout << "AMateria Copy assignment operator called" << std::endl;
		}
		return *this;	
	}
	
	std::string const & AMateria::getType() const
	{
		return (this->_type);
	}
	
	AMateria* AMateria::clone() const
	{
	}
	
	void AMateria::use(ICharacter& target)
	{
	}
	