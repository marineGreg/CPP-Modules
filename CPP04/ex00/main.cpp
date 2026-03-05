/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amber <amber@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 16:26:26 by mgregoir          #+#    #+#             */
/*   Updated: 2026/03/05 18:07:46 by amber            ###   ########.fr       */
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
    const AAnimal* meta = new AAnimal();
    const AAnimal* j = new Dog();
    const AAnimal* i = new Cat();

    std::cout << "Type of meta : " << meta->getType() << std::endl;
    std::cout << "Type of j : " << j->getType() << std::endl;
    std::cout << "Type of i " << i->getType() << std::endl;
    
    i->makeSound(); // Sortie attendue : Meow!
    j->makeSound(); // Sortie attendue : Woof!
    meta->makeSound(); // Sortie attendue : Generic Animal sound

    delete meta;
    delete j;
    delete i;

    // --- 2. TESTS SUPPLEMENTAIRES (Allocation sur la pile & Copie) ---
    std::cout << "\n=== TESTS SUPPLÉMENTAIRES (Stack & Copy) ===" << std::endl;
    
    Dog originalDog;
    std::cout << "Type of originalDog : " << originalDog.getType() << std::endl;
    
    Dog copyDog(originalDog); // Test du constructeur de recopie
    std::cout << "Type of copyDog : " << copyDog.getType() << std::endl;
    copyDog.makeSound();

    Cat stackCat;
    std::cout << "Type of stackCat : " << stackCat.getType() << std::endl;
    stackCat.makeSound();

    // --- 3. TESTS DU CAS "WRONG" (Preuve par l'erreur) ---
    std::cout << "\n=== TESTS WRONG ANIMAL (Pas de polymorphisme) ===" << std::endl;
    
    const WrongAnimal* wrongMeta = new WrongAnimal();
    const WrongAnimal* wrongCat = new WrongCat();

    std::cout << "Type : " << wrongCat->getType() << std::endl;
    
    // Ici, malgre que ce soit un WrongCat, il va faire le son du WrongAnimal 
    // car la methode n'est pas 'virtual' dans la classe parente.
    wrongCat->makeSound(); 
    wrongMeta->makeSound();

    delete wrongMeta;
    delete wrongCat; // Attention : n'appellera pas le destructeur de WrongCat !

    std::cout << "\n=== FIN DES TESTS ===" << std::endl;
    return 0;
}
