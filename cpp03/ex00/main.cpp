#include "ClapTrap.hpp"

int main ()
{
	ClapTrap a("testAA");
	ClapTrap b("testBB");

	a.attack("DDDDD");
	a.takeDamage(5);
	a.beRepaired(5);
	a.takeDamage(10);

	b.attack("DDDDD");
	b.attack("DDDDD");
	b.attack("DDDDD");
	b.attack("DDDDD");
	b.attack("DDDDD");
	b.attack("DDDDD");
	b.attack("DDDDD");
	b.attack("DDDDD");
	b.attack("DDDDD");
	b.attack("DDDDD");
	b.attack("DDDDD");
	b.attack("DDDDD");
	b.attack("DDDDD");
	b.attack("DDDDD");
	b.attack("DDDDD");
	a.takeDamage(5);
	a.beRepaired(5);

	b.attack("DDDDD");
	b.takeDamage(5);
	b.takeDamage(7);
	b.takeDamage(5);
	b.beRepaired(5);
	return 0;
}
