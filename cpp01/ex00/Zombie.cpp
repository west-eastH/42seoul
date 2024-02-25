#include "Zombie.hpp"

void Zombie::announce(void)
{
	std::cout << this->name << " : BraiiiiiiinnnzzzZ..." << std::endl;
}

Zombie::Zombie()
{
	this->name = "default";
	std::cout << "Default constructor called" << std::endl;
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
