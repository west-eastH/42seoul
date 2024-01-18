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
		void makeSound() const;
		Brain *getBrain() const;
};
