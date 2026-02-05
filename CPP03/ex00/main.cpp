/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 11:41:03 by mgregoir          #+#    #+#             */
/*   Updated: 2026/02/05 11:41:09 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

int main() {
    std::cout << "=== TEST 1: Construction basique ===" << std::endl;
    ClapTrap clap("Clappy");
    ClapTrap enemy("Target");

    std::cout << "\n=== TEST 2: Actions de base ===" << std::endl;
    clap.attack("Target");
    enemy.takeDamage(0);  // Damage par défaut = 0
    clap.beRepaired(5);
    enemy.beRepaired(3);

    std::cout << "\n=== TEST 3: Constructeur de copie ===" << std::endl;
    ClapTrap copyClap(clap);
    copyClap.attack("dummy");

    std::cout << "\n=== TEST 4: Opérateur d'affectation ===" << std::endl;
    ClapTrap assignedClap("Temporary");
    assignedClap = clap;
    assignedClap.beRepaired(2);

    std::cout << "\n=== TEST 5: Épuisement d'énergie ===" << std::endl;
    ClapTrap tired("Exhausted");
    std::cout << "Tentative de 12 actions (max = 10):" << std::endl;
    for (int i = 0; i < 12; i++) {
        std::cout << "Action " << i + 1 << ": ";
        tired.attack("training dummy");
    }

    std::cout << "\n=== TEST 6: Série de réparations ===" << std::endl;
    ClapTrap healer("Medic");
    for (int i = 0; i < 5; i++) {
        healer.beRepaired(2);
    }

    std::cout << "\n=== TEST 7: Combat simulé ===" << std::endl;
    ClapTrap fighter1("Alpha");
    ClapTrap fighter2("Beta");
    fighter1.attack("Beta");
    fighter2.takeDamage(0);
    fighter2.attack("Alpha");
    fighter1.takeDamage(0);
    fighter1.beRepaired(1);

    std::cout << "\n=== TEST 8: Dégâts progressifs ===" << std::endl;
    ClapTrap victim("Victim");
    victim.takeDamage(3);
    victim.takeDamage(4);
    victim.takeDamage(5);  // Total: 12 dégâts, devrait mourir

    std::cout << "\n=== TEST 9: Tentative d'action après mort ===" << std::endl;
    victim.attack("ghost");
    victim.beRepaired(100);

    std::cout << "\n=== TEST 10: Mort instantanée ===" << std::endl;
    ClapTrap fragile("Fragile");
    fragile.takeDamage(100);  // Mort immédiate
    fragile.attack("anyone");

    std::cout << "\n=== TEST 11: Multiple ClapTraps ===" << std::endl;
    ClapTrap army[3] = {ClapTrap("Soldier1"), ClapTrap("Soldier2"), ClapTrap("Soldier3")};
    for (int i = 0; i < 3; i++) {
        army[i].attack("enemy base");
    }

    std::cout << "\n=== Destruction de tous les ClapTraps ===" << std::endl;
    return 0;
}