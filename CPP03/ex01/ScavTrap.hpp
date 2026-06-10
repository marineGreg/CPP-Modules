/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 17:15:46 by mgregoir          #+#    #+#             */
/*   Updated: 2026/06/10 13:51:43 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP

#include "ClapTrap.hpp"

/**
 * CONCEPTS C++ :
 * - Héritage Simple : Création d'une classe dérivée (ScavTrap) héritant des 
 *   attributs et méthodes de la classe de base (ClapTrap).
 * - Spécificateur 'protected' : Utilisation de protected au lieu de private 
 *   pour permettre aux classes enfants d'accéder aux attributs du parent.
 * - Chaînage des constructeurs/destructeurs : Observation de l'ordre d'appel 
 *   hiérarchique (Parent -> Enfant à la création, inverse à la destruction).
 * - Redéfinition (Overriding) : Modification du comportement d'une méthode 
 *   héritée (attack) pour l'adapter aux spécificités de la classe enfant.
 */
class ScavTrap : public ClapTrap {

	public:
    	ScavTrap();
    	ScavTrap(std::string name);
    	ScavTrap(const ScavTrap& other);
    	ScavTrap& operator=(const ScavTrap& other);
    	~ScavTrap();

    	void attack(const std::string& target);
    
    	void guardGate();
};

#endif
