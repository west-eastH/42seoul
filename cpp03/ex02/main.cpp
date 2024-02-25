#include "FragTrap.hpp"

int main ()
{
	FragTrap a("testAA");
	FragTrap b("testBB");

	a.attack("testBB");
	b.takeDamage(30);
	b.beRepaired(10);
	a.highFivesGuys();

	b.attack("testAA");
	a.takeDamage(30);
	a.beRepaired(20);
	b.highFivesGuys();
	b.attack("testAA");
	b.takeDamage(30);
	b.beRepaired(5);
	return 0;
}
