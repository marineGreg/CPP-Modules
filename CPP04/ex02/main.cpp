/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 17:37:19 by mgregoir          #+#    #+#             */
/*   Updated: 2026/02/19 17:49:05 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"
#include "Cat.hpp"

int main() {
    const int count = 4;
    Animal* animals[count];

    // 1. Remplissage du tableau
    std::cout << "=== CREATING ANIMALS ===" << std::endl;
    for (int i = 0; i < count; i++) {
        if (i < count / 2)
            animals[i] = new Dog();
        else
            animals[i] = new Cat();
    }

    // 2. Suppression (doit appeler les destructeurs Dog/Cat et Brain !)
    std::cout << "\n=== DELETING ANIMALS ===" << std::endl;
    for (int i = 0; i < count; i++) {
        delete animals[i];
    }

    // 3. Test de la Deep Copy (Copie profonde)
    std::cout << "\n=== DEEP COPY TEST ===" << std::endl;
    Dog basic;
    {
        Dog tmp = basic; // Appel du constructeur de recopie
    } // tmp est détruit ici. Si c'est une shallow copy, basic.brain est détruit aussi -> Crash.
    
    std::cout << "Basic dog is still alive!" << std::endl;

    // 4. Test de la classe abstraite (ne compile pas si on décommente)
    std::cout << "\n=== NOTE: Animal is now an abstract class ===" << std::endl;
    std::cout << "You cannot instantiate Animal directly anymore:" << std::endl;
    std::cout << "// Animal animal; <-- This would cause a compilation error!" << std::endl;
    std::cout << "Only Dog and Cat (concrete classes) can be instantiated." << std::endl;

    return 0;
}
