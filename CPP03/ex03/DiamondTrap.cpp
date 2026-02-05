/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 12:17:56 by mgregoir          #+#    #+#             */
/*   Updated: 2026/02/05 12:19:38 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap() : ClapTrap("Default_clap_name"), FragTrap(), ScavTrap() {
    this->_name = "Default";
    this->_hitPoints = FragTrap::_hitPoints;    // 100
    this->_energyPoints = ScavTrap::_energyPoints; // 50
    this->_attackDamage = FragTrap::_attackDamage; // 30
    std::cout << "DiamondTrap Default constructor called" << std::endl;
}

DiamondTrap::DiamondTrap(std::string name) : ClapTrap(name + "_clap_name"), FragTrap(), ScavTrap() {
    this->_name = name;
    // On prend les stats des parents comme demandé
    this->_hitPoints = 100;    // Provient de FragTrap
    this->_energyPoints = 50;  // Provient de ScavTrap
    this->_attackDamage = 30;  // Provient de FragTrap
    std::cout << "DiamondTrap Name constructor called for " << name << std::endl;
}

DiamondTrap::DiamondTrap(const DiamondTrap& other) : ClapTrap(other), FragTrap(other), ScavTrap(other) {
    *this = other;
    std::cout << "DiamondTrap Copy constructor called" << std::endl;
}

DiamondTrap& DiamondTrap::operator=(const DiamondTrap& other) {
    if (this != &other) {
        this->_name = other._name;
        this->ClapTrap::_name = other.ClapTrap::_name;
        this->_hitPoints = other._hitPoints;
        this->_energyPoints = other._energyPoints;
        this->_attackDamage = other._attackDamage;
    }
    return *this;
}

DiamondTrap::~DiamondTrap() {
    std::cout << "DiamondTrap Destructor called" << std::endl;
}

void DiamondTrap::whoAmI() {
    std::cout << "I am DiamondTrap: " << this->_name 
              << " and my ClapTrap name is: " << ClapTrap::_name << std::endl;
}
