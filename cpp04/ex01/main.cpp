#include "Dog.hpp"
#include "Cat.hpp"

void a()
{
	system("leaks a.out");
}

int main()
{
	//atexit(a);
	const Animal* i = new Cat();
	const Animal* j = new Dog();
	
	Animal *arr[6];
	for(int i = 0; i < 6; i++)
	{
		if (i % 2 == 0)
			arr[i] = new Cat();
		else
			arr[i] = new Dog();
	}
	for(int i = 0; i < 6; i++)
		delete arr[i];
	delete i;
	delete j;

	return 0;
}