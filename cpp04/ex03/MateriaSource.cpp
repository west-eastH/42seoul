#include "MateriaSource.hpp"

MateriaSource::MateriaSource()
{
	for (int i = 0; i < 4; i++)
		this->slot[i] = NULL;
}

MateriaSource::~MateriaSource()
{
	for(int i = 0; i < 4; i++)
	{
		if (this->slot[i] != NULL)
			delete this->slot[i];
	}
}

MateriaSource::MateriaSource(const MateriaSource &origin)
{

	for (int i = 0; i < 4; i++)
		this->slot[i] = origin.slot[i];
}

MateriaSource& MateriaSource::operator=(const MateriaSource &origin)
{
	if (this != &origin)
	{
		for(int i = 0; i < 3; i++)
		{
			delete this->slot[i];
			this->slot[i] = origin.slot[i];

		}

	}
	return *this;	
}

void MateriaSource::learnMateria(AMateria* m)
{
	for (int i = 0; i < 3; i++)
	{
		if (this->slot[i] == NULL)
		{
			this->slot[i] = m;
			break;
		}
	}

}
AMateria* MateriaSource::createMateria(std::string const & type)
{
	AMateria *temp;

	if (type == "ice")
		temp = new Ice(type);
	else if (type == "cure")
		temp = new Cure(type);
	else
		temp = NULL;
	return temp;
}