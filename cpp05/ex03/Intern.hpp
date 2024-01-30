#pragma once

#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

class Intern
{
private:
public:
	Intern();
	~Intern();
	Intern(const Intern& origin);
	Intern& operator=(const Intern& origin);

	AForm *createRobotomy(const std::string target);
	AForm *createShrubbery(const std::string target);
	AForm *createPresidential(const std::string target);
	AForm *makeForm(const std::string name, const std::string target);

	class NoExistException : public std::exception
		{
			private:
				std::string _msg;
			public:
				NoExistException(const std::string msg);
				~NoExistException() throw();
				virtual const char* what() const throw();
		};
};
