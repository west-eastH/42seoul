#include "Manager.hpp"

Manager::Manager(Argument &arg) : argument(arg)
{
}

void Manager::start()
{
	if (input_open())
		return ;
	my_replace();
	output_open();
}

bool Manager::input_open()
{
	std::ifstream in(this->argument.getFileName());
	if (in.is_open())
	{
		in.seekg(0, std::ios::end);
		int size = in.tellg();
		this->old_data.resize(size);
		in.seekg(0, std::ios::beg);
		in.read(&this->old_data[0], size);
		in.close();
		return 0;
	}
	std::cout << "file open error" << std::endl;
	return (1);
}

void Manager::my_replace()
{
	int start;
	size_t end;
	int tar_len;
	int len;

	start = 0;
	tar_len = this->argument.getTarget().length();
	end = this->old_data.find(this->argument.getTarget(), start);
	len = end;
	while (end != std::string::npos)
	{
		this->new_data += this->old_data.substr(start, len);
		this->new_data += this->argument.getChange();
		start = end + tar_len;
		end = this->old_data.find(this->argument.getTarget(), start);
		len = end - start;
	}
	this->new_data += this->old_data.substr(start);
}

void Manager::output_open()
{
	std::string output_file;
	output_file = this->argument.getFileName() + ".replace";
	std::ifstream check(output_file);
	if (check.is_open())
	{
		std::cout << output_file << " already exists" << std::endl;
		check.close();
		return ;
	}
	std::ofstream out(output_file);
	if (out.is_open())
	{
		out << this->new_data;
		out.close();
		return ;
	}
	std::cout << "Replace failed" << std::endl;
}
