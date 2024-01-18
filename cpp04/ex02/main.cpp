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
	
	Animal *arr[10];
	for(int i = 0; i < 10; i++)
	{
		if (i % 2 == 0)
			arr[i] = new Cat();
		else
			arr[i] = new Dog();
	}
	for(int i = 0; i < 10; i++)
		delete arr[i];
	delete i;
	delete j;
	/* Cat test1;
	Cat test2 = test1;
	for (int i = 0; i < 5; i++)
	{
		test1.getBrain()->setIdea("test", i);
	}
	for (int i = 0; i < 10; i++)
	{
		std::cout << test1.getBrain()->getIdea(i) << std::endl;
		std::cout << test2.getBrain()->getIdea(i) << std::endl;
	}
 */
	return 0;
}