/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 11:40:41 by mgregoir          #+#    #+#             */
/*   Updated: 2026/02/25 13:06:18 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

int main() {
    std::cout << "=== TEST 1: Construction ClapTrap vs ScavTrap ===" << std::endl;
    ClapTrap clap("Basic");
    ScavTrap scav("Guardian");

    std::cout << "\n=== TEST 2: Comparaison attaques ===" << std::endl;
    clap.attack("enemy");  // Message normal
    scav.attack("enemy");  // Message "savagely"

    std::cout << "\n=== TEST 3: Capacite speciale ===" << std::endl;
    scav.guardGate();

    std::cout << "\n=== TEST 4: Constructeur de copie ===" << std::endl;
    ScavTrap copy(scav);
    copy.attack("target");

    std::cout << "\n=== TEST 5: Endurance (50 energy) ===" << std::endl;
    ScavTrap marathon("Marathon");
    for (int i = 0; i < 52; i++)
        marathon.attack("dummy");

    std::cout << "\n=== TEST 6: Resistance (100 HP) ===" << std::endl;
    ScavTrap tank("Tank");
	tank.beRepaired(3);
    tank.takeDamage(105);
    tank.attack("ghost");  // Ne peut plus attaquer

    std::cout << "\n=== Destruction ===" << std::endl;
    return 0;
}
