#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm() : Form("default_ShrubberyCreaationForm", , executeGrade), _target("default_target")
{
}

ShrubberyCreationForm::ShrubberyCreationForm(std::string const name, unsigned int signGrade, unsigned int executeGrade, std::string const target) : Form(name, signGrade, executeGrade), _target(target)
{
	if (signGrade < 1 || _executeGrade < 1)
		throw ShrubberyCreationForm::GradeTooHighException(this->_name + " form's grade is too High");
	else if (signGrade > 150 || _executeGrade > 150)
		throw ShrubberyCreationForm::GradeTooLowException(this->_name + " form's grade is too Low");
}

ShrubberyCreationForm::~ShrubberyCreationForm() throw()
{
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& origin) : _name(origin._name), _signGrade(origin._signGrade), _executeGrade(origin._executeGrade)
{
	this->_isSigned = 0;
}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& origin)
{
	this->_isSigned = origin._isSigned;
	return *this;
}
