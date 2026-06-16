
#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <iostream>
#include <string>

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
