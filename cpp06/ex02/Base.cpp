#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
Base::~Base(){}
Base *generate(void)
{
	Base *temp;
	
	if (rand() % 3 == 0)
		temp = new A();
	else if (rand() % 3 == 1)
		temp = new B();
	else
		temp = new C();
	return temp;
}

void identify(Base* p)
{
	A *a = dynamic_cast<A*>(p);
	if (a)
		std::cout << a << std::endl;
	B *b = dynamic_cast<B*>(p);
	if (b)
		std::cout << b << std::endl;
	C *c = dynamic_cast<C*>(p);
	if (c)
		std::cout << c << std::endl;
}

void identify(Base& p)
{
	try
	{
		A &a = dynamic_cast<A&>(p);
		std::cout << a << std::endl;
	}
	catch(const std::exception& e)
	{
	}
	try
	{
		B &b = dynamic_cast<B&>(p);
		std::cout << b << std::endl;
	}
	catch(const std::exception& e)
	{
	}
	try
	{
		C &c = dynamic_cast<C&>(p);
		std::cout << c << std::endl;
	}
	catch(const std::exception& e)
	{
	}
	
}


std::ostream &operator<<(std::ostream &out, const A &ref)
{
	(void)ref;
	out << "A";
	return out;
}

std::ostream &operator<<(std::ostream &out, const B &ref)
{
	(void)ref;
	out << "B";
	return out;
}

std::ostream &operator<<(std::ostream &out, const C &ref)
{
	(void)ref;
	out << "C";
	return out;
}

std::ostream &operator<<(std::ostream &out, const A *ptr)
{
	(void)ptr;
	out << "A";
	return out;
}

std::ostream &operator<<(std::ostream &out, const B *ptr)
{
	(void)ptr;
	out << "B";
	return out;
}

std::ostream &operator<<(std::ostream &out, const C *ptr)
{
	(void)ptr;
	out << "C";
	return out;
}
