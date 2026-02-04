/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 17:45:13 by mgregoir          #+#    #+#             */
/*   Updated: 2026/02/04 22:00:00 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

int main() {
    std::cout << "=== TEST 1: Construction DiamondTrap ===" << std::endl;
    DiamondTrap diamond("Destroyer");

    std::cout << "\n=== TEST 2: Méthode whoAmI() ===" << std::endl;
    diamond.whoAmI();

    std::cout << "\n=== TEST 3: Vérification de l'héritage multiple ===" << std::endl;
    std::cout << "DiamondTrap a accès aux méthodes de:" << std::endl;
    std::cout << "- ClapTrap (takeDamage, beRepaired)" << std::endl;
    std::cout << "- ScavTrap (attack, guardGate)" << std::endl;
    std::cout << "- FragTrap (highFivesGuys)" << std::endl;

    std::cout << "\n=== TEST 4: Attack (de ScavTrap) ===" << std::endl;
    diamond.attack("enemy");  // Utilise ScavTrap::attack()

    std::cout << "\n=== TEST 5: Capacités spéciales ===" << std::endl;
    std::cout << "De FragTrap:" << std::endl;
    diamond.highFivesGuys();
    std::cout << "\nDe ScavTrap:" << std::endl;
    diamond.guardGate();

    std::cout << "\n=== TEST 6: Méthodes héritées de ClapTrap ===" << std::endl;
    diamond.takeDamage(30);
    diamond.beRepaired(15);
    diamond.takeDamage(20);

    std::cout << "\n=== TEST 7: Constructeur par défaut ===" << std::endl;
    DiamondTrap defaultDiamond;
    defaultDiamond.whoAmI();

    std::cout << "\n=== TEST 8: Constructeur de copie ===" << std::endl;
    DiamondTrap copyDiamond(diamond);
    copyDiamond.whoAmI();
    copyDiamond.attack("copy target");

    std::cout << "\n=== TEST 9: Opérateur d'affectation ===" << std::endl;
    DiamondTrap assignedDiamond("Temporary");
    assignedDiamond = diamond;
    assignedDiamond.whoAmI();

    std::cout << "\n=== TEST 10: Stats DiamondTrap ===" << std::endl;
    std::cout << "HP: 100 (de FragTrap)" << std::endl;
    std::cout << "Energy: 50 (de ScavTrap)" << std::endl;
    std::cout << "Damage: 30 (de FragTrap)" << std::endl;
    DiamondTrap statsTest("StatsTest");
    statsTest.takeDamage(100);  // Devrait survivre avec 0 HP
    statsTest.beRepaired(10);   // Ne peut pas se réparer (mort)

    std::cout << "\n=== TEST 11: Endurance énergétique ===" << std::endl;
    DiamondTrap marathon("Marathon");
    std::cout << "Test de 52 attaques (50 energy max):" << std::endl;
    for (int i = 0; i < 52; i++) {
        if (i % 10 == 0)
            std::cout << "  Attaque " << i + 1 << "..." << std::endl;
        marathon.attack("dummy");
    }

    std::cout << "\n=== TEST 12: Comparaison avec parents ===" << std::endl;
    std::cout << "\nClapTrap:" << std::endl;
    ClapTrap clap("ClapBot");
    clap.attack("target");
    
    std::cout << "\nScavTrap:" << std::endl;
    ScavTrap scav("ScavBot");
    scav.attack("target");
    scav.guardGate();
    
    std::cout << "\nFragTrap:" << std::endl;
    FragTrap frag("FragBot");
    frag.attack("target");
    frag.highFivesGuys();
    
    std::cout << "\nDiamondTrap (combine tout):" << std::endl;
    DiamondTrap ultimate("Ultimate");
    ultimate.attack("target");      // De ScavTrap
    ultimate.guardGate();           // De ScavTrap
    ultimate.highFivesGuys();       // De FragTrap
    ultimate.whoAmI();              // Unique à DiamondTrap

    std::cout << "\n=== TEST 13: Multiple DiamondTraps ===" << std::endl;
    DiamondTrap squad[3] = {
        DiamondTrap("Alpha"),
        DiamondTrap("Beta"),
        DiamondTrap("Gamma")
    };
    for (int i = 0; i < 3; i++) {
        squad[i].whoAmI();
        squad[i].attack("enemy");
    }

    std::cout << "\n=== TEST 14: Combat simulé ===" << std::endl;
    DiamondTrap fighter1("Fighter1");
    DiamondTrap fighter2("Fighter2");
    
    std::cout << "\nFighter1 attaque:" << std::endl;
    fighter1.attack("Fighter2");
    fighter2.takeDamage(30);
    
    std::cout << "\nFighter2 riposte:" << std::endl;
    fighter2.attack("Fighter1");
    fighter1.takeDamage(30);
    
    std::cout << "\nFighter1 se répare:" << std::endl;
    fighter1.beRepaired(20);
    
    std::cout << "\nFighter2 active ses capacités:" << std::endl;
    fighter2.guardGate();
    fighter2.highFivesGuys();

    std::cout << "\n=== Destruction de tous les DiamondTraps ===" << std::endl;
    return 0;
}
