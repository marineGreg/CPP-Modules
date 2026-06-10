/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 12:18:00 by mgregoir          #+#    #+#             */
/*   Updated: 2026/06/10 14:43:19 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIAMONDTRAP_HPP
#define DIAMONDTRAP_HPP

#include "ScavTrap.hpp"
#include "FragTrap.hpp"

/**
 * CONCEPTS C++ :
 * - Héritage Multiple : Création d'une classe (DiamondTrap) héritant simultanément 
 *   de ScavTrap et FragTrap pour combiner leurs fonctionnalités.
 * - Héritage Virtuel : Utilisation du mot-clé 'virtual' pour résoudre le "Problème 
 *   du Diamant", garantissant une instance unique de la classe de base (ClapTrap).
 * - Gestion du "Shadowing" : Résolution des conflits de noms d'attributs entre 
 *   la classe enfant et ses parents via la portée explicite (this->name vs ClapTrap::name).
 * - Composition hybride : Sélection sélective des statistiques et méthodes 
 *   provenant de parents différents (HP de FragTrap, Energy de ScavTrap, etc.).
 */
class DiamondTrap : public FragTrap, public ScavTrap {
private:
    std::string _name; // Nom propre au DiamondTrap

public:
    DiamondTrap();
    DiamondTrap(std::string name);
    DiamondTrap(const DiamondTrap& other);
    DiamondTrap& operator=(const DiamondTrap& other);
    ~DiamondTrap();

    // On utilise l'attaque de ScavTrap explicitement
    using ScavTrap::attack;

    void whoAmI();
};

#endif
