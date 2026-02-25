/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 17:45:13 by mgregoir          #+#    #+#             */
/*   Updated: 2026/02/25 13:30:08 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int main() {
    std::cout << "=== TEST 1: Construction ===" << std::endl;
    ClapTrap clap("Basic");
    ScavTrap scav("Guardian");
    FragTrap frag("Destroyer");

    std::cout << "\n=== TEST 2: Comparaison attaques ===" << std::endl;
    clap.attack("target");  // 0 degats
    scav.attack("target");  // 20 degats
    frag.attack("target");  // 30 degats

    std::cout << "\n=== TEST 3: Capacites speciales ===" << std::endl;
    scav.guardGate();
    frag.highFivesGuys();

    std::cout << "\n=== TEST 4: Endurance ===" << std::endl;
    ClapTrap tired1("Tired1");
    for (int i = 0; i < 12; i++)
        tired1.attack("dummy");
    
    FragTrap tired2("Tired2");
    for (int i = 0; i < 102; i++)
        tired2.attack("dummy");

    std::cout << "\n=== TEST 5: Resistance ===" << std::endl;
    clap.takeDamage(15);    // Meurt (10 HP)
    scav.takeDamage(105);   // Meurt (100 HP)
    frag.takeDamage(105);   // Meurt (100 HP)

    std::cout << "\n=== TEST 6: Constructeurs de copie ===" << std::endl;
    ScavTrap scavCopy(scav);
    FragTrap fragCopy(frag);
    scavCopy.guardGate();
    fragCopy.highFivesGuys();
	
	std::cout << "\n=== TEST 7: Destructeur virtuel ===" << std::endl;
	ClapTrap* scavy = new ScavTrap("Scavy");
	
    std::cout << "\n=== Destruction ===" << std::endl;
	delete scavy;
    return 0;
}
