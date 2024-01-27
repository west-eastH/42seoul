#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm() : AForm("RobotomyRequestForm", 72, 45), _target("default_target") {}

RobotomyRequestForm::RobotomyRequestForm(const std::string target) : AForm("RobotomyRequestForm", 72, 45), _target(target) {}

RobotomyRequestForm::~RobotomyRequestForm() throw() {}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& origin) : AForm(origin.getName(), origin.getSignGrade(), origin.getExecuteGrade()), _target(origin.getTarget())
{
}

RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm& origin)
{
	setIsSigned(origin.getIsSigned());
	return *this;
}

const std::string& RobotomyRequestForm::getTarget() const
{
	return _target;
}

void RobotomyRequestForm::execute(Bureaucrat const & executor) const
{
	if (executor.getGrade() > getExecuteGrade())
		throw AForm::GradeTooLowException(executor.getName() + " Bureaucrat couldn’t execute " + getName() + ". because " + executor.getName() + "'s grade is too Low.");
	std::cout << "drrrrrrrrrrr" << std::endl;
	if (rand() % 2 != 0)
		std::cout << GREEN << _target << " has been robotomized" << RESET << std::endl;
	else
		std::cout << YELLOW << _target << " hasn't been robotomized"<< RESET << std::endl;
}

std::ostream	&operator<<(std::ostream &out, const RobotomyRequestForm &ref)
{
	out << ref.getName() << ", form status : " << ref.getIsSigned() << " signGrade : " << ref.getSignGrade() << " executeGrade : " << ref.getExecuteGrade() << " target : " << ref.getTarget();
	return out;
}

