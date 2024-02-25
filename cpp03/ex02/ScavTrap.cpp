#include "ScavTrap.hpp"


ScavTrap::ScavTrap()
{
	this->_hitPoints = 100;
	this->_energyPoints = 50;
	this->_attackDamage = 20;
	std::cout << "ScavTrap " << this->_name << " constructor called" << std::endl;
}

ScavTrap::ScavTrap(std::string name) : ClapTrap(name)
{
	this->_hitPoints = 100;
	this->_energyPoints = 50;
	this->_attackDamage = 20;
	std::cout << "ScavTrap " << this->_name << " constructor called" << std::endl;
}

ScavTrap::~ScavTrap()
{
	std::cout << "ScavTrap " << this->_name << " destructor called" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap &origin)
{
	this->_name = origin.getName();
	this->_hitPoints = origin.getHitPoints();
	this->_energyPoints = origin.getEnergyPoints();
	this->_attackDamage = origin.getAttackDamage();
	std::cout << "ScavTrap Copy constructor called" << std::endl;
}

ScavTrap& ScavTrap::operator=(const ScavTrap &origin)
{
	if (this != &origin)
	{
		this->_name = origin.getName();
		this->_hitPoints = origin.getHitPoints();
		this->_energyPoints = origin.getEnergyPoints();
		this->_attackDamage = origin.getAttackDamage();
		std::cout << "ScavTrap Copy assignment operator called" << std::endl;
	}
	return *this;
}

void ScavTrap::attack(const std::string &target)
{
	if (this->_hitPoints == 0)
		std::cout << "ScavTrap " << this->_name << " has no hit points" << std::endl;
	else if (this->_energyPoints == 0)
		std::cout << "ScavTrap " << this->_name << " has no energy points" << std::endl;
	else
	{
		this->_energyPoints--;
		std::cout << "ScavTrap " << this->_name << " attacks " << target << ", causing " << this->_attackDamage << " points of damage!" << std::endl;
	}
}

void ScavTrap::takeDamage(unsigned int amount)
{
	if (this->_hitPoints == 0)
		std::cout << "ScavTrap " << this->_name << " has no hit points" << std::endl;
	else
	{
		if (this->_hitPoints < amount)
			this->_hitPoints = 0;
		else
			this->_hitPoints -= amount;
		std::cout << "ScavTrap " << this->_name << " takes damage " << amount << ", current " << this->_name << " hitPoint : " << this->_hitPoints <<std::endl;
	}
}

void ScavTrap::beRepaired(unsigned int amount)
{
	if (this->_hitPoints == 0)
		std::cout << "ScavTrap " << this->_name << " has no hit points" << std::endl;
	else if (this->_energyPoints == 0)
		std::cout << "ScavTrap " << this->_name << " has no energy points" << std::endl;
	else
	{
		this->_hitPoints += amount;
		this->_energyPoints--;
		std::cout << "ScavTrap " << this->_name << " repairs itself " << amount << ", current " << this->_name << " hitPoint : " << this->_hitPoints <<std::endl;
	}
}

void ScavTrap::guardGate()
{
	if (this->_hitPoints == 0)
		std::cout << "ScavTrap " << this->_name << " has no hit points" << std::endl;
	else
		std::cout << "ScavTrap " << this->_name << " is now in Gate keeper mode." << std::endl;
}