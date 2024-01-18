#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongCat.hpp"

void a()
{
	system("leaks a.out");
}

int main()
{
	//atexit(a);
	const Animal* meta = new Animal();
	const Animal* j = new Dog();
	const Animal* i = new Cat();
	const WrongAnimal* meta2 = new WrongAnimal();
	const WrongAnimal* k = new WrongCat();

	std::cout << j->getType() << " " << std::endl;
	std::cout << i->getType() << " " << std::endl;
	std::cout << k->getType() << " " << std::endl;
	i->makeSound(); //will output the cat sound!
	j->makeSound();
	meta->makeSound();

	meta2->makeSound();
	k->makeSound();
	delete i;
	delete j;
	delete meta;
	delete meta2;
	delete k;

	return 0;
}