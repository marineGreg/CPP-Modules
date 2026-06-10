/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 12:49:31 by mgregoir          #+#    #+#             */
/*   Updated: 2026/06/10 13:40:44 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>
# include <cmath>

/*
 * CONCEPTS APPLIQUÉS :
 * 
 * 1. SURCHARGE D'OPÉRATEURS COMPLÈTE :
 *    Permet à la classe Fixed de se comporter comme un type numérique natif :
 *    - Comparaisons : Logic sur les valeurs brutes (raw bits).
 *    - Arithmétique : +, -, *, / avec conservation de la précision.
 * 
 * 2. PRÉ-INCRÉMENT VS POST-INCRÉMENT (++a / a++) :
 *    - Pré-incrément : Modifie et renvoie une référence (performant).
 *    - Post-incrément : Prend une copie (photo), modifie, et renvoie la copie.
 *    - Incrément minimal : 1 bit de valeur brute = 1 graduation (0.0039).
 * 
 * 3. FONCTIONS MEMBRES STATIQUES (min / max) :
 *    Outils utilitaires partagés par la classe, acceptant et renvoyant des 
 *    références pour éviter des copies inutiles, avec versions 'const'.
 */
class Fixed {
	private:
    	int                 _value;
    	static const int    _bits = 8;

	public:
    	Fixed();								// Constructeur par defaut
    	Fixed(const int n);						// Constructeur par un int
    	Fixed(const float n);					// Constructeur par un float
    	Fixed(const Fixed &other);				// Constructeur de copie
    	Fixed &operator=(const Fixed &other);	// Operateur d'affectation
    	~Fixed();								// Destructeur

    	int     getRawBits(void) const;
    	void    setRawBits(int const raw);
    	float   toFloat(void) const;
    	int     toInt(void) const;

    	// --- Comparaisons ---
    	bool operator>(const Fixed &other) const;
    	bool operator<(const Fixed &other) const;
    	bool operator>=(const Fixed &other) const;
    	bool operator<=(const Fixed &other) const;
    	bool operator==(const Fixed &other) const;
    	bool operator!=(const Fixed &other) const;

    	// --- Arithmetiques ---
    	Fixed operator+(const Fixed &other) const;
    	Fixed operator-(const Fixed &other) const;
    	Fixed operator*(const Fixed &other) const;
    	Fixed operator/(const Fixed &other) const;

    	// --- Increment / Decrement ---
    	Fixed &operator++(void);       // Pre-increment
    	Fixed operator++(int);        // Post-increment
    	Fixed &operator--(void);       // Pre-decrement
    	Fixed operator--(int);        // Post-decrement

    	// --- Min / Max (Statiques) ---
    	static Fixed &min(Fixed &a, Fixed &b);
    	static const Fixed &min(const Fixed &a, const Fixed &b);
    	static Fixed &max(Fixed &a, Fixed &b);
    	static const Fixed &max(const Fixed &a, const Fixed &b);
};

std::ostream &operator<<(std::ostream &o, Fixed const &i);

#endif
