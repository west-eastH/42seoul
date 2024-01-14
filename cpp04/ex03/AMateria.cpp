
#include "AMateria.hpp"

	AMateria::AMateria()
	{
		this->_type = "default";
	}
	
	AMateria::AMateria(std::string const & type)
	{	
		this->_type = type;
	}
	
	AMateria::~AMateria()
	{
	}
	
	AMateria::AMateria(const AMateria &origin)
	{
		this->_type = origin.getType();
	}
	
	AMateria& AMateria::operator=(const AMateria &origin)
	{
		if (this != &origin)
		{
			this->_type = origin.getType();

		}
		return *this;	
	}
	
	std::string const & AMateria::getType() const
	{
		return (this->_type);
	}

	void AMateria::use(ICharacter& target)
	{
		(void)target;
	}
	