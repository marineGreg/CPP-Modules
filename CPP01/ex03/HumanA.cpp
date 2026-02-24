/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:03:34 by mgregoir          #+#    #+#             */
/*   Updated: 2026/02/24 12:34:54 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"

HumanA::HumanA(std::string name, Weapon& weapon) :_name(name), _weapon(weapon) {
	/*
    IMPORTANT:
    - Une référence doit être initialisée dans la liste d'initialisation
      (après les deux-points).
    - On ne peut pas faire "_weapon = weapon;" dans le corps du constructeur.
  */
}

HumanA::~HumanA() {}

void	HumanA::attack() const {
	std::cout << this->_name << " attacks with their "
			  << this->_weapon.getType() << std::endl;
}
