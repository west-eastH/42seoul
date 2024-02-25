#pragma once

#include <iostream>
#include <string>

class Argument
{
	private:
		std::string file_name;
		std::string target;
		std::string change;
	public:
		Argument(char *argv[]);
		std::string getFileName();
		std::string getTarget();
		std::string getChange();
};