#pragma once

#include "AForm.hpp"

class RobotomyRequestForm : public AForm
{
private:
	const std::string _target;
	RobotomyRequestForm();
	RobotomyRequestForm& operator=(const RobotomyRequestForm& origin);
public:
	RobotomyRequestForm(const std::string target);
	RobotomyRequestForm(const RobotomyRequestForm& orign);
	virtual ~RobotomyRequestForm() throw();

	const std::string& getTarget() const;
	virtual void execute(Bureaucrat const & executor) const;
};
std::ostream	&operator<<(std::ostream &out, const RobotomyRequestForm &ref);