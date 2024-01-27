#include "AForm.hpp"

AForm::AForm() : _name("default"), _isSigned(0), _signGrade(100), _executeGrade(100)
{
}

AForm::AForm(std::string const name, int signGrade, int executeGrade) : _name(name), _isSigned(0), _signGrade(signGrade), _executeGrade(executeGrade)
{
	if (signGrade < 1 || _executeGrade < 1)
		throw AForm::GradeTooHighException(this->_name + " form's grade is too High");
	else if (signGrade > 150 || _executeGrade > 150)
		throw AForm::GradeTooLowException(this->_name + " form's grade is too Low");
}

AForm::~AForm() throw()
{
}

AForm::AForm(const AForm& origin) : _name(origin._name), _signGrade(origin._signGrade), _executeGrade(origin._executeGrade)
{
	this->_isSigned = 0;
}

AForm& AForm::operator=(const AForm& origin)
{
	this->_isSigned = origin._isSigned;
	return *this;
}

const std::string& AForm::getName() const
{
	return this->_name;
}

int AForm::getIsSigned() const
{
	return this->_isSigned;
}

int AForm::getSignGrade() const
{
	return this->_signGrade;
}

int AForm::getExecuteGrade() const
{
	return this->_executeGrade;
}

void AForm::setIsSigned(bool isSigned)
{
	this->_isSigned = isSigned;
}

void AForm::beSigned(const Bureaucrat& Bureaucrat)
{
	
	if (Bureaucrat.getGrade() > _signGrade)
		throw AForm::GradeTooLowException(Bureaucrat.getName() + " Bureaucrat couldn’t sign " + _name + " AForm. because " + Bureaucrat.getName() + "'s grade is too Low.");
	setIsSigned(1);
}


AForm::GradeTooLowException::GradeTooLowException(const std::string msg) : _msg(msg)
{
}

AForm::GradeTooHighException::GradeTooHighException(const std::string msg) : _msg(msg)
{
}

AForm::GradeTooLowException::~GradeTooLowException() throw(){}
AForm::GradeTooHighException::~GradeTooHighException() throw(){}
const char* AForm::GradeTooHighException::what() const throw()
{
	return this->_msg.c_str();
}
const char* AForm::GradeTooLowException::what() const throw()
{
	return this->_msg.c_str();
}
