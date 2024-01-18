#pragma once

#include "AMateria.hpp"
#include "Ice.hpp"
#include "Cure.hpp"

class Floor
{
private:
	static AMateria **_items;
	static int _maxCnt;
	static int _curIdx;
public:
	Floor();
	~Floor();
	Floor(const Floor &origin);
	Floor& operator=(const Floor &origin);

	static void addItem(AMateria *item);
	static void increase_Space();
};
