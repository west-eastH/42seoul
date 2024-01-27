#pragma once

#include "AForm.hpp"
#include <fstream>

class ShrubberyCreationForm : public AForm
{
private:
	const std::string _target;
	ShrubberyCreationForm();
	ShrubberyCreationForm& operator=(const ShrubberyCreationForm& origin);
public:
	ShrubberyCreationForm(const std::string target);
	ShrubberyCreationForm(const ShrubberyCreationForm& orign);
	virtual ~ShrubberyCreationForm() throw();

	void createAsciiTree() const;
	const std::string& getTarget() const;
	virtual void execute(Bureaucrat const & executor) const;
};
std::ostream	&operator<<(std::ostream &out, const ShrubberyCreationForm &ref);