/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 17:15:46 by mgregoir          #+#    #+#             */
/*   Updated: 2026/02/04 17:24:09 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP

#include "ClapTrap.hpp"

class ScavTrap : public ClapTrap {

	public:
    	ScavTrap();
    	ScavTrap(std::string name);
    	ScavTrap(const ScavTrap& other);
    	ScavTrap& operator=(const ScavTrap& other);
    	~ScavTrap();

    	// Redéfinition de l'attaque (message différent)
    	void attack(const std::string& target);
    
    	// Capacité spéciale
    	void guardGate();
};

#endif
