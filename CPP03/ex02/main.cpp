/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 17:45:13 by mgregoir          #+#    #+#             */
/*   Updated: 2026/02/04 17:46:17 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int main() {
    std::cout << "--- CREATION ---" << std::endl;
    ClapTrap clap("Basic");
    ScavTrap scav("Guardian");
    FragTrap frag("Destroyer");

    std::cout << "\n--- ACTION FRAGTRAP ---" << std::endl;
    frag.attack("a training bot"); // Utilise l'attaque de base mais avec 30 de dégâts
    frag.takeDamage(50);
    frag.beRepaired(20);
    frag.highFivesGuys();

    std::cout << "\n--- COMPARAISON DES DEGATS ---" << std::endl;
    clap.attack("target"); // 0 dégâts
    scav.attack("target"); // 20 dégâts
    frag.attack("target"); // 30 dégâts

    std::cout << "\n--- DESTRUCTION ---" << std::endl;
    // Les destructeurs vont s'appeler dans l'ordre inverse :
    // FragTrap -> ClapTrap
    // ScavTrap -> ClapTrap
    // ClapTrap
    return 0;
}
