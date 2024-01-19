#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat() : _name("default"), _grade(150)
{
}

Bureaucrat::Bureaucrat(std::string const name, unsigned int grade) : _name(name)
{
	if (grade < 1)
		throw Bureaucrat::GradeTooHighException();
	else if (grade > 150)
		throw Bureaucrat::GradeTooLowException();
	this->_grade = grade;
}

Bureaucrat::~Bureaucrat() throw()
{
}

Bureaucrat::Bureaucrat(const Bureaucrat& origin)
{
	this->_grade = origin._grade;
}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& origin)
{
	this->_grade = origin._grade;
	return *this;
}

const std::string& Bureaucrat::getName() const
{
	return this->_name;
}

unsigned int Bureaucrat::getGrade() const
{
	return this->_grade;
}

void Bureaucrat::increaseGrade()
{
	if (this->_grade == 1)
		throw Bureaucrat::GradeTooHighException();
	this->_grade--;
}

void Bureaucrat::decreaseGrade()
{
	if (this->_grade == 150)
		throw Bureaucrat::GradeTooLowException();
	this->_grade++;
}

void Bureaucrat::signForm(const std::string formName) const
{
	std::cout << this->getName() << " signed " << formName << std::endl;
}

const char* Bureaucrat::GradeTooHighException::what() const throw()
{
	return "Bureaucrat's grade is too High";
}
const char* Bureaucrat::GradeTooLowException::what() const throw()
{
	return "Bureaucrat's grade is too Low";
}
std::ostream	&operator<<(std::ostream &out, const Bureaucrat &ref)
{
	out << ref.getName() << ", bureaucrat grade " << ref.getGrade();
	return out;
}
