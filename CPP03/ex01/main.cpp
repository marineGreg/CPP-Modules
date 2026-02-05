/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 11:40:41 by mgregoir          #+#    #+#             */
/*   Updated: 2026/02/05 11:40:43 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

int main() {
    std::cout << "=== TEST 1: Construction ClapTrap vs ScavTrap ===" << std::endl;
    ClapTrap clap("Basic");
    ScavTrap scav("Guardian");

    std::cout << "\n=== TEST 2: Comparaison des attaques ===" << std::endl;
    std::cout << "ClapTrap attack:" << std::endl;
    clap.attack("enemy");  // Message normal, 0 dégâts
    std::cout << "\nScavTrap attack:" << std::endl;
    scav.attack("enemy");  // Message "savagely", 20 dégâts

    std::cout << "\n=== TEST 3: Capacité spéciale ScavTrap ===" << std::endl;
    scav.guardGate();
    scav.guardGate();  // Peut l'activer plusieurs fois

    std::cout << "\n=== TEST 4: Constructeur de copie ScavTrap ===" << std::endl;
    ScavTrap scavCopy(scav);
    scavCopy.attack("intruder");
    scavCopy.guardGate();

    std::cout << "\n=== TEST 5: Opérateur d'affectation ===" << std::endl;
    ScavTrap assigned("Temp");
    assigned = scav;
    assigned.attack("target");

    std::cout << "\n=== TEST 6: Endurance ScavTrap (50 energy) ===" << std::endl;
    ScavTrap endurance("Marathon");
    std::cout << "Série de 52 attaques (max = 50):" << std::endl;
    for (int i = 0; i < 52; i++) {
        if (i % 10 == 0)
            std::cout << "Attaque " << i + 1 << ":" << std::endl;
        endurance.attack("dummy");
    }

    std::cout << "\n=== TEST 7: Résistance ScavTrap (100 HP) ===" << std::endl;
    ScavTrap tank("Tank");
    tank.takeDamage(30);
    tank.takeDamage(40);
    tank.takeDamage(35);  // Total: 105 dégâts, devrait mourir
    tank.attack("ghost");  // Ne peut plus attaquer

    std::cout << "\n=== TEST 8: Combat ClapTrap vs ScavTrap ===" << std::endl;
    ClapTrap weakling("Weakling");
    ScavTrap warrior("Warrior");
    std::cout << "Tour 1 - ClapTrap attaque:" << std::endl;
    weakling.attack("Warrior");
    warrior.takeDamage(0);
    std::cout << "Tour 2 - ScavTrap riposte:" << std::endl;
    warrior.attack("Weakling");
    weakling.takeDamage(20);  // ClapTrap meurt en un coup

    std::cout << "\n=== TEST 9: Réparations multiples ===" << std::endl;
    ScavTrap healer("Healer");
    healer.takeDamage(50);
    for (int i = 0; i < 5; i++) {
        healer.beRepaired(10);
    }

    std::cout << "\n=== TEST 10: Mode Gate keeper pendant combat ===" << std::endl;
    ScavTrap defender("Defender");
    defender.guardGate();
    defender.attack("attacker");
    defender.takeDamage(25);
    defender.beRepaired(15);
    defender.guardGate();  // Remet en mode garde

    std::cout << "\n=== Destruction de tous les robots ===" << std::endl;
    return 0;
}
