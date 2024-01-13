#pragma once

#include <iostream>
#include <string>

class ICharacter
{
	private:
		std::string name;
	public:
		
		ICharacter();
		ICharacter(const ICharacter &origin);
		ICharacter& operator=(const ICharacter &origin);
		virtual ~ICharacter() {}
		virtual std::string const & getName() const = 0;
		virtual void equip(AMateria* m) = 0;
		virtual void unequip(int idx) = 0;
		virtual void use(int idx, ICharacter& target) = 0;
};