#include "MateriaSource.hpp"

MateriaSource::MateriaSource()
{
	for (int i = 0; i < 4; i++)
		this->_slot[i] = NULL;
}

MateriaSource::~MateriaSource()
{
	for(int i = 0; i < 4; i++)
	{
		if (this->_slot[i] != NULL)
			delete this->_slot[i];
	}
}

MateriaSource::MateriaSource(const MateriaSource &origin)
{
	for (int i = 0; i < 4; i++)
	{
		if (origin._slot[i] != NULL)
			this->_slot[i] = origin._slot[i]->clone();
		else
			this->_slot[i] = NULL;
	}
}

MateriaSource& MateriaSource::operator=(const MateriaSource &origin)
{
	if (this != &origin)
	{
		for (int i = 0; i < 4; i++)
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

void MateriaSource::learnMateria(AMateria* m)
{
	for (int i = 0; i < 3; i++)
	{
		if (this->_slot[i] == NULL)
		{
			this->_slot[i] = m;
			break;
		}
	}

}

AMateria* MateriaSource::createMateria(std::string const & type)
{
	AMateria *temp;

	temp = NULL;
	for (int i = 0; i < 4; i++)
	{
		if (this->_slot[i] && !this->_slot[i]->getType().compare(type))
			temp = this->_slot[i]->clone();
	}
	return temp;
}