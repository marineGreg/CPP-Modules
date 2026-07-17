
#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>

/*
 * CONCEPTS APPLIQUÉS :
 * 
 * 1. FORME CANONIQUE ORTHODOXE (OCF) :
 *    Obligatoire pour une gestion rigoureuse des objets en C++. Elle comprend :
 *    - Constructeur par défaut : Initialise l'objet dans un état stable.
 *    - Constructeur de copie : Permet de créer un nouvel objet "jumeau" (Deep Copy).
 *    - Surcharge de l'opérateur d'affectation (=) : Permet de copier les données
 *      d'un objet existant vers un autre objet déjà créé, avec sécurité anti-auto-affectation.
 *    - Destructeur : Assure la libération propre des ressources à la fin de vie de l'objet.
 *
 * 2. ENCAPSULATION :
 *    Les données membres (_value et _bits) sont privées pour protéger l'intégrité
 *    de l'objet. L'accès se fait via des fonctions membres publiques (getters/setters).
 *
 * 3. INTRODUCTION À LA VIRGULE FIXE :
 *    Première étape de la représentation d'un nombre réel à l'aide d'un entier (int).
 *    - _value : Stocke la valeur brute.
 *    - _bits : Variable statique constante partagée par tous les objets, fixant 
 *      le "zoom" (la virgule) à 8 bits du bord droit.
 */
class Fixed
{
	private:
		int					_value;
		static const int 	_bits = 8;
	
	public:
    	// --- Forme Canonique Orthodoxe ---
    	Fixed();                              // Constructeur par defaut
    	Fixed(const Fixed &other);            // Constructeur de copie
    	Fixed &operator=(const Fixed &other); // Operateur d'affectation
    	~Fixed();                             // Destructeur

    	// --- Fonctions membres ---
    	int     getRawBits(void) const;
    	void    setRawBits(int const raw);
};

#endif
