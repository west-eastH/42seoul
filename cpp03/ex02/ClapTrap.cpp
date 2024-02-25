#include "ClapTrap.hpp"

ClapTrap::ClapTrap()
{
	this->_name = "Default";
	this->_hitPoints = 10;
	this->_energyPoints = 10;
	this->_attackDamage = 0;
	std::cout << "ClapTrap " << this->_name << " constructor called" << std::endl;
}

ClapTrap::ClapTrap(std::string name)
{
	this->_name = name;
	this->_hitPoints = 10;
	this->_energyPoints = 10;
	this->_attackDamage = 0;
	std::cout << "ClapTrap " << this->_name << " constructor called" << std::endl;
}

ClapTrap::~ClapTrap()
{
	std::cout << "ClapTrap " << this->_name << " destructor called" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &origin)
{
	this->_name = origin.getName();
	this->_hitPoints = origin.getHitPoints();
	this->_energyPoints = origin.getEnergyPoints();
	this->_attackDamage = origin.getAttackDamage();
	std::cout << "ClapTrap Copy constructor called" << std::endl;
}

ClapTrap& ClapTrap::operator=(const ClapTrap &origin)
{
	if (this != &origin)
	{
		this->_name = origin.getName();
		this->_hitPoints = origin.getHitPoints();
		this->_energyPoints = origin.getEnergyPoints();
		this->_attackDamage = origin.getAttackDamage();
		std::cout << "ClapTrap Copy assignment operator called" << std::endl;
	}
	return *this;
}

const std::string& ClapTrap::getName() const
{
	return (this->_name);;
}

int ClapTrap::getHitPoints() const
{
	return (this->_hitPoints);
}

int ClapTrap::getEnergyPoints() const
{
	return (this->_energyPoints);
}

int ClapTrap::getAttackDamage() const
{
	return (this->_attackDamage);
}

void ClapTrap::attack(const std::string &target)
{
	if (this->_hitPoints == 0)
		std::cout << "ClapTrap " << this->_name << " has no hit points" << std::endl;
	else if (this->_energyPoints == 0)
		std::cout << "ClapTrap " << this->_name << " has no energy points" << std::endl;
	else
	{
		this->_energyPoints--;
		std::cout << "ClapTrap " << this->_name << " attacks " << target << ", causing " << this->_attackDamage << " points of damage!" << std::endl;
	}
}

void ClapTrap::takeDamage(unsigned int amount)
{
	if (this->_hitPoints == 0)
		std::cout << "ClapTrap " << this->_name << " has no hit points" << std::endl;
	else
	{
		if (this->_hitPoints < amount)
			this->_hitPoints = 0;
		else
			this->_hitPoints -= amount;
		std::cout << "ClapTrap " << this->_name << " takes damage " << amount << ", current " << this->_name << " hitPoint : " << this->_hitPoints <<std::endl;
	}
}

void ClapTrap::beRepaired(unsigned int amount)
{
	if (this->_hitPoints == 0)
		std::cout << "ClapTrap " << this->_name << " has no hit points" << std::endl;
	else if (this->_energyPoints == 0)
		std::cout << "ClapTrap " << this->_name << " has no energy points" << std::endl;
	else
	{
		this->_hitPoints += amount;
		this->_energyPoints--;
		std::cout << "ClapTrap " << this->_name << " repairs itself " << amount << ", current " << this->_name << " hitPoint : " << this->_hitPoints <<std::endl;
	}
}
