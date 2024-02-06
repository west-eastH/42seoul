#pragma once

class A;
class B;
class C;
#include <iostream>

class Base
{
	public:
		virtual ~Base();
};
Base *generate(void);
void identify(Base* p);
void identify(Base& p);

std::ostream &operator<<(std::ostream &out, const A &ref);
std::ostream &operator<<(std::ostream &out, const B &ref);
std::ostream &operator<<(std::ostream &out, const C &ref);
std::ostream &operator<<(std::ostream &out, const A *ptr);
std::ostream &operator<<(std::ostream &out, const B *ptr);
std::ostream &operator<<(std::ostream &out, const C *ptr);