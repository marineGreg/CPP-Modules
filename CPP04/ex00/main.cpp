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
    // --- 1. TESTS DU SUJET (Polymorphisme avec pointeurs) ---
    std::cout << "\n=== TESTS DU SUJET ===" << std::endl;
    const Animal* meta = new Animal();
    const Animal* j = new Dog();
    const Animal* i = new Cat();

    std::cout << j->getType() << " " << std::endl;
    std::cout << i->getType() << " " << std::endl;
    
    i->makeSound(); // Sortie attendue : Meow!
    j->makeSound(); // Sortie attendue : Woof!
    meta->makeSound(); // Sortie attendue : Generic Animal sound

    delete meta;
    delete j;
    delete i;

    // --- 2. TESTS SUPPLEMENTAIRES (Allocation sur la pile & Copie) ---
    std::cout << "\n=== TESTS SUPPLÉMENTAIRES (Stack & Copy) ===" << std::endl;
    
    Dog originalDog;
    std::cout << "Type de originalDog : " << originalDog.getType() << std::endl;
    
    Dog copyDog(originalDog); // Test du constructeur de recopie
    std::cout << "Type de copyDog : " << copyDog.getType() << std::endl;
    copyDog.makeSound();

    Cat stackCat;
    stackCat.makeSound();

    // --- 3. TESTS DU CAS "WRONG" (Preuve par l'erreur) ---
    std::cout << "\n=== TESTS WRONG ANIMAL (Pas de polymorphisme) ===" << std::endl;
    
    const WrongAnimal* wrongMeta = new WrongAnimal();
    const WrongAnimal* wrongCat = new WrongCat();

    std::cout << "Type : " << wrongCat->getType() << std::endl;
    
    // Ici, malgré que ce soit un WrongCat, il va faire le son du WrongAnimal 
    // car la methode n'est pas 'virtual' dans la classe parente.
    wrongCat->makeSound(); 
    wrongMeta->makeSound();

    delete wrongMeta;
    delete wrongCat; // Attention : n'appellera pas le destructeur de WrongCat !

    std::cout << "\n=== FIN DES TESTS ===" << std::endl;
    return 0;
}
