#include "Contact.hpp"

void Contact::set_data(std::string first_name, std::string last_name, std::string nickname, std::string phone_number, std::string secret)
{
	this->first_name = first_name;
	this->last_name = last_name;
	this->nickname = nickname;
	this->phone_number = phone_number;
	this->secret = secret;
}
std::string Contact::get_first_name()
{
	return (this->first_name);
}
std::string Contact::get_last_name()
{
	return (this->last_name);
}
std::string Contact::get_nickname()
{
	return (this->nickname);
}
std::string Contact::get_phone_number()
{
	return (this->phone_number);
}
std::string Contact::get_secret()
{
	return (this->secret);
}