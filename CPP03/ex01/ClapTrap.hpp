
#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <iostream>
#include <string>

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
