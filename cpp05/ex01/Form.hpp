#pragma once
#include <iostream>
#include "Bureaucrat.hpp"

class Form
{
	private:
		const std::string _name;
		bool _isSigned;
		const int _signGrade;
		const int _executeGrade;
		Form& operator=(const Form& origin);

	public:
		Form();
		Form(std::string const name, int signGrade, int executeGrade);
		Form(const Form& origin);
		~Form() throw();

		const std::string& getName() const;
		int getIsSigned() const;
		int getSignGrade() const;
		int getExecuteGrade() const;
		void setIsSigned(bool isSigned);

		void beSigned(const Bureaucrat& Bureaucrat);
		
		class GradeTooLowException : public std::exception
		{
			private:
				std::string _msg;
			public:
				GradeTooLowException(const std::string msg);
				~GradeTooLowException() throw();
				virtual const char* what() const throw();
		};
		class GradeTooHighException : public std::exception
		{
			private:
				std::string _msg;
			public:
				GradeTooHighException(const std::string msg);
				~GradeTooHighException() throw();
				virtual const char* what() const throw();
		};
};
std::ostream	&operator<<(std::ostream &out, const Form &ref);