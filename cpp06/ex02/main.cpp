#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

int main ()
{
	srand(time(NULL));
	Base *test1 = generate();
	Base *test2 = generate();
	Base *test3 = generate();
	identify(test1);
	identify(test2);
	identify(test3);
	A a;
	identify(a);
	B b;
	identify(b);
	C c;
	identify(c);
	delete test1;
	delete test2;
	delete test3;
	return 0;
}
