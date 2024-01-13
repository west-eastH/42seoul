#pragma once

#include "AMateria.hpp"

class Ice : public AMateria
{
public:
	Ice();
	Ice(std::string const & type);
	~Ice();
	Ice(const Ice &origin);
	Ice& operator=(const Ice &origin);
	Ice* clone() const;
	void use(ICharacter& target);
};
