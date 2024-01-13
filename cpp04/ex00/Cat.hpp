#pragma once

#include "Animal.hpp"

class Cat : public Animal
{
	public:
		Cat();
		~Cat();
		Cat(const Cat &origin);
		Cat& operator=(const Cat &origin);
		virtual void makeSound() const;
};
