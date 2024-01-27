#pragma once
#include <iostream>
#include <exception>

#define RED "\033[1;31m"
#define RESET "\033[0;0m"

class Form;
class Bureaucrat
{
	private:
		const std::string _name;
		int _grade;
		Bureaucrat& operator=(const Bureaucrat& origin);
	public:
		Bureaucrat();
		Bureaucrat(std::string const name, int grade);
		Bureaucrat(const Bureaucrat& origin);
		~Bureaucrat() throw();

		const std::string& getName() const;
		int getGrade() const;
		void increaseGrade();
		void decreaseGrade();
		void signForm(Form& form);

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