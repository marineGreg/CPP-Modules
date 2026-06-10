/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 15:08:13 by mgregoir          #+#    #+#             */
/*   Updated: 2026/06/10 15:05:10 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Animal.hpp"
#include "Brain.hpp"

/**
 * CONCEPTS C++ :
 * - Deep Copy (Copie Profonde) : Implémentation manuelle de la recopie des attributs 
 *   alloués sur le tas (Brain*) pour garantir l'indépendance mémoire des instances.
 * - Gestion de la Heap : Allocation dynamique via 'new' dans le constructeur et 
 *   libération rigoureuse via 'delete' dans le destructeur pour éviter les leaks.
 * - Forme Canonique d'Orthodox : Application stricte du constructeur de recopie 
 *   et de l'opérateur d'affectation pour prévenir les erreurs de type "Double Free".
 * - Composition d'objets : Relation "Has-a" où les classes Dog et Cat possèdent 
 *   leur propre instance de la classe Brain.
 */
class Cat : public Animal {

	private:
    	Brain* _brain; // Attribut prive
		
	public:
    	Cat();
    	Cat(const Cat& other);
    	Cat& operator=(const Cat& other);
    	~Cat();

    	void makeSound() const;
};
