#pragma once

#include "Brain.hpp"

class Dog : public Animal
{
	private:
		Brain *brain;
	public:
		Dog();
		~Dog();
		Dog(const Dog &origin);
		Dog& operator=(const Dog &origin);
		virtual void makeSound() const;
};
