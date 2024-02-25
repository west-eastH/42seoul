#pragma once

#include <iostream>
#include <string>

class Harl
{
	private:
		std::string level;
		void debug(void);
		void info(void);
		void warning(void);
		void error(void);
	public:
		Harl(char *argv[]);
		void complain();
};