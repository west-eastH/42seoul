#pragma once

#include "AMateria.hpp"

class Cure : public AMateria
{
public:
	Cure();
	Cure(std::string const & type);
	~Cure();
	Cure(const Cure &origin);
	Cure& operator=(const Cure &origin);
	Cure* clone() const;
	void use(ICharacter& target);
};
