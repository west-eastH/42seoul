#pragma once
#include <iostream>
#include "Bureaucrat.hpp"

class AForm
{
	private:
		const std::string _name;
		bool _isSigned;
		const int _signGrade;
		const int _executeGrade;
		AForm& operator=(const AForm& origin);

	public:
		AForm();
		AForm(std::string const name, int signGrade, int executeGrade);
		AForm(const AForm& origin);
		virtual ~AForm() throw();

		const std::string& getName() const;
		int getIsSigned() const;
		int getSignGrade() const;
		int getExecuteGrade() const;
		void setIsSigned(bool isSigned);

		void beSigned(const Bureaucrat& Bureaucrat);
		virtual void execute(Bureaucrat const & executor) const = 0;
		
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