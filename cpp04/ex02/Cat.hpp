#pragma once

#include "Brain.hpp"

class Cat : public Animal
{
	private:
		Brain *brain;
	public:
		Cat();
		~Cat();
		Cat(const Cat &origin);
		Cat& operator=(const Cat &origin);
		void makeSound() const;
		Brain *getBrain() const;
};
