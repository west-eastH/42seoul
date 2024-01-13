#pragma once
#include <iostream>
#include <string>

class Animal
{
	protected :
		std::string type;
	public :
		Animal();
		Animal(std::string type);
		~Animal();
		Animal(const Animal &origin);
		Animal& operator=(const Animal &origin);

		const std::string getType() const;
		void setType(std::string const type);
		virtual void makeSound() const;
};
