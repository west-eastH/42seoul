#include "Zombie.hpp"
Zombie*	zombieHorde( int N, std::string name )
{
	Zombie *Zoms = new Zombie[N];
	for (int i = 0; i < N; i++)
		Zoms[i].set_name(name);
	return (Zoms);
}