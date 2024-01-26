#pragma once

#include "AForm.hpp"

class ShrubberyCreationForm : public Form
{
private:
	std::string target;
public:
	ShrubberyCreationForm();
	ShrubberyCreationForm(std::string const name, unsigned int signGrade, unsigned int executeGrade, std::string target);
	~ShrubberyCreationForm();
};

ShrubberyCreationForm::ShrubberyCreationForm()
{
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
}
