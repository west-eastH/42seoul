#pragma once

#include <iostream>

struct Data
{
	int age;
	std::string name;
};

class  Serialize
{
private:
	Serialize();
	~ Serialize();
	Serialize(const Serialize& origin);
	Serialize& operator=(const Serialize& origin);
public:
	static uintptr_t serialize(Data *ptr);
	static Data* deserialize(uintptr_t raw);
};

