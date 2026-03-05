/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amber <amber@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 17:37:19 by mgregoir          #+#    #+#             */
/*   Updated: 2026/03/05 18:07:46 by amber            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"
#include "Cat.hpp"

int main() {
    const int count = 4;
    AAnimal* animals[count];

    std::cout << "=== CREATING ANIMALS ===" << std::endl;
    for (int i = 0; i < count; i++) {
        if (i < count / 2)
            animals[i] = new Dog();
        else
            animals[i] = new Cat();
    }
    
    std::cout << "\n=== DELETING ANIMALS ===" << std::endl;
    for (int i = 0; i < count; i++) {
        delete animals[i];
    }

    // 3. Test de la Deep Copy
    std::cout << "\n=== DEEP COPY TEST ===" << std::endl;
    Dog basic;
    {
        Dog tmp = basic; // Appel du constructeur de copie
    } // tmp est detruit ici. Si c'est une shallow copy, basic.brain est detruit aussi -> Crash.
    
    std::cout << "Basic dog is still alive!" << std::endl;
    basic.makeSound();
    
    return 0;
}
