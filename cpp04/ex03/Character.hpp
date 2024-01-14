#pragma once

#include "ICharacter.hpp"
#include "Ice.hpp"
#include "Cure.hpp"
#include "Floor.hpp"

class Character : public ICharacter
{
	protected:
		std::string name;
		AMateria* slot[4];
	public:
		Character();
		Character(std::string const & name);
		Character(const Character &origin);
		Character& operator=(const Character &origin);
		
		~Character();
		std::string const & getName() const;
		void equip(AMateria* m);
		void unequip(int idx);
		void use(int idx, ICharacter& target);
};
