#include "Argument.hpp"

Argument::Argument(char *argv[])
{
	this->file_name = argv[1];
	this->target = argv[2];
	this->change = argv[3];
}

std::string Argument::getFileName()
{
	return this->file_name;
}

std::string Argument::getTarget()
{
	return this->target;
}

std::string Argument::getChange()
{
	return this->change;
}