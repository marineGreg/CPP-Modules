/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 12:27:19 by mgregoir          #+#    #+#             */
/*   Updated: 2026/02/17 18:24:55 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

int	main(void)
{
	Fixed		a;
	Fixed const	b( Fixed( 5.05f ) * Fixed( 2 ) );

	std::cout << a << std::endl;
	std::cout << ++a << std::endl;
	std::cout << a << std::endl;
	std::cout << a++ << std::endl;
	std::cout << a << std::endl;
	
	std::cout << b << std::endl;
	std::cout << Fixed::max( a, b ) << std::endl;

	// --- Tests supplémentaires pour toutes les fonctionnalités ---
	std::cout << "\n=== Tests arithmétiques ===" << std::endl;
	Fixed		c( 12.42f );
	Fixed const	d( 5 );
	std::cout << "c = " << c << std::endl;
	std::cout << "d = " << d << std::endl;
	std::cout << "c - d = " << (c - d) << std::endl;
	std::cout << "c + d = " << (c + d) << std::endl;
	std::cout << "c * d = " << (c * d) << std::endl;
	std::cout << "c / d = " << (c / d) << std::endl;
	
	std::cout << "\n=== Tests de comparaison ===" << std::endl;
	std::cout << "c > d: " << (c > d) << std::endl;
	std::cout << "c < d: " << (c < d) << std::endl;
	std::cout << "c >= d: " << (c >= d) << std::endl;
	std::cout << "c <= d: " << (c <= d) << std::endl;
	std::cout << "c == d: " << (c == d) << std::endl;
	std::cout << "c != d: " << (c != d) << std::endl;
	
	std::cout << "\n=== Tests de décrémentation ===" << std::endl;
	Fixed e( 10.5f );
	std::cout << "e = " << e << std::endl;
	std::cout << "--e = " << --e << std::endl;
	std::cout << "e = " << e << std::endl;
	std::cout << "e-- = " << e-- << std::endl;
	std::cout << "e = " << e << std::endl;
	
	std::cout << "\n=== Tests min/max ===" << std::endl;
	std::cout << "min(c, d) = " << Fixed::min( c, d ) << std::endl;
	std::cout << "max(c, d) = " << Fixed::max( c, d ) << std::endl;
	
	return 0;
}
