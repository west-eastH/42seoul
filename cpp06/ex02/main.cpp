#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
int main ()
{
	Base *test1 = generate();
	Base *test2 = generate();
	Base *test3 = generate();
	identify(test1);
	identify(test2);
	identify(test3);
	return 0;
}
