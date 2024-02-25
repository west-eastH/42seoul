#include "Zombie.hpp"

int main()
{
	Zombie *zoms;
	int N;

	N = 15;
	zoms = zombieHorde(N, "test");
	for(int i = 0; i < N; i++)
		zoms[i].announce();
	delete [] zoms;
	return (0);
}