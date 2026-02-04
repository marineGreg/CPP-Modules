/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 17:45:13 by mgregoir          #+#    #+#             */
/*   Updated: 2026/02/04 00:00:00 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int main() {
    std::cout << "=== TEST 1: Construction des 3 types ===" << std::endl;
    ClapTrap clap("Basic");
    ScavTrap scav("Guardian");
    FragTrap frag("Destroyer");

    std::cout << "\n=== TEST 2: Comparaison des stats d'attaque ===" << std::endl;
    std::cout << "ClapTrap (Damage: 0):" << std::endl;
    clap.attack("target");
    std::cout << "\nScavTrap (Damage: 20):" << std::endl;
    scav.attack("target");
    std::cout << "\nFragTrap (Damage: 30):" << std::endl;
    frag.attack("target");

    std::cout << "\n=== TEST 3: Capacités spéciales ===" << std::endl;
    std::cout << "ScavTrap - Gate keeper mode:" << std::endl;
    scav.guardGate();
    std::cout << "\nFragTrap - High five request:" << std::endl;
    frag.highFivesGuys();
    frag.highFivesGuys();  // On peut le faire plusieurs fois

    std::cout << "\n=== TEST 4: Endurance énergétique ===" << std::endl;
    std::cout << "ClapTrap (10 energy):" << std::endl;
    ClapTrap tiredClap("TiredClap");
    for (int i = 0; i < 12; i++)
        tiredClap.attack("dummy");
    
    std::cout << "\nScavTrap (50 energy):" << std::endl;
    ScavTrap tiredScav("TiredScav");
    for (int i = 0; i < 52; i++) {
        if (i % 10 == 0)
            std::cout << "  [Attaque " << i + 1 << "]" << std::endl;
        tiredScav.attack("dummy");
    }
    
    std::cout << "\nFragTrap (100 energy):" << std::endl;
    FragTrap tiredFrag("TiredFrag");
    for (int i = 0; i < 102; i++) {
        if (i % 20 == 0)
            std::cout << "  [Attaque " << i + 1 << "]" << std::endl;
        tiredFrag.attack("dummy");
    }

    std::cout << "\n=== TEST 5: Résistance aux dégâts ===" << std::endl;
    std::cout << "ClapTrap (10 HP):" << std::endl;
    ClapTrap fragileClap("Fragile");
    fragileClap.takeDamage(15);  // Mort immédiate
    
    std::cout << "\nScavTrap (100 HP):" << std::endl;
    ScavTrap tankScav("Tank");
    tankScav.takeDamage(50);
    tankScav.takeDamage(55);  // Mort au 2e coup
    
    std::cout << "\nFragTrap (100 HP):" << std::endl;
    FragTrap tankFrag("Armored");
    tankFrag.takeDamage(30);
    tankFrag.takeDamage(30);
    tankFrag.takeDamage(30);
    tankFrag.takeDamage(30);  // Mort au 4e coup

    std::cout << "\n=== TEST 6: Constructeurs de copie ===" << std::endl;
    std::cout << "Copie de ClapTrap:" << std::endl;
    ClapTrap clapCopy(clap);
    clapCopy.attack("copy target");
    
    std::cout << "\nCopie de ScavTrap:" << std::endl;
    ScavTrap scavCopy(scav);
    scavCopy.attack("copy target");
    scavCopy.guardGate();
    
    std::cout << "\nCopie de FragTrap:" << std::endl;
    FragTrap fragCopy(frag);
    fragCopy.attack("copy target");
    fragCopy.highFivesGuys();

    std::cout << "\n=== TEST 7: Opérateurs d'affectation ===" << std::endl;
    ClapTrap clap2("Clap2");
    clap2 = clap;
    clap2.attack("assigned target");
    
    ScavTrap scav2("Scav2");
    scav2 = scav;
    scav2.guardGate();
    
    FragTrap frag2("Frag2");
    frag2 = frag;
    frag2.highFivesGuys();

    std::cout << "\n=== TEST 8: Bataille royale simulée ===" << std::endl;
    ClapTrap fighter1("BasicFighter");
    ScavTrap fighter2("MediumFighter");
    FragTrap fighter3("HeavyFighter");
    
    std::cout << "\nRound 1:" << std::endl;
    fighter1.attack("enemies");
    fighter2.attack("enemies");
    fighter3.attack("enemies");
    
    std::cout << "\nRound 2 - Tous prennent des dégâts:" << std::endl;
    fighter1.takeDamage(8);
    fighter2.takeDamage(40);
    fighter3.takeDamage(60);
    
    std::cout << "\nRound 3 - Tentative de réparation:" << std::endl;
    fighter1.beRepaired(5);
    fighter2.beRepaired(20);
    fighter3.beRepaired(30);
    
    std::cout << "\nRound 4 - Capacités spéciales:" << std::endl;
    fighter2.guardGate();
    fighter3.highFivesGuys();

    std::cout << "\n=== TEST 9: Scénario de siège ===" << std::endl;
    ScavTrap gatekeeper("Gatekeeper");
    FragTrap attacker1("Attacker1");
    FragTrap attacker2("Attacker2");
    
    std::cout << "Le gardien active son mode:" << std::endl;
    gatekeeper.guardGate();
    
    std::cout << "\nLes attaquants frappent:" << std::endl;
    attacker1.attack("Gatekeeper");
    attacker2.attack("Gatekeeper");
    gatekeeper.takeDamage(60);
    
    std::cout << "\nLe gardien riposte:" << std::endl;
    gatekeeper.attack("Attacker1");
    attacker1.takeDamage(20);

    std::cout << "\n=== TEST 10: Armée de robots ===" << std::endl;
    std::cout << "Création d'une armée variée:" << std::endl;
    ClapTrap army1[2] = {ClapTrap("Scout1"), ClapTrap("Scout2")};
    ScavTrap army2[2] = {ScavTrap("Guard1"), ScavTrap("Guard2")};
    FragTrap army3[2] = {FragTrap("Heavy1"), FragTrap("Heavy2")};
    
    std::cout << "\nAttaque coordonnée:" << std::endl;
    for (int i = 0; i < 2; i++) {
        army1[i].attack("enemy base");
        army2[i].attack("enemy base");
        army3[i].attack("enemy base");
    }

    std::cout << "\n=== Destruction de tous les robots ===" << std::endl;
    return 0;
}
