/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 12:49:31 by mgregoir          #+#    #+#             */
/*   Updated: 2026/02/18 16:18:16 by mgregoir         ###   ########.fr       */
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
    	Fixed(const int n);
    	Fixed(const float n);
    	Fixed(const Fixed &other);
    	Fixed &operator=(const Fixed &other);
    	~Fixed();

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
