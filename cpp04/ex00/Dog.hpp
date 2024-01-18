#pragma once

#include "Animal.hpp"

class Dog : public Animal
{
	public:
		Dog();
		~Dog();
		Dog(const Dog &origin);
		Dog& operator=(const Dog &origin);
		void makeSound() const;
};
