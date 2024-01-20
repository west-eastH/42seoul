#pragma once
#include <iostream>
#include <exception>

class Form;
class Bureaucrat
{
	private:
		const std::string _name;
		unsigned int _grade;
		Bureaucrat& operator=(const Bureaucrat& origin);
	public:
		Bureaucrat();
		Bureaucrat(std::string const name, unsigned int grade);
		Bureaucrat(const Bureaucrat& origin);
		~Bureaucrat() throw();

		const std::string& getName() const;
		unsigned int getGrade() const;
		void increaseGrade();
		void decreaseGrade();
		void signForm(Form& form) const;

		class GradeTooLowException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
		class GradeTooHighException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
};
std::ostream	&operator<<(std::ostream &out, const Bureaucrat &ref);