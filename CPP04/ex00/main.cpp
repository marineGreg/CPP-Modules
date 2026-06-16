
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main() {
    std::cout << "=== 1. TESTS DU SUJET (Polymorphisme) ===" << std::endl;
    const Animal* meta = new Animal();
    const Animal* j = new Dog();
    const Animal* i = new Cat();

    std::cout << "Type: " << j->getType() << " " << std::endl;
    std::cout << "Type: " << i->getType() << " " << std::endl;
    
    i->makeSound();
    j->makeSound();
    meta->makeSound();

    delete meta;
    delete j;
    delete i;

    std::cout << "\n=== 2. TESTS SUPPLÉMENTAIRES (Stack & Copy) ===" << std::endl;

    Dog originalDog;
    std::cout << "Type de originalDog : " << originalDog.getType() << std::endl;

    Dog copyDog(originalDog);
    std::cout << "Type de copyDog : " << copyDog.getType() << std::endl;
    copyDog.makeSound();

    Cat stackCat;
    stackCat.makeSound();

    std::cout << "\n=== 3. TESTS WRONG ANIMAL (Pas de virtual) ===" << std::endl;
    const WrongAnimal* wrongMeta = new WrongAnimal();
    const WrongAnimal* wrongCat = new WrongCat();

    std::cout << "Type: " << wrongCat->getType() << std::endl;
    wrongCat->makeSound();
    wrongMeta->makeSound();

    delete wrongMeta;
    delete wrongCat;

    return 0;
}
