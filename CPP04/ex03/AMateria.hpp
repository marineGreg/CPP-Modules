/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:00:00 by mgregoir          #+#    #+#             */
/*   Updated: 2026/06/10 15:07:37 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <string>

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
class ICharacter; // Forward declaration

class AMateria {

	protected:
		std::string _type;

	public:
		AMateria();
		AMateria(std::string const & type);
		AMateria(const AMateria& other);
		AMateria& operator=(const AMateria& other);
		virtual ~AMateria();

		std::string const & getType() const; // Returns the materia type
		
		virtual AMateria* clone() const = 0; // Pure virtual -> Interface
		virtual void use(ICharacter& target); // Behavior peut être overridé
};

