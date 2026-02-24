/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 17:15:58 by mgregoir          #+#    #+#             */
/*   Updated: 2026/02/24 15:12:18 by mgregoir         ###   ########.fr       */
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
    	unsigned int    _nrgPoints;
    	unsigned int    _aDamage;

	public:
    	ClapTrap();
    	ClapTrap(std::string name);
    	ClapTrap(const ClapTrap& other);
    	ClapTrap& operator=(const ClapTrap& other);
    	virtual ~ClapTrap();

    	void attack(const std::string& target);
    	void takeDamage(unsigned int amount);
    	void beRepaired(unsigned int amount);
};

#endif
