/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 12:49:31 by mgregoir          #+#    #+#             */
/*   Updated: 2026/02/18 11:28:34 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>

class Fixed
{
	private:
		int					_value;
		static const int 	_bits = 8;
	
	public:
    	// --- Forme Canonique Orthodoxe ---
    	Fixed();                            // Constructeur par défaut
    	Fixed(const Fixed &other);            // Constructeur de recopie
    	Fixed &operator=(const Fixed &other); // Surcharge de l'opérateur d'affectation
    	~Fixed();                           // Destructeur

    	// --- Fonctions membres ---
    	int     getRawBits(void) const;
    	void    setRawBits(int const raw);
};

#endif
