/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 17:37:03 by mgregoir          #+#    #+#             */
/*   Updated: 2026/06/10 14:39:39 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAGTRAP_HPP
# define FRAGTRAP_HPP

#include "ClapTrap.hpp"

/**
 * CONCEPTS C++ :
 * - Extension de la hiérarchie : Création d'une seconde classe dérivée (FragTrap) 
 *   partageant la même base (ClapTrap) pour illustrer la réutilisabilité du code.
 * - Spécialisation : Ajout de fonctionnalités spécifiques (highFivesGuys) et 
 *   ajustement des statistiques pour différencier le rôle de chaque classe enfant.
 * - Consolidation de l'héritage : Renforcement de la maîtrise du chaînage des 
 *   constructeurs et de la gestion des attributs protégés au sein d'une structure 
 *   à plusieurs branches.
 */
class FragTrap : public ClapTrap {
	
	public:
    	FragTrap();
    	FragTrap(std::string name);
    	FragTrap(const FragTrap& other);
    	FragTrap& operator=(const FragTrap& other);
    	~FragTrap();

    	void highFivesGuys(void);
};

#endif