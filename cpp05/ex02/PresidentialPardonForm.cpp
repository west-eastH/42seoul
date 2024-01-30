#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm() : AForm("PresidentialPardonForm", 25, 5), _target("default_target") {}

PresidentialPardonForm::PresidentialPardonForm(const std::string target) : AForm("PresidentialPardonForm", 25, 5), _target(target) {}

PresidentialPardonForm::~PresidentialPardonForm() throw() {}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& origin) : AForm(origin.getName(), origin.getSignGrade(), origin.getExecuteGrade()), _target(origin.getTarget()) {}

PresidentialPardonForm& PresidentialPardonForm::operator=(const PresidentialPardonForm& origin)
{
	setIsSigned(origin.getIsSigned());
	return *this;
}

const std::string& PresidentialPardonForm::getTarget() const
{
	return _target;
}

void PresidentialPardonForm::execute(Bureaucrat const & executor) const
{
	if (executor.getGrade() > getExecuteGrade())
		throw AForm::GradeTooLowException(executor.getName() + " Bureaucrat couldn’t execute " + getName() + ". because " + executor.getName() + "'s grade is too Low.");
	std::cout << _target << " has been pardoned by Zaphod Beeblebrox." << std::endl;
}

std::ostream	&operator<<(std::ostream &out, const PresidentialPardonForm &ref)
{
	out << ref.getName() << ", form status : " << ref.getIsSigned() << " signGrade : " << ref.getSignGrade() << " executeGrade : " << ref.getExecuteGrade() << " target : " << ref.getTarget();
	return out;
}

