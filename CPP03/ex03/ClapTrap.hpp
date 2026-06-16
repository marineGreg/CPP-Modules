
#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <iostream>
#include <string>

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
class ClapTrap {
	protected:
    	std::string     _name;
    	unsigned int    _hitPoints;
    	unsigned int    _nrgPoints;
    	unsigned int    _aDamage;

	public:
    	ClapTrap();                                  // Constructeur par défaut
    	ClapTrap(std::string name);                  // Constructeur avec nom
    	ClapTrap(const ClapTrap& other);             // Constructeur de recopie
    	ClapTrap& operator=(const ClapTrap& other);  // Opérateur d'affectation
    	virtual ~ClapTrap();                         // Destructeur

    	// Méthodes membres
    	void attack(const std::string& target);
    	void takeDamage(unsigned int amount);
    	void beRepaired(unsigned int amount);
};

#endif
