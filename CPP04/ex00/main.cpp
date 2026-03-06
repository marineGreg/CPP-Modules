/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 16:26:26 by mgregoir          #+#    #+#             */
/*   Updated: 2026/03/06 15:29:10 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

    std::cout << "\n=== 2. TESTS SUR LA PILE (Stack) ===" << std::endl;
    Dog dog;
    Cat cat;
    dog.makeSound();
    cat.makeSound();

    std::cout << "\n=== 3. TESTS WRONG ANIMAL (Pas de virtual) ===" << std::endl;
    const WrongAnimal* wrongMeta = new WrongAnimal();
    const WrongAnimal* wrongCat = new WrongCat();

    std::cout << "Type: " << wrongCat->getType() << std::endl;
    wrongCat->makeSound(); // Affiche le son du WrongAnimal car pas de virtual
    wrongMeta->makeSound();

    delete wrongMeta;
    delete wrongCat;

    return 0;
}
