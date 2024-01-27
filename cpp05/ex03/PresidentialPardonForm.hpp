#pragma once

#include "AForm.hpp"

class PresidentialPardonForm : public AForm
{
private:
	const std::string _target;
	PresidentialPardonForm();
	PresidentialPardonForm& operator=(const PresidentialPardonForm& origin);
public:
	PresidentialPardonForm(const std::string target);
	PresidentialPardonForm(const PresidentialPardonForm& orign);
	virtual ~PresidentialPardonForm() throw();

	const std::string& getTarget() const;
	virtual void execute(Bureaucrat const & executor) const;
};
std::ostream	&operator<<(std::ostream &out, const PresidentialPardonForm &ref);