#pragma once

#include "IMateriaSource.hpp"

class MateriaSource : public IMateriaSource
{
	private:
		AMateria *_slot[4];
	public:

		MateriaSource();
		MateriaSource(const MateriaSource &origin);
		MateriaSource& operator=(const MateriaSource &origin);
		
		~MateriaSource();
		void learnMateria(AMateria*);
		AMateria* createMateria(std::string const & type);
};