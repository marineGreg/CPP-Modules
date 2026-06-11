/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ICharacter.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:00:00 by mgregoir          #+#    #+#             */
/*   Updated: 2026/06/11 17:23:52 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * CONCEPTS C++ :
 * - Interfaces (Classes Purement Abstraites) : Définition de contrats via ICharacter 
 *   et IMateriaSource ne contenant que des fonctions virtuelles pures et aucun attribut.
 * - Pattern Prototype / Clonage : Utilisation d'une méthode virtuelle pure clone() 
 *   permettant de dupliquer des objets sans connaître leur type concret (Ice ou Cure).
 * - Gestion d'Inventaire complexe : Manipulation d'un tableau de pointeurs de taille 
 *   fixe (4 slots) avec gestion rigoureuse des cases vides (NULL).
 * - Deep Copy de conteneurs : Implémentation de la copie profonde pour le Character, 
 *   nécessitant de supprimer l'ancien inventaire et de cloner le nouveau pour éviter les leaks.
 * - découplage via MateriaSource : Système de "Factory" permettant de créer des 
 *   objets à partir de modèles appris, identifiés uniquement par des chaînes de caractères.
 * - Gestion des fuites (Mémoire "au sol") : Problématique du unequip() qui ne doit pas 
 *   delete la Materia, obligeant à une gestion externe des adresses pour éviter les fuites.
 */

#pragma once
#include <string>

class AMateria; // Forward declaration

/**
 * CONCEPT : INTERFACE (CONTRAT)
 * - En C++98, une interface est une classe sans attributs et avec uniquement 
 *   des méthodes virtuelles pures.
 * - Elle définit un "Contrat" : toute classe héritant de ICharacter s'engage 
 *   légalement à implémenter equip(), unequip(), use(), etc.
 */
class ICharacter {

	public:
		virtual ~ICharacter() {}
		
		virtual std::string const & getName() const = 0;
		virtual void equip(AMateria* m) = 0;
		virtual void unequip(int idx) = 0;
		virtual void use(int idx, ICharacter& target) = 0;
};

