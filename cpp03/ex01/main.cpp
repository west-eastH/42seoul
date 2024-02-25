#include "ScavTrap.hpp"

int main ()
{
	ScavTrap a("testAA");
	ScavTrap b("testBB");

	a.attack("testBB");
	b.takeDamage(20);
	b.beRepaired(10);
	a.guardGate();

	b.attack("testAA");
	a.takeDamage(30);
	a.takeDamage(30);
	a.takeDamage(30);
	a.takeDamage(30);
	a.takeDamage(30);
	a.takeDamage(20);
	a.takeDamage(20);
	a.takeDamage(20);
	a.takeDamage(20);
	a.takeDamage(20);
	a.takeDamage(20);
	a.beRepaired(20);
	b.guardGate();
	b.attack("testAA");
	b.takeDamage(20);
	b.beRepaired(5);
	return 0;
}
