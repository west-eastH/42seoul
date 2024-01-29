#include "Serialize.hpp"
/* 
void a()
{
	system("leaks a.out");
} */

int main ()
{
	//atexit(a);
	Data *d1 = new Data();
	d1->name = "dongseo";
	d1->age = 26;
	Data *d2 = Serialize::deserialize(Serialize::serialize(d1));
	Data *d3 = Serialize::deserialize(Serialize::serialize(Serialize::deserialize(Serialize::serialize(d1))));
	std::cout<< "d1 : name = " << d1->name << " age = " << d1->age << " address = " << d1 << std::endl;
	std::cout<< "d2 : name = " << d2->name << " age = " << d2->age << " address = " << d2 << std::endl;
	std::cout<< "d3 : name = " << d3->name << " age = " << d3->age << " address = " << d3 << std::endl;
	delete d1;
	return 0;
}
