#pragma once

#include "AAnimal.hpp"

class Brain
{
	private:
		std::string ideas[100];
	public:
		Brain();
		~Brain();
		Brain(const Brain &origin);
		Brain& operator=(const Brain &origin);
		const std::string getIdea(int idx) const;
		void setIdea(std::string const str,int idx);
};
