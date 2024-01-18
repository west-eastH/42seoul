#pragma once
#include <iostream>

class Form
{
	private:
		const std::string _name;
		bool _isSigned;
		const unsigned int signGrade;
		const unsigned int executeGrade;
		Form(const Form& origin);
		Form& operator=(const Form& origin);

	public:
		Form();
		~Form();
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
