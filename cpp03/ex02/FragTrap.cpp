#include "FragTrap.hpp"

FragTrap::FragTrap()
{
	this->_hitPoints = 100;
	this->_energyPoints = 100;
	this->_attackDamage = 30;
	std::cout << "FragTrap " << this->_name << " constructor called" << std::endl;
}

FragTrap::FragTrap(std::string name) : ClapTrap(name)
{
	this->_hitPoints = 100;
	this->_energyPoints = 100;
	this->_attackDamage = 30;
	std::cout << "FragTrap " << this->_name << " constructor called" << std::endl;
}

FragTrap::~FragTrap()
{
	std::cout << "FragTrap " << this->_name << " destructor called" << std::endl;
}

FragTrap::FragTrap(const FragTrap &origin)
{
	this->_name = origin.getName();
	this->_hitPoints = origin.getHitPoints();
	this->_energyPoints = origin.getEnergyPoints();
	this->_attackDamage = origin.getAttackDamage();
	std::cout << "FragTrap " << "Copy constructor called" << std::endl;
}

FragTrap& FragTrap::operator=(const FragTrap &origin)
{
	if (this != &origin)
	{
		this->_name = origin.getName();
		this->_hitPoints = origin.getHitPoints();
		this->_energyPoints = origin.getEnergyPoints();
		this->_attackDamage = origin.getAttackDamage();
		std::cout << "FragTrap " << "Copy assignment operator called" << std::endl;
	}
	return *this;
}

void FragTrap::attack(const std::string &target)
{
	if (this->_hitPoints == 0)
		std::cout << "FragTrap " << this->_name << " has no hit points" << std::endl;
	else if (this->_energyPoints == 0)
		std::cout << "FragTrap " << this->_name << " has no energy points" << std::endl;
	else
	{
		this->_energyPoints--;
		std::cout << "FragTrap " << this->_name << " attacks " << target << ", causing " << this->_attackDamage << " points of damage!" << std::endl;
	}
}

void FragTrap::takeDamage(unsigned int amount)
{
	if (this->_hitPoints == 0)
		std::cout << "FragTrap " << this->_name << " has no hit points" << std::endl;
	else
	{
		if (this->_hitPoints < amount)
			this->_hitPoints = 0;
		else
			this->_hitPoints -= amount;
		std::cout << "FragTrap " << this->_name << " takes damage " << amount << ", current " << this->_name << " hitPoint : " << this->_hitPoints <<std::endl;
	}
}

void FragTrap::beRepaired(unsigned int amount)
{
	if (this->_hitPoints == 0)
		std::cout << "FragTrap " << this->_name << " has no hit points" << std::endl;
	else if (this->_energyPoints == 0)
		std::cout << "FragTrap " << this->_name << " has no energy points" << std::endl;
	else
	{
		this->_hitPoints += amount;
		this->_energyPoints--;
		std::cout << "FragTrap " << this->_name << " repairs itself " << amount << ", current " << this->_name << " hitPoint : " << this->_hitPoints <<std::endl;
	}
}

void FragTrap::highFivesGuys(void)
{
	if (this->_hitPoints == 0)
		std::cout << "ScavTrap " << this->_name << " has no hit points" << std::endl;
	else
		std::cout << "FragTrap " << this->_name << " requests high fives you" << std::endl;
}
