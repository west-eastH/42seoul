#pragma once
#include <iostream>
#include <string>

class WrongAnimal
{
	protected :
		std::string type;
	public :
		WrongAnimal();
		WrongAnimal(std::string type);
		~WrongAnimal();
		WrongAnimal(const WrongAnimal &origin);
		WrongAnimal& operator=(const WrongAnimal &origin);

		const std::string& getType() const;
		void setType(std::string const type);
		void makeSound() const;
};
