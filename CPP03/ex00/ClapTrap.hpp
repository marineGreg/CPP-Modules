/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 14:19:56 by mgregoir          #+#    #+#             */
/*   Updated: 2026/02/24 16:12:02 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <iostream>
#include <string>

class ClapTrap {
	private:
    	std::string     _name;
    	unsigned int    _hitPoints;
    	unsigned int    _nrgPoints;
    	unsigned int    _aDamage;

	public:
    	ClapTrap();                                  // Constructeur par defaut
    	ClapTrap(std::string name);                  // Constructeur avec nom
    	ClapTrap(const ClapTrap& other);             // Constructeur de recopie
    	ClapTrap& operator=(const ClapTrap& other);  // Operateur d'affectation
    	~ClapTrap();                                 // Destructeur

    	void attack(const std::string& target);
    	void takeDamage(unsigned int amount);
    	void beRepaired(unsigned int amount);
};

#endif