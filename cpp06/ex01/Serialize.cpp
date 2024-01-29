#include "Serialize.hpp"

Serialize::Serialize() {}
Serialize::~ Serialize() {}
Serialize::Serialize(const Serialize& origin) {(void)origin;}
Serialize& Serialize::operator=(const Serialize& origin) {(void)origin; return *this;}
uintptr_t Serialize::serialize(Data *ptr)
{
	uintptr_t *uptr = reinterpret_cast<uintptr_t*>(&ptr);
	return *uptr;
}

Data* Serialize::deserialize(uintptr_t raw)
{
	Data* data = reinterpret_cast<Data*>(raw);
	return data;
}