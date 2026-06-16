
#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>
# include <cmath>

/*
 * CONCEPTS APPLIQUÉS :
 * 
 * 1. CONVERSIONS SCALAIRES :
 *    Implémentation de constructeurs convertissant des 'int' et 'float' vers 
 *    le format virgule fixe en utilisant le facteur de zoom (2^8 = 256).
 * 
 * 2. MATHÉMATIQUES BINAIRES :
 *    - Utilisation du décalage de bits (<<) pour multiplier rapidement un entier.
 *    - Utilisation de roundf() pour arrondir précisément les nombres flottants.
 * 
 * 3. DÉ-ZOOMAGE (LOGIQUE DE SORTIE) :
 *    Méthodes toInt() et toFloat() pour extraire la valeur réelle stockée
 *    en inversant l'opération de zoom (division par 256).
 * 
 * 4. SURCHARGE DE L'OPÉRATEUR D'INSERTION (<<) :
 *    Surcharge externe permettant d'envoyer l'objet directement dans std::cout
 *    pour afficher sa représentation flottante.
 */
class Fixed {
	private:
    	int                 _value;
    	static const int    _bits = 8;

	public:
		// --- Forme Canonique Orthodoxe ---
    	Fixed();								// Constructeur par defaut
    	Fixed(const Fixed &other);				// Constructeur de copie
    	Fixed &operator=(const Fixed &other);	// Operateur d'affectation
    	~Fixed();								// Destructeur
		
    	Fixed(const int n);
    	Fixed(const float n);
		
    	int     getRawBits(void) const;
    	void    setRawBits(int const raw);
    
    	float   toFloat(void) const;
    	int     toInt(void) const;
};

std::ostream &operator<<(std::ostream &o, Fixed const &i);

#endif
