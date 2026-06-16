
#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <iostream>
#include <string>

/**
 * CONCEPTS :
 * - Forme Canonique Orthodoxe : Implémentation rigoureuse des constructeurs 
 *   (défaut/recopie), de l'opérateur d'affectation et du destructeur.
 * - Encapsulation : Protection des données internes via des attributs privés 
 *   et accès contrôlé par des méthodes publiques.
 * - Logique d'état : Gestion des ressources (Points de Vie et Énergie) 
 *   conditionnant la capacité de l'objet à effectuer des actions.
 */
class ClapTrap {
	private:
    	std::string     _name;
    	unsigned int    _hitPoints;
    	unsigned int    _nrgPoints;
    	unsigned int    _aDamage;

	public:
    	ClapTrap();                                  // Constructeur par defaut
    	ClapTrap(std::string name);                  // Constructeur avec nom
    	ClapTrap(const ClapTrap& other);             // Constructeur de copie
    	ClapTrap& operator=(const ClapTrap& other);  // Operateur d'affectation
    	~ClapTrap();                                 // Destructeur

    	void attack(const std::string& target);
    	void takeDamage(unsigned int amount);
    	void beRepaired(unsigned int amount);
};

#endif