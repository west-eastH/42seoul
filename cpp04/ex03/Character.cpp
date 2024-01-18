#include "Character.hpp"

Character::Character()
{
	this->_name = "default";
	for (int i = 0; i < 4; i++)
		this->_slot[i] = NULL;
}

Character::Character(std::string const & name)
{	
	this->_name = name;
	for (int i = 0; i < 4; i++)
		this->_slot[i] = NULL;
}

Character::~Character()
{
	for(int i = 0; i < 4; i++)
	{
		if (this->_slot[i] != NULL)
			delete this->_slot[i];
	}
}

Character::Character(const Character &origin)
{
	this->_name = origin.getName();
	for (int i = 0; i < 4; i++)
	{
		if (origin._slot[i] != NULL)
			this->_slot[i] = origin._slot[i]->clone();
		else
			this->_slot[i] = NULL;
	}
}

Character& Character::operator=(const Character &origin)
{
	if (this != &origin)
	{
		this->_name = origin.getName();
		for(int i = 0; i < 4; i++)
		{
			if (this->_slot[i] != NULL)
				delete this->_slot[i];
			if (origin._slot[i] != NULL)
				this->_slot[i] = origin._slot[i]->clone();
			else
				this->_slot[i] = NULL;
		}
	}
	return *this;
}

std::string const & Character::getName() const
{
	return this->_name;
}

void Character::equip(AMateria* m)
{
	for (int i = 0; i < 4; i++)
	{
		if (this->_slot[i] == NULL)
		{
			this->_slot[i] = m;
			break;
		}
	}
}

void Character::unequip(int idx)
{
	if (idx < 0 || idx > 3 || this->_slot[idx] == NULL)
		return ;
	Floor::addItem(this->_slot[idx]);
	this->_slot[idx] = NULL;
}

void Character::use(int idx, ICharacter& target)
{
	if (idx < 0 || idx > 3 || this->_slot[idx] == NULL)
		return ;
	this->_slot[idx]->use(target);
}
