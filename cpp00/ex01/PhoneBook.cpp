#include "PhoneBook.hpp"

PhoneBook::PhoneBook()
{
	this->idx = 0;
}

int check_data(std::string data)
{
	int len;

	len = data.length();
	if (len == 0)
		return (1);
	for (int i = 0; i < len; i++)
	{
		if (data[i] < 32 || data[i] == 127)
			return (1);
		if (!(data[i] == 32 || (data[i] >= 9 && data[i] <= 13)))
			return (0);
	}
	return (1);
}

int	PhoneBook::add()
{
	std::string first_name;
	std::string last_name;
	std::string nickname;
	std::string phone_number;
	std::string secret;

	if (this->idx == 8)
	{
		for (int i = 0; i < 7; i++)
			this->con[i] = this->con[i + 1];
		this->idx = 7;
	}
	std::cout << "first_name :";
	std::getline(std::cin, first_name);
	if (std::cin.eof())
		return (1);
	if (check_data(first_name))
	{
		std::cout << "contact can't have empty fields!!" << std::endl;
		return (0);
	}
	std::cout << "last_name :";
	std::getline(std::cin, last_name);
	if (std::cin.eof())
		return (1);
	if (check_data(last_name))
	{
		std::cout << "contact can't have empty fields!!" << std::endl;
		return (0);
	}
	std::cout << "nickname :";
	std::getline(std::cin, nickname);
	if (std::cin.eof())
		return (1);
	if (check_data(nickname))
	{
		std::cout << "contact can't have empty fields!!" << std::endl;
		return (0);
	}
	std::cout << "phone_number :";
	std::getline(std::cin, phone_number);
	if (std::cin.eof())
		return (1);
	if (check_data(phone_number))
	{
		std::cout << "contact can't have empty fields!!" << std::endl;
		return (0);
	}
	std::cout << "secret :";
	std::getline(std::cin, secret);
	if (std::cin.eof())
		return (1);
	if (check_data(secret))
	{
		std::cout << "contact can't have empty fields!!" << std::endl;
		return (0);
	}
	this->con[this->idx].set_data(first_name, last_name, nickname, phone_number, secret);
	this->idx++;
	return (0);
}

void PhoneBook::print_data(std::string data, int pipe)
{
	int i;
	int len;

	len = data.length();
	for (i = 0; i < 10 - len; i++)
		std::cout << " ";
	for (i = 0; i < len; i++)
	{
		if (len > 10 && i == 9)
			break;
		std::cout << data[i];
	}
	if (len > 10)
		std::cout << ".";
	if (pipe)
		std::cout << "|";
}

int	PhoneBook::detail()
{
	std::string	str;
	int			i;

	std::cout << "detail idx : ";
	std::getline(std::cin, str);
	if (std::cin.eof())
		return (1);
	if (str.length() > 1 || str[0] < '0' || str[0] >= this->idx + '0')
	{
		std::cout << "error : not valid index" << std::endl;
		return 0;
	}
	i = str[0] - '0';
	std::cout << "[" << i << "] first name : " << this->con[i].get_first_name() << std::endl;
	std::cout << "[" << i << "] last name  : " << this->con[i].get_last_name() << std::endl;
	std::cout << "[" << i << "] nick name  : " << this->con[i].get_nickname() << std::endl;
	std::cout << "[" << i << "] phone num  : " << this->con[i].get_phone_number() << std::endl;
	std::cout << "[" << i << "] secret     : " << this->con[i].get_secret() << std::endl;
	return (0);
}

int PhoneBook::search()
{
	if (this->idx == 0)
	{
		std::cout << "Phone Book is Empty!!" << std::endl;
		return 0;
	}
	for(int i = 0; i < this->idx; i++)
	{
		print_data(std::to_string(i), 1);
		print_data(this->con[i].get_first_name(), 1);
		print_data(this->con[i].get_last_name(), 1);
		print_data(this->con[i].get_nickname(), 0);
		std::cout << std::endl;
	}
	if (PhoneBook::detail())
		return (1);
	return 0;
}
void PhoneBook::start()
{
	std::string cmd;

	std::cout << "cmd : ";
	while (std::getline(std::cin, cmd))
	{
		if (cmd.compare("ADD") == 0)
		{
			if (PhoneBook::add())
				return ;
		}
		else if (cmd.compare("SEARCH") == 0)
		{
			if (PhoneBook::search())
				return ;
		}
		else if (cmd.compare("EXIT") == 0)
			return ;
		else
			std::cout << "cmd error..." << std::endl;
		std::cout << "cmd : ";
	}
}
