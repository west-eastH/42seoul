#include "Character.hpp"

Character::Character()
{
	this->name = "default";
	for (int i = 0; i < 4; i++)
		this->slot[i] = NULL;
}

Character::Character(std::string const & name)
{	
	this->name = name;
	for (int i = 0; i < 4; i++)
		this->slot[i] = NULL;
}

Character::~Character()
{
	for(int i = 0; i < 4; i++)
	{
		if (this->slot[i] != NULL)
			delete this->slot[i];
	}
}

Character::Character(const Character &origin)
{
	this->name = origin.getName();
	for (int i = 0; i < 4; i++)
		this->slot[i] = origin.slot[i];
}

Character& Character::operator=(const Character &origin)
{
	if (this != &origin)
	{
		this->name = origin.getName();
		for(int i = 0; i < 4; i++)
		{
			delete this->slot[i];
			this->slot[i] = origin.slot[i];
		}

	}
	return *this;	
}

std::string const & Character::getName() const
{
	return this->name;
}

void Character::equip(AMateria* m)
{
	for (int i = 0; i < 4; i++)
	{
		if (this->slot[i] == NULL)
		{
			this->slot[i] = m;
			break;
		}
	}
}

void Character::unequip(int idx)
{
	if (idx < 0 || idx > 3 || this->slot[idx] == NULL)
		return ;
	this->slot[idx] = NULL;
}

void Character::use(int idx, ICharacter& target)
{
	if (idx < 0 || idx > 3 || this->slot[idx] == NULL)
		return ;
	this->slot[idx]->use(target);
}
