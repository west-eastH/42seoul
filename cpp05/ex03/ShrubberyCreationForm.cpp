#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm() : AForm("ShrubberyCreaationForm", 145, 137), _target("default_target") {}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string target) : AForm("ShrubberyCreaationForm", 145, 137), _target(target) {}

ShrubberyCreationForm::~ShrubberyCreationForm() throw() {}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& origin) : AForm(origin.getName(), origin.getSignGrade(), origin.getExecuteGrade()), _target(origin.getTarget())
{
}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& origin)
{
	setIsSigned(origin.getIsSigned());
	return *this;
}

const std::string& ShrubberyCreationForm::getTarget() const
{
	return _target;
}

void ShrubberyCreationForm::createAsciiTree() const
{
	std::string output_file = _target + "_shrubbery";
	std::string asciiTree =
        "            .        +          .      .          .\n"
        "     .            _        .                    .\n"
        "  ,              /;-._,-.____        ,-----.__\n"
        " ((        .    (_:#::_.:::. `-._   /:, /-._, `._,\n"
        "  `                 \\   _|`\"=:_::.`.);  \\ __/ /\n"
        "                      ,    `./  \\:. `.   )==-\'  .\n"
        "    .      ., ,-=-.  ,\\, +#./`   \\:.  / /           .\n"
        ".           \\/:/`-' , ,\\ '` ` `   ): , /_  -o\n"
        "       .    /:+- - + +- : :- + + -:'  /(o-) \\)     .\n"
        "  .      ,=':  \\    ` `/` ' , , ,:' `'--\".--\"---._/`7\n"
        "   `.   (    \\: \\,-._` ` + '\\, ,\"   _,--._,---\":.__/\n"
        "              \\:  `  X` _| _,\\/\'   .-'\n"
        ".               \":._:`\\____  /:'  /      .           .\n"
        "                    \\::.  :\\/:'  /              +\n"
        "   .                 `.:.  /:'  }      .\n"
        "           .           ):_(:;   \\           .\n"
        "                      /:. _/ ,  |\n"
        "                   . (|::.     ,`                  .\n"
        "     .                |::.    {\\\n"
        "                      |::.\\  \\ `.\n"
        "                      |:::(\\    |\n"
        "              O       |:::/{ }  |                  (o\n"
        "               )  ___/#\\::`/ (O \"==._____   O, (O  /`\n"
        "          ~~~w/w~\"~~,\\` `:/,-(~`\"~~~~~~~~\"~o~\\~/~w|/~\n"
        "dew   ~~~~~~~~~~~~~~~~~~~~~~~\\\\W~~~~~~~~~~~~\\|/~~";
	std::ofstream out(output_file);
	if (out.is_open())
	{
		out << asciiTree;
		out.close();
		return ;
	}
}

void ShrubberyCreationForm::execute(Bureaucrat const & executor) const
{
	if (executor.getGrade() > getExecuteGrade())
		throw AForm::GradeTooLowException(executor.getName() + " Bureaucrat couldn’t execute " + getName() + ". because " + executor.getName() + "'s grade is too Low.");
	createAsciiTree();
}

std::ostream	&operator<<(std::ostream &out, const ShrubberyCreationForm &ref)
{
	out << ref.getName() << ", form status : " << ref.getIsSigned() << " signGrade : " << ref.getSignGrade() << " executeGrade : " << ref.getExecuteGrade() << " target : " << ref.getTarget();
	return out;
}

