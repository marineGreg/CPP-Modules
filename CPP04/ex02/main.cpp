
#include "AAnimal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main() {
    // std::cout << "=== TEST INSTANCIATION IMPOSSIBLE ===" << std::endl;
    // AAnimal test; // DECOMMENTER CETTE LIGNE DOIT PROVOQUER UNE ERREUR DE COMPILATION
    // AAnimal* test2 = new AAnimal(); // CELLE-CI AUSSI

    std::cout << "=== TEST POLYMORPHISME (Classe Abstraite) ===" << std::endl;
    const AAnimal* j = new Dog();
    const AAnimal* i = new Cat();

    std::cout << "Type de j: " << j->getType() << std::endl;
    std::cout << "Type de i: " << i->getType() << std::endl;

    j->makeSound();
    i->makeSound();

    delete j;
    delete i;

    std::cout << "\n=== TEST DEEP COPY SUR CHIEN ABSTRAIT ===" << std::endl;
    Dog original;
    Dog copy(original);
    
    std::cout << "Type Original: " << original.getType() << std::endl;
    std::cout << "Type Copy: " << copy.getType() << std::endl;

    return 0;
}
