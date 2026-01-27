/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:03:34 by mgregoir          #+#    #+#             */
/*   Updated: 2026/01/27 13:16:18 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"

HumanB::HumanB(std::string name) : _name(name), _weapon(NULL) {}

HumanB::~HumanB() {}

void	HumanB::attack() const {
	if (this->_weapon != NULL) {
		std::cout << this->_name << " attacks with their " << this->_weapon->getType() << std::endl;
	} else {
		std::cout << this->_name << " has no weapon to attack." << std::endl;
	}
}

void	HumanB::setWeapon(Weapon& weapon) {
	this->_weapon = &weapon;                                                                                                                                                                                                                                                                                                                                  
}
