/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 16:49:11 by mgregoir          #+#    #+#             */
/*   Updated: 2026/02/24 13:00:28 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

// --- Constructeurs et Destructeur ---

ClapTrap::ClapTrap() : _name("Default"), _hitPoints(10), _nrgPoints(10), _aDamage(0) {
    std::cout << "ClapTrap Default constructor called" << std::endl;
}

ClapTrap::ClapTrap(std::string name) : _name(name), _hitPoints(10), _nrgPoints(10), _aDamage(0) {
    std::cout << "ClapTrap Name constructor called for " << _name << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap& other) {
    std::cout << "ClapTrap Copy constructor called" << std::endl;
    *this = other;
}

ClapTrap& ClapTrap::operator=(const ClapTrap& other) {
    std::cout << "ClapTrap Assignment operator called" << std::endl;
    if (this != &other) {
        this->_name = other._name;
        this->_hitPoints = other._hitPoints;
        this->_nrgPoints = other._nrgPoints;
        this->_aDamage = other._aDamage;
    }
    return *this;
}

ClapTrap::~ClapTrap() {
    std::cout << "ClapTrap Destructor called for " << _name << std::endl;
}

// --- Méthodes d'action ---

void ClapTrap::attack(const std::string& target) {
    if (_hitPoints == 0) {
        std::cout << "ClapTrap " << _name << " is dead and cannot attack!" << std::endl;
        return;
    }
    if (_nrgPoints == 0) {
        std::cout << "ClapTrap " << _name << " is out of energy and cannot attack!" << std::endl;
        return;
    }

    _nrgPoints -= 1;
    std::cout << "ClapTrap " << _name << " attacks " << target 
              << ", causing " << _aDamage << " points of damage!" << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount) {
    if (_hitPoints == 0) {
        std::cout << "ClapTrap " << _name << " is already dead!" << std::endl;
        return;
    }
    
    if (amount >= _hitPoints)
        _hitPoints = 0;
    else
        _hitPoints -= amount;

    std::cout << "ClapTrap " << _name << " took " << amount 
              << " points of damage! Remaining HP: " << _hitPoints << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount) {
    if (_hitPoints == 0) {
        std::cout << "ClapTrap " << _name << " is dead and cannot be repaired!" << std::endl;
        return;
    }
    if (_nrgPoints == 0) {
        std::cout << "ClapTrap " << _name << " is out of energy and cannot repair itself!" << std::endl;
        return;
    }

    _nrgPoints -= 1;
    _hitPoints += amount;
    std::cout << "ClapTrap " << _name << " repairs itself by " << amount 
              << " points! Current HP: " << _hitPoints << std::endl;
}