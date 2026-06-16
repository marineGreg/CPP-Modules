
#pragma once

#include <iostream>
#include <string>

/**
 * CONCEPTS C++ :
 * - Classes Abstraites : Classes représentant des concepts génériques qui ne 
 *   peuvent pas être instanciées directement (impossibilité de faire 'new Animal').
 * - Fonctions Virtuelles Pures : Utilisation de la syntaxe '= 0' pour définir 
 *   des méthodes sans implémentation, forçant ainsi les classes enfants à les définir.
 * - Contrat d'Interface : Obligation pour toute classe dérivée concrète de fournir 
 *   une implémentation de 'makeSound()' pour être compilable.
 * - Sécurité de Conception : Protection contre la création d'objets "incomplets" 
 *   qui n'auraient pas de comportement spécifique défini.
 */
class AAnimal {

	protected:
    	std::string type;

	public:
    	AAnimal();
    	AAnimal(const AAnimal& other);
    	AAnimal& operator=(const AAnimal& other);
    	virtual ~AAnimal(); // Virtuel pour permettre la destruction des classes derivees

    	virtual void makeSound() const = 0; // Methode virtuelle pure -> Classe abstraite
    	std::string getType() const;
};
