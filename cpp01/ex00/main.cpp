#include "Zombie.hpp"

int main()
{
	Zombie zom = Zombie();
	Zombie zom1 = Zombie("test");
	Zombie *zom2 = newZombie("test1");
	randomChump("test2");
	delete(zom2);
	return 0;
}
