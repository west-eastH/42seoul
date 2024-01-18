#include "Floor.hpp"

int Floor::_maxCnt = 4;
int Floor::_curIdx = 0;
AMateria **Floor::_items = new AMateria*[4];

Floor::Floor()
{
	for (int i = 0; i < _maxCnt; i++)
		_items[i] = NULL;
}

Floor::~Floor()
{
	if (_items != NULL)
	{
		for (int i = 0; i < _maxCnt; i++)
		{
			if (_items[i] != NULL)
				delete _items[i];
		}
		delete[] _items;
		_items = NULL;
	}
}

Floor::Floor(const Floor &origin)
{
	for (int i = 0; i < 4; i++)
	{
		if (origin._items[i] != NULL)
			this->_items[i] = origin._items[i]->clone();
		else
			this->_items[i] = NULL;
	}
}

Floor& Floor::operator=(const Floor &origin)
{
	if (this != &origin)
	{
		for(int i = 0; i < _maxCnt; i++)
		{
			if (this->_items[i] != NULL)
				delete this->_items[i];
			if (origin._items[i] != NULL)
				this->_items[i] = origin._items[i]->clone();
			else
				this->_items[i] = NULL;
		}
	}
	return *this;
}

void Floor::addItem(AMateria *item)
{
	if (item == NULL)
		return ;
	if (_items[_maxCnt - 1])
		increase_Space();
	_items[_curIdx] = item;
	_curIdx++;
}

void Floor::increase_Space()
{
	AMateria **temp;

	temp = new AMateria*[_maxCnt * 2];
	for (int i = 0; i < _maxCnt; i++)
	{
		temp[i] = _items[i]->clone();
		delete _items[i];
	}
	delete[] _items;
	_maxCnt *= 2;
	_items = temp;
}
