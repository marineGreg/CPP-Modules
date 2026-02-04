/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 17:15:58 by mgregoir          #+#    #+#             */
/*   Updated: 2026/02/04 17:25:22 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <iostream>
#include <string>

class ClapTrap {
	protected:
    	std::string     _name;
    	unsigned int    _hitPoints;
    	unsigned int    _energyPoints;
    	unsigned int    _attackDamage;

	public:
    	ClapTrap();                                  // Constructeur par défaut
    	ClapTrap(std::string name);                  // Constructeur avec nom
    	ClapTrap(const ClapTrap& other);             // Constructeur de recopie
    	ClapTrap& operator=(const ClapTrap& other);  // Opérateur d'affectation
    	~ClapTrap();                                 // Destructeur

    	// Méthodes membres
    	void attack(const std::string& target);
    	void takeDamage(unsigned int amount);
    	void beRepaired(unsigned int amount);
};

#endif
