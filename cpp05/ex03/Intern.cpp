#include "Intern.hpp"

Intern::Intern() {}

Intern::~Intern() {}

Intern::Intern(const Intern& origin) {(void)origin;}
Intern& Intern::operator=(const Intern& origin)
{
	(void)origin;
	return *this;
}

AForm *Intern::createRobotomy(const std::string target) {return new RobotomyRequestForm(target);}
AForm *Intern::createShrubbery(const std::string target) {return new ShrubberyCreationForm(target);}
AForm *Intern::createPresidential(const std::string target) {return new PresidentialPardonForm(target);}

AForm *Intern::makeForm(const std::string name, const std::string target)
{
	AForm* (Intern::*func[3])(const std::string) = {&Intern::createShrubbery, &Intern::createRobotomy, &Intern::createPresidential};
	std::string Forms[3] = {"shrubbery creation", "robotomy request", "presidential pardon"};
	for (int i = 0; i < 3; i++)
	{
		if (name == Forms[i])
			return (this->*func[i])(target);
	}
	throw AForm::GradeTooHighException("tt");
}