/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 12:49:31 by mgregoir          #+#    #+#             */
/*   Updated: 2026/02/04 14:36:58 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>
# include <cmath>

class Fixed {
	private:
    	int                 _value;
    	static const int    _bits = 8;

	public:
    	Fixed();
    	Fixed(const Fixed &src);
    	Fixed &operator=(const Fixed &rhs);
    	~Fixed();

    	Fixed(const int n);
    	Fixed(const float n);

    // Fonctions membres
    	int     getRawBits(void) const;
    	void    setRawBits(int const raw);
    
    	float   toFloat(void) const;
    	int     toInt(void) const;
};

// Surcharge de l'opérateur d'insertion (hors de la classe)
std::ostream &operator<<(std::ostream &o, Fixed const &i);

#endif
