#pragma once

#include "Animal.hpp"

class Brain
{
	protected:
		std::string idea[100];
	public:
		Brain();
		~Brain();
		Brain(const Brain &origin);
		Brain& operator=(const Brain &origin);
		std::string getIdea(int idx) const;
};
