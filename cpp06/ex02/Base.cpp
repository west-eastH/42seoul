#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
Base::~Base(){}
Base *generate(void)
{
	Base *t = NULL;
	Base *b = dynamic_cast<A*>(t);
	return b;
}

void identify(Base* p)
{
	std::cout << p << std::endl;
}
void identify(Base& p)
{
	std::cout << dynamic_cast<Base*>(&p) << std::endl;
}