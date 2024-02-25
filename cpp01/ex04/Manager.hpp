#pragma once

#include <fstream>
#include "Argument.hpp"

class Manager
{
	private:
		Argument argument;
		std::string old_data;
		std::string new_data;
	public:
		Manager(Argument &arg);
		void start();
		bool input_open();
		void my_replace();
		void output_open();
};