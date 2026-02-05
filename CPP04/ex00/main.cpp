/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 16:26:26 by mgregoir          #+#    #+#             */
/*   Updated: 2026/02/05 16:26:27 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main() {
    std::cout << "=== TEST 1: Polymorphisme de base (sujet) ===" << std::endl;
    const Animal* meta = new Animal();
    const Animal* j = new Dog();
    const Animal* i = new Cat();

    std::cout << j->getType() << " " << std::endl;
    std::cout << i->getType() << " " << std::endl;
    i->makeSound(); // Son du chat
    j->makeSound(); // Son du chien
    meta->makeSound();

    delete meta;
    delete j;
    delete i;

    std::cout << "\n=== TEST 2: WrongAnimal (sans virtual) ===" << std::endl;
    const WrongAnimal* wrongMeta = new WrongAnimal();
    const WrongAnimal* wrongCat = new WrongCat();

    std::cout << "Type de wrongCat: " << wrongCat->getType() << std::endl;
    wrongCat->makeSound(); // Son de WrongAnimal (pas de polymorphisme!)
    wrongMeta->makeSound();

    delete wrongMeta;
    delete wrongCat;

    std::cout << "\n=== TEST 3: Constructeur de copie ===" << std::endl;
    Dog originalDog;
    Dog copiedDog(originalDog);
    std::cout << "Original type: " << originalDog.getType() << std::endl;
    std::cout << "Copied type: " << copiedDog.getType() << std::endl;

    std::cout << "\n=== TEST 4: Operateur d'assignation ===" << std::endl;
    Cat cat1;
    Cat cat2;
    cat2 = cat1;
    cat1.makeSound();
    cat2.makeSound();

    std::cout << "\n=== TEST 5: Tableau d'animaux polymorphe ===" << std::endl;
    const Animal* animals[4];
    animals[0] = new Dog();
    animals[1] = new Cat();
    animals[2] = new Dog();
    animals[3] = new Cat();

    for (int idx = 0; idx < 4; idx++) {
        std::cout << "Animal " << idx << " est un " << animals[idx]->getType() 
                  << " qui fait: ";
        animals[idx]->makeSound();
    }

    for (int idx = 0; idx < 4; idx++) {
        delete animals[idx];
    }

    std::cout << "\n=== TEST 6: Comparaison Animal vs WrongAnimal ===" << std::endl;
    std::cout << "Avec virtual (Animal):" << std::endl;
    const Animal* cat = new Cat();
    cat->makeSound();
    delete cat;

    std::cout << "\nSans virtual (WrongAnimal):" << std::endl;
    const WrongAnimal* wrongCat2 = new WrongCat();
    wrongCat2->makeSound();
    delete wrongCat2;

    return 0;
}
