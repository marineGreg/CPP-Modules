/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 17:37:19 by mgregoir          #+#    #+#             */
/*   Updated: 2026/03/06 15:28:48 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"
#include "Cat.hpp"

int main() {
    const int count = 4;
    Animal* animals[count];

    std::cout << "=== 1. CREATION DU TABLEAU ===" << std::endl;
    for (int i = 0; i < count; i++) {
        if (i < count / 2)
            animals[i] = new Dog();
        else
            animals[i] = new Cat();
    }

    std::cout << "\n=== 2. DESTRUCTION DU TABLEAU ===" << std::endl;
    for (int i = 0; i < count; i++) {
        delete animals[i]; // Teste le destructeur virtuel et la suppression du Brain
    }

    std::cout << "\n=== 3. TEST DEEP COPY ===" << std::endl;
    Dog original;
    {
        std::cout << "    (Creation de la copie dans un scope temporaire)" << std::endl;
        Dog copy = original; // Appelle le constructeur de copie (Deep Copy)
        std::cout << "    (Fin du scope, la copie va etre detruite)" << std::endl;
    } 
    // Si la copie etait superficielle (Shallow), 'original' crasherait ici 
    // car son cerveau aurait été supprimé avec la copie.
    std::cout << "Original is still alive !" << std::endl;
	original.makeSound();

    return 0;
}
