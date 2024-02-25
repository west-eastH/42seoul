#include "Zombie.hpp"

void Zombie::announce(void)
{
	std::cout << this->name << " : BraiiiiiiinnnzzzZ..." << std::endl;
}

Zombie::Zombie()
{
}

Zombie::Zombie(std::string name)
{
	this->name = name;
	std::cout << this->name << " constructor called" << std::endl;
	
}

Zombie::~Zombie()
{
	std::cout << this->name << " Destructor called" << std::endl;
}

void	Zombie::set_name(std::string name)
{
	this->name = name;
}