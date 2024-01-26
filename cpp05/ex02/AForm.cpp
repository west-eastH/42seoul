#include "AForm.hpp"

Form::Form() : _name("default"), _isSigned(0), _signGrade(100), _executeGrade(100)
{
}

Form::Form(std::string const name, unsigned int signGrade, unsigned int executeGrade) : _name(name), _isSigned(0), _signGrade(signGrade), _executeGrade(executeGrade)
{
	if (signGrade < 1 || _executeGrade < 1)
		throw Form::GradeTooHighException(this->_name + " form's grade is too High");
	else if (signGrade > 150 || _executeGrade > 150)
		throw Form::GradeTooLowException(this->_name + " form's grade is too Low");
}

Form::~Form() throw()
{
}

Form::Form(const Form& origin) : _name(origin._name), _signGrade(origin._signGrade), _executeGrade(origin._executeGrade)
{
	this->_isSigned = 0;
}

Form& Form::operator=(const Form& origin)
{
	this->_isSigned = origin._isSigned;
	return *this;
}

const std::string& Form::getName() const
{
	return this->_name;
}

unsigned int Form::getIsSigned() const
{
	return this->_isSigned;
}

unsigned int Form::getSignGrade() const
{
	return this->_signGrade;
}

unsigned int Form::getExecuteGrade() const
{
	return this->_executeGrade;
}

void Form::setIsSigned(bool isSigned)
{
	this->_isSigned = isSigned;
}

void Form::beSigned(const Bureaucrat& Bureaucrat)
{
	try
	{
		Bureaucrat.signForm(*this);
	}
	catch(const std::exception& e)
	{
		std::cerr << RED << e.what() << RESET << '\n';
	}
	
}

Form::GradeTooLowException::GradeTooLowException(const std::string msg) : _msg(msg)
{
}

Form::GradeTooHighException::GradeTooHighException(const std::string msg) : _msg(msg)
{
}

Form::GradeTooLowException::~GradeTooLowException() throw(){}
Form::GradeTooHighException::~GradeTooHighException() throw(){}
const char* Form::GradeTooHighException::what() const throw()
{
	return this->_msg.c_str();
}
const char* Form::GradeTooLowException::what() const throw()
{
	return this->_msg.c_str();
}


std::ostream	&operator<<(std::ostream &out, const Form &ref)
{
	out << ref.getName() << ", form status : " << ref.getIsSigned() << " signGrade : " << ref.getSignGrade() << " executeGrade : " << ref.getExecuteGrade();
	return out;
}
