/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 12:49:31 by mgregoir          #+#    #+#             */
/*   Updated: 2026/02/18 15:58:25 by mgregoir         ###   ########.fr       */
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
		// --- Forme Canonique Orthodoxe ---
    	Fixed();
    	Fixed(const Fixed &other);
    	Fixed &operator=(const Fixed &other);
    	~Fixed();
		
    	Fixed(const int n);
    	Fixed(const float n);
		
    	int     getRawBits(void) const;
    	void    setRawBits(int const raw);
    
    	float   toFloat(void) const;
    	int     toInt(void) const;
};

std::ostream &operator<<(std::ostream &o, Fixed const &i);

#endif
