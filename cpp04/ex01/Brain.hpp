#pragma once

#include "Animal.hpp"

class Brain
{
	protected:
		std::string *idea;
	public:
		Brain();
		~Brain();
		Brain(const Brain &origin);
		Brain& operator=(const Brain &origin);
		std::string *getIdea() const;
};
