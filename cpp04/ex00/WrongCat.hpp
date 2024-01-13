#pragma once

#include "WrongAnimal.hpp"

class WrongCat : public WrongAnimal
{
	public:
		WrongCat();
		~WrongCat();
		WrongCat(const WrongCat &origin);
		WrongCat& operator=(const WrongCat &origin);
		void makeSound() const;
};
