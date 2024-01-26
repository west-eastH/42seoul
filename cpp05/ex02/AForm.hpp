#pragma once
#include <iostream>
#include "Bureaucrat.hpp"

class Form
{
	private:
		const std::string _name;
		bool _isSigned;
		const unsigned int _signGrade;
		const unsigned int _executeGrade;
		Form& operator=(const Form& origin);

	public:
		Form();
		Form(std::string const name, unsigned int signGrade, unsigned int executeGrade);
		Form(const Form& origin);
		virtual ~Form() throw();

		const std::string& getName() const;
		unsigned int getIsSigned() const;
		unsigned int getSignGrade() const;
		unsigned int getExecuteGrade() const;
		void setIsSigned(bool isSigned);

		void beSigned(const Bureaucrat& Bureaucrat);
		virtual void execute(Bureaucrat const & executor) const;
		
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